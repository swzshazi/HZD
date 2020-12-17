#include "QD.h"

extern Uint8 readQD();
// Local functions declaration 
int initQD(QD *dp);
void QDCal(QD *dp);
/********************************************************************************
*         Input    : Parent componet, QD name                              *
*         Output   : QD handle                                             *
*         Function : Create the QD                                         *
********************************************************************************/
QD *newQD(Component *parent,const char *name)
{
	Uint16	i=0;
	char	tp_str[150];
    QD *dp;
	
    dp = (QD *)calloc(1,sizeof(QD));
    if (!dp) return NULL;

    dp->parent = (Component *)parent;
    dp->type_name = "QD";
    dp->name = name;
    dp->InitComponent = initQD;
    
    registerComponent((Component *)dp);

    // Define input signals
//	for(i=0; i<QD_NUM; i++)
//	{
//		sprintf(tp_str,"QD1_in%d", T_BIT, LEVEL1,i+1);
//		registerVarIn( (Component*)dp, (void**)&(dp->QD1_in[i]),tp_str);
//	}
//	for(i=0; i<QD_NUM; i++)
//	{
//		sprintf(tp_str,"QD2_in%d", T_BIT, LEVEL1,i+1);
//		registerVarIn( (Component*)dp, (void**)&(dp->QD2_in[i]),tp_str);
//	}
//	for(i=0; i<QD_NUM; i++)
//	{
//		sprintf(tp_str,"QD3_in%d", T_BIT, LEVEL1,i+1);
///		registerVarIn( (Component*)dp, (void**)&(dp->QD3_in[i]),tp_str);
//	}
///	for(i=0; i<QD_NUM; i++)
///	{
//		sprintf(tp_str,"QD4_in%d", T_BIT, LEVEL1,i+1);
//		registerVarIn( (Component*)dp, (void**)&(dp->QD4_in[i]),tp_str);
//	}

	registerVarIn( (Component*)dp, (void**)&(dp->QD1_in[0]), "QD1_in1", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD1_in[1]), "QD1_in2", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD1_in[2]), "QD1_in3", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD1_in[3]), "QD1_in4", T_BIT, LEVEL1);

	registerVarIn( (Component*)dp, (void**)&(dp->QD2_in[0]), "QD2_in1", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD2_in[1]), "QD2_in2", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD2_in[2]), "QD2_in3", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD2_in[3]), "QD2_in4", T_BIT, LEVEL1);

	registerVarIn( (Component*)dp, (void**)&(dp->QD3_in[0]), "QD3_in1", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD3_in[1]), "QD3_in2", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD3_in[2]), "QD3_in3", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD3_in[3]), "QD3_in4", T_BIT, LEVEL1);

	registerVarIn( (Component*)dp, (void**)&(dp->QD4_in[0]), "QD4_in1", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD4_in[1]), "QD4_in2", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD4_in[2]), "QD4_in3", T_BIT, LEVEL1);
	registerVarIn( (Component*)dp, (void**)&(dp->QD4_in[3]), "QD4_in4", T_BIT, LEVEL1);
	
	
	
	registerVarIn( (Component*)dp, (void**)&(dp->QD_ELSE), "QD_ELSE", T_BIT, LEVEL1);
	
	registerVarOut((Component *)dp,(void *)&(dp->QD),"QD", T_BIT, LEVEL2);
	registerVarOut((Component *)dp,(void *)&(dp->QD1),"QD1", T_BIT, LEVEL2);
	registerVarOut((Component *)dp,(void *)&(dp->QD2),"QD2", T_BIT, LEVEL2);
	registerVarOut((Component *)dp,(void *)&(dp->QD3),"QD3", T_BIT, LEVEL2);
	registerVarOut((Component *)dp,(void *)&(dp->QD4),"QD4", T_BIT, LEVEL2);
	
	registerVarOut((Component *)dp,(void *)&(dp->QD_ERR),"QD_ERR", T_BIT, LEVEL2);
	registerVarOut((Component *)dp,(void *)&(dp->CMP_ERR),"CMP_ERR", T_BIT, LEVEL2);
	registerVarOut( (Component*)dp, (void*)&(dp->check_err), "check_err", T_BIT, LEVEL2 );		//指针比较出错


    return (QD *)dp;
}


void QD_check_task(QD *dp)
{
	if(dp->check_err == 0)
	{
		dp->check_err = check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	}
}

/********************************************************************************
*         Input    : QD handle                                            *
*         Output   : None                                                       *
*         Function : Initialize the QD                                    *
********************************************************************************/
int initQD(QD *dp)
{
    if (dp==NULL) return -1;


    // Input variables
    
    // Output variables
	dp->QD = 0;
	dp->QD1 = 0;
	dp->QD2 = 0;
	dp->QD3 = 0;
	dp->QD4 = 0;

	dp->QD_CNT = 0;
	dp->QD_ERR = 0;
	dp->CMP_CNT = 0;
	dp->CMP_ERR = 0;
    // Private variables
	dp->check_err = 0;
	init_check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	
    setTask(2,QDCal,dp);
	setTask(4,QD_check_task, dp);

	return 0;
}


/********************************************************************************
*         Input    : supHtm0 handle                                             *
*         Output   : None                                                       *
*         Function : Run the supHtm0                                            *
********************************************************************************/
void QDCal(QD *dp)
{
	Uint16	i=0;
	Uint8	flag;

	dp->QD = 0;
	dp->QD1 = 0;
	dp->QD2 = 0;
	dp->QD3 = 0;
	dp->QD4 = 0;
	
	
	for(i=0; i<QD_NUM; i++)
	{
		dp->QD1 |= *dp->QD1_in[i];
		dp->QD2 |= *dp->QD2_in[i];
		dp->QD3 |= *dp->QD3_in[i];
		dp->QD4 |= *dp->QD4_in[i];
	}

	dp->QD = dp->QD1|dp->QD2|dp->QD3|dp->QD4;
	
	if(dp->QD)
	{
		setQD();
	}
	else
	{
		clearQD();
	}

	flag = readQD();
	two_signal_cmp(dp->QD, (~flag)&0x01, &dp->QD_ERR, &dp->QD_CNT, lev2_10S);
#ifndef MAIN_DSP
	two_sys_cmp(dp->QD, *dp->QD_ELSE, &dp->CMP_ERR, &dp->CMP_CNT, lev2_10S);
#endif

}



