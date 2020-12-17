

#ifndef _FPGA_REG_H_
#define _FPGA_REG_H_

#include "common_types.h"
#include "Board.h"


//PCIe address map
#define EMIF_BASE                       (FPGA_NETWORK_ADDR)
#define FGPA_CFG_START_ADDR             (volatile Uint16 *)(EMIF_BASE + 0x2000*2)                // goose固定字段配置地址
#define MAC_RX_SV_CONF_ADDR             (volatile Uint16 *)(EMIF_BASE + 0x3000*2)                // SV固定字段配置地址
#define FGPA_CFG_END_ADDR               (volatile Uint16 *)(EMIF_BASE + 0x3000*2)                // goose固定字段配置地址边界
#define FGPA_LINK_REG_ADDR              (volatile Uint16 *)(EMIF_BASE + 0x4000*2)                // 白名单配置地址

#define SMV_FIFO_THRESHOLD              (volatile Uint16 *)(EMIF_BASE + 0x0001*2)                // SMV二级缓存深度设置
#define SMV_FIFO_USEDW                  (volatile Uint16 *)(EMIF_BASE + 0x0007*2)                // SMV缓存深度

/*  Tx: Send packets.   */
#define TX_NMODULE_ERROR_ADDR           (volatile Uint16 *)(EMIF_BASE + 0x830a*2)                // fifo满状态
#define MAC_TX_EN_ADDR                  (volatile Uint16 *)(EMIF_BASE + 0x0800*2)                // 发送模块使能  bit0为1的时候使能

//#define FPGA_START_ADDR                 0x12000000
#define MAC_RX_EN_ADDR                  (volatile Uint16 *)(EMIF_BASE + 0x0000*2)                // 接收模块使能
#define RX_STORM_EN                     (volatile Uint16 *)(EMIF_BASE + 0x0002*2)                // 网络风暴使能
#define RAM_CONF_WREN                   (volatile Uint16 *)(EMIF_BASE + 0x0004*2)                // 配置白名单的读写使能。//初始化时置1，配置完成后清0

/*  Network flow control.       */
#define FLOW_CTRL_CFG_ADDR              (volatile Uint16 *)(EMIF_BASE + 0x0080*2)                // 流控模块配置 




// 版本信息
//#define FPGA_VERSION                    (volatile Uint16 *)(EMIF_BASE + 0x0f0e*2)                // 版本号
//#define FPGA_VER_TIME_L                 (volatile Uint16 *)(EMIF_BASE + 0x0f0c*2)                // 版本时间低16位
//#define FPGA_VER_TIME_H                 (volatile Uint16 *)(EMIF_BASE + 0x0f0d*2)                // 版本时间高16位

//#define PROCESS_LAYER_VERSION           (volatile Uint16 *)(EMIF_BASE + 0x000e*2)                // 版本号
//#define PROCESS_LAYER_VER_L             (volatile Uint16 *)(EMIF_BASE + 0x000c*2)                // 版本时间低16位
//#define PROCESS_LAYER_VER_H             (volatile Uint16 *)(EMIF_BASE + 0x000d*2)                // 版本时间高16位

#define GOOSE_DEC_DDR_ADDR              (volatile Uint32 *)(PCIE_TARGET + 0x98000)               // Goose deal ddr start addr，需要涉及到DMA

#define FPGA_MAX_LINK_NUM               ( 64)

#define FPGA_GS_MAX_LINK_NUM            ( 16)
#define PER_GS_LINK_BUF_NUM             ( 13)
#define PER_GS_LINK_BUF_NUM_MASK        ( 12)
#define PER_GS_BUF_BYTE_SIZE            (512)

#define FPGA_SMV_MAX_LINK_NUM           (  4)
#define PER_SMV_LINK_BUF_NUM            (  8)
#define PER_SMV_LINK_BUF_NUM_MASK       (  7)
#define PER_SMV_BUF_BYTE_SIZE           (512)


#define FPGA_OTHER_MAX_LINK_NUM            ( 16)
#define PER_OTHER_LINK_BUF_NUM             (  8)
#define PER_OTHER_LINK_BUF_NUM_MASK        (  7)
#define PER_OTHER_BUF_BYTE_SIZE            (512)

#define FPGA_OTHER_BUF_NUM              (1024)
#define PER_BUF_BYTE_SIZE               (2048)

#define TF_START_FLAG                   (0x7e)
#define TF_END_FLAG                     (0xe7)
#define TF_END_FLAG1                    (0xAA)
#define TF_END_FLAG2                    (0x55)

#define TF_FLAG                         (0x7E7EE7E7)
#define FT_FLAG                         (0x80000000)
#define FS_FLAG                         (0x0)
#define FS_1588                         (0x40000000)
#define TX_1588_TIC_SEQ_3               (0x3)
#define TX_1588_TIC_SEQ_P_REQ           (0x0)
#define TX_1588_SYNC_INDEX              (0X1)
#define TX_1588_PDELAY_RESP_INDEX       (0X3)

#define TX_1588_TIC_SEQ_SYNC            (0x10000000)
#define TX_1588_TIC_SEQ_OTHER           (0x20000000)
#define TX_1588_NO_PRP_HSR_TAG          (0xC0000)

#define TX_1588_TIC_SEQ_P_RES           (0x30000000)
#define FD_FLAG                         (0xaaaaaaaa)

#define ALL_FLOW_ON                     (0x0000)
#define SV_FLOW_OFF                     (0x0001)
#define GOOSE_FLOW_OFF                  (0x0002)
#define OTHER_FLOW_OFF                  (0x0004)

#define ENABLE                          (0x0001)
#define ENA_ALL_MAC                     (0xFFFF)




#define MAX_SMV_FIFO_THRESHOLD          (1600)                                    //SMV 2级缓存可设置最大深度,32bits
#define MAX_SMV_BUFFER_LEN              (2047)                                    //SMV 2级缓存的最大可能极限深度

#define MAC_TX_DMA_ADDR                 (volatile Uint32 *)(PCIE_TARGET + 0xA0000)      // tx start addr 



#define FLOW_TYPE_CFG_ADDR              (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 12)    // SV GOOSE Other enable

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




#endif //_FPGA_NR1136_REG_H_

