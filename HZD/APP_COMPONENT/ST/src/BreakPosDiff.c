/* File Description   
*  FileName: BreakPosDiff.c -- ��·��λ�ò�һ�´���        
*  Fuction: 
*       ���ܣ���·��λ�ò�һ�´���
*       ���룺�����·��λ�á�KKJ�Ϻ�
*       �������·��λ�ò�һ�¸澯����·����ȫ�ౣ�����¹��ܵ�
*  apply: ���ܻ�����
*  author: ZYB 
*  data:  20200529
*/

#include <stdlib.h>
#include "hzplatform.h"
#include "BreakPosDiff.h"


void BreakPosDiff_task( BreakPosDiff *dp);

int initBreakPosDiff( BreakPosDiff *dp);

#pragma DATA_SECTION(BreakPosDiff_stru,".rtm_data")
BreakPosDiff BreakPosDiff_stru;

BreakPosDiff *newBreakPosDiff(Component *parent, const char *name)
{
	Uint16 i=0;
	char tp_str[150];
	BreakPosDiff *dp;
	
	dp = &BreakPosDiff_stru;
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "PosDiff";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent =  (int (*)(void *))initBreakPosDiff;

	registerComponent( (Component*)dp);

	registerVarIn( (Component*)dp, (void**)&(dp->pKKJ), "pKKJ", T_BIT, LEVEL1 );		        // KKJ�Ϻ�״̬

	registerVarIn( (Component*)dp, (void**)&(dp->pHwj[0]), "pHwjA", T_UINT8, LEVEL1 );          // A���·����λ
	registerVarIn( (Component*)dp, (void**)&(dp->pHwj[1]), "pHwjB", T_UINT8, LEVEL1 );          // B���·����λ
	registerVarIn( (Component*)dp, (void**)&(dp->pHwj[2]), "pHwjC", T_UINT8, LEVEL1 );          // C���·����λ

	registerVarIn( (Component*)dp, (void**)&(dp->pTwj[0]), "pTwjA", T_UINT8, LEVEL1 );          // A���·����λ
	registerVarIn( (Component*)dp, (void**)&(dp->pTwj[1]), "pTwjB", T_UINT8, LEVEL1 );          // B���·����λ
	registerVarIn( (Component*)dp, (void**)&(dp->pTwj[2]), "pTwjC", T_UINT8, LEVEL1 );          // C���·����λ


	registerVarIn( (Component*)dp, (void**)&(dp->pBreakPh_ELSE), "pBreakPh_ELSE", T_BIT, LEVEL1 );   // ��һCPU��ȫ�ౣ��

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	 // ���಻һ�¸澯��ʱʱ��-��λ��s
	registerParameter((Component*)dp,(void*)&(dp->PosDiff_Delay), "DiffDelay min=0.01 max=100 option=1 default=0.5 unit=s", T_FLOAT);
	 // ��ȫ�ౣ����ʱʱ��-��λ��s
	registerParameter((Component*)dp,(void*)&(dp->BreakPh_Delay), "BreakPh_Delay min=0.01 max=100 default=3 unit=s", T_FLOAT);
	// �¹�����ʱʱ��-��λ��s
	registerParameter((Component*)dp,(void*)&(dp->FaultTotal_Delay), "FaultTotal_Delay min=0.01 max=100 option=1  default=0.2 unit=s", T_FLOAT);

	registerVarOut( (Component*)dp, (void*)&(dp->BreakPosDiff), "Diff", T_BIT, LEVEL1 );	// ��·��λ�ò�һ�¸澯
	registerVarOut( (Component*)dp, (void*)&(dp->BreakPhPro), "BreakPhPro", T_BIT, LEVEL1 );	    // ��·����ȫ�ౣ��
	registerVarOut( (Component*)dp, (void*)&(dp->FaultTotal), "FaultTotal", T_BIT, LEVEL1 );	    // �¹���

	registerVarOut( (Component*)dp, (void*)&(dp->CMP_ERR), "CMP_ERR", T_BIT, LEVEL1 );				//˫�ױȽϳ���		
	registerVarOut( (Component*)dp, (void*)&(dp->check_err), "check_err", T_BIT, LEVEL1 );          //ָ��Ƚϳ���

	return dp;
}


