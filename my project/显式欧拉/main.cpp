#include <iostream>

using namespace std;
double f(double x,double y)
{
    return (y-2*x/y);
}

int main()
{
    double x,y;
    cout<<"输入x,y"<<endl;
    cin>>x>>y;
    cout<<"输入n"<<endl;
    int n;
    cin>>n;
    double num;
    cout<<"输入横坐标"<<endl;
    cin>>num;
    double h=(num-x)/n;
    for (int i=0;i<n;i++)
    {
        cout<<y<<endl;
        y=y+h*f(x,y);
        x=x+h;
    }
    cout<<y+h*f(x,y)<<endl;
    return 0;
}
