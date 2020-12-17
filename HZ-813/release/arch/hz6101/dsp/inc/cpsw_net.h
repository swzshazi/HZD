#ifndef  CPSW_NET_H
#define  CPSW_NET_H

#include "common_types.h"

typedef struct
{
    Uint16   type;
    Uint8    res[2];
    int    (*emac_rx_callback)(Uint8 *buf);
}EMAC_RX_FUNC;



#endif
