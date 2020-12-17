/* File Description   
*  FileName: OutDPosGs.c -- ���ܿ����ⲿ������˫λ��Gs����Ԫ��     
*  Fuction: 
*       ���ܣ���ȡ������·������բ˫λ�ò�������ڵ������������߼�������λ��
*       ���룺˫λ��Gsֵ��Ʒ��
*       �����������������˫λ��ֵ���߼�������˫λ��ֵ
*  apply: ���ܻ�����
*  author: ZYB 
*  data:  20200610
*/

#include <stdlib.h>
#include "hzplatform.h"
#include "OutDPosGs.h"
#include "CommFun.h"

void OutDPosGs_task( OutDPosGs *dp);

int initOutDPosGs( OutDPosGs *dp);


OutDPosGs *newOutDPosGs(Component *parent, const char *name)
{
	OutDPosGs *dp;
	
	dp = (OutDPosGs *)calloc(1, sizeof(OutDPosGs));
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "OutDPos";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent = (int (*)(void *))initOutDPosGs;

	registerComponent( (Component*)dp);
	
	registerVarIn( (Component*)dp, (void**)&(dp->pTest), "pTest", T_BIT, LEVEL1 );			         // װ�ü���̬
	
	registerVarIn( (Component*)dp, (void**)&(dp->pHwj_GSE), "pHwj_GSE__AB", T_UINT8, LEVEL1 );	         // ��λGsֵ
	registerVarIn( (Component*)dp, (void**)&(dp->pHwj_GSE_ok), "pHwj_GSE__AB_ok", T_UINT8, LEVEL1 );     
	
	registerVarIn( (Component*)dp, (void**)&(dp->pTwj_GSE), "pTwj_GSE__AB", T_UINT8, LEVEL1 );	         // ��λGsֵ
	registerVarIn( (Component*)dp, (void**)&(dp->pTwj_GSE_ok), "pTwj_GSE__AB_ok", T_UINT8, LEVEL1 );     

//////////////////////////////////////////////////////////////////////////////////////////////////////

	registerVarOut( (Component*)dp, (void*)&(dp->Hwj_Lock), "Hwj_Lock", T_UINT8, LEVEL1 );	 // ��λ--������������
	registerVarOut( (Component*)dp, (void*)&(dp->Twj_Lock), "Twj_Lock", T_UINT8, LEVEL1 );	 // ��λ--������������

	registerVarOut( (Component*)dp, (void*)&(dp->Hwj_Logic), "Hwj_Logic", T_UINT8, LEVEL1 );	 // ��λ--�߼���
	registerVarOut( (Component*)dp, (void*)&(dp->Twj_Logic), "Twj_Logic", T_UINT8, LEVEL1 );	 // ��λ--�߼���

	return dp;
}

INIT_CODE
int initOutDPosGs(OutDPosGs *dp)
{
	setTask( 2, OutDPosGs_task, dp);

	return 0;
}


#pragma CODE_SECTION(OutDPosGs_task,".rtm_code")

void OutDPosGs_task(OutDPosGs *dp)
{
	Uint8 quality1, quality2, test;

	test = *(dp->pTest);
	quality1 = *(dp->pHwj_GSE_ok);
	quality2 = *(dp->pTwj_GSE_ok);

	//�߼���λ���б�--����һ�¸��£����޲�һ�±��֣���������
	if ( ((quality1&0x08) == 0x08) && ((quality1 & 0x04) == 0x04)  && (((quality1 & 0x02)>>1) == test) )
	{
		dp->Hwj_Logic = *(dp->pHwj_GSE);
	}

	if ( ((quality2&0x08) == 0x08) && ((quality2 & 0x04) == 0x04)  && (((quality2 & 0x02)>>1) == test) )
	{
		dp->Twj_Logic = *(dp->pTwj_GSE);
	}

	//������λ���б�--λ�ü���̬ʱ��0������̬���£���������
	if( ( (quality1&0x08) == 0x08 ) && ( (quality1 & 0x04) == 0x04 ) )
	{
		//����GsΪ����̬
		if ( (quality1 & 0x02) == 0x02 )
		{
			dp->Hwj_Lock = 0;
		}
		else
		{
			dp->Hwj_Lock = *(dp->pHwj_GSE);
		}	
	} 

	if( ( (quality2&0x08) == 0x08 ) && ( (quality2 & 0x04) == 0x04 ) )
	{
		//����GsΪ����̬
		if ( (quality2 & 0x02) == 0x02 )
		{
			dp->Twj_Lock = 0;
		}
		else
		{
			dp->Twj_Lock = *(dp->pTwj_GSE);
		}	
	} 
}

