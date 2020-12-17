#ifndef _STREAM_H
#define _STREAM_H



#define MAX_FILE_NUM        8   // 最多支持8个文件

struct strstream
{
    char   *start_pos;          // 文件起始地址
    char   *end_pos;            // 文件结束地址
    char   *rd_pos;             // 文件当前读地址
    char   *wr_pos;             // 文件当前写地址
    int     delta_offset;       // 从FLASH拷到MEM的相对偏移差
    char    rd_enable;          // 允许读
    char    wr_enable;          // 允许写
};

typedef struct
{
    char file_name[50];         // 文件名
    Uint32 file_offset;         // 文件存贮相对偏移
    Uint32 file_len;            // 文件长度
    Uint32 file_crc;            // 文件完整性检查
} FILE_HEADER;

typedef struct
{
    Uint32 check_flag;          // 若非第一次使用,则为0x58554446
    Uint8 item_num;             // 文件个数
    FILE_HEADER   items[MAX_FILE_NUM];
} FLASH_HEADER;

extern struct strstream *stropen(const char *path, const char *mode);
extern int strclose(struct strstream *stream);
extern int strgetc(struct strstream *stream);
extern int strugetc(int c, struct strstream *stream);
extern int strread(void *ptr, int size, int nmemb, struct strstream *stream);
extern int strwrite(const void *ptr, int size, int nmemb, struct strstream *stream);
extern int strscanf(struct strstream *stream, const char *format, ...);
extern int strfeof(struct strstream *stream);
extern char *strgets(char *s, int size, struct strstream *stream);
//extern double strtodf(char *cp);
extern void strclear(void);
extern void skipComment(struct strstream *stream);
extern int mysscanf (const char *s, const char *format, ...);

#endif
