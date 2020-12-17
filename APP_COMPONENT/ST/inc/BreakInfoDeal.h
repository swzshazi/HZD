/* FileName: BreakInfoDeal.h */
#ifndef _BreakInfoDeal_H
#define _BreakInfoDeal_H


#include "hzmodule.h"
#include "common_types.h"
#include "CommFun.h"
//#include "symbol_type_defines.h"

#define  Pos_NUM           3      // ��·��λ����Ŀ
#define  Group_NUM         4      // ������Ϣ��Ŀ


/* Component struct definition: */
typedef struct
{
	#include "base.h"

	/* input variables :*/
	Uint8	*pFault_GSE[Pos_NUM];     // ��·��ģ�����
	Uint8	*pFault_GSE_ok[Pos_NUM];    
	Uint8	*pAlam_GSE[Pos_NUM];      // ��·��ģ�������쳣�澯
	Uint8	*pAlam_GSE_ok[Pos_NUM]; 
	Uint8	*pSynAlam_GSE[Pos_NUM];      // ��·��ģ���ʱ�쳣�澯
	Uint8	*pSynAlam_GSE_ok[Pos_NUM];
	Uint8	*pOptLoss_GSE[Pos_NUM];      // ��·��ģ�����ʧ��澯
	Uint8	*pOptLoss_GSE_ok[Pos_NUM];
	
	Uint8	*pRepair_GSE[Pos_NUM];    // ��·��ģ�����ѹ��Ͷ��
	Uint8	*pRepair_GSE_ok[Pos_NUM];
	Uint8	*pRepairDiff_GSE[Pos_NUM];    // ��·��ģ����޲�һ��
	Uint8	*pRepairDiff_GSE_ok[Pos_NUM];
	Uint8	*pGsAlam_GSE[Pos_NUM];        // ��·��ģ��GOOSE���ո澯
	Uint8	*pGsAlam_GSE_ok[Pos_NUM];
	Uint8	*pGsDataErr_GSE[Pos_NUM];     // ��·��ģ��GOOSE���������쳣
	Uint8	*pGsDataErr_GSE_ok[Pos_NUM];

	Uint8	*pRevTph_GSE[Pos_NUM];         // ��·��ģ���յ���A/B/C����
	Uint8	*pRevTph_GSE_ok[Pos_NUM];
	Uint8	*pRevCls_GSE[Pos_NUM];         // ��·��ģ���յ���բ����
	Uint8	*pRevCls_GSE_ok[Pos_NUM];

	Uint8	*pTripMon_GSE[Pos_NUM];        // ��·��ģ����բ���ڻز�
	Uint8	*pTripMon_GSE_ok[Pos_NUM];
	Uint8	*pClsMon_GSE[Pos_NUM];        // ��·��ģ���բ���ڻز�
	Uint8	*pClsMon_GSE_ok[Pos_NUM];
	Uint8	*pCurAlam_GSE[Pos_NUM];        // ��·��ģ������բ�����쳣
	Uint8	*pCurAlam_GSE_ok[Pos_NUM];
	
	Uint8	*pOpPwrOff_GSE[Pos_NUM];       // ��·��ģ�������Դ�������
	Uint8	*pOpPwrOff_GSE_ok[Pos_NUM];
	Uint8	*pCtrLoopOff_GSE[Pos_NUM];      // ��·��ģ����ƻ�·����
	Uint8	*pCtrLoopOff_GSE_ok[Pos_NUM];

	Uint8	*pBlkClsIn_GSE[Pos_NUM];        // ��·��ģ��ѹ���ͱ��ؿ���
	Uint8	*pBlkClsIn_GSE_ok[Pos_NUM];
	Uint8	*pHzPressLow_GSE[Pos_NUM];        // ��·��ģ���բѹ����
	Uint8	*pHzPressLow_GSE_ok[Pos_NUM];     
	Uint8	*pTzPressLow_GSE[Pos_NUM];        // ��·��ģ����բѹ����
	Uint8	*pTzPressLow_GSE_ok[Pos_NUM];   
	Uint8	*pOpPressLow_GSE[Pos_NUM];        // ��·��ģ�����ѹ����
	Uint8	*pOpPressLow_GSE_ok[Pos_NUM];   

	float32 *pTzCurMax_GSE[Pos_NUM];        // ��·��ģ����Ȧ���������
	float32 *pTzCurMax_GSE_ok[Pos_NUM];
	float32 *pHzCurMax_GSE[Pos_NUM];        // ��·��ģ���Ȧ���������
	float32 *pHzCurMax_GSE_ok[Pos_NUM];

	/* parameter  */
	
	/* Output variables :  */
	Uint8	Fault[Pos_NUM];        // ��·��ģ�����   
	Uint8	Alam[Pos_NUM];         // ��·��ģ�������쳣�澯
	Uint8	SynAlam[Pos_NUM];      // ��·��ģ���ʱ�쳣�澯
	Uint8	OptLoss[Pos_NUM];      // ��·��ģ�����ʧ��澯
	
	Uint8	Repair[Pos_NUM];        // ��·��ģ�����ѹ��Ͷ��
	Uint8	RepairDiff[Pos_NUM];    // ��·��ģ����޲�һ��
	Uint8	GsAlam[Pos_NUM];        // ��·��ģ��GOOSE���ո澯
	Uint8	GsDataErr[Pos_NUM];     // ��·��ģ��GOOSE���������쳣

	Uint8	RevTph[Pos_NUM];          // ��·��ģ���յ���A/B/C����
	Uint8	RevCls[Pos_NUM];          // ��·��ģ���յ���բ����
	Uint8	TripMon[Pos_NUM];         // ��·��ģ����բ���ڻز�
	Uint8	ClsMon[Pos_NUM];          // ��·��ģ���բ���ڻز�
	Uint8	CurAlam[Pos_NUM];         // ��·��ģ������բ�����쳣
	
	Uint8	OpPwrOff[Group_NUM];      // ��·��ģ�������Դ�������
	Uint8	CtrLoopOff[Group_NUM];    // ��·��ģ����ƻ�·����

	Uint8	BlkClsIn[Group_NUM];      // ��·��ģ��ѹ���ͱ��ؿ���
	Uint8	HzPressLow[Group_NUM];    // ��·��ģ���բѹ����
	Uint8	TzPressLow[Group_NUM];    // ��·��ģ����բѹ����
	Uint8	OpPressLow[Group_NUM];    // ��·��ģ�����ѹ����

	float32 TzCurMax[Pos_NUM];        // ��·��ģ����Ȧ���������
	float32 HzCurMax[Pos_NUM];        // ��·��ģ���Ȧ���������

	//private
	
	
} BreakInfoDeal;


extern  BreakInfoDeal  *newBreakInfoDeal(Component *parent, const char *name);
extern int  initBreakInfoDeal(BreakInfoDeal *dp);

#endif
