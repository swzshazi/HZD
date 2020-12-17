
#ifndef _INC_FPGA_MODULE_H
#define _INC_FPGA_MODULE_H


#include "fpga_gen_dma.h"           // 通用DMA控制器
#include "fpga_gpio.h"              // GPIO模块
#include "fpga_mmb.h"               // MMB控制器
#include "fpga_adc8688.h"           // ADC采样
#include "fpga_time.h"              // 对时模块
#include "fpga_network.h"           // 过程层模块
#include "fpga_sfp.h"               // 光强监视 
#include "fpga_link.h"              // serdes高速接口
#include "fpga_soclink.h"           // SOC间通信链路
#include "fpga_iec60044-8.h"
#include "fpga_peripheral.h"        // 新增外设接口，for 刀闸 断路器

#endif 
