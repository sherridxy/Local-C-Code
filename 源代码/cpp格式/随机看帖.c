#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int main()
{
	srand(time(0));
	char *p="http://tieba.baidu.com/p/";
	char ch[35+6];
	ch[0]='@';
	ch[1]='s';
	ch[2]='t';
	ch[3]='a';
	ch[4]='r';
	ch[5]='t';
	ch[6]=' ';
	for (int i=0+7; i<25+7; i++) ch[i]=p[i-7];
	int m=10;
	while (m--)
	{
		for (int i=25+7; i<25+9+7; i++) ch[i]=rand()%10+'0';
		ch[25+9+7]='\0';
		system("@echo off");
		system(ch);
	}
	return 0;
}
