#ifndef _INC_BOARD_H
#define _INC_BOARD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include "common_types.h"
#include "fpga_base.h"
#include "fpga_module.h"

//--------------------------------  Define  -----------------------------------

#define CPU_TYPE                C674X
#define	DEVICE_CAN      		"/dev/xcan"
#define MAX_PLAT_DEV_NUM        8
#define HZ6000_LIB                                
#define HZ6104_LIB
#define SUPPORT_CORE_SHAREMEM      

#ifndef SUPPORT_MMB
#define SUPPORT_MMB
#endif

#define OMAP_SHARE_ADDR     0x09E00000
#define MMB_BUF_START_ADDR  0x0A000000
#define CORTEXA9       		13

typedef long double         float64;                


#define ALIGN_N_BYTES(data, n) (((data) + (n) - 1) & (Uint32)(-(n)))

//-----------------------   MIO����     ---------------- --------------
#define MIO7                            7
#define MIO9                            9
#define MIO32                           32
#define MIO33                           33
           
#define UPSTALL                         MIO7
#define DEBUG                           MIO9

#define GPIO_OUT_DISABLE                     0
#define GPIO_OUT_ENABLE                      1
#define GPIO_DIR_IN                          0
#define GPIO_DIR_OUT                         1
#define GPIO_LOW                             0
#define GPIO_HIGH                            1

#define  TRACE_CORE_TIME_IRQ           0          //core_timer
#define  TRACE_MMB1_IRQ                1          //MMB1�ж�
#define  TRACE_CAN1TX_IRQ              2          //CAN1�����ж�
#define  TRACE_CAN1RX_IRQ              3          //CAN1�����ж�
#define  TRACE_MMB2_IRQ                4          //MMB2�ж�
#define  TRACE_TIMER_IRQ               5          //��ʱ���ж�
#define  TRACE_MONITOR_ERR             6          //�ڴ����
#define  TRACE_CAN2TX_IRQ              7          //CAN2�����ж�
#define  TRACE_CAN2RX_IRQ              8          //CAN2�����ж�
#define  TRACE_EXT_CAN1_TX_IRQ         9          //EXT_CAN1�����ж�
#define  TRACE_EXT_CAN1_RX_IRQ         10         //EXT_CAN1�����ж�
#define  TRACE_EXT_CAN2_TX_IRQ         11         //EXT_CAN2�����ж�
#define  TRACE_EXT_CAN2_RX_IRQ         12         //EXT_CAN2�����ж�
#define  TRACE_MAIN_LOOP               15         //��ѭ��

//ÿ��FPGA TICK 50ns������PPS֮��Ӧ��2*10^7��TICK,�������100us
#define FPGA_TICK_1S             (20000000UL)
#define FPGA_TICK_100US          (2000UL)

//-----------------------   MMB     ---------------- --------------
//MMB �շ���󳤶�����
#define MMB1_MAX_RD_WORD_NUM    0x200
#define MMB2_MAX_RD_WORD_NUM    0x400
#define MMB1_MAX_WR_WORD_NUM    0x200
#define MMB2_MAX_WR_WORD_NUM    0x400

#define MMB_DATA_FRAME_HEAD_LEN   3
#define MMB_DATA_FRAME_TAIL_LEN   10

#define INTC		    XScuGic
#define INTC_HANDLER	XScuGic_InterruptHandler
#define INTC_DEVICE_ID	    XPAR_PS7_SCUGIC_0_DEVICE_ID
#define TIMER_DEVICE_ID		XPAR_XSCUTIMER_0_DEVICE_ID
//����MMB�ж�����
#define XPL_IRQ_TYPE_EDGE_RISING    3
#define XPL_IRQ_TYPE_HIGH_LEVEL     1

