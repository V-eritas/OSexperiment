#include <iostream>
#include <algorithm>
#include <map>
#include <fstream>
#include <deque>
#include <iomanip>
#include <vector>

using namespace std;

int PageNum;
deque<int> PP;
map<int, int> PPin, PPout;


void show_title(fstream &os)
{
    os << left << setw(7) << "Out" ;
    for (int i = 0; i < PageNum; i++)
    {
        os << "Frame" << setw(2) << i << " ";
    }
    os << endl;
}
void init()
{
    PP.clear();
    PPin.clear();
    PPout.clear();
}
void FIFO(fstream &out, const vector<int> &input);
void LRU(fstream &out, const vector<int> &input);

int main()
{
    vector<int> input;
    ifstream in("in.txt");
    if (!in)
    {
        cout << "File open failre!\n";
        exit(1);
    }
    in >> PageNum;
    while (!in.eof())
    {
        int tmp;
        in >> tmp;
        input.push_back(tmp);
    }
    in.close();
    fstream out("out.txt", ios::out);
    FIFO(out, input);
    LRU(out, input);
    out.close();
    return 0;
}

void FIFO(fstream &out, const vector<int> &input)
{
    init();

    out << "FIFO\n";
    show_title(out);
    int misscnt = 0;
    int siz = input.size();
    for (int i = 0; i < siz ; i++)
    {
        int newpage = input[i];
        if (PPin.count(newpage))
        {
            ;
        }
        else
        {
            misscnt++;
            if (PP.size() >= PageNum)
            {
                int outout = PP.back();
                PPin.erase(outout);
                PP.pop_back();
                PPout.insert(pair<int, int>(i, outout));
            }
            PP.push_front(newpage);
            PPin.insert(pair<int, int>(newpage, 1));
        }

        if (PPout.count(i) == 1)
            out << left << setw(7) << PPout[i];
        else
            out << left << setw(7) << " ";
        for (int j = 0; j < PP.size(); j++ )
            out << left << setw(7) << PP[j] << " ";
        out << endl;
    }
    out << "缺页次数:" << setprecision(4) << misscnt << endl;
    out << "缺页率:" << setprecision(4) << double(misscnt) / siz << endl;
}
void LRU(fstream &out, const vector<int> &input)
{
    init();
    out << "LRU:\n";
    show_title(out);
    int misscnt = 0;
    int siz = input.size();
    for (int i = 0; i < siz ; i++)
    {
        int newpage = input[i];
        if (PPin.count(newpage))
        {
            PP.erase(find(PP.begin(), PP.end(), newpage));
            PP.push_front(newpage);
        }
        else
        {
            misscnt++;
            if (PP.size() >= PageNum)
            {
                int outout = PP.back();
                PPin.erase(outout);
                PP.pop_back();
                PPout.insert(pair<int, int>(i, outout));
            }
            PP.push_front(newpage);
            PPin.insert(pair<int, int>(newpage, 1));
        }

        if (PPout.count(i) == 1)
            out << left << setw(7) << PPout[i];
        else
            out << left << setw(7) << " ";
        for (int j = 0; j < PP.size(); j++ )
            out << left << setw(7) << PP[j] << " ";
        out << endl;
    }
    out << "缺页次数:" << setprecision(4) << misscnt << endl;
    out << "缺页率:" << setprecision(4) << double(misscnt) / siz << endl;
}
