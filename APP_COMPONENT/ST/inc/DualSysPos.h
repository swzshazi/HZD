/* FileName: DualSysPos.h */
#ifndef _DualSysPos_H
#define _DualSysPos_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"

// 断路器位置数目
#define HdDualBreakNum  3

// 跨间隔接地刀闸数目
#define HdDualOthSwNum  4

// 双位值比较结果
#define HdDualUseA    0x1         // 使用A套
#define HdDualUseB    0x2         // 使用B套
#define HdDualHold    0x4         // 保持
#define HdDualClear   0x0         // 清0

/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint8  *pTest;            // 装置检修态
	
	Uint8  *pAElecTest;       // A主控带电检修态    
	Uint8  *pACutTest;        // A主控停电检修态      

	Uint8  *pBElecTest;       // B主控带电检修态   
	Uint8  *pBCutTest;        // B主控停电检修态        

	Uint8  *pABreakDis[HdDualBreakNum];     // A套断路器分位
	Uint8  *pABreakDis_ok[HdDualBreakNum];  
	Uint8  *pABreakCls[HdDualBreakNum];     // A套断路器合位
	Uint8  *pABreakCls_ok[HdDualBreakNum];

	Uint8  *pBBreakDis[HdDualBreakNum];     // B套断路器分位
	Uint8  *pBBreakDis_ok[HdDualBreakNum];  
	Uint8  *pBBreakCls[HdDualBreakNum];     // B套断路器合位
	Uint8  *pBBreakCls_ok[HdDualBreakNum];

	Uint8  *pAOthSwDis[HdDualOthSwNum];     // A套跨间隔接地刀闸分位
	Uint8  *pAOthSwDis_ok[HdDualOthSwNum];  
	Uint8  *pAOthSwCls[HdDualOthSwNum];     // A套跨间隔接地刀闸合位
	Uint8  *pAOthSwCls_ok[HdDualOthSwNum];  

	Uint8  *pBOthSwDis[HdDualOthSwNum];     // B套跨间隔接地刀闸分位
	Uint8  *pBOthSwDis_ok[HdDualOthSwNum];  
	Uint8  *pBOthSwCls[HdDualOthSwNum];     // B套跨间隔接地刀闸合位
	Uint8  *pBOthSwCls_ok[HdDualOthSwNum];  

	/* output variables :*/
	Uint8	ABreakDis[HdDualBreakNum];      // A套断路器分位
	Uint8	ABreakCls[HdDualBreakNum];      // A套断路器合位

	Uint8	BBreakDis[HdDualBreakNum];      // B套断路器分位
	Uint8	BBreakCls[HdDualBreakNum];      // B套断路器合位

	Uint8	BreakDis[HdDualBreakNum];       // 断路器分位
	Uint8	BreakCls[HdDualBreakNum];       // 断路器合位
	
	Uint8	AOthSwDis[HdDualOthSwNum];      // A套接地刀闸分位
	Uint8	AOthSwCls[HdDualOthSwNum];      // A套接地刀闸合位
	
	Uint8	BOthSwDis[HdDualOthSwNum];      // B套接地刀闸分位
	Uint8	BOthSwCls[HdDualOthSwNum];      // B套接地刀闸合位
	
	Uint8	OthSwDis[HdDualOthSwNum];       // 跨间隔接地刀闸分位
	Uint8	OthSwCls[HdDualOthSwNum];       // 跨间隔接地刀闸合位
	
	/* prameter variables :*/
	Uint8       MainModNum;         // 主控套数

	//private

	
} DualSysPos;


extern  DualSysPos  *newDualSysPos(Component *parent, const char *name);
extern int  initDualSysPos(DualSysPos *dp);

#endif
