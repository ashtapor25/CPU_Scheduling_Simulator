#include <stdlib.h>
#include <stdio.h>
#include "algorithm.h"

int* FCFS(Queue* JQp)
{
    int* res = malloc(sizeof(int)*MAX_TIME);
    Queue RQ;
    Queue WQ;
    Process* running = NULL;
    RQ.size = 0;
    WQ.size = 0;
    int clock = 0;
    while(clock < MAX_TIME)
    {
        // JP -> RQ
        // printf("Job Queue size: %d\n", JQp->size);
        // printf("top element arrival: %d\n", top_queue(JQp)->arrival);

        while( (JQp->size >0) && (JQp->arr[1]->arrival <= clock) )
        {
            Process* temp = pop_queue(JQp, arrival_cmp);
            insert_queue(&RQ, temp, arrival_cmp);
            //printf("pid: %d inserted into RQ\n", temp->pid);
        }

        // < RQ -> Running >
        // no process running
        if(running == NULL)
        {
            if(RQ.size <= 0)
            {
                //res[clock] = 0; // 0 means idle
            }
            else
            {
                running = pop_queue(&RQ, arrival_cmp);
                if(running->exec_start == -1)
                    running->exec_start = clock;
            }
            
        }
        // current process has remaining cpu time
        else
        {

        }
        
        // increment clock
        if(running == NULL)
        {
            res[clock] = 0;
        }
        else
        {
            res[clock] = running->pid;
        }
        clock++;

        // < proceed I/O >
        for(int i=1; i <= WQ.size; i++)
        {
            if(--(WQ.arr[i]->io_remaining) == 0)
            {
                WQ.arr[i]->arrival = clock; // assigned new arrival
                insert_queue(&RQ, WQ.arr[i], arrival_cmp); // insert into waiting queue
            }
        }

        // < proceed running proc >
        if(running != NULL)
        {
            if(--running->cpu_remaining == 0)
            {
                running->exec_end = clock;
                running = NULL;
            }

            else if( (running->io_burst > 0) && (clock - (running->exec_start) == (running->io_start)) )
            {
                insert_queue(&WQ, running, arrival_cmp);
                running = NULL;
            }
        }

    }
    if(running!=NULL)
    {
        running->exec_end = MAX_TIME;
    }

    return res;
}

// preemptive: 0 - false, 1 - true
int* SJF(Queue* JQp, int preemptive)
{
    int* res = malloc(sizeof(int)*MAX_TIME);
    Queue RQ;
    Queue WQ;
    Process* running = NULL;
    RQ.size = 0;
    WQ.size = 0;
    int clock = 0;
    while(clock < MAX_TIME)
    {
        // JP -> RQ
        // printf("Job Queue size: %d\n", JQp->size);
        // printf("top element arrival: %d\n", top_queue(JQp)->arrival);

        while( (JQp->size >0) && (JQp->arr[1]->arrival <= clock) )
        {
            Process* temp = pop_queue(JQp, arrival_cmp);
            insert_queue(&RQ, temp, cpu_cmp);
            //printf("pid: %d inserted into RQ\n", temp->pid);
        }

        // < RQ -> Running >
        // no process running
        if(running == NULL)
        {
            if(RQ.size <= 0)
            {
                //res[clock] = 0; // 0 means idle
            }
            else
            {
                running = pop_queue(&RQ, cpu_cmp);
                if(running->exec_start == -1)
                    running->exec_start = clock;
            }
            
        }
        // current process has remaining cpu time
        else
        {
            if(preemptive)
            {
                insert_queue(&RQ, running, cpu_cmp);
                running = pop_queue(&RQ, cpu_cmp);
                if(running->exec_start == -1)
                    running->exec_start = clock;
            }
        }
        
        // increment clock
        if(running == NULL)
        {
            res[clock] = 0;
        }
        else
        {
            res[clock] = running->pid;
        }
        clock++;

        // < proceed I/O >
        for(int i=1; i <= WQ.size; i++)
        {
            if(--(WQ.arr[i]->io_remaining) == 0)
            {
                WQ.arr[i]->arrival = clock; // assigned new arrival
                insert_queue(&RQ, WQ.arr[i], cpu_cmp); // insert into waiting queue
            }
        }

        // < proceed running proc >
        if(running != NULL)
        {
            if(--running->cpu_remaining == 0)
            {
                running->exec_end = clock;
                running = NULL;
            }

            else if(running->io_burst==0)
            {

            }

            else if(clock - (running->exec_start) == (running->io_start))
            {
                insert_queue(&WQ, running, arrival_cmp);
                running = NULL;
            }
        }

    }
    if(running!=NULL)
    {
        running->exec_end = MAX_TIME;
    }

    return res;
}

