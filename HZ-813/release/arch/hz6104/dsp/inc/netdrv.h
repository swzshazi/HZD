//---------------------------------------------------------------------------
//功能说明：网卡驱动，与硬件相关
//版本说明：1.00												   2017.10.08
//
//---------------------------------------------------------------------------
#ifndef		_NETDRV_H
#define		_NETDRV_H

#include  "common_types.h"
#include  "board.h"
#include  "fpga_tx_chc.h"

#define    ADD_LINK_CTRL_INFO       			0x1001
#define    SET_GOOSE_LINK_FRAME_INFO			0x1002
#define    SET_SMV_LINK_FRAME_INFO				0x1003
#define    SET_GOOSE_FLOWCTRL_PARA              0x1004
#define    SET_SMV_FLOWCTRL_PARA				0x1005
#define    SET_OTHER_FLOWCTRL_PARA				0x1006
#define    SET_SMV_TX_RAM_MASK					0x1007
#define    SET_SMV_TX_DATA						0x1008
#define    SET_SMV_TX_RAM_COMPARE				0x1009
#define    SET_GSE_RX_MEM						0x100a
#define    SET_SMV_RX_MEM					    0x100b
#define    SET_FT3_RX_MEM						0x100c
#define    SET_OTH_RX_MEM						0x100d
#define    SET_GSE_RX_REAR                      0x100e
#define    SET_SMV_RX_REAR                      0x100f

#define    GET_TX_READY_STATE					0x1020
#define    GET_RX_LINK_INDEPEND_MODE			0x1021

#define    PROCESS_PORT_NUM             		16
#define    MAX_TX_WAIT_TIME                    (250)   // 25us
#define    EPPI_TX_DATA_LEN			           (5) 

#define    U8_TO_U16(high, low)                 (((high << 8) | low) & 0xffff)
#define    ALIGN_4_LEN(len)                     ((len + 3) >> 2)
#define    CONVERT_4_LEN(len)      				((len + 3) >> 2)
#define    U8_TO_U16(high, low)        			(((high << 8) | low) & 0xffff)
#define    U16_TO_U32(high, low)       			(((high << 16)| low) & 0xffffffff)

#define    TX_ON								1
#define    TX_OFF								2
#define    RX_ON								3
#define    RX_OFF								4

#define    EMAC_STOP                            1
#define    EMAC_START							2
#define    EMAC_CONFIG							3
#define    EMAC_WAIT                            4
#define    EMAC_READY							5
#define    EMAC_RUN								6

typedef struct
{
	Uint16	 len;
    Uint16	 len_type_filed;
	Uint8	*dst_mac;
	Uint8	*src_mac;
	Uint8	*data;
	Uint32   rxTime;
	Uint16	 port;
	Uint16	 net;
	Uint16   numValidEntries;
	Uint16   rxCtrlId;
}EMAC_BUF;

typedef struct
{
	Uint8      *mac;
	Uint16     port;   
	Uint16     appid;
	Uint16     msg_type;
	Uint16     cfgAddr; 
	Uint8      ctrl_id; 
	Uint8      link_id;
	Uint16     goid;
}EMAC_REG_INFO;

typedef struct
{
    Uint8      *start_ptr;
	Uint8      *field_ptr;
	Uint8      *end_ptr;
	Uint8      enc_err;
}DEC_CFG_CTXT;

typedef struct
{
    Uint8      ena;
    
    Uint8      threshold; 
    Uint8      RecoverNum;
    Uint16     timer;
    Uint16     RecoverTimer;
}NET_TRAFIC_CTRL;

typedef struct
{
	char *	   data;
	Uint16	   len;
}DATA_ATTRIBUTE;

typedef struct
{
	Uint32 data_addr;
	Uint32 stat_addr;
	Uint16 max_index;
	Uint16 frame_offset;
}PROCESS_MEM_INFO;

typedef struct
{
	Uint16   len;
	Uint16   rx_no;
	Uint8    port;
	Uint8    rxCtrlId;
	Uint8   *data;
	Uint32   rxTime;
}FT3_BUF;

typedef struct
{
	Uint32     reg0;
	Uint32     reg1;
	Uint32     reg2;
	Uint32     reg3;
	Uint32     reg4;
	Uint32     reg5;
	Uint32     reg6;
	Uint32     reg7;
}FPGA_LINK_INFO;

typedef struct
{
	Uint32		rx_cnt;
	Uint32		rx_buf_full;
	Uint32      rx_err_cnt;
	Uint32		tx_cnt;
	Uint32		tx_err_cnt; 
	Uint32		tx_timed_errs;
	Uint32		tx_buff_full;
}EMAC_STAT;

typedef struct
{
	Uint8		tx_reset;
	Uint16		rx_state;
	Uint16		tx_try_cnt;
	Uint16		tx_rst_cnt;
	Uint16      rx_rst_cnt;

	EMAC_STAT	stat;
}EMAC_DEV; 

struct netdev_priv
{
	Uint8     tx_buf_scan_level;
	Uint16    flow_ctrl_setting;
	volatile  Uint16     	*gCurDecAddrGoose;
	volatile  Uint16     	*gCurDecAddrSmv;
	volatile  DMA_CFG_REG 	*dma_goose_cfg_reg;
	volatile  Uint32        *dma_goose_stat_reg;
	volatile  DMA_CFG_REG 	*dma_smv_cfg_reg;
	volatile  Uint32        *dma_smv_stat_reg;
	volatile  DMA_CFG_REG 	*dma_other_cfg_reg;
	volatile  Uint32        *dma_other_stat_reg;
	
	// 与硬件相关SMV操作
	volatile 				TX_CHC_REG_SET *tx_cfg;				// 设置最大长度和互校使能
	volatile 				Uint16 *pMaskAddr;
};

#endif // end by hz.

