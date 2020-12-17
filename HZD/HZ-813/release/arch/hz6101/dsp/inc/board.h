
#ifndef INC_BOARD_H
#define INC_BOARD_H

#include <stdlib.h>
#include <c6x.h>
#include "common_types.h"
#include "evm811x_gpio.h"
#include "evm811x_pinmux.h"
#include "evm811x_gpmc.h"
#include "hw_dspcache.h"
#include "hw_dspintc.h"
#include "edma.h"
#include "stream.h"
#include "fpga_module.h"
#include "cpsw_net.h"

#define CPU_TYPE                C674X

#define HZ6000_LIB                                
#define SUPPORT_CORE_SHAREMEM
#define SUPPORT_MMB3_OPTIMIZE

#ifndef SUPPORT_MMB
#define SUPPORT_MMB
#define SUPPORT_MMB_NRT
#endif

#define CLEAR_MMB1_INT_FLAG             GPIO2_IRQSTATUS_0 |= 0x1<<17
#define CLEAR_MMB2_INT_FLAG             GPIO2_IRQSTATUS_1 |= 0x1<<16

#define SHM_MBAR                0x40300000
#define SHM_MBAR_SIZE           0x00020000
#define ARM_DSP_MAP_OFFSET      0x40000000

#define OMAP_SHARE_ADDR         0xAF600000
#define GPMC_START_ADDR         0x11000000
#define FPGA_START_ADDR         0x12000000


#define BOARD_ADDR_REG          (FPGA_START_ADDR+0x80C*2)
#define CAN_START_ADDR          (FPGA_START_ADDR+0x0e00*2)
#define CAN_RST_ADDR            (FPGA_START_ADDR+0x0f00*2)

#define FPGA_SRAM0_START        FPGA_START_ADDR

#define SMV_BUF_START_ADDR           0xA9000000
#define MMB_BUF_START_ADDR           0xB0000000
#define MMB_BUF_END_ADDR             0xBFFFFFFF

#define MMB_DATA_FRAME_HEAD_LEN      3
#define MMB_DATA_FRAME_TAIL_LEN      10

#define pFPGA_VER_TIME_L             (volatile Uint16 *)(FPGA_GPIO_ADDR + 0x0c*2) 
#define pFPGA_VER_TIME_H             (volatile Uint16 *)(FPGA_GPIO_ADDR + 0x0d*2)

#define pRAM_DATA_CLEAR              (volatile Uint16 *)(FPGA_START_ADDR + 0x2003*2) 
#define pBOARD_ADDR_REG              (volatile Uint16 *)(BOARD_ADDR_REG) 
#define NMI_INT_BIT                 (1<<1)
#define MMB1_INT_BIT                (1<<4)
#define CAN1_INT_BIT                (1<<5)
#define MMB2_INT_BIT                (1<<6)
#define TIMER_INT_BIT               (1<<7)

#define BIT(x)                      (1<<(x))

#define FLASH_USED_FLAG         	0x58554446
#define FLASH_CONFIG_ADDR       	0xAF400000  
#define FLASH_FILE_SIZE         	0x40000     

extern Uint32 version;
extern Uint8  alig_size;
extern Uint8  int8_size;
extern Uint8  int16_size;
extern Uint8  int32_size;
extern Uint32 board_type;
extern Uint8  share_mode;
extern Uint8  this_core;
extern int    self_pid;
extern Uint32 lvl1_run_cnt;
extern Uint32 lvl2_run_cnt;
extern Uint32 lvl3_run_cnt;
extern Uint32 lvl4_run_cnt;
extern Uint32 lvl1_run_time;
extern Uint32 lvl2_run_time;
extern Uint32 lvl3_run_time;
extern Uint32 max_lvl1_run_time;
extern Uint32 max_lvl2_run_time;
extern Uint32 max_lvl3_run_time;
extern Uint32 while_loop_cycle;

extern Uint32 mmb1_frame_num;
extern Uint32 mmb2_frame_num;
extern Uint32 mmb1_start_time;
extern Uint32 mmb2_start_time;
extern Uint32 lvl1_locked_int_time;
extern Uint32 lvl2_locked_int_time;


extern Uint8  fpga_crc_err; 

#define cli _disable_interrupts
#define sti _restore_interrupts

#define INIT_CODE
#define INIT_LOW_CODE
#define RTM_CODE
#define RTM_CODE1
#define RTM_CODE2
#define RTM_DATA1
#define RTM_DATA2

#define QUERY_NOW_TIME          (TIMER4_TCRR)

