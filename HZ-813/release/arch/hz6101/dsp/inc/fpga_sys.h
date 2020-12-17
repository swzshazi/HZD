
#ifndef FPGA_SYS_H_
#define FPGA_SYS_H_

#include "fpga_base.h"

#define Mmb1_Int_Period_Addr        (FPGA_EMIF_BASE_ADDR +0x000*2)
#define Mmb1_Set_Word_Num_Addr      (FPGA_EMIF_BASE_ADDR +0x002*2)
#define Mmb1_Enable_Reg             (FPGA_EMIF_BASE_ADDR +0x003*2)
#define Mmb1_Max_cnt_Addr           (FPGA_EMIF_BASE_ADDR +0x004*2)
#define Mmb1_Int_Delay              (FPGA_EMIF_BASE_ADDR +0x006*2)
#define Mmb1_Irq_cnt                (FPGA_EMIF_BASE_ADDR +0x00c*2)


#define Mmb2_Int_Period_Addr        (FPGA_EMIF_BASE_ADDR +0x010*2)
#define Mmb2_Set_Word_Num_Addr      (FPGA_EMIF_BASE_ADDR +0x012*2)
#define Mmb2_Enable_Reg             (FPGA_EMIF_BASE_ADDR +0x013*2)
#define Mmb2_Max_cnt_Addr           (FPGA_EMIF_BASE_ADDR +0x014*2)
#define Mmb2_Int_Delay              (FPGA_EMIF_BASE_ADDR +0x016*2)
#define Mmb2_Irq_cnt                (FPGA_EMIF_BASE_ADDR +0x01c*2)

#define MASTER_SLAVE_MODE           (FPGA_EMIF_BASE_ADDR +0x000e*2)


#define pMmb1_Int_Period_Addr       (volatile Uint32 *)(Mmb1_Int_Period_Addr)
#define pMmb2_Int_Period_Addr       (volatile Uint32 *)(Mmb2_Int_Period_Addr)
#define pMmb1_Int_Delay             (volatile Uint32 *)(Mmb1_Int_Delay)
#define pMmb2_Int_Delay             (volatile Uint32 *)(Mmb2_Int_Delay)
#define pMmb1_Set_Word_Num_Addr     (volatile Uint16 *)(Mmb1_Set_Word_Num_Addr)
#define pMmb2_Set_Word_Num_Addr     (volatile Uint16 *)(Mmb2_Set_Word_Num_Addr)
#define pMmb1_Max_cnt_Addr          (volatile Uint16 *)(Mmb1_Max_cnt_Addr)
#define pMmb2_Max_cnt_Addr          (volatile Uint16 *)(Mmb2_Max_cnt_Addr)
#define pTask1_Enable_Reg           (volatile Uint16 *)(Mmb1_Enable_Reg)
#define pTask2_Enable_Reg           (volatile Uint16 *)(Mmb2_Enable_Reg)
#define pMaster_slave_mode          (volatile Uint16 *)(MASTER_SLAVE_MODE)

#define Mmb1_Dsp_Int_Low_Addr       (FPGA_EMIF_BASE_ADDR +0x008*2)
#define Mmb1_Dsp_Int_High_Addr      (FPGA_EMIF_BASE_ADDR +0x009*2)
#define Mmb2_Dsp_Int_Low_Addr       (FPGA_EMIF_BASE_ADDR +0x018*2)
#define Mmb2_Dsp_Int_High_Addr      (FPGA_EMIF_BASE_ADDR +0x019*2)

#define Mmb1_Dsp_Begin_Low_Addr     (FPGA_EMIF_BASE_ADDR +0x00a*2)
#define Mmb1_Dsp_Begin_High_Addr    (FPGA_EMIF_BASE_ADDR +0x00b*2)
#define Mmb2_Dsp_Begin_Low_Addr     (FPGA_EMIF_BASE_ADDR +0x01a*2)
#define Mmb2_Dsp_Begin_High_Addr    (FPGA_EMIF_BASE_ADDR +0x01b*2)


#define FPGA_realtick_Low_Addr      (FPGA_EMIF_BASE_ADDR +0x00c*2)
#define FPGA_realtick_Hign_Addr     (FPGA_EMIF_BASE_ADDR +0x00d*2)

#define pMmb1_Dsp_Int_Low_Addr      (volatile Uint16 *)(Mmb1_Dsp_Int_Low_Addr)
#define pMmb1_Dsp_Int_High_Addr     (volatile Uint16 *)(Mmb1_Dsp_Int_High_Addr)
#define pMmb2_Dsp_Int_Low_Addr      (volatile Uint16 *)(Mmb2_Dsp_Int_Low_Addr)
#define pMmb2_Dsp_Int_High_Addr     (volatile Uint16 *)(Mmb2_Dsp_Int_High_Addr)

#define pMmb1_Dsp_Begin_Low_Addr    (volatile Uint16 *)(Mmb1_Dsp_Begin_Low_Addr)
#define pMmb1_Dsp_Begin_High_Addr   (volatile Uint16 *)(Mmb1_Dsp_Begin_High_Addr)
#define pMmb2_Dsp_Begin_Low_Addr    (volatile Uint16 *)(Mmb2_Dsp_Begin_Low_Addr)
#define pMmb2_Dsp_Begin_High_Addr   (volatile Uint16 *)(Mmb2_Dsp_Begin_High_Addr)


#define MMB1_RXBUF_WR_REG           (FPGA_GEN_DMA_ADDR+ (0x102<<1))     // FPGA主动推送的数据指针
#define MMB2_RXBUF_WR_REG           (FPGA_GEN_DMA_ADDR+ (0x202<<1))     // FPGA主动推送的数据指针

#define pMMB1_RXBUF_WR_REG          (volatile Uint32 *)(MMB1_RXBUF_WR_REG)
#define pMMB2_RXBUF_WR_REG          (volatile Uint32 *)(MMB2_RXBUF_WR_REG)

typedef struct  //主CPU
{
	Uint32 set_int_period;

	Uint16 set_int_word_num;
	
	Uint16 set_cfg:1;
	Uint16 set_cfg_rev:15;	
	
	Uint32 max_task_index;

	Uint16 set_int_delay;
	Uint16 reserve_6;	

	Uint32 int_tic;
	
	Uint32 int_begin_tic;

	Uint32 real_tic;
	
	Uint16 master_tag;
	
	Uint16 reserve_f;	

}MMB_REG_MAP;   



#endif  


