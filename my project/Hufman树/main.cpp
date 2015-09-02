#include <iostream>
#include <fstream>
#define DEFAULTSIZE_MINHEAP 2
#include <ctime>
using namespace std;
int br;

template <class T>
class MinHeap
{
private:
    T *arr;
    int maxSize;
    int last;
    void _shiftDown (int start,int ende);
    void _shiftUp (int current);
    void _reSize ();
public:
    T &Front(){return arr[0];}
    void Put(T x);
    T Remove();
    void Show() {for (int i=0;i<=last;i++) cout<<arr[i]<<' ';cout<<endl;}
    MinHeap(int sz=DEFAULTSIZE_MINHEAP);
    MinHeap (T *a,int n);
    ~MinHeap (){delete []arr;}
    int Length(){return last+1;}
};

template <class T>
MinHeap<T>::MinHeap(int sz)
{
    maxSize=sz;
    last=-1;
    arr=new T[sz];
}

template <class T>
MinHeap<T>::MinHeap (T *a,int n)
{
    last=-1;
    maxSize=n+DEFAULTSIZE_MINHEAP;
    arr=new T[maxSize];
    for (int i=0;i<n;i++)
    {
        last++;
        arr[last]=a[i];
    }
    int j=(last-1)/2;
    for (int i=j;i>=0;i--) _shiftDown(i,last);
}

template <class T>
void MinHeap<T>::_shiftDown (int start,int ende) //调整的开始下标和最后的下标
{
    T temp=arr[start];
    int current=start;
    int minChild;
    while (true)
    {
        minChild=current*2+1;
        if (minChild>ende) break;
        if ((minChild+1)<=ende&&arr[minChild+1]<arr[minChild]) minChild++;
        if (temp<=arr[minChild]) break;
        else
        {
            arr[current]=arr[minChild];
            current=minChild;
        }
    }
    arr[current]=temp;
}

template <class T>
void MinHeap<T>::_shiftUp (int current)
{
    T temp=arr[current];
    int father;
    while (current>0)
    {
        father=(current-1)/2;
        if (arr[father]>temp)
        {
            arr[current]=arr[father];
            current=father;
        }
        else break;
    }
    arr[current]=temp;
}

template <class T>
void MinHeap<T>::_reSize ()
{
    int sz=maxSize+DEFAULTSIZE_MINHEAP;
    T *temp=new T[sz];
    for (int i=0;i<=last;i++) temp[i]=arr[i];
    maxSize=sz;
    delete []arr;
    arr=temp;
}

template <class T>
void MinHeap<T>::Put(T x)
{
    if (last==maxSize-1) _reSize();
    last++;
    arr[last]=x;
    _shiftUp(last);
}

template <class T>
T MinHeap<T>::Remove()
{
    T ret;
    if (last==-1)
    {
        cout<<"堆已空，返回垃圾值"<<endl;
        return ret;
    }
    ret=arr[0];
    arr[0]=arr[last];
    last--;
    _shiftDown(0,last);
    return ret;
}


struct HufTreeNode
{
    HufTreeNode *leftChild;
    HufTreeNode *rightChild;
    int weight;
    char value;
    HufTreeNode (int w=0,char v='\0'){leftChild=NULL;rightChild=NULL;weight=w;value=v;}
};

struct HufTreeNodePtr  //指向哈夫曼树结点的指针，设计成结构体以便在最小堆中比较权值大小
{
    HufTreeNode *p;
    bool operator > (HufTreeNodePtr Q) {return p->weight>Q.p->weight;}
    bool operator < (HufTreeNodePtr Q) {return p->weight<Q.p->weight;}
    bool operator <= (HufTreeNodePtr Q) {return p->weight<=Q.p->weight;}
    bool operator >= (HufTreeNodePtr Q) {return p->weight>=Q.p->weight;}
    bool operator == (HufTreeNodePtr Q) {return p->weight==Q.p->weight;}
    HufTreeNodePtr (HufTreeNode* ptr=NULL) {p=ptr;}
};

class HuffmanTree
{
private:
    HufTreeNode *root;
public:
    HuffmanTree ();
    void PreOrderShow(HufTreeNode *subTree,char *c,int &n);
    void Show (char *c,int &n) {PreOrderShow(root,c,n);cout<<endl;Code(c,n);}
    void Translate (char * c);
    void Code (char *c,int n);
};

void OneZero (char x,char *c,char *retn)
{
    int i=0;
    int j=0;
    while (c[i]!=x)
    {
        if (c[i]=='(') retn[j++]='0';
        if (c[i]==',') retn[j-1]='1';
        if (c[i]==')') j--;
        i++;
    }
    retn[j]='\0';

}

void HuffmanTree::Code (char *c,int n)
{
    char retn[50];
    char arr[50];
    int i=0;
    for (int j=0;j<n;j++)
    {
        if (c[j]>='a'&&c[j]<='z') arr[i++]=c[j];
    }
    for (int j=0;j<i;j++)
    {
        cout<<arr[j]<<' ';
        OneZero (arr[j],c,retn);
        cout<<retn;
        cout<<endl;
    }
}


void HuffmanTree::Translate (char *c)
{
    HufTreeNode *current=root;
    int i=0;
    while (c[i]!='#')
    {
        if (current->value>='a'&&current->value<='z') {cout<<current->value;current=root;continue;}
        if (c[i]=='0') {current=current->leftChild;i++;continue;}
        if (c[i]=='1') {current=current->rightChild;i++;continue;}
    }
    if (current->value>='a'&&current->value<='z') cout<<current->value;
}

void HuffmanTree::PreOrderShow(HufTreeNode *subTree,char *c,int &n)
{
    if (subTree==NULL) return;
    if (subTree->value>='a'&&subTree->value<='z') {cout<<subTree->value;c[n++]=subTree->value;}
    else {cout<<'0';c[n++]='0';}
    if (subTree->leftChild) {cout<<'(';c[n++]='(';}
    PreOrderShow(subTree->leftChild,c,n);
    if (subTree->rightChild) {cout<<',';c[n++]=',';}
    PreOrderShow(subTree->rightChild,c,n);
    if (subTree->rightChild) {cout<<')';c[n++]=')';}
}

 HuffmanTree::HuffmanTree()
 {
     MinHeap<HufTreeNodePtr> M;
     int calcu[26]={0};//0->a
     HufTreeNode *p;
     HufTreeNodePtr ptr;
     char c[100];
     cout<<"请输入以#结尾的一串小写英文序列"<<endl;
     cin>>c;
     int i=0;
     while (c[i]!='#')
     {
         calcu[c[i]-'a']++;
         i++;
     }
     for (int i=0;i<26;i++)
     {
         if (calcu[i]==0) continue;
         cout<<calcu[i]<<' '<<(char)('a'+i)<<endl;/////////////////////////////////
         p=new HufTreeNode(calcu[i],'a'+i);
         ptr.p=p;
         M.Put(ptr);
     }
     HufTreeNodePtr ptra,ptrb;
     while (M.Length()>1)
     {
         ptrb=M.Remove();
         ptra=M.Remove();
         ptr.p=new HufTreeNode(ptra.p->weight+ptrb.p->weight);
         ptr.p->leftChild=ptra.p;
         ptr.p->rightChild=ptrb.p;
         M.Put(ptr);
     }
     root=M.Front().p;
 }




int main()
{

    HuffmanTree H;
    char c[50];
    int n=0;
    H.Show(c,n);
    cout<<endl;
    cout<<"请输入01序列#结尾"<<endl;
    cin>>c;
    H.Translate(c);
    return 0;
}
