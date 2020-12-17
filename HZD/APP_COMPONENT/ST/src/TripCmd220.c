/* File Description   
*  FileName: SysSwapDeal.c -- 智能开关双套交互数据处理元件     
*  Fuction: 
*       功能：获取双套主控模块数据并转发
*       输入：双套数据Gs值和品质
*       输出：双套数据值和Gs品质
*  apply: 智能化开关
*  author: ZYB 
*  data:  20200825
*/

#include <stdlib.h>
#include "hzplatform.h"
#include "SysSwapDeal.h"
#include "CommFun.h"

void SysSwapDeal_task( SysSwapDeal *dp);

int initSysSwapDeal( SysSwapDeal *dp);


SysSwapDeal *newSysSwapDeal(Component *parent, const char *name)
{
	Uint8 i;
	char tp_str[150];
	
	SysSwapDeal *dp;
	
	dp = (SysSwapDeal *)calloc(1, sizeof(SysSwapDeal));
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "SysSwapDeal";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent = (int (*)(void *))initSysSwapDeal;

	registerComponent( (Component*)dp);
	
	registerVarIn( (Component*)dp, (void**)&(dp->pAtB_HandH), "pAtB_HandH", T_BIT, LEVEL2 );            // A套至B套手合
	registerVarIn( (Component*)dp, (void**)&(dp->pAtB_HandH_ok), "pAtB_HandH_ok", T_UINT8, LEVEL2 );    
	registerVarIn( (Component*)dp, (void**)&(dp->pAtB_HandF), "pAtB_HandF", T_BIT, LEVEL2 );            // A套至B套手跳
	registerVarIn( (Component*)dp, (void**)&(dp->pAtB_HandF_ok), "pAtB_HandF_ok", T_UINT8, LEVEL2 ); 
	registerVarIn( (Component*)dp, (void**)&(dp->pAtB_LockRcls), "pAtB_LockRcls", T_BIT, LEVEL2 );      // A套至B套闭锁重合闸
	registerVarIn( (Component*)dp, (void**)&(dp->pAtB_LockRcls_ok), "pAtB_LockRcls_ok", T_UINT8, LEVEL2 ); 

	registerVarIn( (Component*)dp, (void**)&(dp->pBtA_HandH), "pBtA_HandH", T_BIT, LEVEL2 );            // B套至A套手合
	registerVarIn( (Component*)dp, (void**)&(dp->pBtA_HandH_ok), "pBtA_HandH_ok", T_UINT8, LEVEL2 );    
	registerVarIn( (Component*)dp, (void**)&(dp->pBtA_HandF), "pBtA_HandF", T_BIT, LEVEL2 );            // B套至A套手跳
	registerVarIn( (Component*)dp, (void**)&(dp->pBtA_HandF_ok), "pBtA_HandF_ok", T_UINT8, LEVEL2 ); 
	registerVarIn( (Component*)dp, (void**)&(dp->pBtA_LockRcls), "pBtA_LockRcls", T_BIT, LEVEL2 );      // B套至A套闭锁重合闸
	registerVarIn( (Component*)dp, (void**)&(dp->pBtA_LockRcls_ok), "pBtA_LockRcls_ok", T_UINT8, LEVEL2 ); 

//////////////////////////////////////////////////////////////////////////////////////////////////////

	registerVarOut( (Component*)dp, (void*)&(dp->AtB_HandH), "AtB_HandH", T_BIT, LEVEL2 );	            // A套至B套手合
	registerVarOut( (Component*)dp, (void*)&(dp->AtB_HandH_ok), "AtB_HandH_ok", T_UINT8, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->AtB_HandF), "AtB_HandF", T_BIT, LEVEL2 );	            // A套至B套手跳
	registerVarOut( (Component*)dp, (void*)&(dp->AtB_HandF_ok), "AtB_HandF_ok", T_UINT8, LEVEL2 );	      
	registerVarOut( (Component*)dp, (void*)&(dp->AtB_LockRcls), "AtB_LockRcls", T_BIT, LEVEL2 );	    // A套至B套闭锁重合闸
	registerVarOut( (Component*)dp, (void*)&(dp->AtB_LockRcls_ok), "AtB_LockRcls_ok", T_UINT8, LEVEL2 );

	registerVarOut( (Component*)dp, (void*)&(dp->BtA_HandH), "BtA_HandH", T_BIT, LEVEL2 );	            // B套至A套手合
	registerVarOut( (Component*)dp, (void*)&(dp->BtA_HandH_ok), "BtA_HandH_ok", T_UINT8, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->BtA_HandF), "BtA_HandF", T_BIT, LEVEL2 );	            // B套至A套手跳
	registerVarOut( (Component*)dp, (void*)&(dp->BtA_HandF_ok), "BtA_HandF_ok", T_UINT8, LEVEL2 );	      
	registerVarOut( (Component*)dp, (void*)&(dp->BtA_LockRcls), "BtA_LockRcls", T_BIT, LEVEL2 );	    // B套至A套闭锁重合闸
	registerVarOut( (Component*)dp, (void*)&(dp->BtA_LockRcls_ok), "BtA_LockRcls_ok", T_UINT8, LEVEL2 );

	return dp;
}

