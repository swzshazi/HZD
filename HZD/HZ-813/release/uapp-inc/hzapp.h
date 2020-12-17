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

// Ӧ�ýӿ�C����
// ��ȡ�����źŵ����ԣ��β�Ϊ�������
extern  Uint8         getInVarShareMode(void *in_var);                                 // ��ȡ���������ͨ�ŷ�ʽ
extern  Uint8         getInVarType(void *in_var);                                      // ��ȡ�������������
extern  Uint32        getInVarUtcSec(void *in_var);                                    // ��ȡ��������仯��utc��
extern  Uint16        getInVarFractSec(void *in_var);                                  // ��ȡ��������仯��С���룬bit0-9Ϊms��bit10-13Ϊ0.1ms��bit14Ϊ������

// ��ȡ����źŵ�����
extern  int           getOutVarType(void *var_addr);                                   // ͨ�����������ַ��ȡ�����������
extern  int           getOutVarTypeByName(char *var_name);                             // ͨ����������̵�ַ��ȡ����������� 
extern  Uint32        getOutVarShmem(void *var_addr, Uint8 manual);                    // ͨ�����������ַ��ȡ�ñ����ڹ����ڴ��еĵ�ַ

// �������������Ʒ�ʶ�ȡ
extern IN_VALUE      *updateVarIn(void *in);                                           // ��ȡ���������ǰֵ�����ڷ�ʵʱ����
extern void           updateVarOut(void *addr);                                        // ���������ǰֵ������������ڷ�ʵʱ����
extern Uint16         getInVarQuality(void *in);                                       // ��ȡ���������Ʒ��
                                                                 
extern SETTING       *getSettingInfoByName(char *var_name);                            // ���ݶ�ֵ����ȡ��ֵ��Ϣgroup��no��section
extern SETTINGRPS    *getSettingGroupInfo(void);                                       // ��ȡ��ֵgroup��Ϣ
extern DESCRIPTION   *getSettingItemDesc(int grp,int section, int no);                 // ���ݶ�ֵ����Ϣ��ȡ��ֵ����
extern VALUE         *getSettingItemValue(int grp,int section, int no);                // ���ݶ�ֵ����Ϣ��ȡ��ֵ
extern VALUE         *setSettingItemValue(int grp,int section,int no, VALUE *value);   // ���ݶ�ֵ����Ϣ���ö�ֵ
extern int            saveSettingValue(int save);                                      // ֪ͨϵͳ���򱣴涨ֵ���β�Ϊ1��
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