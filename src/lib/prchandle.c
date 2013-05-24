#include "pcb.h"
#include "debug.h"
#include "semaphore.h"



PCB * current = NULL;
PCB * temp;

ListHead RunQP;
ListHead FreeQP;
	
PCB PCBStack[MAX_PROCESS_NUM];
int PCBStackTail;

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
	temp=list_entry(current->runq.prev,PCB, runq);
	list_add_before(&FreeQP,&current->freeq);
	list_del(&current->runq);

	asm volatile("int $0x80");	// insert a software interruption
}

void wakeup(PCB *pcb)
{
	ListHead *wake_temp;
	PCB *pcb_temp;
	list_foreach(wake_temp,&FreeQP)
	{
		if(list_entry(wake_temp,PCB,freeq) == pcb)
		{
			pcb_temp = list_entry(wake_temp,PCB,freeq); 
			list_del(&pcb_temp->freeq);
			list_add_before(&RunQP,&pcb_temp->runq);
		}
	}

}


void lock(void)
{
	cli();
	current->lock_count++;
}

void unlock(void)
{
	current->lock_count--;
	assert(current->lock_count >= 0);

	if (current->lock_count == 0) sti();
}

void prcswitch(void)
{
	if (current == list_entry(RunQP.prev, PCB, runq) )
		current = list_entry(RunQP.next, PCB, runq);
	else
		current = list_entry(current->runq.next, PCB, runq);
}


void init_all()
{
	int i,j;
	list_init(&RunQP);
	list_init(&FreeQP);
	current=list_entry(&RunQP,PCB,runq);
	PCBStackTail=0;
	
	for (i = 0; i < MAX_PROCESS_NUM; i++)
	{
		PCBStack[i].tf = NULL;
		PCBStack[i].lock_count=0;
		for(j = 0; j < KSTACK_SIZE; j++)
			PCBStack[i].kstack[j] = 0;  
	}
	test_setup();
}