INIT_CODE
int initSysSwapDeal(SysSwapDeal *dp)
{
	setTask( 2, SysSwapDeal_task, dp);

	return 0;
}


#pragma CODE_SECTION(SysSwapDeal_task,".rtm_code")


void SysSwapDeal_task(SysSwapDeal *dp)
{
	
	dp->AtB_HandH        =  *(dp->pAtB_HandH);
	dp->AtB_HandH_ok     =  *(dp->pAtB_HandH_ok);
	dp->AtB_HandF        =  *(dp->pAtB_HandF);
	dp->AtB_HandF_ok     =  *(dp->pAtB_HandF_ok);
	dp->AtB_LockRcls     =  *(dp->pAtB_LockRcls);
	dp->AtB_LockRcls_ok  =  *(dp->pAtB_LockRcls_ok);

	dp->BtA_HandH        =  *(dp->pBtA_HandH);
	dp->BtA_HandH_ok     =  *(dp->pBtA_HandH_ok);
	dp->BtA_HandF        =  *(dp->pBtA_HandF);
	dp->BtA_HandF_ok     =  *(dp->pBtA_HandF_ok);
	dp->BtA_LockRcls     =  *(dp->pBtA_LockRcls);
	dp->BtA_LockRcls_ok  =  *(dp->pBtA_LockRcls_ok);
	
}
		registerVarIn( (Component*)dp, (void**)&(dp->pCBYF_GSE[i]), tp_str, T_BIT, LEVEL1 );         // ң�ֶ�·��ֵ

		sprintf(tp_str, "pCBYF%d_GSE__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pCBYF_GSE_ok[i]), tp_str, T_UINT8, LEVEL1 );    // ң�ֶ�·��Ʒ��
	}

	
	registerVarIn( (Component*)dp, (void**)&(dp->pTestReset_GSE), "pTestReset_GSE__AB", T_BIT, LEVEL1 );      // �����Ǹ���
	registerVarIn( (Component*)dp, (void**)&(dp->pTestReset_GSE_ok), "pTestReset_GSE__AB_ok", T_UINT8, LEVEL1 );     

	registerVarIn( (Component*)dp, (void**)&(dp->pTestTA_GSE), "pTestTA_GSE__AB", T_BIT, LEVEL1 );            // ��������Aֵ
	registerVarIn( (Component*)dp, (void**)&(dp->pTestTA_GSE_ok), "pTestTA_GSE__AB_ok", T_UINT8, LEVEL1 );    // ��������AƷ��

	registerVarIn( (Component*)dp, (void**)&(dp->pTestTB_GSE), "pTestTB_GSE__AB", T_BIT, LEVEL1 );            // ��������Bֵ
	registerVarIn( (Component*)dp, (void**)&(dp->pTestTB_GSE_ok), "pTestTB_GSE__AB_ok", T_UINT8, LEVEL1 );    // ��������BƷ��

	registerVarIn( (Component*)dp, (void**)&(dp->pTestTC_GSE), "pTestTC_GSE__AB", T_BIT, LEVEL1 );            // ��������Cֵ
	registerVarIn( (Component*)dp, (void**)&(dp->pTestTC_GSE_ok), "pTestTC_GSE__AB_ok", T_UINT8, LEVEL1 );    // ��������CƷ��

	registerVarIn( (Component*)dp, (void**)&(dp->pTestTJQ_GSE), "pTestTJQ_GSE__AB", T_BIT, LEVEL1 );            // ��������TJQֵ
	registerVarIn( (Component*)dp, (void**)&(dp->pTestTJQ_GSE_ok), "pTestTJQ_GSE__AB_ok", T_UINT8, LEVEL1 );    // ��������TJQƷ��

	registerVarIn( (Component*)dp, (void**)&(dp->pTestTJR_GSE), "pTestTJR_GSE__AB", T_BIT, LEVEL1 );            // ��������TJRֵ
	registerVarIn( (Component*)dp, (void**)&(dp->pTestTJR_GSE_ok), "pTestTJR_GSE__AB_ok", T_UINT8, LEVEL1 );    // ��������TJRƷ��

	registerVarIn( (Component*)dp, (void**)&(dp->pTestCBYF_GSE), "pTestCBYF_GSE__AB", T_BIT, LEVEL1 );            // ������ң����բֵ
	registerVarIn( (Component*)dp, (void**)&(dp->pTestCBYF_GSE_ok), "pTestCBYF_GSE__AB_ok", T_UINT8, LEVEL1 );    // ������ң����բƷ��

	registerVarIn( (Component*)dp, (void**)&(dp->pTestCBBLK_GSE), "pTestCBBLK_GSE__AB", T_BIT, LEVEL1 );            // �����Ƕ�·�������ֵ
	registerVarIn( (Component*)dp, (void**)&(dp->pTestCBBLK_GSE_ok), "pTestCBBLK_GSE__AB_ok", T_UINT8, LEVEL1 );    // �����Ƕ�·�������Ʒ��

	registerVarIn( (Component*)dp, (void**)&(dp->pBSysST_GSE), "pBSysST_GSE__AB", T_BIT, LEVEL1 );		     // ������һ������
	registerVarIn( (Component*)dp, (void**)&(dp->pBSysST_GSE_ok), "pBSysST_GSE__AB_ok", T_UINT8, LEVEL1 );

	registerVarIn( (Component*)dp, (void**)&(dp->pTZ_ELSE), "pTZ_ELSE", T_BIT, LEVEL1 );	            //��һCPU��TZ������ӵ��ˣ���������ϵͳ�ıȶ�

	registerVarIn( (Component*)dp, (void**)&(dp->pCBBLK1_GSE), "pCBBLK1_GSE__AB", T_BIT, LEVEL1 );            // ��·�������1ֵ
	registerVarIn( (Component*)dp, (void**)&(dp->pCBBLK1_GSE_ok), "pCBBLK1_GSE__AB_ok", T_UINT8, LEVEL1 );    // ��·�������1Ʒ��
	
	registerVarIn( (Component*)dp, (void**)&(dp->pCBBLK2_GSE), "pCBBLK2_GSE__AB", T_BIT, LEVEL1 );            // ��·�������2ֵ
	registerVarIn( (Component*)dp, (void**)&(dp->pCBBLK2_GSE_ok), "pCBBLK2_GSE__AB_ok", T_UINT8, LEVEL1 );    // ��·�������2Ʒ��

	registerVarIn( (Component*)dp, (void**)&(dp->pCBBLK_ELSE), "pCBBLK_ELSE", T_BIT, LEVEL1 );	          // ��һCPU�Ľ����������ӵ��ˣ���������ϵͳ�ıȶ�

