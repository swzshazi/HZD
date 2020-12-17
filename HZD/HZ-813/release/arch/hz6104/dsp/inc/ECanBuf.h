#ifndef _INCECANBUFH
#define _INCECANBUFH

#ifdef __cplusplus
extern "C" {
#endif

#define     MAX_MFBUF               160
#define     MAX_SFBUF               32
#define     MAX_SFBUF_L             31
#define     MAX_ACKBUF              16
#define     MAX_ACKBUF_L            15

#define     NEED_ACK_FRAME          0
#define     NEEDLESS_ACK_FRAME      1
#define     CONFIRM_ACK_FRAME       2
#define     DENY_ACK_FRAME          3


/* eCAN Message ID (MSGID) bit definitions */
struct CANMSGID_BITS
{
    unsigned      Destination:7;    // 目的地址
    unsigned      Finish:1;         // 结束标志
    unsigned      Source:7;         // 源地址
    unsigned      FrameFlag:1;      // 单帧或多帧标志
    unsigned      AppType:5;        // 应用报文类型
    unsigned      Vsq:3;            // 可变结构限定词
    unsigned      FrameType:2;      // 帧类型
    unsigned      CycNo:2;          // 循环序列号
    unsigned      Priority:1;       // 优先级
    unsigned      Ide:1;            // ID扩展位
    unsigned      Rtr:1;            // 远程传送请求位
    unsigned      Ame:1;            // 访问屏蔽使能位
};

/* Allow access to the bit fields or entire register */
union CANMSGID_REG
{
    unsigned int all;
    struct CANMSGID_BITS bit;
};

/* Define Rx and Tx Buf struct */
struct MultiFrameBuf
{
    union CANMSGID_REG id;
    Uint8 len;
    Uint8 pointer;
    Uint8 data[MAX_MFBUF];
};

struct SingleFrame
{
    union CANMSGID_REG id;
    unsigned int len;
    Uint8 data[8];
};

struct SingleFrameBuf
{
    Uint8 in;
    Uint8 out;
    struct SingleFrame queue[MAX_SFBUF];
};

struct MSFRXSTATUS                          // 提供给应用层的用于处理接收报文的状态
{
    Uint8 sfnum;                            // 单帧报文缓冲区中下一个要处理的报文在mailbox中的序号
    Uint8 sflen;                            // 单帧报文缓冲区中未处理的报文总数
    Uint8 mflen;                            // 多帧报文缓冲区的当前报文所占用的有效mailbox数量，最高位为1表示收到完整的一个多帧报文
};

struct AckFrame
{
    union CANMSGID_REG id;
    Uint8 data;
};

struct AckFrameBuf
{
    Uint8 in;
    Uint8 out;
    struct AckFrame queue[MAX_ACKBUF];
};

struct CANSTATUS
{
    Uint8 times;
    Uint8 waiting;                          //0 no waiting; 1 single frame waiting ACK; 2 multi frame waiting ACK
    Uint8 multi_frame_sending;
    Uint8 timeout;
    Uint32 last_send_time;
};

struct CANERRORSTAT
{
    unsigned int can_irqcnt;                // Number of irqs
    Uint16 can_msglost;                     // Number of messages lost
    Uint16 can_bus_off;                     // Number of bus offs
    Uint16 can_abort_tx;                    // Number of error warnings
    Uint16 can_discard;                     // Number of stuff errors
    Uint16 can_form_err;                    // Number of form errors
    Uint16 can_ack_err ;                    // Number of ack errors
    Uint16 can_qeue_full;                   // Number of times qeue filled
    Uint16 can_restarted;                   // Number of times controller restarted
};

extern struct MultiFrameBuf  MFTXBuf;
extern struct SingleFrameBuf SFTXBuf;
extern struct AckFrameBuf    ACKTXBuf;
extern struct BroadFrameBuf    BCRXBuf;
extern struct MSFRXSTATUS    MSRStatus;     // 多帧或单帧报文接收状态
extern struct CANSTATUS      CanStatus;
extern struct CANERRORSTAT   CanError;
extern union  CANMSGID_REG CanMbid;

#ifdef __cplusplus
}
#endif

#endif 
