#ifndef _HZ6101_H
#define _HZ6101_H

#ifdef __cplusplus
extern "C" {
#endif

// 定义CPU类型
#define     CPU_TYPE 	    LINUX_INSTALLED
#define     KERNEL_BUILD    

#define	    DEVICE_CAN      "/dev/pcan0"



#define MMB_BUF_LEN     0x10000000
#define MMB_BUF_ADDR    0xB0000000
#define OMAP_SHARE_LEN  0x00A00000	
#define OMAP_SHARE_ADDR 0xAF600000


extern unsigned char int8_size;
extern unsigned char int16_size;
extern unsigned char int32_size;
extern unsigned long version;
extern unsigned char share_mode;
extern unsigned long board_type;
extern unsigned long lib_version;
extern unsigned char alig_size;

extern void  putInt8(char *data, int *offset, unsigned char value);
extern void  putInt16(char *data, int *offset, unsigned short value);
extern void  putInt32(char *data, int *offset, unsigned long value);
extern void  putInt64(char *data, int *offset, unsigned long long value);

extern unsigned char       getInt8(char *data, int *offset);
extern unsigned short      getInt16(char *data, int *offset);
extern unsigned long       getInt32(char *data, int *offset);
extern unsigned long long  getInt64(char *data, int *offset);

extern void  getString(char *src, int *offset, char *dst, int len);
extern void  putString(char *src, int len, char *dst, int *offset);
extern void  putValue(char *data, int *offset, char *value, int size);
extern void  putMemory(char *dest, int *offset, char *value, int size);
extern int 	 getViewDataLen(Uint32 addr);
extern unsigned long getProgramTime();
extern unsigned long getProgramCrc();
extern void   waitForcmd(void);
extern void   checkTypeSize(void);
extern void   delayUs(int delay_time);
extern void   resetCpu(void);
extern void   registerSystemStatus(void);

#ifdef __cplusplus
}
#endif
#endif
