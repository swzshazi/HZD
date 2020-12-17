/* FileName: SENSOR.c */

#include <stdlib.h>
#include "hzplatform.h"
#include "Board.h"

#include "SENSOR.h"
#include "CommFun.h"
#include "math.h"

S6101_AD_para* analog_para = (S6101_AD_para*)PARA_START_ADDR;
void SENSOR_task( SENSOR *dp);

int initSENSOR( SENSOR *dp);

const static float32 DC1_TALBE[4][11]=
{
 {0.0,		0.5,		1.0,		1.5,		2.0,		2.5,		3.0,		3.5,		4.0,		4.5,		5.0},		//0~5V
 {0.012743,	0.089909,	0.167089,	0.244265,	0.321447,	0.398656,	0.475859,	0.553039,	0.630257,	0.707473,	0.784665},
 {0.0,		2.0,		4.0,		6.0,		8.0,		10.0,		12.0,		14.0,		16.0,		18.0,		20.0},		//4~20mA
 {0.000831,	0.096396,	0.191979,	0.287548,	0.383141,	0.478736,	0.574335,	0.669913,	0.765516,	0.861136,	0.956731}
};

const static float32 DC2_TALBE[4][11]=
{
 {0.0,		0.5,		1.0,		1.5,		2.0,		2.5,		3.0,		3.5,		4.0,		4.5,		5.0},		//0~5V
 {0.017991,	0.095069,	0.172145,	0.249196,	0.326235,	0.403326,	0.480423,	0.557471,	0.634521,	0.711568,	0.788643},
 {0.0,		2.0,		4.0,		6.0,		8.0,		10.0,		12.0,		14.0,		16.0,		18.0,		20.0},		//4~20mA
 {0.000872,	0.096734,	0.192112,	0.287513,	0.382889,	0.478281,	0.573663,	0.669046,	0.764455,	0.859855,	0.955255}
};



SENSOR *newSENSOR(Component *parent, const char *name)
{
	SENSOR *dp;
	
	dp = (SENSOR*)calloc(1, sizeof( SENSOR ));
	
	if( !dp )
	{
	  return NULL;
	}

	dp->type_name = "SENSOR";
	dp->parent = parent;
	dp->name = name;
	dp->InitComponent = (void *)initSENSOR;

	registerComponent( (Component*)dp);


	registerVarIn( (Component*)dp, (void**)&(dp->ch1_data_in), "ch1_data_in", T_INT32, LEVEL1);		//模拟量输入1
	registerVarIn( (Component*)dp, (void**)&(dp->ch2_data_in), "ch2_data_in", T_INT32, LEVEL1);		//模拟量输入2
	registerVarIn( (Component*)dp, (void**)&(dp->TQ1_C_in), "TQ1_C_in", T_FLOAT, LEVEL2 );		
	registerVarIn( (Component*)dp, (void**)&(dp->TQ2_C_in), "TQ2_C_in", T_FLOAT, LEVEL2 );		
	registerVarIn( (Component*)dp, (void**)&(dp->HQ_C_in), "HQ_C_in", T_FLOAT, LEVEL2 );		
	registerVarIn( (Component*)dp, (void**)&(dp->temperature), "temperature", T_INT16,LEVEL2 );
//////////////////////////////////////////////////////////////////////////////////////////////////////
	registerVarOut( (Component*)dp, (void*)&(dp->test_mode),  "test_mode", T_BIT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->para_err),  "para_err", T_BIT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->ch1_data),  "ch1_data", T_FLOAT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->ch2_data),  "ch2_data", T_FLOAT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->ch1_data_bak),  "ch1_data:0.2:0.02", T_FLOAT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->ch2_data_bak),  "ch2_data:0.2:0.02", T_FLOAT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->TQ1_C),  "TQ1_C", T_FLOAT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->TQ2_C),  "TQ2_C", T_FLOAT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->HQ_C),   "HQ_C", T_FLOAT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->ch1_data_min),  "ch1_data_min", T_FLOAT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->ch2_data_min),  "ch2_data_min", T_FLOAT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->ch1_data_max),  "ch1_data_max", T_FLOAT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->ch2_data_max),  "ch2_data_max", T_FLOAT, LEVEL2 );
	registerVarOut( (Component*)dp, (void*)&(dp->para_save_flag),  "para_save_flag", T_BIT, LEVEL2 );
	
