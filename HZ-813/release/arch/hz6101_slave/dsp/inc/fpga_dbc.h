/********************************************************************
*     File Name   : fpga_IEC60044-8.h             *
*     Date    : 2016 Halloween              *
*     Written by  : Zhaoyc                  *
*     Description : TX & RX module register definitions.
//  Ver | dd mmm yyyy | Author | Description of changes                      //
//  ====|=============|========|===========================================  //
//  0.9|        2018-10-23 |        |                                             //		*
********************************************************************/
#include "fpga_base.h"

#ifndef _fpga_dbc_
#define _fpga_dbc_

//baud rate
#define DBC_BAUDRATE_10M        0x0000    // 10 Mbps
#define DBC_BAUDRATE_5M         0x0001    // 5 Mbps
#define DBC_BAUDRATE_2M5        0x0002    // 2.5 Mbps
#define DBC_BAUDRATE_20M        0x0003    // 20 Mbps

//The application layer frame structure between DSP and FPGA
#define DBC_FRAME_HEAD          0x7E7E
#define DBC_FRAME_EOF           0x55AA

//Optical logic
#define DBC_OPT_LOGIC_POSITIVE			    0x0000
#define DBC_OPT_LOGIC_NEGATIVE				0x0040

//发送模式BIT位
#define DBC_CTRLWORD_TX_ON_TIME             0x0000          //定时
#define DBC_CTRLWORD_TX_AT_ONCE             0x0004          //即时

//接收使能BIT位
#define DBC_FPGA_RX_ENA_BIT                 0x0080
#define DBC_FPGA_RX_DIS_BIT                 0xFF7F

//接收状态寄存器BIT位
#define DBC_FPGA_RX_TIMEOUT_BIT             0x01
#define DBC_FPGA_RX_LINKERR_BIT             0x02

//发送状态寄存器BIT位
#define DBC_FPGA_TX_ERROR_BIT               0x01

//接收使能BIT位
#define DBC_FPGA_TX_ENA_BIT                 0x0080
#define DBC_FPGA_TX_DIS_BIT                 0xFF7F



//RXModules
#define DBC_RXMODULE1_CTRLREG         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0000*2)
#define DBC_RXMODULE1_TIMEOUT_SETTING (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0001*2)
#define DBC_RXMODULE1_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0002*2)
#define DBC_RXMODULE1_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0003*2)
#define DBC_RXMODULE1_STATUSREG       (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0008*2)
#define DBC_RXMODULE1_ALL_CNT         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x000A*2)
#define DBC_RXMODULE1_OK_CNT          (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0009*2)
#define DBC_RXMODULE1_FAIL_CNT        (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x000C*2)
#define DBC_RXMODULE1_TIMEOUT_CNT     (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x000B*2)
#define DBC_RXMODULE1_FRAME_LOST_CNT  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x000D*2)

#define DBC_RXMODULE2_CTRLREG         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0010*2)
#define DBC_RXMODULE2_TIMEOUT_SETTING (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0011*2)
#define DBC_RXMODULE2_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0012*2)
#define DBC_RXMODULE2_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0013*2)
#define DBC_RXMODULE2_STATUSREG       (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0018*2)
#define DBC_RXMODULE2_ALL_CNT         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x001A*2)
#define DBC_RXMODULE2_OK_CNT          (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0019*2)
#define DBC_RXMODULE2_FAIL_CNT        (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x001C*2)
#define DBC_RXMODULE2_TIMEOUT_CNT     (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x001B*2)
#define DBC_RXMODULE2_FRAME_LOST_CNT  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x001D*2)
                                                                                  
#define DBC_RXMODULE3_CTRLREG         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0020*2)
#define DBC_RXMODULE3_TIMEOUT_SETTING (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0021*2)
#define DBC_RXMODULE3_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0022*2)
#define DBC_RXMODULE3_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0023*2)
#define DBC_RXMODULE3_STATUSREG       (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0028*2)
#define DBC_RXMODULE3_ALL_CNT         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x002A*2)
#define DBC_RXMODULE3_OK_CNT          (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0029*2)
#define DBC_RXMODULE3_FAIL_CNT        (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x002C*2)
#define DBC_RXMODULE3_TIMEOUT_CNT     (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x002B*2)
#define DBC_RXMODULE3_FRAME_LOST_CNT  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x002D*2)
                                                                                  
