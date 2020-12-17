/* FileName: DzCmdMerge.h */
#ifndef _DzCmdMerge_H
#define _DzCmdMerge_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"

//#include "symbol_type_defines.h"

#define YK_DZ_NUM  8

// 双命令比较结果
#define HdDzCmdUseA        0x1         // 使用A套
#define HdDzCmdUseB        0x2         // 使用B套
#define HHdDzCmdUseAClear  0x0         // 清0

/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint32 	start;
	Uint8	*pElecTest;                    // 带电检修
	Uint8	*pTest;                        // 检修状态

	Uint8	*pAElecTest;                   // A套带电检修
	Uint8	*pAElecTest_ok;                  
	Uint8	*pACutTest;                    // A套停电检修
	Uint8	*pACutTest_ok;

	Uint8	*pBElecTest;                   // B套带电检修
	Uint8	*pBElecTest_ok;
	Uint8	*pBCutTest;                    // B套停电检修
	Uint8	*pBCutTest_ok;

	Uint8	*pLocalCon;                    // 就地控制投入
	Uint8	*pFarCon;                      // 远方控制投入
	
	Uint8	*pADZYF[YK_DZ_NUM];            // A套刀闸遥分
	Uint8	*pADZYF_ok[YK_DZ_NUM];
	Uint8	*pADZYH[YK_DZ_NUM];            // A套刀闸遥合
	Uint8	*pADZYH_ok[YK_DZ_NUM];

	Uint8	*pBDZYF[YK_DZ_NUM];            // B套刀闸遥分
	Uint8	*pBDZYF_ok[YK_DZ_NUM];
	Uint8	*pBDZYH[YK_DZ_NUM];            // B套刀闸遥合
	Uint8	*pBDZYH_ok[YK_DZ_NUM];

	Uint8	*pADZBLK[YK_DZ_NUM];           // A套刀闸解闭锁
	Uint8	*pADZBLK_ok[YK_DZ_NUM];
	Uint8	*pBDZBLK[YK_DZ_NUM];           // B套刀闸解闭锁
	Uint8	*pBDZBLK_ok[YK_DZ_NUM];

	Uint8	*pTestDZYF[YK_DZ_NUM];         // 测试仪刀闸遥分
	Uint8	*pTestDZYF_ok[YK_DZ_NUM]; 
	Uint8	*pTestDZYH[YK_DZ_NUM];         // 测试仪刀闸遥合值
	Uint8	*pTestDZYH_ok[YK_DZ_NUM]; 
	
	Uint8	*pTestDZBLK[YK_DZ_NUM];        // 测试仪刀闸解闭锁值
	Uint8	*pTestDZBLK_ok[YK_DZ_NUM];    

	Uint8	*pDZHandF[YK_DZ_NUM];          // 手分刀闸
	Uint8	*pDZHandH[YK_DZ_NUM];          // 手合刀闸 

	Uint8	*pDZOutBd[YK_DZ_NUM];          // 刀闸出口压板 

	Uint8	*pDZYF_ELSE;                   // 另一CPU刀闸遥分 
	Uint8	*pDZYH_ELSE;                   // 另一CPU刀闸遥合 
	Uint8	*pDZBLK_ELSE;                  // 另一CPU刀闸解闭锁

	Uint32  checksum;                      // 输入指针校验结果
	Uint8	check_err;                     // 输入指针校验错误
	/* output variables :*/
	SOE_VALUE	AElecTest_E;               // A套带电检修 SOE
	SOE_VALUE	ACutTest_E;                // A套停电检修 SOE
	Uint8	    AElecTest;                 // A套主控带电检修态
	Uint8	    ACutTest;                  // A套主控停电检修态

	SOE_VALUE	BElecTest_E;               // B套带电检修 SOE
	SOE_VALUE	BCutTest_E;                // B套停电检修 SOE
	Uint8	    BElecTest;                 // B套主控带电检修态
	Uint8	    BCutTest;                  // B套主控停电检修态

	SOE_VALUE	ADZYF_E[YK_DZ_NUM];        // A套刀闸遥分 SOE  
	SOE_VALUE	ADZYH_E[YK_DZ_NUM];        // A套刀闸遥合 SOE
    SOE_VALUE	ADZBLK_E[YK_DZ_NUM];       // A套刀闸解闭锁 SOE	

	SOE_VALUE	BDZYF_E[YK_DZ_NUM];        // B套刀闸遥分 SOE  
	SOE_VALUE	BDZYH_E[YK_DZ_NUM];        // B套刀闸遥合 SOE
    SOE_VALUE	BDZBLK_E[YK_DZ_NUM];       // B套刀闸解闭锁 SOE	
	
	Uint8		DZYF[YK_DZ_NUM];           // 刀闸遥分结果
	Uint8		DZYH[YK_DZ_NUM];           // 刀闸遥合结果
	Uint8		DZBLK[YK_DZ_NUM];          // 刀闸解闭锁结果

	SOE_VALUE	TestDZYF_E[YK_DZ_NUM];     // 测试仪刀闸遥分 SOE  
	SOE_VALUE	TestDZYH_E[YK_DZ_NUM];     // 测试仪刀闸遥合 SOE
	SOE_VALUE	TestDZBLK_E[YK_DZ_NUM];    // 测试仪刀闸解闭锁 SOE  
	Uint8		TestDZYF[YK_DZ_NUM];       // 测试仪刀闸遥分动作  
	Uint8		TestDZYH[YK_DZ_NUM];       // 测试仪刀闸遥合动作
	Uint8		TestDZBLK[YK_DZ_NUM];      // 测试仪刀闸解闭锁动作

	Uint8   	DZHandF[YK_DZ_NUM];        // 手分刀闸动作
	Uint8   	DZHandH[YK_DZ_NUM];        // 手合刀闸动作 
	
	Uint8		DZLF_OP[YK_DZ_NUM];         // 刀闸就地分动作
	Uint8		DZLH_OP[YK_DZ_NUM];         // 刀闸就地合动作
	Uint8		DZLBLK_OP[YK_DZ_NUM];       // 刀闸就地解闭锁动作

	Uint8		DZYF_Out[YK_DZ_NUM];         // 刀闸遥分输出
	Uint8		DZYH_Out[YK_DZ_NUM];         // 刀闸遥合输出
	Uint8		DZBLK_Out[YK_DZ_NUM];        // 刀闸解闭锁输出
	
	Uint8		DZYF_GSE[YK_DZ_NUM];         // 刀闸遥分命令反馈       
	Uint8		DZYH_GSE[YK_DZ_NUM];         // 刀闸遥合命令反馈
	Uint8		DZBLK_GSE[YK_DZ_NUM];        // 刀闸解闭锁命令反馈

	Uint8 		DZYF_ALL;                  // 刀闸遥分总
	Uint8 		DZYH_ALL;                  // 刀闸遥合总
	Uint8 		DZBLK_ALL;                 // 刀闸解闭锁总 

	Uint8		DZYK_LONGTIME;             // 刀闸遥控长时间动作

	Uint8	   CMP_ERR;                    // 双CPU比较出错
	
	//prarameter
	
	//private
	Uint16  CMP_CNT1;
	Uint16  CMP_CNT2;
	Uint16  CMP_CNT3;
		
	Uint32 	time_save1;
	Uint8  	status1;
} DzCmdMerge;


extern  DzCmdMerge  *newDzCmdMerge(Component *parent, const char *name);
extern int  initDzCmdMerge(DzCmdMerge *dp);

#endif
