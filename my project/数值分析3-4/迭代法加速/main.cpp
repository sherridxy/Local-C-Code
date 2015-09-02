#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;
double f(double x)
{
    return pow(x+1,1.0/3);
}
int main()
{
    double x0,x1,x2;
    double e;
    int N,i;
    cout<<"请输入初值：\n";
    cin>>x0;
    cout<<"请输入最大迭代次数：\n";
    cin>>N;
    cout<<"请输入精度：\n";
    cin>>e;
    for (i=0;i<N;i++)
    {
        x1=f(x0);
        x2=f(x1);
        x2-=pow(x2-x1,2)/(x2-2*x1+x0);
        if (fabs(x2-x0)<e) break;
        x0=x2;
    }
    if (i==N) cout<<"迭代失败\n";
    else printf("结果为%.9lf,经过%d次迭代\n",x2,i);
    return 0;
}
