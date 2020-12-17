

#ifndef _FPGA_REG_H_
#define _FPGA_REG_H_

#include "common_types.h"
#include "Board.h"


//PCIe address map
#define EMIF_BASE                       (FPGA_NETWORK_ADDR)
#define FGPA_CFG_START_ADDR             (volatile Uint16 *)(EMIF_BASE + 0x2000*2)                // goose�̶��ֶ����õ�ַ
#define MAC_RX_SV_CONF_ADDR             (volatile Uint16 *)(EMIF_BASE + 0x3000*2)                // SV�̶��ֶ����õ�ַ
#define FGPA_CFG_END_ADDR               (volatile Uint16 *)(EMIF_BASE + 0x3000*2)                // goose�̶��ֶ����õ�ַ�߽�
#define FGPA_LINK_REG_ADDR              (volatile Uint16 *)(EMIF_BASE + 0x4000*2)                // ���������õ�ַ

#define SMV_FIFO_THRESHOLD              (volatile Uint16 *)(EMIF_BASE + 0x0001*2)                // SMV���������������
#define SMV_FIFO_USEDW                  (volatile Uint16 *)(EMIF_BASE + 0x0007*2)                // SMV�������

/*  Tx: Send packets.   */
#define TX_NMODULE_ERROR_ADDR           (volatile Uint16 *)(EMIF_BASE + 0x830a*2)                // fifo��״̬
#define MAC_TX_EN_ADDR                  (volatile Uint16 *)(EMIF_BASE + 0x0800*2)                // ����ģ��ʹ��  bit0Ϊ1��ʱ��ʹ��

//#define FPGA_START_ADDR                 0x12000000
#define MAC_RX_EN_ADDR                  (volatile Uint16 *)(EMIF_BASE + 0x0000*2)                // ����ģ��ʹ��
#define RX_STORM_EN                     (volatile Uint16 *)(EMIF_BASE + 0x0002*2)                // ����籩ʹ��
#define RAM_CONF_WREN                   (volatile Uint16 *)(EMIF_BASE + 0x0004*2)                // ���ð������Ķ�дʹ�ܡ�//��ʼ��ʱ��1��������ɺ���0

/*  Network flow control.       */
#define FLOW_CTRL_CFG_ADDR              (volatile Uint16 *)(EMIF_BASE + 0x0080*2)                // ����ģ������ 




// �汾��Ϣ
//#define FPGA_VERSION                    (volatile Uint16 *)(EMIF_BASE + 0x0f0e*2)                // �汾��
//#define FPGA_VER_TIME_L                 (volatile Uint16 *)(EMIF_BASE + 0x0f0c*2)                // �汾ʱ���16λ
//#define FPGA_VER_TIME_H                 (volatile Uint16 *)(EMIF_BASE + 0x0f0d*2)                // �汾ʱ���16λ

//#define PROCESS_LAYER_VERSION           (volatile Uint16 *)(EMIF_BASE + 0x000e*2)                // �汾��
//#define PROCESS_LAYER_VER_L             (volatile Uint16 *)(EMIF_BASE + 0x000c*2)                // �汾ʱ���16λ
//#define PROCESS_LAYER_VER_H             (volatile Uint16 *)(EMIF_BASE + 0x000d*2)                // �汾ʱ���16λ

#define GOOSE_DEC_DDR_ADDR              (volatile Uint32 *)(PCIE_TARGET + 0x98000)               // Goose deal ddr start addr����Ҫ�漰��DMA

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




#define MAX_SMV_FIFO_THRESHOLD          (1600)                                    //SMV 2�����������������,32bits
#define MAX_SMV_BUFFER_LEN              (2047)                                    //SMV 2������������ܼ������

#define MAC_TX_DMA_ADDR                 (volatile Uint32 *)(PCIE_TARGET + 0xA0000)      // tx start addr 



#define FLOW_TYPE_CFG_ADDR              (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 12)    // SV GOOSE Other enable

#define SV_FLOW_CFG_OP_INDEX            (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 0)     // SV���ض�����Ŀ
#define SV_FLOW_CFG_REC_INDEX           (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 1)     // SV���ػָ���Ŀ
#define SV_FLOW_CFG_OP_TIC              (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 2)     // SV���ض���ʱ����   
#define SV_FLOW_CFG_REC_TIC             (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 3)     // SV���ػָ�ʱ����   

#define GOOSE_FLOW_CFG_OP_INDEX         (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 4)   
#define GOOSE_FLOW_CFG_REC_INDEX        (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 5)   
#define GOOSE_FLOW_CFG_OP_TIC           (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 6)   
#define GOOSE_FLOW_CFG_REC_TIC          (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 7)   

#define OTHER_FLOW_CFG_OP_INDEX         (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 8)   
#define OTHER_FLOW_CFG_REC_INDEX        (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 9)   
#define OTHER_FLOW_CFG_OP_TIC           (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 10)   
#define OTHER_FLOW_CFG_REC_TIC          (volatile Uint16 *)(FLOW_CTRL_CFG_ADDR + 11)   




#endif //_FPGA_NR1136_REG_H_

