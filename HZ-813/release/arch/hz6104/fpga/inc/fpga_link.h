
#ifndef _FPGA_LINK_H_
#define _FPGA_LINK_H_

#include "fpga_base.h"
//--------------xilinx_7 series chip_Link module   ------------------------------//
 typedef struct
{
/////////////////////addr=0x0 通道初始化///////////////////////////////////////    
    Uint32 chan0_tx_enable:1;           // ADC互推
    Uint32 chan0_rx_enable:1;
    Uint32 chan0_reserve:30;
    
/////////////////////addr=0x1 通道初始化///////////////////////////////////////    
    Uint32 chan1_tx_enable:1;          // 软件互推
    Uint32 chan1_rx_enable:1;
    Uint32 chan1_reserve:30;   

/////////////////////addr=0x2 通道初始化///////////////////////////////////////    
    Uint32 chan2_tx_enable:1;          // 过程层互推
    Uint32 chan2_rx_enable:1;
    Uint32 chan2_reserve:30;       

/////////////////////addr=0x3~0x7 通道初始化///////////////////////////////////////    
    Uint32 chan_reserve[5];  
    
/////////////////////addr=0x8 物理层初始化/////////////////////////    
    Uint32 phy_set_tx_rst:1;
    Uint32 phy_set_rx_rst:1;
    Uint32 phy_set_pll_rst:1;
    Uint32 phy_reserve1:5;
    Uint32 phy_set_loop:3;
    Uint32 phy_reserve2:21;
   
/////////////////////addr=0x9 时钟实时计数器/////////////////////////    
    Uint32 rx_all_cnt:16;    
    Uint32 rx_ok_cnt:16;   
    
/////////////////////addr=0xa 时钟实时计数器/////////////////////////    
    Uint32 rx_err_cnt:16;    
    Uint32 reserve_cnt:16;    

/////////////////////addr=0xb 时钟实时计数器/////////////////////////    
    Uint32 ref_clk_cnt:16;    
    Uint32 ref_clk_reserve:16;        

/////////////////////addr=0xc 时钟实时计数器/////////////////////////    
    Uint32 link_tx_clk_cnt:16;    
    Uint32 link_rx_clk_cnt:16;   
    
/////////////////////addr=0xd~0xe 时钟实时计数器/////////////////////////    
    Uint32 reserve_cntd[2];    
    
    
/////////////////////addr=0xf 时钟实时计数器/////////////////////////    
    Uint32 module_version;     // 0xf

/////////////////////addr=0x10 通道发送统计/////////////////////////    
    Uint32 chan0_tx_ok_cnt:16;
    Uint32 chan0_tx_err_cnt:16;

/////////////////////addr=0x11 通道发送统计/////////////////////////    
    Uint32 chan1_tx_ok_cnt:16;
    Uint32 chan1_tx_err_cnt:16;

/////////////////////addr=0x12 通道发送统计/////////////////////////    
    Uint32 chan2_tx_ok_cnt:16;
    Uint32 chan2_tx_err_cnt:16;   
    
}LINK_REG_MAP;


/*////////////////操作说明  TIPS////////////////////////////////////////////////////////////////////////////
//    1、 initDsp阶段（FPGA已经配置完成），对硬件进行初始化，操作（phy_set_rx_rst，phy_set_tx_rst，置1再置0
//    2、 元件初始化阶段或第1个应用任务，可以配置各通道接收使能（chan0_rx_enable，chan1_rx_enable，chan2_rx_enable)，置1为使能
//    3、 第1个应用任务，配置各通道发送使能（chan0_tx_enable，chan1_tx_enable，chan2_tx_enable），置1为使能   
//    
//
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#endif // end of _INC_FRAM_H




