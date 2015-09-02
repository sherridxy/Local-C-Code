#include <iostream>

using namespace std;

int main()
{
    int n;
    cout<<"输入个数"<<endl;
    cin>>n;
    double *x=new double [n];
    double *y=new double [n];
    cout<<"输入数据"<<endl;
    for (int i=0;i<n;i++) cin>>x[i]>>y[i];
    for (int i=0;i<n-1;i++)
    {
        for (int j=n-1;j>=i+1;j--)
        {
            y[j]=(y[j]-y[j-1])/(x[j]-x[j-1-i]);
        }
    }
    double sum=0;
    double temp;
    double num;
    cout<<"输入x"<<endl;
    cin>>num;
    for (int i=0;i<n;i++)
    {
        temp=1;
        for (int j=0;j<i;j++)
        {
           temp=temp*(num-x[j]);
        }
        sum+=temp*y[i];
    }
    cout<<sum<<endl;
    delete []x;
    delete []y;
    return 0;
}
