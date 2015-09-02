#include <iostream>
#include <fstream>
#include <Algorithm>

using namespace std;

int main()
{
    double a[4][4]={0.012,0.116,0.105,0.008,0.004,0.012,0.054,0.011,0.043,0.148,0.268,0.024,0,0.044,0.133,0.018};//Êµ¼Ê
    double b[4][4]={0.032,0.168,0.065,0,0.002,0.032,0.052,0.004,0.087,0.224,0.271,0.002,0.001,0.102,0.142,0.005};
    fstream out("C:\\Users\\Administrator\\Desktop\\lingo.txt");
    for(int i=0;i<4;i++)
    {

        for (int j=0;j<4;j++)
        {
           out<<'x'<<i+1<<j+1<<'+';
        }
    }
    out.close();
    return 0;
}
