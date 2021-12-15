/* start of practice.c */
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/memcontrol.h>
#include <linux/list.h>
#include <linux/cpuset.h>

void num_pages(struct list_head *src) {
	int page_count = 0;
	struct page *temp;

	list_for_each_entry(temp, src, lru) {
		page_count++;
	}

	printk(KERN_INFO "The current number of pages : %d\n", page_count);
}

void num_ref_pages(struct list_head *src) {
	int page_count = 0;
	struct page *temp;

	list_for_each_entry(temp, src, lru) {
		if (temp->counters)
			page_count++;
	}

	printk(KERN_INFO "The current number of pages those reference bits are set : %d\n", page_count);
}

void show_list(void)
{
	struct pglist_data *current_pglist = NULL;
	struct lruvec *lruvec = NULL;

	current_pglist = NODE_DATA(0);

	if (current_pglist->node_present_pages == 0) {
		printk(KERN_INFO "Current node does not have any pages.\n");
	}

	spin_lock_irq(&current_pglist->__lruvec.lru_lock);

	lruvec = &current_pglist->__lruvec;

	printk(KERN_INFO "LRU_ACTIVE_FILE\n");
	num_pages(&lruvec->lists[LRU_ACTIVE_FILE]);
	num_ref_pages(&lruvec->lists[LRU_ACTIVE_FILE]);
	printk(KERN_INFO "LRU_INACTIVE_FILE\n");
	num_pages(&lruvec->lists[LRU_INACTIVE_FILE]);
	num_ref_pages(&lruvec->lists[LRU_INACTIVE_FILE]);
	printk(KERN_INFO "LRU_ACTIVE_ANON\n");
	num_pages(&lruvec->lists[LRU_ACTIVE_ANON]);
	num_ref_pages(&lruvec->lists[LRU_ACTIVE_ANON]);
	printk(KERN_INFO "LRU_INACTIVE_ANON\n");
	num_pages(&lruvec->lists[LRU_INACTIVE_ANON]);
	num_ref_pages(&lruvec->lists[LRU_INACTIVE_ANON]);
	printk(KERN_INFO "LRU_UNEVICTABLE\n");
	num_pages(&lruvec->lists[LRU_UNEVICTABLE]);
	num_ref_pages(&lruvec->lists[LRU_UNEVICTABLE]);

	spin_unlock_irq(&current_pglist->__lruvec.lru_lock);
}

SYSCALL_DEFINE0(mm_statistics_syscall)
{
	show_list();
	return 0;
}