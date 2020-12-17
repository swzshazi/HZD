/********************************************************************************************
*          File Name   : GLOBAL_VAR.h                                                         *
*          Description : Type definitions, prototype declaration for the GLOBAL_VAR.          *
********************************************************************************************/

#ifndef _GLOBAL_VAR_
#define _GLOBAL_VAR_

#ifdef __cplusplus
extern "C" {
#endif

#include "hzplatform.h"
#include "CommFun.h"

// Constant macro definition

/* input variables :*/

#define		HdGsTx_Num	8
#define		HdSvTx_Num	8

#define     HdStartTx   0x55


// Component type definition : GLOBAL_VAR
typedef struct
{
    #include "base.h"

    // Parameter
    
    // Input variables
    Uint32 start;

    Uint8 * pGsTx_ctr[HdGsTx_Num];
    Uint8 * pSvTx_ctr[HdSvTx_Num];

	Uint32  checksum;
	Uint8	check_err;
	
    // Output variables for HTM

    // Output variables for other components
	Uint8 RAM_ERR;
	Uint8 TWO_SYS_CMP_ERR;

	Uint32 utc_sec;
	Uint16 utc_ms;

    Uint8  GsTx_ctr;    // GOOSE发送控制
    Uint8  SvTx_ctr;    // SV 发送控制
	
    // Private variables
    
} GLOBAL_VAR;


extern GLOBAL_VAR *newGLOBAL_VAR(Component *parent,const char *name);
extern int initGLOBAL_VAR(GLOBAL_VAR *dp);
extern void GLOBAL_VARCal(GLOBAL_VAR *dp);

#endif

