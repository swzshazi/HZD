#ifndef _GPIO_H
#define _GPIO_H

#ifdef __cplusplus
extern "C" {
#endif


#include "xgpiops.h"
#include "board.h"
//--------------------------------  Define  -----------------------------------
#define GPIO_DEVICE_ID XPAR_PS7_GPIO_0_DEVICE_ID


//--------------------------------  Variable  -------------------------------


//--------------------------------  Function  ---------------------------------
extern int initCpuGpio(void);
extern void gpioSetDirection(Uint32 io_no, Uint8 direction);
extern void gpioSetOutput(Uint32 io_no);
extern void gpioClearOutput(Uint32 io_no);
extern void gpioToggleOutput(Uint32 io_no);
extern Uint8 gpioReadInput(Uint32 io_no);


#ifdef __cplusplus
}
#endif

#endif // 
