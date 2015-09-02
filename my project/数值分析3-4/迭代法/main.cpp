#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;
double f(double x)
{
    return exp(-x);
}
int main()
{
    int N,i;
    cout<<"请输入最大迭代次数\n";
    cin>>N;
    double x,y,e;
    cout<<"输入迭代初值"<<endl;
    cin>>x;
    cout<<"请输入精度"<<endl;
    cin>>e;
    for (i=0;i<N;i++)
    {
        y=f(x);
        if (fabs(y-x)<e) break;
        x=y;
    }
    if (i==N) printf("迭代失败\n");
    else printf("方程的解为:%.9lf,经过%d次迭代\n",y,i);
    return 0;
}
