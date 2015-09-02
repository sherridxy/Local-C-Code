#include <iostream>
#include <assert.h>
using namespace std;

struct Xnode//多项式的某一项
{
	int level;
	double value;
	Xnode (int l=0,double v=0)
	{
		level=l;
		value=v;
	}

};



template<class T>
struct Node
{
    T data;
    Node<T> *point;
    Node () {point=NULL;}
};

template <class T>
struct List
{
private:
    Node<T> *head;
	int maxLevel;
public:
    List () {head=new Node<T>;}//ok
    List (List<T> &L);//ok
    ~List ();//析构函数ok
    void MakeEmpty();//把表变成空表，仅保留表头节点ok
    int Length();//返回表长ok
    Node<T> *GetHead(void) {return head;}//返回head ok
    Node<T> *Search(T x) ;//搜索x，存在返回结点地址，反之返回NULL  ok
    bool GetData(int i,T &x);//将第i个元素赋给x，返回值代表成功与否 ok
    bool SetData (int i,T x);//用x给元素赋值，返回值为是否成功（与教材不同）ok
    bool Insert (int i,T x);//在第i个元素后插入x ok
    bool Remove (int i);//删除第i个元素(与教材不同) ok
    bool IsEmpty() {return Length()==0;} //ok
    void Show(void); //ok
    bool PutInEnd(T x); //ok
	bool PutInEnd(int l,double v);
};

template<class T>
List<T>::List (List<T> &L)
{
    Node<T> *po=L.head;
    Node<T> *pi=head=new Node<T>;
    while(po->point!=NULL)//当Po指向的节点存在下一个节点的时候
    {
        pi->point=new Node<T>;
        po=po->point;
        pi=pi->point;
        pi->data=po->data;
    }
}

template<class T>
void List<T>::MakeEmpty()
{
    Node<T> *p;
    while (head->point!=NULL)
    {
        p=head->point;
        head->point=head->point->point;
        delete p;
    }
}

template<class T>
List<T>::~List ()
{
    Node<T> *p=head;
    MakeEmpty();
    cout<<"析构函数响应";
    delete p;
}

template<class T>
int List<T>::Length()
{
    Node<T> *p=head;
    int count=0;
    while (p->point!=NULL)
    {
        p=p->point;
        count++;
    }
    return count;
}

template <class T>
Node<T> *List<T>::Search(T x)
{
    Node<T> *p=head;
    while (p->point!=0)
    {
        p=p->point;
        if (p->data==x) return p;
    }
    cout<<"找不到该元素"<<endl;
    return NULL;
}


template<class T>
bool List<T>::GetData(int i,T &x)
{
    Node<T>* p=head;
    int length=Length();
    int count=0;
    if (i>0&&i<=length)
    {
        for (count=0;count<i;count ++) p=p->point;
        x=p->data;
        return true ;
    }
    else
    {
        cout<<"取值操作非法"<<endl;
        return false;
    }
}

template<class T>
bool List<T>::SetData (int i,T x)
{
    Node<T>* p=head;
    int length=Length();
    int count=0;
    if (i>0&&i<=length)
    {
        for (count=0;count<i;count ++) p=p->point;
        p->data=x;
        return true ;
    }
    else
    {
        cout<<"设定值操作非法"<<endl;
        return false;
    }

}

template<class T>
bool  List<T>::Insert (int i,T x)
{
    Node<T>* p=head;
    Node<T>*p_temp;
    int length=Length();
    int count=0;
    if (i>0&&i<=length)
    {
        for (count=0;count<i;count ++) p=p->point;//此时p指向第i个元素
        p_temp=new Node<T>;
        p_temp->point=p->point;
        p_temp->data=x;
        p->point=p_temp;
        return true;
    }
    else
    {
        cout<<"插入操作非法"<<endl;
        return false;
    }

}

template<class T>
bool List<T>::Remove (int i)
{
    Node<T>* p=head;
    Node<T>*p_temp;
    int length=Length();
    int count=0;
    if (i>0&&i<=length)
    {
        for (count=0;count<i-1;count ++) p=p->point;//此时p指向第i-1个元素
        p_temp=p->point;
        p->point=p_temp->point;
        delete p_temp;
        return true;
    }
    else
    {
        cout<<"删除操作非法"<<endl;
        return false;
    }
}

