#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

extern const int MEM;
extern const int BLOCKSIZE;
extern int BM[];

extern int Random(int , int );
extern int getRSize(int , int);


struct File
{
    int indexLoca;              // 索引表位置
    int siz;                    // 文件大小
    string name;
    string ext;                 // 扩展名
    vector<int> index;
    int getRLocation();
    void setBlock();
    File(int _siz = 0, string _name = "")
    {
        siz = _siz;
        name = _name;
        indexLoca = getRLocation();
        setBlock();
    }
    void show_Loca()const;
    bool operator==(const File &f)
    {
        return name == f.name;
    }
};

class Manager
{
private:
    int num;
    vector<File> Flist;
public:
    Manager()
    {
        for (int i = 0; i < MEM; i++)
            BM[i] = 0;
        Flist.clear();
    }
    vector<File>& getFlist()
    {
        return Flist;
    }
    void showBM()const
    {
        cout << "bitMap as follow:\n" << setw(3) << "";
        for (int j = 0; j < 16; j++)
            cout << setw(3) << j;
        cout << endl;
        for (int i = 0; i < 32; i++)
        {
            cout << setw(3) << i;
            for (int j = 0; j < 16; j++)
            {
                if (i == 31 && j >= 4)
                    break;
                cout << setw(3) << BM[16 * i + j];
            }
            cout << endl;
        }
    }
    void Insert(File &f)
    {
        Flist.push_back(f);
        num++;
    }
    void Delete(const File &f)
    {
        vector<File>::iterator i = find(Flist.begin(), Flist.end(), f);
        for (vector<int>::iterator iter = (i->index).begin(); iter != (i->index).end(); ++iter)
        {
            BM[*iter] = 0;
        }
        Flist.erase(i);
        num--;
    }
};
