#include <iostream>
#include <ctime>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
int bre;
template <class T>
bool STL_MinHeap_Compare(T &a,T &b);

template <class T>
class STL_MinHeap
{
private:
    vector<T> data;
public:
    friend bool STL_MinHeap_Compare <T> (T &a,T &b);
    int Length(){return data.size();}
    void Push(T &x)
    {
        data.push_back(x);
        push_heap(data.begin(),data.end(),STL_MinHeap_Compare<T>);
    }
    T Front()
    {
        return *data.begin();
    }
    T Pop()
    {
        T temp=Front();
        pop_heap(data.begin(),data.end(),STL_MinHeap_Compare<T>);
        data.pop_back();
        return temp;
    }
};

template <class T>
bool STL_MinHeap_Compare(T &a,T &b)
{
    if (a<b) return false;
    else return true;
}

int main()
{srand(41);
    STL_MinHeap<int> H;
    for (int i=0;i<20;i++)
    {
        int r=rand()%100;
        H.Push(r);
        cout<<r<<' ';
    }
    cout<<endl<<endl;
    for (int i=0;i<20;i++)
    {
        int temp=H.Pop();
        cout<<temp<<' ';
    }
    cout<<endl;
    return 0;
}
