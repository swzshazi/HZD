/* FileName: SysSwapDeal.h */
#ifndef _SysSwapDeal_H
#define _SysSwapDeal_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"


/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint8  *pAtB_HandH;             // A套至B套手合
	Uint8  *pAtB_HandH_ok;  
	Uint8  *pAtB_HandF;             // A套至B套手跳
	Uint8  *pAtB_HandF_ok;
	Uint8  *pAtB_LockRcls;          // A套至B套闭重
	Uint8  *pAtB_LockRcls_ok;

	Uint8  *pBtA_HandH;             // B套至A套手合
	Uint8  *pBtA_HandH_ok;  
	Uint8  *pBtA_HandF;             // B套至A套手跳
	Uint8  *pBtA_HandF_ok;
	Uint8  *pBtA_LockRcls;          // B套至A套闭重
	Uint8  *pBtA_LockRcls_ok;

	/* output variables :*/
	Uint8	AtB_HandH;              // A套至B套手合
	Uint8	AtB_HandH_ok; 
	Uint8   AtB_HandF;              // A套至B套手跳
	Uint8   AtB_HandF_ok;
	Uint8   AtB_LockRcls;           // A套至B套闭重
	Uint8   AtB_LockRcls_ok;

	Uint8   BtA_HandH;             // B套至A套手合
	Uint8   BtA_HandH_ok;  
	Uint8   BtA_HandF;             // B套至A套手跳
	Uint8   BtA_HandF_ok;
	Uint8   BtA_LockRcls;          // B套至A套闭重
	Uint8   BtA_LockRcls_ok;
	
	/* prameter variables :*/
	

	//private

	
} SysSwapDeal;


extern  SysSwapDeal  *newSysSwapDeal(Component *parent, const char *name);
extern int  initSysSwapDeal(SysSwapDeal *dp);

#endif
