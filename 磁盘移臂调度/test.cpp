#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

vector<int> input;

void SSTF(fstream &os, const vector<int> &input, const int sta);
void SCAN(fstream &os, const vector<int> &input, const int sta);    // 默认初始时磁头移动方向向外

int main()
{
    ifstream in("in.txt");
    if (!in)
    {
        cout << "File open failure!\n";
        exit(0);
    }
    int sta;
    in >> sta;
    while (!in.eof())
    {
        int tmp;
        in >> tmp;
        input.push_back(tmp);
    }
    in.close();
    if (input.empty())
    {
        cout << "Input queue empty!\n";
        exit(0);
    }
    fstream out("out.txt", ios::out);
    sort(input.begin(), input.end());
    SSTF(out, input, sta);
    SCAN(out, input, sta);
    out.close();
    return 0;
}
void SSTF(fstream &os, const vector<int> &input, const int sta)
{
    vector<int> q(input);
    int cur = sta, sum = 0;
    os << "SSTF:\n";
    os << left << setw(10) << "Next" << setw(10) << "Dist" << endl;
    vector<int>::iterator i = lower_bound(q.begin(), q.end(), cur);
    while (!q.empty())
    {
        if ( i == q.begin())
        {
            os << setw(10) << *i << setw(10) << abs(cur - *i) << endl;
            sum += abs(cur - *i);
            cur = *i;
            i = q.erase(i);
        }
        else if (i == q.end())
        {
            i--;
            os << setw(10) << *i << setw(10) << abs(cur - *i) << endl;
            sum += abs(cur - *i);
            cur = *i;
            i = q.erase(i - 1);
        }
        else
        {
            if (abs(*i - cur) < abs(*(i - 1)) - cur)
            {
                os << setw(10) << *i << setw(10) << abs(cur - *i) << endl;
                sum += abs(cur - *i);
                cur = *i;
                i = q.erase(i);
            }
            else
            {
                os << setw(10) << *(i - 1) << setw(10) << abs(cur - * (i - 1)) << endl;
                sum += abs(cur - * (i - 1));
                cur = *(i - 1);
                i = q.erase(i - 1);
            }
        }
    }
    os << "移臂总量:" << sum << endl << "平均寻道长度:" << setprecision(4) << double(sum) / input.size() << endl;
}
void SCAN(fstream &os, const vector<int> &input, const int sta)
{
    vector<int> q(input);
    int cur = sta, sum = 0;
    os << "SCAN:\n";
    os << left << setw(10) << "Next" << setw(10) << "Dist" << endl;
    vector<int>::iterator i = lower_bound(q.begin(), q.end(), cur);
    while (!q.empty())
    {
        if ( i != q.end())
        {
            os << setw(10) << *i << setw(10) << abs(cur - *i) << endl;
            sum += abs(cur - *i);
            cur = *i;
            i = q.erase(i);
        }
        else
        {
            i--;
            os << setw(10) << *i << setw(10) << abs(cur - *i) << endl;
            sum += abs(cur - *i);
            cur = *i;
            i = q.erase(i);
        }
    }
    os << "移臂总量:" << sum << endl << "平均寻道长度:" << setprecision(4) << double(sum) / input.size() << endl;
}