#define DBC_RXMODULE4_CTRLREG         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0030*2)
#define DBC_RXMODULE4_TIMEOUT_SETTING (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0031*2)
#define DBC_RXMODULE4_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0032*2)
#define DBC_RXMODULE4_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0033*2)
#define DBC_RXMODULE4_STATUSREG       (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0038*2)
#define DBC_RXMODULE4_ALL_CNT         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x003A*2)
#define DBC_RXMODULE4_OK_CNT          (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0039*2)
#define DBC_RXMODULE4_FAIL_CNT        (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x003C*2)
#define DBC_RXMODULE4_TIMEOUT_CNT     (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x003B*2)
#define DBC_RXMODULE4_FRAME_LOST_CNT  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x003D*2)
                                                                                  
#define DBC_RXMODULE5_CTRLREG         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0040*2)
#define DBC_RXMODULE5_TIMEOUT_SETTING (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0041*2)
#define DBC_RXMODULE5_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0042*2)
#define DBC_RXMODULE5_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0043*2)
#define DBC_RXMODULE5_STATUSREG       (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0048*2)
#define DBC_RXMODULE5_ALL_CNT         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x004A*2)
#define DBC_RXMODULE5_OK_CNT          (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0049*2)
#define DBC_RXMODULE5_FAIL_CNT        (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x004C*2)
#define DBC_RXMODULE5_TIMEOUT_CNT     (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x004B*2)
#define DBC_RXMODULE5_FRAME_LOST_CNT  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x004D*2)
                                                                                  
#define DBC_RXMODULE6_CTRLREG         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0050*2)
#define DBC_RXMODULE6_TIMEOUT_SETTING (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0051*2)
#define DBC_RXMODULE6_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0052*2)
#define DBC_RXMODULE6_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0053*2)
#define DBC_RXMODULE6_STATUSREG       (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0058*2)
#define DBC_RXMODULE6_ALL_CNT         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x005A*2)
#define DBC_RXMODULE6_OK_CNT          (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0059*2)
#define DBC_RXMODULE6_FAIL_CNT        (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x005C*2)
#define DBC_RXMODULE6_TIMEOUT_CNT     (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x005B*2)
#define DBC_RXMODULE6_FRAME_LOST_CNT  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x005D*2)
                                                                                  
#define DBC_RXMODULE7_CTRLREG         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0060*2)
#define DBC_RXMODULE7_TIMEOUT_SETTING (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0061*2)
#define DBC_RXMODULE7_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0062*2)
#define DBC_RXMODULE7_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0063*2)
#define DBC_RXMODULE7_STATUSREG       (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0068*2)
#define DBC_RXMODULE7_ALL_CNT         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x006A*2)
#define DBC_RXMODULE7_OK_CNT          (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0069*2)
#define DBC_RXMODULE7_FAIL_CNT        (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x006C*2)
#define DBC_RXMODULE7_TIMEOUT_CNT     (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x006B*2)
#define DBC_RXMODULE7_FRAME_LOST_CNT  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x006D*2)
                                                                                  
#define DBC_RXMODULE8_CTRLREG         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0070*2)
#define DBC_RXMODULE8_TIMEOUT_SETTING (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0071*2)
#define DBC_RXMODULE8_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0072*2)
#define DBC_RXMODULE8_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0073*2)
#define DBC_RXMODULE8_STATUSREG       (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0078*2)
#define DBC_RXMODULE8_ALL_CNT         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x007A*2)
#define DBC_RXMODULE8_OK_CNT          (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0079*2)
#define DBC_RXMODULE8_FAIL_CNT        (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x007C*2)
#define DBC_RXMODULE8_TIMEOUT_CNT     (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x007B*2)
#define DBC_RXMODULE8_FRAME_LOST_CNT  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x007D*2)

