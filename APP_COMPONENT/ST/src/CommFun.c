#include "CommFun.h"

Uint8	ZERO_Uint8=0;
Uint16	ZERO_Uint16=0;
Uint32	ZERO_Uint32=0;
Uint8   ZERO_BUFFER[1024];

Uint8	TWO_SYS_CMP_ERR = 0;
Uint8	RAM_ERR = 0;


void initbuffer(Uint8 * p, Uint32 size)
{
	Uint32 i=0;
	for(i=0;i<size;i++)
	{
		*p++=0;
	}
}


void init_pointer(Uint32 start,Uint32 end)
{
	Uint32 * p1,* p2;
	Uint16 i=1;

	p1 = (Uint32 *) start;
	p2 = (Uint32 *) end;
	
	while(p1+i != p2)
	{
		*(p1+i) = (Uint32)ZERO_BUFFER;
	}	
}


#pragma CODE_SECTION(GSE_Test_Q,".rtm_code")
//测试仪GOOSE命令品质处理：均为检修态时更新，否则数据清0
Uint8 GSE_Test_Q(Uint8 *data_in, Uint8 *date_in_q, Uint8 device_test)
{
    Uint8 value=0,quality=0;
    
    quality = *date_in_q;
    
    //接收软压板使能且链路正常且检修位一致
    if( ( (quality&0x08) == 0x08 ) && ( (quality&0x04) == 0x04 ) && (( (quality&0x02)>>1 ) & device_test) )
    {
        value = *data_in;
    }
    else
    {
        value = 0;
    }
    
    return(value);
}

#pragma CODE_SECTION(GSE_Bool_Q,".rtm_code")
//GOOSE品质处理：检修一致更新，检修不一致清0
Uint8 GSE_Bool_Q(Uint8 *data_in, Uint8 *date_in_q, Uint8 device_test)
{
    Uint8 value=0,quality=0;
    
    quality = *date_in_q;
    
    //接收软压板使能且链路正常且检修位一致
    if(((quality&0x08) == 0x08) && ((quality&0x04) == 0x04) && (!(((quality&0x02)>>1)^device_test)))
    {
        value = *data_in;
    }
    else
    {
        value = 0;
    }
    
    return(value);
}

// 初始化SOE
void initSOE_fun(SOE_VALUE * soe_str, Uint8 value)
{
	soe_str->value.c_value = value;
	soe_str->time.s = utc_sec;
	soe_str->time.ms = local_ms;
}

void SOE_fun(SOE_VALUE * soe_str, Uint8 value)
{
	if(soe_str->value.c_value != value)
	{
		soe_str->value.c_value = value;
		soe_str->time.s = utc_sec;
		soe_str->time.ms = local_ms;
	}
}

#pragma CODE_SECTION(Dlyon,".rtm_code")
////////////////////防抖函数/////////////////////////////////////////////////////
Uint8 Dlyon(Uint8 * status, Uint32 * time_save,Uint8 signal_in, Uint32 delay_time)
{
	if(signal_in)
	{
		if(*status == 2)
		{
			return 1;
		}
		else if(*status == 0)
		{
			*status = 1;
			*time_save = current_time_lo;
			return 0;
		}
		else if(*status == 1)
		{
			if((current_time_lo - *time_save) >= delay_time)
			{
				*status = 2;
				return 1;
			}
			else return 0;
		}
	}
	*status = 0;
	return 0;
}
////////////////////防抖展宽函数/////////////////////////////////////////////////////
Uint8 Dly_expand(Uint8 * status, Uint32 * time_save,Uint8 signal_in, Uint32 delay_time,Uint32 expand_time)
{
	Uint8 	result=0;
	if(signal_in)
	{
		if(*status == 2)
		{
			result = 1;
		}
		else if(*status == 0)
		{
			*status = 1;
			*time_save = current_time_lo;
			result = 0;
		}
		else if(*status == 1)
		{
			if((current_time_lo - *time_save) >= delay_time)
			{
				*status = 2;
				result = 1;
			}
			else
			{
				result = 0;
			}
		}
	}
	else
	{
		if(*status == 2)							//说明曾经变为1
		{
			*status = 3;
			*time_save = current_time_lo;			//记录由1变0的时刻
		}
		else if(*status == 3)
		{
			if((current_time_lo - *time_save) >= expand_time)
			{
				*status = 0;
				result = 0;
			}
			else
			{
				result = 1;
			}
		}
		else
		{
			*status = 0;
			result = 0;
		}
		
	}
	return(result);
}

