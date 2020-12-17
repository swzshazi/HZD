
#ifndef _FPGA_ADC8688_
#define _FPGA_ADC8688_

#include "fpga_base.h"


#define ADC_EN                          (volatile Uint16 *)(FPGA_ADC_ADDR+0x0000*2)
#define ADC_CONFIG                      (volatile Uint16 *)(FPGA_ADC_ADDR+0x0002*2)
#define ADC_DLY                         (volatile Uint16 *)(FPGA_ADC_ADDR+0x0003*2)
#define ADC_INIT_CFG                    (volatile Uint16 *)(FPGA_ADC_ADDR+0x0004*2)
#define ADC_INIT_TRIG                   (volatile Uint16 *)(FPGA_ADC_ADDR+0x0005*2)
#define ADC_PERIOD_SET                  (volatile Uint16 *)(FPGA_ADC_ADDR+0x0006*2)

#define ADC_STATE                       (volatile Uint16 *)(FPGA_ADC_ADDR+0x0010*2)
#define ADC_PROG                        (volatile Uint16 *)(FPGA_ADC_ADDR+0x0011*2)
#define ADC_INIT_STATE                  (volatile Uint16 *)(FPGA_ADC_ADDR+0x0012*2)

#define ADC_VERSION_DATE_H              (volatile Uint16 *)(FPGA_ADC_ADDR+0x00F0*2)
#define ADC_VERSION_DATE_L              (volatile Uint16 *)(FPGA_ADC_ADDR+0x00F1*2)
#define ADC_VERSION_ID                  (volatile Uint16 *)(FPGA_ADC_ADDR+0x00F2*2)

#define ADC_SEL_INT1                (0x0000)
#define ADC_SEL_INT0                (0x8000)
#define ADC_DIV_1                   (0x0000)
#define ADC_DIV_2                   (0x0001)
#define ADC_DIV_4                   (0x0002)
#define ADC_DIV_8                   (0x0003)
#define ADC_DIV_16                  (0x0004)

#define RESET_CHIP_REG              (0x8500)
#define ADC_CH0_SELECT              (0x0A00)
#define ADC_CH1_SELECT              (0x0C00)
#define ADC_CH2_SELECT              (0x0E00)
#define ADC_CH3_SELECT              (0x1000)
#define ADC_CH4_SELECT              (0x1200)
#define ADC_CH5_SELECT              (0x1400)
#define ADC_CH6_SELECT              (0x1600)
#define ADC_CH7_SELECT              (0x1800)

#define WRITE_CHIP_REG              (0x0100)
#define READ_CHIP_REG               (0x0000)

#define ADC_RANGE_0                 (0x0000)  //-2.5*4.096   ~  +2.5*4.096
#define ADC_RANGE_1                 (0x0001)  //-1.25*4.096  ~  +1.25*4.096
#define ADC_RANGE_2                 (0x0002)  //-0.625*4.096 ~  +0.625*4.096
#define ADC_RANGE_3                 (0x0005)  //0  ~  +2.5*4.096
#define ADC_RANGE_4                 (0x0006)  //0  ~  +1.25*4.096

typedef struct
{
    Uint16 adc_conv_cnt:8;
    Uint16 adc_dma_error_cnt:4;
    Uint16 reserved_1:2;
    Uint16 adc_fifo_empty:1;
    Uint16 adc_fifo_fill:1;
}ADC_STATE_TYPE;

typedef struct
{
    Uint16 adc_config_cnt:12;
    Uint16 reserved_1:3;
    Uint16 config_busy:1;
}ADC_INIT_STATE_TYPE;

#endif

