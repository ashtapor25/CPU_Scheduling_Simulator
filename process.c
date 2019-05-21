#include <stdlib.h>
#include <time.h>
#include "process.h"

Process* generate_process(int pid_given) 
{
	Process* newp = malloc(sizeof(Process));
	srand(pid_given);

	newp->pid = pid_given;
	newp->arrival = rand() % (MAX_TIME-20);
	newp->fst_arrival = newp->arrival;
	newp->cpu_burst = rand() % MAX_CPU_BURST + 1;
	newp->priority = rand() % MAX_PRIORITY;
	newp->io_burst = 0;//rand() % MAX_IO_BURST;
	newp->io_start = rand() % (newp->cpu_burst/2) + (newp->cpu_burst/4);
	newp->cpu_remaining = newp->cpu_burst;
	newp->io_remaining = newp->io_burst;
	newp->exec_start = -1; // -1 means not started yet
	newp->exec_end = -1; // -1 means not ended yet

	return newp;
}