Uint8 deal_TripClose(Uint8 * status, Uint32 * time_save,Uint8 command)
{
	Uint8 result=0;
	if(command == 1)
	{
		if(*status == 0)	//命令开始
		{
			*status = 1;
			(*time_save)++;
		}
		else if(*status == 1)	//命令在3.2ms内
		{
			(*time_save)++;
			if(*time_save >= lev2_2_4ms)
			{
				*status = 2;
			}
		}
		else if(*status == 2)	//命令在40ms内
		{
			(*time_save)++;
			if(*time_save >= lev2_40ms)
			{
				*status = 3;
			}
		}
		else if(*status == 3)	//命令在40~100ms内
		{
			(*time_save)++;
			if(*time_save >= lev2_100ms)
			{
				*status = 4;
			}
		}
		else if(*status == 4)	//命令在100ms外
		{
			*time_save = lev2_100ms;
		}
		else
		{
			*time_save = 0;
			*status = 0;
		}
	}
	else
	{
		if(*status == 2)	//命令在3~40ms内,扩展到40ms
		{
			(*time_save)++;
			if(*time_save >= lev2_40ms)
			{
				*time_save = 0;
				*status = 0;
			}
		}
		else
		{
			*time_save = 0;
			*status = 0;
		}
	}

	if((*time_save == 0)||(*time_save >= lev2_100ms))
	{
		result = 0;
	}
	else
	{
		result = 1;
	}



	return(result);
}

Uint8 deal_DLYFYH(Uint8 * status, Uint32 * time_save,Uint8 command)
{
	Uint8 result=0;
	if(command == 1)
	{
		if(*status == 0)	//命令开始
		{
			*status = 1;
			(*time_save)++;
		}
		else if(*status == 1)	//命令在250ms内,随动
		{
			(*time_save)++;
			if(*time_save >= lev2_250ms)
			{
				*status = 2;
			}
		}
		else if(*status == 2)	//命令在250ms外
		{
			*time_save = lev2_250ms;
		}
		else
		{
			*time_save = 0;
			*status = 0;
		}
	}
	else
	{
		*time_save = 0;
		*status = 0;
	}

	if((*time_save == 0)||(*time_save >= lev2_250ms))
	{
		result = 0;
	}
	else
	{
		result = 1;
	}

	return(result);
}

Uint8 deal_GD_DD(Uint8 * status, Uint32 * time_save,Uint8 command)
{
	Uint8 result=0;
	if(command == 1)
	{
		if(*status == 0)	//命令开始
		{
			*status = 1;
			(*time_save)++;
		}
		else if(*status == 1)	//命令在1000ms内
		{
			(*time_save)++;
			if(*time_save >= lev2_1S)
			{
				*status = 2;
			}
		}
		else if(*status == 2)	//命令在1000ms外
		{
			*time_save = lev2_1S;
		}
		else
		{
			*time_save = 0;
			*status = 0;
		}
	}
	else
	{

		*time_save = 0;
		*status = 0;
	}

	if((*time_save == 0)||(*time_save >= lev2_1S))
	{
		result = 0;
	}
	else
	{
		result = 1;
	}

	return(result);
}

Uint8 CommandContrl(Uint8 * status, Uint32 * time_save,Uint8 command, Uint8 command_type)
{
	Uint8 result=0;
	switch(command_type)
	{
		case 	1:					//跳合闸
			result = deal_TripClose(status,time_save,command);
			break;
		case	2:					//遥跳遥合
			result = deal_DLYFYH(status,time_save,command);
			break;
		case	3:					//其他遥控
			result = deal_GD_DD(status,time_save,command);
			break;
		default :					//简单随动
			result = command;
			break;
	}

	return(result);
}


