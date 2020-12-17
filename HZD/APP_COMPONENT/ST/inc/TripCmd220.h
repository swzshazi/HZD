/* FileName: TripCmd220.h */
#ifndef _TripCmd220_H
#define _TripCmd220_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"


#define  OpS_Num    3     // ����������Ŀ
#define  TJQ_Num    3     // TJQ������Ŀ--���غ���ʧ��
#define  TJR_Num    10    // TJR������Ŀ--���غ���ʧ��
#define  Reset_Num  2     // ������Ŀ

#define  YK_Open_NUM  4     // ң�ֶ�·����Ŀ

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

	SOE_VALUE	*pReset_OPT;               // ���鿪��
	Uint8	    *pReset_GSE[Reset_Num];    // Զ������
	Uint8	    *pReset_GSE_ok[Reset_Num];    

	Uint8	*pTA_GSE[OpS_Num];             // ������Aֵ
	Uint8	*pTA_GSE_ok[OpS_Num];          // ������AƷ��
	
	Uint8	*pTB_GSE[OpS_Num];             // ������Bֵ
	Uint8	*pTB_GSE_ok[OpS_Num];          // ������BƷ��

	Uint8	*pTC_GSE[OpS_Num];             // ������Cֵ
	Uint8	*pTC_GSE_ok[OpS_Num];          // ������CƷ��

	Uint8	*pTJQ_GSE[TJQ_Num];             // ����TJQ��ֵ
	Uint8	*pTJQ_GSE_ok[TJQ_Num];          // ����TJQ��Ʒ��

	Uint8	*pTJR_GSE[TJR_Num];             // ����TJR��ֵ
	Uint8	*pTJR_GSE_ok[TJR_Num];          // ����TJR��Ʒ��

	Uint8 	*pTJF_OPT;                      // �ǵ�������TJF����
	Uint8	*pTJR_OPT;                      // ��������TJR����

	Uint8 	*pBreakPh;                      // �����ȫ�ౣ��

	Uint8	*pCBYF_GSE[YK_Open_NUM];        // ң�ֶ�·��
	Uint8	*pCBYF_GSE_ok[YK_Open_NUM];
	
	Uint8 	*pBSysST_GSE;                   // ����B������
	Uint8 	*pBSysST_GSE_ok;               
	
	Uint8 	*pST_OPT;                       // ��������

	Uint8	*pTestTA_GSE;                   // �����Ǳ�����Aֵ
	Uint8	*pTestTA_GSE_ok;                // �����Ǳ�����AƷ��

	Uint8	*pTestTB_GSE;                   // �����Ǳ�����Bֵ
	Uint8	*pTestTB_GSE_ok;                // �����Ǳ�����BƷ��

	Uint8	*pTestTC_GSE;                   // �����Ǳ�����Cֵ
	Uint8	*pTestTC_GSE_ok;                // �����Ǳ�����CƷ��

	Uint8	*pTestTJQ_GSE;                  // �����Ǳ���TJQ��բֵ
	Uint8	*pTestTJQ_GSE_ok;               // �����Ǳ���TJQ��բƷ��

	Uint8	*pTestTJR_GSE;                  // �����Ǳ���TJR��բֵ
	Uint8	*pTestTJR_GSE_ok;               // �����Ǳ���TJR��բƷ��
	
	Uint8	*pTestCBYF_GSE;                 // ������ң����բֵ
	Uint8	*pTestCBYF_GSE_ok;              // ������ң����բƷ��

	Uint8	*pTestReset_GSE;                 // �����Ǹ���
	Uint8	*pTestReset_GSE_ok;              // �����Ǹ���Ʒ��
	
	Uint8	*pTZ_ELSE;                      // ��һCPU��բ

	Uint8	*pCBBLK1_GSE;                   // ��·�������1
	Uint8	*pCBBLK1_GSE_ok;                // ��·�������1Ʒ��
	
	Uint8	*pCBBLK2_GSE;                   // ��·�������2	
	Uint8	*pCBBLK2_GSE_ok;                // ��·�������2Ʒ��
	
	Uint8	*pTestCBBLK_GSE;                // �����Ƕ�·�������ֵ	
	Uint8	*pTestCBBLK_GSE_ok;             // �����Ƕ�·�������Ʒ��

	Uint8	*pCBBLK_ELSE;                   // ��һCPU�����

	Uint32  checksum;
	Uint8	check_err;

	/* output variables :*/
	Uint8	ResetCmd;      //��������

	SOE_VALUE	Reset_E[Reset_Num];         // ���� SOE

	SOE_VALUE	TA_E[OpS_Num];              // ��A SOE
	SOE_VALUE	TB_E[OpS_Num];              // ��B SOE
	SOE_VALUE	TC_E[OpS_Num];              // ��C SOE
	
	SOE_VALUE	TJQ_E[TJQ_Num];             // TJQ SOE
	SOE_VALUE	TJR_E[TJR_Num];             // TJR SOE

	SOE_VALUE	CBYF_E[YK_Open_NUM];        // ң�ط�բSOE
	
	SOE_VALUE	TestReset_E;                  // �����Ǹ��� SOE

	SOE_VALUE	TestTA_E;                   // ��������A SOE
	SOE_VALUE	TestTB_E;                   // ��������B SOE
	SOE_VALUE	TestTC_E;                   // ��������C SOE

	SOE_VALUE	TestTJQ_E;                  // ������TJQ SOE
	SOE_VALUE	TestTJR_E;                  // ������TJR SOE
	
	SOE_VALUE	TestCBYF_E;                 // ������ң�ط�բ SOE

	Uint8	TZ_LONGTIME;                    // ��բ��ʱ�䶯��

	SOE_VALUE	CBBLK1_E;                   // ��·�������1 SOE
	SOE_VALUE	CBBLK2_E;                   // ��·�������2 SOE
	SOE_VALUE	TestCBBLK_E;                // ��·�������ǽ���� SOE
	
	SOE_VALUE	BSysST_E;                    // B������SOE
	

	Uint8   QD;                             // ����
	Uint8	TJQ_Op;                         // TJQ���
	Uint8	TJR_Op;                         // TJR���
	Uint8	TJR_OPT;					    // ����TJR��բ
	Uint8	TJF_OPT;                        // ����TJF��բ   
	
	Uint8	TA_Op;                          // ����TA����
	Uint8	TB_Op;                          // ����TB����
	Uint8	TC_Op;                          // ����TC����

	Uint8	ProTA_Out;                      // ����TA���
	Uint8	ProTB_Out;                      // ����TB���
	Uint8	ProTC_Out;                      // ����TC���

	Uint8   ST_Else;                        // �������--����һ��
	Uint8	STJ;                            // STJ�ź�

	Uint8	TA_Out;                         // TA���-����·��ģ��
	Uint8	TB_Out;                         // TB���-����·��ģ��
	Uint8	TC_Out;                         // TC���-����·��ģ��
	
	Uint8	TZ_Op;                          // ��һ��բ����
	Uint8	TZ_Out;                         // ��һ��բ���
	
	Uint8  	CBYF_Op;                        // ң�ִ�����
	Uint8  	CBYF_Out;                       // ң�ִ������
	Uint8	CBBLK_Op;                       // ��·����������

	Uint8	TZ_GSE;				    	    // Goose������բ�����
	Uint8	TA_GSE;                         // Goose��A�����
	Uint8	TB_GSE;                         // Goose��B�����
	Uint8	TC_GSE;                         // Goose��C�����
	Uint8	CBYF_GSE;                       // Goose�����բ�����
	Uint8	CBBLK_GSE;                      // Goose��·������������
	Uint8	RESET_GSE;                      // Goose���������
	
	Uint8	CMP_ERR;                        // ˫CPU�Ƚϳ���
	
	//private
	Uint8	Reset[Reset_Num];               // ���鴦�����
	
	Uint8	TA[OpS_Num];              		// TA�������
	Uint8	TB[OpS_Num];                    // TB�������
	Uint8	TC[OpS_Num];                    // TC�������
	
	Uint8	TJQ[TJQ_Num];                   // TJQ�������
	Uint8	TJR[TJR_Num];                   // TJR�������
	
	Uint8  	CBYF[YK_Open_NUM];              // ң�����
	
	Uint8	CBBLK1;                         // ��·�������1���
	Uint8	CBBLK2;                         // ��·�������2���

	Uint8   TestReset;                      // �����Ǹ��鴦�����
	Uint8   TestTA;                         // ������TA�������
	Uint8   TestTB;                         // ������TB�������
	Uint8   TestTC;                         // ������TC�������
	Uint8   TestTJQ;                        // ������TJQ�������
	Uint8   TestTJR;                        // ������TJR�������

	Uint8 	ST_OPT;                         // ����������
	Uint8 	ST_Out;                         // �����������
	Uint8   BSysST;						    // B�������������
	Uint8   STJ_Old;                        // A��B���ֺ�
	Uint8   STJ_New;                        // A��B���ֺ�
	Uint16	STJ_CNT;                        // SHJ����
	
	Uint8   TestCBYF;                       // ������ң�ִ������ 
	
	Uint8   TestCBBLK;                      // �����ǽ�����������
	
	Uint16  CMP_CNT1;                        // �Ƚϼ���1
	Uint16  CMP_CNT2;                        // �Ƚϼ���2
	
	Uint32 	time_save1;
	Uint8  	status1;
	
} TripCmd220;


extern  TripCmd220  *newTripCmd220(Component *parent, const char *name);
extern int  initTripCmd220(TripCmd220 *dp);

#endif
