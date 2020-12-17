/*
  sfp.h
*/

//////*****************include******************//////
#ifndef _SFP_H_
#define _SFP_H_

#include "hzplatform.h"
#include "hzmodule.h"
#include "fpga_sfp.h"
//////*****************define******************//////

#define   SFP_NUM    14

typedef struct
{
  Uint16  id[8];
  int16   temp;
  Uint16  vcc;
  Uint16  tx_bias;
  Uint16  tx_pow;
  Uint16  rx_pow;
  Uint16  ext_info1;
  Uint16  ext_info2;
  Uint16  resv;
}SFP_MODULES;

typedef struct
{
  Uint16  cfg_reg;
  Uint16  address_ex;
  Uint16  sfp_no_ack;
  Uint16  resv;
  Uint16  back[10]; 
  Uint16  version_date;
  Uint16  version_year;
}SFP_CTRL;

typedef struct
{  
  SFP_MODULES  sfp_modules[SFP_NUM];
}SFP_MODULE;
 

typedef struct
{ 
  #include "base.h"
  int16 * temp;
 
  Uint16 sfp_link_state;  
  Uint16 cfg_reg;

  float32	deubg_f;

  float32  p_tx_max[SFP_NUM];
  float32  p_rx_max[SFP_NUM];
  float32  p_temp_max[SFP_NUM];
  float32  p_tx_min[SFP_NUM];
  float32  p_rx_min[SFP_NUM];
  float32  p_temp_min[SFP_NUM];

  
  volatile SFP_CTRL   *sfp_ctrl;
  volatile SFP_MODULE *sfp_module;


  float32	VCC500;
  float32	dev_temp;
  
  float32  p_tx_tmp[SFP_NUM];
  float32  p_rx_tmp[SFP_NUM];
  float32  p_temp_tmp[SFP_NUM];

  float32  p_tx[SFP_NUM];
  float32  p_rx[SFP_NUM];
  float32  p_temp[SFP_NUM];

} SFP;  


extern SFP *newSFP(Component *Parent,const char *Name);  
extern int initSFP(SFP *dp);  

  
#endif



