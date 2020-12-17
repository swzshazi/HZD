#ifndef _FPGA_ADC_REG_H_
#define _FPGA_ADC_REG_H_

#include "fpga_base.h"

/***********************************************************************************
*                                   ADC define
***********************************************************************************/

#define ADC_MODULE_BASE_ADDR          (FPGA_ADC7606_ADDR) 




#define ADC_FILTER_GRP1_PARA_REG      (ADC_MODULE_BASE_ADDR + (0x000<<1))  	
#define ADC_FILTER_GRP2_PARA_REG      (ADC_MODULE_BASE_ADDR + (0x010<<1))  	    
#define ADC_FILTER_GRP3_PARA_REG      (ADC_MODULE_BASE_ADDR + (0x020<<1))      
#define ADC_FILTER_GRP4_PARA_REG      (ADC_MODULE_BASE_ADDR + (0x030<<1))  


typedef struct 
{
    volatile Uint16   cfg_adc_filter_para_set[16];		
 
}ADC_FILTER_REG_SET;   


   


#define ADC_CFG_REG                   (ADC_MODULE_BASE_ADDR + (0x040<<1))   
	
#define ADC_CHIP1_CFG_REG	          (ADC_MODULE_BASE_ADDR + (0x080<<1))  
#define ADC_CHIP2_CFG_REG	          (ADC_MODULE_BASE_ADDR + (0x082<<1))  
#define ADC_CHIP3_CFG_REG	          (ADC_MODULE_BASE_ADDR + (0x084<<1))  
#define ADC_CHIP4_CFG_REG	          (ADC_MODULE_BASE_ADDR + (0x086<<1))  

#define p_adc7616_chip1_cfg	(volatile Uint16 *)(ADC_CHIP1_CFG_REG)
#define p_adc7616_chip2_cfg	(volatile Uint16 *)(ADC_CHIP2_CFG_REG)
#define p_adc7616_chip3_cfg	(volatile Uint16 *)(ADC_CHIP3_CFG_REG)
#define p_adc7616_chip4_cfg	(volatile Uint16 *)(ADC_CHIP4_CFG_REG)


typedef struct 
{
    volatile Uint16   cfg_rst:1;				 
    volatile Uint16   cfg_enable:1;				 
    volatile Uint16   reserve_0:6;				
    volatile Uint16   cfg_src_sel:8;			
    	
    volatile Uint16   cfg_period;			   
    
    volatile Uint16   cfg_bypass_offset_para:1;	                
    volatile Uint16   cfg_bypass_qualtity_chc:1;	            
    volatile Uint16   cfg_bypass_bignum_chc:1;	                
    volatile Uint16   cfg_bypass_filter:1;	                   
    volatile Uint16   cfg_bypass_reserve:12;	                  
       
    volatile Uint16   cfg_debug;	                   
   
    volatile Uint16   cfg_qualtity_cool_limit;	    
    volatile Uint16   cfg_bignum_cool_limit;	    
    
    volatile Uint16   cfg_reserve_Uint16_2[2];	 
   
    volatile Uint16   cfg_bignum_grp1_para1;	
    volatile Uint16   cfg_bignum_grp1_para2;	
    volatile Uint16   cfg_bignum_grp2_para1;	
    volatile Uint16   cfg_bignum_grp2_para2;	
    volatile Uint16   cfg_bignum_grp3_para1;	
    volatile Uint16   cfg_bignum_grp3_para2;	
    volatile Uint16   cfg_bignum_grp4_para1;	
    volatile Uint16   cfg_bignum_grp4_para2;	

}ADC_CFG_REG_SET;



#define ADC_MODULE_VERSION_ADDR       (ADC_MODULE_BASE_ADDR + (0x050<<1))    

typedef struct 
{
    volatile Uint32   adc_module_version_date;			    
    volatile Uint16   adc_module_version_tag;		       
 
}ADC_VERSION_REG_SET;
   	
 	


#define ADC_CHIP_1_ADDR               (ADC_MODULE_BASE_ADDR + (0x200<<1))  
#define ADC_CHIP_2_ADDR               (ADC_MODULE_BASE_ADDR + (0x400<<1))      
#define ADC_CHIP_3_ADDR               (ADC_MODULE_BASE_ADDR + (0x600<<1))    
#define ADC_CHIP_4_ADDR               (ADC_MODULE_BASE_ADDR + (0x800<<1)) 
#define ADC_CHIP_5_ADDR               (ADC_MODULE_BASE_ADDR + (0xa00<<1))
#define ADC_CHIP_6_ADDR               (ADC_MODULE_BASE_ADDR + (0xc00<<1))

typedef struct 
{
    volatile Uint16   para_offset;				      
    volatile Uint16   pare_mult;		              
    volatile Uint16   stat_qualtity_cool_limit;       	
    volatile Uint16   stat_qualtity_cnt;		      
    volatile Uint16   stat_bignum_cool_limit;	      	
    volatile Uint16   stat_bignum_cnt;	             
    volatile Uint16   para_bignum_set_num;	         
    volatile Uint16   reserver_Uint16_1;	        
    
    volatile Uint16   stat_adc_wr_prt;	             
    volatile Uint16   reserver_Uint16_2;	        
    volatile Uint16   para_filter_set_num;	       
    volatile Uint16   reserver_Uint16_3;	       
    volatile Uint16   reserver_Uint16_4[4];	      
    
    volatile Uint32   data_sample_1;	        
    volatile Uint32   data_sample_2;	        
    volatile Uint32   data_sample_3;	       
    volatile Uint32   reserver_Uint32[5];	    
    
}ADC_CHIP_REG_SET;



#endif 

