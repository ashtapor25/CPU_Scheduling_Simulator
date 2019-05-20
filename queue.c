#include "queue.h"

int arrival_cmp(Process* p1, Process* p2)
{
    return (p1->arrival - p2->arrival);
}

int cpu_cmp(Process* p1, Process* p2)
{
    if(p1->cpu_remaining - p2->cpu_remaining == 0)
        return (p1->arrival - p2->arrival);
    else
        return (p1->cpu_remaining - p2->cpu_remaining);
}

int priority_cmp(Process* p1, Process* p2)
{
    if(p1->priority - p2->priority == 0)
        return (p1->arrival - p2->arrival);
    else
        return (p1->priority - p2->priority);
}

void swap(Process** p1, Process** p2)
{
    Process** temp = p1;
    p1 = p2;
    p2 = temp;
    return;
}

void insert_queue(Queue* myqueue, Process* proc, int(*cmp)(Process*, Process*))
{
    int i;
    i = ++(myqueue->size);

    while((i != 1) && (cmp(proc, myqueue->arr[i/2]) < 0))
    {
        myqueue->arr[i] = myqueue->arr[i/2];
        i /= 2;
    }
    myqueue->arr[i] = proc;
    
    return;
}


Process* pop_queue(Queue* myqueue, int(*cmp)(Process*, Process*))
{
    Process* res = myqueue->arr[1];
    Process* temp = myqueue->arr[(myqueue->size)--];

    int parent = 1;
    int child = 2;

    while(child <= myqueue->size)
    {
        if( (child < myqueue->size) && (cmp(myqueue->arr[child+1], myqueue->arr[child]) < 0))
        {
            child++;
        }

        if( cmp(temp, myqueue->arr[child]) <= 0)
        {
            break;
        }

        myqueue->arr[parent] = myqueue->arr[child];
        parent = child;
        child *= 2;
    }
    myqueue->arr[parent] = temp;

    return res;
}

Process* top_queue(Queue* myqueue)
{
    return myqueue->arr[1];
}