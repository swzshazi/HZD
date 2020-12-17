/* File Description   
*  FileName: DzCmdMerge.c -- 刀闸命令合并处理元件        
*  Fuction: 
*       功能：获取刀闸遥控命令、手分手合命令合并处理
*       输入：遥控刀闸命令
*       输出：刀闸遥控命令SOE、刀闸遥控命令反馈、刀闸控制输出等
*  apply: 本体模块
*  author: ZYB 
*  data:  20200811
*/

#include <stdlib.h>
#include "hzplatform.h"
#include "DzCmdMerge.h"
#include "CommFun.h"

void DzCmdMerge_task( DzCmdMerge *dp);

int initDzCmdMerge( DzCmdMerge *dp);


DzCmdMerge *newDzCmdMerge(Component *parent, const char *name)
{
	DzCmdMerge *dp;
	Uint16 i=0;
	char tp_str[150];
	
	dp = (DzCmdMerge *)calloc(1, sizeof(DzCmdMerge));
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "DzCtr";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent = (int (*)(void *))initDzCmdMerge;

	registerComponent( (Component*)dp);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	registerVarIn( (Component*)dp, (void**)&(dp->pElecTest), "pElecTest", T_BIT, LEVEL1 );		 //带电检修
	registerVarIn( (Component*)dp, (void**)&(dp->pTest), "pTest", T_BIT, LEVEL1 );		         //装置检修状态
	
	registerVarIn( (Component*)dp, (void**)&(dp->pAElecTest), "pAElecTest__AB", T_BIT, LEVEL1 );     //A套主控带电检修
	registerVarIn( (Component*)dp, (void**)&(dp->pAElecTest_ok), "pAElecTest__AB_ok", T_UINT8, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->pACutTest), "pACutTest", T_BIT, LEVEL1 );		 //A套主控停电检修
	registerVarIn( (Component*)dp, (void**)&(dp->pACutTest_ok), "pACutTest__AB_ok", T_UINT8, LEVEL1 );

	registerVarIn( (Component*)dp, (void**)&(dp->pBElecTest), "pBElecTest", T_BIT, LEVEL1 );     //B套主控带电检修
	registerVarIn( (Component*)dp, (void**)&(dp->pBElecTest_ok), "pBElecTest__AB_ok", T_UINT8, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->pBCutTest), "pBCutTest", T_BIT, LEVEL1 );		 //B套主控停电检修
	registerVarIn( (Component*)dp, (void**)&(dp->pBCutTest_ok), "pBCutTest__AB_ok", T_UINT8, LEVEL1 );

	registerVarIn( (Component*)dp, (void**)&(dp->pLocalCon), "pLocalCon", T_BIT, LEVEL1 );		 //就地控制投入
	registerVarIn( (Component*)dp, (void**)&(dp->pFarCon), "pFarCon", T_BIT, LEVEL1 );		     //远方控制投入

	for ( i=0; i<YK_DZ_NUM; i++ )
	{
		sprintf(tp_str, "pADZ%dYF__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pADZYF[i]), tp_str, T_BIT, LEVEL1 );        // A套刀闸遥分
		sprintf(tp_str, "pADZ%dYF__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pADZYF_ok[i]), tp_str, T_UINT8, LEVEL1 );  

		sprintf(tp_str, "pADZ%dYH__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pADZYH[i]), tp_str, T_BIT, LEVEL1 );        // A套刀闸遥合
		sprintf(tp_str, "pADZ%dYH__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pADZYH_ok[i]), tp_str, T_UINT8, LEVEL1 );  

		sprintf(tp_str, "pADZ%dBLK__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pADZBLK[i]), tp_str, T_BIT, LEVEL1 );        // A套刀闸解闭锁
		sprintf(tp_str, "pADZ%dBLK__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pADZBLK_ok[i]), tp_str, T_UINT8, LEVEL1 );  

		sprintf(tp_str, "pBDZ%dYF__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBDZYF[i]), tp_str, T_BIT, LEVEL1 );        // B套刀闸遥分
		sprintf(tp_str, "pBDZ%dYF__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBDZYF_ok[i]), tp_str, T_UINT8, LEVEL1 );  

		sprintf(tp_str, "pBDZ%dYH__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBDZYH[i]), tp_str, T_BIT, LEVEL1 );        // B套刀闸遥合
		sprintf(tp_str, "pBDZ%dYH__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBDZYH_ok[i]), tp_str, T_UINT8, LEVEL1 ); 

		sprintf(tp_str, "pBDZ%dBLK__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBDZBLK[i]), tp_str, T_BIT, LEVEL1 );        // B套刀闸解闭锁
		sprintf(tp_str, "pBDZ%dBLK__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBDZBLK_ok[i]), tp_str, T_UINT8, LEVEL1 );  

		sprintf(tp_str, "pTestDZ%dYF__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTestDZYF[i]), tp_str, T_BIT, LEVEL1 );       // 测试仪刀闸遥分
		sprintf(tp_str, "pTestDZ%dYF__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTestDZYF_ok[i]), tp_str, T_UINT8, LEVEL1 );  

		sprintf(tp_str, "pTestDZ%dYH__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTestDZYH[i]), tp_str, T_BIT, LEVEL1 );       // 测试仪刀闸遥合
		sprintf(tp_str, "pTestDZ%dYH__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTestDZYH_ok[i]), tp_str, T_UINT8, LEVEL1 ); 

		sprintf(tp_str, "pTestDZ%dBLK__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTestDZBLK[i]), tp_str, T_BIT, LEVEL1 );       // 测试仪刀闸遥合
		sprintf(tp_str, "pTestDZ%dBLK__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTestDZBLK_ok[i]), tp_str, T_UINT8, LEVEL1 );

		sprintf(tp_str, "pDZ%dHandF", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pDZHandF[i]), tp_str, T_BIT, LEVEL1 );        // 手分刀闸
		sprintf(tp_str, "pDZ%dHandH", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pDZHandH[i]), tp_str, T_BIT, LEVEL1 );        // 手合刀闸
	}	
	
	registerVarIn( (Component*)dp, (void**)&(dp->pDZYF_ELSE), "pDZYF_ELSE", T_BIT, LEVEL1 );			   // 另一CPU的输出连接到此，进行两套系统的比对
	registerVarIn( (Component*)dp, (void**)&(dp->pDZYH_ELSE), "pDZYH_ELSE", T_BIT, LEVEL1 );			   // 另一CPU的输出连接到此，进行两套系统的比对
	registerVarIn( (Component*)dp, (void**)&(dp->pDZBLK_ELSE), "pDZBLK_ELSE", T_BIT, LEVEL1 );		       // 另一CPU的输出连接到此，进行两套系统的比对

/////////////////////////////////////////刀闸遥控输出//////////////////////////////////////////////////
	registerVarOut( (Component*)dp, (void*)&(dp->AElecTest), "AElecTest", T_BIT, LEVEL1 );       //A套主控带电检修态
	registerVarOut( (Component*)dp, (void*)&(dp->ACutTest), "ACutTest", T_BIT, LEVEL1 );         //A套主控停电检修态

	registerVarOut( (Component*)dp, (void*)&(dp->BElecTest), "BElecTest", T_BIT, LEVEL1 );       //B套主控带电检修态
	registerVarOut( (Component*)dp, (void*)&(dp->BCutTest), "BCutTest", T_BIT, LEVEL1 );         //B套主控停电检修态

	for ( i=0; i<YK_DZ_NUM; i++ )
	{
		sprintf(tp_str, "ADZ%dYF_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->ADZYF_E[i]), tp_str, T_SOE, LEVEL2 );      //A套刀闸遥分 SOE
		sprintf(tp_str, "ADZ%dYH_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->ADZYH_E[i]), tp_str, T_SOE, LEVEL2 );      //A套刀闸遥合 SOE
		sprintf(tp_str, "ADZ%dBLK_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->ADZBLK_E[i]), tp_str, T_SOE, LEVEL2 );     //A套刀闸解闭锁 SOE

		sprintf(tp_str, "BDZ%dYF_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BDZYF_E[i]), tp_str, T_SOE, LEVEL2 );      //B套刀闸遥分 SOE
		sprintf(tp_str, "BDZ%dYH_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BDZYH_E[i]), tp_str, T_SOE, LEVEL2 );      //B套刀闸遥合 SOE
		sprintf(tp_str, "BDZ%dBLK_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BDZBLK_E[i]), tp_str, T_SOE, LEVEL2 );     //B套刀闸解闭锁 SOE
		
		sprintf(tp_str, "TestDZ%dYF_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TestDZYF_E[i]), tp_str, T_SOE, LEVEL2 );   //测试仪刀闸遥分 SOE
		sprintf(tp_str, "TestDZ%dYH_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TestDZYH_E[i]), tp_str, T_SOE, LEVEL2 );   //测试仪刀闸遥合 SOE
		sprintf(tp_str, "TestDZ%dBLK_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TestDZBLK_E[i]), tp_str, T_SOE, LEVEL2 );  //测试仪刀闸解闭锁 SOE

		sprintf(tp_str, "DZ%dYF", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->DZYF[i]), tp_str, T_BIT, LEVEL2 );       //刀闸遥分 动作
		sprintf(tp_str, "DZ%dYH", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->DZYH[i]), tp_str, T_BIT, LEVEL2 );       //刀闸遥合 动作
		sprintf(tp_str, "DZ%dBLK", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->DZBLK[i]), tp_str, T_BIT, LEVEL2 );      //刀闸解闭锁 动作

		sprintf(tp_str, "TestDZ%dYF", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TestDZYF[i]), tp_str, T_BIT, LEVEL2 );    //测试仪刀闸遥分 动作
		sprintf(tp_str, "TestDZ%dYH", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TestDZYH[i]), tp_str, T_BIT, LEVEL2 );    //测试仪刀闸遥合 动作
		sprintf(tp_str, "TestDZ%dBLK", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TestDZBLK[i]), tp_str, T_BIT, LEVEL2 );   //测试仪刀闸解闭锁 动作

		sprintf(tp_str, "DZ%dYF_Out", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->DZYF_Out[i]), tp_str, T_BIT, LEVEL2 );    //刀闸遥分输出
		sprintf(tp_str, "DZ%dYH_Out", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->DZYH_Out[i]), tp_str, T_BIT, LEVEL2 );    //刀闸遥合输出
		sprintf(tp_str, "DZ%dBLK_Out", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->DZBLK_Out[i]), tp_str, T_BIT, LEVEL2 );   //刀闸遥解闭锁输出
	}
	
	registerVarOut( (Component*)dp, (void*)&(dp->DZYF_ALL), "DZYF_ALL", T_BIT, LEVEL2 );       //刀闸遥分总
	registerVarOut( (Component*)dp, (void*)&(dp->DZYH_ALL), "DZYH_ALL", T_BIT, LEVEL2 );       //刀闸遥合总
	registerVarOut( (Component*)dp, (void*)&(dp->DZBLK_ALL), "DZBLK_ALL", T_BIT, LEVEL2 );     //刀闸解闭锁总

	registerVarOut( (Component*)dp, (void*)&(dp->DZYK_LONGTIME), "DZYK_LONGTIME", T_BIT, LEVEL2 );   //刀闸遥控长时间动作
	
	registerVarOut( (Component*)dp, (void*)&(dp->check_err), "check_err", T_BIT, LEVEL2 );		//指针比较出错
	registerVarOut( (Component*)dp, (void*)&(dp->CMP_ERR), "CMP_ERR", T_BIT, LEVEL2 );			//双套比较

/////////////////////////////////////////刀闸遥控参数//////////////////////////////////////////////////	

	return dp;
}

void DzCmdMerge_check_task(DzCmdMerge *dp)
{
	if(dp->check_err == 0)
	{
		dp->check_err = check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	}
}


INIT_CODE
int initDzCmdMerge(DzCmdMerge *dp)
{
	Uint16 i;
	
	initSOE_fun( &(dp->AElecTest_E), 0 );
	initSOE_fun( &(dp->ACutTest_E), 0 );
	initSOE_fun( &(dp->BElecTest_E), 0 );
	initSOE_fun( &(dp->BCutTest_E), 0 );
	
	for( i=0; i<YK_DZ_NUM; i++ )
	{
		initSOE_fun( &(dp->ADZYF_E[i]), 0 );
		initSOE_fun( &(dp->ADZYH_E[i]), 0 );
		initSOE_fun( &(dp->ADZBLK_E[i]), 0 );

		initSOE_fun( &(dp->BDZYF_E[i]), 0 );
		initSOE_fun( &(dp->BDZYH_E[i]), 0 );
		initSOE_fun( &(dp->BDZBLK_E[i]), 0 );

		initSOE_fun( &(dp->TestDZYF_E[i]), 0 );
		initSOE_fun( &(dp->TestDZYH_E[i]), 0 );
		initSOE_fun( &(dp->TestDZBLK_E[i]), 0 );
	}

	dp->CMP_CNT1 = 0;
	dp->CMP_CNT2 = 0;
	dp->CMP_CNT3 = 0;
	
	dp->CMP_ERR = 0;
	
	dp->status1 = 0;
	dp->time_save1  = 0;

	dp->DZYK_LONGTIME = 0;
	dp->check_err = 0;

	init_check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	
	setTask( 2, DzCmdMerge_task, dp);
	setTask( 4, DzCmdMerge_check_task, dp);
	return 0;
}


#pragma CODE_SECTION(DzCmdMerge_task,".rtm_code")

//品质一致：在线且检修一致，命令或；否则，清0
//品质不一致：A运行态，用A;B运行态，用B；无运行态，清0。
Uint8 Fun_CMD_QComp( Uint8 ACmd, Uint8 *Aquality, Uint8 BCmd, Uint8 *Bquality, Uint8 DevTest )
{
	Uint8  Astate, Bstate;

	Astate = *Aquality;
	Bstate = *Bquality;

	//品质一致
	if ( Astate == Bstate )
	{
		//在线
		if ( ((Astate & 0x08) == 0x08) && ((Astate & 0x04) == 0x04) &&  (((Astate & 0x02) >> 1) == DevTest) )
		{
			return ( ACmd | BCmd);
		}
		else 
		{
			return 0;
		}
	}
	else
	{
		//A在线且为运行态
		if ( ((Astate & 0x08) == 0x08) && ((Astate & 0x04) == 0x04) && ((Astate & 0x02) == 0x0) && ( DevTest == 0 ) )
		{
			return ACmd;
		}
		else if ( ((Bstate & 0x08) == 0x08) && ((Bstate & 0x04) == 0x04) && ((Bstate & 0x02) == 0x0) && ( DevTest == 0 ) )  //B在线且为运行态
		{
			return BCmd;
		}
		else
		{
			
			return 0;	  //B在线
		}
	}
}

void DzCmdMerge_task(DzCmdMerge *dp)
{
	Uint8 tmp=0;
	Uint16	i;

////////////////////////////GOOSE接收SOE报文生成及命令反馈////////////////////////////////////////////
	//A套主控检修状态
	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pAElecTest, dp->pAElecTest_ok, &(dp->AElecTest_E) );
	dp->AElecTest = dp->AElecTest_E.value.c_value;
	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pACutTest, dp->pACutTest_ok, &(dp->ACutTest_E) );
	dp->ACutTest = dp->ACutTest_E.value.c_value;
	
	//B套主控检修状态
	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pBElecTest, dp->pBElecTest_ok, &(dp->BElecTest_E) );
	dp->BElecTest = dp->BElecTest_E.value.c_value;
	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pBCutTest, dp->pBCutTest_ok, &(dp->BCutTest_E) );
	dp->BCutTest = dp->BCutTest_E.value.c_value;

	for(i=0; i<YK_DZ_NUM; i++)
	{
		//测试仪控制刀闸SOE
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestDZYF[i], dp->pTestDZYF_ok[i], &(dp->TestDZYF_E[i]) );
		dp->DZYF_GSE[i] = dp->TestDZYF_E[i].value.c_value;
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestDZYH[i], dp->pTestDZYH_ok[i], &(dp->TestDZYH_E[i]) );
		dp->DZYH_GSE[i] = dp->TestDZYH_E[i].value.c_value;
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestDZBLK[i], dp->pTestDZBLK_ok[i], &(dp->TestDZBLK_E[i]) );
		dp->DZBLK_GSE[i] = dp->TestDZBLK_E[i].value.c_value;

		//A套控制刀闸SOE
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pADZYF[i], dp->pADZYF_ok[i], &(dp->ADZYF_E[i]) );
		dp->DZYF_GSE[i] |= dp->ADZYF_E[i].value.c_value;
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pADZYH[i], dp->pADZYH_ok[i], &(dp->ADZYH_E[i]) );
		dp->DZYH_GSE[i] |= dp->ADZYH_E[i].value.c_value;
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pADZBLK[i], dp->pADZBLK_ok[i], &(dp->ADZBLK_E[i]) );
		dp->DZBLK_GSE[i] |= dp->ADZBLK_E[i].value.c_value;

		//B套控制刀闸SOE
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pBDZYF[i], dp->pBDZYF_ok[i], &(dp->BDZYF_E[i]) );
		dp->DZYF_GSE[i] |= dp->BDZYF_E[i].value.c_value;
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pBDZYH[i], dp->pBDZYH_ok[i], &(dp->BDZYH_E[i]) );
		dp->DZYH_GSE[i] |= dp->BDZYH_E[i].value.c_value;
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pBDZBLK[i], dp->pBDZBLK_ok[i], &(dp->BDZBLK_E[i]) );
		dp->DZBLK_GSE[i] |= dp->BDZBLK_E[i].value.c_value;
	}
	
//////////////////////////GOOSE报文品质处理/////////////////////////////////////////////////

	//测试命令处理
	if ( *(dp->pTest) == 1 )
	{
		//检修态：检修一致认可测试仪命令
		for ( i=0; i<YK_DZ_NUM; i++ )
		{
			dp->TestDZYF[i]  = GSE_Test_Q( dp->pTestDZYF[i], dp->pTestDZYF_ok[i], *(dp->pTest) );
			dp->TestDZYH[i]  = GSE_Test_Q( dp->pTestDZYH[i], dp->pTestDZYH_ok[i], *(dp->pTest) );
			dp->TestDZBLK[i] = GSE_Test_Q( dp->pTestDZBLK[i], dp->pTestDZBLK_ok[i], *(dp->pTest) );
		}
	}
	else
	{
		for ( i=0; i<YK_DZ_NUM; i++ )
		{
			dp->TestDZYF[i]  = 0;
			dp->TestDZYH[i]  = 0;
			dp->TestDZBLK[i] = 0;
		}
	}

	for ( i=0; i<YK_DZ_NUM; i++ )
	{
		dp->DZLF_OP[i]  = dp->TestDZYF[i];
		dp->DZLH_OP[i]  = dp->TestDZYH[i];
		dp->DZLBLK_OP[i] = dp->TestDZBLK[i];
	}
	
	//过程层命令处理
	if ( *(dp->pElecTest) == 1 )
	{
		//本体模块带电检修：过程层命令清0
		for ( i=0; i<YK_DZ_NUM; i++ )
		{
			dp->DZYF[i] = 0;
			dp->DZYH[i] = 0;	
			dp->DZBLK[i] = 0;

			dp->DZHandF[i] = 0;
			dp->DZHandH[i] = 0;
		}
	}
	else
	{
		for ( i=0; i<YK_DZ_NUM; i++ )
		{
			dp->DZHandF[i] = *(dp->pDZHandF[i]);
			dp->DZLF_OP[i] |= dp->DZHandF[i];

			dp->DZHandH[i] = *(dp->pDZHandH[i]);
			dp->DZLH_OP[i] |= dp->DZHandH[i];
		}

		// A/B套主控为不同的检修态
		if ( (( dp->AElecTest == 1) && ( dp->BCutTest == 1)) || (( dp->ACutTest == 1) && ( dp->BElecTest == 1))
		  || (( dp->AElecTest == 1) && ( dp->BElecTest == 1)) )
		{
			//AB主控检修态不一致：过程层命令清0
			for ( i=0; i<YK_DZ_NUM; i++ )
			{
				dp->DZYF[i] = 0;
				dp->DZYH[i] = 0;
				dp->DZBLK[i] = 0;
			}
		}
		else
		{
			//主控运行态或停电检修态：检修一致更新，检修不一致清0
			for ( i=0; i<YK_DZ_NUM; i++ )
			{
				dp->DZYF[i]  = Fun_CMD_QComp( *(dp->pADZYF[i]), dp->pADZYF_ok[i], *(dp->pBDZYF[i]), dp->pBDZYF_ok[i], *(dp->pTest) );
				dp->DZYH[i]  = Fun_CMD_QComp( *(dp->pADZYH[i]), dp->pADZYH_ok[i], *(dp->pBDZYH[i]), dp->pBDZYH_ok[i], *(dp->pTest) );
				dp->DZBLK[i] = Fun_CMD_QComp( *(dp->pADZBLK[i]), dp->pADZBLK_ok[i], *(dp->pBDZBLK[i]), dp->pBDZBLK_ok[i], *(dp->pTest) );
			}
		}	
	}

///////////////////////////动作及点灯信号/////////////////////////////////////////////////////
	dp->DZYF_ALL  = 0;
	dp->DZYH_ALL  = 0;
	dp->DZBLK_ALL = 0;
	
	// 远控模式
	if ( *(dp->pFarCon) == 1 )
	{
		for ( i=0; i<YK_DZ_NUM; i++ )
		{	
			dp->DZYF_Out[i]  = dp->DZYF[i];
			dp->DZYH_Out[i]  = dp->DZYH[i];
			dp->DZBLK_Out[i] = dp->DZBLK[i];	
		}
	}
	else if ( *(dp->pLocalCon) == 1 )  // 近控模式
	{
		for ( i=0; i<YK_DZ_NUM; i++ )
		{
			dp->DZYF_Out[i]  = dp->DZLF_OP[i];
			dp->DZYH_Out[i]  = dp->DZLH_OP[i];
			dp->DZBLK_Out[i] = dp->DZLBLK_OP[i];
		}
	}
	else
	{
		for ( i=0; i<YK_DZ_NUM; i++ )
		{
			dp->DZYF_Out[i]  = 0;
			dp->DZYH_Out[i]  = 0;
			dp->DZBLK_Out[i] = 0;
		}
	}
	

	for ( i=0; i<YK_DZ_NUM; i++ )
	{
		if ( *(dp->pDZOutBd[i]) == 0 )
		{
			dp->DZYF_Out[i] = 0;
			dp->DZYH_Out[i] = 0;
			dp->DZBLK_Out[i] = 0;
		}
		
		dp->DZYF_ALL  |= dp->DZYF_Out[i];
		dp->DZYH_ALL  |= dp->DZYH_Out[i];
		dp->DZBLK_ALL |= dp->DZBLK_Out[i];
	}

	dp->DZYK_LONGTIME = Dlyon(&(dp->status1), &(dp->time_save1), dp->DZYF_ALL|dp->DZYH_ALL, tick_10000ms);
//////////////////////////双系统监视比较////////////////////////////////////////////////////////////
#ifndef MAIN_DSP
	two_sys_cmp( dp->DZYF_ALL, *(dp->pDZYF_ELSE), &tmp, &(dp->CMP_CNT1), lev2_10S);
	dp->CMP_ERR |= tmp;
	two_sys_cmp( dp->DZYH_ALL, *(dp->pDZYH_ELSE), &tmp, &(dp->CMP_CNT2), lev2_10S);
	dp->CMP_ERR |= tmp;
	two_sys_cmp( dp->DZBLK_ALL, *(dp->pDZBLK_ELSE), &tmp, &(dp->CMP_CNT3), lev2_10S);
	dp->CMP_ERR |= tmp;
#endif
//////////////////////////启动出口//////////////////////////////////////////////////////////////////
	
}

