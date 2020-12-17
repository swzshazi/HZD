/* FileName: SENSOR.h */
#ifndef _SENSOR_H
#define _SENSOR_H


#include "hzmodule.h"
#include "common_types.h"
//#include "symbol_type_defines.h"


#define  DC_LSB   0.00000011921			//2.048v对应的码值是7fffff
//#define  TEST_DEVICE_NO	  3
#define  PARA_START_ADDR    0x1106fc00

/*
typedef struct
{
    signed int      zd;         
    float           gain;
    float           angle_diff;
    float           resis;
}S6101_16chan_para;

typedef struct
{
    signed int      zd;
    float           gain;
}S6101_24chan_para;

typedef struct
{
    unsigned short      version;        
    unsigned short      total_chan;
    S6101_16chan_para   chan_7616[48];
    S6101_24chan_para   chan_1247[4];
    char                save_flag;
    char                align[3];
    unsigned short      check_sum;
}S6101_para;

typedef struct
{
    unsigned short  version;
    unsigned short  save_flag;
    float vol_chan1_table[11];
    float cur_chan1_table[11];
    float vol_chan2_table[11];
    float cur_chan2_table[11];
    unsigned char   vol_pga;
    unsigned char   cur_pga;
    unsigned short  check_sum;
}S6101_1247_para;

typedef struct
{
    S6101_para      AD7616_para;
    S6101_1247_para AD1247_para;
}S6101_AD_para;

*/


/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint32 	start;
	
	int32	*ch1_data_in;
	int32	*ch2_data_in;
	int16	*temperature;
	float32	*TQ1_C_in;
	float32	*TQ2_C_in;
	float32	*HQ_C_in;

	/*  parameter   */
	float32	ch1_min;
	float32	ch1_max;
	float32	ch2_min;
	float32	ch2_max;
	Uint32  dc1_type;
	Uint32  dc2_type;

	Uint32  checksum;
	Uint8	check_err;



	/* output variables :*/
	Uint8   test_mode;
	Uint8   para_save_flag;
	Uint8	para_err;
	float32	TQ1_C;
	float32	TQ2_C;
	float32	HQ_C;
	float32	ch1_data;
	float32	ch2_data;
	float32	ch1_data_bak;
	float32	ch2_data_bak;

	//private
	float32 ch1_data_min;
	float32 ch2_data_min;
	float32 ch1_data_max;
	float32 ch2_data_max;
	float32 DC1_TALBE[4][11];
	float32 DC2_TALBE[4][11];
} SENSOR;


extern  SENSOR  *newSENSOR(Component *parent, const char *name);
extern int  initSENSOR(SENSOR *dp);

#endif
