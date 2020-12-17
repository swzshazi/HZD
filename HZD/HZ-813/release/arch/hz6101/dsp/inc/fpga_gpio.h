

#ifndef _FPGA_GPIO_H_
#define _FPGA_GPIO_H_

#include "fpga_base.h"


typedef struct  //Ö÷CPU
{
////////////addr=0////////////////
	Uint16 can_rst:1;
	Uint16 cfg_reg0:15;

////////////addr=1////////////////
	Uint16 gpio_out_en:1;
	Uint16 cfg_reg1:15;	

////////////addr=2////////////////
	Uint16 cfg_reg2;	
	
////////////addr=3////////////////
	Uint16 bus_io_rd;	
	
////////////addr=4////////////////
	Uint16 sys_bs_n_rd:1;	
	Uint16 sys_bj_n_rd:1;	
	Uint16 sys_qd_n_rd:1;	
	Uint16 sys_stall_n_rd:1;	
	Uint16 cfg_reg4:12;	

////////////addr=5////////////////
	Uint16 board_id;	
	
////////////addr=6////////////////
	Uint16 pll_locked_status;	

////////////addr=0x7~0xb////////////////
	Uint16 reserve[5];	
	
////////////addr=0xc////////////////
	Uint16 version_date;	

////////////addr=0xd////////////////
	Uint16 version_year;	

////////////addr=0xe////////////////
	Uint16 master_slave_tag;	
	
}FPGA_GPIO;   



#endif  

