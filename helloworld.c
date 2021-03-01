#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>

static char *message=" ";
module_param(message,charp,0660);

static int no_of_times=0;
module_param(no_of_times,int,0660);


int init_module(void){
	int i;
	printk(KERN_INFO "Hello World CSCE-3402 :) \n");
	for(i=0; i<no_of_times;i++){
		printk(KERN_INFO "%s", message);
	}
	return 0; /*means init_module can't be loaded and failed*/
}
void cleanup_module(void){
	printk(KERN_INFO "Bye Bye CSCE-3402 :)\n");
}

MODULE_LICENSE("GPL");
