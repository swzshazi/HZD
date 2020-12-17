/* Filename:WirelessRecv.c */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "WirelessRecv.h"
#include "hzplatform.h"
#include "uart.h"

void GetFrame(WirelessRecv *dp);
void If_FPGA_Empty(WirelessRecv *dp);

WirelessRecv *newWirelessRecv(Component *parent, const char *name)
{
    WirelessRecv *dp;
    dp=(WirelessRecv*)calloc(1,sizeof(WirelessRecv));
    if(!dp)
    {
        return NULL;
    }

    dp->type_name="WirelessRecv";
    dp->parent=parent;
    dp->name=name;
    dp->InitComponent=(void*)initWirelessRecv;

    registerComponent((Component*)dp);

    registerVarIn( (Component*)dp, (void**)&(dp->UnpackReadIndex), "UnpackReadIndex", T_UINT16, LEVEL2 );           //接收缓冲读取指示位

    registerVarOut( (Component*)dp, (void*)&(dp->WirelessWriteIndex),  "WirelessWriteIndex", T_UINT16, LEVEL2 );    //接收缓冲写入指示位
    registerVarOut( (Component*)dp, (void*)&(dp->WirelessRecvBuffer),  "WirelessRecvBuffer", T_UINT32, LEVEL2 );     //接收缓冲区
    registerVarOut( (Component*)dp, (void*)&(dp->err_code),  "err_code", T_UINT8, LEVEL2 );                         //错误指示代码
    registerVarOut( (Component*)dp, (void*)&(dp->heartbeat),  "heartbeat", T_UINT8, LEVEL2 );                       //程序心跳

    return dp;
}

INIT_CODE
void initWirelessRecv(WirelessRecv *dp)
{
    //串口配置------COM1，波特率115200，数据长度8位，停止位1位，无奇偶校验位
    configUart16c554(0, 115200, 8, 1, 0);
    //使能接收
    write16C554(0,TX_CFG1,0x03);
    //初始化接收缓冲区写入指示位
    dp->WirelessWriteIndex = 0;             //写位置初始为0，即起始位置
    dp->wr_pos = EQUAL;                     //当前读写位置相同
    dp->WriteReady = NOT_READY;             //未判断FPGA接收区是否为空
    dp->err_loc = NO_ERROR;                 //当前未定位到错误信息
    dp->err_code = NO_ERROR_CODE;           //当前未产生错误代码
    dp->write_next = 1;                     //本轮写入尚未造成数据区溢出
    //初始化数据缓冲区
    memset(dp->WirelessRecvBuffer,0,sizeof(uint8_t)*Buffer_Length);
    //任务等级Lv1,250us
    setTask(1,GetFrame,dp);
}
//错误处理函数（可扩展）
void Error_Handler(WirelessRecv *dp)
{
    dp->err_code = IS_ERROR_CODE;
    switch (dp->err_loc)
    {
    case FPGA_RECV_EMPTY:   //FPGA接收区为空
        dp->err_code = (dp->err_code)+(FPGA_RECV_EMPTY_CODE);
        break;
    case LOOP_CRASH:        //循环次数溢出
        dp->err_code = (dp->err_code)+(LOOP_CRASH_CODE);
    default:
        break;
    }
}
//判断FPGA接收区是否为空
void If_FPGA_Empty(WirelessRecv *dp)
{
    uint8_t uartreg;
    uartreg = read16C554(0,UART_STATUS_REG);    //读串口接收区状态标志位
    uartreg = uartreg&Empty_Check;              //检验其第5位，bit4
    if(uartreg==Empty_Confirm)                  //bit4=1，接收区为空
    {
        dp->WriteReady = NOT_READY;
    }
    else                                        //bit4=0,接收区有数据
    {
        dp->WriteReady = IS_READY;
    }
}
//写位置移动
void WriteNext(WirelessRecv *dp)
{
    if(dp->WirelessWriteIndex==Buffer_Length-1) //到达存储区尾部，回到开头
    {
        dp->WirelessWriteIndex=0;
    }
    else                                        //未到达尾部，向后挪动一位
    {
        dp->WirelessWriteIndex++;
    }
}
//将部分参量重新初始化
void reinitWirelessRecv(WirelessRecv *dp)
{
    dp->wr_pos = EQUAL;
    dp->WriteReady = NOT_READY;
    dp->err_loc = NO_ERROR;
    dp->err_code = NO_ERROR_CODE;
    dp->write_next=1;
}

void GetFrame(WirelessRecv *dp)
{
    if(dp->heartbeat<0xff)
    {
        dp->heartbeat++;
    }
    else
    {
        dp->heartbeat=0;
    }
    If_FPGA_Empty(dp);
    if(dp->WriteReady == NOT_READY)         //接收区为空，结束接收，等待下次中断
    {
        dp->err_loc = FPGA_RECV_EMPTY;      //定位FPGA接收区为空
        Error_Handler(dp);
    }
    else
    {
        int count=0;
        while(dp->write_next==1&&count<2048)
        {
            dp->WirelessRecvBuffer[dp->WirelessWriteIndex] = read16C554(0,RX_DATA_CFG1);
            WriteNext(dp);
            If_FPGA_Empty(dp);
            if(dp->WriteReady==NOT_READY)
            {
                dp->write_next = 0;
                break;
            }
            else
            {
                dp->write_next=1;
            }
            count++;
        }
        if(count>=2048)
        {
            dp->err_loc = LOOP_CRASH;
            Error_Handler(dp);
        }
    }
    reinitWirelessRecv(dp);
}