//////////////////////////////////////////////////////////////////////////////////////////////////////
	registerParameter((Component *)dp,(void *)&(dp->ch1_min),"ch1_min min=-10000.0 max=10000.0 default=0.0 option=1", T_FLOAT);
	registerParameter((Component *)dp,(void *)&(dp->ch1_max),"ch1_max min=-10000.0 max=10000.0 default=0.0 option=1", T_FLOAT);
	registerParameter((Component *)dp,(void *)&(dp->ch2_min),"ch2_min min=-10000.0 max=10000.0 default=0.0 option=1", T_FLOAT);
	registerParameter((Component *)dp,(void *)&(dp->ch2_max),"ch2_max min=-10000.0 max=10000.0 default=0.0 option=1", T_FLOAT);
	registerParameter((Component *)dp,(void *)&(dp->dc1_type) ,"dc1_type  default=0 option=1 list=4~20mA 0~5V", T_STR_L);
	registerParameter((Component *)dp,(void *)&(dp->dc2_type) ,"dc2_type  default=0 option=1 list=4~20mA 0~5V", T_STR_L);


	registerVarOut( (Component*)dp, (void*)&(dp->check_err), "check_err", T_BIT, LEVEL2 );		//指针比较出错

	return dp;
}

void SENSOR_check_task(SENSOR *dp)
{
	if(dp->check_err == 0)
	{
		dp->check_err = check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
	}
}


INIT_CODE
void getADS1247ParaFromEeprom(SENSOR *dp)
{
    Uint16 i,j;
	Uint16	check_sum;
	
	dp->para_save_flag = analog_para->AD1247_para.save_flag;				//看看是否有系数存储
	if(analog_para->AD1247_para.save_flag == 1)
	{
		unsigned char *tmp = (unsigned char *)(&analog_para->AD1247_para.version);
	    for(i=0;i<182;i++)
	    {
	        check_sum += tmp[i];
	    }
		if(analog_para->AD1247_para.check_sum != check_sum)
		{
			dp->para_err = 1;
		}
	    
		
	    for(i=0;i<11;i++)
	    {
	        dp->DC1_TALBE[0][i] = 0.0 + 0.5*i;
	        dp->DC1_TALBE[1][i] = analog_para->AD1247_para.vol_chan1_table[i];
	    }
	    for(i=0;i<11;i++)
	    {
	        dp->DC1_TALBE[2][i] = 0.0 + 2.0*i;
	        dp->DC1_TALBE[3][i] = analog_para->AD1247_para.cur_chan1_table[i];
	    }
	    for(i=0;i<11;i++)
	    {
	        dp->DC2_TALBE[0][i] = 0.0 + 0.5*i;
	        dp->DC2_TALBE[1][i] = analog_para->AD1247_para.vol_chan2_table[i];
	    }
	    for(i=0;i<11;i++)
	    {
	        dp->DC2_TALBE[2][i] = 0.0 + 2.0*i;
	        dp->DC2_TALBE[3][i] = analog_para->AD1247_para.cur_chan2_table[i];
	    }
	}
	else
	{
		for(i=0;i<11;i++)
		{
			for(j=0;j<4;j++)
			{
				dp->DC1_TALBE[j][i] = DC1_TALBE[j][i];
			}
		}
		for(i=0;i<11;i++)
		{
			for(j=0;j<4;j++)
			{
				dp->DC2_TALBE[j][i] = DC2_TALBE[j][i];
			}
		}
	}
}
int initSENSOR(SENSOR *dp)
{
	dp->check_err = 0;
	init_check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));

	dp->para_err = 0;
	dp->test_mode = 0;
	dp->ch1_data_min = 0;
	dp->ch2_data_min = 0;
	dp->ch1_data_max = 0;
	dp->ch2_data_max = 0;
	
    getADS1247ParaFromEeprom(dp);

	setTask( 4, SENSOR_task, dp);
	setTask( 4, SENSOR_check_task, dp);

	return 0;
}



