#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
using namespace std;
int main(int argc,char *argv[])
{
	if (argc==2)
	{
		ofstream myout("C:\\Users\\Administrator\\Desktop\\resultOutput.txt");
		myout<<"the argument you have input is:   ";
		for (int i=0;argv[1][i]!='\0';i++)
		{
			if (argv[1][i]=='\\') myout<<'\\';
			myout<<argv[1][i];
		}
		cout<<"结果已生成至 resultOutput文件中"<<endl;
	}
	else cout<<" 您未输入相应参数"<<endl;
	system("pause");
	return 0;
}