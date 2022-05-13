#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>

#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/fcntl.h> /*Helps fix O_ACCMODE*/
#include <linux/sched.h> /*Helps fix TASK_UNINTERRUPTIBLE */
#include <linux/fs.h> /*Helps fix the struct intializer */

#include<linux/slab.h>                 //kmalloc()
#include<linux/uaccess.h>              //copy_to/from_user()
#include <linux/ioctl.h>

#include <linux/proc_fs.h>    // proc file system
#include <linux/compiler.h>
#include <linux/types.h>
#include <linux/proc_ns.h>

#include <linux/kobject.h>

#include <linux/interrupt.h>

#include <linux/kthread.h> // therad 
#include <linux/delay.h>   // sleep 
#include <linux/sched.h>  
#include <linux/mutex.h>
/*

	1  create a module 
	2. create a thread and execute.

*/

MODULE_LICENSE("GPL");
MODULE_LICENSE("GPL v2");
MODULE_LICENSE("Dual BSD/GPL");
//____________________________________________________
//DEFINE_MUTEX(&my_mutex)
//_______________________________________________________


int  my_thread_handle(void *p);

int count =0;
struct task_struct * char_thread,*char_thread1;

int my_thread_handle(void *p)
{
	int i =0;
	while(!kthread_should_stop())
	{
		//mutex_lock(&my_mutex);
		//for(i =0;i<100;i++)
		//{
			printk("my therad function %d",count++);
			count++;
		//}
		//mutex_unlock(&my_mutex);
	}	
	return 0;
}


static int __init my_thread_driver_init(void)
{
	
	printk("hello world\n");


	char_thread = kthread_run(my_thread_handle, NULL, "vinay_therad");

	if(char_thread)
	{
		printk("thread created successfully");
	}
	else
	{
		printk("thread created failed");
		 
	}

	char_thread1 = kthread_run(my_thread_handle, NULL, "vinay_therad1");

	if(char_thread1)
	{
		printk("thread1 created successfully");
	}
	else
	{
		printk("thread created failed");
		 
	}
	printk("my therad function %d",count);
	return 0;
}

static void __exit my_therad_driver_exit(void)
{

	printk("exit hello world\n");

	kthread_stop(char_thread);
	kthread_stop(char_thread1);
}
module_init(my_thread_driver_init);
module_exit(my_therad_driver_exit);

