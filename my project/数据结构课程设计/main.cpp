#include <iostream>
#define  DEFAULTSIZE 100
#define DEFAULTSIZE_QUE 3
using namespace std;

template <class T> //队列
class MyQueue
{
private:
    int head;
    int tail;
    int maxSize;//数组所能容纳的最多元素个数
    T *elem;
    void _overFlow(void);  //ok
public:
    MyQueue (){maxSize=DEFAULTSIZE_QUE;head=tail=0;elem=new T[maxSize];} //ok
    MyQueue (MyQueue<T> &Q); //ok
    ~MyQueue () {delete []elem;} //ok
    void EnQueue (T &x); //ok
    T DeQueue (); //ok
    T &getFront();  //ok
    int Lengh();
    bool IsEmpty(){return tail==head;}
};

template <class T>
T MyQueue<T>::DeQueue ()
{
    T ret;
   if (head==tail)
   {
       cout<<"队列已空，拒绝出队,返回垃圾值 "<<endl;
       return ret;
   }
   T temp=elem[head];
   head=(head+1)%maxSize;
   return temp;
}

template <class T>
void MyQueue<T>::EnQueue (T &x)
{
    if ((tail+1)%maxSize==head) _overFlow();
    elem[tail]=x;
    tail=(tail+1)%maxSize;
}

template <class T>
void MyQueue<T>::_overFlow(void)
{
    T *temp=new T[maxSize+DEFAULTSIZE_QUE];
    int i=0;
    while (head!=tail)
    {
        temp[i]=elem[head];
        head=(head+1)%maxSize;
        i++;
    }
    maxSize+=DEFAULTSIZE_QUE;
    delete elem;
    head=0;
    tail=i;
    elem=temp;
}

template <class T>
T &MyQueue<T>::getFront()
{
    T ret;
    if (head==tail)
    {
        cout<<"队列已空，无法获取队首元素"<<endl;
        return ret;
    }
    return elem[head];
}

template <class T>
MyQueue<T>::MyQueue (MyQueue<T> &Q)
{
    maxSize=Q.maxSize;
    head=Q.head;
    tail=Q.tail;
    elem=new T[maxSize];
    int i;
    for (i=0;i<maxSize;i++) elem[i]=Q.elem[i];
}

template <class T>
int MyQueue<T>::Lengh()
{
    return (maxSize+tail-head)%maxSize;
}

template <class T>//栈结点
struct Node
{
	T data;
	Node<T> * next;
	Node() {next=NULL;}
};

template <class T>//栈的定义
class MyStack
{
private:
	Node<T> *top;
	void _makeEmpty();//清空函数 ok
public:
	MyStack();//构造函数 ok
    MyStack(MyStack<T> & S);//复制构造函数 ok
	~MyStack(){	_makeEmpty();delete top;}//析构函数 ok
	void Push(T x);// ok
	T Pop();//弹出栈顶 ok
	T& GetTop();//得到栈顶元素 ok
	bool IsEmpty(){if (top->next==NULL) return true;else return false;}
};

template <class T>
MyStack<T>::MyStack()
{
	top=new Node<T>;//新建表头节点
}

template <class T>
MyStack<T>::MyStack(MyStack<T> & S)
{
	Node<T> *pi=top=new Node<T>;
	Node<T> *po=S.top;
	while (po->next!=NULL)
	{
		pi->data=po->data;
        pi->next=new Node<T>;
		pi=pi->next;
		po=po->next;
	}
	pi->data=po->data;
}


template <class T>
void MyStack<T>::Push(T x)
{
	Node<T> *temp=new Node<T>;
	temp->data=x;
	temp->next=top->next;
	top->next=temp;
}

template <class T>
T MyStack<T>::Pop()
{
	T atrtemp;
	if (top->next!=NULL)//若非空
	{
		Node<T> *temp;
		temp=top->next;
		atrtemp=temp->data;
		top->next=temp->next;
        delete temp;
	}
	else {cout<<"栈已空，无法出栈"<<endl;}
	return atrtemp;
}

template <class T>
T& MyStack<T>::GetTop()
{
    T rubbish;
	if (top->next!=NULL)//若非空
	{
		return top->next->data;
	}
	else cout<<"栈已空"<<endl;
	return rubbish;
}

template <class T>
void MyStack<T>::_makeEmpty()
{
	while (top->next!=NULL)
	{
		Pop();
	}
}






















template <class T>
struct TreeNode
{
	T data;
	TreeNode<T> *leftChild;
	TreeNode<T> *rightChild;
	TreeNode() {leftChild=NULL;rightChild=NULL;data=0;}
	TreeNode(T value) {leftChild=NULL;rightChild=NULL;data=value;}
};


