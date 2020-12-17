/* FileName: BlkReClsLog.h */
#ifndef _BlkReClsLog_H
#define _BlkReClsLog_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"
//#include "symbol_type_defines.h"

#define  BlkReCls_NUM  3      // 闭锁保护重合闸数目

/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint8	*pElecTest;                       // 带电检修
	Uint8	*pTest;                           // 检修状态		

	Uint8	*pBlkReCLS_GSE[BlkReCls_NUM];     // GOOSE闭锁重合闸值
	Uint8	*pBlkReCLS_GSE_ok[BlkReCls_NUM];  // GOOSE闭锁重合闸品质

	Uint8	*pTestBlkReCLS_GSE;               // 测试仪GOOSE闭锁重合闸值
	Uint8	*pTestBlkReCLS_GSE_ok;            // 测试仪GOOSE闭锁重合闸品质

	Uint8	*pCBYF;                           // 遥分断路器
	Uint8	*pCBYH;                           // 遥合断路器

	Uint8 	*pSH_OPT;                         // 手合开入
	Uint8 	*pST_OPT;                         // 手跳开入
	Uint8 	*pTJR_OPT;                        // TJR开入
	Uint8 	*pTJF_OPT;                        // TJF开入
	
	Uint8 	*pGS_TJR;                         // GOOSE TJR

	Uint8 	*pBSysBlkReCls_GSE;               // 接入另一套闭重
	Uint8 	*pBSysBlkReCls_GSE_ok;               

	/* parameter  */
	
	/* output variables :*/
	SOE_VALUE	BlkReCLS_E[BlkReCls_NUM];     // GOOSE闭锁重合闸SOE
	SOE_VALUE	TestBlkReCLS_E;               // 测试仪GOOSE闭锁重合闸SOE
	SOE_VALUE	BSysBlkReCls_E;               // B套闭锁重合闸SOE

	Uint8   BlkReCls_Out; 	                  // 闭锁本套重合闸
	Uint8   BlkReCls_Bsys; 	                  // 闭锁另一套重合闸

	//private
	Uint8	GsBlkReCLS[BlkReCls_NUM];         // GOOSE闭锁重合闸
	Uint8	BlkReCLS_Op;
	Uint8	TestBlkReCLS;                     // 测试仪闭锁重合闸
	Uint8   SH_OPT;                           // 手合开入
	Uint8   ST_OPT;                           // 手跳开入
	Uint8	BSysBlkReCls;					  // B套闭锁重合闸

	Uint8 	PWRUP;                            // 装置上电
	Uint16	PWRUP_CNT;                        // 装置上电时间计数
	
} BlkReClsLog;


extern  BlkReClsLog  *newBlkReClsLog(Component *parent, const char *name);
extern int  initBlkReClsLog(BlkReClsLog *dp);

#endif
