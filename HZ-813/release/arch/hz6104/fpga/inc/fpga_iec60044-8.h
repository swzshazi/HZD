#include "fpga_base.h"

#ifndef _IEC60044_8_
#define _IEC60044_8_

//baud rate
#define IEC_BAUDRATE_10M        0x0000    // 10 Mbps
#define IEC_BAUDRATE_5M         0x0001    // 5 Mbps
#define IEC_BAUDRATE_2M5        0x0002    // 2.5 Mbps
#define IEC_BAUDRATE_14M        0x0003    // 14 Mbps

//The application layer frame structure between DSP and FPGA
#define IEC_FRAME_HEAD          0x7E7E
#define IEC_FRAME_EOF           0x55AA

//Optical logic
#define OPT_LOGIC_POSITIVE      0x0000
#define OPT_LOGIC_NEGATIVE      0x0040

//发送模式BIT位
#define CTRLWORD_TX_ON_TIME             0x0000          //定时
#define CTRLWORD_TX_AT_ONCE             0x0004          //即时

//接收使能BIT位
#define FPGA_RX_ENA_BIT                 0x0080
#define FPGA_RX_DIS_BIT                 0xFF7F

//接收状态寄存器BIT位
#define FPGA_RX_TIMEOUT_BIT             0x01
#define FPGA_RX_LINKERR_BIT             0x02

//发送状态寄存器BIT位
#define FPGA_TX_ERROR_BIT               0x01

//接收使能BIT位
#define FPGA_TX_ENA_BIT                 0x0080
#define FPGA_TX_DIS_BIT                 0xFF7F

//帧长定义
#define FRAME_LEN_32                    32
#define FRAME_LEN_48                    48
#define FRAME_LEN_64                    64

//TXModules
#define IEC_TXMODULE1_CTRLREG         (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0000*2)
#define IEC_TXMODULE1_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0001*2)
#define IEC_TXMODULE1_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0002*2)
#define IEC_TXMODULE1_STATUSREG       (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0004*2)
#define IEC_TXMODULE1_DMA_RCV_CNT     (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0008*2)
#define IEC_TXMODULE1_TX_OK_CNT       (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0009*2)
#define IEC_TXMODULE1_CRC_ERR_CNT     (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x000A*2)
#define IEC_TXMODULE1_STR_ERR_CNT     (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x000B*2)
#define IEC_TXMODULE1_CACHE_FULL_CNT  (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x000C*2)
#define IEC_TXMODULE1_TX_ERR_CNT      (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x000D*2)
#define IEC_TXMODULE1_TIC_ERR_CNT     (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x000E*2)

#define IEC_TXMODULE2_CTRLREG         (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0010*2)
#define IEC_TXMODULE2_BLOCK_WORD_NUM  (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0011*2)
#define IEC_TXMODULE2_TOTAL_WORD_NUM  (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0012*2)
#define IEC_TXMODULE2_STATUSREG       (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0014*2)
#define IEC_TXMODULE2_DMA_RCV_CNT     (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0018*2)
#define IEC_TXMODULE2_TX_OK_CNT       (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x0019*2)
#define IEC_TXMODULE2_CRC_ERR_CNT     (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x001A*2)
#define IEC_TXMODULE2_STR_ERR_CNT     (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x001B*2)
#define IEC_TXMODULE2_CACHE_FULL_CNT  (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x001C*2)
#define IEC_TXMODULE2_TX_ERR_CNT      (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x001D*2)
#define IEC_TXMODULE2_TIC_ERR_CNT     (volatile Uint16 *)(FPGA_IEC_TXMOD_ADDR+0x001E*2)

#define IEC_TX1_CACHE                 (volatile Uint16 *)(IEC_TX_START+((0x0000)<<2))
#define IEC_TX2_CACHE                 (volatile Uint16 *)(IEC_TX_START+((0x0100)<<2))


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
    volatile Uint16 resv[4];
    volatile Uint16 rx_status;
}IEC_60044_8_RX_CFG_REG;

//tx configure structure
typedef struct
{
    volatile Uint32 clk_sel:2;
    volatile Uint32 tx_mode:1;
    volatile Uint32 chc_enable:1;
    volatile Uint32 reserved_1:2;
    volatile Uint32 opt_logic:1;
    volatile Uint32 enable:1;
    volatile Uint32 reserved_2:24;
    volatile Uint32 block_word_num;
    volatile Uint32 total_word_num;
    volatile Uint32 tx_status;
}IEC_60044_8_TX_CFG_REG;


#endif
