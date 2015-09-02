#include <iostream>

using namespace std;
struct Point
{
    double x;
    double y;
    Point (int mx=0,int my=0)
    {
        x=mx;
        y=my;
    }
};

int main()
{
    int n;
    cout<<"请输入数据个数"<<endl;
    cin>>n;
    cout<<"请输入数据"<<endl;
    Point *p=new Point[n];
    for (int i=0;i<n;i++) cin>>p[i].x>>p[i].y;
    double sum=0;
    double l=1;
    double x;
    cout<<"输入x";
    cin>>x;
    for (int i=0;i<n;i++)
    {
        l=1;
        for (int j=0;j<n;j++)
        {
            if (i==j) continue;
            l=l*(x-p[j].x)/(p[i].x-p[j].x);
        }
        sum+=l*p[i].y;
    }
    cout<<sum;
    delete []p;
    return 0;
}
