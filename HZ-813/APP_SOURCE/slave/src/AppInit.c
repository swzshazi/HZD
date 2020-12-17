/* FileName: AppInit.c */

//#include "symbol_type_defines.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
/************************************************************************
*                               宏定义
************************************************************************/
#define SMV_TX_9_2
#define SMV_RX_9_2
#define GOOSE_RX_TX

#define MAX_AUTO_LINK_NUM   (4)

#include "hzplatform.h"

#include "AdcSample.h"
#include "TphaseDel.h"
#include "AphaseDel.h"
#include "ggio_component.h"
#include "gmrp.h"
#include "smv_tx_9_2_component.h"
#include "emac_component.h"
#include "goose_component.h"
#include "ptp_component.h"
#include "Nodestable.h"
#include "dec_9_2_component.h"
#include "SmvDeal.h"
#include "DzPosSelect.h"
#include "CalFreq.h"
#include "CalAgl.h"
#include <stdarg.h>
#include "GLOBAL_VAR.h"


#include "TestBoard.h"
#include "DataMerge.h"

#ifdef PROG_DEBUG
#include "simulator.h"
#endif

#ifdef TEST_GOOSE
#include "test_goose.h"
#endif

#ifdef FILE_INFO
#include "file_info.h"
#endif

#include "InDPosGs.h"
#include "OutDPosGs.h"
#include "BIOGs16.h"
#include "AIOGs8.h"
#include "TripCmd220.h"
#include "CloseCmd220.h"
#include "DzCmd.h"
#include "BreakPosDiff.h"
#include "BlkReClsLog.h"

Uint32 board_type=6101;
Uint32 version=100;
Uint32  GMRP_EN;
AdcSample   *AdcDma;
TphaseDel   *TphaseDelIp;
TphaseDel   *TphaseDelUp;
TphaseDel   *TphaseDelUm;
AphaseDel   *AphaseDelI0;
AphaseDel   *AphaseDelIn;
AphaseDel   *AphaseDelIbak;
AphaseDel   *AphaseDelU0;
EMAC_COMPONENT *emac_component;
GMRP_COMPONENT *GMRPUnit;
GOOSE_COMPONENT *goose;
SMV_TX_9_2_COMPONENT *smv_tx_9_2;
DEC_9_2_COMPONENT *smv_rx_9_2;
SmvDeal *SmvDeal1;
DzPosSelect *DzPosSelect1;
DzPosSelect *DzPosSelect2;
CalFreq *CalFreq1;
CalAgl  *IpAB_phase;
CalAgl  *IpBC_phase;
CalAgl  *IpCA_phase;
CalAgl  *ImAB_phase;
CalAgl  *ImBC_phase;
CalAgl  *ImCA_phase;
CalAgl  *UpAB_phase;
CalAgl  *UpBC_phase;
CalAgl  *UpCA_phase;
CalAgl  *UmAB_phase;
CalAgl  *UmBC_phase;
CalAgl  *UmCA_phase;
CalAgl  *UpIpA_phase;
TestBoard *TestBoard1;
DataMerge *DataMerge1;

GLOBAL_VAR 							*GLOB_VAR			    = NULL;

TripCmd220   *Trip;
CloseCmd220  *Close;
DzCmd        *DzCtr;
BreakPosDiff *PosDiff;
BlkReClsLog  *BlkReCls;

//应用动态元件接口定义
const COMP_INFO app_comp_info[]=
{
    {"InDPos",                  (Component* (*)())newInDPosGs,                      initInDPosGs},
    {"OutDPos",                 (Component* (*)())newOutDPosGs,                     initOutDPosGs},
    {"BIOGs16",                   (Component* (*)())newBIOGs16,                       initBIOGs16},
    {"AIOGs8",                    (Component* (*)())newAIOGs8,                        initAIOGs8},
    {NULL,                        NULL,                                               NULL},
};

