#include "sk_ioctl.h"
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/major.h>
#include <linux/module.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

int result;
/* Define Prototype of functions */
int sk_open(struct inode *inode, struct file *filp);
int sk_release(struct inode *inode, struct file *filp);
ssize_t sk_write(struct file *filp, const char *buf, size_t count,
                 loff_t *f_pos);
ssize_t sk_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
long sk_ioctl(struct file *flip, unsigned int cmd, unsigned long arg);

/* Implementation of functions */
int sk_open(struct inode *inode, struct file *filp) {
  printk("Device has been opened...\n");
  /* H/W Initialization */
  return 0;
}

int sk_release(struct inode *inode, struct file *filp) {
  printk("Device has been closed...\n");
  return 0;
}

ssize_t sk_write(struct file *filp, const char *buf, size_t count,
                 loff_t *f_pos) {
  char data[10];
  copy_from_user(data, buf, count);
  return count;
}

ssize_t sk_read(struct file *filp, char *buf, size_t count, loff_t *f_pos) {
  char data[20] = "this is read func...";
  copy_to_user(buf, data, count);
  return count;
}

long sk_ioctl(struct file *flip, unsigned int cmd, unsigned long arg) {
  switch (cmd) {
  case SPEED_UP: {
    printk("\n");
    printk("UP\n");
    break;
  }
  case SPEED_DOWN: {
    printk("\n");
    printk("DOWN\n");
    break;
  }
  default:
    return 0;
  }
  return 0;
}

struct file_operations sk_fops = {
    .open = sk_open,
    .release = sk_release,
    .write = sk_write,
    .read = sk_read,
    .unlocked_ioctl = sk_ioctl,
};

static int __init sk_init(void) {
  printk("SK Module is up... \n");
  result = register_chrdev(0, "SK", &sk_fops);
  if (result < 0) {
    printk("Couldn't get a major number...\n");
  }
  printk("major number=%d\n", result);
  return 0;
}

static void __exit sk_exit(void) {
  printk("The module is down...\n");
  unregister_chrdev(result, "SK");
}

module_init(sk_init);
module_exit(sk_exit);
