#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

template <class T>
class STL_MinHeap
{
private:
    vector<T> data;
public:
    int Length(){return data.size();}
    void Push(T &x)
    {
        data.push_back(x);
        push_heap(data.begin(),data.end());
    }
    T Front()
    {
        return *data.begin();
    }
    T Pop()
    {
        T temp=Front();
        pop_heap(data.begin(),data.end());
        data.pop_back();
        return temp;
    }
};

int main()
{
    ifstream myin("C:\\Users\\Administrator\\Desktop\\ans.txt");
    STL_MinHeap<double> a;
    for (int i=0; i<100000; i++)
    {
        double temp;
        myin>>temp;
        a.Push(temp);
    }
    cout<<a.Pop()<<endl;
    myin.close();
    return 0;
}
