#ifndef _GooseClose_H
#define _GooseClose_H

#include "hzplatform.h"

#define	tick_10ms	 	200000
#define	tick_20ms	 	400000
#define	tick_200ms	 	4000000
#define	tick_500ms  	10000000
#define	tick_1000ms  	20000000
#define	tick_10000ms  	200000000


#define lev1_10ms		40
#define lev1_2S			8000	

#define	lev2_2_4ms      3
#define	lev2_20ms		24
#define	lev2_40ms		48
#define	lev2_100ms		120
#define	lev2_250ms		300
#define	lev2_500ms		600
#define	lev2_1S			1200
#define	lev2_5S			6002
#define	lev2_10S		12005
#define	lev2_20S		24010
#define	lev2_1H			4321729




extern Uint32 utc_sec;
extern Uint16 local_ms;

extern Uint32 current_time_lo ; //时间的低32位
extern Uint32 current_time_hi;  //时间的高32位

extern Uint8	TWO_SYS_CMP_ERR;
extern Uint8	RAM_ERR;


extern void initSOE_fun(SOE_VALUE * soe_str, Uint8 value);
extern void SOE_MAKE(SOE_VALUE * soe_str, Uint8 value);
extern Uint8 Dlyon(Uint8 * status, Uint32 * time_save,Uint8 signal_in, Uint32 delay_time);
extern Uint8 CommandContrl(Uint8 * status, Uint32 * time_save,Uint8 command, Uint8 command_type);
extern void init_pointer(Uint32 start, Uint32 end);
extern void init_check_set_pointer(Uint32 start, Uint32 checksum);
extern Uint8 check_set_pointer(Uint32 start, Uint32 checksum);
extern Uint8 GSE_Bool_Q(Uint8 * data_in, Uint8 * date_in_q, Uint8 device_test);
extern Uint8 GSE_Test_Q(Uint8 * data_in, Uint8 * date_in_q, Uint8 device_test);
extern void GOOSE_SOE(SOE_VALUE * command, SOE_VALUE * command_old);
extern void BI_SOE(SOE_VALUE * command, SOE_VALUE * command_old);
extern void GOOSE_LINK_SOE(SOE_VALUE * command, Uint8 *date_in_q, SOE_VALUE* command_old);
extern void two_sys_cmp(Uint8 A_SYS, Uint8 B_SYS, Uint8 * result, Uint16 * CNT, Uint32 window);
extern void get_relay_stat(Uint8 command, Uint8 * SWI, Uint8 * RELAY_STAT);
extern void PULSE_TRIG(Uint8 * signal_now, Uint8 * signal_old, Uint16 * signal_cnt, Uint16 pulse_wide, Uint8 * pulse, Uint8 edge_mode);
extern Uint8 Dly_expand(Uint8 * status, Uint32 * time_save, Uint8 signal_in, Uint32 delay_time, Uint32 expand_time);
#endif
