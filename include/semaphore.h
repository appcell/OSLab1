#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include "pcb.h"
#define INTR assert(readf() & FL_IF)
#define NOINTR assert(~readf() & FL_IF)

struct Semaphore {
    int count;
    ListHead queue;
};
typedef struct Semaphore Semaphore;

//extern Semaphore empty, full, mutex;

void new_sem(Semaphore *sem, int value);
void P(Semaphore *sem);
void V(Semaphore *sem);


#endif
