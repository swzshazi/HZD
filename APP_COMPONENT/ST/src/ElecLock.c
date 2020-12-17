/* File Description   
*  FileName: ElecLock.c -- 智能开关电气联锁逻辑处理元件     
*  Fuction: 
*       功能：获取联锁位置和联锁开入并产生电气联锁结果
*       输入：联锁位置、联锁开入、另一CPU联锁结果
*       输出：电气联锁结果
*  apply: 智能化开关
*  author: ZYB 
*  data:  20200813
*/

#include <stdlib.h>
#include<string.h>
#include "hzplatform.h"
#include "ElecLock.h"
#include "CommFun.h"

void ElecLock_task( ElecLock *dp);

int initElecLock( ElecLock *dp);


ElecLock *newElecLock(Component *parent, const char *name)
{
	Uint8 i;
	char tp_str[150], tp_str2[150];
	
	ElecLock *dp;
	
	dp = (ElecLock *)calloc(1, sizeof(ElecLock));
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "ElecLock";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent = (int (*)(void *))initElecLock;

	registerComponent( (Component*)dp);
	
	for ( i = 0; i < HdElecPosNum; i++ )
	{
		sprintf(tp_str, "pPosDis%d", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pPosDis[i]), tp_str, T_BIT, LEVEL1 );   // 分位 

		sprintf(tp_str, "pPosCls%d", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pPosCls[i]), tp_str, T_BIT, LEVEL1 );   // 合位 
	}

	for ( i = 0; i < HdElecDINum; i++ )
	{
		sprintf(tp_str, "pDI%d", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pDI[i]), tp_str, T_BIT, LEVEL1 );      // 开入 
	}
//////////////////////////////////////////////////////////////////////////////////////////////////////

	for ( i = 0; i < HdElecPosNum; i++ )
	{
		sprintf(tp_str, "PosState%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->PosState[i]), tp_str, T_UINT8, LEVEL2 );	    // 位置状态
	}

	for ( i = 0; i < HdElecDINum; i++ )
	{
		sprintf(tp_str, "DIState%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->DIState[i]), tp_str, T_BIT, LEVEL2 );	      // 开入状态
	}

	registerVarOut( (Component*)dp, (void*)&(dp->ElecUnlock), "ElecUnlock", T_BIT, LEVEL2 );	  // 电气联锁解锁状态

//////////////////////////////////////////////////////////////////////////////////////////////////////	
	// 联锁双位置数目
	registerParameter((Component*)dp,(void*)&(dp->PosSet_Num),  "PosSet_Num min=0 max=16 option=1 default=0", T_UINT8);
	
	// 联锁开入数目
	registerParameter((Component*)dp,(void*)&(dp->DISet_Num),  "DISet_Num min=0 max=16 option=1 default=0", T_UINT8);
	
	// 位置允许操作值
	for ( i = 0; i < HdElecPosNum; i++ )
	{
		sprintf(tp_str, "Pos%dSet_En ", i+1);
		sprintf(tp_str2, "min=0 max=1 list=off_state on_state");
		strcat(tp_str,tp_str2);
		registerParameter((Component*)dp,(void*)&(dp->PosSet_En[i]), tp_str, T_STR_L);
	}
	
	// 开入允许操作值
	for ( i = 0; i < HdElecDINum; i++ )
	{
		sprintf(tp_str, "DI%dSet_En ", i+1);
		sprintf(tp_str2, "min=0 max=1 list=off_state on_state");
		strcat(tp_str,tp_str2);
		registerParameter((Component*)dp,(void*)&(dp->DISet_En[i]), tp_str, T_STR_L);
	}

	return dp;
}

INIT_CODE
int initElecLock(ElecLock *dp)
{
	Uint8 i;

	for ( i=0; i<HdElecPosNum; i++ )
	{
		if ( dp->PosSet_En[i] == 0 )
		{
			dp->PosVal_En[i] = 1;
		}
		else
		{
			dp->PosVal_En[i] = 2;
		}
	}
	 
	setTask( 2, ElecLock_task, dp);

	return 0;
}


#pragma CODE_SECTION(ElecLock_task,".rtm_code")


void ElecLock_task(ElecLock *dp)
{
	Uint8 i;
    
	// 断路器位置处理
	dp->PosUnLock = 1;
	if ( dp->PosSet_Num > 0 )
	{
		for ( i = 0; i < dp->PosSet_Num; i++ )
		{
			dp->PosState[i] = *(dp->pPosDis[i]) + *(dp->pPosCls[i]) >> 1;
			
			if ( dp->PosState[i] != dp->PosVal_En[i] )
			{
				dp->PosUnLock = 0;
				break;
			}
		}
	}
	
	// 开入处理
	dp->DIUnLock = 1;
	if ( dp->DISet_Num > 0 )
	{
		for ( i = 0; i < dp->DISet_Num; i++ )
		{
			if ( *(dp->pDI[i]) != dp->DISet_En[i] )
			{
				dp->DIUnLock = 0;
				break;
			}
		}
	}
}