// preemptive: 0 - false, 1 - true
int* Priority(Queue* JQp, int preemptive)
{
    int* res = malloc(sizeof(int)*MAX_TIME);
    Queue RQ;
    Queue WQ;
    Process* running = NULL;
    RQ.size = 0;
    WQ.size = 0;
    int clock = 0;
    while(clock < MAX_TIME)
    {
        // JP -> RQ
        // printf("Job Queue size: %d\n", JQp->size);
        // printf("top element arrival: %d\n", top_queue(JQp)->arrival);

        while( (JQp->size >0) && (JQp->arr[1]->arrival <= clock) )
        {
            Process* temp = pop_queue(JQp, arrival_cmp);
            insert_queue(&RQ, temp, priority_cmp);
            //printf("pid: %d inserted into RQ\n", temp->pid);
        }

        // < RQ -> Running >
        // no process running
        if(running == NULL)
        {
            if(RQ.size <= 0)
            {
                //res[clock] = 0; // 0 means idle
            }
            else
            {
                running = pop_queue(&RQ, priority_cmp);
                if(running->exec_start == -1)
                    running->exec_start = clock;
            }
            
        }
        // current process has remaining cpu time
        else
        {
            if(preemptive)
            {
                insert_queue(&RQ, running, priority_cmp);
                running = pop_queue(&RQ, priority_cmp);
                if(running->exec_start == -1)
                    running->exec_start = clock;
            }
        }
        
        // increment clock
        if(running == NULL)
        {
            res[clock] = 0;
        }
        else
        {
            res[clock] = running->pid;
        }
        clock++;

        // < proceed I/O >
        for(int i=1; i <= WQ.size; i++)
        {
            if(--(WQ.arr[i]->io_remaining) == 0)
            {
                WQ.arr[i]->arrival = clock; // assigned new arrival
                insert_queue(&RQ, WQ.arr[i], priority_cmp); // insert into waiting queue
            }
        }

        // < proceed running proc >
        if(running != NULL)
        {
            if(--running->cpu_remaining == 0)
            {
                running->exec_end = clock;
                running = NULL;
            }

            else if(running->io_burst==0)
            {

            }

            else if(clock - (running->exec_start) == (running->io_start))
            {
                insert_queue(&WQ, running, arrival_cmp);
                running = NULL;
            }
        }

    }
    if(running!=NULL)
    {
        running->exec_end = MAX_TIME;
    }

    return res;
}

