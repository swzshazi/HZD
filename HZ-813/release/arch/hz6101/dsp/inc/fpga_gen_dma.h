#ifndef _FPGA_GEN_DMA_
#define _FPGA_GEN_DMA_


#include "fpga_base.h"

typedef struct
{
    volatile Uint16   set_enable:1;                    
    volatile Uint16   reserve_Uint8_1:7;    
    volatile Uint16   set_frame_en:1;     
    volatile Uint16   set_active_en:1;      
    volatile Uint16   set_ptr_en:1;       
    volatile Uint16   set_rotate_en:1;      
    volatile Uint16   reserve_Uint8_2:4;    
    
    volatile Uint16   set_tx_en:1;                    
    volatile Uint16   set_chan_rst:1;   
    volatile Uint16   reserve_Uint8_3:14;       
      
    volatile Uint16   set_dma_len:11;          
    volatile Uint16   reserve_Uint8_4:5;              
      
    volatile Uint16   reserve_Uint16_1;                     
      
    volatile Uint32    set_dma_base_addr;               
        
    volatile Uint32    set_dma_addr_mask;                 
          
    volatile Uint32    set_dma_frame_offset:14;       
    volatile Uint32    set_dma_max_link_index:18;           
      
    volatile Uint32    set_dma_link_offset;           
        
    volatile Uint32    set_dma_stat_addr;               
    
    volatile Uint32    reserve_Uint32_1;             
    
    volatile Uint16   dma_fifo_status;                
    volatile Uint16   dma_ok_cnt    ;                
    
    volatile Uint16   dma_err_cnt;                  
    volatile Uint16   dma_chan_status;               
      
}DMA_CFG_REG;

typedef struct
{
    volatile Uint16   set_cfg;         

    
    volatile Uint16   set_cmd;          
      
    volatile Uint16   set_para;          
      
    volatile Uint16   reserve_Uint16_1;                  
      
    volatile Uint32    set_dma_base_addr;          
        
    volatile Uint32    set_dma_addr_mask;              
          
    volatile Uint32    set_dma_frame_para;           
      
    volatile Uint32    set_dma_link_offset;          
          
    volatile Uint32    set_dma_stat_addr;             
    
    volatile Uint32    reserve_Uint32_1;             
    
    volatile Uint16   dma_fifo_status;                
    volatile Uint16   dma_ok_cnt    ;               
    
    volatile Uint16   dma_err_cnt;                      
    volatile Uint16   dma_chan_status;                
    volatile Uint32    dma_op_addr;                  
}DMA_CFG_REG_U16;

typedef struct
{
    
    volatile Uint32    rd_index:18;      
    volatile Uint32    reserve_Uint32_1:14; 
        
    volatile Uint32    wr_index:18;     
    volatile Uint32    reserve_Uint32_2:14; 
          
    volatile Uint16   ok_cnt;           
    volatile Uint16   err_cnt;              
              
}DMA_STAT_REG;

typedef struct
{
    volatile Uint32    rd_index;        
    volatile Uint32    wr_index;       
    volatile Uint16    ok_cnt;          
    volatile Uint16    err_cnt;         
}DMA_STAT_REG_U16;

typedef struct
{
    volatile Uint32    rd_index[256];      
}DMA_STAT_WR_BACK_REG_U16;

typedef struct
{
    volatile Uint32    version_date;       
    volatile Uint16    version_tag;        
    volatile Uint16    reserve_Uint16_1;   
    volatile Uint16    pcie_dbg_data[11];  
}DMA_VERSION_REG_U16;


#define DMA_CHAN0_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x0) <<1))
#define DMA_CHAN1_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x20)<<1))
#define DMA_CHAN2_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x40)<<1))
#define DMA_CHAN3_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x60)<<1))
#define DMA_CHAN4_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x80)<<1))
#define DMA_CHAN5_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0xa0)<<1))
#define DMA_CHAN6_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0xc0)<<1))
#define DMA_CHAN7_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0xe0)<<1))

#define DMA_CHAN0_STAT_ADDR  (volatile Uint32 *)(FPGA_GEN_DMA_ADDR + ((0x100)<<1))             
#define DMA_CHAN1_STAT_ADDR  (volatile Uint32 *)(FPGA_GEN_DMA_ADDR + ((0x200)<<1))           
#define DMA_CHAN2_STAT_ADDR  (volatile Uint32 *)(FPGA_GEN_DMA_ADDR + ((0x300)<<1))
#define DMA_CHAN3_STAT_ADDR  (volatile Uint32 *)(FPGA_GEN_DMA_ADDR + ((0x400)<<1))
#define DMA_CHAN4_STAT_ADDR  (volatile Uint32 *)(FPGA_GEN_DMA_ADDR + ((0x500)<<1))
#define DMA_CHAN5_STAT_ADDR  (volatile Uint32 *)(FPGA_GEN_DMA_ADDR + ((0x600)<<1))
#define DMA_CHAN6_STAT_ADDR  (volatile Uint32 *)(FPGA_GEN_DMA_ADDR + ((0x700)<<1))
#define DMA_CHAN7_STAT_ADDR  (volatile Uint32 *)(FPGA_GEN_DMA_ADDR + ((0x800)<<1))


#define DMA_MODULE_VER_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x900)<<1))  


#endif
