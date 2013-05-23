#include "pcb.h"
#include "debug.h"

void sleep(void)
{
	asm volatile("int $0x80");
}


void prcswitch(void)
{
	
}
