#ifndef _INC_FPGA_BASE_H
#define _INC_FPGA_BASE_H


//--------------------------------  Define  emif space-----------------------------------

#define FPGA_EMIF_BASE_ADDR  (0x12000000)
#define FPGA_PCIE_BASE_ADDR  (0x20000000)

//Master & Slave
#define FPGA_TASK1_ADDR           (FPGA_EMIF_BASE_ADDR)                 // FPGA起始地址
#define SIZE_OF_FPGA_TASK1        ((0x10)<<1)                           // 寄存器范围

#define FPGA_TASK2_ADDR           (FPGA_EMIF_BASE_ADDR+(0x0010<<1))     // FPGA起始地址
#define SIZE_OF_FPGA_TASK2        ((0x10)<<1) 

//Master only
#define FPGA_SYN_ADDR             (FPGA_EMIF_BASE_ADDR+(0x0100<<1))       // FPGA起始地址
#define SIZE_OF_FPGA_SYN          ((0x100)<<1)      

//Master only
#define FPGA_SFP_ADDR             (FPGA_EMIF_BASE_ADDR+(0x2000<<1))       // FPGA起始地址
#define SIZE_OF_FPGA_SFP          ((0x200)<<1)     
 

//Slave only
#define FPGA_SHARE_RAM0_ADDR      (FPGA_EMIF_BASE_ADDR+(0x0200<<1) )      // FPGA起始地址
#define SIZE_OF_FPGA_RAM0         ((0x200)<<1)       

//Slave only
#define FPGA_SHARE_RAM1_ADDR      (FPGA_EMIF_BASE_ADDR+(0x0400<<1) )      // FPGA起始地址
#define SIZE_OF_FPGA_RAM1          ((0x200)<<1)    						  // 寄存器范围

//Slave only
#define FPGA_RGMII_ADDR           (FPGA_EMIF_BASE_ADDR+(0x0800<<1))       // FPGA起始地址
#define SIZE_OF_FPGA_RGMII        ((0x10)<<1)      



//Master only
#define FPGA_CAN_ADDR             (FPGA_EMIF_BASE_ADDR+(0x0E00<<1) )                       // FPGA起始地址
#define SIZE_OF_FPGA_CAN          ((0x100)<<1)       

//Master only
#define FPGA_GPIO_ADDR            (FPGA_EMIF_BASE_ADDR+(0x0F00<<1) )                       // FPGA起始地址
#define SIZE_OF_FPGA_GPIO         ((0x100)<<1)                         // 寄存器范围


//Master & Slave
#define FPGA_ADC7606_ADDR         (FPGA_EMIF_BASE_ADDR+(0x1000<<1))       // ADC 起始地址
#define SIZE_OF_FPGA_ADC7606      ((0x1000)<<1)                           // 寄存器范围
 
//Master only
#define FPGA_GEN_DMA_ADDR         (FPGA_EMIF_BASE_ADDR+(0x08000<<1))      // 通用DMA起始地址
#define SIZE_OF_FPGA_GEN_DMA      ((0x8000)<<1)                           // 寄存器范围

//Master only
#define FPGA_STATION_ADDR         (FPGA_EMIF_BASE_ADDR+(0x10000<<1))       // 过程层模块起始地址
#define SIZE_OF_FPGA_STATION      ((0x10000)<<1)    

//Master & Slave
#define FPGA_NETWORK_ADDR         (FPGA_EMIF_BASE_ADDR+(0x20000<<1))       // 过程层模块起始地址
#define SIZE_OF_FPGA_NETWORK      ((0x10000)<<1)                            // 寄存器范围

        
//Master & Slave
#define FPGA_TX_CHC_CFG_ADDR      (FPGA_EMIF_BASE_ADDR+(0x30000<<1))       // FPGA起始地址
#define SIZE_OF_FPGA_TX_CHC_CFG   ((0x10)<<1)   

//Master & Slave
#define FPGA_TX_CHC_MASK_ADDR     (FPGA_EMIF_BASE_ADDR+(0x30400<<1))       // FPGA起始地址
#define SIZE_OF_FPGA_TX_CHC_MASK  ((0x400)<<1)   