/*
���    ��ʼ��ַ    ������ַ    �ռ�    ˵��
0   0x00000000  0x04000000  64MB   Core0���롢���������ı�
1   0x04000000  0x099FFFFF  90MB   Core1���롢������
2   0x09A00000  0x09BFFFFF  2MB    Core0/Core1����������
3   0x09C00000  0x09FFFFFF  4MB    Core1�ı���
4   0x0A000000  0x0FFFFFFF  96MB   Core0���롢���������ı�
*/
//DSP�ı�������
#define SHM_MBAR                0x09C00000
#define SHM_MBAR_SIZE           0x00400000
#define FLASH_USED_FLAG         0x58554446
#define FLASH_CONFIG_ADDR       SHM_MBAR            // ���һ���������������ļ�
#define FLASH_FILE_SIZE         0x100000            // �����ļ���С:1Mbytes

//ARM��DSP�����ڴ涨��
#define DSP_SHM_START_ADDR          0x09A00000
#define DSP_SHM_SIZE                0x00200000          //�����ڴ�ռ�2M
#define DSP_FRAM_START_ADDR         DSP_SHM_START_ADDR  
#define DSP_FRAM_SIZE               0x8000              //FRAM�ռ��С32K
#define SYS_FRAM_INF_HEAD               0x55AA
#define SYS_FRAM_INF_BUF_SIZE           128
#define SYS_FRAM_INF_DESC_LEN           20
#define DSP_SYS_FRAM_INF_MBAR           ((DSP_FRAM_START_ADDR) + 0x4000 - SYS_FRAM_INF_BUF_SIZE)

#define MAX_AD_CH_NUM               64
#define VALID_STORE_FLAG            0x55AA
#define COEF_INF_SIZE               512
#define LOCAL_CALIBRATION_COEF_DDR_ADDR   (DSP_FRAM_START_ADDR)
#define REMOTE_CALIBRATION_COEF_DDR_ADDR  (DSP_FRAM_START_ADDR + 0x200)
#define ARM_DSP_MAP_OFFSET          0x40000000

#define EEPROM_START_ADDR           (DSP_SHM_START_ADDR + 0x8000)
#define EEPROM_SIZE                 0x2000
#define EEPROM_FRAME_FLAG           0x55AA
#define EEPROM_FRAME_LEN_OFFSET     68
#define EEPROM_FRAME_DATA_OFFSET    70
#define EEPROM_FRAME_INFO_LEN       72

//-----------------------   FPGA     ---------------- --------------
#define MMB_WR_CRC_EN_START_CNT             10

#define CPU_CORE_NO  1
#define FPGA_MMB1_REG     CORE1_FPGA_MMB1_REG
#define FPGA_MMB2_REG     CORE1_FPGA_MMB2_REG
#define FPGA_SRAM0_START  CORE1_FPGA_SRAM0_START 
#define FPGA_SRAM1_START  CORE1_FPGA_SRAM1_START 
#define MMB1_WR_START     CORE1_MMB1_WR_START 
#define MMB2_WR_START     CORE1_MMB2_WR_START 
#define MMB1_DMA_CFG_ADDR DMA_CHAN1_CFG_ADDR
#define MMB2_DMA_CFG_ADDR DMA_CHAN3_CFG_ADDR

//���忴�Ź��жϺ�
#define AWDT_DEVICE_ID		XPAR_SCUWDT_0_DEVICE_ID
#define AWDT_IRPT_INTR		XPAR_SCUWDT_INTR

//����CAN0�жϺ�
#define CAN_DEVICE_ID       XPAR_PS7_CAN_1_DEVICE_ID
#define CAN_INTR_VEC_ID     XPAR_XCANPS_1_INTR
#define SW_INTR_VEC_ID      0

//����PL�жϺ�
#define MMB1_PL_IRQ_ID      XPS_FPGA1_INT_ID
#define MMB2_PL_IRQ_ID      XPS_FPGA3_INT_ID

