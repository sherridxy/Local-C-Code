#include <iostream>
#include <cstdio>
using namespace std;
int bre;
struct Marix
{
	int row;//ÐÐ
	int col;//ÁÐ
	double **p;
	Marix(int r,int c)
	{
		row=r;
		col=c;
		p=new double *[r];
		for (int i=0;i<r;i++) p[i]=new double[c];
		for (int i=0;i<row;i++)
			for (int j=0;j<col;j++)
				p[i][j]=0;
	}
	Marix(Marix &b)
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
	Marix operator *(Marix &b)
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
	void  operator =(Marix &b)
	{
		for (int i=0;i<row;i++)
			for (int j=0;j<col;j++)
				p[i][j]=b.p[i][j];
	}
	Marix operator +(Marix &b)
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
		Marix a(row,col);
		a=*this;
		a.Show();
		while (n!=0)
		{
			if (n&1==1)
				sum=sum+a;
			a=a*a;
			printf("then\n");
			n>>=1;
			printf("then2\n");
			printf("a.row=%d a.col=%d\n",a.row,a.col);
			a.Show();
			printf("then3\n");
			printf("n=%d\n",n);
			cin>>bre;
		}
		return sum;
	}
};
int main()
{
	Marix a(3,3);
	double xx[]={1,2,1,2,3,4,1,2,3};
	a.Create(xx);
	(a^5).Show();

	return 0;
}
