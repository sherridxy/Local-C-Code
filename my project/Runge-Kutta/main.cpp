#include <iostream>

using namespace std;
double f(double x,double y)
{
    return (y-2*x/y);
}

int main()
{
    double x,y;
    cout<<"输入数据"<<endl;
    cin>>x>>y;
    int n;
    cout<<"输入n"<<endl;
    cin>>n;
    double num;
    cout<<"输入横坐标"<<endl;
    cin>>num;
    double h=(num-x)/n;
    double k1,k2,k3,k4;
    for (int i=0;i<n;i++)
    {
        k1=f(x,y);
        k2=f(x+h/2,y+h/2*k1);
        k3=f(x+h/2,y+h/2*k2);
        k4=f(x+h,y+h*k3);
        y=y+h/6*(k1+2*k2+2*k3+k4);
        x=x+h;
    }
    cout<<y<<endl;
    return 0;
}