//����L1�����жϺ�
#define L1_PARITY_INT_ID    XPS_CORE_PARITY1_INT_ID
//-----------------------          TICK����       ------------------------------//
#define T1US                    (1000)
#define T_US(x)                 ((x)*T1US)
#define T1MS                    (1000*T1US)
#define T_MS(x)                 ((x)*T1MS)
#define TSCL                    (1000)
#define QUERY_NOW_TIME          getNowTimerTic()
#define ONE_TICK_NS             (3UL)                       //ÿ����ʱ��TICK��Ӧ��ns��

//-----------------------          �ζ���      ------------------------------//
#define INIT_CODE
#define INIT_LOW_CODE
#define RTM_CODE            __attribute__((section( ".rtm_code")))
#define RTM_CODE1
#define RTM_CODE2
#define RTM_DATA1           __attribute__((section( ".rtm_data")))
#define RTM_DATA2

#define MDSP_NO         (0x0)
#define QDSP_NO         (0x1)

#define BIT(n) ((1UL) << (n))

#define FORCE_ALLOC_MASK        0x80                        //DSP_CALLOCǿ���ڴ����

typedef struct addr_tbl
{
    Uint8 addr_index;
    Uint32 min_valid_addr;
    Uint32 max_valid_addr;
}ADDR_TBL_TYPE;

//-----------------------          DMAͨ������      ------------------------------//
typedef enum
{
    MMB1_DMA_CH     = 0,
    MMB2_DMA_CH     = 1,
    PROCESS_DMA_CH1 = 2,
    PROCESS_DMA_CH2 = 3,
    PROCESS_DMA_CH3 = 4,
    COMM1_DMA_CH    = 5,
    COMM2_DMA_CH    = 6,
    COMM3_DMA_CH    = 7,
}DMA_CONFIG;

//-----------------------          XADCͨ�������ݽṹ����      ------------------------------//
typedef struct
{
    float cur_value;
    float max_value;
    float min_value;
}XADC_DATA;

typedef enum
{
    XADC_TEMP_CH        = 0,
    XADC_VCCPINT_CH     = 1,
    XADC_VCCPAUX_CH     = 2,
    XADC_VCCPDRO_CH     = 3,
}XADC_CH;


//-----------------------          SOC-LINKͨ������      ------------------------------//
typedef enum
{
    ADC_LINK_CH         = 0,    //ADC����
    DSP_LINK_CH         = 1,    //�������
    PROCESS_LINK_CH     = 2,    //���̲㻥��
}FPGA_LINK_CONFIG;

//--------------------------------------------------------------------------//
// Global variables                                                         //
//--------------------------------------------------------------------------//
extern Uint8 char_bits;
extern Uint8 int8_size;
extern Uint8 short_size;
extern Uint8 int_size;
extern Uint8 long_size;
extern Uint8 float_size;
extern Uint8 point_size;
extern Uint8 longlong_size;
extern Uint8 double_size;
extern Uint8 int16_size;
extern Uint8 int32_size;
extern Uint8 alig_size;
extern Uint32 board_type;
extern Uint8 share_mode;
extern Uint32 version;
extern Uint8 mcpu_addr;
extern Uint8 this_core;
Uint8   signal_address;
extern int   self_pid;

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
extern Uint32 mmb1_start_time;
extern Uint32 mmb2_start_time;
extern Uint32 lvl1_locked_int_time;
extern Uint32 lvl2_locked_int_time;
extern Uint32 while_loop_count;
extern Uint32 task1_begin_time;
extern Uint32 task2_begin_time;

extern Uint8  mmb1_data_ok;
extern Uint8  mmb2_data_ok;
extern Uint8  bus_bsj_level;
extern char   bs_flag;
extern Uint8  sync_err;
extern Uint8  pps_miss;
extern Uint32 pps_time_irig;

