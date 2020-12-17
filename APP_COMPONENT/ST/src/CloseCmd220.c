/* File Description   
*  FileName: CloseCmd220.c -- 分相断路器合闸命令处理        
*  Fuction: 
*       功能：处理合闸命令并将控制命令转发断路器
*       输入：保护重合闸命令、手合开入、测控合命令、控制及出口压板
*       输出：合闸命令SOE、合闸命令反馈、合闸结果输出等
*  apply: 智能化开关
*  author: ZYB 
*  data:  20200528
*/

#include <stdlib.h>
#include "hzplatform.h"
#include "CloseCmd220.h"


void CloseCmd220_task( CloseCmd220 *dp);

int initCloseCmd220( CloseCmd220 *dp);

#pragma DATA_SECTION(CloseCmd220_stru,".rtm_data")
CloseCmd220 CloseCmd220_stru;

CloseCmd220 *newCloseCmd220(Component *parent, const char *name)
{
	Uint16 i=0;
	char tp_str[150];
	CloseCmd220 *dp;
	
	dp = &CloseCmd220_stru;
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "Close";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent =  (int (*)(void *))initCloseCmd220;

	registerComponent( (Component*)dp);

	registerVarIn( (Component*)dp, (void**)&(dp->pElecTest), "pElecTest", T_BIT, LEVEL1 );		 // 带电检修
	registerVarIn( (Component*)dp, (void**)&(dp->pTest), "pTest", T_BIT, LEVEL1 );		         // 装置检修状态

	registerVarIn( (Component*)dp, (void**)&(dp->pProBd), "pProBd", T_BIT, LEVEL1 );		     // 保护出口压板
	registerVarIn( (Component*)dp, (void**)&(dp->pConBd), "pConBd", T_BIT, LEVEL1 );		     // 控制出口压板
	registerVarIn( (Component*)dp, (void**)&(dp->pLocalConBd), "pLocalBd", T_BIT, LEVEL1 );		 // 就地控制把手

	for ( i=0; i<ReClose_NUM; i++ )
	{
		sprintf(tp_str, "pRECLS%d_GSE__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pRECLS_GSE[i]), tp_str, T_BIT, LEVEL1 );         // 保护重合闸值

		sprintf(tp_str, "pRECLS%d_GSE__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pRECLS_GSE_ok[i]), tp_str, T_UINT8, LEVEL1 );    // 保护重合闸品质
	}

	for ( i=0; i<YK_Close_NUM; i++ )
	{
		sprintf(tp_str, "pCBYH%d_GSE__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pCBYH_GSE[i]), tp_str, T_BIT, LEVEL1 );         // 遥合断路器值

		sprintf(tp_str, "pCBYH%d_GSE__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pCBYH_GSE_ok[i]), tp_str, T_UINT8, LEVEL1 );    // 遥合断路器品质
	}
	
	registerVarIn( (Component*)dp, (void**)&(dp->pBSysSH_GSE), "pBSysSH_GSE__AB", T_BIT, LEVEL1 );		 // B套手合输入
	registerVarIn( (Component*)dp, (void**)&(dp->pBSysSH_GSE_ok), "pBSysSH_GSE__AB_ok", T_UINT8, LEVEL1 );		
	
	registerVarIn( (Component*)dp, (void**)&(dp->pSH_OPT), "pSH_OPT", T_BIT, LEVEL1 );		    	// 手合开入
	registerVarIn( (Component*)dp, (void**)&(dp->pSTJ), "pSTJ", T_BIT, LEVEL1 );		    	    // STJ输入
	
	registerVarIn( (Component*)dp, (void**)&(dp->pTestCLS_GSE), "pTestCLS_GSE__AB", T_BIT, LEVEL1 );    // 测试仪保护重合闸值
	registerVarIn( (Component*)dp, (void**)&(dp->pTestCLS_GSE_ok), "pTestCLS_GSE__AB_ok", T_UINT8, LEVEL1 );	

	registerVarIn( (Component*)dp, (void**)&(dp->pTestCBYH_GSE), "pTestCBYH_GSE__AB", T_BIT, LEVEL1 );    // 测试仪遥合断路器值
	registerVarIn( (Component*)dp, (void**)&(dp->pTestCBYH_GSE_ok), "pTestCBYH_GSE__AB_ok", T_UINT8, LEVEL1 );	
	
	registerVarIn( (Component*)dp, (void**)&(dp->pHZ_ELSE), "pHZ_ELSE", T_BIT, LEVEL1 );				//另一CPU的HZ输出连接到此，进行双CPU的比对
	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	for ( i=0; i<ReClose_NUM; i++ )
	{
		sprintf(tp_str, "RECLS%d_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->RECLS_E[i]), tp_str, T_SOE, LEVEL2 );
	}

	for ( i=0; i<YK_Close_NUM; i++ )
	{
		sprintf(tp_str, "CBYH%d_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->CBYH_E[i]), tp_str, T_SOE, LEVEL2 );
	}

	registerVarOut( (Component*)dp, (void*)&(dp->BSysSH_E), "BSysSH_E", T_SOE, LEVEL2 );	//另一套手合输入
	registerVarOut( (Component*)dp, (void*)&(dp->TestCLS_E), "TestCLS_E", T_SOE, LEVEL2 );	//测试仪保护重合闸
	
	registerVarOut( (Component*)dp, (void*)&(dp->RECLS_GSE), "RECLS_GSE", T_BIT, LEVEL2 );	//GOOSE保护重合闸命令反馈
	registerVarOut( (Component*)dp, (void*)&(dp->CBYH_GSE), "CBYH_GSE", T_BIT, LEVEL2 );	//GOOSE测控合闸命令反馈
	
	registerVarOut( (Component*)dp, (void*)&(dp->SH_Else), "SH_Else", T_BIT, LEVEL2 );	    //手合输出-给另一套
	registerVarOut( (Component*)dp, (void*)&(dp->SHJ), "SHJ", T_BIT, LEVEL2 );	            //SHJ信号
	
	registerVarOut( (Component*)dp, (void*)&(dp->SH_Flag), "SH_Flag", T_BIT, LEVEL2 );	    //手合标志
	registerVarOut( (Component*)dp, (void*)&(dp->ST_Flag), "ST_Flag", T_BIT, LEVEL2 );	    //手跳标志
	registerVarOut( (Component*)dp, (void*)&(dp->KKJ), "KKJ", T_BIT, LEVEL2 );	            //KKJ合后

	registerVarOut( (Component*)dp, (void*)&(dp->RECLS_Op), "RECLS_Op", T_BIT, LEVEL2 );	//保护重合闸处理结果
	registerVarOut( (Component*)dp, (void*)&(dp->RECLS_Out), "RECLS_Out", T_BIT, LEVEL2 );	//保护重合闸输出
	registerVarOut( (Component*)dp, (void*)&(dp->CBYH_Op), "CBYH_Op", T_BIT, LEVEL2 );	    //测控合闸处理结果
	registerVarOut( (Component*)dp, (void*)&(dp->CBYH_Out), "CBYH_Out", T_BIT, LEVEL2 );	//测控合闸输出
	registerVarOut( (Component*)dp, (void*)&(dp->SH_OPT), "SH_OPT", T_BIT, LEVEL2 );	    //手合处理结果
	registerVarOut( (Component*)dp, (void*)&(dp->SH_Out), "SH_Out", T_BIT, LEVEL2 );	    //手合处理输出
	registerVarOut( (Component*)dp, (void*)&(dp->HZ_Out), "HZ_Out", T_BIT, LEVEL2 );	    //合闸输出-合断路器模块
	registerVarOut( (Component*)dp, (void*)&(dp->HZ_LONGTIME), "HZ_LONGTIME", T_BIT, LEVEL2 );

	//registerVarOut( (Component*)dp, (void*)&(dp->QD), "QD", T_BIT, LEVEL2 );
	
	registerVarOut( (Component*)dp, (void*)&(dp->CMP_ERR), "CMP_ERR", T_BIT, LEVEL2 );				//比较出错输出	
	registerVarOut( (Component*)dp, (void*)&(dp->check_err), "check_err", T_BIT, LEVEL2 );

	return dp;
}


void CloseCmd220_check_task(CloseCmd220 *dp)
{
	if(dp->check_err == 0)
	{
		dp->check_err = check_set_pointer((Uint32)(&dp->start),(Uint32)(&dp->checksum));
	}
}


INIT_CODE
int initCloseCmd220(CloseCmd220 *dp)
{
	Uint16 i=0;

	for ( i=0; i<ReClose_NUM; i++ )
	{
		initSOE_fun( &(dp->RECLS_E[i]), 0 );
	}

	for ( i=0; i<YK_Close_NUM; i++ )
	{
		initSOE_fun( &(dp->CBYH_E[i]), 0 );
	}

	initSOE_fun( &(dp->BSysSH_E), 0 );
	initSOE_fun( &(dp->TestCLS_E), 0 );
	
	dp->HZ_LONGTIME = 0;
	dp->HZ_Out = 0;
	dp->CMP_CNT = 0;
	dp->CMP_ERR = 0;

	dp->SHJ_New = 0;
	dp->SHJ_Old = 0;
	dp->SHJ_CNT = 0;
	
	dp->status1 = 0;
	dp->time_save1 = 0;
	dp->checksum = 0;
	dp->check_err = 0;
	
	init_check_set_pointer( (Uint32)(&dp->start), (Uint32)(&dp->checksum) );
	
	setTask( 2, CloseCmd220_task, dp);
	setTask( 4, CloseCmd220_check_task, dp);

	return 0;
}



#pragma CODE_SECTION(CloseCmd220_task,".rtm_code")
void CloseCmd220_task(CloseCmd220 *dp)
{
	Uint16 i=0;

////////////////////////////GOOSE接收SOE报文生成////////////////////////////////////////////////////
	
	//测试仪合闸命令
	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestCLS_GSE, dp->pTestCLS_GSE_ok, &(dp->TestCLS_E) );
	dp->RECLS_GSE = dp->TestCLS_E.value.c_value;

	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestCBYH_GSE, dp->pTestCBYH_GSE_ok, &(dp->TestCBYH_E) );
	dp->CBYH_GSE = dp->TestCBYH_E.value.c_value;

	//保护合闸命令
	for ( i=0; i<ReClose_NUM; i++ )
	{
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pRECLS_GSE[i], dp->pRECLS_GSE_ok[i], &(dp->RECLS_E[i]) );
		dp->RECLS_GSE |= dp->RECLS_E[i].value.c_value;
	}

	//遥控合闸命令
	for ( i=0; i<YK_Close_NUM; i++ )
	{
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pCBYH_GSE[i], dp->pCBYH_GSE_ok[i], &(dp->CBYH_E[i]) );
		dp->CBYH_GSE |= dp->CBYH_E[i].value.c_value;
	}

	//双套交互数据
	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pBSysSH_GSE, dp->pBSysSH_GSE_ok, &(dp->BSysSH_E) );

//////////////////////////GOOSE报文品质处理/////////////////////////////////////////////////////////

	if ( *(dp->pTest) == 1 )
	{
		//检修态：检修一致认可测试仪命令
		dp->TestCLS  = GSE_Test_Q( dp->pTestCLS_GSE, dp->pTestCLS_GSE_ok, *(dp->pTest) );
		dp->TestCBYH = GSE_Test_Q( dp->pTestCBYH_GSE, dp->pTestCBYH_GSE_ok, *(dp->pTest) );
	}
	else
	{
		//运行态：测试仪命令清0
		dp->TestCLS  = 0;
		dp->TestCBYH = 0;
	}

	dp->RECLS_Op = dp->TestCLS;
	dp->CBYH_Op  = dp->TestCBYH;
	
	//过程层命令处理
	if ( *(dp->pElecTest) == 1 )
	{
		//主控带电检修：过程层命令清0
		for ( i=0; i<ReClose_NUM; i++ )
		{
			dp->RECLS[i]  = 0;
		}

		for ( i=0; i<YK_Close_NUM; i++ )
		{
			dp->CBYH[i] = 0;
		}

		dp->SH_OPT = 0;
		dp->BSysSH = 0;
	}
	else
	{
		//主控运行态或停电检修态：检修一致更新，检修不一致清0
		for ( i=0; i<ReClose_NUM; i++ )
		{
			dp->RECLS[i] = GSE_Bool_Q( dp->pRECLS_GSE[i], dp->pRECLS_GSE_ok[i], *(dp->pTest) );
			dp->RECLS_Op |= dp->RECLS[i];
		}

		for ( i=0; i<YK_Close_NUM; i++ )
		{
			dp->CBYH[i] = GSE_Bool_Q( dp->pCBYH_GSE[i], dp->pCBYH_GSE_ok[i], *(dp->pTest) );
			dp->CBYH_Op |= dp->CBYH[i];
		}

		dp->BSysSH = GSE_Bool_Q( dp->pBSysSH_GSE, dp->pBSysSH_GSE_ok, *(dp->pTest) );
		dp->SH_OPT = *(dp->pSH_OPT);
	}

///////////////////////////动作及点灯信号///////////////////////////////////////////////////////////
	
	dp->RECLS_Out = dp->RECLS_Op;
	//保护出口压板退出，闭锁保护合闸出口
	if ( *(dp->pProBd) == 0 )
	{
		dp->RECLS_Out = 0;
	}

	dp->CBYH_Out = dp->CBYH_Op;
	//控制出口压板退出，闭锁遥合
	if ( *(dp->pConBd) == 0 )
	{
		dp->CBYH_Out = 0;
	}

	dp->SH_Out = dp->SH_OPT;
	//就地把手判别
	if ( *(dp->pLocalConBd) == 0 )
	{
		//就地把手退出, 闭锁手合
		dp->SH_Out = 0;
	}
	else
	{
		//就地把手投入, 闭锁遥控
		dp->CBYH_Out = 0;
	}
	
	//合闸命令输出至断路器模块
	dp->HZ_Out = dp->RECLS_Out | dp->CBYH_Out | dp->SH_Out;

	//合闸命令长时间动作
	dp->HZ_Op = dp->RECLS_Op | dp->CBYH_Op | dp->SH_OPT;
	dp->HZ_LONGTIME = Dlyon(&(dp->status1), &(dp->time_save1), dp->HZ_Op, tick_1000ms);

	//手合输出给另一套
	dp->SH_Else = dp->CBYH_Op | dp->SH_OPT;
	//SHJ更新
	dp->SHJ_New = dp->SH_Else | dp->BSysSH;
    //SH输入时且跳变时，产生1s的高电平信号
	PULSE_TRIG(&(dp->SHJ_New), &(dp->SHJ_Old), &(dp->SHJ_CNT), lev2_1S, &(dp->SHJ), 1);

	//KKJ合后
	if ( dp->SHJ == 1 )
	{
		dp->SH_Flag = 1;
		dp->ST_Flag = 0;
	}	

	if ( *(dp->pSTJ) == 1 )
	{
		dp->ST_Flag = 1;
		dp->SH_Flag = 0;
	}		

	dp->KKJ = dp->SH_Flag;  //ZYB-还需增加掉电不丢失逻辑（变化写KKJ状态，以及初始上读KKJ状态）
//////////////////////////双系统监视比较////////////////////////////////////////////////////////////
#ifndef MAIN_DSP
	two_sys_cmp( dp->HZ_Out, *(dp->pHZ_ELSE), &(dp->CMP_ERR), &(dp->CMP_CNT), lev2_10S );
#endif
//////////////////////////启动出口//////////////////////////////////////////////////////////////////
	//dp->QD = dp->HZ;
////////////////////////出口接点回采////////////////////////////////////////////////////////////////
	//get_relay_stat(dp->HZ, dp->TWJA_OPT, &(dp->HA_RELAY_DZ));
	//get_relay_stat(dp->HZ, dp->TWJB_OPT, &(dp->HB_RELAY_DZ));
	//get_relay_stat(dp->HZ, dp->TWJC_OPT, &(dp->HC_RELAY_DZ));
}
