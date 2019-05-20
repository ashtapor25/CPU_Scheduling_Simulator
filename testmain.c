#include <stdio.h>
#include "process.h"
#include "queue.h"

int main()
{   
    RQ.size = 0;
    for(int i=0; i<MAX_PROCESS_NUM; i++) {
        Process* nproc = generate_process(i);
        insert_queue(&RQ, nproc, arrival_cmp);
        printf("size: %d\n", RQ.size);
    }

    int max = RQ.size;
    printf("max: %d\n", max);
    
    int d=1;
    int i=1;
    while(i <= max)
    {
        for(int j=1; j<=d; j++)
        {
            if(i > max) break;
            printf("%d ", RQ.arr[i]->arrival);
            i++;
        }
        d *= 2;
        printf("\n");
    }
    
    
    for(int i=1; i<=max; i++)
    {
        
        Process* nextp = pop_queue(&RQ, arrival_cmp);
        printf("%d\n", nextp->arrival);
        
    }
    

    return 0;
}

    /*
    Process* test = generate_process(0);
    printf("%d\n", test->pid);
    printf("%d\n", test->cpu_burst);
    printf("%d\n", test->priority);
    printf("%d\n", test->io_burst);
    printf("%d\n", test->io_start);
    printf("%d\n", test->cpu_remaining);
    printf("%d\n", test->io_remaining);
    printf("%d\n", test->exec_start);
    printf("%d\n", test->exec_end);
    */