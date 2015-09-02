#include <iostream>
using namespace std;
class dFunction //相当于一个函数的包
{
public:
    static void showInt(int a) //输出整型数字
    {
        cout<<a<<endl;
    }
    static int putInt()//输入整型数字
    {
        int a;
        cin>>a;
        return a;
    }

};
