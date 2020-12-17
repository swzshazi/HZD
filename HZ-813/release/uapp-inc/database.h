#ifndef __INC_DATABASE_H
#define __INC_DATABASE_H

#ifdef __cplusplus
extern "C" {
#endif
#include "common_types.h"

#define SECTION_NUM 	30
#define MAX_GROUP_NUM	120
#define TICKS_SHIFT	    8

#ifndef NAME_STRING_LEN
#define NAME_STRING_LEN 50
#endif

typedef struct
{
	char   name[NAME_STRING_LEN];
	Uint8  type:4;
	Uint8  level:3;
	Uint8  setted:1;			
	Uint8  ref_type:1;			
	Uint8  is_unsigned:1;    	
    Uint8  ref_opt:1;        	
    Uint8  with_default:1;   	
    Uint8  is_dps:1;    		
    Uint8  is_time_scale:1;		
    Uint8  comm_priority:1;		
    Uint8  with_constant:1;   	
    Uint16 struct_size;			
    Uint8  list_num;			
    Uint8  show_attr;			
    char   format[8];			
	char   unit[8];				
	union
	{
		struct
		{
			float norm;
			float prm;
			float max;
			float min;
			float default_value;
		}d_float;
		struct
		{
			char value[20];
		}d_string;
		char type_name[20];
	}config;
	Uint16 list_no;				
	char   desc[NAME_STRING_LEN];			
}DESCRIPTION;

typedef struct
{
	Uint8  board;
	Uint8  pid;
	Uint8  grp;					
    Uint8  bit;					
	Uint16 inf;					
	Uint16 shmem_var_no;
	Uint32 parent_addr;
	Uint32 addr;
    DESCRIPTION desc;
}ITEM;

typedef struct
{
	char str_list_value[3][NAME_STRING_LEN];
}LIST_ITEM;

typedef struct
{
	int data_item_no;	
	Uint8 need_confirm;	
	Uint8 primary_and_secondary;
	Uint8 reserved[2];
	double value[SECTION_NUM];
}VALUE_NODE;

typedef struct
{
	unsigned char type;
	union
	{
		double f_value;
		char   s_value[32];	
	}value;
}VALUE;

typedef struct
{
	int grp;
	int section;
	int inf;
}SETTING;

typedef struct
{
	char desc[3][NAME_STRING_LEN];
}LANGUAGE_NODE;

typedef struct
{
	int current_section;
	int	group_num;
	struct group				
	{
		char  group_name[2][NAME_STRING_LEN];
		char  desc[3][NAME_STRING_LEN];
		int   group_item_num;
		Uint8 multi_set;
		Uint8 section_num;
		Uint8 show_flag;
		Uint8 desc_change_flag;
	}group[MAX_GROUP_NUM];
}SETTINGRPS;

extern SETTINGRPS    *group_db;

#ifdef __cplusplus
}
#endif

#endif
