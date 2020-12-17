

#ifndef _FPGA_SYNC_H_
#define _FPGA_SYNC_H_

//#include "fpga_base.h"
//-----------------------            ------------------------------//
#define TICK_1S                    20000000UL            // 1000*1000*20
#define TICK_250US                 5000UL
#define TICK_125US                 2500
#define TICK_100US                 2000
#define TICK_10US                  200
#define TICK_1US                   20

 typedef struct
{
    volatile Uint16  set_enable:1;
    volatile Uint16  cfg0_reserver1:3;
    volatile Uint16  set_pps_sel:3;    
    volatile Uint16  cfg0_reserver2:1;
    volatile Uint16  set_resample:1;
    volatile Uint16  set_polar:1;
    volatile Uint16  cfg0_reserver3:6;
   
    volatile Uint16  bcd_second:7;
    volatile Uint16  cfg1_reserver1:1;
    volatile Uint16  bcd_minute:7;
    volatile Uint16  cfg1_loading:1;

    volatile Uint16  bcd_hour:6;
    volatile Uint16  cfg2_reserver1:9;
    volatile Uint16  cfg2_loading:1;
    
    volatile Uint16  bcd_date:10;
    volatile Uint16  cfg3_reserver1:5;
    volatile Uint16  cfg3_loading:1;    
    
    volatile Uint16  bcd_year:11;
    volatile Uint16  cfg4_reserver1:4;
    volatile Uint16  cfg4_loading:1;    

    volatile Uint16  satl:3;
    volatile Uint16  cfg5_reserver1:1;
    volatile Uint16  qual:4;
    volatile Uint16  idle:1;    
    volatile Uint16  parity_err:1;    
    volatile Uint16  cfg5_reserver2:5;    
    volatile Uint16  cfg5_loading:1;    

    volatile Uint16  leap_offset:9;
    volatile Uint16  cfg6_reserver1:7;    
    
    volatile Uint16  cfg_reserver7;   
    
    volatile Uint16  irigbi_rx_cnt_all;              //0x8
    volatile Uint16  irigbi_rx_cnt_ok;               //0x9
    volatile Uint16  irigbi_rx_cnt_fail;             //0xa
    volatile Uint16  irgbi_link_err_cnt;             //0xb
    volatile Uint16  irgbi_wave_err_cnt;             //0xc   

    volatile Uint16  cfg_reserverd[3];   

	///////////////////////fake pps cfg //////////////////////////
    volatile Uint16  set_fake_pps_en:1;              //0x10 
    volatile Uint16  set_fake_pps_mode:1;            //0x10 	  
    volatile Uint16  cfg_reserver10:14;              //0x10   
    volatile Uint16  cfg_reserver11[3];            
    volatile Uint32  set_fake_pps_start;            // 0x14~0x15
    volatile Uint32  set_fake_pps_period;           // 0x16~0x17
    volatile Uint32  fake_pps_trig_tic;             // 0x18~0x19	
    volatile Uint16  cfg_reserver18[6];   
	
	///////////////////////debug pps cfg //////////////////////////
    volatile Uint16  set_debug_pps_en:1;              //0x20   
    volatile Uint16  set_debug_pps_mode:1;            //0x20   	
    volatile Uint16  cfg_reserver20:14;              //0x10   
    volatile Uint16  cfg_reserver21[3];            
    volatile Uint32  set_debug_pps_start;             // 0x24~0x25
    volatile Uint32  set_debug_pps_period;            // 0x26~0x27
    volatile Uint32  debug_pps_trig_tic;             // 0x28~0x29
    volatile Uint16  cfg_reserver28[6];     
	
	///////////////////////debug test-pps cfg //////////////////////////
    volatile Uint16  set_test_pps_en:1;              //0x30   
    volatile Uint16  set_test_pps_mode:1;            //0x30  	
    volatile Uint16  cfg_reserver30:14;              //0x30   
    volatile Uint16  cfg_reserver31[3];            
    volatile Uint32  set_test_pps_start;             // 0x34~0x35
    volatile Uint32  set_test_pps_period;            // 0x36~0x37
    volatile Uint32  test_pps_trig_tic;              // 0x38~0x39	
    volatile Uint16  cfg_reserver38[6];   

        
    volatile Uint32  pps_timer;                     // 0x40~0x41  
    volatile Uint32  ocxo_pps_timer;                // 0x42~0x43          
    volatile Uint32  int1_timer;                    // 0x44~0x45          
    volatile Uint32  int2_timer;                    // 0x46~0x47        
    volatile Uint32  ocxo_int1_timer;               // 0x48~0x49             
    volatile Uint32  ocxo_int2_timer;               // 0x4a~0x4b        
    volatile Uint32  fake_pps_locked_time;          // 0x4c~0x4d
    volatile Uint32  real_htm_tick;                 // 0x4e~0x4f
    
}SYNC_REG;


#define pFake_pps_AddrL      (volatile Uint16 *)(FPGA_EMIF_BASE_ADDR + 0x14c*2)
#define pFake_pps_AddrH      (volatile Uint16 *)(FPGA_EMIF_BASE_ADDR + 0x14d*2)

/*

volatile SYNC_REG *syn_cfg_reg = NULL; 

syn_cfg_reg =(SYNC_REG *)FPGA_SYN_ADDR;

syn_cfg_reg->set_enable=1;


*/

#endif 
