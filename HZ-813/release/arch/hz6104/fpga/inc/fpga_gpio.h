/********************************************************************
*           File Name   : fpga_gpio.h                             *
*           Date        : 2020-05-8                                *
*           Written by  : zqy                               *
*           Description : FPGA_GPIO       *
********************************************************************/

#ifndef _FPGA_GPIO_
#define _FPGA_GPIO_

#include "fpga_base.h"

#define GPIO_SPE_WREN_CFG_ADDR         (volatile Uint32 *)(FPGA_GPIO_ADDR + (0x1<<2))  
#define GPIO_SPE_SET_ADDR             (volatile Uint32 *)(FPGA_GPIO_ADDR + (0x2<<2))  


#define GPIO_EN_CFG_ADDR             (volatile Uint32 *)(FPGA_GPIO_ADDR + (0x3<<2))  
#define GPIO_DIR_CFG_ADDR            (volatile Uint32 *)(FPGA_GPIO_ADDR + (0x4<<2))  
#define GPIO_DO_CFG_ADDR             (volatile Uint32 *)(FPGA_GPIO_ADDR + (0x5<<2))  
#define GPIO_DI_CFG_ADDR             (volatile Uint32 *)(FPGA_GPIO_ADDR + (0x6<<2))  



typedef struct
{
    volatile Uint32   arm_bj_n	  :1   ;	 
	volatile Uint32   dsp_bj_n    :1   ;     
	volatile Uint32   arm_bs_n    :1   ;     
	volatile Uint32   dsp_bs_n	  :1   ;	 
    volatile Uint32   dsp_qd_n	  :1   ;	 
    volatile Uint32   reserved    :27;
}GPIO_SPE_WREN_MAP;

typedef struct
{

    volatile Uint32   arm_bj_set_n	  :1   ;
	volatile Uint32   dsp_bj_set_n    :1   ;
	volatile Uint32   arm_bs_set_n    :1   ;
	volatile Uint32   dsp_bs_set_n	  :1   ;
    volatile Uint32   dsp_qd_set_n	  :1   ;
    volatile Uint32   reserved    :27;
}GPIO_SPE_SET_MAP;



typedef struct
{

    volatile Uint32   gpio_en_bit0	  :1   ;	 
	volatile Uint32   gpio_en_bit1    :1   ;     
	volatile Uint32   gpio_en_bit2    :1   ;     
	volatile Uint32   gpio_en_bit3	  :1   ;	 

	volatile Uint32   gpio_en_bit4    :1   ;             
    volatile Uint32   gpio_en_bit5    :1   ;   
	volatile Uint32   gpio_en_bit6    :1   ;             
	volatile Uint32   gpio_en_bit7    :1   ;             
	volatile Uint32   gpio_en_bit8    :1   ;             
	volatile Uint32   gpio_en_bit9    :1   ;             
	volatile Uint32   gpio_en_bit10   :1   ;             
	volatile Uint32   gpio_en_bit11   :1   ;             
	volatile Uint32   gpio_en_bit12   :1   ;             
	volatile Uint32   gpio_en_bit13   :1   ;             
	volatile Uint32   gpio_en_bit14   :1   ;             
    volatile Uint32   gpio_en_bit15   :1   ;    
	volatile Uint32   gpio_en_bit16   :1   ;             
	volatile Uint32   gpio_en_bit17   :1   ;             
	volatile Uint32   gpio_en_bit18   :1   ;             
	volatile Uint32   gpio_en_bit19   :1   ;             
	volatile Uint32   gpio_en_bit20   :1   ;             
	volatile Uint32   gpio_en_bit21   :1   ;             
	volatile Uint32   gpio_en_bit22   :1   ;             
    volatile Uint32   gpio_en_bit23   :1   ;   
	volatile Uint32   gpio_en_bit24   :1   ;             
	volatile Uint32   gpio_en_bit25   :1   ;             
	volatile Uint32   gpio_en_bit26   :1   ;             
	volatile Uint32   gpio_en_bit27   :1   ;             
	volatile Uint32   gpio_en_bit28   :1   ;             
	volatile Uint32   gpio_en_bit29   :1   ;             
	volatile Uint32   gpio_en_bit30   :1   ;             
	volatile Uint32   gpio_en_bit31   :1   ; 
}GPIO_ENABLE_MAP;

