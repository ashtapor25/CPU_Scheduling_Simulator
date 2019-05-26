#include <stdio.h>
#include "process.h"

int main()
{   
    srand(time(0));
    int nums[21];
    for(int i=1; i<=20; i++)
    {
        nums[i]=0;
    }
    for(int i=0; i<1024 * 1024; i++)
    {
        int ret = expdist_generate(20);
        nums[ret]++;
    }

    for(int i=1; i<=20; i++)
    {
        printf("%d: %d\n", i, nums[i]);
    }
}
