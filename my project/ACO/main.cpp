#include <iostream>
#include <math.h>
#include <time.h>

const double ALPHA=1.0; //�������ӣ���Ϣ�ص���Ҫ�̶�
const double BETA=2.0;   //�������ӣ����м�������Ҫ�̶�
const double ROU=0.5; //��Ϣ�ز�������

const int N_ANT_COUNT=34; //��������
const int N_IT_COUNT=500000; //��������
const int N_CITY_COUNT=48; //��������

const double DBQ=100.0; //�ܵ���Ϣ��
const double DB_MAX=10e9; //һ����־����10��9�η�

double g_Trial[N_CITY_COUNT][N_CITY_COUNT]; //�������м���Ϣ�أ����ǻ�����Ϣ��
double g_Distance[N_CITY_COUNT][N_CITY_COUNT]; //�������м����

//eil51.tsp������������
double x_Ary[N_CITY_COUNT]=
{
   6734,2233,5530,401,3082,7608,7573,7265,6898,1112,5468,5989,4706,4612,6347,6107,7611,7462,7732,5900,4483,6101,5199,1633,4307,675,7555,7541,3177,7352,7545,3245,6426,
4608,23,7248,7762,7392,3484,6271,4985,1916,7280,7509,10,6807,5185,3023
};

double y_Ary[N_CITY_COUNT]=
{
   1453,10,1424,841,1644,4458,3716,1268,1885,2049,2606,2873,2674,2035,2683,669,5184,3590,4723,3561,3369,1110,2182,2809,2322,1006,4819,3981,756,4506,2801,3305,3173,1198
,2216,3779,4595,2244,2829,2135,140,1569,4899,3239,2676,2993,3258,1942
};

//����ָ����Χ�ڵ��������
int rnd(int nLow,int nUpper)
{
    return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);
}

//����ָ����Χ�ڵ����������
double rnd(double dbLow,double dbUpper)
{
    double dbTemp=rand()/((double)RAND_MAX+1.0);
    return dbLow+dbTemp*(dbUpper-dbLow);
}

//���ظ�������������ȡ����ĸ�����
double ROUND(double dbA)
{
    return (double)((int)(dbA+0.5));
}


//����������
class CAnt
{
public:
    CAnt(void);
    ~CAnt(void);

public:

    int m_nPath[N_CITY_COUNT]; //�����ߵ�·��
    double m_dbPathLength; //�����߹���·������

    int m_nAllowedCity[N_CITY_COUNT]; //ûȥ���ĳ���
    int m_nCurCityNo; //��ǰ���ڳ��б��
    int m_nMovedCityCount; //�Ѿ�ȥ���ĳ�������

public:

    int ChooseNextCity(); //ѡ����һ������
    void Init(); //��ʼ��
    void Move(); //�����ڳ��м��ƶ�
    void Search(); //����·��
    void CalPathLength(); //���������߹���·������

};

//���캯��
CAnt::CAnt(void)
{
}

//��������
CAnt::~CAnt(void)
{
}


//��ʼ����������������ǰ����
void CAnt::Init()
{

    for (int i=0;i<N_CITY_COUNT;i++)
    {
        m_nAllowedCity[i]=1; //����ȫ������Ϊû��ȥ��
        m_nPath[i]=0; //�����ߵ�·��ȫ������Ϊ0
    }

    //�����߹���·����������Ϊ0
    m_dbPathLength=0.0;

    //���ѡ��һ����������
    m_nCurCityNo=rnd(0,N_CITY_COUNT);

    //�ѳ������б�����·��������
    m_nPath[0]=m_nCurCityNo;

    //��ʶ��������Ϊ�Ѿ�ȥ����
    m_nAllowedCity[m_nCurCityNo]=0;

    //�Ѿ�ȥ���ĳ�����������Ϊ1
    m_nMovedCityCount=1;

}