#pragma CODE_SECTION(GOOSE_SOE,".rtm_code")
void GOOSE_SOE(SOE_VALUE * command,SOE_VALUE* command_old)
{
	if(command_old->value.c_value != command->value.c_value)
	{
		*command_old = *command;
	}
}

void BI_SOE(SOE_VALUE * command,SOE_VALUE* command_old)
{
	if(command_old->value.c_value != command->value.c_value)
	{
		memcpy(command_old,command,sizeof(SOE_VALUE));
	}
}

void GOOSE_LINK_SOE(SOE_VALUE * command, Uint8 *date_in_q, SOE_VALUE* command_old)
{
	Uint8 quality;

	quality = *date_in_q;
	if(command_old->value.c_value != command->value.c_value)
	{
		*command_old = *command;
	}

	if( ( (quality&0x08) != 0x08 ) || ( (quality&0x04) != 0x04 ))
	{
		command_old->value.c_value = 0;
	}
}

void get_relay_stat(Uint8 command,Uint8 *SWI,Uint8 *RELAY_STAT)
{
    Uint8 tmp1;
    if(command == 1)
    {
        *RELAY_STAT = (~(*SWI))&0x01;
    }
    else
    {
        *RELAY_STAT = 0;
    }
}

#pragma CODE_SECTION(two_sys_cmp,".rtm_code")
void two_sys_cmp(Uint8 A_SYS,Uint8 B_SYS,Uint8 * result, Uint16* CNT,Uint32 window)
{
	if(A_SYS != B_SYS)
	{
		(*CNT)++;
	}
	else *CNT = 0;
	if(*CNT>= window)
	{
		*CNT = window;
		*result = 1;
		TWO_SYS_CMP_ERR |= 0x01;
	}
	else *result = 0;
}


void two_signal_cmp(Uint8 A_SYS,Uint8 B_SYS,Uint8 * result, Uint16* CNT,Uint32 window)
{
	if(A_SYS != B_SYS)
	{
		(*CNT)++;
	}
	else *CNT = 0;
	if(*CNT>= window)
	{
		*CNT = window;
		*result = 1;
	}
	else *result = 0;
}
	
void init_check_set_pointer(Uint32  start,Uint32  checksum)
{
	Uint8 * p1,*p2;
	Uint32 * p3;
	Uint16 i=0;
	Uint32 checksum_now=0;

	p1 = (Uint8 *)start;
	p2 = (Uint8 *)checksum;
	p3 = (Uint32 *)checksum;
	while(p1+i != p2)
	{
		checksum_now += *(p1+i);
		i++;
	}

	checksum_now = ~(checksum_now);
	*p3 = checksum_now;
	
}

Uint8 check_set_pointer(Uint32 start,Uint32 checksum)
{
	Uint8 * p1,*p2;
	Uint32 * p3;
	Uint16 i=0;
	Uint32 checksum_now=0;
	Uint8 flag_err=0;
	
	p1 = (Uint8 *)start;
	p2 = (Uint8 *)checksum;
	p3 = (Uint32 *)checksum;
	while(p1+i != p2)
	{
		checksum_now += *(p1+i);
		i++;
	}

	checksum_now = ~(checksum_now);
	flag_err = (checksum_now == *p3)?0:1;

	if(flag_err) RAM_ERR|=0x01;
	return(flag_err);
	
}


///////////////////////////////////////////////////////////////////////////////////
//				此函数检测信号，当信号有变位时时，产生一个pulse_wide的脉宽信号
///////////////////////////////////////////////////////////////////////////////////
#pragma CODE_SECTION(PULSE_TRIG,".rtm_code")
void PULSE_TRIG(Uint8 * signal_now,Uint8 * signal_old,Uint16 *signal_cnt,Uint16 pulse_wide,Uint8* pulse,Uint8 edge_mode)
{
	if(*signal_now != *signal_old)
	{
		*signal_old = *signal_now;
		if(*signal_now == edge_mode)
		{
			*signal_cnt = pulse_wide;
		}
	}
	if(*signal_cnt != 0)
	{
		*pulse = 1;
		(*signal_cnt)--;
	}
	else *pulse = 0;
}


