#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("BSD License\n");

static int initModule(void) {
  printk(KERN_INFO "Hello Module\n");
  return 0;
}
static void cleanupModule(void) { printk(KERN_INFO "Good-Bye Module\n"); }

module_init(initModule);
module_exit(cleanupModule);
