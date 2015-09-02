#include <iostream>
#include <fstream>
int bre;

using namespace std;

int main()
{
    ifstream in("C:\\Users\\Administrator\\Desktop\\data3.txt");
    ofstream out("C:\\Users\\Administrator\\Desktop\\result.txt");
    char c[90000];
    in.getline(c,90000,'\0');
    char *p=c;
    char temp;
    while (*p!='E')
    {
        if (*p>='0'&&*p<='9')
        {
            if (*(p+1)!='+') {out<<*p;p++;}
            else if (*p<'9') {temp=*p+1;out<<temp;cout<<(char)(*p+1)<<endl;p=p+2;}
            else {out<<*p;p++;}
        }
        else {out<<*p;p++;}
    }
    in.close();
    out.close();
    return 0;
}