//鏂瑰悜
typedef struct
{
    volatile Uint32   gpio_dir_bit0	    :1  ;		//鎶ヨ
	volatile Uint32   gpio_dir_bit1    :1  ;     //arm渚ч棴閿?
	volatile Uint32   gpio_dir_bit2    :1  ;     //dsp渚ч棴閿?
	volatile Uint32   gpio_dir_bit3	   :1  ;		//dsp渚у惎鍔?

	volatile Uint32   gpio_dir_bit4    :1  ;             
    volatile Uint32   gpio_dir_bit5    :1  ;   
	volatile Uint32   gpio_dir_bit6    :1  ;             
	volatile Uint32   gpio_dir_bit7    :1  ;             
	volatile Uint32   gpio_dir_bit8    :1  ;             
	volatile Uint32   gpio_dir_bit9    :1  ;             
	volatile Uint32   gpio_dir_bit10   :1  ;             
	volatile Uint32   gpio_dir_bit11   :1  ;             
	volatile Uint32   gpio_dir_bit12   :1  ;             
	volatile Uint32   gpio_dir_bit13   :1  ;             
	volatile Uint32   gpio_dir_bit14   :1  ;             
    volatile Uint32   gpio_dir_bit15   :1  ;    
	volatile Uint32   gpio_dir_bit16   :1  ;             
	volatile Uint32   gpio_dir_bit17   :1  ;             
	volatile Uint32   gpio_dir_bit18   :1  ;             
	volatile Uint32   gpio_dir_bit19   :1  ;             
	volatile Uint32   gpio_dir_bit20   :1  ;             
	volatile Uint32   gpio_dir_bit21   :1  ;             
	volatile Uint32   gpio_dir_bit22   :1  ;             
    volatile Uint32   gpio_dir_bit23   :1  ;   
	volatile Uint32   gpio_dir_bit24   :1  ;             
	volatile Uint32   gpio_dir_bit25   :1  ;             
	volatile Uint32   gpio_dir_bit26   :1  ;             
	volatile Uint32   gpio_dir_bit27   :1  ;             
	volatile Uint32   gpio_dir_bit28   :1  ;             
	volatile Uint32   gpio_dir_bit29   :1  ;             
	volatile Uint32   gpio_dir_bit30   :1  ;             
	volatile Uint32   gpio_dir_bit31   :1  ; 
}GPIO_DIR_MAP;

//output value
typedef struct
{
    volatile Uint32   gpio_out_val_bit0	  	  :1 ;		
	volatile Uint32   gpio_out_val_bit1	  :1 ;    
	volatile Uint32   gpio_out_val_bit2	  :1 ;     
	volatile Uint32   gpio_out_val_bit3	  	  :1 ;		

	volatile Uint32   gpio_out_val_bit4   :1 ;             
    volatile Uint32   gpio_out_val_bit5   :1 ;   
	volatile Uint32   gpio_out_val_bit6   :1 ;             
	volatile Uint32   gpio_out_val_bit7   :1 ;             
	volatile Uint32   gpio_out_val_bit8   :1 ;             
	volatile Uint32   gpio_out_val_bit9   :1 ;             
	volatile Uint32   gpio_out_val_bit10  :1 ;             
	volatile Uint32   gpio_out_val_bit11  :1 ;             
	volatile Uint32   gpio_out_val_bit12  :1 ;             
	volatile Uint32   gpio_out_val_bit13  :1 ;             
	volatile Uint32   gpio_out_val_bit14  :1 ;             
    volatile Uint32   gpio_out_val_bit15  :1 ;             
	volatile Uint32   gpio_out_val_bit16  :1 ;             
	volatile Uint32   gpio_out_val_bit17  :1 ;             
	volatile Uint32   gpio_out_val_bit18  :1 ;             
	volatile Uint32   gpio_out_val_bit19  :1 ;             
	volatile Uint32   gpio_out_val_bit20  :1 ;             
	volatile Uint32   gpio_out_val_bit21  :1 ;             
	volatile Uint32   gpio_out_val_bit22  :1 ;             
    volatile Uint32   gpio_out_val_bit23  :1 ;   
	volatile Uint32   gpio_out_val_bit24  :1 ;             
	volatile Uint32   gpio_out_val_bit25  :1 ;             
	volatile Uint32   gpio_out_val_bit26  :1 ;             
	volatile Uint32   gpio_out_val_bit27  :1 ;             
	volatile Uint32   gpio_out_val_bit28  :1 ;             
	volatile Uint32   gpio_out_val_bit29  :1 ;             
	volatile Uint32   gpio_out_val_bit30  :1 ;             
	volatile Uint32   gpio_out_val_bit31  :1 ; 
}GPIO_OUT_VALUE_MAP;



