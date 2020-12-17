#ifndef _STREAM_H
#define _STREAM_H



#define MAX_FILE_NUM        8   // ���֧��8���ļ�

struct strstream
{
    char   *start_pos;          // �ļ���ʼ��ַ
    char   *end_pos;            // �ļ�������ַ
    char   *rd_pos;             // �ļ���ǰ����ַ
    char   *wr_pos;             // �ļ���ǰд��ַ
    int     delta_offset;       // ��FLASH����MEM�����ƫ�Ʋ�
    char    rd_enable;          // �����
    char    wr_enable;          // ����д
};

typedef struct
{
    char file_name[50];         // �ļ���
    Uint32 file_offset;         // �ļ��������ƫ��
    Uint32 file_len;            // �ļ�����
    Uint32 file_crc;            // �ļ������Լ��
} FILE_HEADER;

typedef struct
{
    Uint32 check_flag;          // ���ǵ�һ��ʹ��,��Ϊ0x58554446
    Uint8 item_num;             // �ļ�����
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
