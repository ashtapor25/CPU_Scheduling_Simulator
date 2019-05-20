#include <stdio.h>
#include "process.h"
#include "queue.h"
#include "algorithm.h"

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

    int* res = RR(&JQ, 2);
    for(int i=0; i<MAX_TIME; i++)
    {
        printf("%d ", res[i]);
    }
    printf("\n");
    
    return 0;
}