template <class T>
class BinTree
{
private:
	TreeNode<T> *root;
public:
    int TellDep (T x);
    int TellDep(TreeNode<T> *subTree);
    TreeNode<T>* Search(TreeNode<T> *subTree,T x) ;//在subTree的子树中按照前序遍历查找第一个值为x的结点
	BinTree () {root=NULL;}           //构造函数 ok
	BinTree (BinTree<T> & B);        //复制构造函数
	void Chop (TreeNode<T> *& subTree);         //删除subTree指向的子树 ok
	~BinTree () {Chop(root);}       //析构函数  ok
	void InOrderInMirror(TreeNode<T> *subTree,void(*visit)(TreeNode<T> *p,MyQueue<T> & Q),MyQueue<T> & Q);//包含队列的镜像中序遍历
	void PreOrder(TreeNode<T> *subTree,T arr[DEFAULTSIZE],int &i);
	friend TreeNode<char> * Input(BinTree<char> & B);
	friend void Output(BinTree<char> &B);
};


template <class T>
void BinTree<T>::PreOrder(TreeNode<T> *subTree,T arr[DEFAULTSIZE],int &i)
{
    if (subTree==NULL) return;
    arr[i++]=subTree->data;
    if (subTree->leftChild||subTree->rightChild) arr[i++]='(';
    PreOrder(subTree->leftChild,arr,i);
    PreOrder(subTree->rightChild,arr,i);
    if (subTree->leftChild||subTree->rightChild) arr[i++]=')';
}

TreeNode<char> *  Input (BinTree<char> & B) //已声明为模板树的友元函数，可以访问其任意实例
{
	if (B.root!=NULL) {cout<<"该树已存在"<<endl;return NULL;}
    char c[DEFAULTSIZE];
	char *ch=c;  //字符指针
	cin>>ch;
	MyStack<TreeNode<char> *> S;//储存结点指针的栈
	B.root=new TreeNode<char>(*ch);
	int flag;
	TreeNode<char> *p=B.root;
	while (ch++,*ch!='#')
	{
		if (*ch=='(') {flag=1;S.Push(p);}
		else if (*ch==',') flag=2;
		     else if(*ch==')') S.Pop();
			 else
			 {
				 if (flag==1) p=S.GetTop()->leftChild=new TreeNode<char>(*ch);
				 else p=S.GetTop()->rightChild=new TreeNode<char>(*ch);
			 }
	}
	return B.root;
}

template <class T>
void BinTree<T>::Chop (TreeNode<T> *& subTree)
{
	if (subTree==NULL) return;
	Chop (subTree->leftChild);
	Chop (subTree->rightChild);
    delete subTree;
    subTree=NULL;
}


template <class T>
void BinTree<T>::InOrderInMirror(TreeNode<T> *subTree,void(*visit)(TreeNode<T> *p,MyQueue<T> & Q),MyQueue<T> & Q)
{
    if (subTree==NULL) return;
    InOrderInMirror(subTree->rightChild,visit,Q);
    visit (subTree,Q);
    InOrderInMirror(subTree->leftChild,visit,Q);
}

template <class T>
TreeNode<T>* BinTree<T>::Search(TreeNode<T> *subTree,T x)
{
    TreeNode<T>* p;
    if (subTree==NULL) return NULL;
    if (subTree->data==x) return subTree;
    if (p=Search(subTree->leftChild,x)) return p;
    if (p=Search(subTree->rightChild,x)) return p;
    return NULL;
}

template <class T> //通过子树指针返回深度
int BinTree<T>::TellDep(TreeNode<T> *subTree)
{
    if (subTree==NULL) return 0;
    int a,b,m;
    m=((a=TellDep(subTree->leftChild))>(b=TellDep(subTree->rightChild)))?a+1:b+1;
    return m;
}

template <class T> //通过查找前序下满足条件的指针，返回该指针指向的子树的深度
int BinTree<T>::TellDep (T x)
{
    return TellDep(Search(root,x));
}

void Show(TreeNode<char> *p,MyQueue<char> &Q)
{
   Q.EnQueue (p->data);
}

int NumCal (char arr[DEFAULTSIZE],char x)
{
    int i=1;
    int j=0;
    while (arr[j]!=x)
    {
        if (arr[j]=='(') i++;
        if (arr[j]==')') i--;
        j++;
    }
    return i;
}

void Output(BinTree<char> &B)
{
    int num;
    MyQueue<char> Q;
    B.InOrderInMirror(B.root,Show,Q);
    int i=0;
    char arr[DEFAULTSIZE];
    B.PreOrder(B.root,arr,i);
    while (!Q.IsEmpty())
    {
        num=NumCal(arr,Q.getFront());
        for (i=1;i<num;i++) cout<<"  ";
        cout<<Q.DeQueue()<<endl;
    }
}



int main()
{
	BinTree<char> B,temp;
    Input(B);
    Output(B);
    char ch;
    cout<<"输入要查找的元素"<<endl;
    cin>>ch;
	while (ch!='q')
	{
		cout<<"元素值为"<<ch<<"对应子树深度为：";
		cout<<B.TellDep(ch);
		cin>>ch;
	}
	return 0;
}
