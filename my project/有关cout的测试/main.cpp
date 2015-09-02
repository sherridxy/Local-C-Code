#include <iostream>

using namespace std;
class OOO
{
 private:
     int i;
};
OOO Myout;

OOO &operator <<(OOO out,int x)
{
    cout<<x;
    return out;
}
OOO &operator <<(OOO out,char x)
{
    cout<<x;
    return out;
}

int A()
{
    cout<<"hello"<<endl;
    return 1;
}
int B()
{
    cout<<"bye"<<endl;
    return 2;
}

OOO &operator +(OOO out,int x)
{
    cout<<x;
    return out;
}
OOO &operator +(OOO out,char x)
{
    cout<<x;
    return out;
}

void M(int m,int n){;}

int main()
{
    operator <<(operator <<(operator <<(cout,A()),' '),B());
    Myout+A()+' '+B();
    int i=A()+B();
    M(A(),B());
    cout<<A()<<' '<<B();
    Myout<<A()<<' '<<B();
    operator <<(operator <<(operator <<(Myout,A()),' '),B());
    return 0;
}
