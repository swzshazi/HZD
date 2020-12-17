#ifndef   __HZPLATFORM_H
#define   __HZPLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif	

#ifndef CPU_TYPE_MACRO
#define CPU_TYPE_MACRO
#define	LINUX_INSTALLED	    0
#define	PIC33	            1
#define	C674X	            2
#endif

#define	NAME_STRING_LEN	    50
#define	REF_STRING_LEN	    80	

#include <stdio.h>
#include <stdlib.h>
#include "common_types.h"
#include "board.h"
#include "hzmodule.h"

#include "scheduler.h"
#include "control.h"
#include "var.h"

//    	时间变量
extern  Uint32          local_s;		// 当前秒
extern 	Uint16          local_ms;		// 当前毫秒
extern  Uint8           local_fms;		// 当前0.1ms
extern  Uint32          local_us;       // 当前微秒
extern  Uint32          utc_sec;        // 世纪秒

//		系统变量
extern  Uint8			DYNAMIC_LEVEL;	
extern 	Uint8 			init_state;
extern  char           *default_value;	
extern 	Uint8  			this_core;
extern 	Uint8 			host_core;

//		普通变量
typedef union
{
	Uint8   c_value;
	Uint16  i_value;
	Uint32  l_value;
	float   f_value;
}IN_VALUE;

//		时间变量
typedef struct
{
	Uint32 s;
	Uint16 ms:10;
	Uint16 fms:4;
	Uint16 leap:1;
}TIME;

//		SOE变量
typedef struct
{
    IN_VALUE value;
	TIME     time;
}SOE_VALUE;

extern  int             waitNewOrder(void);
extern  int             waitInitOrder(int);
extern  int             waitRunOrder(int);

extern  void 			registerUsrApp(void);
extern   int 			registerToolBoxCmp(const char *name, Component*  (*)());
extern 	 int 			newComponent(const char *type_name, const char *inst_name);

#ifdef __cplusplus
}
#endif

#endif

