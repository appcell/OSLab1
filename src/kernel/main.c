#include "kernel.h"
#include "x86.h"
#include "vm.h"
#include "irq.h"

void
os_init(void) {
	init_seg();
	init_debug();
	init_idt();
	init_i8259();
	printk("The OS is now working!\n");
	printk("This is a common string.\n");
	printk("This is a string with an integer num: %d.\n",3);
	sti();
	while (TRUE) {
		wait_intr();
	}
}

void
entry(void) {
	init_kvm();
	void(*volatile next)(void) = os_init;
	asm volatile("addl %0, %%esp" : : ""(KOFFSET));
	next();
	panic("init code should never return");
}

