#include "pcb.h"
#include "semaphore.h"

void new_sem(Semaphore *sem, int value)
{
	lock();

	sem->count = value;
	list_init(&sem->queue);

	NOINTR;
	unlock();
	INTR;
}
void P(Semaphore *sem)
{
	lock();

	sem->count--;
	if (sem->count < 0)
	{
		list_add_before(&sem->queue,&current->semq);
		sleep();
	}

	NOINTR;
	unlock();
	INTR;
}

void
V(Semaphore *sem)
{
	lock();

	sem->count ++;
	if (sem->count <= 0)
	{
		assert(!list_empty(&sem->queue));
		PCB *pcb = list_entry(sem->queue.next, PCB, semq);
		list_del(sem->queue.next);
		wakeup(pcb);
	}

	NOINTR;
	unlock();
	INTR;
}
