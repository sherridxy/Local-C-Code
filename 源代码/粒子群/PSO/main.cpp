#include <iostream>
#include <cstdio>
#include "PSO.h"
using namespace std;
class MyPSO :public PSO
{
public:
	MyPSO(int dim,int n): PSO(dim,n){;}
	float GetFit(PARTICLE&);
};

float MyPSO::GetFit(PARTICLE& p)
{
	float sum=0;
	for (int i=0;i<p.Dim;i++)
	{
		sum+=100*(p.X[i+1]*p.X[i+1]-p.X[i])*(p.X[i+1]*p.X[i+1]-p.X[i])+(1-p.X[i])*(1-p.X[i]);
	}
	return -sum;
}

int main()
{
	freopen("C:\\Users\\Administrator\\Desktop\\ans.txt","w",stdout);
	double temp1[]={30,30,30};
	double temp2[]={-30,-30,-30};
	double ans[3];
	MyPSO a(3,70);
	a.SetXup(temp1);
	a.SetXdown(temp2);
	a.SetVmax(0.03);
	a.Run(1000000);
	cout<<a.GetBest(ans)<<endl;
	for (int i=0;i<3;i++) cout<<ans[i]<<endl;
	freopen("C:\\Users\\Administrator\\Desktop\\ooo.txt","w",stdout);
	for (int i=0;i<70;i++) printf("[%d] %f %f\n",i+1,a.Particle[i].Fit,a.Particle[i].FitBest);
	return 0;
}
