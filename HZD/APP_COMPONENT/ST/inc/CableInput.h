/********************************************************************************
*         File Name   : CableInput.h                                              *
*         Description : Create, initialize and run the CableInput                 *
********************************************************************************/
#ifndef _CableInput_
#define _CableInput_

#include "hzplatform.h"
#include "hzmodule.h"
#include "CommFun.h"

//出口压板数目
#define HdOutBoard       8
//压板异常告警时间
#define HdBoardAlamNum   1080000      //6小时-20ms任务：3600*6*50

//备用开入数目
#define HdSdByDINum  20

//Constant macro definition

//Component type definition : CableInput
typedef struct 
{
	#include "base.h"

	Uint32 	start;
    // Parameter

    // Input variables
    SOE_VALUE *pOptodc;         // 遥信电源监视
    SOE_VALUE *pCutTest;        // 停电检修
    SOE_VALUE *pElecTest;       // 带电检修

    SOE_VALUE *pOutBoard[HdOutBoard];  // 出口压板
    SOE_VALUE *pSdByDI[HdSdByDINum];   // 备用开入
    
	Uint32	checksum;
	Uint8	check_err;

    // Output variables
    Uint8 opt_err;           // 光耦失电
    Uint8 test_strap_out;    // 检修压板投入
    SOE_VALUE test_Elec_out;     // 带电检修压板投入
    SOE_VALUE test_cut_out;      // 停电检修压板投入

    SOE_VALUE OutBoard[HdOutBoard];  // 出口压板状态
    SOE_VALUE SdByDI[HdSdByDINum];   // 备用开入状态

    Uint8  OutBoardAlam;         // 出口压板异常
    Uint32 BoardAlamNum;         // 出口压板异常计数

    // Private variables
    Uint16 opt_err_cnt;

} CableInput;


// Function declaration
extern  CableInput *newCableInput(Component *Parent,const char *Name);						
extern  int initCableInput(CableInput * dp);					
extern void runCableInputTask4(CableInput *dp);

#endif
