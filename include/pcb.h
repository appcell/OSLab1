#ifndef __PCB_H__
#define __PCB_H__

#include "const.h"
#include "types.h"
#include "adt/list.h"
#include "x86.h"
#include "semaphore.h"

#define KSTACK_SIZE 128
#define MAX_PROCESS_NUM 64
struct PCB {
	TrapFrame *tf;
	uint8_t kstack[KSTACK_SIZE];
	ListHead runq, freeq;

	int lock_count;
	ListHead semq;
};
typedef struct PCB PCB;

extern PCB *current;
extern PCB PCBStack[];
extern int PCBStackTail;
extern PCB *temp;	//???

extern ListHead RunQP;
extern ListHead FreeQP;

PCB *create_kthread(void *entry);
void sleep(void);
void wakeup(PCB *pcb);
void lock(void);
void unlock(void);

void init_proc(void);	//initialize the processes
void prcswitch(void);	//switch process to the next one in run Q
void remove(ListHead *list);	//remove a list node
void test_producer(void);
void test_consumer(void);
void test_setup(void);
	
#endif
