#include <iostream>
#include <ctime>
using namespace std;
void washcard(int a[]);
int onemorecard(int a[]);
void showcard(int);
int main()
{
	int i,k,x=0,y=0,score_computer=0,score_player=0,c[10],p[10];
	int a[52];
	cout<<"这是一个简单的21点小游戏，输入任意数字开始"<<endl;
	cin>>i;
	washcard (a);
	for (i=0; ;i++)
	{
		if (i==0)
		{
			c[i]=onemorecard(a);
			p[i]=onemorecard(a);
			cout<<"您的底牌为：";
			showcard (p[0]);
			cout<<endl;
			cout<<"对方底牌未知"<<endl;
			score_computer=c[0]%13+1;
			score_player=p[0]%13+1;
			continue;
		}
		if (i==1)
		{
			c[i]=onemorecard(a);
			p[i]=onemorecard(a);
			cout<<"您的第2张牌为：";
			showcard (p[i]);
			cout<<endl;
			cout<<"对方的第2张牌为：";
			showcard (c[i]);
			cout<<endl;
			score_computer+=c[i]%13+1;
			score_player+=p[i]%13+1;
			continue;
		}
		if (score_computer<18)
		{
			c[i]=onemorecard(a);
			cout<<"对方选择取走一张牌，该牌为：";
			showcard (c[i]);
			cout<<endl;
			score_computer+=c[i]%13+1;
		}
		else y=1;
		if (x==0)
		{
			cout<<"您当前分数为："<<score_player<<endl;
		    cout<<"对方牌面分数为："<<score_computer-c[0]%13-1<<endl;
		    cout<<"您是否选择抽牌（1代表抽；0代表不抽）"<<endl;
		    cin>>k;
		    if (k==1)
			{
				p[i]=onemorecard(a);
			    cout<<"您抽到的牌为：";
			    showcard (p[i]);
			    cout<<endl;
			    score_player+=p[i]%13+1;
			}
		    else x=1;
		}
		if ((x+y)==2) break;
	}
	cout<<"对方的底牌为：";
	showcard(c[0]);
	cout<<endl;
	cout<<"您的分数为:"<<score_player<<endl;
	cout<<"对方的分数为:"<<score_computer<<endl;
	if ((score_computer>21)&&(score_player>21))
	{
		cout<<"双方都超过二十一点，平局"<<endl;
		cin>>i;
		return 0;
	}
	if (score_computer>21)
	{
		cout<<"你赢了"<<endl;
		cin>>i;
		return 0;
	}
	if (score_player>21)
	{
		cout<<"你输了"<<endl;
		cin>>i;
		return 0;
	}
	if (score_computer==score_player)
	{
		cout<<"平局"<<endl;
		cin>>i;
		return 0;
	}
	score_computer>score_player?(cout<<"你输了"<<endl):(cout<<"你赢了"<<endl);
	cin>>i;
    return 0;
}

void washcard (int a[])
{
	int i,temp;
	int b[52]={0};
	srand (time (0));
	for (i=0;i<52;i++)
	{
		temp=rand()%52;
		if (b[temp]==0)
		{
			b[temp]=1;
			a[i]=temp;
		}
		else i--;
	}
}

int onemorecard(int a[])
{
	static int i=0;
	return (a[i++]);
}

void showcard (int num)
{
	int t=num%13+1;
	char i;
	cout<<(char)(num/13+3);
	if (t==1)
	{
		cout<<'A';
		return;
	}
	if (t>10)
	{
		switch (t)
		{
		case 11: i='J';break;
		case 12: i='Q';break;
		case 13: i='K';break;
		}
		cout<<i;
		return;
	}
	cout<<t;
	return;
}
