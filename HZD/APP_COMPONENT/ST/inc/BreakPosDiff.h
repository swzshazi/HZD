/* FileName: BreakPosDiff.h */
#ifndef _BreakPosDiff_H
#define _BreakPosDiff_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"
//#include "symbol_type_defines.h"

#define  Pos_NUM           3        // ��·��λ����Ŀ

#define  Dis_Value          0x1     // ˫λ�÷�λֵ
#define  Cls_Value          0x2     // ˫λ�ú�λֵ

/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint32 	start;

	Uint8	*pHwj[Pos_NUM];                // ��·����λ
	Uint8	*pTwj[Pos_NUM];                // ��·����λ
	Uint8	*pKKJ;                         // KKJ�Ϻ�
	
	Uint8	*pBreakPh_ELSE;                // ��һCPU��ȫ��

	Uint32	checksum;
	Uint8	check_err;

	/* parameter  */
	float32 PosDiff_Delay;                 // λ�ò�һ����ʱʱ��
	Uint32  PosDiff_Num;                   // ��ʱת�������
	
	float32 BreakPh_Delay;                 // ��ȫ�ౣ����ʱʱ��
	Uint32  BreakPh_Num;                   // ��ʱת�������

	float32 FaultTotal_Delay;              // �¹�����ʱʱ��
	Uint32  FaultTotal_Num;                // ��ʱת�������
	
	/* output variables :*/
	Uint8   BreakPosDiff;                  // ��·��λ�ò�һ��
	Uint8   BreakPhPro;                    // ��·����ȫ�ౣ��
	
	Uint8   FaultTotal;                    // �¹���

	Uint8	CMP_ERR;                        // ˫CPU�Ƚϳ���

	//private
	Uint16  CMP_CNT;
	
	Uint8   ret1;                          // ��ʱ����1
	Uint8   AnyDis;                        // ��һ���λ
	Uint8   AnyCls;                        // ��һ���λ

	Uint8   PosRet[Pos_NUM];               // ��ʱλ��ֵ
	Uint8   DisRet[Pos_NUM];			   // ��ʱ��λֵ
	Uint8   ClsRet[Pos_NUM];			   // ��ʱ��λֵ
	Uint8   ret2;                          // ��ʱ����2
	
	Uint32 	time_save1;
	Uint8  	status1;

	Uint32 	time_save2;
	Uint8  	status2;

	Uint32 	time_save3;
	Uint8  	status3;

	Uint8   ret3;                          // ��ʱ����2
	Uint32 	time_save4;
	Uint8  	status4;
	
} BreakPosDiff;


extern  BreakPosDiff  *newBreakPosDiff(Component *parent, const char *name);
extern int  initBreakPosDiff(BreakPosDiff *dp);

#endif
