#include <stdio.h>
#include "evaluation.h"

void print_eval(Queue* myqueue)
{
    //printf("%d\n", myqueue->size);
    float waiting_total=0, turnaround_total=0, response_total=0, cpu_total=0;
    for(int i=1; i<= myqueue->size; i++)
    {
        //printf("<process #%d>\n", myqueue->arr[i]->pid);

        //printf("waiting time: %d\n", (myqueue->arr[i]->exec_end) - (myqueue->arr[i]->fst_arrival) - (myqueue->arr[i]->cpu_burst) - (myqueue->arr[i]->io_burst));
        //printf("turnaround time: %d\n", (myqueue->arr[i]->exec_end) - (myqueue->arr[i]->fst_arrival));
        //printf("response time: %d\n", (myqueue->arr[i]->exec_start) - (myqueue->arr[i]->fst_arrival));

        waiting_total += (myqueue->arr[i]->exec_end) - (myqueue->arr[i]->fst_arrival) - (myqueue->arr[i]->cpu_burst) - (myqueue->arr[i]->io_burst);
        turnaround_total += (myqueue->arr[i]->exec_end) - (myqueue->arr[i]->fst_arrival);
        response_total += (myqueue->arr[i]->exec_start) - (myqueue->arr[i]->fst_arrival);
        cpu_total += myqueue->arr[i]->cpu_burst;
    }
    printf("avg waiting time: %.2f\n", waiting_total/(myqueue->size));
    printf("avg turnaround time: %.2f\n", turnaround_total/(myqueue->size));
    printf("avg response time: %.2f\n", response_total/(myqueue->size));
    printf("cpu utilization: %.2f%%\n", cpu_total/MAX_TIME * 100);
}

void print_gantt(int* res)
{
    int gantt_lines = MAX_TIME / 50;
    for(int l=0; l<gantt_lines; l++)
    {
        int prev = -1;
        for(int i=l*50; i<(l+1)*50; i++)
        {
            if(res[i]==prev)
            {
                printf("---");
            }
            else
            {
                printf("+---");
            }
            prev = res[i];
        }
        printf("+\n");

        prev = -1;
        for(int i=l*50; i<(l+1)*50; i++)
        {
            if(res[i]==prev)
            {
                printf("   ");
            }
            else
            {
                if(res[i]==0)
                {
                    printf("|idl");
                }
                else if(res[i] < 10)
                {
                    printf("| P%d", res[i]);
                }
                else
                {
                    printf("|P%d", res[i]);
                }
            }
            prev = res[i];
        }
        printf("|\n");

        prev = -1;
        for(int i=l*50; i<(l+1)*50; i++)
        {
            if(res[i]==prev)
            {
                printf("---");
            }
            else
            {
                printf("+---");
            }
            prev = res[i];
        }
        printf("+\n");

        prev = -1;
        for(int i=l*50; i<(l+1)*50; i++)
        {
            if(res[i]==prev)
            {
                printf("   ");
            }
            else
            {
                if(i < 10)
                {
                    printf("%d   ", i);
                }
                else if(i <100)
                {
                    printf("%d  ", i);
                }
                else
                {
                    printf("%d ", i);
                }
            }
            prev = res[i];
        }
        printf("%d\n", (l+1)*50);
    }
    int prev = -1;
    for(int i=gantt_lines*50; i<MAX_TIME; i++)
    {
        if(res[i]==prev)
        {
            printf("---");
        }
        else
        {
            printf("+---");
        }
        prev = res[i];
    }
    if(MAX_TIME%50 !=0) printf("+\n");

    prev = -1;
    for(int i=gantt_lines*50; i<MAX_TIME; i++)
    {
        if(res[i]==prev)
        {
            printf("   ");
        }
        else
        {
            if(res[i]==0)
            {
                printf("|idl");
            }
            else if(res[i] < 10)
            {
                printf("| P%d", res[i]);
            }
            else
            {
                printf("|P%d", res[i]);
            }
        }
        prev = res[i];
    }
    if(MAX_TIME%50 !=0) printf("|\n");

    prev = -1;
    for(int i=gantt_lines*50; i<MAX_TIME; i++)
    {
        if(res[i]==prev)
        {
            printf("---");
        }
        else
        {
            printf("+---");
        }
        prev = res[i];
    }
    if(MAX_TIME%50 !=0) printf("+\n");

    prev = -1;
    for(int i=gantt_lines*50; i<MAX_TIME; i++)
    {
        if(res[i]==prev)
        {
            printf("   ");
        }
        else
        {
            if(i < 10)
            {
                printf("%d   ", i);
            }
            else if(i <100)
            {
                printf("%d  ", i);
            }
            else
            {
                printf("%d ", i);
            }
        }
        prev = res[i];
    }
    if(MAX_TIME%50 !=0) printf("%d\n", MAX_TIME);
    
}