/* Filename:WirelessRecv.h */
#ifndef _WIRELESSRECV_H_
#define _WIRELESSRECV_H_

#include <stdint.h>
#include "hzmodule.h"

#define Empty_Confirm 0x10
#define Empty_Check 0x10
#define NOT_READY 0
#define IS_READY 1

//错误类型
#define NO_ERROR 0
#define FPGA_RECV_EMPTY 1
#define LOOP_CRASH 2
//错误代码
#define NO_ERROR_CODE 0
#define IS_ERROR_CODE 0x80
#define FPGA_RECV_EMPTY_CODE 0x01
#define LOOP_CRASH_CODE 0x02

//读写相对位置指示
#define EQUAL 0
#define FWRITE 1
#define FREAD 2

//数据缓冲区状态
#define BUFFER_ERROR 0xa1
#define BUFFER_ENOUGH 0xa2
//最短帧长
#define FRAMELENGTH 48
//覆盖阈值
#define COVERLENGTH 5

#define Buffer_Length 1024          //数据总缓冲区长度

typedef struct WirelessRecv
{
    #include "base.h"

    //输入
    uint16_t *UnpackReadIndex;
    //输出
    uint16_t WirelessWriteIndex;
    uint8_t WirelessRecvBuffer[Buffer_Length];
    //接收区是否为空标志
    uint8_t WriteReady;
    //错误类型指示位
    uint8_t err_loc;
    //错误总代码
    uint8_t err_code;
    //读写相对位置
    uint8_t wr_pos;
    //数据缓冲区状态

    //连续写入数据标志
    uint8_t write_next;
    //程序心跳
    uint8_t heartbeat;
}WirelessRecv;

extern WirelessRecv *newWirelessRecv(Component *parent, const char *name);
extern void initWirelessRecv(WirelessRecv *dp);

#endif
