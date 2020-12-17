/* FileName: BIOGs16.h */
#ifndef _BIOGs16_H
#define _BIOGs16_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"

// 开关量GS数目
#define BIOGs_Num   16 

/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint8		*pBIO_GSE[BIOGs_Num];        // 开关量Gs值
	Uint8		*pBIO_GSE_ok[BIOGs_Num];     // 开关量Gs品质

	/* output variables :*/
	Uint8	    BIO_GSE[BIOGs_Num];          // 开关量Gs值

	//private

	
} BIOGs16;


extern  BIOGs16  *newBIOGs16(Component *parent, const char *name);
extern int  initBIOGs16(BIOGs16 *dp);

#endif