#define DBC_RXMODULE9_CTRLREG         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0080*2)
#define DBC_RXMODULE9_TIMEOUT_SETTING (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0081*2)
#define DBC_RXMODULE9_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0082*2)
#define DBC_RXMODULE9_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0083*2)
#define DBC_RXMODULE9_STATUSREG       (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0088*2)
#define DBC_RXMODULE9_ALL_CNT         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x008A*2)
#define DBC_RXMODULE9_OK_CNT          (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0089*2)
#define DBC_RXMODULE9_FAIL_CNT        (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x008C*2)
#define DBC_RXMODULE9_TIMEOUT_CNT     (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x008B*2)
#define DBC_RXMODULE9_FRAME_LOST_CNT  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x008D*2)

#define DBC_RXMODULE10_CTRLREG        (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0090*2)
#define DBC_RXMODULE10_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0091*2)
#define DBC_RXMODULE10_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0092*2)
#define DBC_RXMODULE10_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0093*2)
#define DBC_RXMODULE10_STATUSREG      (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0098*2)
#define DBC_RXMODULE10_ALL_CNT        (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x009A*2)
#define DBC_RXMODULE10_OK_CNT         (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x0099*2)
#define DBC_RXMODULE10_FAIL_CNT       (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x009C*2)
#define DBC_RXMODULE10_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x009B*2)
#define DBC_RXMODULE10_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_PCP_PPR_RXMOD_ADDR+0x009D*2)

#define DBC_RXMODULE11_CTRLREG        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0000*2)
#define DBC_RXMODULE11_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0001*2)
#define DBC_RXMODULE11_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0002*2)
#define DBC_RXMODULE11_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0003*2)
#define DBC_RXMODULE11_STATUSREG      (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0008*2)
#define DBC_RXMODULE11_ALL_CNT        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x000A*2)
#define DBC_RXMODULE11_OK_CNT         (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0009*2)
#define DBC_RXMODULE11_FAIL_CNT       (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x000C*2)
#define DBC_RXMODULE11_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x000B*2)
#define DBC_RXMODULE11_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x000D*2)

#define DBC_RXMODULE12_CTRLREG        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0010*2)
#define DBC_RXMODULE12_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0011*2)
#define DBC_RXMODULE12_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0012*2)
#define DBC_RXMODULE12_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0013*2)
#define DBC_RXMODULE12_STATUSREG      (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0018*2)
#define DBC_RXMODULE12_ALL_CNT        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x001A*2)
#define DBC_RXMODULE12_OK_CNT         (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0019*2)
#define DBC_RXMODULE12_FAIL_CNT       (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x001C*2)
#define DBC_RXMODULE12_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x001B*2)
#define DBC_RXMODULE12_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x001D*2)

#define DBC_RXMODULE13_CTRLREG        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0020*2)
#define DBC_RXMODULE13_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0021*2)
#define DBC_RXMODULE13_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0022*2)
#define DBC_RXMODULE13_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0023*2)
#define DBC_RXMODULE13_STATUSREG      (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0028*2)
#define DBC_RXMODULE13_ALL_CNT        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x002A*2)
#define DBC_RXMODULE13_OK_CNT         (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0029*2)
#define DBC_RXMODULE13_FAIL_CNT       (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x002C*2)
#define DBC_RXMODULE13_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x002B*2)
#define DBC_RXMODULE13_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x002D*2)

#define DBC_RXMODULE14_CTRLREG        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0030*2)
#define DBC_RXMODULE14_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0031*2)
#define DBC_RXMODULE14_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0032*2)
#define DBC_RXMODULE14_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0033*2)
#define DBC_RXMODULE14_STATUSREG      (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0038*2)
#define DBC_RXMODULE14_ALL_CNT        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x003A*2)
#define DBC_RXMODULE14_OK_CNT         (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0039*2)
#define DBC_RXMODULE14_FAIL_CNT       (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x003C*2)
#define DBC_RXMODULE14_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x003B*2)
#define DBC_RXMODULE14_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x003D*2)

