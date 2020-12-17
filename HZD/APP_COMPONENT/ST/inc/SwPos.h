/* FileName: SwPos.h */
#ifndef _SwPos_H
#define _SwPos_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"


// 刀闸数目
#define HdSwPosNum  8


/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint8  *pTest;            // 装置检修态

	Uint8  *pSwDis[HdSwPosNum];             // 刀闸分位
	Uint8  *pSwDis_ok[HdSwPosNum];  
	Uint8  *pSwCls[HdSwPosNum];             // 刀闸合位
	Uint8  *pSwCls_ok[HdSwPosNum];

	/* output variables :*/
	Uint8	SwDis[HdSwPosNum];              // 刀闸分位
	Uint8	SwDis_ok[HdSwPosNum]; 

	Uint8	SwCls[HdSwPosNum];              // 刀闸合位
	Uint8	SwCls_ok[HdSwPosNum]; 
	/* prameter variables :*/
	

	//private

	
} SwPos;


extern  SwPos  *newSwPos(Component *parent, const char *name);
extern int  initSwPos(SwPos *dp);

#endif
