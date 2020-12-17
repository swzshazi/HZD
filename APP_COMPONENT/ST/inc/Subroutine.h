 /****************************************************************************************************
*                                                                       *
*          Description : Subfunction Component                                                    *
******************************************************************************************************/
#ifndef _SUB_
#define _SUB_

#include "hzplatform.h"

//CODE_DATA_OUT_CHIP  
Uint32* init_setcheck(Uint32 *check_head,Uint32 *check_sum,Uint32 *check_len,Uint32 *check_len_check);
//CODE_IN_CHIP_C  
void  check_set(Uint8 *mem_error,Uint32 *check_array,Uint32 *check_head,Uint32 check_len,Uint32 check_len_check);

extern void get_offset(int16 data, Uint32 *num,int32 *sum, int32 *offset);
#endif

