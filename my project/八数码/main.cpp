#include <iostream>
#include <stdio.h>
#include <cmath>
#include <queue>
#include <stack>
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
using namespace std;
int table[9]= {1,2,6,24,120,720,5040,40320,362880};
bool visit[362880+5];
int parent[362880+5];
int MyToInt(char *ch,int length)
{
    int sum=0;
    for (int i=0; i<length-1; i++)
    {
        int ccount=0;
        for (int j=i+1; j<length; j++)
            if (ch[j]<ch[i]) ccount++;
        sum+=ccount*table[length-i-2];
    }
    return sum;
}
void MyToArry(char *ch,int length,int num)
{
    int a[length];
    a[0]=0;
    for (int i=2; i<=length; i++)
    {
        a[i-1]=num%i;
        num/=i;
    }
    bool visit[length];
    for (int i=0; i<length; i++) visit[i]=false;
    for (int i=length-1; i>=0; i--)
    {
        int temp=a[i];
        int ccount=0;
        for (int j=0; j<length; j++)
        {
            if (visit[j]==true) continue;
            if (ccount==temp)
            {
                ch[length-i-1]=j+'0';
                visit[j]=true;
                break;
            }
            ccount++;
        }
    }
}

int Move(int num,int length,int action)
{
    char a[length];
    MyToArry(a,length,num);
    int line=(int)sqrt(length);
    int space;
    for (int i=0; i<length; i++)
    {
        if (a[i]=='0')
        {
            space=i;
            break;
        }
    }
    switch (action)
    {
        case UP:
        {
            if (space-line>=0)
            {
                a[space]=a[space-line];
                a[space-line]=0;
            }
            else return -1;
            break;
        }
        case DOWN:
        {
            if (space+line<length)
            {
                a[space]=a[space+line];
                a[space+line]=0;
            }
            else return -1;
            break;
        }
        case LEFT:
            if ((space-1>=0)&&space%line!=0)
            {
                a[space]=a[space-1];
                a[space-1]=0;
            }
            else return -1;
            break;
        case RIGHT:
        {
            if ((space+1<length)&&(space+1)%line!=0)
            {
                a[space]=a[space+1];
                a[space+1]=0;
            }
            else return -1;
            break;
        }
    }
    return MyToInt(a,length);
}

void ShowArry(int num,int length)
{
    int line=(int) sqrt(length);
    char a[length];
    MyToArry(a,length,num);
    int mmcount=0;
    for (int i=0; i<line; i++)
    {
        for (int j=0; j<line; j++)
        {
            cout<<a[mmcount++]<<' ';
        }
        cout<<endl;
    }
}

int main()
{
    while (true)
    {
        queue<int> Q;
        stack<int> S;
        for (int i=0; i<362880+5; i++) visit[i]=false;
        char Begin[9],End[9];
        cout<<"ÇëÊäÈë³õÊ¼×´Ì¬£º"<<endl;
        for (int i=0; i<9; i++) cin>>Begin[i];
        cout<<"ÇëÊäÈëÖÕÖ¹×´Ì¬£º"<<endl;
        for (int i=0; i<9; i++) cin>>End[i];
        int from=MyToInt(Begin,9);
        int des=MyToInt(End,9);
        visit[from]=true;
        parent[from]=-1;
        Q.push(from);
        int head;
        while (!Q.empty())
        {
            head=Q.front();
            Q.pop();
            if (head==des) break;
            for (int i=0; i<4; i++)
            {
                int get=Move(head,9,i);
                if (get==-1) continue;
                if (visit[get]==true) continue;
                visit[get]=true;
                parent[get]=head;
                Q.push(get);
            }
        }
        if (head!=des)
        {
            cout<<"ÎÞ½â"<<endl;
            continue;
        }
        int step=des;
        while (step!=-1)
        {
            S.push(step);
            step=parent[step];
        }
        int MyCount=0;
        while (!S.empty())
        {
            cout<<"µÚ"<<MyCount+1<<"²½:"<<endl;
            ShowArry(S.top(),9);
            cout<<endl;
            S.pop();
            MyCount++;
        }
    }
    return 0;
}
