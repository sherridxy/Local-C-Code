#include <iostream>

using namespace std;
int bre;
int level,rule,user,doc,aciton;

template <class T>
class MyStack
{
private:
    T *top;
    int last;
    int maxSize;
    void _reSize ()
    {
        int sz=2*maxSize;
        T *temp=new T[sz];
        for (int i=0;i<=last;i++) temp[i]=top[i];
        maxSize=sz;
        delete []top;
        top=temp;
    }
public:
    ~MyStack (){delete []top;}
    MyStack()
    {
        top=new T[10000];
        last=-1;
        maxSize=10000;
    }
    void Push (T &x)
    {
        if (last+1==maxSize) _reSize();
        top[++last]=x;
    }
    T  Pop()
    {
        last--;
        return top[last+1];
    }
    bool IsEmpty()
    {
        return last==-1;
    }

};


struct GraphNode
{
    int num;
    GraphNode *next;
    GraphNode()
    {
        num=0;
        next=NULL;
    }
};

struct GraphList
{
    GraphNode *head;
    GraphNode *tail;
    GraphList()
    {
        head=tail=new GraphNode;
    }
    void Input (int &x)
    {
        GraphNode* temp=new GraphNode;
        temp->num=x;
        tail->next=temp;
        tail=temp;
    }
    void Show(void)
    {
        GraphNode *p=head;
        while (p->next!=NULL)
        {
            p=p->next;
            cout<<p->num<<' ';
        }
        cout<<endl;
    }
};

MyStack <GraphNode *> MG;
MyStack <int> StepRecord;


int NearRoute(GraphList *G,int &from,int &destn)
{
    int myCount=0;
    GraphNode *p;
    if (from==destn) return 0;
    p=G[from].head->next;
    if (p!=NULL) myCount++;
    int minStep=-1;
    while (p!=NULL||!MG.IsEmpty())
    {
        if (minStep!=-1&&myCount>minStep)
        {
            if (!MG.IsEmpty())
            {
                p=MG.Pop();
                myCount=StepRecord.Pop();
                continue;
            }
            else return minStep;


        }
        if (p!=NULL&&p->num==destn&&(minStep<0||myCount<minStep)) minStep=myCount;
        if (p==NULL)
        {
            p=MG.Pop();
            myCount=StepRecord.Pop();
            continue;
        }
        if (p->next!=NULL)
        {
            MG.Push(p->next);
            StepRecord.Push(myCount);
        }
        p=G[p->num].head->next;
        if (p!=NULL) myCount++;
    }
    return minStep;
}

int Dfs(GraphList *G,int &m,int &n)
{
    int minRord=-1;
    int itemp1,itemp2,itemp;
    int vetix;
    for (int i=1;i<=level;i++)
    {
        itemp1=NearRoute(G,i,m);
        if (itemp1<0) continue;
        if (minRord!=-1&&itemp1>minRord) continue;
        itemp2=NearRoute(G,i,n);
        if (itemp2<0) continue;
        itemp=itemp1+itemp2;
        if (minRord==-1||itemp<minRord)
        {
            minRord=itemp;
            vetix=i;
        }
    }
    return vetix;
}

int main()
{

    cin>>level>>rule>>user>>doc>>aciton;
    GraphList *G=new GraphList[level+1];
    int temp_x,temp_y;
    for (int i=rule;i>0;i--)
    {
        cin>>temp_x>>temp_y;
        G[temp_x].Input(temp_y);
    }
    int *u=new int[user+1];
    for (int i=1;i<=user;i++)
    {
        cin>>u[i];
    }
    int *d=new int[doc+1];
    for (int i=1;i<=doc;i++)
    {
        cin>>d[i];
    }
    while (aciton--)
    {
        int a;
        int b;
        char lett[10];
        cin>>a>>lett>>b;
        if (lett[0]=='w')
        {
            int temp=Dfs(G,u[a],d[b]);
            d[b]=temp;
            cout<<temp<<endl;
            continue;
        }
        if (lett[0]=='r')
        {
            int temp=Dfs(G,u[a],d[b]);
            u[a]=temp;
            cout<<temp<<endl;
            continue;
        }
    }
    return 0;

}