//////////////////////////////////////////////////////////////////////////////////////////////////////
	
	for ( i=0; i<Reset_Num; i++ )
	{
		sprintf(tp_str, "Reset%d_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->Reset_E[i]), tp_str, T_SOE, LEVEL2 );   //Զ������ SOE
	}
	
	for ( i=0; i<OpS_Num; i++ )
	{
		sprintf(tp_str, "TA%d_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TA_E[i]), tp_str, T_SOE, LEVEL2 );   //��A SOE

		sprintf(tp_str, "TB%d_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TB_E[i]), tp_str, T_SOE, LEVEL2 );   //��B SOE

		sprintf(tp_str, "TC%d_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TC_E[i]), tp_str, T_SOE, LEVEL2 );   //��C SOE
	}

	for ( i=0; i<TJQ_Num; i++ )
	{
		sprintf(tp_str, "TJQ%d_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TJQ_E[i]), tp_str, T_SOE, LEVEL2 );   //TJQ SOE
	}

	for ( i=0; i<TJR_Num; i++ )
	{
		sprintf(tp_str, "TJR%d_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TJR_E[i]), tp_str, T_SOE, LEVEL2 );   //TJR SOE
	}

	for ( i=0; i<YK_Open_NUM; i++ )
	{
		sprintf(tp_str, "CBYF%d_E", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->CBYF_E[i]), tp_str, T_SOE, LEVEL2 );   //ң�ֶ�·�� SOE
	}

	registerVarOut( (Component*)dp, (void*)&(dp->CBBLK1_E), "CBBLK1_E", T_BIT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->CBBLK2_E), "CBBLK2_E", T_BIT, LEVEL2 );

	registerVarOut( (Component*)dp, (void*)&(dp->BSysST_E), "BSysST_E", T_BIT, LEVEL2 );
	
	registerVarOut( (Component*)dp, (void*)&(dp->TestReset_E), "TestReset_E", T_SOE, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->TestTA_E), "TestTA_E", T_SOE, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->TestTB_E), "TestTB_E", T_SOE, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->TestTC_E), "TestTC_E", T_SOE, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->TestTJQ_E), "TestTJQ_E", T_SOE, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->TestTJR_E), "TestTJR_E", T_SOE, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->TestCBBLK_E), "TestCBBLK_E", T_SOE, LEVEL2 );

	registerVarOut( (Component*)dp, (void*)&(dp->ResetCmd), "ResetCmd", T_BIT, LEVEL2 );   // ��������

	registerVarOut( (Component*)dp, (void*)&(dp->TA_Op), "TA_Op", T_BIT, LEVEL2 );          //������TA����
	registerVarOut( (Component*)dp, (void*)&(dp->TB_Op), "TB_Op", T_BIT, LEVEL2 );          //������TB����
	registerVarOut( (Component*)dp, (void*)&(dp->TC_Op), "TC_Op", T_BIT, LEVEL2 );          //������TC����
	
	registerVarOut( (Component*)dp, (void*)&(dp->TJQ_Op), "TJQ_Op", T_BIT, LEVEL2 );        //goose��TJQ��բ
	registerVarOut( (Component*)dp, (void*)&(dp->TJR_Op), "TJR_Op", T_BIT, LEVEL2 );		//goose��TJR��բ
	registerVarOut( (Component*)dp, (void*)&(dp->TJR_OPT), "TJR_OPT", T_BIT, LEVEL2 );	    //�����TJR��բ
	registerVarOut( (Component*)dp, (void*)&(dp->TJF_OPT), "TJF_OPT", T_BIT, LEVEL2 );      //�����TJF��բ
	
	registerVarOut( (Component*)dp, (void*)&(dp->CBYF_Op), "CBYF_Op", T_BIT, LEVEL2 );      //ң�ֶ���
	registerVarOut( (Component*)dp, (void*)&(dp->CBBLK_Op), "CBBLK_Op", T_BIT, LEVEL2 );    //���������

	registerVarOut( (Component*)dp, (void*)&(dp->ST_OPT), "ST_OPT", T_BIT, LEVEL2 );        //��������
	registerVarOut( (Component*)dp, (void*)&(dp->STJ), "STJ", T_BIT, LEVEL2 );              //STJ�ź�
	registerVarOut( (Component*)dp, (void*)&(dp->ST_Else), "ST_Else", T_BIT, LEVEL2 );	    //�������-����һ��
	
	registerVarOut( (Component*)dp, (void*)&(dp->TA_Out), "TA_Out", T_BIT, LEVEL2 );        //TA���
	registerVarOut( (Component*)dp, (void*)&(dp->TB_Out), "TB_Out", T_BIT, LEVEL2 );        //TB���
	registerVarOut( (Component*)dp, (void*)&(dp->TC_Out), "TC_Out", T_BIT, LEVEL2 );        //TC���

	registerVarOut( (Component*)dp, (void*)&(dp->TZ_Out), "TZ_Out", T_BIT, LEVEL2 );        //��һ��բ���--��բ����
	
	registerVarOut( (Component*)dp, (void*)&(dp->TZ_GSE), "TZ_GSE", T_BIT, LEVEL2 );		//goose��һ��բ�����
	registerVarOut( (Component*)dp, (void*)&(dp->TA_GSE), "TA_GSE", T_BIT, LEVEL2 );		//goose������A�����
	registerVarOut( (Component*)dp, (void*)&(dp->TB_GSE), "TB_GSE", T_BIT, LEVEL2 );		//goose������B�����
	registerVarOut( (Component*)dp, (void*)&(dp->TC_GSE), "TC_GSE", T_BIT, LEVEL2 );		//goose������C�����
	registerVarOut( (Component*)dp, (void*)&(dp->CBYF_GSE), "CBYF_GSE", T_BIT, LEVEL2 );    //goose�����բ�����

	registerVarOut( (Component*)dp, (void*)&(dp->TZ_LONGTIME), "TZ_LONGTIME", T_BIT, LEVEL2 );

	//registerVarOut( (Component*)dp, (void*)&(dp->QD), "QD", T_BIT, LEVEL2 );

	registerVarOut( (Component*)dp, (void*)&(dp->CMP_ERR), "CMP_ERR", T_BIT, LEVEL2 );			//˫�ױȽϳ���
	registerVarOut( (Component*)dp, (void*)&(dp->check_err), "check_err", T_BIT, LEVEL2 );		//ָ��Ƚϳ���

	/////////INIT IN////////////////////////////////////
	//init_pointer((Uint32)(&dp->p_start),(Uint32)(&dp->p_end));
	///////////////////////////////////////////////////
	
	return dp;
}

