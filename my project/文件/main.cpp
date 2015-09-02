#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    int i;
    char c[10];
    ifstream fin;
    fin.open("rec.txt");
    if (!fin) {cout<<"null"<<endl;return -1;}
    c[0]= fin.get();
    c[1]='\0';
    if (!fin) cout<<"null"<<endl;
    return 0;



}
