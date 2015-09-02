#include <iostream>
#include <stdio.h>
#include <cmath>
using namespace std;
int main()
{
    int n,k,N;
    cout<<"输入未知元个数\n";
    cin>>n;
    double a[n][n];
    double b[n],x[n],y[n];
    double mmax,e;
    cout<<"输入最大迭代次数\n";
    cin>>N;
    cout<<"输入精度\n";
    cin>>e;
    cout<<"输入对应矩阵\n";
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++) cin>>a[i][j];
        cin>>b[i];
    }
    cout<<"输入迭代初值\n";
    for (int i=0;i<n;i++)
    {
        cin>>x[i];
        y[i]=x[i];
    }
    for (k=0;k<N;k++)
    {
        double temp;
        for (int i=0;i<n;i++)
        {
            temp=0;
            for (int j=0;j<n;j++)
            {
                if (i==j) continue;
                temp+=a[i][j]*y[j];
            }
            y[i]=(b[i]-temp)/a[i][i];
        }
        mmax=fabs(y[0]-x[0]);
        for (int i=0;i<n;i++)
        {
            if (fabs(y[i]-x[i])>mmax) mmax= fabs(y[i]-x[i]);
        }
        if  (mmax<e) break;
        for (int i=0;i<n;i++) x[i]=y[i];
    }
    if (k==N) cout<<"迭代失败\n";
    else
    {
        printf("经过%d次迭代，解为：\n",k);
        for (int i=0;i<n;i++) printf("%.8lf\n",y[i]);
    }
    return 0;
}
