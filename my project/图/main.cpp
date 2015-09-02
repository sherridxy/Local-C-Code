#include <iostream>
#define maxValue 9999
using namespace std;

class Graph
{
public:
    Graph(int n);
    int  GetWeight(int i,int j) {return Edge[i][j];}
    ~Graph()
    {
        for (int i=0;i<numVertices;i++) delete Edge[i];
        delete Edge;
    }
    void Show();
    friend int MaxDistence(Graph &G,int v,bool flag);
private:
    int maxVertices;
    int numEdges;
    int numVertices;
    int **Edge;
};

Graph::Graph(int n)
 {
        numEdges=0;
        Edge=new int*[n];
        maxVertices=n;
        numVertices=n;
        for (int i=0;i<n;i++)
        {
            Edge[i]=new int[n];
        }
        for (int i=0;i<n;i++)
        {
            for (int j=0;j<n;j++)
            {
                if (i==j) {Edge[i][j]=0;continue;}
                Edge[i][j]=maxValue;
            }
        }
        cout<<"请输入边"<<endl;
        int from,ende,weight;
        cin>>from>>ende>>weight;
        while (from!=-1)
        {
            if (from>=n&&ende>=n) break;
            if (Edge[from][ende]==maxValue)
            {
                Edge[from][ende]=weight;
                numEdges++;
            }
            cin>>from>>ende>>weight;
        }
}

void Graph::Show()
{
    for (int i=0;i<numVertices;i++)
    {
        for (int j=0;j<numVertices;j++)
        {
            cout<<Edge[i][j]<<' ';
        }
        cout<<endl;
    }
}


int MaxDistence(Graph &G,int v,bool flag)
{
    int n=G.numVertices;
    int *dist=new int[n];
    bool *S=new bool[n];
    int w,min;
    for (int i=0;i<n;i++)
    {
        dist[i]=G.GetWeight(v,i);
        S[i]=false;
    }
    S[v]=true;dist[v]=0;
    for (int i=0;i<n-1;i++)
    {
        min=maxValue;
        int u=v;
        for (int j=0;j<n;j++)
        {
            if (S[j]==false&&dist[j]<min) {u=j;min=dist[j];}
        }
        S[u]=true;
        for (int k=0;k<n;k++)
        {
            w=G.GetWeight(u,k);
            if (S[k]==false&&w<maxValue&&dist[u]+w<dist[k])
            {
                dist[k]=dist[u]+w;
            }
        }
    }
    int maxDist=0;
    for (int i=0;i<n;i++)
    {
        if (dist[i]<maxValue&&dist[i]>maxDist) maxDist=dist[i];
    }
    if (flag==false) return maxDist;
    cout<<"各点距离医院的距离依次为：";
    for (int i=0;i<n;i++) cout<<dist[i]<<' ';
    cout<<endl;
    return maxDist;

}


int main()
{
    int n=0;
    cout<<"请输入顶点数"<<endl;
    cin>>n;
    Graph G(n);
    int greatPlace=-1;
    int currentNear=maxValue;
    int temp;
    for (int i=0;i<n;i++)
    {
        if ((temp=MaxDistence(G,i,false))<currentNear)
        {
            cout<<i<<"距离为 "<<temp<<endl;
            greatPlace=i;
            currentNear=temp;
        }
    }
    cout<<"医院的最佳地址是："<<greatPlace<<endl;
    cout<<"距离该医院最远距离是："<<currentNear<<endl;
    MaxDistence(G,greatPlace,true);
    return 0;
}
