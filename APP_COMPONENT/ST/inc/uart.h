#ifndef _UART_H_
#define _UART_H_

#define COMB1_BASE_ADDR					((volatile Uint16 *)0x120C0000) 		//串口模块基地址
#define COMBx_OFFSET					(0x100)   								//dsp偏移地址

//串口配置模块寄存器//<<1
#define UART_CTRL_EN					(0x03)   	//	RS485方向控制，1：发送使能, 0：接收使能
#define TX_CFG1							(0x04)   	//	只写: 接收，发送功能使能与禁止
#define TX_CFG2							(0x05)		//	只写: CRC校验使能选择，CRC校验模式选择，设置波特率

//串口状态模块寄存器
#define TX_READ_DEN		   				(0x13)
#define RX_CFG1							(0x14)		//只读: 接收，发送功能使能与禁止
#define RX_CFG2							(0x15)		//只读: CRC校验使能选择，CRC校验模式选择，设置波特率

#define UART_STATUS_REG					(0x16)		//只读:当前是否接收数据，接收区是否已满，接收区是否已空，发送区是否已满，发送区是否已空标
#define Txcnt_REG_LO					(0x18)		//只读:已发送数据的计数值低8位
#define Txcnt_REG_HI					(0x19)		//只读:已发送数据的计数值高8位

#define Rxcnt_All_REG_LO				(0x1A)		//只读:已读取数据的计数值低8位
#define Rxcnt_All_REG_HI				(0x1B)		//只读:已读取数据的计数值高8位

#define Rxcnt_OK_REG_LO					(0x1C)		//只读:已读取有效数据的计数值低8位
#define Rxcnt_OK_REG_HI					(0x1D)		//只读:已读取有效数据的计数值高8位

#define Rxcnt_Fail_REG_LO				(0x1E)		//只读:已读取无效数据的计数值低8位
#define Rxcnt_Fail_REG_HI				(0x1F)		//只读:已读取无效数据的计数值高8位

//串口数据寄存器
#define TX_DATA_CFG1					(0x00)		//只写: 串行数据发送区
#define RX_DATA_CFG1					(0x10) 		//只读: 串行数据接收区

#define     TX_ENABLE							0x01
#define     RX_ENABLE							0x02

#define		SET_COM_PARA					0x8001
#define     SET_TX_RX_DIR					0x8002
#define     QUERY_RX_STATE					0x8003
#define     QUERY_TX_STATE   				0x8004

#define     TX_DIR								 1
#define     RX_DIR								 2

extern void write16C554(int uart_no, Uint8 reg_addr, Uint8 data);
extern Uint8 read16C554(int uart_no, Uint8 reg_addr);
extern void configUart16c554(Uint8 portno, Uint32 bps, Uint8 datanum, Uint8 stopbit, Uint8 parity);
extern void  uart_rx_poll(char port, char *buf);
extern void uartdev_write(char port, char *buffer, int size, int offset);

#endif
