/* Start of my_func.c */
#include <linux/kernel.h>
#include <linux/syscalls.h>

SYSCALL_DEFINE0(my_syscall)
{
	printk(KERN_INFO "This is my first system call!\n");
	return 0;
}
