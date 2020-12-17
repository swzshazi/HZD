/********************************************************************************************
*          File Name   : DevAlarm.h                                                         *
*          Description : Type definitions, prototype declaration for the DevAlarm.          *
********************************************************************************************/

#ifndef _DevAlarm_
#define _DevAlarm_

#ifdef __cplusplus
extern "C" {
#endif

#include "hzplatform.h"
#include "CommFun.h"

// Constant macro definition

/* input variables :*/

#define		BJJ_NUM1	16
#define		BJJ_NUM2	16
#define		BJJ_NUM3	16

#define		BSJ_NUM1	16




// Component type definition : DevAlarm
typedef struct
{
    #include "base.h"

    // Parameter
    
    // Input variables
    Uint32 start;

	Uint8 *bjj_in1[BJJ_NUM1];
	Uint8 *bjj_in2[BJJ_NUM2];
	Uint8 *bjj_in3[BJJ_NUM3];
	
	Uint8 *bsj_in[BSJ_NUM1];

	Uint32  checksum;
	Uint8	check_err;
	
    // Output variables for HTM

    // Output variables for other components
	Uint8 bsj_sum;
	Uint8 bjj_sum;
	Uint8 bjj1_sum;
	Uint8 bjj2_sum;
	Uint8 bjj3_sum;
	Uint8 RAM_ERR;
	Uint8 TWO_SYS_CMP_ERR;	
	
    // Private variables
    
} DevAlarm;


extern DevAlarm *newDevAlarm(Component *parent,const char *name);
extern int initDevAlarm(DevAlarm *dp);
extern void DevAlarmCal(DevAlarm *dp);

#endif