template <class T>
void List<T>::Show()
{
    Node<T> *p=head;
    while (p->point!=NULL)
    {
        p=p->point;
        cout<<p->data.value<<"x^"<<p->data.level;
        if (p->point!=NULL && p->point->data.value >0) cout<<'+';


    }
    cout<<endl;
}

template <class T>
bool List<T>::PutInEnd(T x)
{
    Node<T> *p=head;
    Node<T> *p_temp;
    while (p->point!=NULL)
    {
        p=p->point;
    }
    p_temp=new Node<T>;
    if (p_temp==NULL) return false;
    p_temp->data=x;
    p->point=p_temp;
    return true;
}

template <class T>
bool List<T>::PutInEnd(int l,double v)
{
	Xnode xtemp(l,v);
    Node<T> *p=head;
    Node<T> *p_temp;
    while (p->point!=NULL)
    {
        p=p->point;
    }
    p_temp=new Node<T>;
    if (p_temp==NULL) return false;
    p_temp->data=xtemp;
    p->point=p_temp;
    return true;
}

List<Xnode> Add (List<Xnode> &a,List<Xnode> &b)
{
    List<Xnode> c;
    int i,maxlevelA,maxlevelB,maxlevel;
	double *ans =new double[maxlevel+1];
	Node<Xnode> *pa,*pb;
	pa=a.GetHead();
	pb=b.GetHead();
	pa=pa->point;
	pb=pb->point;
	for (i=1;i<=a.Length();i++)
    {
        ans[pa->data.level] += pa->data.value;
        maxlevelA=pa->data.level;
        pa=pa->point;
    }
    for (i=1;i<=b.Length();i++)
    {
        ans[pb->data.level] += pb->data.value;
        maxlevelB=pb->data.level;
        pb=pb->point;
    }
    maxlevel= maxlevelA>maxlevelB ? maxlevelA:maxlevelB ;
	for ( i=0;i<=maxlevel;i++)
	{
		if (ans[i]!=0) c.PutInEnd(i,ans[i]);
	}
	delete []ans;
	return c;

}

List<Xnode> Cross(List<Xnode> &a,List<Xnode> &b)
{
	int i,j;
	List<Xnode> c;
	Node<Xnode> *pa,*pb;
	pa=a.GetHead();
	pb=b.GetHead();
	pa=pa->point;
	pb=pb->point;
	int maxlevelA,maxlevelB,maxlevel;
	Xnode temp;
	a.GetData(a.Length(),temp);
	maxlevelA=temp.level;
	b.GetData(b.Length(),temp);
	maxlevelB=temp.level;
	maxlevel=maxlevelA+maxlevelB;
	double *ans=new double [maxlevel+1];
	for ( i=1;i<=a.Length();i++)
	{
		for ( j=1;j<=b.Length();j++)
		{
			ans[pa->data.level+pb->data.level] += (pa->data.value)*(pb->data.value);
			pb=pb->point;
		}
        pa=pa->point;
        pb=b.GetHead();
        pb=pb->point;

	}
	for ( i=0;i<=maxlevel;i++)
	{
		if (ans[i]!=0) c.PutInEnd(i,ans[i]);
	}
	delete []ans;
	return c;
}












int main()
{
	List<Xnode> a,b,c;
	a.PutInEnd (1,2);
	a.PutInEnd(2,6);
	a.PutInEnd(3,9);
	a.PutInEnd(5,2);
	a.PutInEnd(8,3);
	b.PutInEnd(3,3);
	b.PutInEnd(8,2);
	b.PutInEnd(10,2);
	b.PutInEnd(22,2);
	a.Show();
	b.Show();
	cout<<"after add"<<endl;
	Add (a,b).Show();
	cout<<"after cross"<<endl;
	Cross (a,b).Show();
	int i;
	cin>>i;
    return 0;
}