//ѡ����һ������
//����ֵ Ϊ���б��
int CAnt::ChooseNextCity()
{

    int nSelectedCity=-1; //���ؽ��������ʱ��������Ϊ-1

    //==============================================================================
    //���㵱ǰ���к�ûȥ���ĳ���֮�����Ϣ���ܺ�

    double dbTotal=0.0;
    double prob[N_CITY_COUNT]; //����������б�ѡ�еĸ���

    for (int i=0;i<N_CITY_COUNT;i++)
    {
        if (m_nAllowedCity[i] == 1) //����ûȥ��
        {
            prob[i]=pow(g_Trial[m_nCurCityNo][i],ALPHA)*pow(1.0/g_Distance[m_nCurCityNo][i],BETA); //�ó��к͵�ǰ���м����Ϣ��
            dbTotal=dbTotal+prob[i]; //�ۼ���Ϣ�أ��õ��ܺ�
        }
        else //�������ȥ���ˣ����䱻ѡ�еĸ���ֵΪ0
        {
            prob[i]=0.0;
        }
    }

    //==============================================================================
    //��������ѡ��
    double dbTemp=0.0;
    if (dbTotal > 0.0) //�ܵ���Ϣ��ֵ����0
    {
        dbTemp=rnd(0.0,dbTotal); //ȡһ�������

        for (int i=0;i<N_CITY_COUNT;i++)
        {
            if (m_nAllowedCity[i] == 1) //����ûȥ��
            {
                dbTemp=dbTemp-prob[i]; //��������൱��ת�����̣����������ѡ����Ϥ����ϸ����һ��
                if (dbTemp < 0.0) //����ֹͣת�������³��б�ţ�ֱ������ѭ��
                      {
                    nSelectedCity=i;
                    break;
                }
            }
        }
    }

    //==============================================================================
    //������м����Ϣ�طǳ�С ( С����double�ܹ���ʾ����С�����ֻ�ҪС )
    //��ô���ڸ�����������ԭ���������ĸ����ܺͿ���Ϊ0
    //����־�������������û�г��б�ѡ�����
    //��������������Ͱѵ�һ��ûȥ���ĳ�����Ϊ���ؽ��

    //���⻰���տ�ʼ����ʱ��������δ����������Һܳ�ʱ�䣬�벻ͨΪ��Ҫ����δ��룬�����Ÿ������
    if (nSelectedCity == -1)
    {
        for (int i=0;i<N_CITY_COUNT;i++)
        {
            if (m_nAllowedCity[i] == 1) //����ûȥ��
            {
                nSelectedCity=i;
                break;
            }
        }
    }

    //==============================================================================
    //���ؽ�������ǳ��еı��
    return nSelectedCity;
}
//�����ڳ��м��ƶ�
void CAnt::Move()
{
    int nCityNo=ChooseNextCity(); //ѡ����һ������

    m_nPath[m_nMovedCityCount]=nCityNo; //���������ߵ�·��
    m_nAllowedCity[nCityNo]=0;//������������ó��Ѿ�ȥ����
    m_nCurCityNo=nCityNo; //�ı䵱ǰ���ڳ���Ϊѡ��ĳ���
    m_nMovedCityCount++; //�Ѿ�ȥ���ĳ���������1
}

//���Ͻ�������һ��
void CAnt::Search()
{
    Init(); //��������ǰ���ȳ�ʼ��

    //�������ȥ���ĳ�������С�ڳ����������ͼ����ƶ�
    while (m_nMovedCityCount < N_CITY_COUNT)
    {
        Move();
    }

    //�������������߹���·������
    CalPathLength();
}


//���������߹���·������
void CAnt::CalPathLength()
{

    m_dbPathLength=0.0; //�Ȱ�·��������0
    int m=0;
    int n=0;

    for (int i=1;i<N_CITY_COUNT;i++)
    {
        m=m_nPath[i];
        n=m_nPath[i-1];
        m_dbPathLength=m_dbPathLength+g_Distance[m][n];
    }

    //���ϴ������з��س������еľ���
    n=m_nPath[0];
    m_dbPathLength=m_dbPathLength+g_Distance[m][n];

}


//tsp��
class CTsp
{
public:
    CTsp(void);
    ~CTsp(void);

public:
    CAnt m_cAntAry[N_ANT_COUNT]; //��������
    CAnt m_cBestAnt; //����һ�����ϱ����������������������е����Ž��
                                        //�����ϲ�����������ֻ�������������Ž��

public:

    //��ʼ������
    void InitData();

    //��ʼ����
    void Search();

    //���»�����Ϣ��
    void UpdateTrial();


};


//���캯��
CTsp::CTsp(void)
{
}

CTsp::~CTsp(void)
{
}


