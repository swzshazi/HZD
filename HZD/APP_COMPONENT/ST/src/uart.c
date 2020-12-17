#include "hzplatform.h"
#include "common_types.h"
#include "uart.h"

// 端口号，寄存器地址，写入数据
void write16C554(int uart_no, Uint8 reg_addr, Uint8 data)
{	
	*(COMB1_BASE_ADDR + uart_no * COMBx_OFFSET + reg_addr) = data;
}

Uint8 read16C554(int uart_no, Uint8 reg_addr)
{
    unsigned char data;
	data = *(COMB1_BASE_ADDR + uart_no * COMBx_OFFSET +reg_addr);
    return  data;
}

// 端口号，波特率，数据长度，停止位，奇偶校验位
void configUart16c554(Uint8 portno, Uint32 bps, Uint8 datanum, Uint8 stopbit, Uint8 parity)
{
	Uint8 tmp=0x00;//bit2~bit0表示波特率，bit4~bit3表示奇偶校验

	switch(bps)
	{
		case 2400: 
			tmp = 0x02; //2400
			break;
		
		case 4800: 
			tmp = 0x03; //4800
			break;
		
		case 9600: 
			tmp = 0x04; //9600
			break;
		
		case 19200: 
			tmp = 0x05; //19200
			break;
		
		case 57600: 
			tmp = 0x06; //57600
			break;
		
		case 115200: 
			tmp = 0x07; //115200
			break;
		
		default:
			tmp = 0x04; //9600
			break;
	}

	//default=0 list=none_parity odd_parity even_parity
	switch(parity)
   	{
		case 0:
			tmp|=0x10;	//none_parity ，bit4=1,bit3=0
			break; 	

		case 1: 
			tmp|=0x00;		//奇校验 bit4=0,bit3=0
			break; 

		case 2:
			tmp|=0x08;	//偶校验 bit4=0,bit3=1
			break;	

		default:	
			tmp|=0x10;	//none_parity ，bit4=1,bit3=0
			break; 	
	}

	write16C554(portno, TX_CFG2, tmp); 	   //设置奇偶校验 和 比特率
}


// 读保存
/*
void  uart_rx_poll(char port, char *buf)
{

	state = read16C554(port,UART_STATUS_REG);
	while(( state & 0x10 ) == 0x00)
	{	
		byte = read16C554(port,RX_DATA_CFG1);
		// 保存byte
		state = read16C554(port,UART_STATUS_REG);
	}
}*/

// 写操作
/*
int uartdev_write(char port, char *buffer, int size, int offset)
{
	int  i;
		
	i = 0;
	while((read16C554(port,UART_STATUS_REG) & 0x02) == 0)
	{
		write16C554(port,TX_DATA_CFG1,buffer[i++]);
		if( i == size)
			break;		
	}

    return i;
}*/

// 切换方向
/*
if( TX_DIR)
	write16C554(((UART_PRIV *)(dev->priv_data))->port, UART_CTRL_EN, 1);
else
	write16C554(((UART_PRIV *)(dev->priv_data))->port, UART_CTRL_EN, 0);	
*/

