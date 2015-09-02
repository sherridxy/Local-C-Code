#include <iostream>
using namespace std;


struct Point
{
    int x;
    int y;
    int key;
    Point (int m=0) {key=m;}
};

struct Edge
{
    int x;
    int y1;
    int y2;
    Edge(int a=0,int b=0,int c=0)
    {
        x=a;
        y1=b;
        y2=c;
    }
};


void SortByX(Point *p,int n)
{
    Point temp;
    for (int i=0;i<n-1;i++)
    {
        for (int j=0;j<n-i-1;j++)
            {
                if (p[j].x>p[j+1].x||(p[j].x==p[j+1].x&&p[j].y>p[j+1].y))
                {
                    temp=p[j];
                    p[j]=p[j+1];
                    p[j+1]=temp;
                }
            }
    }
}

void SortByY(Point *p,int n)
{
    Point temp;
    for (int i=0;i<n-1;i++)
    {
        for (int j=0;j<n-i-1;j++)
            {
                if (p[j].y>p[j+1].y||(p[j].y==p[j+1].y&&p[j].x>p[j+1].x))
                {
                    temp=p[j];
                    p[j]=p[j+1];
                    p[j+1]=temp;
                }
            }
    }
}

void SetsInput(int x,int y,int *a)
{
    int i=x;
    int j=y;
    while (a[i]>=0) i=a[i];
    while (a[j]>=0) j=a[j];
    if (i!=j)
    {
        a[i]+=a[j];
        a[j]=i;
    }
}

int Run()
{
    int length=0;
    int n;
    cin>>n;
    Edge *E=new Edge[n/2];
    int edgeCount=0;
    int temp_x,temp_y;
    int *Sets=new int[n];
    for (int i=0;i<n;i++) Sets[i]=-1;
    Point *p=new Point[n];
    for (int i=0;i<n;i++)
    {
        cin>>temp_x>>temp_y;
        p[i].x=temp_x;
        p[i].y=temp_y;
        p[i].key=i;
    }
    SortByX (p,n);
    if (n%2==1) {delete []p;delete []E;delete []Sets;return -1;}
    for (int i=0;i<n;i+=2)
    {
        if (p[i].x!=p[i+1].x) {delete []p;delete []E;delete []Sets;return -1;}
        length+=p[i+1].y-p[i].y;
        SetsInput(p[i].key,p[i+1].key,Sets);
        E[edgeCount++]=Edge(p[i].x,p[i].y,p[i+1].y);
    }
    SortByY(p,n);
    for (int i=0;i<n;i+=2)
    {
        if (p[i].y!=p[i+1].y) {delete []p;delete []E;delete []Sets;return -1;}
        for (int j=0;j<edgeCount;j++)
        {
            if ((p[i].y>E[j].y1&&p[i].y<E[j].y2)&&(E[j].x<p[i+1].x&&E[j].x>p[i].x)) {delete []p;delete []E;delete []Sets;return -1;}
        }
        length+=p[i+1].x-p[i].x;
        SetsInput(p[i].key,p[i+1].key,Sets);
    }
    bool flag=false;
    for (int i=0;i<n;i++)
    for (int i=0;i<n;i++)
    {
        if (Sets[i]==-n) {flag=true;break;}
    }
    if (flag==false) {delete []p;delete []E;delete []Sets;return -1;}
    return length;
}


int main()
{
    int m;
    cin>>m;
    while (m--)
    {
        cout<<Run();
    }
    return 0;
}
