#include <stdio.h>
#include "process.h"
#include "queue.h"
#include "algorithm.h"
#include "evaluation.h"

Queue JQ;

int main()
{   
    JQ.size = 0;
    for(int i=1; i<=MAX_PROCESS_NUM; i++) {
        Process* nproc = generate_process(i);
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
            printf("%d(arri: %d, cpu: %d, io: %d, ios: %d, pri: %d) ", JQ.arr[i]->pid, JQ.arr[i]->arrival, JQ.arr[i]->cpu_burst, JQ.arr[i]->io_burst, JQ.arr[i]->io_start, JQ.arr[i]->priority);
            i++;
        }
        d *= 2;
        printf("\n");
    }

    printf("cloning queues\n");
    Queue *JQ1, *JQ2, *JQ3, *JQ4, *JQ5, *JQ6;
    JQ1 = clone_queue(&JQ);
    JQ2 = clone_queue(&JQ);
    JQ3 = clone_queue(&JQ);
    JQ4 = clone_queue(&JQ);
    JQ5 = clone_queue(&JQ);
    JQ6 = clone_queue(&JQ);

    Queue TQ1, TQ2, TQ3, TQ4, TQ5, TQ6;
    TQ1 = *JQ1;
    TQ2 = *JQ2;
    TQ3 = *JQ3;
    TQ4 = *JQ4;
    TQ5 = *JQ5;
    TQ6 = *JQ6;

    int* res1 = FCFS(JQ1);
    printf("\nFCFS\n");
    for(int i=0; i<MAX_TIME; i++)
    {
        printf("%d ", res1[i]);
    }
    printf("\n");
    print_eval(&TQ1);

    int* res2 = SJF(JQ2, 0);
    printf("\nnon-preemptive SJF\n");
    for(int i=0; i<MAX_TIME; i++)
    {
        printf("%d ", res2[i]);
    }
    printf("\n");
    print_eval(&TQ2);

    int* res3 = SJF(JQ3, 1);
    printf("\npreemptive SJF\n");
    for(int i=0; i<MAX_TIME; i++)
    {
        printf("%d ", res3[i]);
    }
    printf("\n");
    print_eval(&TQ3);

    int* res4 = Priority(JQ4, 0);
    printf("\nnon-preemptive Priority\n");
    for(int i=0; i<MAX_TIME; i++)
    {
        printf("%d ", res4[i]);
    }
    printf("\n");
    print_eval(&TQ4);

    int* res5 = Priority(JQ5, 1);
    printf("\npreemptive Priority\n");
    for(int i=0; i<MAX_TIME; i++)
    {
        printf("%d ", res5[i]);
    }
    printf("\n");
    print_eval(&TQ5);

    int* res6 = RR(JQ6, 2);
    printf("\nRound Robin\n");
    for(int i=0; i<MAX_TIME; i++)
    {
        printf("%d ", res6[i]);
    }
    printf("\n"); 
    print_eval(&TQ6);

    return 0;
}


