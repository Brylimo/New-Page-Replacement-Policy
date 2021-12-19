/* Start of ref_counter.c */
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/mm.h>
#include <linux/memcontrol.h>
#include <linux/list.h>
#include <linux/cpuset.h>
#include <linux/swap.h>

#define TIMER_TIMEOUT		1
#define MY_MAXIMUM_VALUE 	200

int gold_key = MY_MAXIMUM_VALUE;
static struct timer_list timer;

static void timer_handler(struct timer_list *tl)
{
	struct pglist_data *current_pglist = NULL;
	struct lruvec *lruvec = NULL;
	struct page *temp;
	struct list_head *src;
	enum lru_list lru;

	current_pglist = NODE_DATA(0);
	
	if (current_pglist->node_present_pages == 0) {
		printk(KERN_INFO "Current node does not have any pages.\n");
	}	

	lruvec = &current_pglist->__lruvec;
	
	lru_add_drain();

	spin_lock_irq(&lruvec->lru_lock);
	
	for_each_lru(lru) 
	{
		src = &lruvec->lists[lru];
		list_for_each_entry(temp, src, lru) {
			if ((temp->flags & (1 << PG_referenced))) {
				if (page_ref_count(temp) >= MY_MAXIMUM_VALUE)
				{
					continue;
				}
				page_ref_add(temp, 1);
				temp->flags &= ~(1UL << PG_referenced);
			}
		}
	}
	spin_unlock_irq(&lruvec->lru_lock);
	mod_timer(&timer, jiffies + TIMER_TIMEOUT*HZ);
}

SYSCALL_DEFINE0(ref_counter_syscall)
{
	timer_setup(&timer, timer_handler, 0);
	mod_timer(&timer, jiffies + TIMER_TIMEOUT*HZ);

	return 0;
}
