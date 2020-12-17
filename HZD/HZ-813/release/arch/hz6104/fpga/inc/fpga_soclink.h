#ifndef _FPGA_SOCLINK_H_
#define _FPGA_SOCLINK_H_

#include "fpga_base.h"


 typedef struct    
{
    Uint32 set_enable :1;
    Uint32 reserve_1:31;
    Uint32 reserve_2[3];
    Uint32 wr_cnt;
    Uint32 rst_cnt;

}SOC_LINK_MAP;


#endif




