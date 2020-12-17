/*
Ԫ����  Subroutine
����������
        �ӳ��򼯺ϣ�
��������Ϊ��
        �ӳ��򼯺�

*/

#include "hzplatform.h"
#include "Subroutine.h"
//#include "Const.h"

//��ʼ���ڴ汣��
//����˵��
//Uint8 *set_error���ڴ��Լ�����־
//Uint32 *check_array,��ʼ������������Ķ�ֵ�����ڴ����ַ
//Uint32 *check_head,��Ҫ�����Ķ�ֵ����ַ
//Uint32 check_len,��Ҫ�������ڴ�ĳ���
//Uint32 check_len_check,��Ҫ�������ڴ�ĳ��ȵ�У��
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

//�����ڴ汣��
//����˵��
//Uint32 *check_head,��Ҫ�����Ķ�ֵ����ַ
//Uint32 *check_end,��Ҫ�����Ķ�ֵβ��ַ
//Uint32 *check_len,��Ҫ�������ڴ�ĳ���
//Uint32 *check_len_check,��Ҫ�������ڴ�ĳ��ȵ�У��
//Uint32 *check_sum,��Ҫ�����ڴ������У���
//����ֵ
//�������ڴ濽������ַ
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
void get_offset(int16 data, Uint32 *num,int32 *sum, int32 *offset)				//��Ư�������
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




