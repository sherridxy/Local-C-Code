#include <stdio.h>
#define ZHEN_XING int
#define FU_DIAN_XING double
#define ZHU_HAN_SHU main(void)
#define ZI_FU_XING char
#define RU_GUO(C,S1,S2) do{if (C){ S1 } else { S2 } }while(0)
#define XUN_HUAN(C,S) RU_GUO(C,do{S}while(C);,;)
#define SHU_CHU(X) printf("%s",X)
#define DU_QU(X) scanf("%d",&X)
#define FAN_HUI(X) return X 
ZHEN_XING ZHU_HAN_SHU
{
	ZHEN_XING r=2;
	ZHEN_XING i=10;XUN_HUAN(i--,ZHEN_XING x;DU_QU(x);RU_GUO(x==r,SHU_CHU("right");break;,RU_GUO(x<r,SHU_CHU("low\n");,SHU_CHU("high\n"););););
	FAN_HUI(0);
}
