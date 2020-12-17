/* FileName: DEBUGU.h */
#ifndef _DEBUGU_H
#define _DEBUGU_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"
//#include "symbol_type_defines.h"



/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint32 	start;
	Uint8	*dbg_b1_in;
	Uint8	*dbg_b2_in;
	Uint8	*dbg_b3_in;
	Uint8	*dbg_b4_in;
	Uint8	*dbg_b5_in;
	Uint8	*dbg_b6_in;
	Uint8	*dbg_b7_in;
	Uint8	*dbg_b8_in;

	
	Uint16	*dbg_s1_in;
	Uint16	*dbg_s2_in;
	Uint16	*dbg_s3_in;
	Uint16	*dbg_s4_in;
	Uint16	*dbg_s5_in;
	Uint16	*dbg_s6_in;
	Uint16	*dbg_s7_in;
	Uint16	*dbg_s8_in;

	float32	*dbg_f1_in;
	float32	*dbg_f2_in;
	float32	*dbg_f3_in;
	float32	*dbg_f4_in;
	float32	*dbg_f5_in;
	float32	*dbg_f6_in;
	float32	*dbg_f7_in;
	float32	*dbg_f8_in;
	
	Uint32  checksum;
	Uint8	check_err;
	/* output variables :*/


	Uint8	dbg_b1;
	Uint8	dbg_b2;
	Uint8	dbg_b3;
	Uint8	dbg_b4;
	Uint8	dbg_b5;
	Uint8	dbg_b6;
	Uint8	dbg_b7;
	Uint8	dbg_b8;

	Uint16	dbg_s1;
	Uint16	dbg_s2;
	Uint16	dbg_s3;
	Uint16	dbg_s4;
	Uint16	dbg_s5;
	Uint16	dbg_s6;
	Uint16	dbg_s7;
	Uint16	dbg_s8;

	float32	dbg_f1;
	float32	dbg_f2;
	float32	dbg_f3;
	float32	dbg_f4;
	float32	dbg_f5;
	float32	dbg_f6;
	float32	dbg_f7;
	float32	dbg_f8;

	//private

} DEBUGU;


extern  DEBUGU  *newDEBUGU(Component *parent, const char *name);
extern int  initDEBUGU(DEBUGU *dp);

#endif
