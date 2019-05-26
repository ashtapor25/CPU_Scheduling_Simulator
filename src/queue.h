#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "process.h"

// queue based on min-heap
typedef struct queue
{
    Process* arr[MAX_PROCESS_NUM+1];
    int size;
} Queue;

// param: 0 - arrival, 1 - cpu_burst, 2 - priority
int arrival_cmp(Process* p1, Process* p2);
int cpu_cmp(Process* p1, Process* p2);
int priority_cmp(Process* p1, Process* p2);

void insert_queue(Queue* myqueue, Process* proc, int(*cmp)(Process*, Process*));
Process* pop_queue(Queue* myqueue, int(*cmp)(Process*, Process*));
Process* top_queue(Queue* myqueue);

Queue* clone_queue(Queue* myqueue);

#endif