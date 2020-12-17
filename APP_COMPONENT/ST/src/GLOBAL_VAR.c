#include "GLOBAL_VAR.h"
#include "CommFun.h"
// Local functions declaration 
int initGLOBAL_VAR(GLOBAL_VAR *dp);
void GLOBAL_VARCal(GLOBAL_VAR *dp);
/********************************************************************************
*         Input    : Parent componet, GLOBAL_VAR name                              *
*         Output   : GLOBAL_VAR handle                                             *
*         Function : Create the GLOBAL_VAR                                         *
********************************************************************************/
GLOBAL_VAR *newGLOBAL_VAR(Component *parent,const char *name)
{
	Uint8  i;
	char   tp_str[20];
	
	GLOBAL_VAR *dp;
    dp = (GLOBAL_VAR *)calloc(1,sizeof(GLOBAL_VAR));
    if (!dp) return NULL;

    dp->parent = (Component *)parent;
    dp->type_name = "GLOB_VAR";
    dp->name = name;
    dp->InitComponent = (int (*)(void *))initGLOBAL_VAR;
    
    registerComponent((Component *)dp);

	// Define input signals
	for ( i = 0; i < HdGsTx_Num; i++ )
	{
		sprintf(tp_str,"pGsTx_ctr%d",i+1); 
		registerVarIn( (Component*)dp, (void**)&(dp->pGsTx_ctr[i]), tp_str, T_BIT, LEVEL1 );    //接入GOOSE发送控制信号
	}

	for ( i = 0; i < HdSvTx_Num; i++ )
	{
		sprintf(tp_str,"pSvTx_ctr%d",i+1); 
		registerVarIn( (Component*)dp, (void**)&(dp->pSvTx_ctr[i]), tp_str, T_BIT, LEVEL1 );    //接入SV发送控制信号
	}
	
    // Define output signals
	registerVarOut((Component *)dp,(void *)&(dp->RAM_ERR),"RAM_ERR", T_BIT, LEVEL2);
	registerVarOut((Component *)dp,(void *)&(dp->TWO_SYS_CMP_ERR),"TWO_SYS_CMP_ERR", T_BIT, LEVEL2);
	registerVarOut((Component *)dp,(void *)&(dp->utc_sec),"utc_sec", T_UINT32, LEVEL1);
	registerVarOut((Component *)dp,(void *)&(dp->utc_ms),"utc_ms", T_UINT16, LEVEL1);

	registerVarOut( (Component*)dp, (void*)&(dp->check_err), "check_err", T_BIT, LEVEL2);	 //指针比较出错

	registerVarOut((Component *)dp,(void *)&(dp->GsTx_ctr),"GsTx_ctr", T_BIT, LEVEL1);       //控制GOOSE发送
	registerVarOut((Component *)dp,(void *)&(dp->SvTx_ctr),"SvTx_ctr", T_BIT, LEVEL1);       //控制SV发送

	/////////INIT IN///////////////////////////////////
//	init_pointer(dp->p_start,dp->p_end);
	///////////////////////////////////////////////////

    return (GLOBAL_VAR *)dp;
}


void GLOBAL_VAR_check_task(GLOBAL_VAR *dp)
{
	if(dp->check_err == 0)
	{
		dp->check_err = check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	}
}

/********************************************************************************
*         Input    : GLOBAL_VAR handle                                            *
*         Output   : None                                                       *
*         Function : Initialize the GLOBAL_VAR                                    *
********************************************************************************/
int initGLOBAL_VAR(GLOBAL_VAR *dp)
{
    if (dp==NULL) return -1;


    // Input variables
    
    // Output variables

    // Private variables
	dp->check_err = 0;
	init_check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	
    setTask(1,GLOBAL_VARCal,dp);
	setTask(4,GLOBAL_VAR_check_task, dp);

	return 0;
}


/********************************************************************************
*         Input    : supHtm0 handle                                             *
*         Output   : None                                                       *
*         Function : Run the supHtm0                                            *
********************************************************************************/
void GLOBAL_VARCal(GLOBAL_VAR *dp)
{
	Uint8  i;

	dp->RAM_ERR = RAM_ERR&0x01;
	dp->TWO_SYS_CMP_ERR = TWO_SYS_CMP_ERR&0x01;
	dp->utc_sec = utc_sec;
	dp->utc_ms = local_ms;

	dp->GsTx_ctr = HdStartTx;
	//GOOSE发送控制处理
    for ( i=0; i<HdGsTx_Num; i++ )
	{
		if ( *(dp->pGsTx_ctr[i]) == 1 )
		{
			dp->GsTx_ctr = 0;
			break;
		}		
	}
	
	dp->SvTx_ctr = HdStartTx;
	//GOOSE发送控制处理
    for ( i=0; i<HdGsTx_Num; i++ )
	{
		if ( *(dp->pSvTx_ctr[i]) == 1 )
		{
			dp->SvTx_ctr = 0;
			break;
		}		
	}
}



