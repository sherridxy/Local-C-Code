#include <iostream>
using namespace std;
int main()
{
	int f[3];
	double a[3][4];
	double b1[3][3];
	double b2[3][3];
	double b3[3][3];
	double c[3][3];
	int i,j,k,t,m,n,p,q,u;
	double x1,x2,x3,h1,h2,h3,h0;
    aga:h1=h2=h3=h0=0;
    cout<<"请输入所要计算三元一次方程组的对应矩阵"<<endl;
	for (i=0;i<3;i++)
	{
		for (j=0;j<4;j++) cin>>a[i][j];
	}
	cout<<"您输入的矩阵为:"<<endl;
	for (i=0;i<3;i++)
	{
		for (j=0;j<4;j++) cout<<a[i][j]<<"  ";
		cout<<endl;
	}
    cout<<"如果输入有误，请回复0重新输入，如果无误请输入1确认"<<endl;
	cin>>q;
	if (q==0) goto aga;
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++) c[i][j]=a[i][j];
	}
	for (i=0;i<3;i++) b1[i][0]=a[i][3];
	for (i=0;i<3;i++)
	{
		for (j=1;j<3;j++) b1[i][j]=c[i][j];
	}
	for (i=0;i<3;i++)
	{
		b2[i][1]=a[i][3];
		b2[i][0]=c[i][0];
		b2[i][2]=c[i][2];
	}
	for (i=0;i<3;i++) b3[i][2]=a[i][3];
	for (i=0;i<3;i++)
	{
		for (j=0;j<2;j++) b3[i][j]=c[i][j];
	}
	for (i=0;i<3;i++)
	{
		for (j=0;j<3;j++)
		{
			if (i==j) continue;
			for (k=0;k<3;k++)
			{
				if ((i==k)||(j==k)) continue;
				f[0]=i,f[1]=j,f[2]=k,t=0;
				for (m=0;m<2;m++)
				{
					for (n=m+1;n<3;n++)
					{
						if (f[m]>f[n]) t++;
					}
				}
				if ((t+2)%2==0) p=1;
				else p=-1;
				h1=h1+p*b1[0][i]*b1[1][j]*b1[2][k];
				h2=h2+p*b2[0][i]*b2[1][j]*b2[2][k];
				h3=h3+p*b3[0][i]*b3[1][j]*b3[2][k];
				h0=h0+p*c[0][i]*c[1][j]*c[2][k];
			}
		}
	}
	if (h0==0) cout<<"该方程组无解";
	else
	{
		x1=h1/h0,x2=h2/h0,x3=h3/h0;
		cout<<"该方程组的解为"<<"x="<<x1<<"  "<<"y="<<x2<<"  "<<"z="<<x3<<endl;
	}
	cout<<"如需退出请输入0，再次计算请输入1"<<endl;
	cin>>u;
	if (u==1) goto aga;
	return 0;
}
