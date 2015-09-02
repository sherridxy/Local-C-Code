#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream in("C:\\Users\\Administrator\\Desktop\\att532_2.txt");
    ofstream out("C:\\Users\\Administrator\\Desktop\\result.txt");
    char c[9000];
    char *p=c;
    in.getline(c,9000,'\0');
    while (*p!='E')
    {
        out<<*p;
        p++;
    }
    in.close();
    out.close();
    return 0;
}
