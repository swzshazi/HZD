/********************************************************************************************
*          File Name   : QD.h                                                         *
*          Description : Type definitions, prototype declaration for the QD.          *
********************************************************************************************/

#ifndef _QD_
#define _QD_

#ifdef __cplusplus
extern "C" {
#endif

#include "hzplatform.h"
#include "CommFun.h"

// Constant macro definition

/* input variables :*/

#define		QD_NUM		4




// Component type definition : QD
typedef struct
{
    #include "base.h"

    // Parameter
    
    // Input variables
    Uint32 start;
	
	Uint8 *QD_ELSE;			//另外一套启动信号			
	Uint8 *QD1_in[QD_NUM];
	Uint8 *QD2_in[QD_NUM];
	Uint8 *QD3_in[QD_NUM];
	Uint8 *QD4_in[QD_NUM];
	

	Uint32  checksum;
	Uint8	check_err;
	
    // Output variables for HTM
    Uint8 	QD;
	Uint8 	QD1;
	Uint8 	QD2;
	Uint8 	QD3;
	Uint8 	QD4;
	
	Uint8 	QD_ERR;
	Uint16  QD_CNT;

	Uint8 	CMP_ERR;
	Uint16  CMP_CNT;

    // Output variables for other components
	
    // Private variables
    
} QD;


extern QD *newQD(Component *parent,const char *name);
extern int initQD(QD *dp);
extern void QDCal(QD *dp);

#endif

