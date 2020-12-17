/* FileName: TripCmd220.h */
#ifndef _TripCmd220_H
#define _TripCmd220_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"


#define  OpS_Num    3     // 单跳单合数目
#define  TJQ_Num    3     // TJQ三跳数目--启重合启失灵
#define  TJR_Num    10    // TJR永跳数目--闭重合启失灵
#define  Reset_Num  2     // 复归数目

#define  YK_Open_NUM  4     // 遥分断路器数目

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

	SOE_VALUE	*pReset_OPT;               // 复归开入
	Uint8	    *pReset_GSE[Reset_Num];    // 远方复归
	Uint8	    *pReset_GSE_ok[Reset_Num];    

	Uint8	*pTA_GSE[OpS_Num];             // 保护跳A值
	Uint8	*pTA_GSE_ok[OpS_Num];          // 保护跳A品质
	
	Uint8	*pTB_GSE[OpS_Num];             // 保护跳B值
	Uint8	*pTB_GSE_ok[OpS_Num];          // 保护跳B品质

	Uint8	*pTC_GSE[OpS_Num];             // 保护跳C值
	Uint8	*pTC_GSE_ok[OpS_Num];          // 保护跳C品质

	Uint8	*pTJQ_GSE[TJQ_Num];             // 保护TJQ跳值
	Uint8	*pTJQ_GSE_ok[TJQ_Num];          // 保护TJQ跳品质

	Uint8	*pTJR_GSE[TJR_Num];             // 保护TJR跳值
	Uint8	*pTJR_GSE_ok[TJR_Num];          // 保护TJR跳品质

	Uint8 	*pTJF_OPT;                      // 非电量保护TJF开入
	Uint8	*pTJR_OPT;                      // 电量保护TJR开入

	Uint8 	*pBreakPh;                      // 本体非全相保护

	Uint8	*pCBYF_GSE[YK_Open_NUM];        // 遥分断路器
	Uint8	*pCBYF_GSE_ok[YK_Open_NUM];
	
	Uint8 	*pBSysST_GSE;                   // 接入B套手跳
	Uint8 	*pBSysST_GSE_ok;               
	
	Uint8 	*pST_OPT;                       // 手跳开入

	Uint8	*pTestTA_GSE;                   // 测试仪保护跳A值
	Uint8	*pTestTA_GSE_ok;                // 测试仪保护跳A品质

	Uint8	*pTestTB_GSE;                   // 测试仪保护跳B值
	Uint8	*pTestTB_GSE_ok;                // 测试仪保护跳B品质

	Uint8	*pTestTC_GSE;                   // 测试仪保护跳C值
	Uint8	*pTestTC_GSE_ok;                // 测试仪保护跳C品质

	Uint8	*pTestTJQ_GSE;                  // 测试仪保护TJQ跳闸值
	Uint8	*pTestTJQ_GSE_ok;               // 测试仪保护TJQ跳闸品质

	Uint8	*pTestTJR_GSE;                  // 测试仪保护TJR跳闸值
	Uint8	*pTestTJR_GSE_ok;               // 测试仪保护TJR跳闸品质
	
	Uint8	*pTestCBYF_GSE;                 // 测试仪遥控跳闸值
	Uint8	*pTestCBYF_GSE_ok;              // 测试仪遥控跳闸品质

	Uint8	*pTestReset_GSE;                 // 测试仪复归
	Uint8	*pTestReset_GSE_ok;              // 测试仪复归品质
	
	Uint8	*pTZ_ELSE;                      // 另一CPU跳闸

	Uint8	*pCBBLK1_GSE;                   // 断路器解闭锁1
	Uint8	*pCBBLK1_GSE_ok;                // 断路器解闭锁1品质
	
	Uint8	*pCBBLK2_GSE;                   // 断路器解闭锁2	
	Uint8	*pCBBLK2_GSE_ok;                // 断路器解闭锁2品质
	
	Uint8	*pTestCBBLK_GSE;                // 测试仪断路器解闭锁值	
	Uint8	*pTestCBBLK_GSE_ok;             // 测试仪断路器解闭锁品质

	Uint8	*pCBBLK_ELSE;                   // 另一CPU解闭锁

	Uint32  checksum;
	Uint8	check_err;

	/* output variables :*/
	Uint8	ResetCmd;      //复归命令

	SOE_VALUE	Reset_E[Reset_Num];         // 复归 SOE

	SOE_VALUE	TA_E[OpS_Num];              // 跳A SOE
	SOE_VALUE	TB_E[OpS_Num];              // 跳B SOE
	SOE_VALUE	TC_E[OpS_Num];              // 跳C SOE
	
	SOE_VALUE	TJQ_E[TJQ_Num];             // TJQ SOE
	SOE_VALUE	TJR_E[TJR_Num];             // TJR SOE

	SOE_VALUE	CBYF_E[YK_Open_NUM];        // 遥控分闸SOE
	
	SOE_VALUE	TestReset_E;                  // 测试仪复归 SOE

	SOE_VALUE	TestTA_E;                   // 测试仪跳A SOE
	SOE_VALUE	TestTB_E;                   // 测试仪跳B SOE
	SOE_VALUE	TestTC_E;                   // 测试仪跳C SOE

	SOE_VALUE	TestTJQ_E;                  // 测试仪TJQ SOE
	SOE_VALUE	TestTJR_E;                  // 测试仪TJR SOE
	
	SOE_VALUE	TestCBYF_E;                 // 测试仪遥控分闸 SOE

	Uint8	TZ_LONGTIME;                    // 跳闸长时间动作

	SOE_VALUE	CBBLK1_E;                   // 断路器解闭锁1 SOE
	SOE_VALUE	CBBLK2_E;                   // 断路器解闭锁2 SOE
	SOE_VALUE	TestCBBLK_E;                // 断路器测试仪解闭锁 SOE
	
	SOE_VALUE	BSysST_E;                    // B套手跳SOE
	

	Uint8   QD;                             // 启动
	Uint8	TJQ_Op;                         // TJQ结果
	Uint8	TJR_Op;                         // TJR结果
	Uint8	TJR_OPT;					    // 电缆TJR跳闸
	Uint8	TJF_OPT;                        // 电缆TJF跳闸   
	
	Uint8	TA_Op;                          // 保护TA动作
	Uint8	TB_Op;                          // 保护TB动作
	Uint8	TC_Op;                          // 保护TC动作

	Uint8	ProTA_Out;                      // 保护TA输出
	Uint8	ProTB_Out;                      // 保护TB输出
	Uint8	ProTC_Out;                      // 保护TC输出

	Uint8   ST_Else;                        // 手跳输出--给另一套
	Uint8	STJ;                            // STJ信号

	Uint8	TA_Out;                         // TA输出-跳断路器模块
	Uint8	TB_Out;                         // TB输出-跳断路器模块
	Uint8	TC_Out;                         // TC输出-跳断路器模块
	
	Uint8	TZ_Op;                          // 任一跳闸动作
	Uint8	TZ_Out;                         // 任一跳闸结果
	
	Uint8  	CBYF_Op;                        // 遥分处理结果
	Uint8  	CBYF_Out;                       // 遥分处理输出
	Uint8	CBBLK_Op;                       // 断路器解闭锁结果

	Uint8	TZ_GSE;				    	    // Goose保护跳闸命令反馈
	Uint8	TA_GSE;                         // Goose跳A命令反馈
	Uint8	TB_GSE;                         // Goose跳B命令反馈
	Uint8	TC_GSE;                         // Goose跳C命令反馈
	Uint8	CBYF_GSE;                       // Goose测控跳闸命令反馈
	Uint8	CBBLK_GSE;                      // Goose断路器解闭锁命令反馈
	Uint8	RESET_GSE;                      // Goose复归命令反馈
	
	Uint8	CMP_ERR;                        // 双CPU比较出错
	
	//private
	Uint8	Reset[Reset_Num];               // 复归处理情况
	
	Uint8	TA[OpS_Num];              		// TA处理情况
	Uint8	TB[OpS_Num];                    // TB处理情况
	Uint8	TC[OpS_Num];                    // TC处理情况
	
	Uint8	TJQ[TJQ_Num];                   // TJQ处理情况
	Uint8	TJR[TJR_Num];                   // TJR处理情况
	
	Uint8  	CBYF[YK_Open_NUM];              // 遥分情况
	
	Uint8	CBBLK1;                         // 断路器解闭锁1情况
	Uint8	CBBLK2;                         // 断路器解闭锁2情况

	Uint8   TestReset;                      // 测试仪复归处理情况
	Uint8   TestTA;                         // 测试仪TA处理情况
	Uint8   TestTB;                         // 测试仪TB处理情况
	Uint8   TestTC;                         // 测试仪TC处理情况
	Uint8   TestTJQ;                        // 测试仪TJQ处理情况
	Uint8   TestTJR;                        // 测试仪TJR处理情况

	Uint8 	ST_OPT;                         // 手跳处理结果
	Uint8 	ST_Out;                         // 手跳处理输出
	Uint8   BSysST;						    // B套手跳处理情况
	Uint8   STJ_Old;                        // A或B套手合
	Uint8   STJ_New;                        // A或B套手合
	Uint16	STJ_CNT;                        // SHJ计数
	
	Uint8   TestCBYF;                       // 测试仪遥分处理情况 
	
	Uint8   TestCBBLK;                      // 测试仪解闭锁处理情况
	
	Uint16  CMP_CNT1;                        // 比较计数1
	Uint16  CMP_CNT2;                        // 比较计数2
	
	Uint32 	time_save1;
	Uint8  	status1;
	
} TripCmd220;


extern  TripCmd220  *newTripCmd220(Component *parent, const char *name);
extern int  initTripCmd220(TripCmd220 *dp);

#endif
