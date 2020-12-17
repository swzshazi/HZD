/* FileName: BreakPosDiff.h */
#ifndef _BreakPosDiff_H
#define _BreakPosDiff_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"
//#include "symbol_type_defines.h"

#define  Pos_NUM           3        // 断路器位置数目

#define  Dis_Value          0x1     // 双位置分位值
#define  Cls_Value          0x2     // 双位置合位值

/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint32 	start;

	Uint8	*pHwj[Pos_NUM];                // 断路器合位
	Uint8	*pTwj[Pos_NUM];                // 断路器分位
	Uint8	*pKKJ;                         // KKJ合后
	
	Uint8	*pBreakPh_ELSE;                // 另一CPU非全相

	Uint32	checksum;
	Uint8	check_err;

	/* parameter  */
	float32 PosDiff_Delay;                 // 位置不一致延时时间
	Uint32  PosDiff_Num;                   // 延时转晶振计数
	
	float32 BreakPh_Delay;                 // 非全相保护延时时间
	Uint32  BreakPh_Num;                   // 延时转晶振计数

	float32 FaultTotal_Delay;              // 事故总延时时间
	Uint32  FaultTotal_Num;                // 延时转晶振计数
	
	/* output variables :*/
	Uint8   BreakPosDiff;                  // 断路器位置不一致
	Uint8   BreakPhPro;                    // 断路器非全相保护
	
	Uint8   FaultTotal;                    // 事故总

	Uint8	CMP_ERR;                        // 双CPU比较出错

	//private
	Uint16  CMP_CNT;
	
	Uint8   ret1;                          // 临时变量1
	Uint8   AnyDis;                        // 任一相分位
	Uint8   AnyCls;                        // 任一相合位

	Uint8   PosRet[Pos_NUM];               // 临时位置值
	Uint8   DisRet[Pos_NUM];			   // 临时分位值
	Uint8   ClsRet[Pos_NUM];			   // 临时合位值
	Uint8   ret2;                          // 临时变量2
	
	Uint32 	time_save1;
	Uint8  	status1;

	Uint32 	time_save2;
	Uint8  	status2;

	Uint32 	time_save3;
	Uint8  	status3;

	Uint8   ret3;                          // 临时变量2
	Uint32 	time_save4;
	Uint8  	status4;
	
} BreakPosDiff;


extern  BreakPosDiff  *newBreakPosDiff(Component *parent, const char *name);
extern int  initBreakPosDiff(BreakPosDiff *dp);

#endif
