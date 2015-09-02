#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
#define MIU 0.8
#define SIGAMA 0.05
using namespace std;
int bre;
ofstream myout("C:\\Users\\Administrator\\Desktop\\ans.txt");
struct Person
{
    int num;
    int firstExam;
    int antherExam;
    int lastExam;
    int fb;
    int fe;
    int ab;
    int ae;
    int lb;
    int le;
    bool firstFinished;
    bool antherFinished;
    bool lastFinished;
    Person()
    {
        num=0;
        firstExam=0;
        antherExam=0;
        lastExam=0;
        firstFinished=false;
        antherFinished=false;
        lastFinished=false;
        fb=-120;
        fe=-120;
        ab=-120;
        ae=-120;
        lb=-120;
        le=-120;
    }
};

template <class T>
bool STL_MinHeap_Compare(T &a,T &b);

template <class T>
class STL_MinHeap
{
private:
    vector<T> data;
public:
    friend bool STL_MinHeap_Compare <T> (T &a,T &b);
    int Length()
    {
        return data.size();
    }
    bool IsEmpty()
    {
        return data.size()==0;
    }
    void Push(T &x)
    {
        data.push_back(x);
        push_heap(data.begin(),data.end(),STL_MinHeap_Compare<T>);
    }
    T Front()
    {
        return *data.begin();
    }
    T Pop()
    {
        T temp=Front();
        pop_heap(data.begin(),data.end(),STL_MinHeap_Compare<T>);
        data.pop_back();
        return temp;
    }
};


template <class T>
bool STL_MinHeap_Compare(T &a,T &b)
{
    if (a<b) return false;
    else return true;
}

struct Record
{
    int num;
    int finishTime;
    int room;
    int exam;
};
bool operator <(Record a,Record b)
{
    if (a.finishTime<b.finishTime) return true;
    else return false;
}



int examRest[6];
int RoomRest[3];
int CurrentExam[3];
int CurrentExamCount[3];
int ExamList[3][5];
int ExamListLength[3];
int CurrentTime;
int BeginTime[6]={-1,-1,-1,-1,-1,-1};
int EndTime[6]={-1,-1,-1,-1,-1,-1};
vector<Person> List;
vector<Person> Wait;
STL_MinHeap<Record> H;

void inite()
{
    while (!List.empty()) List.pop_back();
    for (int i=0; i<11; i++)
    {
        Person temp;
        temp.num=i;
        temp.firstExam=1;
        temp.antherExam=2;
        temp.lastExam=3;
        temp.antherFinished=false;
        temp.antherFinished=false;
        temp.lastFinished=false;
        List.push_back(temp);
    }
    for (int i=11; i<42; i++)
    {
        Person temp;
        temp.num=i;
        temp.firstExam=1;
        temp.antherExam=2;
        temp.lastExam=4;
        temp.antherFinished=false;
        temp.antherFinished=false;
        temp.lastFinished=false;
        List.push_back(temp);
    }
    for (int i=42; i<49; i++)
    {
        Person temp;
        temp.num=i;
        temp.firstExam=1;
        temp.antherExam=2;
        temp.lastExam=5;
        temp.antherFinished=false;
        temp.antherFinished=false;
        temp.lastFinished=false;
        List.push_back(temp);
    }
    for (int i=49; i<52; i++)
    {
        Person temp;
        temp.num=i;
        temp.firstExam=1;
        temp.antherExam=3;
        temp.lastExam=5;
        temp.antherFinished=false;
        temp.antherFinished=false;
        temp.lastFinished=false;
        List.push_back(temp);
    }
    for (int i=52; i<79; i++)
    {
        Person temp;
        temp.num=i;
        temp.firstExam=1;
        temp.antherExam=4;
        temp.lastExam=5;
        temp.antherFinished=false;
        temp.antherFinished=false;
        temp.lastFinished=false;
        List.push_back(temp);
    }
    examRest[1]=79;
    examRest[2]=49;
    examRest[3]=14;
    examRest[4]=58;
    examRest[5]=37;
    RoomRest[1]=24;
    RoomRest[2]=32;
    while (!Wait.empty()) Wait.pop_back();
    for (unsigned i=0; i<List.size(); i++)
    {
        Wait.push_back(List[i]);
    }
    srand(time(0));
    random_shuffle(Wait.begin(),Wait.end());
}

