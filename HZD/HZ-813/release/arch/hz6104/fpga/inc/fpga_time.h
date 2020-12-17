

#ifndef _FPGA_SYNC_H_
#define _FPGA_SYNC_H_

#include "fpga_base.h"

 typedef struct
{
    volatile Uint32  pps_src_sel:3;
    volatile Uint32  resever_bit1:1;  
    volatile Uint32  pps_resample:1;
    volatile Uint32  pps_polar:2;
    volatile Uint32  resever_bit2:1;      
    volatile Uint32  pps_out_en:1;
    volatile Uint32  pps_fake_pps_sel:1;
    volatile Uint32  resever_bit3:2;    
    volatile Uint32  pps_fake_pps_en:1;
    volatile Uint32  test_pps_en:1;
    volatile Uint32  debug_pps_tic_en:1;
    volatile Uint32  resever_bit4:1;     
    volatile Uint32  resever_bit5:16;  
    
    volatile Uint32  pps_local_timer;            //1
    volatile Uint32  set_fake_pps_start;         //2
    volatile Uint32  fake_pps_local_timer;       //3
    volatile Uint32  real_timer;                 //4
    volatile Uint32  clk10k_timer;              //5
    
    volatile Uint32  time_siganl_state;              //6
    volatile Uint32  debug_pps_local_timer_wr;        //7
    volatile Uint32  debug_pps_local_timer_rd;       //8
    volatile Uint32  test_pps_start;                  //9

    volatile Uint32  resver_u32[6];              //10~0xf
    
    volatile Uint32  irigbi_info1;
    volatile Uint32  irigbi_info2;
    volatile Uint32  irigbi_info3;
    volatile Uint32  resver_u32_2[5];              //13~17
    
    volatile Uint32  irgbi_link_err_cnt:16;             //18
    volatile Uint32  irgbi_wave_err_cnt:16;             //18
    
    volatile Uint32  irigbi_rx_cnt_all:16;              //19
    volatile Uint32  irigbi_rx_cnt_ok:16;              //19
    
    volatile Uint32  irigbi_rx_cnt_fail:16;             //1a
    volatile Uint32  resver_u32_3:16;                   //1a
}SYNC_REG;



 typedef struct
{
///////////////////////addr = 0x0//////////////////////////////////////////    
    volatile Uint32   ms_cnt;           
///////////////////////addr = 0x1//////////////////////////////////////////    
    volatile Uint32   fake_pps_local_timer;           
///////////////////////addr = 0x2//////////////////////////////////////////    
    volatile Uint32   pps_local_timer;  
///////////////////////addr = 0x2//////////////////////////////////////////    
    volatile Uint32   real_timer;  
}SLAVE_SYNC_REG;
    


#endif 




