#include <iostream>

using namespace std;
int theMap[4][4]={0};
int bre;



template <class T>
class MyStack
{
private:
    T *top;
    int last;
    int maxSize;
    void _reSize ()
    {
        int sz=2*maxSize;
        T *temp=new T[sz];
        for (int i=0;i<=last;i++) temp[i]=top[i];
        maxSize=sz;
        delete []top;
        top=temp;
    }
public:
    ~MyStack (){delete []top;}
    MyStack()
    {
        top=new T[100];
        last=-1;
        maxSize=100;
    }
    void Push (T x)
    {
        if (last+1==maxSize) _reSize();
        top[++last]=x;
    }
    T  Pop()
    {
        last--;
        return top[last+1];
    }
    bool IsEmpty()
    {
        return last==-1;
    }

};

bool UpCan(int x,int y)
{
    if ((x-1)<0||theMap[x-1][y]==0) return false;
    int temp=x;
    while (temp-1>=0&&theMap[temp-1][y]!=0)
    {
        temp--;
    }
    if (temp-1<0) return false;
    if (theMap[temp][y]==-2) return false;
    temp--;
    if (temp-1>=0&&theMap[temp-1][y]==-1) return false;
    if (y-1>=0&&theMap[temp][y-1]==-1) return false;
    if (y+1<=3&&theMap[temp][y+1]==-1) return false;
    if (temp+1<=3&&theMap[temp+1][y]==-1) return false;
    return true;
}

bool DownCan(int x,int y)
{
    if ((x+1)>3||theMap[x+1][y]==0) return false;
    int temp=x;
    while (temp+1<=3&&theMap[temp+1][y]!=0)
    {
        temp++;
    }
    if (temp+1>3) return false;
    if (theMap[temp][y]==-2) return false;
    temp++;
    if (temp-1>=0&&theMap[temp-1][y]==-1) return false;
    if (y-1>=0&&theMap[temp][y-1]==-1) return false;
    if (y+1<=3&&theMap[temp][y+1]==-1) return false;
    if (temp+1<=3&&theMap[temp+1][y]==-1) return false;
    return true;
}

bool LeftCan(int x,int y)
{
    if ((y-1)<0||theMap[x][y-1]==0) return false;
    int temp=y;
    while (temp-1>=0&&theMap[x][temp-1]!=0)
    {
        temp--;
    }
    if (temp-1<0) return false;
    if (theMap[x][temp]==-2) return false;
    temp--;
    if (temp-1>=0&&theMap[x][temp-1]==-1) {return false;}
    if (x-1>=0&&theMap[x-1][temp]==-1) {return false;}
    if (x+1<=3&&theMap[x+1][temp]==-1) {return false;}
    if (temp+1<=3&&theMap[x][temp+1]==-1) {return false;}
    return true;
}


bool RightCan(int x,int y)
{
    if ((y+1)>3||theMap[x][y+1]==0) return false;
    int temp=y;
    while (temp+1<=3&&theMap[x][temp+1]!=0)
    {
        temp++;
    }
    if (temp+1>3) return false;
    if (theMap[x][temp]==-2) return false;
    temp++;
    if (temp-1>=0&&theMap[x][temp-1]==-1) {return false;}
    if (x-1>=0&&theMap[x-1][temp]==-1) {return false;}
    if (x+1<=3&&theMap[x+1][temp]==-1) {return false;}
    if (temp+1<=3&&theMap[x][temp+1]==-1) {return false;}
    return true;
}

int main()
{
    int minStep=-1;
    char c[5];
    int rX=0;
    int rY=0;
    for (int i=0;i<4;i++)
    {
        cin>>c;
        for (int j=0;j<4;j++)
        {
            if (c[j]=='G'||c[j]=='B'||c[j]=='R')
            {
                if (c[j]=='G') theMap[i][j]=1;
                else if (c[j]=='B') theMap[i][j]=-1;
                else
                {
                    rX=i;
                    rY=j;
                }
            }
        }
    }

    MyStack<int> xP;
    MyStack<int> yP;
    MyStack<int> state;
    int sta=0;
    MyStack<int> countStore;
    int stepCount=0;
    while (true)
    {
      if (rX==0&&rY==0)
      {
          if (minStep==-1|| minStep>stepCount)   minStep=stepCount;
          goto lab1;
      }

      if (UpCan(rX,rY))
      {
          theMap[rX][rY]=-2;
          xP.Push(rX);
          yP.Push(rY);
          while (theMap[rX][rY]!=0) rX--;
          state.Push(0);
          countStore.Push(stepCount);
          stepCount++;
          continue;
      }
      if (LeftCan(rX,rY))
      {
          theMap[rX][rY]=-2;
          xP.Push(rX);
          yP.Push(rY);

          while (theMap[rX][rY]!=0) rY--;
          state.Push(1);
          countStore.Push(stepCount);
          stepCount++;
          continue;
      }
      if (RightCan(rX,rY))
      {
          theMap[rX][rY]=-2;
          xP.Push(rX);
          yP.Push(rY);
          while (theMap[rX][rY]!=0) rY++;

          state.Push(2);
          countStore.Push(stepCount);
          stepCount++;
          continue;
      }
      if (DownCan(rX,rY))
      {
          theMap[rX][rY]=-2;
          xP.Push(rX);
          yP.Push(rY);
          while (theMap[rX][rY]!=0) rX++;

          state.Push(3);
          countStore.Push(stepCount);
          stepCount++;
          continue;
      }
      lab1:if (xP.IsEmpty()) break;
      while (!xP.IsEmpty())
      {
            rX=xP.Pop();
            rY=yP.Pop();
            sta=state.Pop();
            stepCount=countStore.Pop();
            theMap[rX][rY]=0;

            if (sta<=0&&LeftCan(rX,rY))
            {

                theMap[rX][rY]=-2;
                xP.Push(rX);
                yP.Push(rY);
                while (theMap[rX][rY]!=0) rY--;

                state.Push(1);
                countStore.Push(stepCount);
                stepCount++;
                break;
            }
            if (sta<=1&&RightCan(rX,rY))
            {

                theMap[rX][rY]=-2;
                xP.Push(rX);
                yP.Push(rY);
                while (theMap[rX][rY]!=0) rY--;

                state.Push(2);
                countStore.Push(stepCount);
                stepCount++;
                break;
            }
            if (sta<=2&&DownCan(rX,rY))
            {

                theMap[rX][rY]=-2;
                xP.Push(rX);
                yP.Push(rY);
                while (theMap[rX][rY]!=0) rX++;

                state.Push(3);
                countStore.Push(stepCount);
                stepCount++;
                break;
            }
      }
      if (xP.IsEmpty()) break;
    }
    cout<<minStep;
    return 0;
}
