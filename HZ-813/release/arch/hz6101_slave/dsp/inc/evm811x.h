/*
 *  Copyright 2010 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  Definitions & Register
 *
 */


/* ------------------------------------------------------------------------ *
 *  Variable types                                                          *
 * ------------------------------------------------------------------------ */
#define Uint32  unsigned int
#define Uint16  unsigned short
#define Uint8   unsigned char
#define Int32   int
#define Int16   short
#define Int8    char

/* ------------------------------------------------------------------------ *
 *  Software Breakpoint code                                                *
 *      Uses inline assembly command                                        *
 * ------------------------------------------------------------------------ */
#define SW_BREAKPOINT       asm( " .long 0xe1200070" );

/* ------------------------------------------------------------------------ *
 *  Device Control Module                                                   *
 * ------------------------------------------------------------------------ */
//#define CTRL_BASE                0x08140000

/* ------------------------------------------------------------------------ *
 *  Function Renaming                                                       *
 * ------------------------------------------------------------------------ */
#define _wait                   EVM811X_wait
#define _waitusec               EVM811X_waitusec
#define _waitmsec               EVM811X_waitmsec

/* ------------------------------------------------------------------------ *
 *  Prototypes                                                              *
 * ------------------------------------------------------------------------ */
/* Board Initialization */
short EVM811X_init( );

/* Wait Functions */
void EVM811X_wait    ( Uint32 delay );
void EVM811X_waitusec( Uint32 usec );
void EVM811X_waitmsec( Uint32 msec );

/* ------------------------------------------------------------------------ *
 *  Registers                                                               *
 * ------------------------------------------------------------------------ */
/* PLLSS */
#define PLLSS_BASE           0x081C5000                                    // PLLSS Base
#define CLKOUT_MUX           *( volatile Uint32* )( PLLSS_BASE + 0x02E4 )
#define DMTIMER_CLKSRC       *( volatile Uint32* )( PLLSS_BASE + 0x02E0 )

/* Control Module */
#define CTRL_MODULE_BASE_ADDR   0x08140000

#define MMU_CFG             *( volatile Uint32* )( CTRL_MODULE_BASE_ADDR + 0x610 )
#define MLBP_SIG_IO_CTRL    *( volatile Uint32* )( CTRL_MODULE_BASE_ADDR + 0xE18 )
#define MLBP_DAT_IO_CTRL    *( volatile Uint32* )( CTRL_MODULE_BASE_ADDR + 0xE1C )
#define PRCM_DEBUG_ALWON_DEFAULT    *( volatile Uint32* )( CTRL_MODULE_BASE_ADDR + 0x6B0 )
#define INIT_PRIORITY_0     *( volatile Uint32* )( CTRL_MODULE_BASE_ADDR + 0x608 )
#define INIT_PRIORITY_1     *( volatile Uint32* )( CTRL_MODULE_BASE_ADDR + 0x60C )
#define TPTC_CFG            *( volatile Uint32* )( CTRL_MODULE_BASE_ADDR + 0x614 )

/* PRCM */
#define PRCM_BASE                0x08180000

#define CM_ALWON_BASE               (PRCM_BASE + 0x1400)
#define CM_DPLL_BASE                (PRCM_BASE + 0x0300)
#define CM_ETHERNET_CLKSTCTRL       (PRCM_BASE + 0x1404)
#define CM_ALWON_ETHERNET_0_CLKCTRL (PRCM_BASE + 0x15D4)
#define CM_ALWON_ETHERNET_1_CLKCTRL (PRCM_BASE + 0x15D8)

#define CM_ALWON_GPIO_0_CLKCTRL   *( volatile Uint32* )( CM_ALWON_BASE + 0x015C )
#define CM_ALWON_GPIO_1_CLKCTRL   *( volatile Uint32* )( CM_ALWON_BASE + 0x0160 )
#define CM_ALWON_MMCHS_0_CLKCTRL  *( volatile Uint32* )( CM_ALWON_BASE + 0x021C )
#define CM_ALWON_MMCHS_1_CLKCTRL  *( volatile Uint32* )( CM_ALWON_BASE + 0x0220 )
#define CM_ALWON_MMCHS_2_CLKCTRL  *( volatile Uint32* )( CM_ALWON_BASE + 0x0224 )

#define CM_SYSCLK10_CLKSEL        *( volatile Uint32* )( CM_DPLL_BASE  + 0x0024 )



