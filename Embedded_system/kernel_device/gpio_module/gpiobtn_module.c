#include <linux/cdev.h> /* 문자 디바이스 */
#include <linux/fs.h>   /* open( ), read( ), write( ), close( ) 커널 함수 */
#include <linux/gpio.h> /* GPIO 함수 */
#include <linux/interrupt.h> /* 인터럽트 처리를 위한 헤더 파일 */
#include <linux/io.h>        /* ioremap( ), iounmap( ) 커널 함수 */
#include <linux/module.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/string.h>
#include <linux/timer.h>
#include <linux/uaccess.h> /* copy_to_user( ), copy_from_user( ) 커널 함수 */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YoungJin Suh");
MODULE_DESCRIPTION("Raspberry Pi GPIO LED Device Module");

#if 0
//#define BCM_IO_BASE 0x20000000 	/* Raspberry Pi B/B+의 I/O Peripherals 주소 */
#define BCM_IO_BASE 0x3F000000 /* Raspberry Pi 2/3의 I/O Peripherals 주소 */      

#else
#define BCM_IO_BASE 0xFE000000 /* Raspberry Pi 4의 I/O Peripherals 주소 */
#endif

#define GPIO_BASE (BCM_IO_BASE + 0x200000) /* GPIO 컨트롤러의 주소 */
#define GPIO_SIZE (256) /* 0x7E2000B0 - 0x7E2000000 + 4 = 176 + 4 = 180 */

/* GPIO 설정 매크로 */
#define GPIO_IN(g)                                                             \
  (*(gpio + ((g) / 10)) &= ~(7 << (((g) % 10) * 3))) /* 입력 설정 */
#define GPIO_OUT(g)                                                            \
  (*(gpio + ((g) / 10)) |= (1 << (((g) % 10) * 3))) /* 출력 설정 */
#define GPIO_SET(g) (*(gpio + 7) = 1 << g)          /* 비트 설정 */
#define GPIO_CLR(g) (*(gpio + 10) = 1 << g) /* 설정된 비트 해제 */
#define GPIO_GET(g)                                                            \
  (*(gpio + 13) & (1 << g)) /* 현재 GPIO의 비트에 대한 정보 획득 */                        

/* 디바이스 파일의 주 번호와 부 번호 */
#define GPIO_MAJOR 201
#define GPIO_MINOR 0
#define GPIO_DEVICE "gpiobtn" /* 디바이스 디바이스 파일의 이름 */

#define GPIO_SW 536 /* 스위치에 대한 GPIO의 번호 */

/* 입출력 함수를 위한 선언 */
static int gpiobtn_open(struct inode *, struct file *);
static int gpiobtn_close(struct inode *, struct file *);
// static ssize_t gpiobtn_read(struct file *, char *, size_t, loff_t *);
// static ssize_t gpiobtn_write(struct file *, const char *, size_t, loff_t *);
static ssize_t gpiobtn_ioctl(struct file *filp, unsigned int cmd,
                             unsigned long arg);

/* 유닉스 입출력 함수들의 처리를 위한 구조체 */
static struct file_operations gpio_fops = {
    .owner = THIS_MODULE,
    // .read = gpiobtn_read,
    // .write = gpiobtn_write,
    .open = gpiobtn_open,
    .release = gpiobtn_close,
    .unlocked_ioctl = gpiobtn_ioctl,
};

struct cdev gpio_cdev;
static int btn_irq;
pid_t app_pid;

static ssize_t gpiobtn_ioctl(struct file *filp, unsigned int cmd,
                             unsigned long arg) {
  switch (cmd) {
  case _IO(0, 3):
    app_pid = (int)arg;
    printk(KERN_INFO "PID: %d\n", app_pid);
    break;
  default:
    return -EINVAL;
  }
  return 0;
}

/* 인터럽트 처리를 위한 인터럽트 서비스 루틴(Interrupt Service Routine) */

