
#ifndef _INC_FPGA_BASE_H
#define _INC_FPGA_BASE_H


//#include "board_base.h"

//--------------------------------  define  emif space-----------------------------------


#define SOC_FPGA_EMIF_START         (0x80000000 )

#define CORE0_FPGA_SRAM0_START         (SOC_FPGA_EMIF_START )
#define CORE0_FPGA_SRAM1_START         (SOC_FPGA_EMIF_START + (0x1000<<2))
#define CORE1_FPGA_SRAM0_START         (SOC_FPGA_EMIF_START + (0x2000<<2) )
#define CORE1_FPGA_SRAM1_START         (SOC_FPGA_EMIF_START + (0x3000<<2))

#define CORE0_FPGA_MMB1_REG            (SOC_FPGA_EMIF_START + (0x800<<2))
#define CORE0_FPGA_MMB2_REG            (SOC_FPGA_EMIF_START + (0x1800<<2))
#define CORE1_FPGA_MMB1_REG            (SOC_FPGA_EMIF_START + (0x2800<<2))
#define CORE1_FPGA_MMB2_REG            (SOC_FPGA_EMIF_START + (0x3800<<2))

#define FPGA_GEN_DMA_ADDR                 (SOC_FPGA_EMIF_START+(0x4000<<2))              // FPGA起始地址
#define SIZE_OF_FPGA_GEN_DMA              ((0x1000)<<1)                                  // 寄存器范围

#define FPGA_ADC_ADDR                    (SOC_FPGA_EMIF_START+(0X8000<<2))              // FPGA起始地址
#define SIZE_OF_FPGA_ADC                 ((0X100)<<2)       

#define FPGA_VERSION_ADDR              (SOC_FPGA_EMIF_START + (0X10000<<2))             // FPGA起始地址
#define SIZE_OF_FPGA_VERSION           ((0X10)<<2)       

#define FPGA_GPIO_ADDR                 (SOC_FPGA_EMIF_START + (0X10010<<2))             // FPGA起始地址
#define SIZE_OF_FPGA_GPIO              ((0X10)<<2)       

//#define FPGA_KI_ADDR                     (SOC_FPGA_EMIF_START+(0X10020<<2))              // FPGA起始地址
//#define SIZE_OF_FPGA_KI                  ((0X10)<<2)    

#define FPGA_SYNC_ADDR                    (SOC_FPGA_EMIF_START+(0X10040<<2))              // FPGA起始地址
#define SIZE_OF_FPGA_SYNC                 ((0X40)<<2)       

//#define FPGA_HDLC1_ADDR                    (SOC_FPGA_EMIF_START+(0X10080<<2))              // FPGA起始地址
//#define SIZE_OF_FPGA_HDLC1                 ((0X10)<<2)      

//#define FPGA_HDLC2_ADDR                    (SOC_FPGA_EMIF_START+(0X10090<<2))              // FPGA起始地址
//#define SIZE_OF_FPGA_HDLC2                 ((0X10)<<2)    

#define FPGA_I2C_MOD_ADDR                  (SOC_FPGA_EMIF_START + (0x10100<<2))
#define SIZE_OF_FPGA_I2C                   ((0X00100)<<2)  

#define FPGA_LINK_MOD_ADDR                  (SOC_FPGA_EMIF_START + (0x10200<<2))
#define SIZE_OF_FPGA_LINK                   ((0X00100)<<2)  

#define FPGA_SOCTX_ADDR                     (SOC_FPGA_EMIF_START + (0x10300<<2))
#define SIZE_OF_FPGA_LINK                   ((0X00100)<<2)  

#define FPGA_IEC_TXMOD_ADDR                 (SOC_FPGA_EMIF_START + (0x12100<<2))
#define SIZE_OF_IEC_TX_CFG                  0x400

#define FPGA_AURORA_MOD_ADDR                (SOC_FPGA_EMIF_START + (0x17000<<2))
#define SIZE_OF_FPGA_AURORA                 ((0X1000)<<2)

#define FPGA_NETWORK_MOD_ADDR               (SOC_FPGA_EMIF_START + (0x20000<<2))
#define SIZE_OF_FPGA_NET                    ((0X10000)<<2)  

#define FPGA_UART_MOD_ADDR                  (SOC_FPGA_EMIF_START + (0x30000<<2))
#define SIZE_OF_FPGA_UART                   ((0X1000)<<2)  

#define FPGA_PWM_MOD_ADDR                   (SOC_FPGA_EMIF_START + (0x33008<<2))
#define SIZE_OF_FPGA_PWM                    ((0X0008)<<2)  

#define FPGA_USB_MOD_ADDR                   (SOC_FPGA_EMIF_START + (0x33010<<2))
#define SIZE_OF_FPGA_USB                    ((0X0010)<<2) 

                       // 寄存器范围

//--------------------------------  define outbound space -----------------------------------
   #define DDR_USER_AREA                    (0x3e000000)
   #define SIZE_OF_FPGA_MMB1_WR             (0x100000)                                      // 地址范围
   
#define CORE0_MMB1_WR_START                (0x40000000)
#define SIZE_OF_CORE0_MMB1_WR              ((0X400)<<2)                           // 寄存器范围

#define CORE0_MMB2_WR_START                (0x40000000 + (0x800<<2))
#define SIZE_OF_CORE0_MMB2_WR              ((0X800)<<2)                           // 寄存器范围

#define CORE1_MMB1_WR_START                (0x40000000 + (0x1000<<2))
#define SIZE_OF_CORE1_MMB1_WR              ((0X400)<<2)                           // 寄存器范围

#define CORE1_MMB2_WR_START                (0x40000000 + (0x1800<<2))
#define SIZE_OF_CORE1_MMB2_WR              ((0X800)<<2)                           // 寄存器范围

#define NETWORK_TX_WR_START                (0x40000000 + (0x2000<<2))
#define SIZE_OF_NET_TX_WR                  ((0X800)<<2)    

#define FPGA_IEC_TX_DAT_ADDR               (0x40000000 + (0x2000<<2))
#define SIZE_OF_IEC_TX_START               0x800

#define FPGA_IEC_RXMOD_ADDR                (0x40000000 + (0x2800<<2))
#define SIZE_OF_IEC_RX_SIZE                0x800

#define SOC_TX_START                       (0x40000000 + (0x3000<<2))
#define SIZE_OF_SOC_TX_START               ((0X800)<<2)    

//新增的过程层网络发送dma推送首地址
#define SV_TX_START                       (0x40000000 + (0x3800<<2))
#define SIZE_OF_SV_TX_START               ((0X800)<<2) 

#define GOOSE_TX_START                    (0x40000000 + (0x4000<<2))
#define SIZE_OF_GOOSE_TX_START            ((0X800)<<2) 

#define OTH_TX_START                      (0x40000000 + (0x4800<<2))
#define SIZE_OF_OTH_TX_START              ((0X800)<<2) 









#endif // end of 