//Master & Slave
#define FPGA_TX_CHC_RAM_A_ADDR    (FPGA_EMIF_BASE_ADDR+(0x31000<<1))       // FPGA起始地址

//Master & Slave
#define FPGA_TX_CHC_RAM_B_ADDR    (FPGA_EMIF_BASE_ADDR+(0x31800<<1))       // FPGA起始地址

//Master
#define MASTER_TX_CHC_RAM_A_ADDR    (0x200C0000)     
#define SIZE_OF_FPGA_RAM_A          (0x400)  

//Master
#define MASTER_TX_CHC_RAM_B_ADDR    (0x200C0800)     
#define SIZE_OF_FPGA_RAM_B          (0x400)


//Master & Slave
#define FPGA_IEC_RXMOD_ADDR       (FPGA_EMIF_BASE_ADDR+(0x40000<<1))       // FPGA起始地址
#define SIZE_IEC_RXMOD_CFG        ((0x1000)<<1)

//Master & Slave
#define FPGA_IEC_TXMOD_ADDR       (FPGA_EMIF_BASE_ADDR+(0x51400<<1))       // FPGA起始地址, 当前未使用
#define SIZE_OF_TXMOD_CFG         ((0x200)<<1)

#define FPGA_IEC_TX_DAT_ADDR      (FPGA_PCIE_BASE_ADDR+(0x40000<<2)) 
#define SIZE_OF_TXMOD_DAT         ((0x1000)<<2)

#define FPGA_CMD_TXMOD_CFG_ADDR   (FPGA_EMIF_BASE_ADDR+(0x51200<<1))
#define SIZE_OF_CMD_TXMOD_CFG     ((0x0100)<<1)
 
#define FPGA_CMD_TXMOD_DAT_ADDR   (FPGA_PCIE_BASE_ADDR+(0x41020<<2))        
#define SIZE_OF_CMD_TXMOD_DAT     ((0x0010)<<1)

//控保接收专用60044-8模块
#define FPGA_PCP_PPR_RXMOD_ADDR   (FPGA_EMIF_BASE_ADDR+(0x50000<<1))       
#define SIZE_OF_FPGA_PCP_PPR_RX   ((0x0100)<<1)

//控保接收解析模块
#define FPGA_PCP_PPR_RXCMD_OUT    (FPGA_EMIF_BASE_ADDR+(0x50100<<1))       
#define SIZE_OF_FPGA_PCP_PPR_CMD  ((0x0200)<<1)

//FEU控制子机反馈信息接收
#define FPGA_FEU_RXMOD_ADDR       (FPGA_EMIF_BASE_ADDR+(0x50300<<1))       
#define SIZE_OF_FPGA_FEU_RX       ((0x0100)<<1)

//本体保护、三取二
#define FPGA_MU_PR_MOD_ADDR       (FPGA_EMIF_BASE_ADDR+(0x50400<<1))       
#define SIZE_OF_FPGA_MU_PR        ((0x0100)<<1)

//耗能支路状态监视
#define FPGA_MOV_MOD_ADDR         (FPGA_EMIF_BASE_ADDR+(0x50500<<1))       
#define SIZE_OF_FPGA_MOV_MOD      ((0x0100)<<1)

//UPS
#define FPGA_UPS_MOD_ADDR         (FPGA_EMIF_BASE_ADDR+(0x50600<<1))       
#define SIZE_OF_FPGA_UPS_MOD      ((0x0100)<<1)

//reserve
#define FPGA_RES_MOD_ADDR         (FPGA_EMIF_BASE_ADDR+(0x50700<<1))       
#define SIZE_OF_FPGA_RES_MOD      ((0x0100)<<1)

//DBC发送数据给控保系统(配置地址)
#define FPGA_DBC_TO_PCP_CFG_ADDR      (FPGA_EMIF_BASE_ADDR+(0x51000<<1))       
#define SIZE_OF_FPGA_DBC_TO_PCP_ADDR   ((0x0200)<<1)

