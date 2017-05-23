#include "manager.h"

using namespace std;

const int MEM = 500;
const int BLOCKSIZE=2;
int BM[MEM];

int Random(int h, int l = 0)
{
    random_device rd;
    default_random_engine re(rd());
    uniform_int_distribution<int> dist(l, h);
    return dist(re);
}
int getRSize(int h, int l = 0)
{
    return Random(h, l);
}



int File::getRLocation()
{
    int tmpLoca;
    do
    {
        tmpLoca = Random(MEM);
    } while (BM[tmpLoca] == 1);
    BM[tmpLoca] = 1;
    return tmpLoca;
}
void File::setBlock()
{
    for (int i = 0; i < siz + BLOCKSIZE; i += BLOCKSIZE)
    {
        index.push_back(getRLocation());
    }
}
void File::show_Loca()const
{
    cout << "File name " << name << endl;
    cout << "File's IndexBlock in Block " << indexLoca << endl;
    cout << "Files in Blocks ";
    for (vector<int>::const_iterator ii = index.begin(); ii != index.end(); ii++)
    {
        cout << setw(4) << *ii;
    }
    cout << endl;
}
