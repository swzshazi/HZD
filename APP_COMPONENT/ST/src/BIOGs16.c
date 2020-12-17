/* File Description   
*  FileName: BIOGs16.c -- 开关量Gs元件        
*  Fuction: 
*       功能：获取16路开关量Gs并输出
*       输入：16路开关量Gs值和品质
*       输出：16路开关量Gs值
*  apply: 智能化开关
*  author: ZYB 
*  data:  20200521
*/

#include <stdlib.h>
#include "hzplatform.h"
#include "BIOGs16.h"
#include "CommFun.h"

void BIOGs16_task( BIOGs16 *dp);

int initBIOGs16( BIOGs16 *dp);


BIOGs16 *newBIOGs16(Component *parent, const char *name)
{
	Uint8 i;
	char tp_str[150];

	BIOGs16 *dp;
	
	dp = (BIOGs16 *)calloc(1, sizeof(BIOGs16));
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "BIOGs16";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent = (int (*)(void *))initBIOGs16;

	registerComponent( (Component*)dp);
	
	for ( i=0; i<BIOGs_Num; i++ )
	{
		sprintf(tp_str, "pBIO_GSE%d", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBIO_GSE[i]), tp_str, T_BIT, LEVEL2 );        //开关量Gs值

		sprintf(tp_str, "pBIO_GSE%d_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBIO_GSE_ok[i]), tp_str, T_UINT8, LEVEL2 );   //开关量Gs品质

	}
	
//////////////////////////////////////////////////////////////////////////////////////////////////////

	for ( i=0; i<BIOGs_Num; i++ )
	{
		sprintf(tp_str, "BIO_GSE%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BIO_GSE[i]), tp_str, T_BIT, LEVEL1 );	  //开关量Gs值
	}

	return dp;
}

INIT_CODE
int initBIOGs16(BIOGs16 *dp)
{
	setTask( 2, BIOGs16_task, dp);

	return 0;
}


#pragma CODE_SECTION(BIOGs16_task,".rtm_code")

void BIOGs16_task(BIOGs16 *dp)
{
	Uint8 i;
	Uint8 quality;

	for ( i=0; i<BIOGs_Num; i++ )
	{
		quality = *(dp->pBIO_GSE_ok[i]);

		//接收软压板使能且链路正常
		if( ( (quality&0x08) == 0x08 ) && ( (quality & 0x04) == 0x04 ) )
		{
			dp->BIO_GSE[i] = *(dp->pBIO_GSE[i]);
		} 
		else
		{
			dp->BIO_GSE[i] = 0;
		}
	}	
}

