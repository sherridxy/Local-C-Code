#include <iostream>
#include <cmath>
#include <assert.h>
#define MAXSIZE 100
using namespace std;

template <class T>
struct Node
{
	T data;
	Node<T> * next;
	Node() {next=NULL;}
};

template <class T>
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







bool IsRight (char *c) //判断表达式是否合法
{
	int i=1;
	for (i=1;1;i++)
	{
		if (i>MAXSIZE) return false;
		if (c[i]=='.') continue;
		if (c[i]>='0'&&c[i]<='9') continue ;
		if (c[i]=='+'||c[i]=='-'||c[i]=='*'||c[i]=='/') continue ;
		if (c[i]=='('||c[i]==')') continue ;
		if (c[i]=='=') break;
		return false;
	}
	return true;
}

int icp(char x)//栈外优先级
{
	if (x=='=') return 0;
	if (x==')') return 1;
	if (x=='+'||x=='-') return 2;
	if (x=='*'||x=='/') return 4;
	if (x=='(') return 8;
	return -1;

}

int isp(char x) //栈内优先级
{
	if (x=='=') return 0;
	if (x==')') return 8;
	if (x=='+'||x=='-') return 3;
	if (x=='*'||x=='/') return 5;
	if (x=='(') return 1;
	return -1;

}


int main()
{
	MyStack<char> s;
	char c[MAXSIZE+1]={'='};//接受外界输入的字符数组
	char temp[MAXSIZE+20];//接受第一次转换后的临时数组
	cin>>c+1;
	assert(IsRight(c));//断言输入正确
	char *ch=c+1;
	char *t=temp;
	MyStack<double> ds;
	s.Push('=');
	while ((*ch)!='='||s.GetTop()!='=')
    {
        if (*ch>='0'&&*ch<='9') //如果是操作数
        {
            while (((*ch)!='+')&&((*ch)!='-')&&((*ch)!='*')&&((*ch)!='/')&&((*ch)!='=')&&((*ch)!='(')&&((*ch)!=')'))
            {
                *t=*ch;
                ch++;
                t++;//每次t均指向空的位置
            }//出来的时候ch指向操作符
            *t='?';
            t++;
        }
        if (icp(*ch)==isp(s.GetTop()))
        {

            if (s.Pop()=='(') {ch++;continue;}
            else break;
        }
        if (icp(*ch)>isp(s.GetTop())) { s.Push(*ch); ch++;continue;}
        if (icp(*ch)<isp(s.GetTop())) {*t=s.Pop();t++;}
    }
    *t='\0';
    t++;
    double x,y;//两个操作数
    t=temp;//初始化指针t
    while (*t!='\0')
    {
        if ((*t)>='0'&&(*t)<='9')//若为数字
        {
            bool pointFlag=false;
            int befp=0,myCount=1;
            double aftp=0;
            while (1)
                {
                    if (*t=='?')
                    {
                        if (pointFlag==true) {aftp=aftp/myCount;ds.Push(aftp+befp);t++;break;}
                        else {ds.Push(befp);t++;break;}
                    }
                    if (*t=='.') {pointFlag=true;t++;continue;}
                    if (pointFlag==false) {befp=befp*10+*t-'0';t++;continue;}
                    if (pointFlag==true) {myCount*=10;aftp=10*aftp+*t-'0';t++;continue;}
                }
            continue;
        }
        else
        {
            y=ds.Pop();
            x=ds.Pop();
            if (*t=='+') ds.Push(x+y);
            if (*t=='-') ds.Push(x-y);
            if (*t=='*') ds.Push(x*y);
            if (*t=='/') {assert(fabs(y)>0.0000001);ds.Push(x/y);}
            t++;

        }

    }
    cout<<ds.Pop();
	return 0;
}
