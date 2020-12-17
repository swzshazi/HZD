/********************************************************************
*           File Name   : fpga_dlq_hz6104.h                             *
*           Date        : 2020-05-09                                *
*           Written by  : zqy                               *
*           Description : peripharl cfg addr       *
********************************************************************/

#ifndef _FPGA_DLQ_HZ6104_
#define _FPGA_DLQ_HZ6104_


#include "fpga_base.h"

/***********************    adc   **************************/
// SPI  AD7689
#define ADC_CFG_ADDR             	  (volatile Uint16 *)(FPGA_ADC_ADDR + (0x0<<2))  
#define ADC_PEIROD_CFG_ADDR           (volatile Uint16 *)(FPGA_ADC_ADDR + (0x1<<2))  

// dilta-ADC
#define DELTA_ADC_CFG_ADDR            (volatile Uint16 *)(FPGA_ADC_ADDR + (0x8<<2))   //   W/R
#define DELTA_ADC_FILTER1_ADDR        (volatile Uint16 *)(FPGA_ADC_ADDR + (0x9<<2))   //     R
#define DELTA_ADC_FILTER2_ADDR        (volatile Uint16 *)(FPGA_ADC_ADDR + (0xa<<2))   //     R
#define DELTA_ADC_FILTER3_ADDR        (volatile Uint16 *)(FPGA_ADC_ADDR + (0xb<<2))   //     R
#define DELTA_ADC_FILTER4_ADDR        (volatile Uint16 *)(FPGA_ADC_ADDR + (0xc<<2))   //     R
#define DELTA_ADC_FILTER5_ADDR        (volatile Uint16 *)(FPGA_ADC_ADDR + (0xd<<2))   //     R
#define DELTA_ADC_FILTER6_ADDR        (volatile Uint16 *)(FPGA_ADC_ADDR + (0xe<<2))   //     R


/***********************    UART   **************************/
#define UART_TX_DATA_ADDR             (volatile Uint16 *)(FPGA_UART_MOD_ADDR + (0x00<<2))  //   W
#define UART_CFG0_ADDR                (volatile Uint16 *)(FPGA_UART_MOD_ADDR + (0x03<<2))  //   W
#define UART_CFG1_ADDR                (volatile Uint16 *)(FPGA_UART_MOD_ADDR + (0x04<<2))  //   W
#define UART_CFG2_ADDR                (volatile Uint16 *)(FPGA_UART_MOD_ADDR + (0x05<<2))  //   W
                                                                               
#define UART_RX_DATA_ADDR             (volatile Uint16 *)(FPGA_UART_MOD_ADDR + (0x10<<2))  //     R
#define UART_RD_CFG0_ADDR             (volatile Uint16 *)(FPGA_UART_MOD_ADDR + (0x13<<2))  //     R
#define UART_RD_CFG1_ADDR             (volatile Uint16 *)(FPGA_UART_MOD_ADDR + (0x14<<2))  //     R
#define UART_RD_CFG2_ADDR             (volatile Uint16 *)(FPGA_UART_MOD_ADDR + (0x15<<2))  //     R

/***********************    PWM   **************************/
#define PWM_CFG_ADDR                  (volatile Uint32 *)(FPGA_PWM_MOD_ADDR + (0x00<<2))  //   W/R
#define PWM_PERIOD_RD_ADDR            (volatile Uint32 *)(FPGA_PWM_MOD_ADDR + (0x04<<2))  //     R
#define PWM_HIGH_PULSEWIDTH_ADDR      (volatile Uint32 *)(FPGA_PWM_MOD_ADDR + (0x05<<2))  //     R
                                                                              
/***********************    IIC   **************************/                 
#define IIC_CFG_ADDR                  (volatile Uint16 *)(FPGA_I2C_MOD_ADDR + (0x00<<2))  //   W/R
#define IIC_STATUS0_RD_ADDR           (volatile Uint16 *)(FPGA_I2C_MOD_ADDR + (0x08<<2))  //     R
#define IIC_RX0_LIGPWR_ADDR           (volatile Uint16 *)(FPGA_I2C_MOD_ADDR + (0x09<<2))  //     R
#define IIC_TX0_LIGPWR_ADDR           (volatile Uint16 *)(FPGA_I2C_MOD_ADDR + (0x0A<<2))  //     R
#define IIC_STATUS1_RD_ADDR           (volatile Uint16 *)(FPGA_I2C_MOD_ADDR + (0x10<<2))  //     R
#define IIC_RX1_LIGPWR_ADDR           (volatile Uint16 *)(FPGA_I2C_MOD_ADDR + (0x11<<2))  //     R
#define IIC_TX1_LIGPWR_ADDR           (volatile Uint16 *)(FPGA_I2C_MOD_ADDR + (0x12<<2))  //     R

/***********************    USB OTG   **************************/
#define USB_CFG_ADDR                  (volatile Uint16 *)(FPGA_USB_MOD_ADDR + (0x00<<2))  //   W/R




#endif

