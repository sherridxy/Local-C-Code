#include <iostream>

using namespace std;
int bre;
struct Point
{
    double x;
    double y;
    Point(double X=0,double Y=0)
    {
        x=X;
        y=Y;
    }
};

int main()
{
    double a,b,c,d;
    int n;
    cout<<"请输入n"<<endl;
    cin>>n;
    Point *p=new Point[n];
    cout<<"请输入n个点"<<endl;
    double k;
    double S=-1;
    double temp;
    int m;
    for (int i=0;i<n;i++)
    {
        cin>>p[i].x>>p[i].y;
    }
    for (int i=0;i<n-1;i++)
    {

        for (int j=i+1;j<=n-1;j++)
            if ((p[i].x-p[j].x!=0)&&(p[i].y!=p[j].y))
            {
                k=(p[i].y-p[j].y)/(p[i].x-p[j].x);
                for ( m=0;m<n;m++)
                {
                    if (m==i||m==j) continue;
                    if (p[m].y<k*(p[m].x-p[i].x)+p[i].y) break;
                }
                if (m<n) continue;
                temp=0.5*(2*p[i].x*p[i].y-p[i].y*p[i].y/k-k*p[i].x*p[i].x);
                if (S<0||temp>S)
                {
                    S=temp;
                    a=p[i].x;
                    b=p[i].y;
                    c=p[j].x;
                    d=p[j].y;
                }
            }
    }
    cout<<"最大面积为 "<<S<<endl;
    cout<<"对应直线过点（"<<a<<","<<b<<")    ("<<c<<","<<d<<")  "<<endl;
    cin>>bre;
    delete []p;
    return 0;
}
