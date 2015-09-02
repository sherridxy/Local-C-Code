#include <iostream>
#include <cmath>
using namespace std;
double f(double x,double y)
{
    return (y-2*x/y);
}

int main()
{
    double x0,y0,x1,y1;
    cout<<"输入两组数据"<<endl;
    cin>>x0>>y0;
    cin>>x1>>y1;
    double h=x1-x0;
    double num;
    cout<<"输入横坐标"<<endl;
    cin>>num;
    double xt;
    double yt;
    while (true)
    {
        if (abs(xt-num)<1e-6) break;
        yt=y0+2*h*f(x1,y1);
        xt=x1+h;
        y0=y1;
        x0=x1;
        y1=yt;
        x1=xt;
    }
    cout<<yt<<endl;
    return 0;
}