/* TIMER */
#define TIMER2_BASE_ADDR        0x08040000
#define TIMER2_TOCP     *( volatile Uint32* )( TIMER2_BASE_ADDR + 0x10 )
#define TIMER2_TCLR     *( volatile Uint32* )( TIMER2_BASE_ADDR + 0x38 )
#define TIMER2_TCRR     *( volatile Uint32* )( TIMER2_BASE_ADDR + 0x3C )
#define TIMER2_TLDR     *( volatile Uint32* )( TIMER2_BASE_ADDR + 0x40 )
#define TIMER2_TSICR    *( volatile Uint32* )( TIMER2_BASE_ADDR + 0x54 )
#define TIMER2_IRQENABLE_SET    *( volatile Uint32* )( TIMER2_BASE_ADDR + 0x2C )


#define TIMER3_BASE_ADDR        0x08042000
#define TIMER3_TOCP     *( volatile Uint32* )( TIMER3_BASE_ADDR + 0x10 )
#define TIMER3_TCLR     *( volatile Uint32* )( TIMER3_BASE_ADDR + 0x38 )
#define TIMER3_TCRR     *( volatile Uint32* )( TIMER3_BASE_ADDR + 0x3C )
#define TIMER3_TLDR     *( volatile Uint32* )( TIMER3_BASE_ADDR + 0x40 )
#define TIMER3_TSICR    *( volatile Uint32* )( TIMER3_BASE_ADDR + 0x54 )
#define TIMER3_IRQENABLE_SET    *( volatile Uint32* )( TIMER3_BASE_ADDR + 0x2C )
#define TIMER3_IRQENABLE_CLR    *( volatile Uint32* )( TIMER3_BASE_ADDR + 0x30 )
#define TIMER3_TTGR     *( volatile Uint32* )( TIMER3_BASE_ADDR + 0x44 )
#define TIMER3_TMAR     *( volatile Uint32* )( TIMER3_BASE_ADDR + 0x4C )
#define TIMER3_IRQSTATUS        *( volatile Uint32* )( TIMER3_BASE_ADDR + 0x28 )

#define TIMER4_BASE_ADDR        0x08044000
#define TIMER4_TOCP     *( volatile Uint32* )( TIMER4_BASE_ADDR + 0x10 )
#define TIMER4_TCLR     *( volatile Uint32* )( TIMER4_BASE_ADDR + 0x38 )
#define TIMER4_TCRR     *( volatile Uint32* )( TIMER4_BASE_ADDR + 0x3C )
#define TIMER4_TLDR     *( volatile Uint32* )( TIMER4_BASE_ADDR + 0x40 )
#define TIMER4_TSICR    *( volatile Uint32* )( TIMER4_BASE_ADDR + 0x54 )
#define TIMER4_IRQENABLE_SET    *( volatile Uint32* )( TIMER4_BASE_ADDR + 0x2C )
#define TIMER4_IRQENABLE_CLR    *( volatile Uint32* )( TIMER4_BASE_ADDR + 0x30 )
#define TIMER4_TTGR     *( volatile Uint32* )( TIMER4_BASE_ADDR + 0x44 )
#define TIMER4_TMAR     *( volatile Uint32* )( TIMER4_BASE_ADDR + 0x4C )
#define TIMER4_IRQSTATUS        *( volatile Uint32* )( TIMER4_BASE_ADDR + 0x28 )



//PCIe address map (256MB)
#define PCIE_TARGET                     0x20000000
#define PCIE_TARGET_END                 0x2FFFFFFF

#define TXS_PCIE_DDR1_L                 (volatile Uint32 *)(PCIE_TARGET + 0x101000) //TXS_PCIE_DDR1_L
#define TXS_PCIE_DDR1_H                 (volatile Uint32 *)(PCIE_TARGET + 0x101004) //TXS_PCIE_DDR1_H
#define TXS_PCIE_DDR2_L                 (volatile Uint32 *)(PCIE_TARGET + 0x101008) //TXS_PCIE_DDR2_L
#define TXS_PCIE_DDR2_H                 (volatile Uint32 *)(PCIE_TARGET + 0x10100C) //TXS_PCIE_DDR2_H
#define TXS_PCIE_DDR3_L                 (volatile Uint32 *)(PCIE_TARGET + 0x101010) //TXS_PCIE_DDR3_L
#define TXS_PCIE_DDR3_H                 (volatile Uint32 *)(PCIE_TARGET + 0x101014) //TXS_PCIE_DDR3_H
#define TXS_PCIE_DDR4_L                 (volatile Uint32 *)(PCIE_TARGET + 0x101018) //TXS_PCIE_DDR4_L
#define TXS_PCIE_DDR4_H                 (volatile Uint32 *)(PCIE_TARGET + 0x10101C) //TXS_PCIE_DDR4_H



//EDMA base addr
#define SOC_EDMA30CC_0_REGS             (0x09000000)


