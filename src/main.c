#include <stdio.h>
#include "process.h"
#include "queue.h"
#include "algorithm.h"
#include "evaluation.h"

Queue JQ;

int main()
{   
    char exp;
    printf("Enable exponential distribution for cpu burst?(Y/N)\n");
    scanf("%c", &exp);
    int exp_int;
    if(exp == 'Y' || exp == 'y') exp_int = 1;
    else exp_int = 0;

    JQ.size = 0;
    printf("\nGenerating Processes...\n");
    for(int i=1; i<=MAX_PROCESS_NUM; i++) {
        Process* nproc = generate_process(i, exp_int);
        insert_queue(&JQ, nproc, arrival_cmp);
    }

    int d=1;
    int i=1;
    int max = JQ.size;
    while(i <= max)
    {
        for(int j=1; j<=d; j++)
        {
            if(i > max) break;
            printf("%d(arri: %d, cpu: %d, io: %d, ios: %d, pri: %d) \n", JQ.arr[i]->pid, JQ.arr[i]->arrival, JQ.arr[i]->cpu_burst, JQ.arr[i]->io_burst, JQ.arr[i]->io_start, JQ.arr[i]->priority);
            i++;
        }
        d *= 2;
        //printf("\n");
    }
    printf("\n");

    printf("cloning queues\n");
    Queue *JQs[NUM_ALGORITHM+1];
    for(int i=1; i<=NUM_ALGORITHM; i++)
    {
        JQs[i] = clone_queue(&JQ);
    }

    // dummy queues for evaluation reference
    Queue DQs[NUM_ALGORITHM+1];
    for(int i=1; i<=NUM_ALGORITHM; i++)
    {
        DQs[i] = *JQs[i];
    }

    int* res1 = FCFS(JQs[1]);
    printf("\n[FCFS]\n");
    print_eval(&DQs[1]);
    print_gantt(res1);

    int* res2 = SJF(JQs[2], 0);
    printf("\n[non-preemptive SJF]\n");
    print_eval(&DQs[2]);
    print_gantt(res2);

    int* res3 = SJF(JQs[3], 1);
    printf("\n[preemptive SJF]\n");
    print_eval(&DQs[3]);
    print_gantt(res3);

    int* res4 = Priority(JQs[4], 0);
    printf("\n[non-preemptive Priority]\n");
    print_eval(&DQs[4]);
    print_gantt(res4);

    int* res5 = Priority(JQs[5], 1);
    printf("\n[preemptive Priority]\n");
    print_eval(&DQs[5]);
    print_gantt(res5);

    int* res6 = RR(JQs[6], 2);
    printf("\n[Round Robin]\n");
    print_eval(&DQs[6]);
    print_gantt(res6);

    int* res7 = LIFO(JQs[7]);
    printf("\n[LIFO]\n");
    print_eval(&DQs[7]);
    print_gantt(res7);

    return 0;
}