#define DBC_RXMODULE15_CTRLREG        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0040*2)
#define DBC_RXMODULE15_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0041*2)
#define DBC_RXMODULE15_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0042*2)
#define DBC_RXMODULE15_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0043*2)
#define DBC_RXMODULE15_STATUSREG      (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0048*2)
#define DBC_RXMODULE15_ALL_CNT        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x004A*2)
#define DBC_RXMODULE15_OK_CNT         (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0049*2)
#define DBC_RXMODULE15_FAIL_CNT       (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x004C*2)
#define DBC_RXMODULE15_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x004B*2)
#define DBC_RXMODULE15_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x004D*2)

#define DBC_RXMODULE16_CTRLREG        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0050*2)
#define DBC_RXMODULE16_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0051*2)
#define DBC_RXMODULE16_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0052*2)
#define DBC_RXMODULE16_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0053*2)
#define DBC_RXMODULE16_STATUSREG      (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0058*2)
#define DBC_RXMODULE16_ALL_CNT        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x005A*2)
#define DBC_RXMODULE16_OK_CNT       (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0059*2)
#define DBC_RXMODULE16_FAIL_CNT     (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x005C*2)
#define DBC_RXMODULE16_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x005B*2)
#define DBC_RXMODULE16_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x005D*2)

#define DBC_RXMODULE17_CTRLREG        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0060*2)
#define DBC_RXMODULE17_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0061*2)
#define DBC_RXMODULE17_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0062*2)
#define DBC_RXMODULE17_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0063*2)
#define DBC_RXMODULE17_STATUSREG      (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0068*2)
#define DBC_RXMODULE17_ALL_CNT        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x006A*2)
#define DBC_RXMODULE17_OK_CNT       (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0069*2)
#define DBC_RXMODULE17_FAIL_CNT     (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x006C*2)
#define DBC_RXMODULE17_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x006B*2)
#define DBC_RXMODULE17_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x006D*2)

#define DBC_RXMODULE18_CTRLREG        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0070*2)
#define DBC_RXMODULE18_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0071*2)
#define DBC_RXMODULE18_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0072*2)
#define DBC_RXMODULE18_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0073*2)
#define DBC_RXMODULE18_STATUSREG      (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0078*2)
#define DBC_RXMODULE18_ALL_CNT        (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x007A*2)
#define DBC_RXMODULE18_OK_CNT       (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x0079*2)
#define DBC_RXMODULE18_FAIL_CNT     (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x007C*2)
#define DBC_RXMODULE18_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x007B*2)
#define DBC_RXMODULE18_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_FEU_RXMOD_ADDR+0x007D*2)

#define DBC_RXMODULE19_CTRLREG        (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0000*2)
#define DBC_RXMODULE19_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0001*2)
#define DBC_RXMODULE19_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0002*2)
#define DBC_RXMODULE19_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0003*2)
#define DBC_RXMODULE19_STATUSREG      (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0008*2)
#define DBC_RXMODULE19_ALL_CNT        (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x000A*2)
#define DBC_RXMODULE19_OK_CNT       (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0009*2)
#define DBC_RXMODULE19_FAIL_CNT     (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x000C*2)
#define DBC_RXMODULE19_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x000B*2)
#define DBC_RXMODULE19_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x000D*2)

#define DBC_RXMODULE20_CTRLREG        (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0010*2)
#define DBC_RXMODULE20_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0011*2)
#define DBC_RXMODULE20_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0012*2)
#define DBC_RXMODULE20_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0013*2)
#define DBC_RXMODULE20_STATUSREG      (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0018*2)
#define DBC_RXMODULE20_ALL_CNT        (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x001A*2)
#define DBC_RXMODULE20_OK_CNT       (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x0019*2)
#define DBC_RXMODULE20_FAIL_CNT     (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x001C*2)
#define DBC_RXMODULE20_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x001B*2)
#define DBC_RXMODULE20_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_MU_PR_MOD_ADDR+0x001D*2)

#define DBC_RXMODULE21_CTRLREG        (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0000*2)
#define DBC_RXMODULE21_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0001*2)
#define DBC_RXMODULE21_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0002*2)
#define DBC_RXMODULE21_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0003*2)
#define DBC_RXMODULE21_STATUSREG      (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0008*2)
#define DBC_RXMODULE21_ALL_CNT        (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x000A*2)
#define DBC_RXMODULE21_OK_CNT       (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0009*2)
#define DBC_RXMODULE21_FAIL_CNT     (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x000C*2)
#define DBC_RXMODULE21_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x000B*2)
#define DBC_RXMODULE21_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x000D*2)

