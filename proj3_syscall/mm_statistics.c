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
		if ((temp->flags & (1 << PG_referenced))) {
			page_count++;
		}
		//printk("ref %d\n", page_ref_count(temp));
	}

	printk(KERN_INFO "The current number of pages those reference bits are set : %d\n", page_count);
}

void cum_num_page_moved(struct lruvec *lruvec, int flag)
{
	switch(flag) {
		case LRU_ACTIVE_FILE:
			printk(KERN_INFO "The cumulative number of pages moved from active to inactive(FILE): %lu\n", lruvec->active_file_to_inactive);
			break;
		case LRU_INACTIVE_FILE:
			printk(KERN_INFO "The cumulative number of pages moved from inactive to active(FILE): %lu\n", lruvec->inactive_file_to_active);
			break;
		case LRU_ACTIVE_ANON:
			printk(KERN_INFO "The cumulative number of pages moved from active to inactive(ANON): %lu\n", lruvec->active_anon_to_inactive);
			break;
		case LRU_INACTIVE_ANON:
			printk(KERN_INFO "The cumulative number of pages moved from inactive to active(ANON): %lu\n", lruvec->inactive_anon_to_active);
			break;
		default:
			break;
	}
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
	cum_num_page_moved(lruvec, LRU_ACTIVE_FILE);
	printk(KERN_INFO "LRU_INACTIVE_FILE\n");
	num_pages(&lruvec->lists[LRU_INACTIVE_FILE]);
	num_ref_pages(&lruvec->lists[LRU_INACTIVE_FILE]);
	cum_num_page_moved(lruvec, LRU_INACTIVE_FILE);
	printk(KERN_INFO "LRU_ACTIVE_ANON\n");
	num_pages(&lruvec->lists[LRU_ACTIVE_ANON]);
	num_ref_pages(&lruvec->lists[LRU_ACTIVE_ANON]);
	cum_num_page_moved(lruvec, LRU_ACTIVE_ANON);
	printk(KERN_INFO "LRU_INACTIVE_ANON\n");
	num_pages(&lruvec->lists[LRU_INACTIVE_ANON]);
	num_ref_pages(&lruvec->lists[LRU_INACTIVE_ANON]);
	cum_num_page_moved(lruvec, LRU_INACTIVE_ANON);

	printk(KERN_INFO "The cumulative number of eviction : %lu\n", lruvec->evic_count);

	spin_unlock_irq(&current_pglist->__lruvec.lru_lock);

	printk(KERN_INFO "\n");
}

SYSCALL_DEFINE0(mm_statistics_syscall)
{
	show_list();
	return 0;
}
