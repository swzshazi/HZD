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
