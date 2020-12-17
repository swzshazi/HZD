/* FileName: ElecLock.h */
#ifndef _ElecLock_H
#define _ElecLock_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"


// 电气联锁位置数目
#define HdElecPosNum    10

// 电气联锁开入数目
#define HdElecDINum     4


/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint8  *pPosDis[HdElecPosNum];     // 联锁分位
	Uint8  *pPosCls[HdElecPosNum];     // 联锁合位

	Uint8  *pDI[HdElecDINum];          // 联锁开入

	/* output variables :*/
	Uint8	PosState[HdElecPosNum];    // 联锁位置状态
	Uint8   DIState[HdElecDINum];      // 联锁开入状态
	Uint8   ElecUnlock;                // 电气联锁解锁状态
	
	/* prameter variables :*/
	Uint8  PosSet_En[HdElecPosNum];    // 位置允许操作值  
	Uint8  DISet_En[HdElecPosNum];     // 开入允许操作值

	Uint8  PosSet_Num;                 // 联锁位置使用数目
	Uint8  DISet_Num;                  // 联锁开入使用数目
	//private
    Uint8  PosVal_En[HdElecPosNum];    // 位置允许操作值  

	Uint8  PosUnLock;                  // 位置解锁
	Uint8  DIUnLock;                   // 开入解锁	
} ElecLock;


extern  ElecLock  *newElecLock(Component *parent, const char *name);
extern int  initElecLock(ElecLock *dp);

#endif
