/* File Description   
*  FileName: SwPos.c -- ���ܿ��ص�բλ�ô���Ԫ��     
*  Fuction: 
*       ���ܣ���ȡ��բλ�ò�ת��վ�ز����������ģ��
*       ���룺��բ1~8λ��Gsֵ��Ʒ��
*       �������բλ��ֵ��GsƷ��
*  apply: ���ܻ�����
*  author: ZYB 
*  data:  20200811
*/

#include <stdlib.h>
#include "hzplatform.h"
#include "SwPos.h"
#include "CommFun.h"

void SwPos_task( SwPos *dp);

int initSwPos( SwPos *dp);


SwPos *newSwPos(Component *parent, const char *name)
{
	Uint8 i;
	char tp_str[150];
	
	SwPos *dp;
	
	dp = (SwPos *)calloc(1, sizeof(SwPos));
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "SwPos";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent = (int (*)(void *))initSwPos;

	registerComponent( (Component*)dp);
	
	for ( i = 0; i < HdSwPosNum; i++ )
	{
		sprintf(tp_str, "pSw%dDis__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pSwDis[i]), tp_str, T_BIT, LEVEL1 );      // ��բ��λ 
		sprintf(tp_str, "pSw%dDis__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pSwDis_ok[i]), tp_str, T_UINT8, LEVEL1 );

		sprintf(tp_str, "pSw%dCls__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pSwCls[i]), tp_str, T_BIT, LEVEL1 );      // ��բ��λ
		sprintf(tp_str, "pSw%dCls__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pSwCls_ok[i]), tp_str, T_UINT8, LEVEL1 );
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////

	for ( i = 0; i < HdSwPosNum; i++ )
	{
		sprintf(tp_str, "Sw%dDis", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->SwDis[i]), tp_str, T_BIT, LEVEL1 );	    //��բ��λ
		
		sprintf(tp_str, "Sw%dCls", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->SwCls[i]), tp_str, T_BIT, LEVEL1 );	    //��բ��λ
	}
	
	return dp;
}

INIT_CODE
int initSwPos(SwPos *dp)
{
	setTask( 2, SwPos_task, dp);

	return 0;
}


#pragma CODE_SECTION(SwPos_task,".rtm_code")


void SwPos_task(SwPos *dp)
{
	Uint8 i;

	// ��·��λ�ô���
	for ( i = 0; i < HdSwPosNum; i++ )
	{
		dp->SwDis[i] = *(dp->pSwDis[i]);
		
		dp->SwCls[i] = *(dp->pSwCls[i]);
	
	}
}
