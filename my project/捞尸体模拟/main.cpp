#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <vector>
#define ROOM_MAX_FOREACH 60
#define LONGTH_BREATH 300000
int dis[4][ROOM_MAX_FOREACH][ROOM_MAX_FOREACH];
int roomNum[4];
int searchTime[4];
int currentTime=0;
int restTime=LONGTH_BREATH;
int roomRest[4];
bool peopleIn[4][ROOM_MAX_FOREACH];
bool visit[4][ROOM_MAX_FOREACH];
int currentSite;

int bre;

using namespace std;

void Init(void) //未写
{
    /*
    dis;
    roomNum;
    searchTime;
    roomRest;
    peopleIn;
    visit
    */
}
void TestInit()
{
    //srand(time(0));
    ifstream fin("C:\\Users\\Administrator\\Desktop\\data2.txt");
    for (int i=0; i<4; i++) fin>>roomNum[i];
    for (int i=0; i<4; i++) roomRest[i]=roomNum[i];
    for (int i=0; i<4; i++) fin>>searchTime[i];
    for (int k=0; k<4; k++)
    {
        for (int i=0; i<=roomNum[k]; i++)
        {
            for(int j=0; j<=roomNum[k]; j++)
                fin>>dis[k][i][j];
        }
    }
    for(int k=0; k<4; k++)
    {
        for (int i=0; i<=roomNum[k]; i++)
        {
            int r=rand()%3;
            if (r==0) peopleIn[k][i]=1;
            else peopleIn[k][i]=0;
        }
    }
   /* for(int k=0; k<4; k++)
    {
        for (int i=0; i<=roomNum[k]; i++)
        {
            visit[k][i]=0;
            fin>>peopleIn[k][i];
        }
    }*/
    fin.close();



    for (int i=0; i<4; i++) cout<<roomNum[i]<<' ';
    cout<<endl;
    for (int i=0; i<4; i++) cout<<roomRest[i]<<' ';
    cout<<endl;
    for (int i=0; i<4; i++) cout<<searchTime[i]<<' ';
    cout<<endl;
    for (int k=0; k<4; k++)
    {
        for (int i=0; i<=roomNum[k]; i++)
        {
            for(int j=0; j<=roomNum[k]; j++)
            {
                cout<<dis[k][i][j]<<' ';
            }
            cout<<endl;
        }
        cout<<endl;
    }
    for(int k=0; k<4; k++)
    {
        for (int i=0; i<=roomNum[k]; i++)
        {
            visit[k][i]=0;
            cout<<peopleIn[k][i]<<' ';
        }
        cout<<endl;
    }
    system("pause");

}

struct Record
{
    int floor;
    int room;
    int time;
    Record(int f,int r,int t)
    {
        floor=f;
        room=r;
        time=t;
    }
};

vector<Record> V;

int main()
{
    TestInit();
    currentTime=0;
    restTime=LONGTH_BREATH;
    for (int i=0; i<4; i++)
    {
        currentSite=0;
        while (true)
        {
            //printf("循环初始： currenttime:%d currentsite:%d ,resttime: %d\n",currentTime,currentSite,restTime);
            //cin>>bre;
            if (roomRest[i]==0)
            {
                currentSite=0;
                restTime=LONGTH_BREATH;
                currentTime+=dis[i][currentSite][0];
                break;
            }
            int mmin=-1;
            int tempSite;
            for (int k=1; k<=roomNum[i]; k++)
            {
                if (currentSite==k) continue;
                if ((mmin<0&&visit[i][k]==false)||(dis[i][currentSite][k]<mmin&&visit[i][k]==false))
                {
                    mmin=dis[i][currentSite][k];
                    tempSite=k;
                }
            }
            if (restTime-dis[i][currentSite][tempSite]-searchTime[i]-dis[i][tempSite][0]>=0)
            {
                visit[i][tempSite]=true;
                currentTime=currentTime+dis[i][currentSite][tempSite]+searchTime[i];
                restTime=restTime-dis[i][currentSite][tempSite]-searchTime[i];
                roomRest[i]--;
                currentSite=tempSite;
                //printf("找到房间后 currenttime:%d currentsite:%d ,resttime: %d\n",currentTime,currentSite,restTime);
                //cin>>bre;
                if (peopleIn[i][currentSite]==true)
                {
                    int storeSite=currentSite;
                    currentTime+=dis[i][currentSite][0];
                    //printf("找到人后 currenttime:%d currentsite:%d ,resttime: %d\n",currentTime,currentSite,restTime);
                    //cin>>bre;
                    restTime=LONGTH_BREATH;
                    currentSite=0;
                    Record temp(i,storeSite,currentTime);
                    V.push_back(temp);
                    continue;
                }
                else continue;
            }
            else
            {
                currentTime+=dis[i][currentSite][0];
                //printf("呼吸不够时： currenttime:%d currentsite:%d ,resttime: %d\n",currentTime,currentSite,restTime);
                //cin>>bre;
                currentSite=0;
                restTime=LONGTH_BREATH;
                continue;
            }
        }
    }
    for (unsigned i=0; i<V.size(); i++)
    {
        printf("floor :%d,  room:%d  time:%d  \n",V[i].floor,V[i].room,V[i].time);
    }
    return 0;
}