//input value
typedef struct
{
    volatile Uint32   gpio_in_val_bit0	  	 :1 ;		//鎶ヨ
	volatile Uint32   gpio_in_val_bit1	 :1 ;     //arm渚ч棴閿?
	volatile Uint32   gpio_in_val_bit2	 :1 ;     //dsp渚ч棴閿?
	volatile Uint32   gpio_in_val_bit3	  	 :1 ;		//dsp渚у惎鍔?

	volatile Uint32   gpio_in_val_bit4   :1 ;             
    volatile Uint32   gpio_in_val_bit5   :1 ;   
	volatile Uint32   gpio_in_val_bit6   :1 ;             
	volatile Uint32   gpio_in_val_bit7   :1 ;             
	volatile Uint32   gpio_in_val_bit8   :1 ;             
	volatile Uint32   gpio_in_val_bit9   :1 ;             
	volatile Uint32   gpio_in_val_bit10  :1 ;             
	volatile Uint32   gpio_in_val_bit11  :1 ;             
	volatile Uint32   gpio_in_val_bit12  :1 ;             
	volatile Uint32   gpio_in_val_bit13  :1 ;             
	volatile Uint32   gpio_in_val_bit14  :1 ;             
    volatile Uint32   gpio_in_val_bit15  :1 ;    
	volatile Uint32   gpio_in_val_bit16  :1 ;             
	volatile Uint32   gpio_in_val_bit17  :1 ;             
	volatile Uint32   gpio_in_val_bit18  :1 ;             
	volatile Uint32   gpio_in_val_bit19  :1 ;             
	volatile Uint32   gpio_in_val_bit20  :1 ;             
	volatile Uint32   gpio_in_val_bit21  :1 ;             
	volatile Uint32   gpio_in_val_bit22  :1 ;             
    volatile Uint32   gpio_in_val_bit23  :1 ;   
	volatile Uint32   gpio_in_val_bit24  :1 ;             
	volatile Uint32   gpio_in_val_bit25  :1 ;             
	volatile Uint32   gpio_in_val_bit26  :1 ;             
	volatile Uint32   gpio_in_val_bit27  :1 ;             
	volatile Uint32   gpio_in_val_bit28  :1 ;             
	volatile Uint32   gpio_in_val_bit29  :1 ;             
	volatile Uint32   gpio_in_val_bit30  :1 ;             
	volatile Uint32   gpio_in_val_bit31  :1 ; 
}GPIO_IN_VALUE_MAP;


/////////////////以下结构体用于从SOC//////////////////////////////////////////////////
 typedef struct
{
///////////////////////addr = 0x0//////////////////////////////////////////    
    volatile Uint32   sarm_bsj:1;            //0x0 output io
    volatile Uint32   reserve_sarm_bjj:1;
    volatile Uint32   core0_reserve:30;
    
///////////////////////addr = 0x1//////////////////////////////////////////    
    volatile Uint32   sbjj:1;
    volatile Uint32   core1_reserve:31;
 
///////////////////////addr = 0x2//////////////////////////////////////////    
    volatile Uint32   bsj_r:1;               //0x1 input io
    volatile Uint32   reserve_mstall_n:1;
    volatile Uint32   reserve_sstall_n:1;
    volatile Uint32   reserve_power_ok:1;
    volatile Uint32   board_id:4;
    volatile Uint32   board_type:4;
    volatile Uint32   qd_r:1;               
    volatile Uint32   reserve_bj_r:1;               
    volatile Uint32   reserve_io2:18;

///////////////////////addr = 0x3~0x4//////////////////////////////////////////    
    volatile Uint32   reserve_u32[2];         
    
///////////////////////addr = 0x5//////////////////////////////////////////    
    volatile Uint32   soc0_irq0_cnt:16 ;            
    volatile Uint32   soc1_irq0_cnt:16 ;        
    
///////////////////////addr = 0x6//////////////////////////////////////////    
    volatile Uint32   soc0_irq1_cnt:16 ;            
    volatile Uint32   soc1_irq1_cnt:16 ;    

    
///////////////////////addr = 0x7~0xd//////////////////////////////////////////    
    volatile Uint32   reserve_u32_2[7];       
    
///////////////////////addr = 0xe//////////////////////////////////////////    
    volatile Uint32   version_date   ;  
    
///////////////////////addr = 0xf//////////////////////////////////////////    
    volatile Uint32   version_tag   ;   

}S_GPIO_REG_MAP;


#endif

