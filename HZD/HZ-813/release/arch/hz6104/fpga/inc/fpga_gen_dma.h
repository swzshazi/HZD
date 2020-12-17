#ifndef _FPGA_GEN_DMA_
#define _FPGA_GEN_DMA_

//--------------------------------------------------------------------------//
// Header files                                                             //
//--------------------------------------------------------------------------//
#include "fpga_base.h"

typedef struct
{
    volatile Uint32   set_enable:1;						// 0x0
    volatile Uint32   reserve_Uint8_1:7;		
    volatile Uint32   set_frame_en:1;			
    volatile Uint32   set_active_en:1;			
    volatile Uint32   set_ptr_en:1;				
    volatile Uint32   set_rotate_en:1;			
    volatile Uint32   reserve_Uint8_2:4;		
    volatile Uint32   set_tx_en:1;				    		 
    volatile Uint32   set_chan_rst:1;		
    volatile Uint32   reserve_Uint8_3:14;		    
    	
    volatile Uint32   set_dma_len:11;				    // 0x1	
    volatile Uint32   reserve_Uint8_4:5;	                	
    volatile Uint32   reserve_Uint16:16;	                	    	
    	
    volatile Uint32    set_dma_base_addr;	            // 0x2		
        
    volatile Uint32    set_dma_addr_mask;	            // 0x3			  
          
    volatile Uint32    set_dma_frame_offset:14;	        // 0x4	
    volatile Uint32    set_dma_max_link_index:18;          	
    	
    volatile Uint32    set_dma_link_offset;	 			// 0x5  
        
    volatile Uint32    set_dma_stat_addr;	            // 0x6	   
    
    volatile Uint32    reserve_Uint32_1;	            // 0x7	   
    
    volatile Uint32   dma_fifo_status:16;	            // 0x8
    volatile Uint32   dma_ok_cnt:16    ;	               
    
    volatile Uint32   dma_err_cnt:16;	                    // 0x9	   
    volatile Uint32   dma_chan_status:16;	                  

    volatile Uint32   dma_real_ptr;	                  
    
}DMA_CFG_REG;

typedef struct
{
    volatile Uint16   set_cfg;						// 0x0

    
    volatile Uint16   set_cmd;				   // 0x1	 
    	
    volatile Uint16   set_para;				    // 0x2	
    	
    volatile Uint16   reserve_Uint16_1;	              // 0x3		    	
    	
    volatile Uint32    set_dma_base_addr;	            // 0x4~0x5		
        
    volatile Uint32    set_dma_addr_mask;	            // 0x6~0x7			  
          
    volatile Uint32    set_dma_frame_para;	          // 0x8~0x9	
    	
    volatile Uint32    set_dma_link_offset;	 		     	// 0xa~0xb	  
          
    volatile Uint32    set_dma_stat_addr;	            // 0xc~0xd	   
    
    volatile Uint32    reserve_Uint32_1;	             // 0xe~0xf	   
    
    volatile Uint16   dma_fifo_status;	              // 0x10	   
    volatile Uint16   dma_ok_cnt    ;	                // 0x11	   
    
    volatile Uint16   dma_err_cnt;	                    // 0x12		   
    volatile Uint16   dma_chan_status;	                // 0x13	   
    	
}DMA_CFG_REG_U16;

typedef struct
{
   	
    volatile Uint32    rd_index:18;				// 0x1~0x1
    volatile Uint32    reserve_Uint32_1:14;	
        
    volatile Uint32    wr_index:18;				// 0x2~0x3
    volatile Uint32    reserve_Uint32_2:14;	
          
    volatile Uint16   ok_cnt;			        // 0x4
    volatile Uint16   err_cnt;	                // 0x5
            	
}DMA_STAT_REG;

typedef struct
{
    volatile Uint32    rd_index;				// 0x1~0x1  
    volatile Uint32    wr_index;				// 0x2~0x3
    volatile Uint16    ok_cnt:16;			      // 0x4
    volatile Uint16    err_cnt:16;	        // 0x5
}DMA_STAT_REG_U16;

typedef struct
{
    volatile Uint32    rd_index[256];				// 0x0~0x3FF  
}DMA_STAT_WR_BACK_REG_U16;

typedef struct
{
    volatile Uint32    version_date;				// 0x0~0x1  
    volatile Uint16    version_tag;				  // 0x2
    volatile Uint16    reserve_Uint16_1;		// 0x3
    volatile Uint16    pcie_dbg_data[11];	  // 0x6~0xe
}DMA_VERSION_REG_U16;


#define DMA_CHAN0_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x0) <<2))
#define DMA_CHAN1_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x10)<<2))
#define DMA_CHAN2_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x20)<<2))
#define DMA_CHAN3_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x30)<<2))
#define DMA_CHAN4_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x40)<<2))
#define DMA_CHAN5_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x50)<<2))
#define DMA_CHAN6_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x60)<<2))
#define DMA_CHAN7_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x70)<<2))
#define DMA_CHAN8_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x80)<<2))
#define DMA_CHAN9_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x90)<<2))
#define DMA_CHAN10_CFG_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0xa0)<<2))

#define DMA_CHAN0_STAT_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x1000)<<1))
#define DMA_CHAN1_STAT_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x1800)<<1))
#define DMA_CHAN2_STAT_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x2000)<<1))
#define DMA_CHAN3_STAT_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x2800)<<1))
#define DMA_CHAN4_STAT_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x3000)<<1))
#define DMA_CHAN5_STAT_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x3800)<<1))
#define DMA_CHAN6_STAT_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x4000)<<1))
#define DMA_CHAN7_STAT_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x4800)<<1))
#define DMA_CHAN8_STAT_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x5000)<<1))
#define DMA_CHAN9_STAT_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x5800)<<1))
#define DMA_CHAN10_STAT_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x6000)<<1))

#define DMA_MODULE_VER_ADDR  (volatile Uint16 *)(FPGA_GEN_DMA_ADDR + ((0x100)<<1))	


#endif
