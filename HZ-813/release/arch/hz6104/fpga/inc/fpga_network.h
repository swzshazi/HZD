#ifndef _FPGA_NETWORK_H_
#define _FPGA_NETWORK_H_

#include "fpga_base.h"
#include "fpga_tx_chc.h"

/***********************************************************************************
*                                   Base Addr Define
***********************************************************************************/
#define MAX_PORT_NUM                    (8)


/***********************************************************************************
*                                   DMA channel Part
***********************************************************************************/

#define SMV_RX_DMA_CHN_ADDR             DMA_CHAN6_CFG_ADDR
#define GOOSE_RX_DMA_CHN_ADDR           DMA_CHAN4_CFG_ADDR
#define OTHERS_RX_DMA_CHN_ADDR          DMA_CHAN7_CFG_ADDR

#define GOOSE_DEAL_POINT                DMA_CHAN6_STAT_ADDR
#define OTH_DEAL_POINT                  DMA_CHAN7_STAT_ADDR	// OTH数据已经处理数据指针

/***********************************************************************************
*                                   HSR PCS-Rx Register
***********************************************************************************/

// lyh ++



/***********************************************************************************
*                                   HSR CORE_Rx Register
***********************************************************************************/

// CORE_RX 保持不变地址由16位变成32位


// lyh ++

#define MAC_RX_EN_ADDR                  (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x00000*4)    // 接收模块使能
#define SMV_FIFO_THRESHOLD              (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x00001*4)    // SMV二级缓存深度设置
#define RX_STORM_EN                     (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x00002*4)	  // 网络风暴抑制
#define RAM_CONF_WREN                   (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x00004*4)    // 配置白名单的读写使能
#define SMV_FIFO_USEDW                  (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x00007*4)    // SMV缓存深度

#define MII_TX_EN		                (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x001A0*4)    // GMII_TX/MII_TX发送使能 BIT0 0:复位 1：置位


/***********************************************************************************
*                                  HSR CORE-MODULE CFG-RAM
***********************************************************************************/

// lyh ++

#define FGPA_LINK_REG_ADDR              (volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x4000*4)    // 白名单配置地址
#define SV_DEC_CFG_START_ADDR           (volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x3000*4)    // SV配置起始地址
#define SV_DEC_CFG_END_ADDR             (volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x3800*4)    // Sv配置结束地址
#define GOOSE_DEC_CFG_START_ADDR        (volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x2000*4)    // GOOSE配置起始地址
#define GOOSE_DEC_CFG_END_ADDR          (volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x3000*4)    // GOOSE配置结束地址

/***********************************************************************************
*                                   PFGA Rx Statistics Rester
***********************************************************************************/
// lyh ++

#define PORT_RX_CNT_BASE_ADDR           (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x8100*4) // 报文接收统计基地址
#define PORT_RX_OFFSET                  (0x40)												  // 每个端口偏移地址0X10*4

#define PORT_RX_ALL_CNT                 (0x02 * 4) // 判断该端口是否断链
#define PORT_RX_OK_CNT                  (0x03 * 4)
#define PORT_RX_FAIL_CNT                (0x04 * 4)
#define PORT_RX_ERR_CNT                 (0x05 * 4)

//#define PORT_RX_DROP_CNT                (0x06 * 4)

#define FPGA_SMV_DEC_OK_CNT             (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x00c2*4)
#define FPGA_SMV_DEC_ERR_CNT            (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x00c3*4)

#define FPGA_GOOSE_DEC_OK_CNT           (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x00e2*4)
#define FPGA_GOOSE_DEC_ERR_CNT          (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x00e3*4)

#define FPGA_SMV_RX_CNT                 (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x0121*4) // SV_TRANS 模块计数
#define FPGA_GOOSE_RX_CNT               (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x0141*4) // GOOSE_TRANS 模块计数
#define FPGA_OTHER_RX_CNT               (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x0161*4) // OTH_TRANS 模块计数

#define FPGA_MII_TX_OK_CNT               (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x01A4*4) // GMII/MII模块发送正确计数
#define FPGA_MII_TX_ERR_CNT              (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x01A4*4) // GMII/MII模块发送错误计数


/***********************************************************************************
*                                   Process Tx Regiseter
***********************************************************************************/

