#include <iostream>
#include <cstdio>
using namespace std;
int bre;
struct Marix
{
	int row;//行
	int col;//列
	double **p;
	Marix(int r,int c,int n=0)
	{
		row=r;
		col=c;
		p=new double *[r];
		for (int i=0;i<r;i++) p[i]=new double[c];
		for (int i=0;i<row;i++)
			for (int j=0;j<col;j++)
				p[i][j]=n;
	}
	Marix(const Marix &b)
	{
		row=b.row;
		col=b.col;
		p=new double *[row];
		for (int i=0;i<row;i++) p[i]=new double[col];
		for (int i=0;i<row;i++)
			for (int j=0;j<col;j++)
				p[i][j]=b.p[i][j];
	}
	~Marix()
	{
		for (int i=0;i<row;i++) delete [](p[i]);
		delete []p;
	}
	Marix operator *(const Marix &b)
	{
		Marix ans(this->row,b.col);
		if (this->col!=b.row) 
		{
			cout<<"not fit\n";
		}
		else 
		{
			ans.row=this->row;
			ans.col=b.col;
			for (int i=0;i<this->row;i++)
				for (int j=0;j<b.col;j++)
					for (int k=0;k<this->col;k++)
						ans.p[i][j]+=this->p[i][k]*b.p[k][j];
		}
		return ans;
	}
	void Show()
	{
		for (int i=0;i<row;i++)
		{
			for (int j=0;j<col;j++) cout<<p[i][j]<<' ';
			cout<<endl;
		}
	}
	void Create(double *a)
	{
		int ccount=0;
		for (int i=0;i<row;i++)
			for (int j=0;j<col;j++)
				p[i][j]=a[ccount++];
	}
	Marix  operator = (const Marix &b)
	{
		for (int i=0;i<row;i++)
			for (int j=0;j<col;j++)
				p[i][j]=b.p[i][j];
		return *this;
	}
	Marix operator +(const Marix &b)
	{
		Marix ans(row,col);
		for (int i=0;i<row;i++)
			for (int j=0;j<col;j++)
				ans.p[i][j]=p[i][j]+b.p[i][j];
		return ans;
	}
	Marix operator ^ (int n)
	{
		Marix sum(row,col);
		for (int i=0;i<row;i++) sum.p[i][i]=1;
		Marix a(row,col);
		a=*this;
		while (n!=0)
		{
			if (n&1==1)
				sum= sum*a;
			a= a*a;
			n>>=1;
		}
		return sum;
	}
};
int main()
{
	Marix a(2,2);
	double aa[]={1,1,1,0};
	Marix b(2,1);
	double bb[]={1,1};
	a.Create(aa);
	b.Create(bb);
	int i;
	while (scanf("%d",&i)&&i!=-1)
	{
		cout<<endl;
		((a^i)*b).Show();
	}
	return 0;
}