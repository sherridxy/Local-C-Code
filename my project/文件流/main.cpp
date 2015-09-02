#include <iostream>
#include <fstream>

using namespace std;
int x_pos[48]={0};
int y_pos[48]={0};

int main()
{
    int mycount=0;
    int xtemp;
    int ytemp;
    int flag=1;
    char c[9000];
    ifstream in;
    in.open("C:\\Users\\Administrator\\Desktop\\data.txt");
    in.getline(c,9000,'\0');
    cout<<c<<endl;
    char *p=c;
    while(mycount<48)
    {
        if (*p==' ')
        {
            if (flag==0) {flag=1;ytemp=0;x_pos[mycount]=xtemp;p++;}
            else
                {
                    flag=0;
                    xtemp=0;
                    p++;
                }
        }
        else if (*p>='0'&&*p<='9')
        {
            if (flag==0) {xtemp=xtemp*10+*p-'0';p++;}
            else {ytemp=ytemp*10+*p-'0';p++;}
        }
        else if (*p=='\n')
        {
            y_pos[mycount]=ytemp;
            mycount++;
            p++;
        }
        else p++;

    }
    for (int i=0;i<48;i++) cout<<x_pos[i]<<' ';
    cout<<endl;
    for (int i=0;i<48;i++) cout<<y_pos[i]<<' ';
    cout<<endl;
    in.close();
    return 0;
}
