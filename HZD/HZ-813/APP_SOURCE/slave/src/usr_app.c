#include "hzplatform.h"
//MU元件头文件
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

//BU元件头文件
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
//外部函数声明
//-------------------------------------------------------------------------
extern int registerToolBoxCmp(const char *, Component*  (*)());

void registerUsrApp(void)
{
    setMmbIntMode(0, 0);			// 两级中断的模式，0代表FPGA中断后定时启动DSP中断，1代表变量推送给DSP完成后即时启动DSP中断
    setMmbIntDelayTime(50, 150);	// 定时中断的延时时间
	
	// 包含平台相关库
	linkLIB(libProcess);
    linkLIB(ToolBox);
	
	// 包含平台相关驱动
	
	// 添加MU符号块，将来应用元件可以封装成库，直接包含库。
/*	registerToolBoxCmp("DataMerge",		(Component* (*)())newDataMerge);
	registerToolBoxCmp("AdcSample",		(Component* (*)())newAdcSample);
	registerToolBoxCmp("AphaseDel",		(Component* (*)())newAphaseDel);
	registerToolBoxCmp("TphaseDel",		(Component* (*)())newTphaseDel);
    registerToolBoxCmp("SmvDeal",		(Component* (*)())newSmvDeal);
	registerToolBoxCmp("DzPosSelect",	(Component* (*)())newDzPosSelect);
	registerToolBoxCmp("CalFreq",		(Component* (*)())newCalFreq);
	registerToolBoxCmp("CalAgl",		(Component* (*)())newCalAgl);
	registerToolBoxCmp("TestBoard",		(Component* (*)())newTestBoard);  */
	
    // 添加MU静态元件
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
	
	// 添加BU符号块，将来应用元件可以封装成库，直接包含库。
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
	
	// 添加应用静态元件
	/*newComponent("TripCmd220",     	"Trip");
	newComponent("CloseCmd220",     "Close");
	newComponent("BreakPosDiff",    "PosDiff");
	newComponent("BlkReClsLog",     "BlkReCls"); */
    
	newComponent("DzCmdMerge",   	"DzCtr");
	newComponent("GLOBAL_VAR",      "GLOB_VAR");
	
}

/* end by hz */