void TripCmd220_check_task(TripCmd220 *dp)
{
	if(dp->check_err == 0)
	{
		dp->check_err = check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	}
}



INIT_CODE
int initTripCmd220(TripCmd220 *dp)
{
	Uint16 i=0;

	for ( i=0; i<Reset_Num; i++ )
	{
		initSOE_fun( &(dp->Reset_E[i]), 0 );
	}

	for ( i=0; i<OpS_Num; i++ )
	{
		initSOE_fun( &(dp->TA_E[i]), 0 );
		initSOE_fun( &(dp->TB_E[i]), 0 );
		initSOE_fun( &(dp->TC_E[i]), 0 );
	}
	
	for ( i=0; i<TJQ_Num; i++ )
	{
		initSOE_fun( &(dp->TJQ_E[i]), 0 );
	}

	for ( i=0; i<TJR_Num; i++ )
	{
		initSOE_fun( &(dp->TJR_E[i]), 0 );
	}

	for ( i=0; i<YK_Open_NUM; i++ )
	{
		initSOE_fun( &(dp->CBYF_E[i]), 0 );
	}

	initSOE_fun( &(dp->CBBLK1_E), 0 );
	initSOE_fun( &(dp->CBBLK2_E), 0 );

	initSOE_fun( &(dp->BSysST_E), 0 );

	initSOE_fun( &(dp->TestReset_E), 0 );
	initSOE_fun( &(dp->TestTA_E), 0 );
	initSOE_fun( &(dp->TestTB_E), 0 );
	initSOE_fun( &(dp->TestTC_E), 0 );

	initSOE_fun( &(dp->TestTJQ_E), 0 );
	initSOE_fun( &(dp->TestTJR_E), 0 );
	initSOE_fun( &(dp->TestCBBLK_E), 0 );
	

	dp->TZ_LONGTIME = 0;
	dp->TJQ_Op = 0;
	dp->TJR_Op = 0;
	dp->TZ_Out = 0;
	dp->CBBLK_Op = 0;
	dp->CMP_CNT1 = 0;
	dp->CMP_CNT2 = 0;
	dp->CMP_ERR = 0;

	dp->STJ_New = 0;
	dp->STJ_Old = 0;
	dp->STJ_CNT = 0;
	
	dp->status1 = 0;
	dp->time_save1  = 0;
	dp->check_err = 0;

	init_check_set_pointer( (Uint32)(&dp->start), (Uint32)(&dp->checksum) );
	
	setTask( 2, TripCmd220_task, dp);
	setTask( 4, TripCmd220_check_task, dp);

	return 0;
}

