#ifndef  CPSW_NET_H
#define  CPSW_NET_H

#include "common_types.h"

#define  TI811X_CPSW_MDIO_BASE  0x0A101000
#define  TI814X_CPSW_BASE       0x0A100000

struct cpsw_slave_data {
    Uint32     slave_reg_ofs;
    Uint32     sliver_reg_ofs;
    int        phy_id;
};

struct cpsw_platform_data {
    Uint32     mdio_base;
    Uint32     cpsw_base;
    int        mdio_div;
    int        channels;           /* number of cpdma channels (symmetric) */
    Uint32     cpdma_reg_ofs;      /* cpdma register offset        */
    Uint32     cpdma_sram_ofs;     /* cpdma sram offset       */
    int        slaves;             /* number of slave cpgmac ports     */
    Uint32     ale_reg_ofs;        /* address lookup engine reg offset */
    int        ale_entries;        /* ale table size           */
    Uint32     host_port_reg_ofs;  /* cpdma host port registers    */
    Uint32     hw_stats_reg_ofs;   /* cpsw hw stats counters   */
    Uint32     mac_control;
    struct     cpsw_slave_data  *slave_data;
    void     (*control)(int enabled);
    void     (*phy_init)(char *name, int addr);
    Uint32     host_port_num;
    Uint32     bd_ram_ofs;
};

typedef struct
{
    Uint16   type;
    Uint8    res[2];
    int    (*emac_rx_callback)(Uint8 *buf);
}EMAC_RX_FUNC;

#define BITMASK(bits)      ((1 << (bits)) - 1)
#define PHY_REG_MASK        0x1f
#define PHY_ID_MASK         0x1f
#define PKTBUFSRX           64
#define NUM_DESCS           128                  // (PKTBUFSRX * 2),其中有1半是接收的，1半是发送的。
#define PKT_MIN             60
#define PKT_MAX            (1500 + 14 + 4 + 4)
#define PKTSIZE             1518
#define PKTSIZE_ALIGN       1536
#define PKT_BUF             2048
#define PKT_NUM             256

#define CPSW_ARM_TO_ERR     3

#define AUTO                99
#define _1000BASET          1000
#define _100BASET           100
#define _10BASET            10
#define HALF                22
#define FULL                44

#define PHY_BMCR            0x00
#define PHY_BMSR            0x01
#define PHY_ANAR            0x04
#define PHY_ANLPAR          0x05
#define PHY_1000BTCR        0x09
#define PHY_ANLPAR_100      0x0380
#define PHY_ANLPAR_10       0x0020
#define PHY_ANLPAR_10FD     0x0040
#define PHY_ANLPAR_TX       0x0080
#define PHY_ANLPAR_TXFD     0x0100
#define PHY_BMSR_LS         0x0004
#define PHY_BMCR_RESET      0x8000
#define PHY_BMCR_100MB      0x2000
#define PHY_BMCR_DPLX       0x0100
#define PHY_BMCR_AUTON      0x1000
#define PHY_BMCR_100_MBPS   0x2000
#define PHY_1000BTCR_1000FD 0x0200
#define PHY_1000BTCR_1000HD 0x0100
#define PHY_BMCR_RST_NEG    0x0200
#define PHY_BMSR_AUTN_COMP  0x0020




/* DMA Registers */
#define CPDMA_TXCONTROL     0x004
#define CPDMA_RXCONTROL     0x014
#define CPDMA_SOFTRESET     0x01c
#define CPDMA_RXFREE        0x0e0
#define CPDMA_TXHDP         0x000
#define CPDMA_RXHDP         0x020
#define CPDMA_TXCP          0x040
#define CPDMA_RXCP          0x060

/* Descriptor mode bits */
#define CPDMA_DESC_SOP      (1 << (31))
#define CPDMA_DESC_EOP      (1 << (30))
#define CPDMA_DESC_OWNER    (1 << (29))
#define CPDMA_DESC_EOQ      (1 << (28))

struct cpsw_mdio_regs {
    Uint32 version;
    Uint32 control;
    Uint32 alive;
    Uint32 link;
    Uint32 linkintraw;
    Uint32 linkintmasked;
    Uint32 __reserved_0[2];
    Uint32 userintraw;
    Uint32 userintmasked;
    Uint32 userintmaskset;
    Uint32 userintmaskclr;
    Uint32 __reserved_1[20];

    struct 
    {
        Uint32 access;
        Uint32 physel;
    } user[1];
};
//结构体中control寄存器定义
#define CONTROL_IDLE        (1 << 31)
#define CONTROL_ENABLE      (1 << 30)
//结构体中physel寄存器相关定义
#define USERACCESS_GO       (1 << 31)
#define USERACCESS_WRITE    (1 << 30)
#define USERACCESS_ACK      (1 << 29)
#define USERACCESS_READ     (0)
#define USERACCESS_DATA     (0xffff)


struct cpsw_regs {
    Uint32 id_ver;
    Uint32 control;
    Uint32 soft_reset;
    Uint32 stat_port_en;
    Uint32 ptype;
};

struct cpsw_slave_regs {
    Uint32 max_blks;
    Uint32 blk_cnt;
    Uint32 flow_thresh;
    Uint32 port_vlan;
    Uint32 tx_pri_map;
    Uint32 ts_ctl;
    Uint32 ts_seq_ltype;
    Uint32 ts_vlan;
    Uint32 sa_lo;
    Uint32 sa_hi;
};

