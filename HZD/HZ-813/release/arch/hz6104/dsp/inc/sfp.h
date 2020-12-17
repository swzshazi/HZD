#ifndef _SFPH
#define _SFPH

#include "hzplatform.h"

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------  Define  -----------------------------------
#define MODULE_OFFSET_SHIFT_LEN     4       //ģ��֮��Ĵ�����ַ���0x10����Ӧ����4
#define MODULE_ENABLE_BIT           0       //ģ��ʹ��λ
#define MAX_SFP_NUM                 16      //����ģ������
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