int* RR(Queue* JQp, int quantum)
{
    int* res = malloc(sizeof(int)*MAX_TIME);
    Queue RQ;
    Queue WQ;
    Process* running = NULL;
    RQ.size = 0;
    WQ.size = 0;
    int clock = 0;
    int q_remaining = quantum;
    while(clock < MAX_TIME)
    {
        // JP -> RQ
        // printf("Job Queue size: %d\n", JQp->size);
        // printf("top element arrival: %d\n", top_queue(JQp)->arrival);

        while( (JQp->size >0) && (JQp->arr[1]->arrival <= clock) )
        {
            Process* temp = pop_queue(JQp, arrival_cmp);
            insert_queue(&RQ, temp, arrival_cmp);
            //printf("pid: %d inserted into RQ\n", temp->pid);
        }

        // < RQ -> Running >
        // no process running
        if(running == NULL)
        {
            if(RQ.size <= 0)
            {
                //res[clock] = 0; // 0 means idle
            }
            else
            {
                running = pop_queue(&RQ, arrival_cmp);
                q_remaining = quantum;
                if(running->exec_start == -1)
                    running->exec_start = clock;
            }
            
        }
        // current process has remaining cpu time
        else
        {
            
        }
        
        // increment clock
        if(running == NULL)
        {
            res[clock] = 0;
        }
        else
        {
            res[clock] = running->pid;
            q_remaining--;
        }
        clock++;

        // < proceed I/O >
        for(int i=1; i <= WQ.size; i++)
        {
            if(--(WQ.arr[i]->io_remaining) == 0)
            {
                WQ.arr[i]->arrival = clock; // assigned new arrival
                insert_queue(&RQ, WQ.arr[i], arrival_cmp); // insert into waiting queue
            }
        }

        // < proceed running proc >
        if(running != NULL)
        {
            if(--running->cpu_remaining == 0)
            {
                running->exec_end = clock;
                running = NULL;
            }

            else if( (running->io_burst > 0) && (clock - (running->exec_start) == (running->io_start)) )
            {
                insert_queue(&WQ, running, arrival_cmp);
                running = NULL;
            }

            else if(q_remaining==0)
            {
                running->arrival = clock;
                insert_queue(&RQ, running, arrival_cmp);
                running = NULL;
            }
        }

    }
    if(running!=NULL)
    {
        running->exec_end = MAX_TIME;
    }

    return res;
}

int* LIFO(Queue* JQp)
{
    int* res = malloc(sizeof(int)*MAX_TIME);
    Queue RQ;
    Queue WQ;
    Process* running = NULL;
    RQ.size = 0;
    WQ.size = 0;
    int clock = 0;
    while(clock < MAX_TIME)
    {
        // JP -> RQ
        // printf("Job Queue size: %d\n", JQp->size);
        // printf("top element arrival: %d\n", top_queue(JQp)->arrival);

        while( (JQp->size >0) && (JQp->arr[1]->arrival <= clock) )
        {
            Process* temp = pop_queue(JQp, arrival_cmp);
            insert_stack(&RQ, temp);
            //printf("pid: %d inserted into RQ\n", temp->pid);
        }

        // < RQ -> Running >
        // no process running
        if(running == NULL)
        {
            if(RQ.size <= 0)
            {
                //res[clock] = 0; // 0 means idle
            }
            else
            {
                running = pop_stack(&RQ);
                if(running->exec_start == -1)
                    running->exec_start = clock;
            }
            
        }
        // current process has remaining cpu time
        else
        {

        }
        
        // increment clock
        if(running == NULL)
        {
            res[clock] = 0;
        }
        else
        {
            res[clock] = running->pid;
        }
        clock++;

        // < proceed I/O >
        for(int i=1; i <= WQ.size; i++)
        {
            if(--(WQ.arr[i]->io_remaining) == 0)
            {
                WQ.arr[i]->arrival = clock; // assigned new arrival
                insert_stack(&RQ, WQ.arr[i]); // insert into waiting queue
            }
        }

        // < proceed running proc >
        if(running != NULL)
        {
            if(--running->cpu_remaining == 0)
            {
                running->exec_end = clock;
                running = NULL;
            }

            else if( (running->io_burst > 0) && (clock - (running->exec_start) == (running->io_start)) )
            {
                insert_queue(&WQ, running, arrival_cmp);
                running = NULL;
            }
        }

    }
    if(running!=NULL)
    {
        running->exec_end = MAX_TIME;
    }

    return res;
}