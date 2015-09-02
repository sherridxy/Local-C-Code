#include<math.h>
#include<stdio.h>
#include<windows.h>
HANDLE H;
DWORD ret,n,l,v;
#define O FillConsoleOutputCharacter(H,h,1,p,&ret)
void drw(int c,int h)
{
	int i=c<n/2.?0:c-(n-1)/2,e=c<n/2.?c:(n-1)/2;
	COORD p;
	for(; i<=e; i++)p.X=i,p.Y=c-i,O,p.X=l-i,p.Y=c-i,O,p.X=i,p.Y=l-c+i,O,p.X=l-i,p.Y=l-c+i,O;
}
int main()
{
	DWORD i,f=1;
	COORD p= {0,0};
	H=GetStdHandle(STD_OUTPUT_HANDLE);
	while(!scanf("%lu",&n)||n<0||n>24)getchar();
	l=n-1;
	v=(n+1)/2*2-1;
	SetConsoleCursorPosition(H,p);


	for(i=0; i<v; drw(i++,'*'));
	p.X=50;
	SetConsoleCursorPosition(H,p);
	while(Sleep(75),1)f?(drw(--i,' '),!i?f=0:0):(drw(i++,'*'),i==v?f=1:0);
}
