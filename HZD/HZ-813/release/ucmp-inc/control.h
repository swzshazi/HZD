#ifndef _HZ_CONTROL_H
#define _HZ_CONTROL_H
#include "hzplatform.h"
#ifdef __cplusplus
extern "C" {
#endif

#define IEC103_ID      		1          //103规约ID
#define IEC104_ID      		2          //104规约ID
#define IEC61850_ID    		3          //61850规约ID
#define MMI_ID         		4          //LCD规约ID

#define VALID_DEF           1
#define TEST_DEF            2
#define LINK_OK_DEF         4
#define STRAP_ENA_DEF       8
#define SYNC_ERR_DEF        16
#define SOURCE_DEF          32
#define INACCURATE_DEF      64
#define INCONSIST_DEF       128
#define OLDDATA_DEF         256
#define FAILURE_DEF         512
#define OSCILLATORY_DEF     1024
#define BADREFER_DEF        2048
#define OUTOFRANGE_DEF      4096
#define OVERFLOW_DEF        8192
#define VALID2_DEF          16384
#define OPBLOCKED_DEF       32768

#define SELECT                	1
#define OPERATE               	2
#define CANCEL                	3

#define CONTROL_OPEN           	1
#define CONTROL_CLOSE          	2
#define CONTROL_STOP           	3
#define CONTROL_SETVALUE       	4

#define CONTROL_ST_REQYK1      	1
#define CONTROL_ST_REQYT1      	2


#define VERIFY_NONE            	0
#define VERIFY_SYNC            	1
#define VERIFY_NOVOLT          	2
#define VERIFY_LOOP            	3 
#define VERIFY_LINE            	4
#define VERIFY_AUTO            	5
#define VERIFY_SYNC_NOVOL      	6

#define LOCAL_MONITOR_POS       0       //本地监控
#define REMOTE_MONITOR_POS      1       //远方监控
#define AUTO_POS                2         
#define LOCAL_POS               3       //本地控制

#define USE_PROCESS_VALUE             0 
#define USE_SUBSTITUTE_VALUE          1
#define CANCEL_ALL_SUBSTITUTE_VALUE   2

#define YK_VERIFY_WORD   0xD2A3BFD8
#define YT_VERIFY_WORD   0xD2A3B5F7

#if CPU_TYPE == LINUX_INSTALLED
typedef struct
{
    Uint16 console_id;              	//后台ID
    Uint32 link_in;                 	//遥控遥调对象返回数据结构首地址
    Uint8  prtcl_id;                	//规约进程
    Uint8  cmd_type;                	//命令类型 1=SELECT（选择） 2=OPERATE（操作） 3=CANCEL（取消）
    Uint8  cmd_content;             	//命令值   1=OPEN 			2=CLOSE 		  3=STOP 			4=SETVALUE
    Uint8  ctrl_location;           	//控制位置 0=LOCAL_MONITOR_POS(本地监控),1=REMOTE_MONITOR_POS(远方监控),2=AUTO,3=LOCAL_POS(就地)
    float  ctrl_value;              	//遥调操作设置值
}ORDER_OUT;

typedef struct              
{
    Uint8 update_id;        
    Uint8 cmd_type;             		//命令类型 1=SELECT 2=OPERATE 3=CANCEL
    Uint8 op_result;            		//操作结果 255表示成功
    Uint8 error_index;         			//错误表索引
    Uint32 error_info;         			//错误（或不满足）原因具体信息
}ORDER_RETURN;

typedef struct
{
    Uint16 dtg_addr;         			//报文缓存指针
    Uint16 curr_num;         			//当前报文数目
    Uint16 max_num;          			//最大可记录数目
    Uint16 dtg_no;           			//报文序号
} CONTROL_HEADER;

typedef struct 
{
    struct timeval dtg_time;   			//报文时间信息
    Uint16 dtg_item_no;        			//报文对应序号
    Uint16 item_index;
    Uint16 console_id;       
    Uint8  prtcl_id;          
    Uint8  ctrl_location;         
    Uint8  ykyt_no;           
    Uint8  cmd_type;          
    Uint8  cmd_content;             
    Uint8  op_result;         
    float  ctrl_value;       
} CONTROL_CONTENT;

//HOST事件数据结构
typedef struct
{
    CONTROL_HEADER  header;
    CONTROL_CONTENT content[1];   
} CONTROL_FILE;

//python接口C库，遥控遥调管理部分
//sendControlOrder为非实时任务使用  
extern int sendControlOrder(const char *name, const ORDER_OUT *out, Uint8 order_type, void (*pfunc)(void *), void *args);
#endif

//sendTkAck、sendYtAck、handleYkYt为DSP使用接口
extern void sendDigitalAck(Uint8 ,Uint8 ,Uint8 ,Uint8 ,Uint8 ,Uint32 );
extern void sendAnalogAck(Uint8 ,Uint8 ,Uint8 ,Uint8 ,Uint8 ,Uint32 );
extern void handleYkYt(char *, int );

#ifdef __cplusplus
}
#endif

#endif