#define TX_NMODULE_ERROR_ADDR           (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x00804*4)    // fifo满状态
#define MAC_TX_EN_ADDR                  (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x00800*4)    // 发送模块使能  bit0为1的时候使能
#define MAC_TX_DMA_ADDR                 (volatile Uint32 *)(NETWORK_TX_WR_START)     //tx start addr 
#define ACT_TX_DMA_ADDR                 (volatile Uint32 *)(NETWORK_TX_WR_START)     // tx start addr 
#define GOOSE_TX_DMA_ADDR               (volatile Uint32 *)0x40010000
#define SV_TX_DMA_ADDR                  (volatile Uint32 *)0x4000E000
#define OTH_TX_DMA_ADDR                 (volatile Uint32 *)0x40012000


/***********************************************************************************
*                                   FPGA Time Register 
***********************************************************************************/

#define DSP_USE_SAME_MMB_TIME           (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + (0x0808<<2))
#define FPGA_TIME_TRIG_ADDR             (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + (0x080f<<2))

#define FPGA_TIME_LO_REG_ADDR           (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + (0x0817<<2))
#define FPGA_TIME_HI_REG_ADDR           (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + (0x0818<<2))


//新网络部分后添加的
#define STAT_TX_EN_ADDR                 (volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x0808*4)		//站控层发送使能的设置 bit0
#define STAT_TX_MASK_ADDR               (volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x0809*4)		//站控层tx_mask的设置,低8位有效  bit7~bit0
#define HSR_OWN_MAC_L				    (volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x0844*4)		//用于转发检测，本地mac地址（mac的最右侧2字节） 
#define HSR_OWN_MAC_M				    (volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x0845*4)		//用于转发检测，本地mac地址（mac的中间2字节）
#define HSR_OWN_MAC_H				    (volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x0846*4)		//用于转发检测，本地mac地址（mac的最左侧2字节）
#define PCS_RX_EN						(volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x08000*4)      // PCS_RX_EN接收使能信号
#define HSR_MAC_H						(volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x08003*4)      // PCS_RX MAC_H信号  010C 
#define HSR_MAC_M						(volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x08004*4)      // PCS_RX MAC_M信号  CD04
#define HSR_MAC_L						(volatile Uint32 *)(FPGA_NETWORK_MOD_ADDR + 0x08005*4)      // PCS_RX MAC_L信号  4419

//eg:若设置的mac地址为：aa-bb-cc-dd-ee-ff，则addr0写入eeff，addr1写入ccdd，addr2写入aabb


#define HSR_POS_ADDR                    (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x800c*4)       //环网口位置寄存器对应bit位为1表示环网口


/***********************************************************************************
*                                   PFGA Tx Statistics Rester
***********************************************************************************/


/***********************************************************************************
*                                   Network flow control
***********************************************************************************/
#define MAX_FLOW_CTRL_NUM               (192)
#define FLOW_CTRL_PORT_NUM              (12)

#define FLOW_CTRL_CFG_ADDR              (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x0080*2) // 流控模块配置 
#define FLOW_CTRL_EN_ADDR               (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x008C*2)  // á÷??ê1?ü??′??÷
#define FLOW_CTRL_STATE_ADDR            (volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x1800*2) //流控状态统计

#define FLOW_TYPE_CFG_ADDR              (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 12)    //SV GOOSE Other enable

#define SV_FLOW_CFG_OP_INDEX            (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 0)     // SV流控动作数目
#define SV_FLOW_CFG_REC_INDEX           (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 1)     // SV流控恢复数目
#define SV_FLOW_CFG_OP_TIC              (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 2)     // SV流控动作时间间隔   
#define SV_FLOW_CFG_REC_TIC             (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 3)     // SV流控恢复时间间隔   

#define GOOSE_FLOW_CFG_OP_INDEX         (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 4)   
#define GOOSE_FLOW_CFG_REC_INDEX        (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 5)   
#define GOOSE_FLOW_CFG_OP_TIC           (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 6)   
#define GOOSE_FLOW_CFG_REC_TIC          (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 7)   

#define OTHER_FLOW_CFG_OP_INDEX         (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 8)   
#define OTHER_FLOW_CFG_REC_INDEX        (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 9)   
#define OTHER_FLOW_CFG_OP_TIC           (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 10)   
#define OTHER_FLOW_CFG_REC_TIC          (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 11)   


/***********************************************************************************
*                                   IEEE 1588 Register
***********************************************************************************/

#define XFPGA_ADDR1588                  (FPGA_NETWORK_MOD_ADDR + 0x8400*2)              // MII FPGA起始地址

