/* FileName: BreakInfoDeal.h */
#ifndef _BreakInfoDeal_H
#define _BreakInfoDeal_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"
//#include "symbol_type_defines.h"

#define  Pos_NUM           3      // 断路器位置数目
#define  Group_NUM         4      // 组内信息数目


/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint8	*pFault_GSE[Pos_NUM];     // 断路器模块故障
	Uint8	*pFault_GSE_ok[Pos_NUM];    
	Uint8	*pAlam_GSE[Pos_NUM];      // 断路器模块运行异常告警
	Uint8	*pAlam_GSE_ok[Pos_NUM]; 
	Uint8	*pSynAlam_GSE[Pos_NUM];      // 断路器模块对时异常告警
	Uint8	*pSynAlam_GSE_ok[Pos_NUM];
	Uint8	*pOptLoss_GSE[Pos_NUM];      // 断路器模块光耦失电告警
	Uint8	*pOptLoss_GSE_ok[Pos_NUM];
	
	Uint8	*pRepair_GSE[Pos_NUM];    // 断路器模块检修压板投入
	Uint8	*pRepair_GSE_ok[Pos_NUM];
	Uint8	*pRepairDiff_GSE[Pos_NUM];    // 断路器模块检修不一致
	Uint8	*pRepairDiff_GSE_ok[Pos_NUM];
	Uint8	*pGsAlam_GSE[Pos_NUM];        // 断路器模块GOOSE接收告警
	Uint8	*pGsAlam_GSE_ok[Pos_NUM];
	Uint8	*pGsDataErr_GSE[Pos_NUM];     // 断路器模块GOOSE接收数据异常
	Uint8	*pGsDataErr_GSE_ok[Pos_NUM];

	Uint8	*pRevTph_GSE[Pos_NUM];         // 断路器模块收到跳A/B/C命令
	Uint8	*pRevTph_GSE_ok[Pos_NUM];
	Uint8	*pRevCls_GSE[Pos_NUM];         // 断路器模块收到合闸命令
	Uint8	*pRevCls_GSE_ok[Pos_NUM];

	Uint8	*pTripMon_GSE[Pos_NUM];        // 断路器模块跳闸出口回采
	Uint8	*pTripMon_GSE_ok[Pos_NUM];
	Uint8	*pClsMon_GSE[Pos_NUM];        // 断路器模块合闸出口回采
	Uint8	*pClsMon_GSE_ok[Pos_NUM];
	Uint8	*pCurAlam_GSE[Pos_NUM];        // 断路器模块跳合闸电流异常
	Uint8	*pCurAlam_GSE_ok[Pos_NUM];
	
	Uint8	*pOpPwrOff_GSE[Pos_NUM];       // 断路器模块操作电源掉电监视
	Uint8	*pOpPwrOff_GSE_ok[Pos_NUM];
	Uint8	*pCtrLoopOff_GSE[Pos_NUM];      // 断路器模块控制回路断线
	Uint8	*pCtrLoopOff_GSE_ok[Pos_NUM];

	Uint8	*pBlkClsIn_GSE[Pos_NUM];        // 断路器模块压力低闭重开入
	Uint8	*pBlkClsIn_GSE_ok[Pos_NUM];
	Uint8	*pHzPressLow_GSE[Pos_NUM];        // 断路器模块合闸压力低
	Uint8	*pHzPressLow_GSE_ok[Pos_NUM];     
	Uint8	*pTzPressLow_GSE[Pos_NUM];        // 断路器模块跳闸压力低
	Uint8	*pTzPressLow_GSE_ok[Pos_NUM];   
	Uint8	*pOpPressLow_GSE[Pos_NUM];        // 断路器模块操作压力低
	Uint8	*pOpPressLow_GSE_ok[Pos_NUM];   

	float32 *pTzCurMax_GSE[Pos_NUM];        // 断路器模块跳圈最大动作电流
	float32 *pTzCurMax_GSE_ok[Pos_NUM];
	float32 *pHzCurMax_GSE[Pos_NUM];        // 断路器模块合圈最大动作电流
	float32 *pHzCurMax_GSE_ok[Pos_NUM];

	/* parameter  */
	
	/* Output variables :  */
	Uint8	Fault[Pos_NUM];        // 断路器模块故障   
	Uint8	Alam[Pos_NUM];         // 断路器模块运行异常告警
	Uint8	SynAlam[Pos_NUM];      // 断路器模块对时异常告警
	Uint8	OptLoss[Pos_NUM];      // 断路器模块光耦失电告警
	
	Uint8	Repair[Pos_NUM];        // 断路器模块检修压板投入
	Uint8	RepairDiff[Pos_NUM];    // 断路器模块检修不一致
	Uint8	GsAlam[Pos_NUM];        // 断路器模块GOOSE接收告警
	Uint8	GsDataErr[Pos_NUM];     // 断路器模块GOOSE接收数据异常

	Uint8	RevTph[Pos_NUM];          // 断路器模块收到跳A/B/C命令
	Uint8	RevCls[Pos_NUM];          // 断路器模块收到合闸命令
	Uint8	TripMon[Pos_NUM];         // 断路器模块跳闸出口回采
	Uint8	ClsMon[Pos_NUM];          // 断路器模块合闸出口回采
	Uint8	CurAlam[Pos_NUM];         // 断路器模块跳合闸电流异常
	
	Uint8	OpPwrOff[Group_NUM];      // 断路器模块操作电源掉电监视
	Uint8	CtrLoopOff[Group_NUM];    // 断路器模块控制回路断线

	Uint8	BlkClsIn[Group_NUM];      // 断路器模块压力低闭重开入
	Uint8	HzPressLow[Group_NUM];    // 断路器模块合闸压力低
	Uint8	TzPressLow[Group_NUM];    // 断路器模块跳闸压力低
	Uint8	OpPressLow[Group_NUM];    // 断路器模块操作压力低

	float32 TzCurMax[Pos_NUM];        // 断路器模块跳圈最大动作电流
	float32 HzCurMax[Pos_NUM];        // 断路器模块合圈最大动作电流

	//private
	
	
} BreakInfoDeal;


extern  BreakInfoDeal  *newBreakInfoDeal(Component *parent, const char *name);
extern int  initBreakInfoDeal(BreakInfoDeal *dp);

#endif
