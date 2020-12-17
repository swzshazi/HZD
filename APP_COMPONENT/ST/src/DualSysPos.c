/* File Description   
*  FileName: DualSysPos.c -- 智能开关双套位置处理元件     
*  Fuction: 
*       功能：获取A/B套断路器位置并转发站控层网络和刀闸模块; 获取跨间隔接地刀闸位置并转发刀闸模块
*       输入：A/B套断路器位置Gs值和品质、A/B套跨间隔接地刀闸位置
*       输出：处理后双位置值
*  apply: 智能化开关
*  author: ZYB 
*  data:  20200817
*/

#include <stdlib.h>
#include "hzplatform.h"
#include "DualSysPos.h"
#include "CommFun.h"

void DualSysPos_task( DualSysPos *dp);

int initDualSysPos( DualSysPos *dp);


DualSysPos *newDualSysPos(Component *parent, const char *name)
{
	Uint8 i;
	char tp_str[150];
	
	DualSysPos *dp;
	
	dp = (DualSysPos *)calloc(1, sizeof(DualSysPos));
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "DualPos";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent = (int (*)(void *))initDualSysPos;

	registerComponent( (Component*)dp);
	
	registerVarIn( (Component*)dp, (void**)&(dp->pTest), "pTest", T_BIT, LEVEL1 );			         // 装置检修态
	
	registerVarIn( (Component*)dp, (void**)&(dp->pAElecTest), "pAElecTest", T_BIT, LEVEL1 );	     // A主控带电检修态 
	registerVarIn( (Component*)dp, (void**)&(dp->pACutTest), "pACutTest", T_BIT, LEVEL1 );	         // A主控停电检修态

	registerVarIn( (Component*)dp, (void**)&(dp->pBElecTest), "pBElecTest", T_BIT, LEVEL1 );	     // B主控带电检修态     
	registerVarIn( (Component*)dp, (void**)&(dp->pBCutTest), "pBCutTest", T_BIT, LEVEL1 );	         // B主控停电检修态
	
	for ( i = 0; i < HdDualBreakNum; i++ )
	{
		sprintf(tp_str, "pABreakDis%d__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pABreakDis[i]), tp_str, T_BIT, LEVEL1 );       // A套断路器分位 
		sprintf(tp_str, "pABreakDis%d__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pABreakDis_ok[i]), tp_str, T_UINT8, LEVEL1 );

		sprintf(tp_str, "pABreakCls%d__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pABreakCls[i]), tp_str, T_BIT, LEVEL1 );       // A套断路器合位
		sprintf(tp_str, "pABreakCls%d__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pABreakCls_ok[i]), tp_str, T_UINT8, LEVEL1 );

		sprintf(tp_str, "pBBreakDis%d__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBBreakDis[i]), tp_str, T_BIT, LEVEL1 );       // B套断路器分位
		sprintf(tp_str, "pBBreakDis%d__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBBreakDis_ok[i]), tp_str, T_UINT8, LEVEL1 );

		sprintf(tp_str, "pBBreakCls%d__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBBreakCls[i]), tp_str, T_BIT, LEVEL1 );       // B套断路器合位
		sprintf(tp_str, "pBBreakCls%d__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBBreakCls_ok[i]), tp_str, T_UINT8, LEVEL1 );
	}

	for ( i = 0; i < HdDualOthSwNum; i++ )
	{
		sprintf(tp_str, "pAOthSwDis%d__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pAOthSwDis[i]), tp_str, T_BIT, LEVEL1 );       // A套跨间隔接地刀闸分位 
		sprintf(tp_str, "pAOthSwDis%d__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pAOthSwDis_ok[i]), tp_str, T_UINT8, LEVEL1 );

		sprintf(tp_str, "pAOthSwCls%d__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pAOthSwCls[i]), tp_str, T_BIT, LEVEL1 );       // A套跨间隔接地刀闸分位 
		sprintf(tp_str, "pAOthSwCls%d__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pAOthSwCls_ok[i]), tp_str, T_UINT8, LEVEL1 );

		sprintf(tp_str, "pBOthSwDis%d__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBOthSwDis[i]), tp_str, T_BIT, LEVEL1 );       // B套跨间隔接地刀闸分位 
		sprintf(tp_str, "pBOthSwDis%d__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBOthSwDis_ok[i]), tp_str, T_UINT8, LEVEL1 );

		sprintf(tp_str, "pBOthSwCls%d__AB", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBOthSwCls[i]), tp_str, T_BIT, LEVEL1 );       // B套跨间隔接地刀闸分位 
		sprintf(tp_str, "pBOthSwCls%d__AB_ok", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pBOthSwCls_ok[i]), tp_str, T_UINT8, LEVEL1 );
	}

//////////////////////////////////////////////////////////////////////////////////////////////////////

	for ( i = 0; i < HdDualBreakNum; i++ )
	{
		sprintf(tp_str, "ABreakDis%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->ABreakDis[i]), tp_str, T_BIT, LEVEL1 );	    //A套断路器分位
		sprintf(tp_str, "ABreakCls%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->ABreakCls[i]), tp_str, T_BIT, LEVEL1 );	    //A套断路器合位
		
		sprintf(tp_str, "BBreakDis%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BBreakDis[i]), tp_str, T_BIT, LEVEL1 );	    //B套断路器分位
		sprintf(tp_str, "BBreakCls%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BBreakCls[i]), tp_str, T_BIT, LEVEL1 );	    //B套断路器合位
		
		sprintf(tp_str, "BreakDis%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BreakDis[i]), tp_str, T_BIT, LEVEL1 );	        //断路器分位
		sprintf(tp_str, "BreakCls%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BreakCls[i]), tp_str, T_BIT, LEVEL1 );	        //断路器合位
	}
	
	for ( i = 0; i < HdDualOthSwNum; i++ )
	{
		sprintf(tp_str, "AOthSwDis%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->AOthSwDis[i]), tp_str, T_BIT, LEVEL1 );	    //A套跨间隔接地刀闸分位

		sprintf(tp_str, "AOthSwCls%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->AOthSwCls[i]), tp_str, T_BIT, LEVEL1 );	    //A套跨间隔接地刀闸分位

		sprintf(tp_str, "BOthSwDis%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BOthSwDis[i]), tp_str, T_BIT, LEVEL1 );	    //B套跨间隔接地刀闸分位

		sprintf(tp_str, "BOthSwCls%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->BOthSwCls[i]), tp_str, T_BIT, LEVEL1 );	    //B套跨间隔接地刀闸分位
		
		sprintf(tp_str, "OthSwDis%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->OthSwDis[i]), tp_str, T_BIT, LEVEL1 );	    //跨间隔接地刀闸分位

		sprintf(tp_str, "OthSwCls%d", i+1);
		registerVarOut( (Component*)dp, (void*)&(dp->OthSwCls[i]), tp_str, T_BIT, LEVEL1 );	    //跨间隔接地刀闸合位
	}
	
	return dp;
}

INIT_CODE
int initDualSysPos(DualSysPos *dp)
{
	setTask( 2, DualSysPos_task, dp);

	return 0;
}


#pragma CODE_SECTION(DualSysPos_task,".rtm_code")

//品质一致断链：保持；
//品质一致均在线：值相同，用A； 值不相同，A有效B无效，用A，B有效A无效，用B；均有效或均无效，清0；
//品质不一致均在线：A运行态，用A;B运行态，用B；无运行态，清0。
//品质不一致仅一在线：A在线，用A；B在线
//品质不一致均不在线：A在线，用A；B在线
Uint8 Fun_Pos_QComp( Uint8 PosA, Uint8 *Aquality, Uint8 PosB, Uint8 *Bquality )
{
	Uint8  Astate, Bstate;

	Astate = *Aquality;
	Bstate = *Bquality;

	//品质一致
	if ( Astate == Bstate )
	{
		//在线
		if ( ((Astate & 0x08) == 0x08) && ((Astate & 0x04) == 0x04) )
		{
			if ( PosA == PosB ) return HdDualUseA;
			else
			{
				if ( (PosA == 0x1) || (PosA == 0x2) )
				{
					if ( (PosB == 0x1) || (PosB == 0x2) )  return HdDualClear;
					else  return HdDualUseA;
				}
				else
				{
					if ( (PosB == 0x1) || (PosB == 0x2) )  return HdDualUseB;
					else return HdDualClear;
				}
			}
		}
		else 
		{
			return HdDualHold;
		}
	}
	else
	{
		//A在线且为运行态
		if ( ((Astate & 0x08) == 0x08) && ((Astate & 0x04) == 0x04) && ((Astate & 0x02) == 0) )
		{
			return HdDualUseA;
		}
		else if ( ((Bstate & 0x08) == 0x08) && ((Bstate & 0x04) == 0x04) && ((Bstate & 0x02) == 0) )  //B在线且为运行态
		{
			return HdDualUseB;
		}
		else if ( ( (Astate & 0x08) != 0x08) || ((Astate & 0x04) != 0x04) )  //A不在线
		{
			if ( ((Bstate & 0x08) != 0x08) || ((Bstate & 0x04) != 0x04) ) return HdDualHold;   //B不在线
			else  return HdDualUseB;	  //B在线
		}
		else
		{
			if ( ((Bstate & 0x08) != 0x08) || ((Bstate & 0x04) != 0x04) ) return HdDualUseA;   //B不在线
			else return HdDualClear;  //AB均在线均不为运行态，品质还不一致，目前无此可能
		}	
	}
}

void DualSysPos_task(DualSysPos *dp)
{
	Uint8 i, quality, quality1, quality2, test, APos, BPos;

	// 断路器位置处理
	for ( i = 0; i < HdDualBreakNum; i++ )
	{
		dp->ABreakDis[i] = *(dp->pABreakDis[i]);
		dp->ABreakCls[i] = *(dp->pABreakCls[i]);
		
		dp->BBreakDis[i] = *(dp->pBBreakDis[i]);
		dp->BBreakCls[i] = *(dp->pBBreakCls[i]);

		APos = dp->ABreakDis[i] + dp->ABreakCls[i] << 1;
		BPos = dp->BBreakDis[i] + dp->BBreakCls[i] << 1;
 
		quality = Fun_Pos_QComp( APos, dp->pABreakDis_ok[i], BPos, dp->pBBreakDis_ok[i] );

		switch(quality)
		{
			case HdDualUseA:
				dp->BreakDis[i] = dp->ABreakDis[i];
				dp->BreakCls[i] = dp->ABreakCls[i];
				break;
			case HdDualUseB:
				dp->BreakDis[i] = dp->BBreakDis[i];
				dp->BreakCls[i] = dp->BBreakCls[i];
				break;
			case HdDualClear:
				dp->BreakDis[i] = 0;
				dp->BreakCls[i] = 0;
				break;
			default:
			    break;
		}
	}
	
	// 跨间隔接地刀闸位置处理
	for ( i = 0; i < HdDualOthSwNum; i++ )
	{
		dp->AOthSwDis[i] = *(dp->pAOthSwDis[i]);
		dp->AOthSwCls[i] = *(dp->pAOthSwCls[i]);
		
		dp->BOthSwDis[i] = *(dp->pBOthSwDis[i]);
		dp->BOthSwCls[i] = *(dp->pBOthSwCls[i]);

		APos = dp->AOthSwDis[i] + dp->AOthSwCls[i] << 1;
		BPos = dp->BOthSwDis[i] + dp->BOthSwCls[i] << 1;

		if ( (*(dp->pAElecTest) != *(dp->pBElecTest) ) || (*(dp->pACutTest) != *(dp->pBCutTest) ) )
		{
			dp->OthSwDis[i] = 0;
			dp->OthSwCls[i] = 0;
		}
		else
		{
			quality = Fun_Pos_QComp( APos, dp->pAOthSwDis_ok[i], BPos, dp->pBOthSwDis_ok[i] );
		}	
		
		switch(quality)
		{
			case HdDualUseA:
				dp->OthSwDis[i] = dp->AOthSwDis[i];
				dp->OthSwCls[i] = dp->AOthSwCls[i];
				break;
			case HdDualUseB:
				dp->OthSwDis[i] = dp->BOthSwDis[i];
				dp->OthSwCls[i] = dp->BOthSwCls[i];
				break;
			case HdDualClear:
				dp->OthSwDis[i] = 0;
				dp->OthSwCls[i] = 0;
				break;
			default:
			    break;
		}
	}
}
