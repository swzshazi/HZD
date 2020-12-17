/* FileName: CloseCmd220.h */
#ifndef _CloseCmd220_H
#define _CloseCmd220_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"
//#include "symbol_type_defines.h"

#define  ReClose_NUM   4      // �����غ�բ��Ŀ
#define  YK_Close_NUM  4      // ң�϶�·����Ŀ

/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint32 	start;
	Uint8	*pElecTest;                    // �������
	Uint8	*pTest;                        // ����״̬
	Uint8	*pProBd;                       // ��������ѹ��
	Uint8	*pConBd;                       // ���Ƴ���ѹ��
	Uint8	*pLocalConBd;                  // �͵ؿ��ư���
		

	Uint8	*pRECLS_GSE[ReClose_NUM];      // �����غ�բֵ
	Uint8	*pRECLS_GSE_ok[ReClose_NUM];   // �����غ�բƷ��

	Uint8	*pCBYH_GSE[YK_Close_NUM];      // ң�϶�·��
	Uint8	*pCBYH_GSE_ok[YK_Close_NUM];

	Uint8 	*pBSysSH_GSE;                  // ����B���ֺ�
	Uint8 	*pBSysSH_GSE_ok;               

	Uint8 	*pSH_OPT;                      // �ֺϿ���
	Uint8 	*pSTJ;                         // STJ����

	Uint8	*pTestCLS_GSE;                 // �����Ǳ����غ�բֵ
	Uint8	*pTestCLS_GSE_ok;              // �����Ǳ����غ�բƷ��

	Uint8	*pTestCBYH_GSE;                // ������ң�϶�·��ֵ
	Uint8	*pTestCBYH_GSE_ok;             // ������ң�϶�·��Ʒ��
	
	Uint8	*pHZ_ELSE;                      // ��һCPU��բ

	Uint32	checksum;
	Uint8	check_err;

	/* parameter  */
	
	/* output variables :*/
	SOE_VALUE	RECLS_E[ReClose_NUM];     // �����غ�բSOE
	SOE_VALUE	CBYH_E[YK_Close_NUM];     // ң�غ�բSOE
	
	SOE_VALUE	TestCLS_E;                // �����Ǳ����غ�բSOE
	SOE_VALUE	TestCBYH_E;                // ������ң�ض�·��SOE
	
	SOE_VALUE	BSysSH_E;                 // B���ֺ�SOE
	
	Uint8	HZ_LONGTIME;                  // ��բ��ʱ�䶯��

	Uint8   QD;

	Uint8	RECLS_Op;                     // ������բ������
	Uint8	RECLS_Out;                    // ������բ���
	Uint8	CBYH_Op;                      // ��غ�բ������
	Uint8	CBYH_Out;                     // ��غ�բ���
	
	Uint8   SH_Else;                      // �ֺ����--����һ��
	Uint8   SHJ;                          // SHJ�ź�--A��B���ֺ�չ��

	Uint8   SH_Flag;                      // �ֺϱ�־
	Uint8   ST_Flag;                      // ������־
	Uint8   KKJ;                          // KKJ�Ϻ�
	
	Uint8	HZ_Op;                       // ��բ����
	Uint8	HZ_Out;                       // ��բ���-�϶�·��ģ��

	Uint8	RECLS_GSE;                    // Goose�����غ�բ�����
	Uint8	CBYH_GSE;                     // Goose��غ�բ�����

	Uint8	CMP_ERR;
	Uint8 	HA_RELAY_DZ;			//��բ�ӵ㶯��
	Uint8 	HB_RELAY_DZ;			//��բ�ӵ㶯��
	Uint8 	HC_RELAY_DZ;			//��բ�ӵ㶯��
	

	//private
	Uint8	RECLS[ReClose_NUM];         // �غ�բ�������
	Uint8   CBYH[YK_Close_NUM];         // ң�ϴ������
	
	Uint8   SH_OPT;						// �ֺϴ�����
	Uint8   SH_Out;						// �ֺ����
	Uint8   BSysSH;						// B���ֺϴ������
	Uint8   SHJ_Old;                    // A��B���ֺ�
	Uint8   SHJ_New;                    // A��B���ֺ�
	Uint16	SHJ_CNT;                    // SHJ����

	Uint8	TestCLS;                    // �����Ǳ����غ�բ�������
	Uint8	TestCBYH;                   // ������ң�϶�·��������� 

	Uint16  CMP_CNT;
	
	Uint32 	time_save1;
	Uint8  	status1;
	
} CloseCmd220;


extern  CloseCmd220  *newCloseCmd220(Component *parent, const char *name);
extern int  initCloseCmd220(CloseCmd220 *dp);

#endif
