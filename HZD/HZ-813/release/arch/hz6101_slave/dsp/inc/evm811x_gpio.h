#include "evm811x.h"

#define GPIO1_BASE          0x0804C000

#define GPIO1_SYSCONFIG     *( volatile Uint32* )( GPIO1_BASE + 0x10 )
#define GPIO1_OE            *( volatile Uint32* )( GPIO1_BASE + 0x0134 ) // 0 = o/p, 1 = i/p
#define GPIO1_DATAIN        *( volatile Uint32* )( GPIO1_BASE + 0x0138 )
#define GPIO1_DATAOUT       *( volatile Uint32* )( GPIO1_BASE + 0x013C )
#define GPIO1_CLEARDATAOUT  *( volatile Uint32* )( GPIO1_BASE + 0x190 )
#define GPIO1_SETDATAOUT    *( volatile Uint32* )( GPIO1_BASE + 0x194 )

#define GPIO1_CTRL          *( volatile Uint32* )( GPIO1_BASE + 0x130 )

#define GPIO1_IRQSTATUS_0    *( volatile Uint32* )( GPIO1_BASE + 0x2C )
#define GPIO1_IRQSTATUS_1    *( volatile Uint32* )( GPIO1_BASE + 0x30 )

#define GPIO1_IRQSTATUS_RAW_0    *( volatile Uint32* )( GPIO1_BASE + 0x24 )
#define GPIO1_IRQSTATUS_RAW_1    *( volatile Uint32* )( GPIO1_BASE + 0x28 )

#define GPIO1_IRQENABLE_SET_0    *( volatile Uint32* )( GPIO1_BASE + 0x34 )
#define GPIO1_IRQENABLE_SET_1    *( volatile Uint32* )( GPIO1_BASE + 0x38 )
#define GPIO1_IRQENABLE_CLR_0    *( volatile Uint32* )( GPIO1_BASE + 0x3C )
#define GPIO1_IRQENABLE_CLR_1    *( volatile Uint32* )( GPIO1_BASE + 0x40 )

#define GPIO1_LEVELDETECT0    *( volatile Uint32* )( GPIO1_BASE + 0x140 )
#define GPIO1_LEVELDETECT1    *( volatile Uint32* )( GPIO1_BASE + 0x144 )
#define GPIO1_RISINGDETECT    *( volatile Uint32* )( GPIO1_BASE + 0x148 )
#define GPIO1_FALLINGDETECT   *( volatile Uint32* )( GPIO1_BASE + 0x14C )

#define GPIO2_BASE          0x081AC000

#define GPIO2_SYSCONFIG     *( volatile Uint32* )( GPIO2_BASE + 0x10 )
#define GPIO2_OE            *( volatile Uint32* )( GPIO2_BASE + 0x0134 ) // 0 = o/p, 1 = i/p
#define GPIO2_DATAIN        *( volatile Uint32* )( GPIO2_BASE + 0x0138 )
#define GPIO2_DATAOUT       *( volatile Uint32* )( GPIO2_BASE + 0x013C )
#define GPIO2_CLEARDATAOUT  *( volatile Uint32* )( GPIO2_BASE + 0x190 )
#define GPIO2_SETDATAOUT    *( volatile Uint32* )( GPIO2_BASE + 0x194 )

#define GPIO2_CTRL          *( volatile Uint32* )( GPIO2_BASE + 0x130 )

#define GPIO2_IRQSTATUS_0    *( volatile Uint32* )( GPIO2_BASE + 0x2C )
#define GPIO2_IRQSTATUS_1    *( volatile Uint32* )( GPIO2_BASE + 0x30 )

#define GPIO2_IRQENABLE_SET_0    *( volatile Uint32* )( GPIO2_BASE + 0x34 )
#define GPIO2_IRQENABLE_SET_1    *( volatile Uint32* )( GPIO2_BASE + 0x38 )
#define GPIO2_IRQENABLE_CLR_0    *( volatile Uint32* )( GPIO2_BASE + 0x3C )
#define GPIO2_IRQENABLE_CLR_1    *( volatile Uint32* )( GPIO2_BASE + 0x40 )

#define GPIO2_LEVELDETECT0    *( volatile Uint32* )( GPIO2_BASE + 0x140 )
#define GPIO2_LEVELDETECT1    *( volatile Uint32* )( GPIO2_BASE + 0x144 )
#define GPIO2_RISINGDETECT    *( volatile Uint32* )( GPIO2_BASE + 0x148 )
#define GPIO2_FALLINGDETECT   *( volatile Uint32* )( GPIO2_BASE + 0x14C )


#define GPIO4_BASE          0x08420000

#define GPIO4_SYSCONFIG     *( volatile Uint32* )( GPIO4_BASE + 0x10 )
#define GPIO4_OE            *( volatile Uint32* )( GPIO4_BASE + 0x0134 ) // 0 = o/p, 1 = i/p
#define GPIO4_DATAIN        *( volatile Uint32* )( GPIO4_BASE + 0x0138 )
#define GPIO4_DATAOUT       *( volatile Uint32* )( GPIO4_BASE + 0x013C )
#define GPIO4_CLEARDATAOUT  *( volatile Uint32* )( GPIO4_BASE + 0x190 )
#define GPIO4_SETDATAOUT    *( volatile Uint32* )( GPIO4_BASE + 0x194 )

#define GPIO4_CTRL          *( volatile Uint32* )( GPIO4_BASE + 0x130 )