#pragma CODE_SECTION(TripCmd220_task,".rtm_code")

void TripCmd220_task(TripCmd220 *dp)
{
	Uint16 i=0;
	Uint8 tmp=0;

////////////////////////////GOOSE����SOE�������ɼ������////////////////////////////////////////////
	
	//����������
	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestReset_GSE, dp->pTestReset_GSE_ok, &(dp->TestReset_E) );
	dp->RESET_GSE = dp->TestReset_E.value.c_value;

	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestTA_GSE, dp->pTestTA_GSE_ok, &(dp->TestTA_E) );
	dp->TA_GSE  = dp->TestTA_E.value.c_value;

	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestTB_GSE, dp->pTestTB_GSE_ok, &(dp->TestTB_E) );
	dp->TB_GSE  = dp->TestTB_E.value.c_value;

	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestTC_GSE, dp->pTestTC_GSE_ok, &(dp->TestTC_E) );
	dp->TC_GSE  = dp->TestTC_E.value.c_value;

	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestTJQ_GSE, dp->pTestTJQ_GSE_ok, &(dp->TestTJQ_E) );
	dp->TA_GSE  |= dp->TestTJQ_E.value.c_value;
	dp->TB_GSE  |= dp->TestTJQ_E.value.c_value;
	dp->TC_GSE  |= dp->TestTJQ_E.value.c_value;

	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestTJR_GSE, dp->pTestTJR_GSE_ok, &(dp->TestTJR_E) );
	dp->TA_GSE  |= dp->TestTJR_E.value.c_value;
	dp->TB_GSE  |= dp->TestTJR_E.value.c_value;
	dp->TC_GSE  |= dp->TestTJR_E.value.c_value;

	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestCBYF_GSE, dp->pTestCBYF_GSE_ok, &(dp->TestCBYF_E) );
	dp->CBYF_GSE = dp->TestCBYF_E.value.c_value;

	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTestCBBLK_GSE, dp->pTestCBBLK_GSE_ok, &(dp->TestCBBLK_E) );
	dp->CBBLK_GSE = dp->TestCBBLK_E.value.c_value;
	
	//Զ������
	for ( i=0; i<Reset_Num; i++ )
	{
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pReset_GSE[i], dp->pReset_GSE_ok[i],&(dp->Reset_E[i]) );
		
		dp->RESET_GSE |= dp->Reset_E[i].value.c_value;
	}

	//��������
	for ( i=0; i<OpS_Num; i++ )
	{
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTA_GSE[i], dp->pTA_GSE_ok[i], &(dp->TA_E[i]) );
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTB_GSE[i], dp->pTB_GSE_ok[i], &(dp->TB_E[i]) );
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTC_GSE[i], dp->pTC_GSE_ok[i], &(dp->TC_E[i]) );
		
		dp->TA_GSE  |= dp->TA_E[i].value.c_value;
		dp->TB_GSE  |= dp->TB_E[i].value.c_value;
		dp->TC_GSE  |= dp->TC_E[i].value.c_value;
	}

	for ( i=0; i<TJQ_Num; i++ )
	{
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTJQ_GSE[i], dp->pTJQ_GSE_ok[i], &(dp->TJQ_E[i]) );
		dp->TA_GSE  |= dp->TJQ_E[i].value.c_value;
		dp->TB_GSE  |= dp->TJQ_E[i].value.c_value;
		dp->TC_GSE  |= dp->TJQ_E[i].value.c_value;
	}
	
	for ( i=0; i<TJR_Num; i++ )
	{
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pTJR_GSE[i], dp->pTJR_GSE_ok[i], &(dp->TJR_E[i]) );
		dp->TA_GSE  |= dp->TJR_E[i].value.c_value;
		dp->TB_GSE  |= dp->TJR_E[i].value.c_value;
		dp->TC_GSE  |= dp->TJR_E[i].value.c_value;
	}

	dp->TZ_GSE = dp->TA_GSE | dp->TB_GSE | dp->TC_GSE;

	//ң������
	for ( i=0; i<YK_Open_NUM; i++ )
	{
		GOOSE_LINK_SOE( (SOE_VALUE *)dp->pCBYF_GSE[i], dp->pCBYF_GSE_ok[i], &(dp->CBYF_E[i]) );
		dp->CBYF_GSE |= dp->CBYF_E[i].value.c_value; 
	}

	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pCBBLK1_GSE, dp->pCBBLK1_GSE_ok, &(dp->CBBLK1_E) );
	dp->CBBLK_GSE |= dp->CBBLK1_E.value.c_value;
	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pCBBLK2_GSE, dp->pCBBLK2_GSE_ok, &(dp->CBBLK2_E) );
	dp->CBBLK_GSE |= dp->CBBLK2_E.value.c_value;

	//˫�׽�������
	GOOSE_LINK_SOE( (SOE_VALUE *)dp->pBSysST_GSE, dp->pBSysST_GSE_ok, &(dp->BSysST_E) );
	