/*
#if	TEST_DEVICE_NO==1

const static float32 DC1_FOR_85[2]={1.0,1.0};	//85度环境温度补偿
const static float32 DC1_TALBE[4][11]=
{
 {0.0,		0.5,		1.0,		1.5,		2.0,		2.5,		3.0,		3.5,		4.0,		4.5,		5.0},		//0~5V
 {0.012743,	0.089909,	0.167089,	0.244265,	0.321447,	0.398656,	0.475859,	0.553039,	0.630257,	0.707473,	0.784665},
 {0.0,		2.0,		4.0,		6.0,		8.0,		10.0,		12.0,		14.0,		16.0,		18.0,		20.0},		//4~20mA
 {0.000831,	0.096396,	0.191979,	0.287548,	0.383141,	0.478736,	0.574335,	0.669913,	0.765516,	0.861136,	0.956731}
};

const static float32 DC2_FOR_85[2]={1.0,1.0};	 //85度环境温度补偿
const static float32 DC2_TALBE[4][11]=
{
 {0.0,		0.5,		1.0,		1.5,		2.0,		2.5,		3.0,		3.5,		4.0,		4.5,		5.0},		//0~5V
 {0.017991,	0.095069,	0.172145,	0.249196,	0.326235,	0.403326,	0.480423,	0.557471,	0.634521,	0.711568,	0.788643},
 {0.0,		2.0,		4.0,		6.0,		8.0,		10.0,		12.0,		14.0,		16.0,		18.0,		20.0},		//4~20mA
 {0.000872,	0.096734,	0.192112,	0.287513,	0.382889,	0.478281,	0.573663,	0.669046,	0.764455,	0.859855,	0.955255}
};

#elif TEST_DEVICE_NO==2

const static float32 DC1_FOR_85[2]={1.0,1.0};	//85度环境温度补偿
const static float32 DC1_TALBE[4][11]=
{
 {0.0,		0.5,		1.0,		1.5,		2.0,		2.5,		3.0,		3.5,		4.0,		4.5,		5.0},		//0~5V
 {0.012371,	0.089532,	0.166661,	0.243775,	0.320976,	0.398113,	0.475247,	0.552405,	0.629553,	0.706709,	0.783875},
 {0.0,		2.0,		4.0,		6.0,		8.0,		10.0,		12.0,		14.0,		16.0,		18.0,		20.0},		//4~20mA
 {0.000814,	0.096377,	0.191956,	0.287524,	0.383112,	0.478705,	0.574298,	0.669883,	0.765481,	0.861091,	0.956685}
};

const static float32 DC2_FOR_85[2]={1.0,1.0};	//85度环境温度补偿
const static float32 DC2_TALBE[4][11]=
{
 {0.0,		0.5,		1.0,		1.5,		2.0,		2.5,		3.0,		3.5,		4.0,		4.5,		5.0},		//0~5V
 {0.015674,	0.092767,	0.169836,	0.246914,	0.323985,	0.401126,	0.478236,	0.555399,	0.632533,	0.709642,	0.786803},
 {0.0,		2.0,		4.0,		6.0,		8.0,		10.0,		12.0,		14.0,		16.0,		18.0,		20.0},		//4~20mA
 {0.001044,	0.096438,	0.191847,	0.287244,	0.382661,	0.478079,	0.573502,	0.668918,	0.764351,	0.859781,	0.955213}
};

#else
const static float32 DC1_FOR_85[2]={1.0,1.0};	//85度环境温度补偿
const static float32 DC1_TALBE[4][11]=
{
 {0.0,		0.5,		1.0,		1.5,		2.0,		2.5,		3.0,		3.5,		4.0,		4.5,		5.0},		//0~5V
 {0.007764,	0.084927,	0.162046,	0.239177,	0.316274,	0.393434,	0.470572,	0.547717,	0.624853,	0.702054,	0.779211},
 {0.0,		2.0,		4.0,		6.0,		8.0,		10.0,		12.0,		14.0,		16.0,		18.0,		20.0},		//4~20mA
 {0.000528,	 0.096073,	0.191638,	0.287184,	0.382757,	0.478329,	 0.573909,	 0.669469,	 0.765053,	 0.860639,	 0.956215}
};

const static float32 DC2_FOR_85[2]={1.0,1.0};	//85度环境温度补偿
const static float32 DC2_TALBE[4][11]=
{
 {0.0,		0.5,		1.0,		1.5,		2.0,		2.5,		3.0,		3.5,		4.0,		4.5,		5.0},		//0~5V
 {0.015496,	0.092595,	0.169687,	0.246788,	0.323905,	0.401039,	0.478102,	0.555192,	0.632383,	0.709487,	0.786629},
 {0.0,		2.0,		4.0,		6.0,		8.0,		10.0,		12.0,		14.0,		16.0,		18.0,		20.0},		//4~20mA
 {0.001019,	0.096439,	0.191875,	0.287298,	0.382743,	0.478184,	0.573633,	0.669062,	0.764514,	0.859966,	0.955397}
};

#endif
*/

