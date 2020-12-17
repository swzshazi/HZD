#ifndef __INCSIGNALH
#define __INCSIGNALH

#ifdef __cplusplus
extern "C" {
#endif

#include "database.h"

struct board_status
{
	unsigned char  addr;
	unsigned char  version_ok;
	unsigned short reserved;
	unsigned long  type;
	unsigned long  status;	
	char desc[24];
};

typedef struct
{
	char   board_num;
	struct board_status *board_stat;
	struct board_status  board[1];
}BOARD_INFO;

struct prog_info
{
	unsigned char addr;
	unsigned long type;
	unsigned long prog_version;
	unsigned long prog_time;
	unsigned long prog_chksum;
};

typedef struct
{
	char language_type;			
	char main_version[16];		
	char sub_version[16];		
	char config_version[16];	
	char manager_no[16];		
	char area_id[16];			
	char device_type[32];		
	char develop_no[16];		
	char prog_crc[16];			
	char device_name[3][64];	
	char instan_name[3][64];	
	char date[16];				
	char time[16];
	char hmi_version[16];		
	char hmi_date[16];			
	char hmi_time[16];			
	char hmi_crc[16];			
	char ck_version[16];		
	char ck_sub_version[16];
	char ck_date[16];
	char ck_time[16];
	char ck_crc[16];
	char ck_manager_no[16];
	char io_version[16];		
	char io_sub_version[16];
	char io_date[16];
	char io_time[16];
	char io_crc[16];
	char io_manager_no[16];
	char uboot_ver[12];			
	char kernel_ver[24];		
	char filesys_ver[12];		
	char version_err_info[7][24];
	char run_dev_ver[48];		
	char backup_dev_ver[48];	
	char device_cid_crc[12];	
	char station_cid_crc[12];
    char config_date[16];		
    char config_time[16];
	char reserved[68];
	char num;
	struct prog_info board[1];
}DEVICE_INFO;

extern DESCRIPTION   *getVarDesc(char *name);		
extern ITEM          *getVarItem(char *name);
extern BOARD_INFO    *getBoardInfo(void);
extern DEVICE_INFO   *getDeviceInfo(void);
extern LANGUAGE_NODE *getLanguageDesc(char *name);
extern char 		 *getThirdLanguageDesc(char *name);
extern char 		 *getDescByLanguage(DESCRIPTION *desc,int language_type);  
extern char 		 *getDescFromLanguagedb(int language_item_no,int language_type);
extern unsigned long  calcMsFromTicks(unsigned long start_ticks,unsigned long end_ticks);

#ifdef __cplusplus
}
#endif
#endif