#define TX1588_TIC_NET_FLAG(x)          (volatile Uint16 *)(XFPGA_ADDR1588 + 0x011*4 + (0))        //R 1588 网口1时标有效性标志

#define TX1588_TIC_NET_NO1_NS_L(x)      (volatile Uint16 *)(XFPGA_ADDR1588 + 0x020*4 + (0))        //R 1588帧网口1 1时刻NS低字
#define TX1588_TIC_NET_NO1_NS_H(x)      (volatile Uint16 *)(XFPGA_ADDR1588 + 0x021*4 + (0))        //R 1588帧网口1 1时刻NS高字
#define TX1588_TIC_NET_NO1_S_L(x)       (volatile Uint16 *)(XFPGA_ADDR1588 + 0x022*4 + (0))        //R 1588帧网口1 1时刻S低字  
#define TX1588_TIC_NET_NO1_S_H(x)       (volatile Uint16 *)(XFPGA_ADDR1588 + 0x023*4 + (0))        //R 1588帧网口1 1时刻S高字  

/* 1588 CHANGE REGS ADDR */
#define CLK1588_NS_L                    (volatile Uint16 *)(XFPGA_ADDR1588 + 0x000*4)        //R/W 1588模块实时NS时间低位寄存器  
#define CLK1588_NS_H                    (volatile Uint16 *)(XFPGA_ADDR1588 + 0x001*4)        //R/W 1588模块实时NS时间高位寄存器  
#define CLK1588_S_L                     (volatile Uint16 *)(XFPGA_ADDR1588 + 0x002*4)        //R/W 1588模块实时S时间低位寄存器
#define CLK1588_S_H                     (volatile Uint16 *)(XFPGA_ADDR1588 + 0x003*4)        //R/W 1588模块实时S时间高位寄存器
#define CLK1588_RATE_L                  (volatile Uint16 *)(XFPGA_ADDR1588 + 0x004*4)        //R/W 1588模块时间调整率低位寄存器
#define CLK1588_RATE_H                  (volatile Uint16 *)(XFPGA_ADDR1588 + 0x005*4)        //R/W 1588模块时间调整率低位寄存器
#define CLK1588_RATE_FLAG               (volatile Uint16 *)(XFPGA_ADDR1588 + 0x006*4)        //R/W 1588模块时间调整率符号寄存器
#define CLK1588_STEP_L                  (volatile Uint16 *)(XFPGA_ADDR1588 + 0x007*4)        //R/W 1588模块实时NS时间低位寄存器
#define CLK1588_STEP_H                  (volatile Uint16 *)(XFPGA_ADDR1588 + 0x008*4)        //R/W 1588模块实时NS时间高位寄存器
#define CLK1588_STEP_FLAG               (volatile Uint16 *)(XFPGA_ADDR1588 + 0x009*4)        //R/W 1588模块实时S时间低位寄存器 
#define CLK1588_SET_CUR_OK              (volatile Uint16 *)(XFPGA_ADDR1588 + 0x00A*4)        //W 1588模块实时S时间高位寄存器 
#define CLK1588_SET_RATE_OK             (volatile Uint16 *)(XFPGA_ADDR1588 + 0x00B*4)        //W 1588模块时间调整率低位寄存器
#define CLK1588_SET_STEP_OK             (volatile Uint16 *)(XFPGA_ADDR1588 + 0x00C*4)        //W 1588模块时间调整率低位寄存器
#define CLK1588_REG_CUR_OK              (volatile Uint16 *)(XFPGA_ADDR1588 + 0x00D*4)        //W 1588模块设置时间调整率符号寄存器
#define MMB_CUR_TIC_L                   (volatile Uint16 *)(XFPGA_ADDR1588 + 0x00E*4)        //R MMB实时时间寄存器低字
#define MMB_CUR_TIC_H                   (volatile Uint16 *)(XFPGA_ADDR1588 + 0x00F*4)        //R MMB实时时间寄存器高字

/* 1588 CHANGE REGS ADDR */
#define PPIEN_ADDR                      (volatile Uint16 *)(XFPGA_ADDR1588 + 0x010*4)
#define FPGA_PTP_ENA                    (0x01)
#define FPGA_PTP_PPS_ENA                (0x02)


/***********************************************************************************
*                                   General Macro Define
***********************************************************************************/
#define FPGA_MAX_LINK_NUM               (192)
#define PER_LINK_BUF_NUM                (64)
#define FPGA_OTHER_BUF_NUM              (1024)
#define PER_BUF_BYTE_SIZE               (2048)