//////////////////////////GOOSE����Ʒ�ʴ���/////////////////////////////////////////////////
	//���������
	if ( *(dp->pTest) == 1 )
	{
		//����̬������һ���Ͽɲ���������
		dp->TestReset = GSE_Test_Q( dp->pTestReset_GSE, dp->pTestReset_GSE_ok, *(dp->pTest) );
		
		dp->TestTA = GSE_Test_Q( dp->pTestTA_GSE, dp->pTestTA_GSE_ok, *(dp->pTest) );
		dp->TestTB = GSE_Test_Q( dp->pTestTB_GSE, dp->pTestTB_GSE_ok, *(dp->pTest) );
		dp->TestTC = GSE_Test_Q( dp->pTestTC_GSE, dp->pTestTC_GSE_ok, *(dp->pTest) );

		dp->TestTJQ = GSE_Test_Q( dp->pTestTJQ_GSE, dp->pTestTJQ_GSE_ok, *(dp->pTest) );
		dp->TestTJR = GSE_Test_Q( dp->pTestTJR_GSE, dp->pTestTJR_GSE_ok, *(dp->pTest) );
		

		dp->TestCBYF = GSE_Test_Q( dp->pTestCBYF_GSE, dp->pTestCBYF_GSE_ok, *(dp->pTest) );
		dp->TestCBBLK = GSE_Test_Q( dp->pTestCBBLK_GSE, dp->pTestCBBLK_GSE_ok, *(dp->pTest) );
	}
	else
	{
		//����̬��������������0
		dp->TestReset = 0;

		dp->TestTA  = 0;
		dp->TestTB  = 0;
		dp->TestTC  = 0;

		dp->TestTJQ = 0;
		dp->TestTJR = 0;

		dp->TestCBYF = 0;
		dp->TestCBBLK = 0;
	}

	dp->TA_Op = dp->TestTA;
	dp->TB_Op = dp->TestTB;
	dp->TC_Op = dp->TestTC;

	dp->TJQ_Op = dp->TestTJQ;
	dp->TJR_Op = dp->TestTJR;
	
	dp->CBYF_Op  = dp->TestCBYF;
	dp->CBBLK_Op = dp->TestCBBLK;

	dp->ResetCmd = dp->TestReset;
	
	//���̲������
	if ( *(dp->pElecTest) == 1 )
	{
		//���ش�����ޣ����̲�������0
		for ( i=0; i<Reset_Num; i++ )
		{
			dp->Reset[i] = 0;
		}

		for ( i=0; i<OpS_Num; i++ )
		{
			dp->TA[i] = 0;
			dp->TB[i] = 0;
			dp->TC[i] = 0;
		}

		for ( i=0; i<TJQ_Num; i++ )
		{
			dp->TJQ[i] = 0;
		}

		for ( i=0; i<TJR_Num; i++ )
		{
			dp->TJR[i] = 0;
		}

		for ( i=0; i<YK_Open_NUM; i++ )
		{
			dp->CBYF[i] = 0;
		}

		dp->CBBLK1 = 0;
		dp->CBBLK2 = 0;

		dp->ST_OPT = 0;
		dp->BSysST = 0;
	}
	else
	{
		//��������̬��ͣ�����̬������һ�¸��£����޲�һ����0
		for ( i=0; i<Reset_Num; i++ )
		{
			dp->Reset[i] = GSE_Bool_Q( dp->pReset_GSE[i], dp->pReset_GSE_ok[i], *(dp->pTest) );
			dp->ResetCmd |= dp->Reset[i];
		}

		for ( i=0; i<OpS_Num; i++ )
		{
			dp->TA[i] = GSE_Bool_Q( dp->pTA_GSE[i], dp->pTA_GSE_ok[i], *(dp->pTest) );
			dp->TB[i] = GSE_Bool_Q( dp->pTB_GSE[i], dp->pTB_GSE_ok[i], *(dp->pTest) );
			dp->TC[i] = GSE_Bool_Q( dp->pTC_GSE[i], dp->pTC_GSE_ok[i], *(dp->pTest) );

			dp->TA_Op |= dp->TA[i];
			dp->TB_Op |= dp->TB[i];
			dp->TC_Op |= dp->TC[i];
		}

		for ( i=0; i<TJQ_Num; i++ )
		{
			dp->TJQ[i] = GSE_Bool_Q( dp->pTJQ_GSE[i], dp->pTJQ_GSE_ok[i], *(dp->pTest) );
			dp->TJQ_Op |= dp->TJQ[i];
		}

		for ( i=0; i<TJR_Num; i++ )
		{
			dp->TJR[i] = GSE_Bool_Q( dp->pTJR_GSE[i], dp->pTJR_GSE_ok[i], *(dp->pTest) );
			dp->TJR_Op |= dp->TJR[i];
		}

		for ( i=0; i<YK_Open_NUM; i++ )
		{
			dp->CBYF[i] = GSE_Bool_Q( dp->pCBYF_GSE[i], dp->pCBYF_GSE_ok[i], *(dp->pTest) );
			dp->CBYF_Op |= dp->CBYF[i];
		}

		dp->CBBLK1 = GSE_Bool_Q( dp->pCBBLK1_GSE, dp->pCBBLK1_GSE_ok, *(dp->pTest) );
		dp->CBBLK_Op |= dp->CBBLK1;

		dp->CBBLK2 = GSE_Bool_Q( dp->pCBBLK2_GSE, dp->pCBBLK2_GSE_ok, *(dp->pTest) );
		dp->CBBLK_Op |= dp->CBBLK2;

		dp->BSysST = GSE_Bool_Q( dp->pBSysST_GSE, dp->pBSysST_GSE_ok, *(dp->pTest) );
		dp->ST_OPT = *(dp->pST_OPT);	
	}

	dp->TJR_OPT = *(dp->pTJR_OPT);
	dp->TJF_OPT = *(dp->pTJF_OPT);

