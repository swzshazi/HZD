/* File Description   
*  FileName: BlkReCls.c -- 闭锁重合闸逻辑        
*  Fuction: 
*       功能：闭锁重合闸逻辑处理
*       输入：GOOSE闭重、手合开入、手跳开入、TJR开入、TJF开入、GOOSE TJR、另一套闭重等
*       输出：GOOSE闭重SOE、本套闭重、另一套闭重等
*  apply: 智能化开关
*  author: ZYB 
*  data:  20200528
*/

#include <stdlib.h>
#include "hzplatform.h"
#include "BlkReClsLog.h"


void BlkReClsLog_task( BlkReClsLog *dp);

int initBlkReClsLog( BlkReClsLog *dp);

#pragma DATA_SECTION(BlkReClsLog_stru,".rtm_data")
BlkReClsLog BlkReClsLog_stru;

BlkReClsLog *newBlkReClsLog(Component *parent, const char *name)
{
	Uint16 i=0;
	char tp_str[150];
	BlkReClsLog *dp;
	
	dp = &BlkReClsLog_stru;
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "BlkReCls";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent =  (int (*)(void *))initBlkReClsLog;

	registerComponent( (Component*)dp);

	registerVarIn( (Component*)dp, (void**)&(dp->pElecTest), "pElecTest", T_BIT, LEVEL1 );		 // 带电检修状态
	registerVarIn( (Component*)dp, (void**)&(dp->pTest), "pTest", T_BIT, LEVEL1 );		         // 装置检修状态


	for ( i=0; i<BlkReCls_NUM; i++ )
	{
		sprintf(tp_str, "pBlkReCLS%d_GSE__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBlkReCLS_GSE[i]), tp_str, T_BIT, LEVEL1 );      // 闭锁重合闸值

		sprintf(tp_str, "pBlkReCLS%d_GSE__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBlkReCLS_GSE_ok[i]), tp_str, T_UINT8, LEVEL1 ); // 闭锁重合闸品质
	}
	
	registerVarIn( (Component*)dp, (void**)&(dp->pCBYF), "pCBYF", T_BIT, LEVEL1 );		  // 遥分断路器
	registerVarIn( (Component*)dp, (void**)&(dp->pCBYH), "pCBYH", T_BIT, LEVEL1 );	      // 遥合断路器
	
	registerVarIn( (Component*)dp, (void**)&(dp->pSH_OPT), "pSH_OPT", T_BIT, LEVEL1 );    // 手合开入
	registerVarIn( (Component*)dp, (void**)&(dp->pST_OPT), "pST_OPT", T_BIT, LEVEL1 );    // 手跳开入

	registerVarIn( (Component*)dp, (void**)&(dp->pTJR_OPT), "pTJR_OPT", T_BIT, LEVEL1 );  // TJR开入
	registerVarIn( (Component*)dp, (void**)&(dp->pTJF_OPT), "pTJF_OPT", T_BIT, LEVEL1 );  // TJF开入
	
	registerVarIn( (Component*)dp, (void**)&(dp->pGS_TJR), "pGS_TJR", T_BIT, LEVEL1 );    // GOOSE TJR
	
	registerVarIn( (Component*)dp, (void**)&(dp->pTestBlkReCLS_GSE), "pTestBlkReCLS_GSE__AB", T_BIT, LEVEL1 );    // 测试仪GOOSE闭重
	registerVarIn( (Component*)dp, (void**)&(dp->pTestBlkReCLS_GSE_ok), "pTestBlkReCLS_GSE__AB_ok", T_BIT, LEVEL1 );   
	
	registerVarIn( (Component*)dp, (void**)&(dp->pBSysBlkReCls_GSE), "pBSysBlkReCls_GSE__AB", T_BIT, LEVEL1 );    // 另一套闭重输入
	registerVarIn( (Component*)dp, (void**)&(dp->pBSysBlkReCls_GSE_ok), "pBSysBlkReCls_GSE__AB_ok", T_UINT8, LEVEL1 );	
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for ( i=0; i<BlkReCls_NUM; i++ )
	{
		sprintf(tp_str, "BlkReCLS%d_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BlkReCLS_E[i]), tp_str, T_SOE, LEVEL1 );
	}
	registerVarOut( (Component*)dp, (void*)&(dp->BSysBlkReCls_E), "BSysBlkReCls_E", T_SOE, LEVEL1 ); // 另一套闭重输入
	
	registerVarOut( (Component*)dp, (void*)&(dp->TestBlkReCLS_E), "TestBlkReCLS_E", T_SOE, LEVEL1 ); // 测试仪GOOSE闭锁重合闸

	registerVarOut( (Component*)dp, (void*)&(dp->BlkReCls_Out), "BlkReCls_Out", T_BIT, LEVEL1 );	// 闭锁本套重合闸
	registerVarOut( (Component*)dp, (void*)&(dp->BlkReCls_Bsys), "BlkReCls_Bsys", T_BIT, LEVEL1 );	// 闭锁另一套重合闸
	
	return dp;
}

INIT_CODE
int initBlkReClsLog(BlkReClsLog *dp)
{
	Uint16 i=0;

	for ( i=0; i<BlkReCls_NUM; i++ )
	{
		initSOE_fun( &(dp->BlkReCLS_E[i]), 0 );
	}

	initSOE_fun( &(dp->TestBlkReCLS_E), 0 );
	initSOE_fun( &(dp->BSysBlkReCls_E), 0 );

	setTask( 2, BlkReClsLog_task, dp);

	return 0;
}



#pragma CODE_SECTION(BlkReClsLog_task,".rtm_code")
void BlkReClsLog_task(BlkReClsLog *dp)
{
	Uint16 i=0;

////////////////////////////GOOSE接收SOE报文生成////////////////////////////////////////////////////
	
	//测试仪GOOSE闭锁重合闸
	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestBlkReCLS_GSE, dp->pTestBlkReCLS_GSE_ok, &(dp->TestBlkReCLS_E) );

	//GOOSE闭锁重合闸
	for ( i=0; i<BlkReCls_NUM; i++ )
	{
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pBlkReCLS_GSE[i], dp->pBlkReCLS_GSE_ok[i], &(dp->BlkReCLS_E[i]) );
	}

	//双套交互数据
	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pBSysBlkReCls_GSE, dp->pBSysBlkReCls_GSE_ok, &(dp->BSysBlkReCls_E) );

//////////////////////////GOOSE报文品质处理/////////////////////////////////////////////////////////

	if ( *(dp->pTest) == 1 )
	{
		//检修态：检修一致认可测试仪命令
		dp->TestBlkReCLS  = GSE_Test_Q( dp->pTestBlkReCLS_GSE, dp->pTestBlkReCLS_GSE_ok, *(dp->pTest) );
	}
	else
	{
		//运行态：测试仪命令清0
		dp->TestBlkReCLS = 0;
	}

	dp->BlkReCLS_Op = dp->TestBlkReCLS;
	
	//过程层命令处理
	if ( *(dp->pElecTest) == 1 )
	{
		//主控带电检修：过程层命令清0
		for ( i=0; i<BlkReCls_NUM; i++ )
		{
			dp->GsBlkReCLS[i]  = 0;
		}

		dp->SH_OPT = 0;
		dp->ST_OPT = 0;
		dp->BSysBlkReCls = 0;
	}
	else
	{
		//主控运行态或停电检修态：检修一致更新，检修不一致清0
		for ( i=0; i<BlkReCls_NUM; i++ )
		{
			dp->GsBlkReCLS[i] = GSE_Bool_Q( dp->pBlkReCLS_GSE[i], dp->pBlkReCLS_GSE_ok[i], *(dp->pTest) );
			dp->BlkReCLS_Op |= dp->GsBlkReCLS[i];
		}

		dp->BSysBlkReCls = GSE_Bool_Q( dp->pBSysBlkReCls_GSE, dp->pBSysBlkReCls_GSE_ok, *(dp->pTest) );
		dp->SH_OPT = *(dp->pSH_OPT);
		dp->ST_OPT = *(dp->pST_OPT);
	}

	if(dp->PWRUP_CNT > lev2_5S) 
	{
		dp->PWRUP = 0;
	}
	else
	{
		dp->PWRUP_CNT++;
		dp->PWRUP = 1;
	}

///////////////////////////动作及点灯信号///////////////////////////////////////////////////////////
	
	// 闭锁另一套重合闸
	dp->BlkReCls_Bsys =  *(dp->pCBYF) | *(dp->pCBYH) | (dp->SH_OPT) | (dp->ST_OPT) | *(dp->pGS_TJR)
					   | *(dp->pTJR_OPT) | *(dp->pTJF_OPT) | dp->BlkReCLS_Op;
	
	// 闭锁本套重合闸
	dp->BlkReCls_Out = dp->BlkReCls_Bsys | dp->BSysBlkReCls | dp->PWRUP;
}
