#include <iostream>
#include <time.h>
#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;
int main()
{
	vector<double> a;
	int m=10000;
	srand(time(0));
	while (m--)
	{
		double u1=rand()/(1.0+RAND_MAX);
	    double u2=rand()/(1.0+RAND_MAX);
	    double r=0.8+0.05*sqrt(-2.0*log(u1))*cos(2*3.1415926536*u2);
	    a.push_back(r);
	}
	/*double sum=0;
	for (int i=0;i<a.size();i++)
	{
		sum+=a[i];
	}
	double miu=sum/100;
	sum=0;
	for (int i=0;i<a.size();i++)
	{
		sum+=(a[i]-miu)*(a[i]-miu);
	}*/
	for (int i=0;i<a.size();i++) cout<<a[i]<<endl;
	//printf("%.9lf %.9lf",miu,sum/100);
	return 0;
}
