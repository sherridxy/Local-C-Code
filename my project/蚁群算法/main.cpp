#include <iostream>
#include <cmath>
#include <ctime>
#define ANT_AMOUNT 50
#define CITY_AMOUNT 48
#define GENERATION_TIMES 500000
#define FIRST_PHER 0.1 /////////////////////////////////////////////////////////////////////////
int bre;
using namespace std;
int MinRoute=-1;
int MinTour[CITY_AMOUNT+1]={0};
int distant[CITY_AMOUNT][CITY_AMOUNT]={0};
double pheromone[CITY_AMOUNT][CITY_AMOUNT]={0};
double choice_info[CITY_AMOUNT][CITY_AMOUNT]={0};
double selection_pro[CITY_AMOUNT]={0};
int x_pos[CITY_AMOUNT]={6734,2233,5530,401,3082,7608,7573,7265,6898,1112,5468,5989,4706,4612,6347,6107,7611,7462,7732,5900,4483,6101,5199,1633,4307,675,7555,7541,3177,7352,7545,3245,6426,
4608,23,7248,7762,7392,3484,6271,4985,1916,7280,7509,10,6807,5185,3023};
int y_pos[CITY_AMOUNT]={1453,10,1424,841,1644,4458,3716,1268,1885,2049,2606,2873,2674,2035,2683,669,5184,3590,4723,3561,3369,1110,2182,2809,2322,1006,4819,3981,756,4506,2801,3305,3173,1198
,2216,3779,4595,2244,2829,2135,140,1569,4899,3239,2676,2993,3258,1942};
struct Ant
{
    int tour_length;
    int tour[CITY_AMOUNT+1];
    bool visited[CITY_AMOUNT];
    Ant ()
    {
        for (int i=0;i<CITY_AMOUNT;i++) visited[i]=false;
    }
};

Ant a[ANT_AMOUNT];

int HowFar(int m,int n)
{
    return (int) sqrt((x_pos[m]-x_pos[n])*(x_pos[m]-x_pos[n])/10.0+(y_pos[m]-y_pos[n])*(y_pos[m]-y_pos[n])/10.0);
}
void Prepare()
{
    for (int i=0;i<CITY_AMOUNT;i++)
        for (int j=i+1;j<CITY_AMOUNT;j++) distant[i][j]=distant[j][i]=HowFar(i,j);
    for (int i=0;i<CITY_AMOUNT;i++)
        for (int j=0;j<CITY_AMOUNT;j++) pheromone[i][j]=FIRST_PHER;
    for (int i=0;i<CITY_AMOUNT;i++)
        for (int j=i+1;j<CITY_AMOUNT;j++) choice_info[i][j]=choice_info[j][i]=pheromone[i][j]*1.0/(distant[i][j]*distant[i][j]);

}

void ASDecisionRule(int k,int step)
{
    int current=a[k].tour[step-1];
    double sum_pro=0.0;
    for (int i=0;i<CITY_AMOUNT;i++)
    {
        if (a[k].visited[i]==true) selection_pro[i]=0;
        else
        {
            selection_pro[i]=choice_info[current][i];
            sum_pro+=selection_pro[i];
        }
    }
    double r=0;
    do
    {
        r=rand()/(RAND_MAX+1.0)*sum_pro;
    } while (r<=0);
    int j=0;
    double p=selection_pro[j];
    if (p>r&&a[k].visited[0]==true) cout<<"fuckfuckfuckfuckfuckfuckfuckfuckfuckfuckfuckfuck"<<endl;
    while (p<r)
    {
        j++;
        p+=selection_pro[j];
    }
    a[k].tour[step]=j;
    if (a[k].visited[j]==true)
    {
        cout<<"wrong "<<j<<endl;
        for (int i=0;i<=step;i++) cout<<a[k].tour[i]<<' ';
        cout<<endl;
        cout<<r<<endl;
        cout<<selection_pro[0]<<endl;
        cout<<a[k].visited[0]<<endl;
        cin>>bre;
    }
    a[k].visited[j]=true;
}

int ComputeLengh(int k)
{
    int temp=0;
    for (int i=0;i<CITY_AMOUNT;i++) temp+=distant[a[k].tour[i]][a[k].tour[i+1]];
    return temp;
}

void Move()
{
    for (int i=0;i<ANT_AMOUNT;i++)
        for (int j=0;j<CITY_AMOUNT;j++) a[i].visited[j]=false;//所有蚂蚁的访问记忆清除
    int step=0;
    for (int i=0;i<ANT_AMOUNT;i++)
    {
        int r=rand()%CITY_AMOUNT;
        a[i].tour[0]=r;
        a[i].visited[r]=true;
    }
    while (step<CITY_AMOUNT-1)
    {
        step++;
        for (int i=0;i<ANT_AMOUNT;i++) ASDecisionRule(i,step);
    }
    for (int i=0;i<ANT_AMOUNT;i++)
    {
        a[i].tour[CITY_AMOUNT]=a[i].tour[0];
        a[i].tour_length=ComputeLengh(i);
    }
    for (int i=0;i<ANT_AMOUNT;i++)
        if (MinRoute<0||a[i].tour_length<MinRoute)
        {
            MinRoute=a[i].tour_length;
            for (int k=0;k<CITY_AMOUNT+1;k++) MinTour[k]=a[i].tour[k];
        }

}

void PheUpdate()
{
    for (int i=0;i<CITY_AMOUNT;i++)
        for (int j=i+1;j<CITY_AMOUNT;j++)
        {
            pheromone[i][j]=pheromone[i][j]/2.0;
            pheromone[j][i]=pheromone[i][j];
        }
    for (int i=0;i<ANT_AMOUNT;i++)
    {
        double delta=1.0/a[i].tour_length;
        for (int k=0;k<CITY_AMOUNT;k++)
        {
            int j=a[i].tour[k];
            int l=a[i].tour[k+1];
            pheromone[j][l]+=delta;
            pheromone[l][j]=pheromone[j][l];
        }
    }
    for (int i=0;i<CITY_AMOUNT;i++)
        for (int j=i+1;j<CITY_AMOUNT;j++) choice_info[i][j]=choice_info[j][i]=pheromone[i][j]*1.0/(distant[i][j]*distant[i][j]);


}

int main()
{
    Prepare();
    for (int i=0;i<CITY_AMOUNT;i++)
    {
        for (int j=0;j<CITY_AMOUNT;j++) cout<<distant[i][j]<<' ';
        cout<<endl;
        cout<<"line "<<i;
        cout<<endl;
    }
    srand(time(0));
    for (int temp=0;temp<GENERATION_TIMES;temp++)
    {
        Move();
        PheUpdate();
        cout<<"["<<temp+1<<"]      "<<MinRoute<<endl;
    }
    cout<<"shortest is "<<MinRoute<<endl;
    for (int k=0;k<CITY_AMOUNT+1;k++) cout<<MinTour[k]<<' ';
    cout<<endl;
    return 0;
}
