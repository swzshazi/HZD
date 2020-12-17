#include "DevAlarm.h"
#include "CommFun.h"
// Local functions declaration 
int initDevAlarm(DevAlarm *dp);
void DevAlarmCal(DevAlarm *dp);
/********************************************************************************
*         Input    : Parent componet, DevAlarm name                              *
*         Output   : DevAlarm handle                                             *
*         Function : Create the DevAlarm                                         *
********************************************************************************/
DevAlarm *newDevAlarm(Component *parent,const char *name)
{
	Uint16	i=0;
	char	tp_str[150];
    DevAlarm *dp;
	
    dp = (DevAlarm *)calloc(1,sizeof(DevAlarm));
    if (!dp) return NULL;

    dp->parent = (Component *)parent;
    dp->type_name = "DevAlarm";
    dp->name = name;
    dp->InitComponent = initDevAlarm;
    
    registerComponent((Component *)dp);

    // Define input signals
    /*
//	for(i=0; i<BJJ_NUM1; i++)
//	{
//		sprintf(tp_str,"bjj%02d_in1", T_BIT, LEVEL1,i+1);
//		registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[i]),tp_str);
//	}
//	for(i=0; i<BJJ_NUM2; i++)
//	{
//		sprintf(tp_str,"bjj%02d_in2", T_BIT, LEVEL1,i+1);
//		registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[i]),tp_str);
//	}
//	for(i=0; i<BJJ_NUM3; i++)
//	{
//		sprintf(tp_str,"bjj%02d_in3", T_BIT, LEVEL1,i+1);
//		registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[i]),tp_str);
//	}
//	for(i=0; i<BSJ_NUM1; i++)
//	{
//		sprintf(tp_str,"bsj%02d_in", T_BIT, LEVEL1,i+1);
//		registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[i]),tp_str);
//	}
	*/
	
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[0]), "bjj1_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[1]), "bjj2_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[2]), "bjj3_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[3]), "bjj4_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[4]), "bjj5_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[5]), "bjj6_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[6]), "bjj7_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[7]), "bjj8_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[8]), "bjj9_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[9]), "bjj10_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[10]), "bjj11_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[11]), "bjj12_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[12]), "bjj13_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[13]), "bjj14_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[14]), "bjj15_in1", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in1[15]), "bjj16_in1", T_BIT, LEVEL1 );
	
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[0]), "bjj1_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[1]), "bjj2_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[2]), "bjj3_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[3]), "bjj4_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[4]), "bjj5_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[5]), "bjj6_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[6]), "bjj7_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[7]), "bjj8_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[8]), "bjj9_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[9]), "bjj10_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[10]), "bjj11_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[11]), "bjj12_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[12]), "bjj13_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[13]), "bjj14_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[14]), "bjj15_in2", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in2[15]), "bjj16_in2", T_BIT, LEVEL1 );
	
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[0]), "bjj1_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[1]), "bjj2_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[2]), "bjj3_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[3]), "bjj4_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[4]), "bjj5_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[5]), "bjj6_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[6]), "bjj7_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[7]), "bjj8_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[8]), "bjj9_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[9]), "bjj10_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[10]), "bjj11_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[11]), "bjj12_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[12]), "bjj13_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[13]), "bjj14_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[14]), "bjj15_in3", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bjj_in3[15]), "bjj16_in3", T_BIT, LEVEL1 );

	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[0]), "bsj1_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[1]), "bsj2_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[2]), "bsj3_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[3]), "bsj4_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[4]), "bsj5_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[5]), "bsj6_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[6]), "bsj7_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[7]), "bsj8_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[8]), "bsj9_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[9]), "bsj10_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[10]), "bsj11_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[11]), "bsj12_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[12]), "bsj13_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[13]), "bsj14_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[14]), "bsj15_in", T_BIT, LEVEL1 );
	registerVarIn( (Component*)dp, (void**)&(dp->bsj_in[15]), "bsj16_in", T_BIT, LEVEL1 );
	
    // Define output signals
	registerVarOut((Component *)dp,(void *)&(dp->bsj_sum),"bsj_sum", T_BIT, LEVEL2);
	registerVarOut((Component *)dp,(void *)&(dp->bjj_sum),"bjj_sum", T_BIT, LEVEL2);
	registerVarOut((Component *)dp,(void *)&(dp->RAM_ERR),"RAM_ERR", T_BIT, LEVEL2);
	registerVarOut((Component *)dp,(void *)&(dp->TWO_SYS_CMP_ERR),"TWO_SYS_CMP_ERR", T_BIT, LEVEL2);

	registerVarOut( (Component*)dp, (void*)&(dp->check_err), "check_err", T_BIT, LEVEL2 );		//指针比较出错

	/////////INIT IN///////////////////////////////////
//	init_pointer(dp->p_start,dp->p_end);
	///////////////////////////////////////////////////

    return (DevAlarm *)dp;
}


void DevAlarm_check_task(DevAlarm *dp)
{
	if(dp->check_err == 0)
	{
		dp->check_err = check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	}
}

/********************************************************************************
*         Input    : DevAlarm handle                                            *
*         Output   : None                                                       *
*         Function : Initialize the DevAlarm                                    *
********************************************************************************/
int initDevAlarm(DevAlarm *dp)
{
    if (dp==NULL) return -1;


    // Input variables
    
    // Output variables
    dp->bsj_sum= 0;
	dp->bjj_sum= 0;
    // Private variables
	dp->check_err = 0;
	init_check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	
    setTask(3,DevAlarmCal,dp);
	setTask(4,DevAlarm_check_task, dp);

	return 0;
}


/********************************************************************************
*         Input    : supHtm0 handle                                             *
*         Output   : None                                                       *
*         Function : Run the supHtm0                                            *
********************************************************************************/
void DevAlarmCal(DevAlarm *dp)
{
	Uint16	i=0;
	Uint8	tmp1=0,tmp2=0,tmp3=0;

	dp->bjj1_sum = 0;
	dp->bjj2_sum = 0;
	dp->bjj3_sum = 0;
	for(i=0; i<BJJ_NUM1; i++)
	{
		tmp1 |= *dp->bjj_in1[i];
	}
	dp->bjj1_sum = tmp1;
	for(i=0; i<BJJ_NUM2; i++)
	{
		tmp2 |= *dp->bjj_in2[i];
	}
	dp->bjj2_sum = tmp2;
	for(i=0; i<BJJ_NUM3; i++)
	{
		tmp3 |= *dp->bjj_in3[i];
	}
	dp->bjj3_sum = tmp3;
	dp->bjj_sum = dp->bjj1_sum | dp->bjj2_sum | dp->bjj3_sum;
	
	tmp1 = 0;
	for(i=0; i<BSJ_NUM1; i++)
	{
		tmp1 |= *dp->bsj_in[i];
	}
	dp->RAM_ERR = RAM_ERR&0x01;
	dp->TWO_SYS_CMP_ERR = TWO_SYS_CMP_ERR&0x01;
	
	dp->bsj_sum = tmp1&0x01;

	if(dp->bjj_sum != 0)
	{
		setBJJ();
	}
	else
	{
		clearBJJ();
	}
	if(dp->bsj_sum != 0)
	{
		setBSJ();
	}
	else
	{
		clearBSJ();
	}
	
}



