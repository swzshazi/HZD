#ifndef _LED_H
#define _LED_H

#ifdef __cplusplus
extern "C" {
#endif


#include "xgpiops.h"
#include "board.h"
//--------------------------------  Define  -----------------------------------


//--------------------------------  Variable  -------------------------------


//--------------------------------  Function  ---------------------------------
extern void lightLed(Uint8 led_num, Uint8 led_ctrl_cmd);


#ifdef __cplusplus
}
#endif

#endif //
