#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

const string MAX="max", MIN="min", AVG="average";
string cmd,word[3];

int main()
{
    cin>>cmd;
    if (cmd==MAX)
    {
        execl("/media/veritas/WORK/码/操作系统实验/max", "max", NULL);
    }
    else if (cmd==MIN)
    {
       execl("/media/veritas/WORK/码/操作系统实验/min", "min", NULL);
    }
    else if (cmd==AVG)
    {
        execl("/media/veritas/WORK/码/操作系统实验/average", "average", NULL);
    }
    return 0;
}
