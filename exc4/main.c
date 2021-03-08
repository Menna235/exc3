#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <linux/slab.h>

struct myfile{
	struct file * f;
	mm_segment_t fs;
	loff_t pos;
};

struct myfile * open_file_for_read (char * filename){
	
	struct myfile * menna;
	
	menna = kmalloc(sizeof(struct myfile), GFP_KERNEL);

	menna -> f = NULL;

	int err=0;
	menna -> fs = get_fs();
	set_fs(get_ds());
	menna -> f=filp_open(filename, O_RDONLY, 0);
	set_fs(menna -> fs);
	if (IS_ERR(menna -> f)){
			err=PTR_ERR(menna -> f);
			return NULL;
	}
	return menna;
}
volatile int read_from_file_until (struct myfile * mf, char * buf, unsigned long vlen, char c){

	int sol;

	mf -> fs = get_fs();
	set_fs(get_ds());

	sol = vfs_read (mf -> f, buf, vlen, &(mf -> pos));

	set_fs(mf -> fs);
	return sol;

}
void close_file (struct myfile * mf){

	filp_close(mf -> f, NULL);
}


int init_module(void){

	char * bufff;
	bufff= kmalloc(150,GFP_KERNEL);
	
	printk(KERN_INFO "Hello World CSCE-3402 :) \n");
	struct myfile * menna =  open_file_for_read ("/proc/version");

	int solution = read_from_file_until(menna, bufff,150,' ');
	printk(KERN_INFO "%s\n",bufff);
	close_file(menna);
	return 0; /*means init_module can't be loaded and failed*/
}
void cleanup_module(void){
	printk(KERN_INFO "Bye Bye CSCE-3402 :)\n");
}

MODULE_LICENSE("GPL");
