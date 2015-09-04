#include <iostream>
#include <fstream>
#include <cstdio>
using namespace std;
int main(int argc,char *argv[])
{
	if (argc==2)
	{
		ofstream myout("C:\\resultOutput.txt");
		myout<<"the argument you have input is:   ";
		myout<<argv[1]<<endl;
		cout<<"结果已生成至本地C盘 resultOutput文件中"<<endl;
	}
	else cout<<" 您未输入相应参数"<<endl;
	system("pause");
	return 0;
}