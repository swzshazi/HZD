
#include <string.h>
#include "sfp.h"
#include <math.h>
#include <stdlib.h> 

/*  code  */
SFP *newSFP(Component *Parent,const char *Name)
{
    SFP *dp;
    int i;
    char buf[250];
  
    dp = (SFP *)calloc(1, sizeof(SFP));
    if (!dp) return NULL;
  
    dp->type_name="SFP";
    dp->parent=Parent;
    dp->name=Name;
    dp->InitComponent=initSFP;
  
    //register component self        
    registerComponent((Component*)dp);

    registerVarIn((Component *)dp,(void **)&(dp->temp),"temp", T_INT16,LEVEL2);
	
    registerVarOut((Component*)dp,(void*)&(dp->sfp_link_state),  "sfp_link_state", T_UINT16,  LEVEL2);			//光模块状态指示寄存器。Bit0～Bit15分别指示1～16号光模块，1～光模块无响应，0～光模块正常响应。
 //   registerVarOut((Component*)dp,(void*)&(dp->cfg_reg),         "cfg_reg", T_UINT16,  LEVEL2);   			//暂无用
    registerVarOut((Component*)dp,(void*)&(dp->VCC500),  "VCC500", T_FLOAT, LEVEL2);
    registerVarOut((Component*)dp,(void*)&(dp->dev_temp),  "dev_temp", T_FLOAT, LEVEL2);
 
 
 
    for(i=0;i<SFP_NUM;i++)
    {
        sprintf(buf, "tx%d_pwr", i+1);
        registerVarOut((Component *)dp, (void *)&(dp->p_tx[i]), buf, T_FLOAT, LEVEL2);
        sprintf(buf, "rx%d_pwr", i+1);
        registerVarOut((Component *)dp, (void *)&(dp->p_rx[i]), buf, T_FLOAT, LEVEL2);
		sprintf(buf, "temp%d", i+1);
        registerVarOut((Component *)dp, (void *)&(dp->p_temp[i]), buf, T_FLOAT, LEVEL2);
		
    }
	
    registerParameter((Component*)dp,(void*)&(dp->cfg_reg),"cfg_reg min=0 max=1 default=0 option=1",T_UINT16);
    
    return dp;
}





void runSFP(SFP * dp)
{
	static Uint8 run_cnt=0,cal_time=0;
    int i;
	float32 tmp;

	if(run_cnt++ >10)
	{
		run_cnt = 0;
		cal_time++;
		dp->sfp_link_state     = dp->sfp_ctrl->sfp_no_ack;
		for(i=0;i<SFP_NUM;i++)
	    {
	    	if(((dp->sfp_link_state>>i)&0x0001) == 0)		//光模块有效
	    	{
			
	    		tmp = (dp->sfp_module->sfp_modules[i].tx_pow <= 10)?(-35.0):(log10(dp->sfp_module->sfp_modules[i].tx_pow/10000.0) * 10.0);		//当太小的时候，直接赋值-35dbm
				dp->deubg_f = tmp;
				dp->p_tx_max[i] = (tmp>dp->p_tx_max[i])?tmp:dp->p_tx_max[i];
				dp->p_tx_min[i] = (tmp<dp->p_tx_min[i])?tmp:dp->p_tx_min[i]; 
				dp->p_tx_tmp[i] +=tmp;
				tmp = (dp->sfp_module->sfp_modules[i].rx_pow <= 10)?(-35.0):(log10(dp->sfp_module->sfp_modules[i].rx_pow/10000.0) * 10.0);
				dp->p_rx_max[i] = (tmp>dp->p_rx_max[i])?tmp:dp->p_rx_max[i];
				dp->p_rx_min[i] = (tmp<dp->p_rx_min[i])?tmp:dp->p_rx_min[i];
				dp->p_rx_tmp[i] +=tmp;
				tmp = dp->sfp_module->sfp_modules[i].temp/256.0;
				dp->p_temp_max[i] = (tmp>dp->p_temp_max[i])?tmp:dp->p_temp_max[i];
				dp->p_temp_min[i] = (tmp<dp->p_temp_min[i])?tmp:dp->p_temp_min[i];
				dp->p_temp_tmp[i] += tmp;
			}
			else										//光模块无效
			{
				dp->p_tx_tmp[i] = 0;
				dp->p_rx_tmp[i] = 0;
				dp->p_temp_tmp[i] = 0;
			}
	    }
		
		if(cal_time >= 10)
		{
			cal_time = 0;
			if(dp->cfg_reg == 1)
			{
				for(i=0;i<SFP_NUM;i++)
			    {
					dp->p_tx[i] = dp->p_tx_tmp[i]/10.0;
					dp->p_tx_tmp[i] = 0;
					dp->p_rx[i] = dp->p_rx_tmp[i]/10.0;
					dp->p_rx_tmp[i] = 0;
					dp->p_temp[i] = dp->p_temp_tmp[i]/10.0;
					dp->p_temp_tmp[i] = 0;
			    }
			}
			else
			{
				for(i=0;i<SFP_NUM;i++)
			    {
					dp->p_tx[i] = 0.0;
					dp->p_rx[i] = 0.0;
					dp->p_temp[i] = 0.0;
			    }
			}
			dp->VCC500 = 4.95+ (rand()%8)*0.01;
			dp->dev_temp = (*dp->temp)/10.0;
		}
		
	}
	
    
    
    
}

int initSFP(SFP *dp)
{
	Uint8 i;
    dp->sfp_link_state = 0xffff;
    dp->sfp_ctrl->cfg_reg  = dp->cfg_reg;
    dp->sfp_ctrl       = (volatile SFP_CTRL *)FPGA_SFP_ADDR;
    dp->sfp_module     = (volatile SFP_MODULE *)(FPGA_SFP_ADDR + 0x200);
	dp->VCC500 = 5.00;

	for(i=0;i<SFP_NUM;i++)
	{
		dp->p_tx_max[i] = -100.0;
		dp->p_rx_max[i] = -100.0;
		dp->p_temp_max[i] = -100.0;
		dp->p_tx_min[i] = 200.0;
		dp->p_rx_min[i] = 200.0;
		dp->p_temp_min[i] = 200.0;
		dp->p_tx_tmp[i] = 0;
		dp->p_rx_tmp[i] = 0;
		dp->p_temp_tmp[i] = 0;
	}

    setTask(4, runSFP, dp);
    return 0;
}