#define DBC_RXMODULE22_CTRLREG        (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0010*2)
#define DBC_RXMODULE22_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0011*2)
#define DBC_RXMODULE22_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0012*2)
#define DBC_RXMODULE22_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0013*2)
#define DBC_RXMODULE22_STATUSREG      (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0018*2)
#define DBC_RXMODULE22_ALL_CNT        (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x001A*2)
#define DBC_RXMODULE22_OK_CNT       (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x0019*2)
#define DBC_RXMODULE22_FAIL_CNT     (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x001C*2)
#define DBC_RXMODULE22_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x001B*2)
#define DBC_RXMODULE22_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_MOV_MOD_ADDR+0x001D*2)

#define DBC_RXMODULE23_CTRLREG        (volatile Uint16 *)(FPGA_UPS_MOD_ADDR+0x0000*2)
#define DBC_RXMODULE23_TIMEOUT_SETTING  (volatile Uint16 *)(FPGA_UPS_MOD_ADDR+0x0001*2)
#define DBC_RXMODULE23_BLOCK_WORD_NUM (volatile Uint16 *)(FPGA_UPS_MOD_ADDR+0x0002*2)
#define DBC_RXMODULE23_TOTAL_WORD_NUM (volatile Uint16 *)(FPGA_UPS_MOD_ADDR+0x0003*2)
#define DBC_RXMODULE23_STATUSREG      (volatile Uint16 *)(FPGA_UPS_MOD_ADDR+0x0008*2)
#define DBC_RXMODULE23_ALL_CNT        (volatile Uint16 *)(FPGA_UPS_MOD_ADDR+0x000A*2)
#define DBC_RXMODULE23_OK_CNT       (volatile Uint16 *)(FPGA_UPS_MOD_ADDR+0x0009*2)
#define DBC_RXMODULE23_FAIL_CNT     (volatile Uint16 *)(FPGA_UPS_MOD_ADDR+0x000C*2)
#define DBC_RXMODULE23_TIMEOUT_CNT    (volatile Uint16 *)(FPGA_UPS_MOD_ADDR+0x000B*2)
#define DBC_RXMODULE23_FRAME_LOST_CNT (volatile Uint16 *)(FPGA_UPS_MOD_ADDR+0x000D*2)

#define DBC_RXMODULE24_CTRLREG       	(volatile Uint16 *)(FPGA_RES_MOD_ADDR+0x0000*2)
#define DBC_RXMODULE24_TIMEOUT_SETTING	(volatile Uint16 *)(FPGA_RES_MOD_ADDR+0x0001*2)
#define DBC_RXMODULE24_BLOCK_WORD_NUM	(volatile Uint16 *)(FPGA_RES_MOD_ADDR+0x0002*2)
#define DBC_RXMODULE24_TOTAL_WORD_NUM	(volatile Uint16 *)(FPGA_RES_MOD_ADDR+0x0003*2)
#define DBC_RXMODULE24_STATUSREG     	(volatile Uint16 *)(FPGA_RES_MOD_ADDR+0x0008*2)
#define DBC_RXMODULE24_ALL_CNT		    (volatile Uint16 *)(FPGA_RES_MOD_ADDR+0x000A*2)
#define DBC_RXMODULE24_OK_CNT		    (volatile Uint16 *)(FPGA_RES_MOD_ADDR+0x0009*2)
#define DBC_RXMODULE24_FAIL_CNT			(volatile Uint16 *)(FPGA_RES_MOD_ADDR+0x000C*2)
#define DBC_RXMODULE24_TIMEOUT_CNT		(volatile Uint16 *)(FPGA_RES_MOD_ADDR+0x000B*2)
#define DBC_RXMODULE24_FRAME_LOST_CNT	(volatile Uint16 *)(FPGA_RES_MOD_ADDR+0x000D*2)

