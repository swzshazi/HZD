/* File Description   
*  FileName: Simulate.c -- 模拟盘接口元件        
*  Fuction: 
*       功能：获取模拟盘开入状态
*       输入：就地/远方控制开入、急停开入、强制解锁开入、手分手合开入
*       输出：控制状态、控制异常、急停、强制解锁，手分/手合等
*  apply: 本体模块
*  author: ZYB 
*  data:  20200817
*/

#include "Simulate.h"
#include "Subroutine.h"

// Local functions declaration
Simulate *newSimulate(Component *Parent,const char *Name);
int initSimulate(Simulate * dp);
void runSimulate(Simulate * dp);

/********************************************************************************
*         Input    : Parent componet, Simulate name                            *
*         Output   : Simulate handle                                           *
*         Function : Create the Simulate                                       *
********************************************************************************/
INIT_CODE Simulate *newSimulate(Component *Parent,const char *Name)
{
    Uint8 i;
    char tp_str[150];
    Simulate *dp;
        
    dp=(Simulate *)calloc(1,sizeof(Simulate));
    if (!dp) return NULL;
	
    dp->type_name="Simulate";
    dp->parent=Parent;
    dp->name=Name;
    dp->InitComponent = (int (*)(void *))initSimulate;
	
    registerComponent((Component *)dp);

    // Define input signals      
    registerVarIn((Component *)dp,(void **)&(dp->pLocalCon),"pLocalCon", T_BIT, LEVEL2);       // 就地控制
    registerVarIn((Component *)dp,(void **)&(dp->pFarCon),"pFarCon", T_BIT, LEVEL2);           // 远方控制
    
    registerVarIn((Component *)dp,(void **)&(dp->pLogicUnLock),"pLogicUnLock", T_BIT, LEVEL2);    // 逻辑解锁
    registerVarIn((Component *)dp,(void **)&(dp->pElecUnLock),"pElecUnLock", T_BIT, LEVEL2);      // 电气解锁
   
    for ( i=0; i<HdSmSwitchNum; i++ )
	{
		sprintf(tp_str, "pHandDis%d", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pHandDis[i]), tp_str, T_BIT, LEVEL2 );       // 手分开入

        sprintf(tp_str, "pHandCls%d", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pHandCls[i]), tp_str, T_BIT, LEVEL2 );       // 手合开入
    }

    // Define output signals
    registerVarOut((Component *)dp,(void *)&(dp->LocalCon),"LocalCon", T_BIT, LEVEL2);            // 就地控制
    registerVarOut((Component *)dp,(void *)&(dp->FarCon),"FarCon", T_BIT, LEVEL2);                // 远方控制
    registerVarOut((Component *)dp,(void *)&(dp->Stop),"Stop", T_BIT, LEVEL2);                    // 急停
    registerVarOut((Component *)dp,(void *)&(dp->LogicUnLock),"LogicUnLock", T_BIT, LEVEL2);      // 逻辑解锁
    registerVarOut((Component *)dp,(void *)&(dp->ElecUnLock),"ElecUnLock", T_BIT, LEVEL2);        // 电气解锁

    for ( i=0; i<HdSmSwitchNum; i++ )
	{
		sprintf(tp_str, "HandDis%d", i+1);
        registerVarOut( (Component*)dp, (void*)&(dp->HandDis[i]), tp_str, T_BIT, LEVEL2 );         // 手分状态

        sprintf(tp_str, "HandCls%d", i+1);
        registerVarOut( (Component*)dp, (void*)&(dp->HandCls[i]), tp_str, T_BIT, LEVEL2 );         // 手合状态

    }
    
    // Define parameters

    return (Simulate *)dp;
}
void CHECK_Simulate_check_task(Simulate *dp)
{
    if(dp->check_err == 0)
	{
		dp->check_err = check_set_pointer((Uint32)(&dp->start),(Uint32)(&dp->checksum));
	}
}
/********************************************************************************
*         Input    : Simulate handle                                           *
*         Output   : None                                                       *
*         Function : Initialize the Simulate                                   *
********************************************************************************/
INIT_CODE int initSimulate(Simulate * dp)
{
    int16 ret;
    if (dp==NULL) return -1;
  
    // Output variables

    // Private variables
	dp->check_err = 0;
  
    init_check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
   
    setTask(2,runSimulate,dp);
	setTask(4, CHECK_Simulate_check_task, dp);
    return 0;
}
/********************************************************************************
*         Input    : Simulate handle                                           *
*         Output   : None                                                       *
*         Function : Run the Simulate                                          *
********************************************************************************/
void runSimulate(Simulate * dp)
{   
	Uint8 i;

    dp->LocalCon = *(dp->pLocalCon);
    dp->FarCon   = *(dp->pFarCon);

    if ( *(dp->pLocalCon) == *(dp->pFarCon) )
        dp->ConErr = 1;
    else
        dp->ConErr = 0;
    
    dp->Stop = *(dp->pStop);
    dp->LogicUnLock = *(dp->pLogicUnLock);
    dp->ElecUnLock  = *(dp->pElecUnLock);

    for ( i = 0; i < HdSmSwitchNum; i++ )
    {
        dp->HandDis[i] = *(dp->pHandDis[i]);
        dp->HandCls[i] = *(dp->pHandCls[i]);
    }
}
/*  End of File */