struct cpsw_host_regs {
    Uint32 max_blks;
    Uint32 blk_cnt;
    Uint32 flow_thresh;
    Uint32 port_vlan;
    Uint32 tx_pri_map;
    Uint32 cpdma_tx_pri_map;
    Uint32 cpdma_rx_chan_map;
};

struct cpsw_sliver_regs {
    Uint32 id_ver;
    Uint32 mac_control;
    Uint32 mac_status;
    Uint32 soft_reset;
    Uint32 rx_maxlen;
    Uint32 __reserved_0;
    Uint32 rx_pause;
    Uint32 tx_pause;
    Uint32 __reserved_1;
    Uint32 rx_pri_map;
};

#define ALE_ENTRY_BITS      68
#define DIV_ROUND_UP(n,d)   (((n) + (d) - 1) / (d))
#define ALE_ENTRY_WORDS     DIV_ROUND_UP(ALE_ENTRY_BITS, 32)

/* ALE Registers */
#define ALE_CONTROL         0x08
#define ALE_UNKNOWNVLAN     0x18
#define ALE_TABLE_CONTROL   0x20
#define ALE_TABLE           0x34
#define ALE_PORTCTL         0x40

#define ALE_TABLE_WRITE     (1 << (31))

#define ALE_TYPE_FREE           0
#define ALE_TYPE_ADDR           1
#define ALE_TYPE_VLAN           2
#define ALE_TYPE_VLAN_ADDR      3

#define ALE_UCAST_PERSISTANT    0
#define ALE_UCAST_UNTOUCHED     1
#define ALE_UCAST_OUI           2
#define ALE_UCAST_TOUCHED       3

#define ALE_MCAST_FWD           0
#define ALE_MCAST_BLOCK_LEARN_FWD   1
#define ALE_MCAST_FWD_LEARN     2
#define ALE_MCAST_FWD_2         3

enum cpsw_ale_port_state { ALE_PORT_STATE_DISABLE,ALE_PORT_STATE_BLOCK,ALE_PORT_STATE_LEARN,ALE_PORT_STATE_FORWARD };

/* ALE unicast entry flags - passed into cpsw_ale_add_ucast() */
#define ALE_SECURE  1
#define ALE_BLOCKED 2

struct cpsw_slave {
    struct cpsw_slave_regs      *regs;
    struct cpsw_sliver_regs     *sliver;
    int                          slave_num;
    Uint32                       mac_control;
    struct cpsw_slave_data      *data;
};

struct cpdma_desc {
    /* hardware fields */
    Uint32         hw_next;
    Uint32         hw_buffer;
    Uint32         hw_len;
    Uint32         hw_mode;
    /* software fields */
    Uint32         sw_buffer;
    Uint32         sw_len;
    Uint32         sw_next;
    Uint32         reserv;
};

struct cpdma_chan {
    struct  cpdma_desc   *head, *tail;
    void                 *hdp,  *cp,   *rxfree;
};


struct cpsw_priv {
    struct eth_device          *dev;
    struct cpsw_platform_data   data;
    int                         host_port;
    Uint32                      mdio_link;
    Uint32                      phy_mask;

    struct cpsw_regs           *regs;
    Uint8                      *dma_regs;
    Uint8                      *dma_sram_regs;
    struct cpsw_host_regs      *host_port_regs;
    Uint8                      *ale_regs;

    struct cpdma_desc          *descs;
    struct cpdma_desc          *desc_free;
    struct cpdma_chan           rx_chan, tx_chan;

    struct cpsw_slave          *slaves;
};

struct eth_device {
    char name[40];
    unsigned char enetaddr[6];
    int   iobase;
    int   state;

    int  (*init) (struct eth_device*);
    int  (*send) (struct eth_device*, volatile Uint8* packet, int length);
    int  (*recv) (struct eth_device*);
    void (*halt) (struct eth_device*);
#ifdef CONFIG_MCAST_TFTP
    int  (*mcast) (struct eth_device*, u32 ip, u8 set);
#endif
    int  (*write_hwaddr) (struct eth_device*);
    struct eth_device *next;
    void *priv;
};

struct  priv_statistic {
    // 统计
    Uint32 recv_cnt;
    Uint32 recv_no_err;
    Uint32 recv_goose_cnt;
    Uint32 recv_smv_cnt;
    Uint32 recv_adc_cnt;
    Uint8  desc_used;
    Uint8  rst_cpsw_err;
    Uint8  process_cpdma_err;
    Uint8  cpsw_alarm;
    Uint8  cpsw_alarm_ack;
    Uint8  cpsw_err;
    
    Uint16 rst_cpsw;
    Uint16 rst_cpdma;
    Uint16 cpsw_recover;
    Uint16 cpsw_poll;
    Uint16 cpdma_sumbit_err;
    
    // 故障诊断
    Uint16 desc_submitfail;
    Uint16 frame_err;
    Uint16 cpsw_no_recv;
    Uint16 reserv2;
    Uint16 magic;    
};

extern void net_recv(void);
extern void cpsw_recv_check(void);
extern void cpdma_start(void);
extern int  eth_initialize(void);
extern int  cpsw_init(struct eth_device *dev);
extern int  cpsw_send(struct eth_device *dev, volatile Uint8 *packet, int length);

#endif
