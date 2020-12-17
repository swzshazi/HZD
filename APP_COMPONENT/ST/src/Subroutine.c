/*
元件：  Subroutine
功能描述：
        子程序集合；
基本功能为：
        子程序集合

*/

#include "hzplatform.h"
#include "Subroutine.h"
//#include "Const.h"

//初始化内存保护
//参数说明
//Uint8 *set_error，内存自检出错标志
//Uint32 *check_array,初始化过程中申请的定值拷贝内存基地址
//Uint32 *check_head,需要保护的定值基地址
//Uint32 check_len,需要保护的内存的长度
//Uint32 check_len_check,需要保护的内存的长度的校验
void check_set(Uint8 *mem_error,Uint32 *check_array,Uint32 *check_head,Uint32 check_len,Uint32 check_len_check)
{
	Uint32 i;
	if(check_len!=(~check_len_check))
	{
		*mem_error = 1;
		return;
	}
	for(i=0;i<check_len;i++)
	{
		if(check_array[i]!=check_head[i]) *mem_error = 1;
	}
}

//运行内存保护
//参数说明
//Uint32 *check_head,需要保护的定值基地址
//Uint32 *check_end,需要保护的定值尾地址
//Uint32 *check_len,需要保护的内存的长度
//Uint32 *check_len_check,需要保护的内存的长度的校验
//Uint32 *check_sum,需要保护内存的内容校验和
//返回值
//创建的内存拷贝基地址
Uint32* init_setcheck(Uint32 *check_head,Uint32 *check_sum,Uint32 *check_len,Uint32 *check_len_check)
{
	Uint32 k;
	Uint32 *p;
	Uint32 *check_array;
	Uint32 temp32;

	p = check_head;
	*check_len = 0;
	temp32 = 0;
	for(;p!=check_sum;p++)
	{
		temp32 += (Uint32)(*p);
		(*check_len)++;
	}
	*check_len_check = ~(*check_len);
	(*check_sum) = temp32;
	check_array = (Uint32 *)calloc(*check_len, sizeof(Uint32));
	if(!check_array) return 0;
	p = check_head;
	for(k=0;k<*check_len;k++)
	{
		check_array[k] = (Uint32)(*p);
		p++;
	}

	return (Uint32 *)check_array;
}

#pragma CODE_SECTION(get_offset,".rtm_code")
void get_offset(int16 data, Uint32 *num,int32 *sum, int32 *offset)				//零漂计算程序
{
	int32 tmp;
	(*num)++;
	*sum = *sum + data;
	if(*num == 32768)
	{
		*num = 0;
		tmp = (*sum)>>15;
		if(tmp >= 50)	*offset = 50;
		else if(tmp <= -50)	*offset = -50;
		else *offset = tmp;
		*sum = 0;
	}
}