//DBC发送数据给控保系统(数据地址)
#define FPGA_DBC_TO_PCP_ADDR      (FPGA_EMIF_BASE_ADDR+(0x51100<<1))  
#define FPGA_DBC_TO_PCP_STS_ADDR  (FPGA_EMIF_BASE_ADDR+(0x511F0<<1))  
#define SIZE_OF_FPGA_DBC_TO_PCP_DATA   ((0x0200)<<1)

//DBC发送数据给FEU子机
#define FPGA_DBC_TO_FEU_ADDR      (FPGA_EMIF_BASE_ADDR+(0x51200<<1))       
#define SIZE_OF_FPGA_DBC_TO_FEU   ((0x0100)<<1)

//DBC系统间通信
#define FPGA_DBC_AB_COM_ADDR      (FPGA_EMIF_BASE_ADDR+(0x52000<<1))       
#define SIZE_OF_FPGA_DBC_AB_COM   ((0x1000)<<1)

//DBC控保系统接口测试模块(配置地址)
#define FPGA_DBC_TEST_PCP_CFG_ADDR      (FPGA_EMIF_BASE_ADDR+(0x51800<<1))       
#define SIZE_OF_FPGA_DBC_TEST_PCP_ADDR   ((0x0200)<<1)
//DBC控保系统接口测试模块(数据地址)
#define FPGA_DBC_TEST_PCP_ADDR      (FPGA_EMIF_BASE_ADDR+(0x54400<<1))       
#define SIZE_OF_FPGA_DBC_TEST_PCP_DATA   ((0x00010)<<1)

//DBC测试模块模式选择
#define FPGA_DBC_TEST_MOD_SEL_ADDR      (FPGA_EMIF_BASE_ADDR+(0x51810<<1)) 

//DBC版本寄存器
#define FPGA_DBC_Version_ADDR      (FPGA_EMIF_BASE_ADDR+(0x51A00<<1)) 

//控保发送主从互校mask寄存器
#define FPGA_DBC_TX_IEC_MASK_ADDR      (FPGA_EMIF_BASE_ADDR+(0x53010<<1)) 
#define SIZE_OF_FPGA_DBC_TX_IEC_MASK   ((0x10)<<1)

//FEU发送主从互校mask寄存器
#define FPGA_DBC_TX_SMC_MASK_ADDR      (FPGA_EMIF_BASE_ADDR+(0x53000<<1)) 
#define SIZE_OF_FPGA_DBC_TX_SMC_MASK   ((0x10)<<1)


//DBC发送数据给故障录波器(配置地址)
#define FPGA_DBC_TO_FR_CFG_ADDR      (FPGA_EMIF_BASE_ADDR+(0x54000<<1))       
#define SIZE_OF_FPGA_DBC_TO_FR_ADDR   ((0x0080)<<1)

//DBC发送数据给故障录波器(数据地址)
#define FPGA_DBC_TO_FR_ADDR      (FPGA_EMIF_BASE_ADDR+(0x54100<<1))  
#define SIZE_OF_FPGA_DBC_TO_FR_DATA   ((0x0080)<<1)


#define pMSmvLen       (volatile Uint16 *)FPGA_TX_CHC_CFG_ADDR
#define pMMaskAddr     (volatile Uint16 *)FPGA_TX_CHC_MASK_ADDR
#define pMRAM_A        (volatile Uint16 *)MASTER_TX_CHC_RAM_A_ADDR
#define pMRAM_B        (volatile Uint16 *)MASTER_TX_CHC_RAM_B_ADDR

#define pSSmvLen       (volatile Uint16 *)FPGA_TX_CHC_CFG_ADDR
#define pSMaskAddr     (volatile Uint16 *)FPGA_TX_CHC_MASK_ADDR
#define pSRAM_A        (volatile Uint16 *)FPGA_TX_CHC_RAM_A_ADDR
#define pSRAM_B        (volatile Uint16 *)FPGA_TX_CHC_RAM_B_ADDR

#endif // end by hz 
