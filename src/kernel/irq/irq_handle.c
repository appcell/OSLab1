#include "x86.h"
#include "kernel.h"
#include "adt/list.h"
#include "pcb.h"

void irq_handle(TrapFrame *tf) {

	int irq = tf->irq;
	current->tf = tf;
	printk("%d\n",irq);
	assert(irq >= 0);

	if (irq < 1000) {
		// exception
		if(irq == 0x80)
		{
			prcswitch();
		}
		cli();
		printk("Unexpected exception #%d\n", irq);
		printk(" errorcode %x\n", tf->err);
		printk(" location  %d:%x, esp %x\n", tf->cs, tf->eip, tf);
		panic("unexpected exception");
	} else if (irq >= 1000) {
		// external interrupt
	}
}