//��ʼ������
void CTsp::InitData()
{

    //�Ȱ��������ϵ�·���������ó�һ���ܴ��ֵ
    m_cBestAnt.m_dbPathLength=DB_MAX;

    //�����������м����
    double dbTemp=0.0;
    for (int i=0;i<N_CITY_COUNT;i++)
    {
        for (int j=0;j<N_CITY_COUNT;j++)
        {
            dbTemp=(x_Ary[i]-x_Ary[j])*(x_Ary[i]-x_Ary[j])+(y_Ary[i]-y_Ary[j])*(y_Ary[i]-y_Ary[j]);
            dbTemp=pow(dbTemp,0.5);
            g_Distance[i][j]=ROUND(dbTemp);
        }
    }

    //��ʼ��������Ϣ�أ��Ȱѳ��м����Ϣ�����ó�һ��
    //�������ó�1.0�����óɶ��ٶԽ��Ӱ�첻��̫�󣬶��㷨�����ٶ���ЩӰ��
    for (int i=0;i<N_CITY_COUNT;i++)
    {
        for (int j=0;j<N_CITY_COUNT;j++)
        {
            g_Trial[i][j]=1.0;
        }
    }

}

//���»�����Ϣ��
void CTsp::UpdateTrial()
{
    //��ʱ���飬�����ֻ�������������м������µ���Ϣ��
    double dbTempAry[N_CITY_COUNT][N_CITY_COUNT];
    memset(dbTempAry,0,sizeof(dbTempAry)); //��ȫ������Ϊ0

    //���������ӵ���Ϣ��,���浽��ʱ������
    int m=0;
    int n=0;
    for (int i=0;i<N_ANT_COUNT;i++) //����ÿֻ�������µ���Ϣ��
    {
            for (int j=1;j<N_CITY_COUNT;j++)
            {
                m=m_cAntAry[i].m_nPath[j];
                n=m_cAntAry[i].m_nPath[j-1];
                dbTempAry[n][m]=dbTempAry[n][m]+DBQ/m_cAntAry[i].m_dbPathLength;
                dbTempAry[m][n]=dbTempAry[n][m];
            }

            //�����кͿ�ʼ����֮�����Ϣ��
            n=m_cAntAry[i].m_nPath[0];
            dbTempAry[n][m]=dbTempAry[n][m]+DBQ/m_cAntAry[i].m_dbPathLength;
            dbTempAry[m][n]=dbTempAry[n][m];

    }

    //==================================================================
    //���»�����Ϣ��
    for (int i=0;i<N_CITY_COUNT;i++)
    {
        for (int j=0;j<N_CITY_COUNT;j++)
        {
            g_Trial[i][j]=g_Trial[i][j]*ROU+dbTempAry[i][j]; //���µĻ�����Ϣ�� = �������Ϣ�� + �����µ���Ϣ��
        }
    }

}


void CTsp::Search()
{

    char cBuf[256]; //��ӡ��Ϣ��

    //�ڵ��������ڽ���ѭ��
    for (int i=0;i<N_IT_COUNT;i++)
    {
        //ÿֻ��������һ��
        for (int j=0;j<N_ANT_COUNT;j++)
        {
            m_cAntAry[j].Search();
        }

        //������ѽ��
        for (int j=0;j<N_ANT_COUNT;j++)
        {
            if (m_cAntAry[j].m_dbPathLength < m_cBestAnt.m_dbPathLength)
            {
                m_cBestAnt=m_cAntAry[j];
            }
        }

        //���»�����Ϣ��
        UpdateTrial();

        //���ĿǰΪֹ�ҵ�������·���ĳ���
        sprintf(cBuf,"\n[%d] %.0f",i+1,m_cBestAnt.m_dbPathLength);
        printf(cBuf);
    }

}


int main()
{
    //�õ�ǰʱ����ʼ��������ӣ���ֹÿ�����еĽ������ͬ
    time_t tm;
    time(&tm);
    unsigned int nSeed=(unsigned int)tm;
    srand(nSeed);

    //��ʼ����
    CTsp tsp;

    tsp.InitData(); //��ʼ��
    tsp.Search(); //��ʼ����

    //������
    printf("\nThe best tour is :\n");

    char cBuf[128];
    for (int i=0;i<N_CITY_COUNT;i++)
    {
        sprintf(cBuf,"%02d ",tsp.m_cBestAnt.m_nPath[i]+1);
        if (i % 20 == 0)
        {
            printf("\n");
        }
        printf(cBuf);
    }

    printf("\n\nPress any key to exit!");
    getchar();

    return 0;
}

