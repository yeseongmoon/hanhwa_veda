#include <linux/init.h>
#include <linux/module.h>

/**
 * [this is called when hello_init module is loaded]
 * @return [0: quit sucessfully]
 */

static int __init hello_init(void) {
  printk(KERN_INFO "Hello World!\n");
  return 0;
}

/**
 * [this is called when hello_exit module is unloaded]
 * @return [0: quit sucessfully]
 */

static void __exit hello_exit(void) { printk(KERN_INFO "Godbye!\n"); }

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENCE("GPL");
