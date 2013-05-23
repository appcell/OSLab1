#include "pcb.h"
#include "debug.h"

PCB PCBStack[MAX_PROCESS_NUM];
int PCBStackTail = 0;
PCB *create_kthread(void *entry)
{
	PCB *pcb;
	pcb = &PCBStack[PSBStackTail];

	/* Initialize the trap frame */
	TrapFrame * tf = ((TrapFrame *)(pcb->kstack + KSTACK_SIZE)) - 1;
	tf->eax = tf->ebx = tf->ecx = tf->edx = tf->edi = tf->esi = tf->ebp = 0;
	tf->ds = tf->es = KSEL(SEG_KDATA);
	tf->eip = (uint32_t)entry;
	tf->cs = KSEL(SEG_KCODE);
	tf->eflags = FL_IF;
	
	/* add this pcb into free queue */
	PCBStackTail ++;
	pcb->tf = tf;
	list_add_before(&FreeQP, &pcb->freeq);

	return pcb;

}
void sleep(void)
{
	asm volatile("int $0x80");
}


void prcswitch(void)
{
	if (current == list_entry(RunQP.prev, PCB, tf) );
		current = list_entry(RunQP.next, PCB, tf);
	else
		current = list_entry(RunQP, PCB, tf);
}
