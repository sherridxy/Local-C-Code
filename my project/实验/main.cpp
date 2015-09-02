#include <iostream>
using namespace std;



int main()
{char c[50]="123.4?";
char *t=c;
bool pointFlag=false;
int befp=0,myCount=1;
double aftp=0;
while (1)
{
   if (*t=='?')
  {
    if (pointFlag==true) {aftp=aftp/myCount;cout<<aftp+befp<<endl;t++;goto then;}
    else {cout<<befp<<endl;t++;goto then;}
  }
  if (*t=='.') {pointFlag=true;t++;continue;}
  if (pointFlag==false) {befp=befp*10+*t-'0';t++;continue;}
  if (pointFlag==true) {myCount*=10;aftp=10*aftp+*t-'0';t++;continue;}

}
then: ;
    return 0;
}