void BreakPosDiff_check_task(BreakPosDiff *dp)
{
	if(dp->check_err == 0)
	{
		dp->check_err = check_set_pointer((Uint32)(&dp->start),(Uint32)(&dp->checksum));
	}
}


INIT_CODE
int initBreakPosDiff(BreakPosDiff *dp)
{
	Uint16 i=0;


	dp->CMP_CNT = 0;
	dp->CMP_ERR = 0;
	
	dp->status1 = 0;
	dp->time_save1 = 0;

	dp->status2 = 0;
	dp->time_save2 = 0;

	dp->status3 = 0;
	dp->time_save3 = 0;

	dp->status4 = 0;
	dp->time_save4 = 0;

	dp->checksum = 0;
	dp->check_err = 0;
	
	init_check_set_pointer( (Uint32)(&dp->start), (Uint32)(&dp->checksum) );
	
	setTask( 2, BreakPosDiff_task, dp);
	setTask( 4, BreakPosDiff_check_task, dp);

	return 0;
}



#pragma CODE_SECTION(BreakPosDiff_task,".rtm_code")
void BreakPosDiff_task(BreakPosDiff *dp)
{
	Uint16 i=0;

////////////////////////////��ȡ��ֵ����////////////////////////////////////////////////////
	dp->PosDiff_Num    = dp->PosDiff_Delay * tick_1000ms;     //��ʱת�������
	dp->BreakPh_Num    = dp->BreakPh_Delay * tick_1000ms;     //��ʱת�������
	dp->FaultTotal_Num = dp->FaultTotal_Delay * tick_1000ms;  //��ʱת�������
	

//////////////////////////�߼�����/////////////////////////////////////////////////////////

	// ����λ�ò�һ�¸澯
	dp->AnyDis = *(dp->pTwj[0]) | *(dp->pTwj[1]) | *(dp->pTwj[2]);
	dp->AnyCls = *(dp->pHwj[0]) | *(dp->pHwj[1]) | *(dp->pHwj[2]);
	dp->ret1 = dp->AnyDis & dp->AnyCls;
	
	dp->BreakPosDiff = Dlyon(&(dp->status2), &(dp->time_save2), dp->ret1, dp->PosDiff_Num);		// ���಻һ��

	// ��ȫ�ౣ��
	for ( i=0; i<Pos_NUM; i++ )
	{
		dp->PosRet[i] = *(dp->pTwj[i]) + ( *(dp->pHwj[i]) << Dis_Value );
		
		if ( ( dp->PosRet[i] == Dis_Value ) ||  ( dp->PosRet[i] == Cls_Value ) )
		{
			dp->DisRet[i] = *(dp->pTwj[i]);
			dp->ClsRet[i] = *(dp->pHwj[i]);
		}
		else
		{
			dp->DisRet[i] = 0;
			dp->ClsRet[i] = 0;
		}
	}
	
	dp->AnyDis = dp->DisRet[0] | dp->DisRet[1] | dp->DisRet[2];
	dp->AnyCls = dp->ClsRet[0] | dp->ClsRet[1] | dp->ClsRet[2];
	dp->ret2     = dp->AnyDis & dp->AnyCls;

	dp->BreakPhPro = Dlyon(&(dp->status3), &(dp->time_save3), dp->ret2, dp->BreakPh_Num);		// ��ȫ�ౣ��
	
	// �¹���
	dp->ret3  = dp->AnyDis & (*(dp->pKKJ));
	
	dp->FaultTotal = Dlyon(&(dp->status4), &(dp->time_save4), dp->ret3, dp->FaultTotal_Num);    // �¹���

//////////////////////////˫ϵͳ���ӱȽ�////////////////////////////////////////////////////////////
#ifndef MAIN_DSP
	two_sys_cmp( dp->BreakPhPro, *dp->pBreakPh_ELSE, &(dp->CMP_ERR), &(dp->CMP_CNT), lev2_10S );
#endif
//////////////////////////��������//////////////////////////////////////////////////////////////////
	//dp->QD = dp->HZ;
////////////////////////���ڽӵ�ز�////////////////////////////////////////////////////////////////
	//get_relay_stat(dp->HZ, dp->TWJA_OPT, &(dp->HA_RELAY_DZ));
	//get_relay_stat(dp->HZ, dp->TWJB_OPT, &(dp->HB_RELAY_DZ));
	//get_relay_stat(dp->HZ, dp->TWJC_OPT, &(dp->HC_RELAY_DZ));
}
