/*
 * BiscuitOS Common system call: Four paramenter
 *
 * (C) 2020.03.20 BuddyZhang1 <buddy.zhang@aliyun.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/kernel.h>
#include <linux/syscalls.h>

/*
 * SYSCALL_DEFINE4(): Four paramenter
 */
SYSCALL_DEFINE4(hello_BiscuitOS, char __user *, strings, 
			int, nr_write, int, nr_read, int __user *, reader)
{
	char buffer[128];
	const char *kstring = "Kernel_BiscuitOS";
	int Kreader = 8;

	/* Copy string from userspace */
	if (copy_from_user(buffer, strings, nr_write)) {
		printk("copy_from_user() error\n");
		return -EINVAL;
	}

	printk("Hello BiscuitOS: %s\n", buffer);

	/* Copy kernel string to userspace */
	if (copy_to_user(strings, kstring, nr_read)) {
		printk("copy_to_user() error\n");
		return -EINVAL;
	}

	/* Copy kread to userspace */
	if (copy_to_user(reader, &Kreader, sizeof(int))) {
		printk("Reader copy failed\n");
		return -EINVAL;
	}

	return 0;
}