extern Uint32 mem1_free_size;                                       //Ӧ�ó�����Ϊdsp_callocԤ���ڴ�1(Ƭ��OCM)�ռ��С����λByte��ע����LDF�ļ�����޸ġ�
extern Uint32 mem1_free_addr;                                       //Ӧ�ó�����Ϊdsp_callocԤ���ڴ�1(Ƭ��OCM)�ռ���ʼ��ַ
extern Uint32 mem1_used_size;                                       //Ӧ�ó�����ʹ��Ԥ���ڴ�1�Ŀռ��С����λByte
extern Uint32 mem2_free_size;                                       //Ӧ�ó�����Ϊdsp_callocԤ���ڴ�2(����link�ļ��Զ���)�ռ��С����λByte
extern Uint32 mem2_free_addr;                                       //Ӧ�ó�����Ϊdsp_callocԤ���ڴ�2(����link�ļ��Զ���)�ռ���ʼ��ַ
extern Uint32 mem2_used_size;                                       //Ӧ�ó�����ʹ��Ԥ���ڴ�2�Ŀռ��С����λByte


extern Uint8 bsp_quick_para_set;                                    //ϵͳ��֧��������ֵ������
extern Uint8 app_quick_para_set;                                    //Ӧ�ó���֧��������ֵ������
extern Uint8 self_keep_alive;                                       //MDSP�ж϶�ʧ����������

extern Uint8 trans_mmb1_addr_err_flag;
extern Uint8 trans_mmb2_addr_err_flag;

typedef union
{
    volatile Uint32 all;
    struct
    {
        volatile Uint32   flash_err:1;
        volatile Uint32   ad7656_err:1;
        volatile Uint32   ad7938_err:1;
        volatile Uint32   fiber_err:1;
        volatile Uint32   can0_err:1;
        volatile Uint32   can1_err:1;
        volatile Uint32   mmb1_err:1;
        volatile Uint32   mmb2_err:1;
        volatile Uint32   hard_err_reserved:8;
        volatile Uint32   task1_stall:1;
        volatile Uint32   task2_stall:1;
        volatile Uint32   task3_stall:1;
        volatile Uint32   task4_stall:1;
        volatile Uint32   soft_err_reserved:12;
    } bit;
} SYS_STAUTS_WORD;
extern SYS_STAUTS_WORD sys_status;

//--------------------------------------------------------------------------//
// Extern functions                                                         //
//--------------------------------------------------------------------------//
extern Uint8 getInt8(char *data,int *index);
extern void putInt8(char *data,int *index,Uint8 value);
extern Uint16 getInt16(char *data, int *index);
extern void putInt16(char *data,int *offset,Uint16 value);
extern Uint32 getInt32(char *data, int *index);
extern void putInt32(char *data,int *offset,Uint32 value);
extern Uint64 getInt64(char *data, int *index);
extern void putInt64(char *data,int *offset, Uint64 value);
extern int  getString(char *src,int *offset,char *dest,Uint16 length);
extern void putString(char *src, int length, char *dest, int *offset);
extern void putValue(char *dest, int *offset, char *src, int size);
extern void putMemory(char *dest, int *offset, char *src, int size);
extern Uint32 getValue(char *data, int *index, int size);
extern void typeSizeCheck(void);
extern void waitForcmd(void);
extern void resetCpu(void);
extern void *dsp_calloc(size_t nmemb, size_t size, char mem_type);  //mem_typeֵ 1(OCM) 2/3(Ƭ��DDR)
extern void monitorCpuLoad(void);
extern void configMmb(Uint8 mmb_no, Uint8  total_no,Uint16 start_word_no,
                      Uint16 length,  Uint8 send_no);
extern void enableMmb(Uint8 send_no0, Uint8 send_no1);
extern void registerSystemStatus(void);
extern void checkMmb1Status(void);
extern void checkMmb2Status(void);


extern void disableMMB1(void);
extern void disableMMB2(void);
extern void disableTimer(void);
extern Uint8 checkMemAddrValid(Uint32 start_addr, Uint32 len);

extern Uint32 getProgramTime(void);
extern Uint32 getProgramCrc(void);
extern void checkTypeSize();

extern Uint32 *getMmb1BufPtr(void);
extern Uint32 *getMmb2BufPtr(void);
extern int getViewDataLen(Uint32 addr);


