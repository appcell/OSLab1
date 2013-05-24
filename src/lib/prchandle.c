#include "pcb.h"
#include "debug.h"


PCB *current=NULL;
ListHead RunQP;
ListHead FreeQP;	
PCB PCBStack[MAX_PROCESS_NUM];
int PCBStackTail = 0;
PCB *create_kthread(void *entry)
{
	PCB *pcb;
	pcb = &PCBStack[PCBStackTail];

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
	list_add_before(&FreeQP,&current->freeq);
	list_del(&current->runq);
	asm volatile("int $0x80");
}
void wakeup(PCB *pcb)
{
	ListHead * temp = &FreeQP;
	list_foreach(temp,&FreeQP)
	{
		if(list_entry(temp,PCB,freeq)==pcb)
		{
			remove(list_entry(temp,PCB,freeq));
			list_add_before(&RunQP,list_entry(temp,PCB,runq));
		}
	}

}

void lock(void)
{
	cli();
}

void unlock(void)
{
	sti();
}

void remove(ListHead *list)
{
	list_del(list);
}
void prcswitch(void)
{
	if (current == list_entry(RunQP.prev, PCB, tf) )
		current = list_entry(RunQP.next, PCB, tf);
	else
		current = list_entry(&RunQP, PCB, tf);
}

