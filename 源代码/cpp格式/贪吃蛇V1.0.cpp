#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
using namespace std;
int food_x,food_y;
int map[33][24]={0};

struct snake //蛇的结构体，x表示屏幕横坐标，y表示屏幕纵坐标，before表示前一段蛇
{
	int x;
	int y;
	snake *before;
};

void snakeMove(snake *body)//移动蛇的函数，参数为蛇尾指针，从蛇尾开始复制前一段蛇的坐标（蛇头保持不变）
{
	while (1)
	{
		if (body->before ==NULL) return;
		body->x =body->before->x;
		body->y =body->before->y;
		body =body->before;
	}
}

void HideCursor()//隐藏光标函数
{
	CONSOLE_CURSOR_INFO cursor_info={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
}

void gotoxy (int x,int y)//光标移动函数
{
	COORD coord;
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void drawMap(void)//绘制地图函数，绘制出横轴方向31格（横轴坐标变化2为一格），纵轴方向22格的地图
{
	int i;
	for (i=0;i<24;i++) map[0][i]=1;
	for (i=0;i<24;i++) map[32][i]=1;
	for (i=0;i<33;i++) map[i][0]=1;
	for (i=0;i<33;i++) map[i][23]=1; // 在地图中标记边框

	cout<<"┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━┓";
	cout<<"┃                                                              ┃  贪吃蛇    ┃";
	cout<<"┃                                                              ┃  控制台    ┃";
	cout<<"┃                                                              ┃  小游戏    ┃";
	cout<<"┃                                                              ┃━━━━━━┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃━━━━━━┃";
	cout<<"┃                                                              ┃ W    ↑    ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃ S    ↓    ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃ A    ←    ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┃                                                              ┃ D    →    ┃";
	cout<<"┃                                                              ┃            ┃";
	cout<<"┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━┛";
	cout<<"  V1.0                                                             制作人：丁磊 ";
	gotoxy(0,0);
}

void setFood(void)//放置食物函数，在地图中没有绘制蛇的地方随机放置
{
	while (1)
	{
		int ran=(rand()%682)+1;
		food_y=(ran-1)/31+1;
		food_x=ran-(food_y-1)*31;//此刻的food_x,food_y为地图中坐标（非屏幕坐标）
		if (map[food_x][food_y]==0)
		{
			food_x=2*food_x;//坐标换为屏幕坐标
			gotoxy(food_x,food_y);
			cout<<'*';
			return;
		}

	}

}

char opposite (char direction) //相反方向函数，输出相反的方向
{
	if (direction==UP) return DOWN;
	if (direction==DOWN) return UP;
	if (direction==LEFT) return RIGHT;
	if (direction==RIGHT) return LEFT;
}

int main()
{
	int head_x=2*10,head_y=15,tail_x=2*8,tail_y=15,food=0; //初始化头尾屏幕坐标
    char direction=RIGHT,lastDirection=RIGHT;//初始化方向
	char name[20];
	snake *S_head,*S_tail;//定义蛇的头尾指针
	HideCursor();//隐藏光标
	drawMap();//绘制地图
	srand(time(0));//根据系统时间设置随机数种子
	getch();
	map[10][15]=1;
	map[9][15]=1;
	map[8][15]=1;//地图中确定蛇的位置
	S_head=new snake;
	S_tail=new snake;
	S_tail->x =tail_x;
	S_tail->y =tail_y;
	S_tail->before =new snake;
	S_tail->before->x =2*9;
	S_tail->before->y =tail_y;
	S_tail->before->before =S_head;
	S_head->x =head_x;
	S_head->y =head_y;
	S_head->before =NULL;//初始化三段蛇的结构体
	gotoxy(tail_x,tail_y);
	cout<<"███";//绘制蛇的初始状态
    while (1)
	{
		if (food==0)    //食物为0时，放置食物
		{
			setFood();
			food=1;
		}
		if (kbhit()!=0)            //键盘缓冲区存在按键时，将其读出
		{
			direction=getch();
		}
		if (direction==opposite(lastDirection)) direction=lastDirection;
		switch (direction)
		{
		  case UP:
			  {
				  if (S_head->x ==food_x && S_head->y-1==food_y)
				  {
					  S_head->before=new snake;
					  *(S_head->before)=*S_head;
					  S_head=S_head->before;
					  S_head->before=NULL;
					  S_head->y+=-1;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"█";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  food=0;
					  lastDirection=direction;
					  break;
				  }
				  gotoxy(S_tail->x,S_tail->y);
				  cout<<" ";
				  map[S_tail->x/2][S_tail->y]=0;
				  snakeMove(S_tail);
				  S_head->y+=-1;
				  gotoxy(S_head->x,S_head->y);
				  cout<<"█";
				  if (map[S_head->x/2][S_head->y]==1) goto over;
				  map[S_head->x/2][S_head->y]=1;
				  lastDirection=direction;
				  break;
			  }
		  case DOWN:
			  {
				  if (S_head->x ==food_x && S_head->y+1==food_y)
				  {
					  S_head->before=new snake;
					  *(S_head->before)=*S_head;
					  S_head=S_head->before;
					  S_head->before=NULL;
					  S_head->y+=1;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"█";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  food=0;
					  lastDirection=direction;
					  break;
				  }
				  gotoxy(S_tail->x,S_tail->y);
				  cout<<" ";
				  map[S_tail->x/2][S_tail->y]=0;
				  snakeMove(S_tail);
				  S_head->y+=1;
				  gotoxy(S_head->x,S_head->y);
				  cout<<"█";
				  if (map[S_head->x/2][S_head->y]==1) goto over;
				  map[S_head->x/2][S_head->y]=1;
				  lastDirection=direction;
				  break;
			  }
		  case LEFT:
			  {
				  if (S_head->x-2 ==food_x && S_head->y==food_y)
				  {
					  S_head->before=new snake;
					  *(S_head->before)=*S_head;
					  S_head=S_head->before;
					  S_head->before=NULL;
					  S_head->x+=-2;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"█";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  food=0;
					  lastDirection=direction;
					  break;
				  }
				  gotoxy(S_tail->x,S_tail->y);
				  cout<<" ";
				  map[S_tail->x/2][S_tail->y]=0;
				  snakeMove(S_tail);
				  S_head->x+=-2;
				  gotoxy(S_head->x,S_head->y);
				  cout<<"█";
				  if (map[S_head->x/2][S_head->y]==1) goto over;
				  map[S_head->x/2][S_head->y]=1;
				  lastDirection=direction;
				  break;
			  }
		  case RIGHT:
			  {
				  if (S_head->x+2 ==food_x && S_head->y==food_y)
				  {
					  S_head->before=new snake;
					  *(S_head->before)=*S_head;
					  S_head=S_head->before;
					  S_head->before=NULL;
					  S_head->x+=2;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"█";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  food=0;
					  lastDirection=direction;
					  break;
				  }
				  gotoxy(S_tail->x,S_tail->y);
				  cout<<" ";
				  map[S_tail->x/2][S_tail->y]=0;
				  snakeMove(S_tail);
				  S_head->x+=2;
				  gotoxy(S_head->x,S_head->y);
				  cout<<"█";
				  if (map[S_head->x/2][S_head->y]==1) goto over;
				  map[S_head->x/2][S_head->y]=1;
				  lastDirection=direction;
				  break;
			  }
		  default :
			  {
				  direction=lastDirection;
				  if (direction==UP)
				  {
					  if (S_head->x ==food_x && S_head->y-1==food_y)
					  {
						  S_head->before=new snake;
						  *(S_head->before)=*S_head;
						  S_head=S_head->before;
						  S_head->before=NULL;
						  S_head->y+=-1;
						  gotoxy(S_head->x,S_head->y);
						  cout<<"█";
						  if (map[S_head->x/2][S_head->y]==1) goto over;
						  map[S_head->x/2][S_head->y]=1;
						  food=0;
						  break;
					  }

					  gotoxy(S_tail->x,S_tail->y);
					  cout<<" ";
					  map[S_tail->x/2][S_tail->y]=0;
					  snakeMove(S_tail);
					  S_head->y+=-1;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"█";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  break;
				  }
				  if (direction==DOWN)
				  {
					  if (S_head->x ==food_x && S_head->y+1==food_y)
					  {
						  S_head->before=new snake;
						  *(S_head->before)=*S_head;
						  S_head=S_head->before;
						  S_head->before=NULL;
						  S_head->y+=1;
						  gotoxy(S_head->x,S_head->y);
						  cout<<"█";
						  if (map[S_head->x/2][S_head->y]==1) goto over;
						  map[S_head->x/2][S_head->y]=1;
						  food=0;
						  break;
					  }
					  gotoxy(S_tail->x,S_tail->y);
					  cout<<" ";
					  map[S_tail->x/2][S_tail->y]=0;
					  snakeMove(S_tail);
					  S_head->y+=1;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"█";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  break;
				  }
				  if (direction==LEFT)
				  {
					  if (S_head->x-2 ==food_x && S_head->y==food_y)
					  {
						  S_head->before=new snake;
						  *(S_head->before)=*S_head;
						  S_head=S_head->before;
						  S_head->before=NULL;
						  S_head->x+=-2;
						  gotoxy(S_head->x,S_head->y);
						  cout<<"█";
						  if (map[S_head->x/2][S_head->y]==1) goto over;
						  map[S_head->x/2][S_head->y]=1;
						  food=0;
						  break;
					  }
					  gotoxy(S_tail->x,S_tail->y);
					  cout<<" ";
					  map[S_tail->x/2][S_tail->y]=0;
					  snakeMove(S_tail);
					  S_head->x+=-2;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"█";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  break;
				  }
				  if (direction==RIGHT)
				  {
					  if (S_head->x+2 ==food_x && S_head->y==food_y)
					  {
						  S_head->before=new snake;
						  *(S_head->before)=*S_head;
						  S_head=S_head->before;
						  S_head->before=NULL;
						  S_head->x+=2;
						  gotoxy(S_head->x,S_head->y);
						  cout<<"█";
						  if (map[S_head->x/2][S_head->y]==1) goto over;
						  map[S_head->x/2][S_head->y]=1;
						  food=0;
						  break;
					  }
					  gotoxy(S_tail->x,S_tail->y);
					  cout<<" ";
					  map[S_tail->x/2][S_tail->y]=0;
					  snakeMove(S_tail);
					  S_head->x+=2;
					  gotoxy(S_head->x,S_head->y);
					  cout<<"█";
					  if (map[S_head->x/2][S_head->y]==1) goto over;
					  map[S_head->x/2][S_head->y]=1;
					  break;
				  }
			  }
		}
		Sleep(200);
	}
over:gotoxy(33*2,10);
	cout<<"游戏结束";
	Sleep(3000);
	getch();
	return 0;
}
