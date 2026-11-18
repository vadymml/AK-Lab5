#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/errno.h>

#include "hello1.h"

struct hello_event {
	struct list_head list;
	ktime_t start_time;
	ktime_t end_time;
};

static LIST_HEAD(event_list);

int print_hello(void)
{
	struct hello_event *event;

	event = kmalloc(sizeof(*event), GFP_KERNEL);

	if (!event) {
		pr_err("hello1: memory allocation failed\n");
		return -ENOMEM;
	}

	event->start_time = ktime_get();

	pr_info("Hello, world!\n");

	event->end_time = ktime_get();

	list_add_tail(&event->list, &event_list);

	return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("hello1: module loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_event *event;
	struct hello_event *tmp;

	list_for_each_entry_safe(event, tmp, &event_list, list) {
		pr_info("hello1: print time: %lld ns\n",
			(long long)ktime_to_ns(
				ktime_sub(event->end_time,
					  event->start_time)));

		list_del(&event->list);
		kfree(event);
	}

	pr_info("hello1: module unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Malysh Vadym");
MODULE_DESCRIPTION("Hello1 module with exported print function and time measurement");
