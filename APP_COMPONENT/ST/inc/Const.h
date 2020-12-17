#ifndef _Const_
#define _Const_
#include "hzplatform.h"

typedef struct
{
  int32 buf_addr;
  Uint16 current_index;			//下一个要写的地址，此索引的数据不可用
  Uint16 old_index;
} adc_set;

typedef struct
{
  int32 data;
  Uint32 data_q;
} data_set;

#define SAMPLE_RATE 2500//Fosc/SAMPLING_RATE,20000000/8000
#define PERMIT_TIC 10//8k,20000000/8000
#define MAX_FRAME_INDEX 16
#define MAX_FRAME_LINE 15//与MAX_FRAME_INDEX合并
#define CONTIUE_LOST MAX_FRAME_INDEX*SAMPLE_RATE/5000//与MAX_FRAME_INDEX合并
#define FRAME_OFFSET 40       // 40*U32 = 160* Byte
#define FRAME_OFFSET_16 80       // 40*U32 = 160* Byte
#define REAL_FRAME_LEN (21)       // 40*U32 = 160* Byte   
#define MAX_INDEX (REAL_FRAME_LEN-1)       // 40*U32 = 160* Byte
#define ADCHANNEL   24
#define CALBUFFER   128
#define CALRING   127
#define SELCHN      10
#define PeriodNums  24

#define TIME10S 40000
#define HOLDCNT 40
#define COUNTS800   800
#define COUNTS10   10

#define AVGBUFFER 50
#define LEV1_TIME 5000

#define LVL1_FAKE_VAL 5000
#define LVL2_FAKE_VAL 16667
#define LVL1_VAL_BUF  256
#define LVL1_VAL_LINE 255

#ifdef MAIN_DSP
	#define AC_CH_NUM 16
#else
	#define AC_CH_NUM 32
#endif

#define CERTIFICATION_TEST	0		//认证测试的时候才使能

extern void alarmSta(Uint16 cnt,Uint16 pre_cnt,Uint16 *continue_cnt,Uint16 *hold_cnt,Uint8 *alarm,Uint16 continue_lvl,Uint16 hold_lvl);
#endif
