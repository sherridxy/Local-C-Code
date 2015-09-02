#include <iostream>
using namespace std;
int c[9]={0},l[15]={0},r[15]={0},mycount=0;
int fill_in_the_next (int floor);
int main()
{
	fill_in_the_next (1);
	cout<<mycount<<endl;
	cin>>mycount;
	return 0;
}

int fill_in_the_next (int floor)
{
	int k,condition;
	for (k=1;k<=8;k++)
	{
		if (c[k]==1||l[floor-k+7]==1||r[floor+k-2]==1) continue;
		c[k]=1;
		l[floor-k+7]=1;
		r[floor+k-2]=1;
		if (floor==8)
		{
			mycount++;
			c[k]=0;
		    l[floor-k+7]=0;
		    r[floor+k-2]=0;
			return 0;
		}
		condition=fill_in_the_next (floor+1);
		if (condition==1) return 1;
		c[k]=0;
		l[floor-k+7]=0;
		r[floor+k-2]=0;
	}
	return 0;
}