INIT_CODE int newComponents()
{
    int ret;
    Uint8 i;
    setMmbIntMode(0, 0);
    setMmbIntDelayTime(50, 150);
    
    DataMerge1 = (DataMerge *)newDataMerge(NULL, "DataMerge1");
    if (NULL == DataMerge1)   {return -1;}
        
    AdcDma = (AdcSample *)newAdcSample(NULL, "AdcDma");
    if (NULL == AdcDma)   {return -1;}
    	
    AphaseDelI0 = (AphaseDel *)newAphaseDel(NULL, "AphaseDelI0");
    if (NULL == AphaseDelI0)   {return -1;}
    	
    AphaseDelIn = (AphaseDel *)newAphaseDel(NULL, "AphaseDelIn");
    if (NULL == AphaseDelIn)   {return -1;}
    
    AphaseDelIbak = (AphaseDel *)newAphaseDel(NULL, "AphaseDelIbak");
    if (NULL == AphaseDelIbak)   {return -1;}
    	
    AphaseDelU0 = (AphaseDel *)newAphaseDel(NULL, "AphaseDelU0");
    if (NULL == AphaseDelU0)   {return -1;}
    	
    TphaseDelIp = (TphaseDel *)newTphaseDel(NULL, "TphaseDelIp");
    if (NULL == TphaseDelIp)   {return -1;}
    	
    TphaseDelUp = (TphaseDel *)newTphaseDel(NULL, "TphaseDelUp");
    if (NULL == TphaseDelUp)   {return -1;}
    
    TphaseDelUm = (TphaseDel *)newTphaseDel(NULL, "TphaseDelUm");
    if (NULL == TphaseDelUm)   {return -1;}

    smv_tx_9_2 = (SMV_TX_9_2_COMPONENT *)new_smv_tx_9_2_component(NULL, "smv_tx_9_2");
    if (NULL == smv_tx_9_2)   {return -1;}
    	
    goose = (GOOSE_COMPONENT *)new_goose_component(NULL, "goose");
    if (NULL == goose)   {return -1;}
    
		GMRPUnit = (GMRP_COMPONENT *)newGmrpComponent(NULL,"GMRPUnit");
		if(NULL == GMRPUnit) 	{return -1;}
	
		emac_component = 
	    (EMAC_COMPONENT*)new_emac_component(NULL,"emac");
    if (NULL == emac_component)
    {
        return -1;
    }
		smv_rx_9_2 = (DEC_9_2_COMPONENT *)new_dec_9_2_component(NULL, "smv_rx_9_2");
    if (NULL == smv_rx_9_2)
    {
        return -1;
    }
		SmvDeal1 = (SmvDeal *)newSmvDeal(NULL, "SmvDeal1");
    if (NULL == SmvDeal1)
    {
        return -1;
    }
    DzPosSelect1 = (DzPosSelect *)newDzPosSelect(NULL, "DzPosSelect1");
    if (NULL == DzPosSelect1)   {return -1;}
    	
    DzPosSelect2 = (DzPosSelect *)newDzPosSelect(NULL, "DzPosSelect2");
    if (NULL == DzPosSelect2)   {return -1;}
    
    CalFreq1 = (CalFreq *)newCalFreq(NULL, "CalFreq1");
    if (NULL == CalFreq1)   {return -1;}
        
    IpAB_phase = (CalAgl *)newCalAgl(NULL, "IpAB_phase");
    if (NULL == IpAB_phase)   {return -1;}
    IpBC_phase = (CalAgl *)newCalAgl(NULL, "IpBC_phase");
    if (NULL == IpBC_phase)   {return -1;}
    IpCA_phase = (CalAgl *)newCalAgl(NULL, "IpCA_phase");
    if (NULL == IpCA_phase)   {return -1;}
    ImAB_phase = (CalAgl *)newCalAgl(NULL, "ImAB_phase");
    if (NULL == ImAB_phase)   {return -1;}
    ImBC_phase = (CalAgl *)newCalAgl(NULL, "ImBC_phase");
    if (NULL == ImBC_phase)   {return -1;}
    ImCA_phase = (CalAgl *)newCalAgl(NULL, "ImCA_phase");
    if (NULL == ImCA_phase)   {return -1;}
    UpAB_phase = (CalAgl *)newCalAgl(NULL, "UpAB_phase");
    if (NULL == UpAB_phase)   {return -1;}
    UpBC_phase = (CalAgl *)newCalAgl(NULL, "UpBC_phase");
    if (NULL == UpBC_phase)   {return -1;}
    UpCA_phase = (CalAgl *)newCalAgl(NULL, "UpCA_phase");
    if (NULL == UpCA_phase)   {return -1;}
    UmAB_phase = (CalAgl *)newCalAgl(NULL, "UmAB_phase");
    if (NULL == UmAB_phase)   {return -1;}
    UmBC_phase = (CalAgl *)newCalAgl(NULL, "UmBC_phase");
    if (NULL == UmBC_phase)   {return -1;}
    UmCA_phase = (CalAgl *)newCalAgl(NULL, "UmCA_phase");
    if (NULL == UmCA_phase)   {return -1;}
    UpIpA_phase = (CalAgl *)newCalAgl(NULL, "UpIpA_phase");
    if (NULL == UpIpA_phase)   {return -1;}
    TestBoard1 = (TestBoard *)newTestBoard(NULL, "TestBoard1");
    if (NULL == TestBoard1)   {return -1;}
   

////////////////////////ST NEW COMPONENT///////////////////////////////////
			
    GLOB_VAR = newGLOBAL_VAR(NULL, "GLOB_VAR");
    if(NULL == GLOB_VAR){return -20;}

    Trip = (TripCmd220 *)newTripCmd220(NULL, "Trip");
    if (NULL == Trip)   {return -22;}
    
    Close = (CloseCmd220 *)newCloseCmd220(NULL, "Close");
    if (NULL == Close)   {return -23;}
    
    DzCtr = (DzCmd *)newDzCmd(NULL, "DzCtr");
    if (NULL == DzCtr)   {return -24;}
    
    PosDiff = (BreakPosDiff *)newBreakPosDiff(NULL, "PosDiff");
    if (NULL == PosDiff)   {return -25;}
    
     BlkReCls = (BlkReClsLog *)newBlkReClsLog(NULL, "BlkReCls");
    if (NULL == BlkReCls)   {return -26;}
   
////////////////////////ST NEW END COMPONENT///////////////////////////////////

/****************AD映射*********************/
//CS1:AD1;CS2:AD2;CS5:AD3;第一路AD
//CS3:AD4;CS4:AD5;CS6:AD6;第二路AD
/****************AD映射*********************/
	
	registerParameter(NULL,(void*)&(GMRP_EN),"GMRP_EN min=0 max=1 default=1 option=1 list=No Yes", T_STR_L);

	return 0;
} 


