/* FileName: BlkReClsLog.h */
#ifndef _BlkReClsLog_H
#define _BlkReClsLog_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"
//#include "symbol_type_defines.h"

#define  BlkReCls_NUM  3      // ���������غ�բ��Ŀ

/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint8	*pElecTest;                       // �������
	Uint8	*pTest;                           // ����״̬		

	Uint8	*pBlkReCLS_GSE[BlkReCls_NUM];     // GOOSE�����غ�բֵ
	Uint8	*pBlkReCLS_GSE_ok[BlkReCls_NUM];  // GOOSE�����غ�բƷ��

	Uint8	*pTestBlkReCLS_GSE;               // ������GOOSE�����غ�բֵ
	Uint8	*pTestBlkReCLS_GSE_ok;            // ������GOOSE�����غ�բƷ��

	Uint8	*pCBYF;                           // ң�ֶ�·��
	Uint8	*pCBYH;                           // ң�϶�·��

	Uint8 	*pSH_OPT;                         // �ֺϿ���
	Uint8 	*pST_OPT;                         // ��������
	Uint8 	*pTJR_OPT;                        // TJR����
	Uint8 	*pTJF_OPT;                        // TJF����
	
	Uint8 	*pGS_TJR;                         // GOOSE TJR

	Uint8 	*pBSysBlkReCls_GSE;               // ������һ�ױ���
	Uint8 	*pBSysBlkReCls_GSE_ok;               

	/* parameter  */
	
	/* output variables :*/
	SOE_VALUE	BlkReCLS_E[BlkReCls_NUM];     // GOOSE�����غ�բSOE
	SOE_VALUE	TestBlkReCLS_E;               // ������GOOSE�����غ�բSOE
	SOE_VALUE	BSysBlkReCls_E;               // B�ױ����غ�բSOE

	Uint8   BlkReCls_Out; 	                  // ���������غ�բ
	Uint8   BlkReCls_Bsys; 	                  // ������һ���غ�բ

	//private
	Uint8	GsBlkReCLS[BlkReCls_NUM];         // GOOSE�����غ�բ
	Uint8	BlkReCLS_Op;
	Uint8	TestBlkReCLS;                     // �����Ǳ����غ�բ
	Uint8   SH_OPT;                           // �ֺϿ���
	Uint8   ST_OPT;                           // ��������
	Uint8	BSysBlkReCls;					  // B�ױ����غ�բ

	Uint8 	PWRUP;                            // װ���ϵ�
	Uint16	PWRUP_CNT;                        // װ���ϵ�ʱ�����
	
} BlkReClsLog;


extern  BlkReClsLog  *newBlkReClsLog(Component *parent, const char *name);
extern int  initBlkReClsLog(BlkReClsLog *dp);

#endif