///////////////////////////����������ź�/////////////////////////////////////////////////////
	
	dp->TA_Op = dp->TA_Op | dp->TJQ_Op | dp->TJR_Op | dp->TJR_OPT;
	dp->TB_Op = dp->TB_Op | dp->TJQ_Op | dp->TJR_Op | dp->TJR_OPT;
	dp->TC_Op = dp->TC_Op | dp->TJQ_Op | dp->TJR_Op | dp->TJR_OPT;
	
	dp->ProTA_Out = dp->TA_Op;
	dp->ProTB_Out = dp->TB_Op;
	dp->ProTC_Out = dp->TC_Op;
	//��������ѹ���˳�������������բ���ڣ��ǵ��������ͱ����ȫ�ౣ�����⣩
	if ( *(dp->pProBd) == 0 )
	{
		dp->ProTA_Out = 0;
		dp->ProTB_Out = 0;
		dp->ProTC_Out = 0;
	}

	dp->CBYF_Out = dp->CBYF_Op;
	//���Ƴ���ѹ���˳�������ң��
	if ( *(dp->pConBd) == 0 )
	{
		dp->CBYF_Out = 0;
	}

	dp->ST_Out = dp->ST_OPT;
	//�͵ذ����б�
	if ( *(dp->pLocalConBd) == 0 )
	{
		//�͵ذ����˳�, ��������
		dp->ST_Out = 0;
	}
	else
	{
		//�͵ذ���Ͷ��, ����ң��
		dp->CBYF_Out = 0;
	}
	
	//��բ�����������·��ģ��
	dp->TA_Out = dp->ProTA_Out | dp->CBYF_Out | dp->ST_Out | *(dp->pBreakPh) | dp->TJF_OPT;
	dp->TB_Out = dp->ProTB_Out | dp->CBYF_Out | dp->ST_Out | *(dp->pBreakPh) | dp->TJF_OPT;
	dp->TC_Out = dp->ProTC_Out | dp->CBYF_Out | dp->ST_Out | *(dp->pBreakPh) | dp->TJF_OPT;

	dp->TZ_Out = dp->TA_Out | dp->TB_Out | dp->TC_Out;

	//��բ���ʱ�䶯��
	dp->TZ_Op = dp->TA_Op | dp->TB_Op | dp->TC_Op | dp->TJQ_Op | dp->TJR_Op |  dp->CBYF_Op 
	          | dp->TJR_OPT | dp->TJF_OPT  | dp->ST_OPT;
	dp->TZ_LONGTIME = Dlyon(&(dp->status1), &(dp->time_save1), dp->TZ_Op, tick_1000ms);

	//�����������һ��
	dp->ST_Else = dp->CBYF_Op | dp->ST_OPT;
	//STJ����
	dp->STJ_New = dp->ST_Else | dp->BSysST;
    //ST����ʱ������ʱ������1s�ĸߵ�ƽ�ź�
	PULSE_TRIG(&(dp->STJ_New), &(dp->STJ_Old), &(dp->STJ_CNT), lev2_1S, &(dp->STJ), 1);

//////////////////////////˫ϵͳ���ӱȽ�//////////////////////////////////////////////////////
#ifndef MAIN_DSP
	two_sys_cmp( dp->TZ_Out, *(dp->pTZ_ELSE), &tmp, &(dp->CMP_CNT1), lev2_10S );
	dp->CMP_ERR |= tmp;
	two_sys_cmp( dp->CBBLK_Op, *(dp->pCBBLK_ELSE), &tmp, &(dp->CMP_CNT2), lev2_10S );
	dp->CMP_ERR |= tmp;
#endif
//////////////////////////�����ź�////////////////////////////////////////////////////////////

	
////////////////////////���ڽӵ�ز�//////////////////////////////////////////////////////////
	//get_relay_stat(dp->TZ_1, dp->HWJA_OPT, &(dp->TZA_RELAY_DZ));
	//get_relay_stat(dp->TZ_1, dp->HWJB_OPT, &(dp->TZB_RELAY_DZ));
	//get_relay_stat(dp->TZ_1, dp->HWJC_OPT, &(dp->TZC_RELAY_DZ));
}