//应用初始化函数
INIT_CODE int initComponents()
{   
    int ret;
    
    if(init_smv_tx_9_2_component(smv_tx_9_2)<0) return -1;
	if(init_emac_component(emac_component)<0) return -1;
    if(initAdcSample(AdcDma)<0) return -1;
	if(init_dec_9_2_component(smv_rx_9_2)<0) return -1;
    if(initDzPosSelect(DzPosSelect1)<0) return -1;
    if(initDzPosSelect(DzPosSelect2)<0) return -1;
	if(initSmvDeal(SmvDeal1)<0) return -1;
    if(initTphaseDel(TphaseDelIp)<0) return -1;
    if(initTphaseDel(TphaseDelUp)<0) return -1;
    if(initTphaseDel(TphaseDelUm)<0) return -1;
    if(initAphaseDel(AphaseDelI0)<0) return -1;
    if(initAphaseDel(AphaseDelIn)<0) return -1;
    if(initAphaseDel(AphaseDelIbak)<0) return -1;
    if(initAphaseDel(AphaseDelU0)<0) return -1;
    if(initDataMerge(DataMerge1)<0) return -1;
    if(initCalFreq(CalFreq1)<0) return -1;
    if(initCalAgl(IpAB_phase)<0) return -1;
    if(initCalAgl(IpBC_phase)<0) return -1;
    if(initCalAgl(IpCA_phase)<0) return -1;
    if(initCalAgl(ImAB_phase)<0) return -1;
    if(initCalAgl(ImBC_phase)<0) return -1;
    if(initCalAgl(ImCA_phase)<0) return -1;
    if(initCalAgl(UpAB_phase)<0) return -1;
    if(initCalAgl(UpBC_phase)<0) return -1;
    if(initCalAgl(UpCA_phase)<0) return -1;
    if(initCalAgl(UmAB_phase)<0) return -1;
    if(initCalAgl(UmBC_phase)<0) return -1;
    if(initCalAgl(UmCA_phase)<0) return -1;
    if(initCalAgl(UpIpA_phase)<0) return -1;
    if(initTestBoard(TestBoard1)<0) return -1;
    if(GMRP_EN) 
	{
		goose->gmrp = GMRPUnit;
	}
	
    if(init_goose_component(goose)<0) return -1;
		if(initGmrpComponent(GMRPUnit)<0) return -1; 

    if(initTripCmd220(Trip)<0) return -1;
    if(initCloseCmd220(Close)<0) return -1;
	if(initDzCmd(DzCtr)<0) return -1;  
	if(initBreakPosDiff(PosDiff)<0) return -1;   
    if(initBlkReClsLog(BlkReCls)<0) return -1; 
    
////////////////////////ST INIT  COMPONENT///////////////////////////

	if(initGLOBAL_VAR(GLOB_VAR)<0) return -1;
////////////////////////ST INIT END COMPONENT///////////////////////////  
	
	return 0;
}
/* end of file */
