/************************************************************************
* ��Ȩ���� (C)2006, 
*

* ����ժҪ���Ĵ�������
* ����˵����
* ��ǰ�汾��1.00
* ������ڣ�
*
* �޸ļ�¼1��
*   �޸����ڣ�2010-05-10
*   �� �� �ţ�1.00
*   �޸����ݣ�����
************************************************************************/

#ifndef _FPGA_TX_CHC_REG_H_
#define _FPGA_TX_CHC_REG_H_

#include "fpga_base.h"

/***********************************************************************************
*                                   ADC define
***********************************************************************************/



   
typedef struct 
{
    volatile Uint16   set_enable;
    volatile Uint16   set_max_index ;			
    volatile Uint16   reserve_2[2] ;			
    volatile Uint16   chc_cnt ;			
    volatile Uint16   chc_ok_cnt ;			
    volatile Uint16   chc_err_cnt ;	 
}TX_CHC_REG_SET;   

typedef struct 
{
    volatile Uint8 mask_ram[2048]	;		
 
}TX_CHC_MASK_SET;   
   
typedef struct 
{
    volatile Uint16 tx_a_ram[2048]	;		
    volatile Uint16 tx_b_ram[2048]	;		
	
}TX_RAM_SET;  


#endif 

