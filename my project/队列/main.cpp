#include <iostream>
#include <assert.h>
#include <ctime>
#define DEFAULTSIZE_QUE 3

using namespace std;


template <class T>
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


int main()
{

    return 0;
}