//TXModules
#define DBC_TXMODULE1_CTRLREG     (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x0000*2)
#define DBC_TXMODULE1_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x0001*2)
#define DBC_TXMODULE1_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x0002*2)
#define DBC_TXMODULE1_STATUSREG     (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x0004*2)
#define DBC_TXMODULE1_DMA_RCV_CNT   (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x0008*2)
#define DBC_TXMODULE1_TX_OK_CNT     (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x0009*2)
#define DBC_TXMODULE1_CRC_ERR_CNT   (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x000A*2)
#define DBC_TXMODULE1_STR_ERR_CNT   (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x000B*2)
#define DBC_TXMODULE1_CACHE_FULL_CNT    (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x000C*2)
#define DBC_TXMODULE1_TX_ERR_CNT    (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x000D*2)
#define DBC_TXMODULE1_TIC_ERR_CNT   (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x000E*2)



//TX top module
#define DBC_TX_VERSION_DATE           (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x0104*2)
#define DBC_TX_VERSION_YEAR           (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x0105*2)
#define DBC_TX_VERSION                (volatile Uint16 *)(FPGA_DBC_TO_PCP_CFG_ADDR+0x0106*2)


//TXModules TEST CONFIG
#define DBC_TXMODULE_TEST_CTRLREG     (volatile Uint16 *)(FPGA_DBC_TEST_PCP_CFG_ADDR+0x0000*2)
#define DBC_TXMODULE_TEST_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_DBC_TEST_PCP_CFG_ADDR+0x0001*2)
#define DBC_TXMODULE_TEST_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_DBC_TEST_PCP_CFG_ADDR+0x0002*2)
#define DBC_TXMODULE_TEST_STATUSREG     (volatile Uint16 *)(FPGA_DBC_TEST_PCP_CFG_ADDR+0x0004*2)
#define DBC_TXMODULE_TEST_DMA_RCV_CNT   (volatile Uint16 *)(FPGA_DBC_TEST_PCP_CFG_ADDR+0x0008*2)
#define DBC_TXMODULE_TEST_TX_OK_CNT     (volatile Uint16 *)(FPGA_DBC_TEST_PCP_CFG_ADDR+0x0009*2)
#define DBC_TXMODULE_TEST_CRC_ERR_CNT   (volatile Uint16 *)(FPGA_DBC_TEST_PCP_CFG_ADDR+0x000A*2)
#define DBC_TXMODULE_TEST_STR_ERR_CNT   (volatile Uint16 *)(FPGA_DBC_TEST_PCP_CFG_ADDR+0x000B*2)
#define DBC_TXMODULE_TEST_CACHE_FULL_CNT    (volatile Uint16 *)(FPGA_DBC_TEST_PCP_CFG_ADDR+0x000C*2)
#define DBC_TXMODULE_TEST_TX_ERR_CNT    (volatile Uint16 *)(FPGA_DBC_TEST_PCP_CFG_ADDR+0x000D*2)
#define DBC_TXMODULE_TEST_TIC_ERR_CNT   (volatile Uint16 *)(FPGA_DBC_TEST_PCP_CFG_ADDR+0x000E*2)

//TXModules TEST DATA
#define DBC_TX_TEST_CACHE             (volatile Uint16 *)(FPGA_DBC_TEST_PCP_ADDR+((0x0000)<<1))

//TXModules TEST MOD_SEL
#define DBC_TEST_MOD_SEL          (volatile Uint16 *)(FPGA_DBC_TEST_MOD_SEL_ADDR)
//DBC_TEST_MOD_SEL[1:0] <= "00" ---- pps口输出'0'，测试输出关闭。
//               "01" ---- pps口输出FSK_5M信号。
//               "10" ---- pps口输出FSK_50K信号。
//               "11" ---- pps口输出标准FT3信号。



//PCIE out bar address
#define DBC_TX1_CACHE             (volatile Uint16 *)(FPGA_DBC_TO_PCP_ADDR+((0x0000)<<1))

