#include <iostream>
#include <fstream>
int bre;

using namespace std;

int main()
{
    bool pointFlag=false;
    ifstream in("C:\\Users\\Administrator\\Desktop\\ch130.txt");
    ofstream out("C:\\Users\\Administrator\\Desktop\\result.txt");
    char c[90000];
    in.getline(c,90000,'\0');
    char *p=c;
    while (*p!='E')
    {
        if (*p>='0'&&*p<='9')
        {
            if (pointFlag==false) {out<<*p;p++;}
            else if (*(p-1)=='.')
            {
                if(*p>='5') {out<<'+';p++;}
                else p++;
            }
            else if(*(p-1)<'0'||*(p-1)>'9') pointFlag=false;
            else p++;
        }
        else if (*p=='.') {pointFlag=true;p++;}
        else {out<<*p;p++;}
    }
    in.close();
    out.close();
    return 0;
}