void Solve()
{
    //srand(41);
    cout<<"begin"<<endl;

    ExamList[1][0]=4;
    ExamList[1][1]=5;
    ExamList[1][2]=3;
    ExamList[2][0]=1;
    ExamList[2][1]=2;
    ExamListLength[1]=3;
    ExamListLength[2]=2;

    inite();
    CurrentExamCount[1]=0;
    CurrentExamCount[2]=0;
    CurrentExam[1]=ExamList[1][0];
    CurrentExam[2]=ExamList[2][0];
    CurrentTime=0;

    while (true)
    {
        if (CurrentExam[1]<0&&CurrentExam[2]<0)
        {
            cout<<"break 2"<<endl;
            break;
        }
        for (int k=1; k<=2; k++)
        {
            if (CurrentExam[k]<0) continue;
            if (RoomRest[k]!=0)
            {
                for (vector<Person>::iterator i=Wait.begin(); i!=Wait.end(); i++)
                {
                    Person temp=*i;
                    if ((temp.firstFinished==false&&temp.firstExam==CurrentExam[k])||(temp.antherFinished==false&&temp.antherExam==CurrentExam[k])||(temp.lastFinished==false&&temp.lastExam==CurrentExam[k]))
                    {
                        if (temp.firstFinished==false&&temp.firstExam==CurrentExam[k])
                        {
                            Record r;
                            r.num=temp.num;
                            r.room=k;
                            r.exam=CurrentExam[k];
                            if (BeginTime[r.exam]==-1) BeginTime[r.exam]=CurrentTime;
                            do
                            {
                                double mm;
                                do
                                {
                                    double u1=rand()/(1.0+RAND_MAX);
                                    double u2=rand()/(1.0+RAND_MAX);
                                    mm=MIU+SIGAMA*sqrt(-2.0*log(u1))*cos(2*3.1415926536*u2);
                                }while (mm<=0||mm>=1);
                                if (CurrentExam[k]==1) r.finishTime=CurrentTime+45*mm;
                                else r.finishTime=CurrentTime+30*mm;
                            }while (r.finishTime==CurrentTime);
                            List[(*i).num].fe=r.finishTime;
                            H.Push(r);
                            examRest[CurrentExam[k]]--;
                            printf("put in is: %d  while the finishtime is %d and the room is %d exam %d room rest:%d\n",r.num,r.finishTime,r.room,r.exam,RoomRest[k]);
                            if (examRest[CurrentExam[k]]==0)
                            {
                                CurrentExamCount[k]++;
                                if (CurrentExamCount[k]>=ExamListLength[k]) CurrentExam[k]=-110;
                                else
                                {
                                    CurrentExam[k]=ExamList[k][CurrentExamCount[k]];
                                }
                            }
                            RoomRest[k]--;
                            List[(*i).num].firstFinished=true;
                            List[(*i).num].fb=CurrentTime;
                            vector<Person>::iterator j=Wait.erase(i);
                            j--;
                            i=j;
                            if (RoomRest[k]==0) break;
                        }
                        else if (temp.antherFinished==false&&temp.antherExam==CurrentExam[k])
                        {
                            Record r;
                            r.num=temp.num;
                            r.room=k;
                            r.exam=CurrentExam[k];
                            if (BeginTime[r.exam]==-1) BeginTime[r.exam]=CurrentTime;
                           do
                            {
                                double mm;
                                do
                                {
                                    double u1=rand()/(1.0+RAND_MAX);
                                    double u2=rand()/(1.0+RAND_MAX);
                                    mm=MIU+SIGAMA*sqrt(-2.0*log(u1))*cos(2*3.1415926536*u2);
                                }while (mm<=0||mm>=1);
                                if (CurrentExam[k]==1) r.finishTime=CurrentTime+45*mm;
                                else r.finishTime=CurrentTime+30*mm;
                            }while (r.finishTime==CurrentTime);
                            List[(*i).num].ae=r.finishTime;
                            H.Push(r);
                            examRest[CurrentExam[k]]--;
                            printf("put in is: %d  while the finishtime is %d and the room is %d exam %d room rest:%d\n",r.num,r.finishTime,r.room,r.exam,RoomRest[k]);
                            if (examRest[CurrentExam[k]]==0)
                            {
                                CurrentExamCount[k]++;
                                if (CurrentExamCount[k]>=ExamListLength[k]) CurrentExam[k]=-110;
                                else
                                {
                                    CurrentExam[k]=ExamList[k][CurrentExamCount[k]];
                                }
                            }
                            RoomRest[k]--;
                            List[(*i).num].antherFinished=true;
                            List[(*i).num].ab=CurrentTime;
                            vector<Person>::iterator j=Wait.erase(i);
                            j--;
                            i=j;
                            if (RoomRest[k]==0) break;
                        }
                        else if (temp.lastFinished==false&&temp.lastExam==CurrentExam[k])
                        {
                            Record r;
                            r.num=temp.num;
                            r.room=k;
                            r.exam=CurrentExam[k];
                            if (BeginTime[r.exam]==-1) BeginTime[r.exam]=CurrentTime;
                            do
                            {
                                double mm;
                                do
                                {
                                    double u1=rand()/(1.0+RAND_MAX);
                                    double u2=rand()/(1.0+RAND_MAX);
                                    mm=MIU+SIGAMA*sqrt(-2.0*log(u1))*cos(2*3.1415926536*u2);
                                }while (mm<=0||mm>=1);
                                if (CurrentExam[k]==1) r.finishTime=CurrentTime+45*mm;
                                else r.finishTime=CurrentTime+30*mm;
                            }while (r.finishTime==CurrentTime);
                            List[(*i).num].le=r.finishTime;
                            H.Push(r);
                            examRest[CurrentExam[k]]--;
                            printf("put in is: %d  while the finishtime is %d and the room is %d exam %d room rest:%d\n",r.num,r.finishTime,r.room,r.exam,RoomRest[k]);
                            if (examRest[CurrentExam[k]]==0)
                            {
                                CurrentExamCount[k]++;
                                if (CurrentExamCount[k]>=ExamListLength[k]) CurrentExam[k]=-110;
                                else
                                {
                                    CurrentExam[k]=ExamList[k][CurrentExamCount[k]];
                                }
                            }
                            RoomRest[k]--;
                            List[(*i).num].lastFinished=true;
                            List[(*i).num].lb=CurrentTime;
                            vector<Person>::iterator j=Wait.erase(i);
                            j--;
                            i=j;
                            if (RoomRest[k]==0) break;
                        }
                    }
                }
            }
        }
        if (H.IsEmpty())
        {
            cout<<"break 1"<<endl;
            break;
        }
        CurrentTime=H.Front().finishTime;
        //printf("CurrentTime is %d\n",CurrentTime);
        do
        {
            Record r=H.Pop();
            int id=r.num;
            RoomRest[r.room]++;
            Person p;
            printf(" record :%d  finishtime is %d and room %d exam %d current room rest %d %d\n",r.num,r.finishTime,r.room,r.exam,RoomRest[1],RoomRest[2]);///////////
            if (EndTime[r.exam]<0||EndTime[r.exam]<r.finishTime) EndTime[r.exam]=r.finishTime;
            if (List[id].firstFinished&&List[id].antherFinished&&List[id].lastFinished) continue;
            else
            {
                Wait.push_back(List[id]);
            }
        }
        while ((H.Front().finishTime==CurrentTime)&&!H.IsEmpty());
       // printf("examRest:%d %d %d %d %d  currentexam :%d %d\n ",examRest[1],examRest[2],examRest[3],examRest[4],examRest[5],CurrentExam[1],CurrentExam[2]);
        cin>>bre;
    }
    cout<<"tax 3"<<endl;
    while (!H.IsEmpty())
    {
        Record rr=H.Pop();
        if (EndTime[rr.exam]<0||EndTime[rr.exam]<rr.finishTime) EndTime[rr.exam]=rr.finishTime;
        cout<<rr.finishTime<<' ';
    }
    cout<<endl;
    for (int i=1;i<=5;i++)
        printf("第%d题的开始时间为：%d 结束时间为：%d\n",i,BeginTime[i],EndTime[i]);
}

int main()
{
    Solve();
    for (int i=0;i<79;i++)
    {
        myout<<i<<' '<<List[i].fb<<' '<<List[i].fe<<' '<<List[i].ab<<' '<<List[i].ae<<' '<<List[i].lb<<' '<<List[i].le<<endl;
    }
    myout.close();
    return 0;
}
