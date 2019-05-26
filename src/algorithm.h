#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__

#define NUM_ALGORITHM 6

#include "queue.h"

int* FCFS(Queue* JQp);
int* SJF(Queue* JQp, int preemptive);
int* Priority(Queue* JQp, int preemptive);
int* RR(Queue* JQp, int quantum);

#endif