/*********************CAN���ͽӿ�***********************/
extern int sendCanMsg(Uint8 app_type, Uint8 dst, int len, char *data);

/*********************˫SOCͨ�Žӿ�***********************/
extern void initSocLink(void);
/*********************************************************
���շ���ֵ
0��OK,
1�����ճ��ȳ�������ֵ,
2����������֡���δ����,
3����������֡��Ų�����,
4����������֡CRC16����,
5��֡��ʽ����֡ͷ֡β����,
6�����ͽ���֡�����ò�һ��
**********************************************************/
extern Uint8 recvDSPLinkData(Uint32 *app_rx_data, Uint16 word_len);
extern Uint8 sendDSPLinkData(Uint32 *app_tx_data, Uint16 word_len);//0��OK,1�����ͳ��ȳ�������ֵ,2: ��һ���жϲ�����
extern int enableSOCLinkTx(FPGA_LINK_CONFIG link_ch);               //����ֵ0��OK,1��ͨ���Ŵ���
extern int enableSOCLinkRx(FPGA_LINK_CONFIG link_ch);               //����ֵ0��OK,1��ͨ���Ŵ���
extern int disableSOCLinkTx(FPGA_LINK_CONFIG link_ch);              //����ֵ0��OK,1��ͨ���Ŵ���
extern int disableSOCLinkRx(FPGA_LINK_CONFIG link_ch);              //����ֵ0��OK,1��ͨ���Ŵ���
/*********************ͨ�� DMA�ӿ�***********************/
extern int moveDMAData(Uint32 src_addr, Uint32 dest_addr, Uint32 data_len, DMA_CONFIG dma_channel);
extern int isMemDMABusy(DMA_CONFIG dma_channel);


/*********************XADC���ݲɼ�***********************/
//XADC_CH��XADC_DATA�ο�board.h�нṹ���壬����ֵ0��ʾ�ɹ���1��ʾpxadc_dataָ��ΪNULL��2��ʾͨ���Ŵ���
extern int getXAdcData(XADC_CH ch, XADC_DATA *pxadc_data);


/*********************ϵͳ�ӿ�***********************/
extern void EnableDog(void);
extern void DisableDog(void);
extern void KickDog(void);
extern void setBJJ(void);
extern void clrBJJ(void);
extern void clearBJJ(void);
extern void setBSJ(void);
extern void clrBSJ(void);
extern void clearBSJ(void);
extern void setQd(void);
extern void clrQd(void);
extern void setUpstall(void);
extern void clearUpstall(void);
extern Uint32 readNowTime(void);
extern Uint32 cli(void);
extern void sti(Uint32 imask);
extern Uint32 getNowTimerTic(void);
extern void lightRunLed(Uint8 led_value);
extern Uint32 getFpgaTick(void);
extern void Xil_L1DCacheInvalidateRange(unsigned int adr, unsigned len);
extern void Xil_L1DCacheFlushRange(unsigned int adr, unsigned len);

/*********************FRAM���ʽӿ�***********************/
extern void *nvram_malloc(size_t size);                             //DSPʹ��NVRAM�ķ��亯��, ����0
extern void *nvram_calloc(size_t nmemb, size_t size);               //DSPʹ��NVRAM�ķ��亯��, ����0



/*********************��ʱ�ӿ�***********************/
extern void delay_ms(Uint32 delay_cnt);
extern void delayUs(Uint32 delay_cnt);
extern void delayNsTimer(Uint32 delay_ns);
extern void startTimer(void);
extern int  initDmaChan(Uint8 chan, Uint32 dma_base_addr, Uint32 dma_stat_addr, Uint16 max_index, Uint16 frame_offset);
extern int  initDmaChanWithMultiLink(Uint8 chan, Uint32 dma_base_addr, Uint32 dma_stat_addr, Uint16 max_index, Uint16 frame_offset);

#ifdef __cplusplus
}
#endif

#endif // end of _INC_XXX_H
