#include <iostream>

#include "manager.h"

using namespace std;

void task1(Manager m)
{
    for (int i = 1; i <= 50; i++)
    {
        File newf(getRSize(10, 2), to_string(i));
        m.Insert(newf);
    }
    m.showBM();
}
void task2(Manager m)
{
    for (vector<File>::iterator i = (m.getFlist()).begin(); i != (m.getFlist()).end(); ++i)
    {
        if (stoi(i->name) & 0x1)
            m.Delete(*i);
    }
    m.showBM();
}
void task3(Manager m)
{
    double size[5] = {7, 5, 2, 9, 3.5};
    string name[5] = {"A", "B", "C", "D", "E"};
    File tmpf[5] =
    {
        File(size[0], name[0]),
        File(size[1], name[1]),
        File(size[2], name[2]),
        File(size[3], name[3]),
        File(size[4], name[4])
    };
    for (int i = 0; i < 5; i++)
    {
        tmpf[i].show_Loca();
        m.Insert(tmpf[i]);
    }
    m.showBM();
}

int main()
{
    Manager m;
    task1(m);
    task2(m);
    task3(m);
    return 0;
}
