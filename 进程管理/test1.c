#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    int c=fork();
    if (c==0)
    {
        int cc=fork();
        if (cc!=0)
        {
            printf("This is child process\nThe child process's PID is %d\nPID of child process of main process's child process is %d\n\n", getpid(), cc);
        }
        else
        {
            printf("This is grandchild process\nThe grandchild process's PID is %d\n\n", getpid());
        }
    }
    else
    {
        printf("This is main process\nThe main process's PID is %d\nPID of Child process of main process is %d\n\n", getpid(), c);
    }
    return 0;
}
