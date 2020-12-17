/* FileName: OutDPosGs.h */
#ifndef _OutDPosGs_H
#define _OutDPosGs_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"


/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint8		*pTest;            // 装置检修态
	Uint8		*pHwj_GSE;         // Hwj_Gs
	Uint8		*pHwj_GSE_ok;  
	Uint8		*pTwj_GSE;         // Twj_Gs
	Uint8		*pTwj_GSE_ok; 

	/* output variables :*/
	Uint8	    Hwj_Lock;          // 合位--电气联闭锁用
	Uint8	    Twj_Lock;          // 跳位--电气联闭锁用

	Uint8	    Hwj_Logic;         // 合位--逻辑用
	Uint8	    Twj_Logic;         // 合位--逻辑用

	//private

	
} OutDPosGs;


extern  OutDPosGs  *newOutDPosGs(Component *parent, const char *name);
extern int  initOutDPosGs(OutDPosGs *dp);

#endif