extern Uint32 getProgramTime(void);
extern Uint32 getProgramCrc(void);
extern void   checkTypeSize(void);
extern void   registerSystemStatus(void);
extern void   waitForcmd(void);
extern void   startTimer(void);
extern Uint8  getInt8(char *data,int *index);
extern void   putInt8(char *data,int *index,Uint8 value);
extern Uint16 getInt16(char *data, int *index);
extern void   putInt16(char *data,int *offset,Uint16 value);
extern Uint32 getInt32(char *data, int *index);
extern void   putInt32(char *data,int *offset,Uint32 value);
extern Uint64 getInt64(char *data, int *index);
extern void   putInt64(char *data,int *offset, Uint64 value);
extern int    getString(char *src,int *offset,char *dest,Uint16 length);
extern void   putString(char *src, int length, char *dest, int *offset);
extern void   putValue(char *dest, int *offset, char *src, int size);
extern void   putMemory(char *dest, int *offset, char *src, int size);
extern Uint32 getValue(char *data, int *index, int size);
extern void   resetCpu(void);
extern void   delayUs(Uint32 count);
extern void   monitorCpuLoad(void);
extern void   enableMmb(Uint8, Uint8);
extern void   configMmb(Uint8,Uint8,Uint16,Uint16,Uint8);                                     

extern void  *dsp_calloc(size_t nmemb, size_t size, char mem_type); 
extern Uint32 readNowTime(void);
extern Uint32 readFpgaInt0StartTime(void);
extern Uint32 readFpgaInt1StartTime(void);
extern Uint32 *getMmb1BufPtr(void);
extern Uint32 *getMmb2BufPtr(void);

extern int  checkMemDMABusy(Uint8);
extern int  checkPcieTxBusy(Uint8);
extern void sendAllCANMsg(void);
extern int  dmaOperate(Uint32 , Uint32 , Uint32 , Uint8 );
extern void invalidCache(unsigned int baseAddr, unsigned int byteSize);
extern int  sendPcieData(Uint32 pcie_addr, Uint8 *send_data_p, Uint32 data_len, Uint8 dma_channel);
extern int  initDmaChan(Uint8 chan, Uint32 dma_base_addr, Uint32 dma_stat_addr, Uint16 max_index, Uint16 frame_offset);
extern int  initDmaChanWithMultiLink(Uint8 chan, Uint32 dma_base_addr, Uint32 dma_stat_addr, Uint16 max_index, Uint16 frame_offset);



typedef struct
{
    signed int      zd;         
    float           gain;
    float           angle_diff;
    float           resis;
}S6101_16chan_para;

typedef struct
{
    signed int      zd;
    float           gain;
}S6101_24chan_para;

typedef struct
{
    unsigned short      version;        
    unsigned short      total_chan;
    S6101_16chan_para   chan_7616[48];
    S6101_24chan_para   chan_1247[4];
    char                save_flag;
    char                align[3];
    unsigned short      check_sum;
}S6101_para;

typedef struct
{
    unsigned short  version;
    unsigned short  save_flag;
    float vol_chan1_table[11];
    float cur_chan1_table[11];
    float vol_chan2_table[11];
    float cur_chan2_table[11];
    unsigned char   vol_pga;
    unsigned char   cur_pga;
    unsigned short  check_sum;
}S6101_1247_para;

typedef struct
{
    S6101_para      AD7616_para;           
    S6101_1247_para AD1247_para;           
}S6101_AD_para;

inline void openInterrupt (void)
{
    _enable_interrupts();
}

inline void closeInterrupt (void)
{
    _disable_interrupts();
}

inline void setQD(void)
{
    GPIO1_CLEARDATAOUT = 1<<11;
}
inline void clrQD(void)
{
    GPIO1_SETDATAOUT = 1<<11;
}

inline void clearQD()
{
    clrQD();
}

inline Uint8 readBSJ(void)
{
    return (Uint8)((GPIO4_DATAIN >> 20) & 1); // GP4_20
}

inline Uint8 readBJJ(void)
{
    return (Uint8)((GPIO2_DATAIN >> 9) & 1);  // GP2_9
}

inline Uint8 readQD(void)
{
    return (Uint8)((GPIO2_DATAIN >> 21) & 1); // GP2_21
}

inline Uint8 readFpgaCrcErr(void)
{
    return (Uint8)((GPIO2_DATAIN >> 8) & 1);
}

inline void setUpstall(void)
{
    GPIO2_SETDATAOUT = 1<<7;
}
inline void clrUpstall(void)
{
    GPIO2_CLEARDATAOUT = 1<<7;
}

inline void writeMmb1Period(Uint32 tic)
{
   *pMmb1_Int_Period_Addr = tic;
}
inline void writeMmb2Period(Uint32 tic)
{
   *pMmb2_Int_Period_Addr = tic;
}

//----------------------------------------------------------
//¶ÁÈ¡AD°å¿¨Á¬½Ó×´Ì¬
//----------------------------------------------------------
inline Uint8  readAdBoardStatus(void)
{
    Uint8 data;
    
    data = (Uint8)((GPIO0_DATAIN >> 3) & 0x01);
    data = data << 1;
    data = data + (Uint8)((GPIO0_DATAIN >> 5) & 0x01);
    
    return data;
}


#endif
