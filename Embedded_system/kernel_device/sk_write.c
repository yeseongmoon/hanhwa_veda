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
  char data[11];
  copy_from_user(data, buf, count);
  printk("data >>>>> = %s\n", data);
  return count;
}

struct file_operations sk_fops = {
    .open = sk_open,
    .release = sk_release,
    .write = sk_write,
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
