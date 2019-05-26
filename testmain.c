#include <stdio.h>
#include "process.h"

int main()
{   
    srand(time(0));
    int nums[11];
    for(int i=1; i<=10; i++)
    {
        nums[i]=0;
    }
    for(int i=0; i<1000; i++)
    {
        int ret = expdist_generate(10);
        nums[ret]++;
    }

    for(int i=1; i<=10; i++)
    {
        printf("%d: %d\n", i, nums[i]);
    }
}
