/*
 *  Copyright 2008 by Spectrum Digital Incorporated.
 *  All rights reserved.  Property of Spectrum Digital Incorporated.
 */

/*
 *  Linker command file
 *
 */

//-l rts67plus.lib


-stack           0x00002000      /* Stack Size */
-heap            0x00400000      /* Heap Size 4M*/

MEMORY
{
    SHAREDRAM:   o = 0xAF600000  l = 0x00A00000
    DSPNVRAM:    o = 0x110C0000  l = 0x00010000
    
    DRAM:        o = 0xA7000000  l = 0x01000000  /*16M */
    DRAM_APP:    o = 0xA8000000  l = 0x01000000  /*16M */
    DRAM_GS:     o = 0xA9000000  l = 0x02000000  /*32M */
    DRAM_RS:     o = 0xAB000000  l = 0x04000000  /*64M*/
    DRAM_BUF1:   o = 0xAF000000  l = 0x00200000  /*2M */
    DRAM_BUF2:   o = 0xAF200000  l = 0x00200000  /*2M */

    DSPL1P:      o = 0x00E00000  l = 0x00008000			//32KB Cache
    DSPL1D:      o = 0x00F00000  l = 0x00008000			//32KB Cache
    
    
    DSPL2_RSVD     o = 0x00800000  l = 0x00000100
 /*   VECS:        o = 0x00800100  l = 0x00000200 */
    DSPL2_C_INIT:  o = 0x00800200  l = 0x80 
    DSPL2:         o = 0x00800280  l = 0x0002FD80
    DSPL2_Cache:   o = 0x00830000  l = 0x00010000		//64KB Cache
    L3RAM_SV:      o = 0x40300000  l = 0x04000      // 4 * 4 * 1024
    L3RAM_GS:      o = 0x40304000  l = 0x1B000      //24 * 8 * 512        
    L3RAM_AD:      o = 0x4031F000  l = 0x00B00  
    L3RAM_RS:      o = 0x4031FB00  l = 0x00500  
}

/*
L1_data_a
L2_data
SDRAM0_BSZ
init_code
rtm_code
*/

SECTIONS
{
    .text:_c_int00      >   DSPL2_C_INIT 
    .text:vecs          >   DSPL2
    .bss                >   DSPL2
    .cinit              >   DSPL2
    .cio                >   DSPL2
    .const              >   DRAM
    .stack              >   DSPL2
    .sysmem             >   DRAM
    .text               >   DRAM
    .switch             >   DSPL2
	GROUP
	{
		.neardata
		.rodata
		.bss
	} 		>   DSPL2
    .far                >   DRAM
    .fardata            >   DRAM
    .rtm_code           >   DSPL2
    .rtm_data           >   DSPL2
    .my_sect            >   SHAREDRAM
    .init_code          >   DRAM
    .init_data          >   DRAM
    .heap               >   DRAM
    .SDRAM0_BSZ         >   DRAM
    .rx_data_buf        >   DRAM_GS
    .rx_app_buf         >   DRAM_APP
    .rx_smv_buf         >   L3RAM_SV
    .rx_ad_buf          >   L3RAM_AD
    .rx_gs_buf          >   L3RAM_GS
    .rx_l3_buf          >   L3RAM_RS
    .arm_msg_buf        >   DRAM_BUF1
    .dsp_msg_buf        >   DRAM_BUF2
    .dsp_nvram          >   DSPNVRAM
}
