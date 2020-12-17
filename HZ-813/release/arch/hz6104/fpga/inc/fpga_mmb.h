
#ifndef _FPGA_MMB_H_
#define _FPGA_MMB_H_

#include "fpga_base.h"
//-----------------------        MMB module    ------------------------------//


 typedef struct
{
	/*******************  offset addr=0~1  **************************/
    volatile Uint16   set_swn_1;					// 本板第1个节点发送数据在MMB空间中的起始地址
    volatile Uint16   set_swn_2;					// 本板第2个节点发送数据在MMB空间中的起始地址
    
	/*******************  offset addr=2~3  **************************/
    volatile Uint16   set_length_1;			  // 本板第1个节点发送数据长度（U32）
    volatile Uint16   set_length_2;				// 本板第2个节点发送数据长度（U32）

	/*******************  offset addr=4~5  **************************/
    volatile Uint16   set_no_1:8;				  // 本板第1个节点起始节点号
    volatile Uint16   set_no_2:8;			    // 本板第2个节点起始节点号
    volatile Uint16   set_no_num:8;       // 系统总节点数（仅主DSP需要配置）
    volatile Uint16   reserve_Uint8_1:8;  // 保留
    	
	/*******************  offset addr=6~7  **************************/
    volatile Uint16   set_word_num;				// MMB数据总数（U32），在支持选择性接收的场合，此寄存器配置内容为本插件实际需要接收的数据总数
    volatile Uint16   set_irq:4;				  // 中断模式
    volatile Uint16   set_time_sys:1;            // 本板时间体系
    volatile Uint16   set_master:1;			  // MMB主节点配置
    volatile Uint16   set_tx_chc:1;				// 发送写校验
    volatile Uint16   set_rx_chc:1;				// 接收读校验	
    volatile Uint16   reserve_bit_2:8;
    	
	/*******************  offset addr=8~9  **************************/
    volatile Uint16   set_period;				  // MMB周期，50ns为单位，（仅主DSP需要配置）	
    volatile Uint16   reserve_Uint16_1;

	/*******************  offset addr=a~b  **************************/    
    volatile Uint16   set_int_gen;				// 定时延迟产生中断模式下，中断延迟值，50ns为单位
    volatile Uint16   reserve_Uint16_2;

	/*******************  offset addr=c~d  **************************/    
    volatile Uint16   set_enable:1;   		// MMB使能信号
    volatile Uint16   reserve_bit_3:15;        
    volatile Uint16   reserve_Uint16_3;     

	/*******************  offset addr=e~f  **************************/    
    volatile Uint16   set_clr_int:1;			// 清电平中断信号
    volatile Uint16   set_clr_fifo:1;		  // 清MMB-FIFO信号
    volatile Uint16   set_lock_tic:1;		  // 锁存实时时刻
    volatile Uint16   reserve_bit_4:13;
    volatile Uint16   reserve_Uint16_4;     

	/*******************  offset addr=10~11  **************************/    
    volatile Uint16   mmb_rx_cnt_all;			// MMB接收总数据帧数   
    volatile Uint16   mmb_rx_cnt_ok; 			// MMB接收正确数据帧数   
        
	/*******************  offset addr=12~13  **************************/    
    volatile Uint16   mmb_rx_cnt_fail;		// MMB接收错误数据帧数       
    volatile Uint16   mmb_tx_chc_fail;		// MMB发送写校验错误统计         

	/*******************  offset addr=14~15  **************************/    
    volatile Uint16   decode_ram_fail_cnt;		// MMB发送写校验错误统计         
    volatile Uint16   abnormal_int_cnt;		// MMB补中断次数统计         

	/*******************  offset addr=16~17  **************************/    		          
    volatile Uint32    mmb_node_status;		// MMB节点状态 

	/*******************  offset addr=18~19  **************************/    		          
    volatile Uint32    mmb_node_err_code_l;  // MMB节点错误代码1 

	/*******************  offset addr=1a~1b  **************************/    		              
    volatile Uint32    mmb_node_err_code_h;   // MMB节点错误代码2 

	/*******************  offset addr=1c  **************************/    		              
    volatile Uint16    timer_jitter_cnt;   // 时钟系统异常跳变统计 
    
	/*******************  offset addr=1d  **************************/    		              
    volatile Uint16    mmb_duty_time ;     // MMB数据传输时间片     
    
	/*******************  offset addr=1e~1f  **************************/    		                       
    volatile Uint32    reserve_Uint32_f;  	// 保留    
    
	/*******************  offset addr=20~21  **************************/    	
    volatile Uint32    slave_real_time;         // 本板实时时刻
		              
	/*******************  offset addr=22~23  **************************/    		              
    volatile Uint32    slave_mmb_time;         // 本板MMB起始时刻
    
	/*******************  offset addr=24~25  **************************/    		                       
    volatile Uint32    slave_int_time;		   // 本板外部中断起始时刻
    
	/*******************  offset addr=26~27  **************************/    		                       
    volatile Uint32    set_tx1_checksum;	  	// 本板MMB起始时刻
    
	/*******************  offset addr=28~29  **************************/    		                       
    volatile Uint32    set_tx2_checksum;	  	// 本板外部中断起始时刻
    
	/*******************  offset addr=2A~2B  **************************/    		                       
    volatile Uint32    set_max_mmb_cnt;  	// 本板第1个节点发送校验和
    
	/*******************  offset addr=2C~2D  **************************/    		                       
    volatile Uint16   board_id_sel:1;    	// 由CPU配置板卡槽号   
    volatile Uint16   reserve_bit_5:7;        	
    volatile Uint16   cpu_set_id:8;      	// DSP配置板卡槽号内容      
    volatile Uint16   board_id_rd:8;
    volatile Uint16   reserve_bit_6:8;     
    
	/*******************  offset addr=2e~2f  **************************/    		                       
    volatile Uint32    reserve_Uint32_17;  	// 保留    
    
	/*******************  offset addr=30~31  **************************/    		                       
    volatile Uint32   device_id;             //模块版本号
    
	/*******************  offset addr=32~33  **************************/    
    volatile Uint32   mmb_version;           //模块版本号	

}MMB_REG_MAP;


typedef struct
{
 Uint32 mmb_oth_ptr;
 Uint32 mmb_status;
 Uint32 mmb_tic;
 Uint32 mmb_data[10];
 Uint32 mmb_rec[8];
 Uint32 mmb_crc;
 Uint32 mmb_eof;
}MMB_DATA_STR;




#endif




