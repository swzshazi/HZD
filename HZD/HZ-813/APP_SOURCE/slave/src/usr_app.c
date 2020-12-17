#include "hzplatform.h"
//MUԪ��ͷ�ļ�
/*#include "AdcSample.h"
#include "TphaseDel.h"
#include "AphaseDel.h"
#include "SmvDeal.h"
#include "DzPosSelect.h"
#include "CompTwoAD.h"
#include "CalFreq.h"
#include "CalAgl.h"
#include "DataMerge.h"
#include "VolMonitor.h"
#include "TestBoard.h" */

//BUԪ��ͷ�ļ�
/*#include "OutDPosGs.h"
#include "TripCmd220.h"
#include "CloseCmd220.h"
#include "BreakPosDiff.h"
#include "BlkReClsLog.h"
#include "BreakInfoDeal.h" */

#include "DevAlarm.h"
#include "GLOBAL_VAR.h"
#include "BIOGs16.h"


#include "CableInput.h"
#include "Simulate.h"
#include "DualSysPos.h"
#include "SwPos.h"
#include "DzCmdMerge.h"
#include "ElecLock.h"


Uint32 board_type=6101;
Uint32 version=100;

//-------------------------------------------------------------------------
//�ⲿ��������
//-------------------------------------------------------------------------
extern int registerToolBoxCmp(const char *, Component*  (*)());

void registerUsrApp(void)
{
    setMmbIntMode(0, 0);			// �����жϵ�ģʽ��0����FPGA�жϺ�ʱ����DSP�жϣ�1����������͸�DSP��ɺ�ʱ����DSP�ж�
    setMmbIntDelayTime(50, 150);	// ��ʱ�жϵ���ʱʱ��
	
	// ����ƽ̨��ؿ�
	linkLIB(libProcess);
    linkLIB(ToolBox);
	
	// ����ƽ̨�������
	
	// ���MU���ſ飬����Ӧ��Ԫ�����Է�װ�ɿ⣬ֱ�Ӱ����⡣
/*	registerToolBoxCmp("DataMerge",		(Component* (*)())newDataMerge);
	registerToolBoxCmp("AdcSample",		(Component* (*)())newAdcSample);
	registerToolBoxCmp("AphaseDel",		(Component* (*)())newAphaseDel);
	registerToolBoxCmp("TphaseDel",		(Component* (*)())newTphaseDel);
    registerToolBoxCmp("SmvDeal",		(Component* (*)())newSmvDeal);
	registerToolBoxCmp("DzPosSelect",	(Component* (*)())newDzPosSelect);
	registerToolBoxCmp("CalFreq",		(Component* (*)())newCalFreq);
	registerToolBoxCmp("CalAgl",		(Component* (*)())newCalAgl);
	registerToolBoxCmp("TestBoard",		(Component* (*)())newTestBoard);  */
	
    // ���MU��̬Ԫ��
	/*newComponent("DataMerge", 	 "DataMerge1");
	newComponent("AdcSample", 	 "AdcDma");

	newComponent("AphaseDel", 	 "AphaseDelI0");
	newComponent("AphaseDel", 	 "AphaseDelIn");
	newComponent("AphaseDel", 	 "AphaseDelIbak");
	newComponent("AphaseDel", 	 "AphaseDelU0");
	newComponent("TphaseDel", 	 "TphaseDelIp");
	newComponent("TphaseDel", 	 "TphaseDelUp");
	newComponent("TphaseDel", 	 "TphaseDelUm");

	newComponent("SmvDeal", 	 "SmvDeal1");
	newComponent("DzPosSelect",  "DzPosSelect1");
	newComponent("DzPosSelect",  "DzPosSelect2");

	newComponent("CalFreq",  	 "CalFreq1");
	newComponent("CalAgl",  	 "IpAB_phase");
	newComponent("CalAgl",  	 "IpBC_phase");
	newComponent("CalAgl",  	 "IpCA_phase");
	newComponent("CalAgl",  	 "ImAB_phase");
	newComponent("CalAgl",  	 "ImBC_phase");
	newComponent("CalAgl",  	 "ImCA_phase");
	newComponent("CalAgl",  	 "UpAB_phase");
	newComponent("CalAgl",  	 "UpBC_phase");
	newComponent("CalAgl",  	 "UpCA_phase");
	newComponent("CalAgl",  	 "UmAB_phase");
	newComponent("CalAgl",  	 "UmBC_phase");
	newComponent("CalAgl",  	 "UmCA_phase");
	newComponent("CalAgl",  	 "UpIpA_phase");

	newComponent("TestBoard",  	 "TestBoard1"); */
	
	// ���BU���ſ飬����Ӧ��Ԫ�����Է�װ�ɿ⣬ֱ�Ӱ����⡣
	/*registerToolBoxCmp("TripCmd220",	    (Component* (*)())newTripCmd220);
	registerToolBoxCmp("CloseCmd220",   	(Component* (*)())newCloseCmd220);
	registerToolBoxCmp("OutDPosGs",	    	(Component* (*)())newOutDPosGs);
	registerToolBoxCmp("BreakPosDiff",		(Component* (*)())newBreakPosDiff);
	registerToolBoxCmp("BlkReClsLog",		(Component* (*)())newBlkReClsLog); */

	registerToolBoxCmp("GLOBAL_VAR",		(Component* (*)())newGLOBAL_VAR);
	
	registerToolBoxCmp("CableInput",		(Component* (*)())newCableInput);
	registerToolBoxCmp("Simulate",			(Component* (*)())newSimulate);
	registerToolBoxCmp("DualSysPos",		(Component* (*)())newDualSysPos);
	registerToolBoxCmp("SwPos",				(Component* (*)())newSwPos);
	registerToolBoxCmp("DzCmdMerge",	    (Component* (*)())newDzCmdMerge);
	registerToolBoxCmp("ElecLock",	    	(Component* (*)())newElecLock);
	
	// ���Ӧ�þ�̬Ԫ��
	/*newComponent("TripCmd220",     	"Trip");
	newComponent("CloseCmd220",     "Close");
	newComponent("BreakPosDiff",    "PosDiff");
	newComponent("BlkReClsLog",     "BlkReCls"); */
    
	newComponent("DzCmdMerge",   	"DzCtr");
	newComponent("GLOBAL_VAR",      "GLOB_VAR");
	
}

/* end by hz */
