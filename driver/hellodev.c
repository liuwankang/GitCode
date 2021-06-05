#include <linux/module.h>

#include <linux/moduleparam.h>

#include <linux/cdev.h>

#include <linux/fs.h>

#include <linux/wait.h>

#include <linux/poll.h>

#include <linux/sched.h>

#include <linux/slab.h>

#define BUFFER_MAX (64)

#define OK (0)
#define ERROR (-1)


struct file_operations *gFile;

dev_t devNum;

unsigned int subDevNum = 1;

int reg_major = 232;

int reg_minor = 0;

char buffer[BUFFER_MAX];

struct cdev *gdev;

struct semaphore sema;

int count = 0;
int hello_open(struct inode *p, struct file *f)
{
	down(&sema);
	if(count >= 1)
	{
		up(&sema);
		printk(KERN_INFO "device is busy");
		return -EBUSY;
	}
	count++;
	up(&sema);
	printk(KERN_INFO "hello_open\r\n");

	return 0;

}

int hello_close(struct inode *p, struct file *f)
{
	if(count != 1)
	{
		printk(KERN_INFO "something is wrong");
		return -EFAULT;
	}
	count--;
	return 0;

}


ssize_t hello_write(struct file *f, const char __user *u, size_t s, loff_t *l)

{

	printk(KERN_INFO "hello_write\r\n");
	int writenlen = 0;
	writenlen = BUFFER_MAX>s?s:BUFFER_MAX;
	if(copy_from_user(buffer, u, writenlen))
	{
		return -EFAULT;
	}
	return writenlen;
	
}

ssize_t hello_read(struct file *f, char __user *u, size_t s, loff_t *l)

{

	printk(KERN_INFO "hello_read\r\n");
	int readlen = 0;
	readlen = BUFFER_MAX>s?s:BUFFER_MAX;
	if(copy_to_user(u, buffer, readlen))
	{
		return -EFAULT;
	}
	return readlen;

}



int hello_init(void)
{

    devNum = MKDEV(reg_major , reg_minor);
    
    gdev = kzalloc(sizeof(struct cdev), GFP_KERNEL);
    
    gFile = kzalloc(sizeof(struct file_operations), GFP_KERNEL);

    gFile->open = hello_open;

	gFile->release = hello_close;

	gFile->read = hello_read;

	gFile->write = hello_write;

	gFile->owner = THIS_MODULE;

	cdev_init(gdev, gFile);

	cdev_add(gdev, devNum, subDevNum);
	sema_init(&sema, 1);
	return 0;
		
}

void __exit hello_exit(void)

{

	printk(KERN_INFO " hello driver exit \n");

	cdev_del(gdev);

	kfree(gFile);

	kfree(gdev);

	unregister_chrdev_region(devNum, subDevNum);

	return;
}

module_init(hello_init);

module_exit(hello_exit);

MODULE_LICENSE("GPL");
