#include "kernel.h"
#include "x86.h"
#include "vm.h"
#include "irq.h"
#include "pcb.h"


void
os_init(void) {
	char aaa='A';
	
	init_seg();
	init_debug();
	init_idt();
	init_i8259();
	printk("The OS is now working!\n");
	printk("This is a common string.\n");
	printk("This is a string with an integer num: %d.\n",3);
printk("This is a string with an x num valued 335: %x.\n",335);
printk("This is a string with two nums: %d and %x.\n",3,334);
printk("This is a string with a string: %s.\n","hello world");
printk("This is a string with a char: %c.\n",aaa);
printk("This is a string with a %");
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