#define TF_START_FLAG                   (0x7e)
#define TF_END_FLAG                     (0xe7)
#define TF_END_FLAG1                    (0xAA)
#define TF_END_FLAG2                    (0x55)


#define TF_FLAG                         (0x7E7EE7E7)
#define FT_FLAG                         (0x80000000)
#define CRC_FLAG                        (0x8000000)
#define FS_FLAG                         (0x0)
#define FS_1588                         (0x40000000)
#define FD_FLAG                         (0xaaaaaaaa)

#define ALL_FLOW_ON                     (0x0000)
#define SV_FLOW_OFF                     (0x0001)
#define GOOSE_FLOW_OFF                  (0x0002)
#define OTHER_FLOW_OFF                  (0x0004)

#define ENABLE                          (0x0001)
#define FORWARD_ENABLE                  (0x0002)
#define ENA_ALL_MAC                     (0xFFFF)

#define MAX_SMV_FIFO_THRESHOLD          (1600)      //SMV 2级缓存可设置最大深度,32bits
#define MAX_SMV_BUFFER_LEN              (2047)      //SMV 2级缓存的最大可能极限深度

#define TR_ACT_ACTIVED                  (0x5D)
#define TR_ACT_INACTIV                  (0x7A)
#define ACT_ALIGN_LEN                   (0x7)
#define ACT_INVACTIVE_LEN               (0x1)
#define ACT_START_FLAG                  (0x55AA5A5A)
#define ACT_NO_FLAG                     (0xFFFFFFFF)
#define ACT_BUF_ALGIN_LEN               (0x4)
#define ACT_BUF_BYTE_LEN                (ACT_BUF_ALGIN_LEN << 2)
#define ACT_CRC32_TMP_VAL               (0xBBBBBBBB)
#define ACT_END_FLAG                    (0x7E7E77EE)

#define FPGA_TYPE_M                     (0x1)
#define FPGA_TYPE_S                     (0x2)

#define SMV_ACT_START_FLAG              (0x55AA5B5B)
#define SMV_ACT_BUF_ALGIN_LEN           (4)
#define SMV_ACT_BUF_ALGIN_BYTE_LEN      (SMV_ACT_BUF_ALGIN_LEN*4)
#define	SMV_ACT_CTRL_INFO_PREFIX      	(0xAA550000)

/* PRP HSR INFO */
#define TX_1588_SYNC_INDEX              (0X1)
#define TX_1588_PDELAY_RESP_INDEX       (0X3)
#define TX_1588_TIC_SEQ_SYNC            (0x10000000)
#define TX_1588_TIC_SEQ_OTHER           (0x20000000)
#define TX_1588_NO_PRP_HSR_TAG          (0xC0000)
#define TX_1588_NET_A_POS               (16)
#define TX_1588_NET_B_POS               (17)
 
#define TX_1588_TIC_SEQ_P_RES           (0x30000000)

/***********************************************************************************
*                                   mii mod Define
***********************************************************************************/
#define GMII_F2C_EN_ADDR 								(volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x0A000*2 + 0x100*4)    // FPGA-CPU使能
#define GMII_C2F_EN_ADDR 								(volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x0A000*2 + 0x110*4)    // CPU-FPGA使能
#define STA_RX_DEST_ADDR 								(volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x0A000*2 + 0x140*4)    // 白名单统计
#define STA_STORM_ADDR   								(volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x0A000*2 + 0x160*4)    // 网络风暴
#define STA_FLOW_EN_ADDR 								(volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x0A000*2 + 0x188*4)    // 流控配置起始地址
#define STA_RX_DEST_LIST 								(volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x0B000*2 )             // 白名单配置起始地址
#define MII_RX_EN_ADDR   								(volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x08000*2)  // ·¢ËÍÄ£¿éÊ¹ÄÜ  bit0Îª1µÄÊ±ºòÊ¹ÄÜ
#define MII_TX_EN_ADDR   								(volatile Uint16 *)(FPGA_NETWORK_MOD_ADDR + 0x08001*2)  // ·¢ËÍÄ£¿éÊ¹ÄÜ  bit0Îª1µÄÊ±ºòÊ¹ÄÜ

/***********************************************************************************
*                                   SFP_MONITOR define
***********************************************************************************/

#endif 

