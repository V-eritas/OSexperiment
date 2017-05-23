#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    if (fork()==0)
    {
        printf("This is child1\nChild1's PID is %d\n\n", getpid());
    }
    else if (fork()==0)
    {
        printf("This is child2\nChild2's PID is %d\n\n", getpid());
    }
    else
    {
        printf("This is main process\nMain process's PID is %d\n\n", getpid());
    }
    return 0;
}
