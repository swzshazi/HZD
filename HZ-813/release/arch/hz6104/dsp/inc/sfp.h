#ifndef _SFPH
#define _SFPH

#include "hzplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------  Define  -----------------------------------
#define MODULE_OFFSET_SHIFT_LEN     4       //模块之间寄存器地址间隔0x10，对应左移4
#define MODULE_ENABLE_BIT           0       //模块使能位
#define MAX_SFP_NUM                 16      //最大光模块数量
//----------------------------  Function  -------------------------------------
extern void initSFPMon(void);
extern int16 isSFPOk(Uint8 port);
extern int16 getSFPTemp(Uint8 port, int16 *temp_ptr);
extern int16 getSFPVcc(Uint8 port, int16 *vcc_ptr);
extern int16 getSFPTxPow(Uint8 port, int16 *tx_pow_ptr);
extern int16 getSFPRxPow(Uint8 port, int16 *rx_pow_ptr);
#ifdef __cplusplus
}
#endif

#endif //
