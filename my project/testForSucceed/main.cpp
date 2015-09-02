#include <iostream>

using namespace std;

class A
{
private:
    int age;
public:
    A(int x) {age=x;}
    int& Age (void) {return age;}
};

class B:public A
{
private:
    int num;
public:
    B(int x=1) :A(-1){num=x;}
    int& Age (void) {return num;}
};

class C
{
private:
    int age;
public:
    C(int x=2) {age=x;}
    int& Age(void) {return age;}
};

class D :public B,public C
{
private:
    int age;
public:
    D (int x=100):B(),C(){age=x;}
    int& Age(void) {return age;}
};





int main()
{
    D t;
    cout<<t.A::Age();
    return 0;
}
