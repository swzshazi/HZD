/* FileName: CloseCmd220.h */
#ifndef _CloseCmd220_H
#define _CloseCmd220_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"
//#include "symbol_type_defines.h"

#define  ReClose_NUM   4      // 保护重合闸数目
#define  YK_Close_NUM  4      // 遥合断路器数目

/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint32 	start;
	Uint8	*pElecTest;                    // 带电检修
	Uint8	*pTest;                        // 检修状态
	Uint8	*pProBd;                       // 保护出口压板
	Uint8	*pConBd;                       // 控制出口压板
	Uint8	*pLocalConBd;                  // 就地控制把手
		

	Uint8	*pRECLS_GSE[ReClose_NUM];      // 保护重合闸值
	Uint8	*pRECLS_GSE_ok[ReClose_NUM];   // 保护重合闸品质

	Uint8	*pCBYH_GSE[YK_Close_NUM];      // 遥合断路器
	Uint8	*pCBYH_GSE_ok[YK_Close_NUM];

	Uint8 	*pBSysSH_GSE;                  // 接入B套手合
	Uint8 	*pBSysSH_GSE_ok;               

	Uint8 	*pSH_OPT;                      // 手合开入
	Uint8 	*pSTJ;                         // STJ输入

	Uint8	*pTestCLS_GSE;                 // 测试仪保护重合闸值
	Uint8	*pTestCLS_GSE_ok;              // 测试仪保护重合闸品质

	Uint8	*pTestCBYH_GSE;                // 测试仪遥合断路器值
	Uint8	*pTestCBYH_GSE_ok;             // 测试仪遥合断路器品质
	
	Uint8	*pHZ_ELSE;                      // 另一CPU合闸

	Uint32	checksum;
	Uint8	check_err;

	/* parameter  */
	
	/* output variables :*/
	SOE_VALUE	RECLS_E[ReClose_NUM];     // 保护重合闸SOE
	SOE_VALUE	CBYH_E[YK_Close_NUM];     // 遥控合闸SOE
	
	SOE_VALUE	TestCLS_E;                // 测试仪保护重合闸SOE
	SOE_VALUE	TestCBYH_E;                // 测试仪遥控断路器SOE
	
	SOE_VALUE	BSysSH_E;                 // B套手合SOE
	
	Uint8	HZ_LONGTIME;                  // 合闸长时间动作

	Uint8   QD;

	Uint8	RECLS_Op;                     // 保护合闸处理结果
	Uint8	RECLS_Out;                    // 保护合闸输出
	Uint8	CBYH_Op;                      // 测控合闸处理结果
	Uint8	CBYH_Out;                     // 测控合闸输出
	
	Uint8   SH_Else;                      // 手合输出--给另一套
	Uint8   SHJ;                          // SHJ信号--A或B套手合展宽

	Uint8   SH_Flag;                      // 手合标志
	Uint8   ST_Flag;                      // 手跳标志
	Uint8   KKJ;                          // KKJ合后
	
	Uint8	HZ_Op;                       // 合闸动作
	Uint8	HZ_Out;                       // 合闸输出-合断路器模块

	Uint8	RECLS_GSE;                    // Goose保护重合闸命令反馈
	Uint8	CBYH_GSE;                     // Goose测控合闸命令反馈

	Uint8	CMP_ERR;
	Uint8 	HA_RELAY_DZ;			//合闸接点动作
	Uint8 	HB_RELAY_DZ;			//合闸接点动作
	Uint8 	HC_RELAY_DZ;			//合闸接点动作
	

	//private
	Uint8	RECLS[ReClose_NUM];         // 重合闸处理情况
	Uint8   CBYH[YK_Close_NUM];         // 遥合处理情况
	
	Uint8   SH_OPT;						// 手合处理结果
	Uint8   SH_Out;						// 手合输出
	Uint8   BSysSH;						// B套手合处理情况
	Uint8   SHJ_Old;                    // A或B套手合
	Uint8   SHJ_New;                    // A或B套手合
	Uint16	SHJ_CNT;                    // SHJ计数

	Uint8	TestCLS;                    // 测试仪保护重合闸处理情况
	Uint8	TestCBYH;                   // 测试仪遥合断路器处理情况 

	Uint16  CMP_CNT;
	
	Uint32 	time_save1;
	Uint8  	status1;
	
} CloseCmd220;


extern  CloseCmd220  *newCloseCmd220(Component *parent, const char *name);
extern int  initCloseCmd220(CloseCmd220 *dp);

#endif
