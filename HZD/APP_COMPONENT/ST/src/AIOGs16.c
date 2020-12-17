/* File Description   
*  FileName: AIOGs16.c -- 模拟量Gs元件        
*  Fuction: 
*       功能：获取模拟量Gs并输出
*       输入：8路模拟量Gs值和品质
*       输出：8路模拟量Gs值
*  apply: 智能化开关
*  author: ZYB 
*  data:  20200521
*/

#include <stdlib.h>
#include "hzplatform.h"
#include "AIOGs16.h"
#include "CommFun.h"

void AIOGs16_task( AIOGs16 *dp);

int initAIOGs16( AIOGs16 *dp);


AIOGs16 *newAIOGs16(Component *parent, const char *name)
{
	Uint8 i;
	char tp_str[150];

	AIOGs16 *dp;
	
	dp = (AIOGs16 *)calloc(1, sizeof(AIOGs16));
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "AIOGs16";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent = (int (*)(void *))initAIOGs16;

	registerComponent( (Component*)dp);
	
	for ( i=0; i<AIOGs_Num; i++ )
	{
		sprintf(tp_str, "pAIO_GSE%d", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pAIO_GSE[i]), tp_str, T_FLOAT, LEVEL2 );        //模拟量Gs值

		sprintf(tp_str, "pAIO_GSE%d_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pAIO_GSE_ok[i]), tp_str, T_UINT8, LEVEL2 );     //模拟量Gs品质

	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////

	for ( i=0; i<AIOGs_Num; i++ )
	{
		sprintf(tp_str, "AIO_GSE%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->AIO_GSE[i]), tp_str, T_FLOAT, LEVEL1 );	  //模拟量Gs值
	}

	return dp;
}

INIT_CODE
int initAIOGs16(AIOGs16 *dp)
{
	setTask( 2, AIOGs16_task, dp);

	return 0;
}


#pragma CODE_SECTION(AIOGs16_task,".rtm_code")

void AIOGs16_task(AIOGs16 *dp)
{
	Uint8 i;
	Uint8 quality;

	for ( i=0; i<AIOGs_Num; i++ )
	{
		quality = *(dp->pAIO_GSE_ok[i]);

		//接收软压板使能且链路正常
		if( ( (quality&0x08) == 0x08 ) && ( (quality & 0x04) == 0x04 ) )
		{
			dp->AIO_GSE[i] = *(dp->pAIO_GSE[i]);
		} 
		else
		{
			dp->AIO_GSE[i] = 0;
		}
	}	
}

