#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>

SYSCALL_DEFINE3(prime_syscall, int, op, int*, basket, int*, count)
{
	int i, j, data, hasDiv = 0, cnt = 0;

	for (i=0;i<op;i++)
        {
                data = basket[i];
                if (data == 1) {
                        continue;
                }
                for (j=2;j<=data/2;j++) // check prime number
                {
                        if(data%j==0) {
                                hasDiv = 1;
                                break;
                        }
                }
                if(!hasDiv){
                 cnt++;
                }
                hasDiv = 0;
        }

	if(put_user(cnt, count)) return -EFAULT;
	return 0;
}
