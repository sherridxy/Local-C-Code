#include <iostream>
#include <ctime>
using namespace std;
int main()
{
	double time1,time2;
	time1=clock();
	int a[14][14];

   		for (int i=1;i<=13;i++)
			for (int j=0;j<=13;j++)
				a[i][j]=0;
		for (int j=0;j<=4;j++) a[1][j]=1;
		for (int i=2;i<=13;i++)
		{
			for (int j=0;j<=13;j++)
			{
				for (int k=0;k<=4;k++)
				{
					if (j-k>=0) a[i][j]+=a[i-1][j-k];
				}
			}
		}

	time2=clock();
	cout<<"run time is"<<1000*(time2-time1)/CLOCKS_PER_SEC<<"ms.\n";
	cout<<a[13][13]<<endl;
	return 0;
}
