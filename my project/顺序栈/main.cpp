#include <iostream>

using namespace std;
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
        T *temp=new [sz];
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


int main()
{
    MyStack<int> S;
    return 0;
}
