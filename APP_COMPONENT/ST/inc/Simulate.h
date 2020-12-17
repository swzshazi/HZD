/********************************************************************************
*         File Name   : Simulate.h                                              *
*         Description : Create, initialize and run the Simulate                 *
********************************************************************************/
#ifndef _Simulate_
#define _Simulate_

#include "hzplatform.h"
#include "hzmodule.h"
#include "CommFun.h"

//模拟盘接口刀闸数目
#define HdSmSwitchNum     8


//Constant macro definition

//Component type definition : Simulate
typedef struct 
{
	#include "base.h"

	Uint32 	start;
    // Parameter

    // Input variables
    Uint8 *pLocalCon;         // 就地控制
    Uint8 *pFarCon;           // 远方控制
    
    Uint8 *pStop;             // 急停
    Uint8 *pLogicUnLock;      // 逻辑解锁
    Uint8 *pElecUnLock;       // 电气解锁

    Uint8 *pHandDis[HdSmSwitchNum];   // 手分开入
    Uint8 *pHandCls[HdSmSwitchNum];   // 手合开入
    
	Uint32	checksum;
	Uint8	check_err;

    // Output variables
    Uint8 LocalCon;          // 就地控制
    Uint8 FarCon;            // 远方控制
    Uint8 ConErr;            // 控制方式出错 

    Uint8 Stop;              // 急停
    Uint8 LogicUnLock;       // 逻辑解锁
    Uint8 ElecUnLock;        // 电气解锁

    Uint8 HandDis[HdSmSwitchNum];   // 手分开入
    Uint8 HandCls[HdSmSwitchNum];   // 手合开入

    // Private variables

} Simulate;


// Function declaration
extern  Simulate *newSimulate(Component *Parent,const char *Name);						
extern  int initSimulate(Simulate * dp);					
extern void runSimulateTask4(Simulate *dp);

#endif