static irqreturn_t btn_interrupt(int irq, void *data) {
  static struct kernel_siginfo sig_info;
  static struct task_struct *task;
  memset(&sig_info, 0, sizeof(struct kernel_siginfo));
  sig_info.si_signo = SIGIO;
  sig_info.si_code = SI_USER;

  if (app_pid > 0) {
    task = pid_task(find_vpid(app_pid), PIDTYPE_PID);
    if (task) {
      printk("Find app!\n");
      send_sig_info(SIGIO, &sig_info, task);
      printk("Send Signal\n");
    }
  }

  return IRQ_HANDLED;
}

int init_module(void) {
  dev_t devno;
  unsigned int count;
  int err;

  printk(KERN_INFO "Hello module!\n");

  /* 문자 디바이스를 등록한다. */
  devno = MKDEV(GPIO_MAJOR, GPIO_MINOR);
  register_chrdev_region(devno, 1, GPIO_DEVICE);

  /* 문자 디바이스를 위한 구조체를 초기화한다. */
  cdev_init(&gpio_cdev, &gpio_fops);

  gpio_cdev.owner = THIS_MODULE;
  count = 1;
  err = cdev_add(&gpio_cdev, devno, count); /* 문자 디바이스를 추가한다. */ if (err < 0) { 
  

    printk("Error : Device Add\n");
    return -1;
  }

  printk("'mknod /dev/%s c %d 0'\n", GPIO_DEVICE, GPIO_MAJOR);
  printk("'chmod 666 /dev/%s'\n", GPIO_DEVICE);

  /* GPIO 사용을 요청한다. */
  gpio_request(GPIO_SW, "SWITCH");
  btn_irq = gpio_to_irq(GPIO_SW); /* GPIO 인터럽트 번호 획득 */
  err = request_irq(btn_irq, btn_interrupt, IRQF_TRIGGER_RISING, "switch",
                    NULL); /* GPIO 인터럽트 핸들러 등록 */

  return 0;
}

void cleanup_module(void) {
  dev_t devno = MKDEV(GPIO_MAJOR, GPIO_MINOR);
  unregister_chrdev_region(devno, 1); /* 문자 디바이스의 등록을 해제한다. */ 

  cdev_del(&gpio_cdev); /* 문자 디바이스의 구조체를 해제한다. */

  /* 사용이 끝난 인터럽트 해제 */
  free_irq(btn_irq, NULL);

  /* 더 이상 사용이 필요 없는 경우 관련 자원을 해제한다. */
  gpio_free(GPIO_SW);
  printk(KERN_INFO "Good-bye module!\n");
}

static int gpiobtn_open(struct inode *inod, struct file *fil) {
  printk("GPIO Device opened(%d/%d)\n", imajor(inod), iminor(inod));

  return 0;
}

static int gpiobtn_close(struct inode *inod, struct file *fil) {
  printk("GPIO Device closed(%d)\n",
         MAJOR(fil->f_path.dentry->d_inode->i_rdev));

  return 0;
}
//
// static ssize_t gpiobtn_read(struct file *inode, char *buff, size_t len,
//                             loff_t *off) {
//   int count;
//
//   strcat(msg, " from Kernel");
//
//   count = copy_to_user(buff, msg,
//                        strlen(msg) + 1); /* 사용자 영역으로 데이터를 보낸다. */
//                        
//
//
//
//
//
//
//
//
//
//
//
//   printk("GPIO Device(%d) read : %s(%d)\n",
//          MAJOR(inode->f_path.dentry->d_inode->i_rdev), msg, count);
//
//   return count;
// }
//
// static ssize_t gpiobtn_write(struct file *inode, const char *buff, size_t
// len,
//                              loff_t *off) {
//   short count;
//
//   memset(msg, 0, BLOCK_SIZE);
//   count = copy_from_user(msg, buff,
//                          len); /* 사용자 영역으로부터 데이터를 가져온다. */
//
//
//   /* LED를 설정한다. */
//   gpio_set_value(GPIO_LED, (!strcmp(msg, "0")) ? 0 : 1);
//
//   printk("GPIO Device(%d) write : %s(%ld)\n",
//          MAJOR(inode->f_path.dentry->d_inode->i_rdev), msg, len);
//
//   return count;
// }
