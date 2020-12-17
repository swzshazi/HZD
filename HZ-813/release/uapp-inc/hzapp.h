#ifndef _HZAPI_H
#define _HZAPI_H

#ifdef __cplusplus
extern "C" {
#endif

#include  "hzplatform.h"
#include  "database.h"
#include  "hzdevice.h"
#include  "nvshmem.h"
#include  "fd.h"

#define 	ERROR_PID      -1
#define 	ZERO_PID        0
#define 	HOST_PID 		1
#define 	DBB_PID 		2

enum 	LANGUAGE_TYPE 	{CHINESE,ENGLISH,RUSSIAN,FRENCH,SPANISH};

typedef struct
{
    IN_VALUE  value;
    Uint32    dword[4];
}IN_VALUE_MEM;

typedef struct
{
	int		  num;
	char      **item_ptr;
	char	  item[1][REF_STRING_LEN];
}REFPARAMETER;

extern Uint32          current_mmb_tics;
extern int             mmb1_fd;
extern int             mmb2_fd;

// 应用接口C函数
// 获取输入信号的属性，形参为输入变量
extern  Uint8         getInVarShareMode(void *in_var);                                 // 获取输入变量的通信方式
extern  Uint8         getInVarType(void *in_var);                                      // 获取输入变量的类型
extern  Uint32        getInVarUtcSec(void *in_var);                                    // 获取输入变量变化的utc秒
extern  Uint16        getInVarFractSec(void *in_var);                                  // 获取输入变量变化的小数秒，bit0-9为ms，bit10-13为0.1ms，bit14为闰秒标记

// 获取输出信号的属性
extern  int           getOutVarType(void *var_addr);                                   // 通过输出变量地址获取输出变量类型
extern  int           getOutVarTypeByName(char *var_name);                             // 通过输出变量短地址获取输出变量类型 
extern  Uint32        getOutVarShmem(void *var_addr, Uint8 manual);                    // 通过输出变量地址获取该变量在共享内存中的地址

// 输入输出变量及品质读取
extern IN_VALUE      *updateVarIn(void *in);                                           // 读取输入变量当前值，用于非实时进程
extern void           updateVarOut(void *addr);                                        // 输出变量当前值立即输出，用于非实时进程
extern Uint16         getInVarQuality(void *in);                                       // 读取输入变量的品质
                                                                 
extern SETTING       *getSettingInfoByName(char *var_name);                            // 根据定值名获取定值信息group、no、section
extern SETTINGRPS    *getSettingGroupInfo(void);                                       // 获取定值group信息
extern DESCRIPTION   *getSettingItemDesc(int grp,int section, int no);                 // 根据定值组信息获取定值描述
extern VALUE         *getSettingItemValue(int grp,int section, int no);                // 根据定值组信息获取定值
extern VALUE         *setSettingItemValue(int grp,int section,int no, VALUE *value);   // 根据定值组信息设置定值
extern int            saveSettingValue(int save);                                      // 通知系统程序保存定值，形参为1。
extern int            setSettingSectionNo(int ld,int new_section);
extern LIST_ITEM     *getSettingItemList(int list_no);
extern double        *getSettingItemValuePtr(int grp,int section,int no);
extern VALUE_NODE    *getSettingItemValueNode(int grp,int no);
extern ITEM          *getSettingItemByName(char *name);

extern char          *getConfigArgs(void);
extern int            newThread(unsigned char policy,int priority,void *thread_func,void *param);
extern int            linkRecordVarlInWithPtr(Component *self, void **in, char *ext_var_name);
extern int 			  addVarInCallback(void *in,void (*)(void *,void *,int),void *,int);

#ifdef __cplusplus
}
#endif
#endif