/* FileName: AIOGs16.h */
#ifndef _AIOGs16_H
#define _AIOGs16_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"

// 开关量GS数目
#define AIOGs_Num   16

/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	float32		*pAIO_GSE[AIOGs_Num];        // 模拟量Gs值
	Uint8		*pAIO_GSE_ok[AIOGs_Num];     // 模拟量Gs品质

	/* output variables :*/
	float32	    AIO_GSE[AIOGs_Num];          // 模拟量Gs值

	//private

	
} AIOGs16;


extern  AIOGs16  *newAIOGs16(Component *parent, const char *name);
extern int  initAIOGs16(AIOGs16 *dp);

#endif