float32 get_the_sensor_data(SENSOR *dp,const float32 * table,float32 smp_data)
{
	Uint16 i=0;
	float32 x1,x2,y1,y2,x,y;
	
	for(i=0;i<11;i++)
	{
		if(smp_data < table[11+i]) break;
	}
	if(i == 0)
	{
		y = 0;
	}
	else if(i>=10)
	{
		y = table[10]*smp_data/table[21];
	}
	else
	{
		x = smp_data;
		x1 = table[11+i-1];
		x2 = table[11+i];
		y1 = table[i-1];
		y2 = table[i];
		y = ((x-x1)*y2+(x2-x)*y1)/(x2-x1);
	}
	
	return(y);
}


void SENSOR_task(SENSOR *dp)
{
	static Uint8 cnt=0;
	float32 data1,data2;

	
	if(cnt++>200) cnt=0;								//4000ms刷新一次
	else return;
	
	dp->TQ1_C = *dp->TQ1_C_in;
	dp->TQ2_C = *dp->TQ2_C_in;
	dp->HQ_C  = *dp->HQ_C_in;

	data1 = (float32)abs(*dp->ch1_data_in)*DC_LSB;				//转换为实际采样的电压
	data2 = (float32)abs(*dp->ch2_data_in)*DC_LSB;				//转换为实际采样的电压

	if(dp->dc1_type == 0)			//4~20mA
	{		
		dp->ch1_data = get_the_sensor_data(dp, &dp->DC1_TALBE[2][0], data1);
		
		if(dp->ch1_min != dp->ch1_max)					//说明定值范围有效
		{
			dp->ch1_data = dp->ch1_min+(dp->ch1_data-4.0)*(dp->ch1_max-dp->ch1_min)/16.0;
		}
	}
	else							//0~5V
	{
		dp->ch1_data = get_the_sensor_data(dp, &dp->DC1_TALBE[0][0], data1);
		if(dp->ch1_min != dp->ch1_max)					//说明定值范围有效
		{
			dp->ch1_data = dp->ch1_min+(dp->ch1_data-0.0)*(dp->ch1_max-dp->ch1_min)/5.0;
		}
	}

	if(dp->dc2_type == 0)			//4~20mA
	{
		dp->ch2_data = get_the_sensor_data(dp, &dp->DC2_TALBE[2][0], data2);
		if(dp->ch2_min != dp->ch2_max)					//说明定值范围有效
		{
			dp->ch2_data = dp->ch2_min+(dp->ch2_data-4.0)*(dp->ch2_max-dp->ch2_min)/16.0;
		}
	}
	else							//0~5V
	{
		dp->ch2_data =  get_the_sensor_data(dp, &dp->DC2_TALBE[0][0], data2);
		if(dp->ch2_min != dp->ch2_max)					//说明定值范围有效
		{
			dp->ch2_data = dp->ch2_min+(dp->ch2_data-0.0)*(dp->ch2_max-dp->ch2_min)/5.0;
		}
	}

	dp->ch1_data_bak = dp->ch1_data;
	dp->ch2_data_bak = dp->ch2_data;

	if(dp->test_mode == 100)
	{
		dp->ch1_data = data1;
		dp->ch2_data = data2;
		
		if(dp->ch1_data < dp->ch1_data_min) dp->ch1_data_min = dp->ch1_data;
		if(dp->ch2_data < dp->ch2_data_min) dp->ch2_data_min = dp->ch2_data;
		if(dp->ch1_data > dp->ch1_data_max) dp->ch1_data_max = dp->ch1_data;
		if(dp->ch2_data > dp->ch2_data_max) dp->ch2_data_max = dp->ch2_data;
	}
	
}

