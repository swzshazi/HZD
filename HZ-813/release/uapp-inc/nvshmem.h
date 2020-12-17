
#ifndef _NVSHMEM_H
#define _NVSHMEM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "common_types.h"

#define SRAM_FILE_SIZE          (400*1024)
#define DRAM_FILE_SIZE          (16*1024*1024)

#define FILE_NAME_LEN_ERR       0x01
#define FILE_NUM_ERR			0x02
#define FILE_USED_SIZE_ERR		0x04

#define USED_FLAG       		0x55aa5a5a
#define RAMFILE_NAME_LEN      	15
#define SRAM_FILE_MAX_NUM       223
#define DRAM_FILE_MAX_NUM       32
#define OTHR_FILE_MAX_NUM 		32

typedef struct
{
    char   file_name[RAMFILE_NAME_LEN+1];
    Uint32 file_addr;
    Uint32 file_len;
    Uint8  resv[8];
}FILE_HEADER;

typedef struct
{
    char   info[64];
    Uint32 used_flag;
    Uint8  max_num;
    Uint8  used_num;
    Uint8  is_writing;
    Uint8  is_clearing;
    Uint32 time_sum;
	Uint8  resv[2];
	Uint16 status;
	Uint32 used_size;
    Uint8  resv1[12];
    FILE_HEADER file_header[SRAM_FILE_MAX_NUM];
	FILE_HEADER othr_header[OTHR_FILE_MAX_NUM];
}SRAM_FILE_CONTROL;

typedef struct
{
    Uint32 used_flag;
    Uint8  max_num;
    Uint8  used_num;
    Uint8  is_writing;
    Uint8  is_clearing;
    Uint32 time_sum;
	Uint32 used_size;
	Uint16 status;
	Uint16 resv;
    FILE_HEADER file_header[DRAM_FILE_MAX_NUM];
}DRAM_FILE_CONTROL;

extern SRAM_FILE_CONTROL *p_sram_file;
extern DRAM_FILE_CONTROL *p_dram_file;
extern int clearSramFileContent(char *file_name);
extern int deleteAllSramFile(void);

// 面向python接口函数
extern int   creatNvShmemFile(char *file_name,int file_len);
extern int   creatDramShmemFile(char *file_name,int file_len);
extern void *getNvShmemFileContent(char *file_name);
extern void *getDramShmemFileContent(char *file_name);
extern void *getDramFileContent(char *file_name);
extern int   showNvShmemFileAllInfo(void);
extern int   registerRamfileStatus(void);
extern int   initSdramFile(Uint32 shmem_base_addr);
extern int   initNvShmemFile(void);

#ifdef __cplusplus
}
#endif

#endif
