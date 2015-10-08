#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;
int bre;
int m,n;
vector<double> systemResource;
struct Process
{
	vector<double> need;
	vector<double>	possess;
};
vector<Process>  p;
bool IsValid (int num,double *request)
{
	bool ok=true;
	for (int i=0; i<m; i++)
	{
		if ((request[i]+p[num].possess[i]>p[num].need[i])||(request[i]>systemResource[i]))
		{
			ok=false;
			break;
		}
	}
	return ok;
}

bool SecondPro(bool *visit,double *sys,int kase)
{
	printf("kase is %d\n",kase);
	for (int i=0;i<n;i++) 
	{
		printf("[ %d ]  ",i);
		cout<<visit[i]<<endl;
	}
	for (int i=0;i<m;i++) 
	{
		printf("%lf ",sys[i]);
	}
	cout<<endl;
	if (kase==n) return true;
	for (int i=0; i<n; i++)
	{
		if (visit[i]==true) continue;
		bool ok=true;
		for (int k=0; k<m; k++)
		{
			if (sys[k]<p[i].need[k]-p[i].possess[k])
			{
				ok=false;
				break;
			}
		}
		if (!ok) continue;
		for (int k=0; k<m; k++) sys[k]+=p[i].possess[k];
		visit[i]=true;
		if (SecondPro(visit,sys,kase+1)) return true;
		for (int k=0; k<m; k++) sys[k]-=p[i].possess[k];
		visit[i]=false;
	}
	return false;
}

bool TryAlloc(int num,double *request)
{
	bool visit[n];
	double sys[m];
	for (int i=0; i<n; i++) visit[i]=false;
	for (int i=0; i<m; i++) 
	{
		sys[i]=systemResource[i]-request[i];
		p[num].possess[i]+=request[i];
	}
	if (SecondPro(visit,sys,0))
	{
		for (int i=0; i<m; i++)
		{
			systemResource[i]-=request[i];
		}
		return true;
	}
	for (int i=0;i<m;i++) p[num].possess[i]-=request[i];
	return false;

}

void Alloc (int num,double *request)
{
	while (IsValid(num,request))
	{
		printf("the requst is valid  ");
		if (!TryAlloc(num,request)) break;
		printf("allocation succeed\n");
		return;
	}
	printf("allocation failed\n");
}


int main()
{
	cin>>m>>n;
	for (int i=0; i<m; i++)
	{
		double temp;
		cin>>temp;
		systemResource.push_back(temp);
	}
	for (int i=0; i<n; i++)
	{
		Process temp;
		double t;
		for (int j=0; j<m; j++)
		{
			cin>>t;
			temp.need.push_back(t);
		}
		for (int j=0; j<m; j++)
		{
			cin>>t;
			temp.possess.push_back(t);
		}
		p.push_back(temp);
	}
	int ccount=1;
	while (true)
	{
		int num;
		double request[m];
		cin>>num;
		if (num==-1) break;
		printf("\nRound %d:\n",ccount++);
		for (int i=0; i<m; i++) cin>>request[i];
		Alloc(num-1,request);
	}
	return 0;
}