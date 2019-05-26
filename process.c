#include <stdlib.h>
#include <time.h>
#include "process.h"

Process* generate_process(int pid_given, int exp_dist) 
{
	Process* newp = malloc(sizeof(Process));
	srand(pid_given + (long)time(0));

	newp->pid = pid_given;
	newp->arrival = rand() % (MAX_TIME-20);
	newp->fst_arrival = newp->arrival;
	if(exp_dist)
	{
		newp->cpu_burst = expdist_generate(MAX_CPU_BURST-1) + 1;
	}
	else
	{
		newp->cpu_burst = rand() % (MAX_CPU_BURST-2) + 2;
	}
	newp->priority = rand() % MAX_PRIORITY;
	newp->io_burst = rand() % MAX_IO_BURST;
	newp->io_start = rand() % (newp->cpu_burst-1) + 1;
	newp->cpu_remaining = newp->cpu_burst;
	newp->io_remaining = newp->io_burst;
	newp->exec_start = -1; // -1 means not started yet
	newp->exec_end = -1; // -1 means not ended yet

	return newp;
}

// generate a number between 1 ~ max_v with exponential distribution
int expdist_generate(int max_v)
{
	long denom = 1;
	for(int i=0; i < max_v; i++) denom *= 2;
	denom -= 1; // (2^max_v - 1) as denominator
	long rand_gen = rand() % denom;
	long cutoff = (denom + 1)/2;

	int ret = 1;
	while(ret < max_v)
	{
		if(rand_gen < cutoff)
		{
			break;
		}
		else
		{
			ret++;
			rand_gen -= cutoff;
			cutoff /= 2;
		}
	}
	return ret;
}