#include "dFunction.h" //相当于加入包
class dMain  //相当于定义一个公共类来给Main调用
{
public:
    static void myMain()//相当于main方法
    {
        int a;
        a=dFunction::putInt();
        a=StepCross(a);
        dFunction::showInt(a);
    }
    static int StepCross(int n)
    {
        if (n==0||n==1) return 1;
        else return n*StepCross(n-1);
    }


};


int main()
{
    dMain::myMain();
    return 0;
}
