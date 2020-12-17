/* File Description   
*  FileName: BreakInfoDeal.c -- 断路器信息处理        
*  Fuction: 
*       功能：分相断路器信息转分，并形成三相总信号
*       输入：分相断路器信号
*       输出：分相断路器信号、断路器总信号等
*  apply: 智能化开关
*  author: ZYB 
*  data:  20200529
*/

#include <stdlib.h>
#include "hzplatform.h"
#include "BreakInfoDeal.h"


void BreakInfoDeal_task( BreakInfoDeal *dp);

int initBreakInfoDeal( BreakInfoDeal *dp);

#pragma DATA_SECTION(BreakInfoDeal_stru,".rtm_data")
BreakInfoDeal BreakInfoDeal_stru;

BreakInfoDeal *newBreakInfoDeal(Component *parent, const char *name)
{
	Uint16 i=0;
	char tp_str[150];
	BreakInfoDeal *dp;
	
	dp = &BreakInfoDeal_stru;
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "BreakInfo";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent =  (int (*)(void *))initBreakInfoDeal;

	registerComponent( (Component*)dp);

	for( i=0; i<Pos_NUM; i++ )
	{
		sprintf(tp_str, "pFault%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pFault_GSE[i]), tp_str, T_BIT, LEVEL3 );         // 断路器模块故障
		sprintf(tp_str, "pFault%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pFault_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );   

		sprintf(tp_str, "pAlam%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pAlam_GSE[i]), tp_str, T_BIT, LEVEL3 );         // 断路器模块运行异常
		sprintf(tp_str, "pAlam%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pAlam_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );   

		sprintf(tp_str, "pSynAlam%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pSynAlam_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块对时异常
		sprintf(tp_str, "pSynAlam%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pSynAlam_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );  

		sprintf(tp_str, "pOptLoss%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pOptLoss_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块光耦失电
		sprintf(tp_str, "pOptLoss%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pOptLoss_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );  

		sprintf(tp_str, "pRepair%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pRepair_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块检修压板投入
		sprintf(tp_str, "pRepair%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pRepair_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );  

		sprintf(tp_str, "pRepairDiff%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pRepairDiff_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块检修不一致
		sprintf(tp_str, "pRepairDiff%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pRepairDiff_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );  

		sprintf(tp_str, "pGsAlam%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pGsAlam_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块GOOSE接收告警
		sprintf(tp_str, "pGsAlam%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pGsAlam_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );  

		sprintf(tp_str, "pGsDataErr%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pGsDataErr_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块GOOSE接收告警
		sprintf(tp_str, "pGsDataErr%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pGsDataErr_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );  


		sprintf(tp_str, "pRevTph%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pRevTph_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块收到跳A/B/C命令
		sprintf(tp_str, "pRevTph%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pRevTph_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );  

		sprintf(tp_str, "pRevCls%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pRevCls_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块收到合闸命令
		sprintf(tp_str, "pRevCls%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pRevCls_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );  

		sprintf(tp_str, "pTripMon%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTripMon_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块跳闸出口回采
		sprintf(tp_str, "pTripMon%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTripMon_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );  

		sprintf(tp_str, "pClsMon%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pClsMon_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块合闸出口回采
		sprintf(tp_str, "pClsMon%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pClsMon_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 ); 

		sprintf(tp_str, "pCurAlam%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pCurAlam_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块跳合闸电流异常
		sprintf(tp_str, "pCurAlam%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pCurAlam_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );  

		sprintf(tp_str, "pOpPwrOff%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pOpPwrOff_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块操作电源掉电监视
		sprintf(tp_str, "pOpPwrOff%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pOpPwrOff_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );

		sprintf(tp_str, "pCtrLoopOff%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pCtrLoopOff_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块控制回路断线
		sprintf(tp_str, "pCtrLoopOff%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pCtrLoopOff_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );

		sprintf(tp_str, "pBlkClsIn%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBlkClsIn_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块压力低闭重开入
		sprintf(tp_str, "pBlkClsIn%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBlkClsIn_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 ); 

		sprintf(tp_str, "pHzPressLow%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pHzPressLow_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块合闸压力低
		sprintf(tp_str, "pHzPressLow%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pHzPressLow_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 );

		sprintf(tp_str, "pTzPressLow%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTzPressLow_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块跳闸压力低
		sprintf(tp_str, "pTzPressLow%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTzPressLow_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 ); 

		sprintf(tp_str, "pOpPressLow%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pOpPressLow_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块操作压力低
		sprintf(tp_str, "pOpPressLow%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pOpPressLow_GSE_ok[i]), tp_str, T_UINT8, LEVEL3 ); 

		sprintf(tp_str, "pTzCurMax%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTzCurMax_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块跳圈最大动作电流
		sprintf(tp_str, "pTzCurMax%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pTzCurMax_GSE_ok[i]), tp_str, T_FLOAT, LEVEL3 ); 

		sprintf(tp_str, "pHzCurMax%d_GSE", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pHzCurMax_GSE[i]), tp_str, T_BIT, LEVEL3 );      // 断路器模块合圈最大动作电流
		sprintf(tp_str, "pHzCurMax%d_GSE_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pHzCurMax_GSE_ok[i]), tp_str, T_FLOAT, LEVEL3 ); 

	}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	for( i=0; i<Pos_NUM; i++ )
	{
		sprintf(tp_str, "Fault%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->Fault[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块故障

		sprintf(tp_str, "Alam%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->Alam[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块运行异常

		sprintf(tp_str, "SynAlam%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->SynAlam[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块对时异常

		sprintf(tp_str, "OptLoss%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->OptLoss[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块光耦失电

		sprintf(tp_str, "Repair%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->Repair[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块检修压板投入

		sprintf(tp_str, "RepairDiff%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->RepairDiff[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块检修不一致

		sprintf(tp_str, "GsAlam%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->GsAlam[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块GOOSE接收告警

		sprintf(tp_str, "GsDataErr%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->GsDataErr[i]), tp_str, T_BIT, LEVEL3 ); // 断路器模块GOOSE接收数据异常

		sprintf(tp_str, "RevTrip%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->RevTph[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块收到跳A/B/C命令

		sprintf(tp_str, "RevCls%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->RevCls[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块收到合闸命令

		sprintf(tp_str, "TripMon%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TripMon[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块跳闸出口回采
		
		sprintf(tp_str, "ClsMon%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->ClsMon[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块合闸出口回采·

		sprintf(tp_str, "CurAlam%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->CurAlam[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块跳合闸电流异常

		sprintf(tp_str, "TzCurMax%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TzCurMax[i]), tp_str, T_FLOAT, LEVEL3 );	// 断路器模块跳圈最大动作电流

		sprintf(tp_str, "HzCurMax%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->HzCurMax[i]), tp_str, T_FLOAT, LEVEL3 );	// 断路器模块合圈最大动作电流
	}

	for( i=0; i<Group_NUM; i++ )
	{
		sprintf(tp_str, "OpPwrOff%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->OpPwrOff[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块操作电源掉电监视

		sprintf(tp_str, "CtrOff%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->CtrLoopOff[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块控制回路断线

		sprintf(tp_str, "BlkClsIn%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BlkClsIn[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块压力低闭重开入

		sprintf(tp_str, "HzPressLow%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->HzPressLow[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块合闸压力低

		sprintf(tp_str, "TzPressLow%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->TzPressLow[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块跳闸压力低

		sprintf(tp_str, "OpPressLow%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->OpPressLow[i]), tp_str, T_BIT, LEVEL3 );	// 断路器模块操作压力低
	}	

	return dp;
}

INIT_CODE
int initBreakInfoDeal(BreakInfoDeal *dp)
{
	setTask( 3, BreakInfoDeal_task, dp);

	return 0;
}



#pragma CODE_SECTION(BreakInfoDeal_task,".rtm_code")
void BreakInfoDeal_task(BreakInfoDeal *dp)
{
	Uint8 i=0, quality=0;

////////////////////////////获取定值参数////////////////////////////////////////////////////
	
	

//////////////////////////逻辑处理/////////////////////////////////////////////////////////

	for ( i=0; i<Pos_NUM; i++ )
	{ 
		quality  = *(dp->pFault_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->Fault[i] = *(dp->pFault_GSE[i]);
		}
		else
		{
			dp->Fault[i] = 0;
		}
		
		quality  = *(dp->pAlam_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->Alam[i] = *(dp->pAlam_GSE[i]);
		}
		else
		{
			dp->Alam[i] = 0;
		}

		quality  = *(dp->pSynAlam_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->SynAlam[i] = *(dp->pSynAlam_GSE[i]);
		}
		else
		{
			dp->SynAlam[i] = 0;
		}
		
		quality  = *(dp->pOptLoss_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->OptLoss[i] = *(dp->pOptLoss_GSE[i]);
		}
		else
		{
			dp->OptLoss[i] = 0;
		}
		
		quality  = *(dp->pRepair_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->Repair[i] = *(dp->pRepair_GSE[i]);
		}
		else
		{
			dp->Repair[i] = 0;
		}
		
		quality  = *(dp->pRepairDiff_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->RepairDiff[i] = *(dp->pRepairDiff_GSE[i]);
		}
		else
		{
			dp->RepairDiff[i] = 0;
		}
		
		quality  = *(dp->pGsAlam_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->GsAlam[i] = *(dp->pGsAlam_GSE[i]);
		}
		else
		{
			dp->GsAlam[i] = 0;
		}
		
		quality  = *(dp->pGsDataErr_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->GsDataErr[i] = *(dp->pGsDataErr_GSE[i]);
		}
		else
		{
			dp->GsDataErr[i] = 0;
		}
		
		quality  = *(dp->pRevTph_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->RevTph[i] = *(dp->pRevTph_GSE[i]);
		}
		else
		{
			dp->RevTph[i] = 0;
		}
		
		quality  = *(dp->pRevCls_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->RevCls[i] = *(dp->pRevCls_GSE[i]);
		}
		else
		{
			dp->RevCls[i] = 0;
		}
		
		quality  = *(dp->pTripMon_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->TripMon[i] = *(dp->pTripMon_GSE[i]);
		}
		else
		{
			dp->TripMon[i] = 0;
		}
		
		quality  = *(dp->pClsMon_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->ClsMon[i] = *(dp->pClsMon_GSE[i]);
		}
		else
		{
			dp->ClsMon[i] = 0;
		}
		
		quality  = *(dp->pCurAlam_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->CurAlam[i] = *(dp->pCurAlam_GSE[i]);
		}
		else
		{
			dp->CurAlam[i] = 0;
		}
		
		quality  = *(dp->pOpPwrOff_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->OpPwrOff[i] = *(dp->pOpPwrOff_GSE[i]);
		}
		else
		{
			dp->OpPwrOff[i] = 0;
		}
		
		quality  = *(dp->pCtrLoopOff_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->CtrLoopOff[i] = *(dp->pCtrLoopOff_GSE[i]);
		}
		else
		{
			dp->CtrLoopOff[i] = 0;
		}
		
		quality  = *(dp->pBlkClsIn_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->BlkClsIn[i] = *(dp->pBlkClsIn_GSE[i]);
		}
		else
		{
			dp->BlkClsIn[i] = 0;
		}
		
		quality  = *(dp->pHzPressLow_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->HzPressLow[i] = *(dp->pHzPressLow_GSE[i]);
		}
		else
		{
			dp->HzPressLow[i] = 0;
		}
		
		quality  = *(dp->pTzPressLow_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->TzPressLow[i] = *(dp->pTzPressLow_GSE[i]);
		}
		else
		{
			dp->TzPressLow[i] = 0;
		}
		
		quality  = *(dp->pOpPressLow_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->OpPressLow[i] = *(dp->pOpPressLow_GSE[i]);
		}
		else
		{
			dp->OpPressLow[i] = 0;
		}
		
		quality  = *(dp->pTzCurMax_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->TzCurMax[i] = *(dp->pTzCurMax_GSE[i]);
		}
		else
		{
			dp->TzCurMax[i] = 0;
		}
		
		quality  = *(dp->pHzCurMax_GSE_ok[i]);
		if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) )
		{
			dp->HzCurMax[i] = *(dp->pHzCurMax_GSE[i]);
		}
		else
		{
			dp->HzCurMax[i] = 0;
		}	
	}
    
	// 操作电源掉电
	dp->OpPwrOff[3]   = dp->OpPwrOff[0] | dp->OpPwrOff[1] | dp->OpPwrOff[2];
	// 控制回路断线
	dp->CtrLoopOff[3] = dp->CtrLoopOff[0] | dp->CtrLoopOff[1] | dp->CtrLoopOff[2];
	
	// 压力低闭重开入
	dp->BlkClsIn[3]   = dp->BlkClsIn[0] | dp->BlkClsIn[1] | dp->BlkClsIn[2];
	// 合闸压力低
	dp->HzPressLow[3] = dp->HzPressLow[0] | dp->HzPressLow[1] | dp->HzPressLow[2];
	// 跳闸压力低
	dp->TzPressLow[3] = dp->TzPressLow[0] | dp->TzPressLow[1] | dp->TzPressLow[2];
	// 操作压力低
	dp->OpPressLow[3] = dp->OpPressLow[0] | dp->OpPressLow[1] | dp->OpPressLow[2];

//////////////////////////双系统监视比较////////////////////////////////////////////////////////////

}