//FEU SEND CFG
#define FEU_TX_NCU_CTRL			  (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0015)*2))
//#define FEU_TX_MASK1			  (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0014)*2))  设计更改，不再需要此寄存器
//#define FEU_TX_MASK2			  (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0015)*2))  设计更改，不再需要此寄存器
#define FEU_TX_MS_MODE            (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0016)*2))
//#define FEU_TX_VER              (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0017)*2))
#define FEU_TX_EN                 (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0018)*2))
#define FEU_TX_COMP_ERR			  (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0019)*2))  //FEU_TX_COMP_ERR, bit0：主从互校错误为‘1’，正确为‘0’。其它bit无效。
#define FEU_TX_OK_CNT             (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x001A)*2))
#define FEU_TX_CHECKERR_CNT       (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x001B)*2))
#define FEU_TX_TEST               (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x001C)*2))


#define FEU_TX1_DATA              (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0000)*2))
#define FEU_TX2_DATA              (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0001)*2))
#define FEU_TX3_DATA              (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0002)*2))
#define FEU_TX4_DATA              (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0003)*2))
#define FEU_TX5_DATA              (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0004)*2))
#define FEU_TX6_DATA              (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0005)*2))
#define FEU_TX7_DATA              (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0006)*2))
#define FEU_TX8_DATA              (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0007)*2))
#define FEU_TX9_DATA              (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0008)*2))

//DSP 给FPGA的16bit数据，FPGA根据此数据和实时报文解析结果，生成各个光口的控制命令
#define FEU_CMD_DATA              (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0009)*2))

#define FEU_TX1_Version             (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x000a)*2))
#define FEU_TX2_Version             (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x000b)*2))
#define FEU_TX3_Version             (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x000c)*2))
#define FEU_TX4_Version             (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x000d)*2))
#define FEU_TX5_Version             (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x000e)*2))
#define FEU_TX6_Version             (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x000f)*2))
#define FEU_TX7_Version             (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0010)*2))
#define FEU_TX8_Version             (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0011)*2))
#define FEU_TX9_Version             (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0012)*2))
//各个光口发送控制命令选择，‘0’为完全由DSP控制，‘1’为FPGA生成。
#define FEU_CMD_MODSEL                (volatile Uint16 *)(FPGA_DBC_TO_FEU_ADDR+((0x0013)*2))

//控保命令解析模块
#define PCP_PPR_MASK_REG1             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x0000)*2))
#define PCP_PPR_MASK_REG2             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x0001)*2))
#define PCP_PPR_MASK_REG3             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x0002)*2))
#define PCP_PPR_MASK_REG4             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x0003)*2))
#define PCP_PPR_MASK_REG5             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x0004)*2))
#define PCP_PPR_MASK_REG6             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x0005)*2))
#define PCP_PPR_MASK_REG7             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x0006)*2))
#define PCP_PPR_MASK_REG8             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x0007)*2))
#define PCP_PPR_MASK_REG9             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x0008)*2))
#define PCP_PPR_MASK_REG10              (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x0009)*2))
//FSK解析MASK
#define FSK_MASK_REG1             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x000a)*2))
#define FSK_MASK_REG2             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x000b)*2))

//三取二解析MASK
#define MU_PR_MASK_REG1             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x000c)*2))
#define MU_PR_MASK_REG2             (volatile Uint16 *)(FPGA_PCP_PPR_RXCMD_OUT+((0x000d)*2))



//rx configure structure
typedef struct
{
    volatile Uint16 clk_sel:2;
    volatile Uint16 reserved_1:4;
    volatile Uint16 opt_logic:1;
    volatile Uint16 enable:1;
    volatile Uint16 reserved_2:8;
    volatile Uint16 timeout_setting;
    volatile Uint16 block_word_num;
    volatile Uint16 total_word_num;
}DBC_60044_8_RX_CFG_REG;

//tx configure structure
typedef struct
{
    volatile Uint16 clk_sel:2;
    volatile Uint16 tx_mode:1;
    volatile Uint16 chc_enable:1;           //发送主从互校
    volatile Uint16 reserved_1:2;
    volatile Uint16 opt_logic:1;
    volatile Uint16 enable:1;
    volatile Uint16 reserved_2:8;
    volatile Uint16 block_word_num;
    volatile Uint16 total_word_num;
}DBC_TX_CFG_REG;


#endif
