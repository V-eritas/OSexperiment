#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
#include <iomanip>
#define MAX 0xffffff
using namespace std;

struct Pro
{
    string name;
    int arrival;
    int ts;
    int whole;
    int finish;
    int in;         // 就绪标志
    Pro() {}
    Pro(string _name, int _arrival, int _ts): name(_name), arrival(_arrival), ts(_ts) {}
    bool operator<(const Pro& t)
    {
        return name < t.name;
    }
};
vector<Pro> Sch;

void init()
{
    int siz = Sch.size();
    for (int i = 0; i < siz; i++)
    {
        Sch[i].finish = Sch[i].whole = -1;
        Sch[i].in = 0;
    }
}
bool cmp1(const Pro &t1, const Pro &t2)
{
    return t1.arrival < t2.arrival;
}
bool cmp2(const Pro &t1, const Pro &t2)
{
    return t1.ts < t2.ts;
}
void show()
{
    sort(Sch.begin(), Sch.end());
    cout << left;
    cout << setw(10) << "name"
         << setw(10) << "fin_t"
         << setw(10) << "ta_t"
         << setw(10) << "wta_t"
         << endl;
    for (int i = 0; i < Sch.size(); i++)
    {
        cout << setw(10) << Sch[i].name
             << setw(10) << Sch[i].finish
             << setw(10) << Sch[i].whole
             << setw(10) << setprecision(6) << double(Sch[i].whole) / Sch[i].ts
             << endl;
    }
}
void FCFS();
void RR();
void SJF();
void HRN();

int main()
{
    ifstream in("in.txt");
    if (!in)
    {
        cout << "File Open Failure\n";
        exit(1);
    }
    while (!in.eof())
    {
        Pro t;
        in >> t.name >> t.arrival >> t.ts;
        Sch.push_back(t);
    }
    in.close();
    FCFS();
    RR();
    SJF();
    HRN();
    return 0;
}

void FCFS()
{
    init();
    sort(Sch.begin(), Sch.end(), cmp1);
    Sch[0].finish = Sch[0].arrival + Sch[0].ts;
    Sch[0].whole = Sch[0].ts;
    for (int i = 1; i < Sch.size(); i++)
    {
        Sch[i].finish = + Sch[i].ts + (Sch[i - 1].finish > Sch[i].arrival ? Sch[i - 1].finish : Sch[i].arrival );
        Sch[i].whole = Sch[i].finish - Sch[i].arrival;
    }
    cout << "FCFS:\n";
    show();
}
void RR()
{
    init();
    int t = Sch[0].arrival, siz = Sch.size(), T = 0;
    int ts_need[siz] = {0};
    queue<int> ready;

    for (int i = 0; i < siz; i++)
    {
        ts_need[i] = Sch[i].ts;
        T += Sch[i].ts;
    }

    while (T)
    {
        if (ready.empty())
            for (int i = 0; i < siz; i++)
                if (ts_need[i] > 0 && !Sch[i].in)
                {
                    ready.push(i);
                    t = Sch[i].arrival;
                    Sch[i].in = 1;
                    break;
                }
        int cur = ready.front();
        ready.pop();
        if (t < Sch[cur].arrival)
            t = Sch[cur].arrival;
        ts_need[cur]--;
        T--;
        t++;
        for (int i = 0; i < siz; i++)
            if (t >= Sch[i].arrival && ts_need[i] > 0 && !Sch[i].in)
            {
                Sch[i].in = 1;
                ready.push(i);
            }
        if (ts_need[cur] == 0)
        {
            Sch[cur].finish = t;
            Sch[cur].whole = t - Sch[cur].arrival;
            ts_need[cur]--;
        }
        else if (ts_need[cur] > 0)
            ready.push(cur);
    }
    cout << "RR:\n";
    show();
}
void SJF()
{
    init();
    int siz = Sch.size(), done = 0, mint = MAX, t = 0;
    sort(Sch.begin(), Sch.end(), cmp2);
    while (done < siz)
    {
        if (mint != MAX && t < mint)
            t = mint;
        mint = MAX;
        bool flag = 0;
        for (int i = 0; i < siz; i++)
        {
            if (Sch[i].in)
                continue;
            else if (t >= Sch[i].arrival && !flag )
            {
                Sch[i].in = 1;
                Sch[i].finish = t + Sch[i].ts;
                Sch[i].whole = Sch[i].finish - Sch[i].arrival;
                t = Sch[i].finish;
                done++;
                flag = 1;
            }
            else
            {
                mint = min(mint, Sch[i].arrival);
            }
        }
    }
    cout << "SJF:\n";
    show();
}
void HRN()
{
    init();
    int siz = Sch.size(), done = 0, t = 0;
    double maxrn=-1;
    int todo, mint=MAX;

    while (done < siz)
    {
        if (mint != MAX && t < mint)
        {
            t = mint;
        }
        maxrn = -1;
        mint = MAX;
        for (int i = 0; i < siz; i++)
        {
            if (Sch[i].in)
                continue;
            else if (t >= Sch[i].arrival)
            {
                if (maxrn < 1 + (t - Sch[i].arrival) / Sch[i].ts)
                {
                    maxrn = 1 + (t - Sch[i].arrival) / Sch[i].ts;
                    todo = i;
                }
            }
            else
            {
                mint = min(mint, Sch[i].arrival);
            }
        }
        Sch[todo].in = 1;
        Sch[todo].finish = t + Sch[todo].ts;
        Sch[todo].whole = Sch[todo].finish - Sch[todo].arrival;
        t = Sch[todo].finish;
        done++;
    }
    sort(Sch.begin(), Sch.end());
    cout << "HRN:\n";
    show();
}
