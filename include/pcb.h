#ifndef __PCB_H__
#define __PCB_H__

#include "types.h"
#include "adt/list.h"
#include "x86.h"

#define KSTACK_SIZE 128
#define MAX_PROCESS_NUM 64
struct PCB {
	TrapFrame *tf;
	uint8_t kstack[KSTACK_SIZE];
	int lock;
	ListHead list;
};
typedef struct PCB PCB;


extern ListHead RunQP;
extern ListHead FreeQP;

PCB *create_kthread(void *entry);
void sleep(void);
void wakeup(PCB *pcb);
void lock(void);
void unlock(void);


void init_proc(void);
void prcswitch(void);	//switch process to the next one in run Q
void remove(ListHead *list);
void test_producer(void);
void test_consumer(void);
void test(void);
	
#endif
