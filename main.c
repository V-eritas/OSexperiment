#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    if (fork()==0)
    {
        printf("This is child process.\n");
        printf("The child process's PID is %d\n", getpid());
        if (fork()==0)
        {
            printf("This is grandchild process.\n");
            printf("The grandchild process's PID is %d\n", getpid());
        }
    }
    else
    {
        printf("This is mian process.\n");
        printf("The main process's PID is %d\n", getpid());
    }
    return 0;
}
