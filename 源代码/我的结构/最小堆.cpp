#include <iostream>
#define DEFAULTSIZE_MINHEAP 2
using namespace std;

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






int main()
{


    return 0;
}
