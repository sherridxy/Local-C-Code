#include <iostream>
using namespace std;
template<class T>
struct Node
{
    T data;
    Node<T> *point;
    Node () {point=NULL;}
};

template <class T>
class List
{
private:
    Node<T> *head;
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
        cout<<p->data<<' ';
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











int main()
{

    return 0;
}
