#ifndef _INC_EXCEPTION_LOG_H
#define _INC_EXCEPTION_LOG_H
/////////////////////////////////////////////
/*异常记录位于DSP可用FRAM起始地址+15KB-128字节处*/
#define EXCEPTION_OFFSET              (0x3C00 - 0x80)
#define EXCEPT_START_ADDR             ((DSP_FRAM_START_ADDR) + (EXCEPTION_OFFSET))

//error_code
#define HARD_ERR_TYPE                  0x10       //硬件异常(CPU提供)
#define EXCEPT_ERR_TYPE                0x20       //软件异常(CPU提供)
#define ERR_TYPE_NO_FPGA_INT           0x31       //FPGA无中断
#define ERR_TYPE_FPGA_INT_ERR          0x32       //FPGA中断异常
#define ERR_TYPE_WAIT_OVER             0x33       //死循环
#define ERR_TYPE_HTM1_INT_ERR          0x34       //HTM1中断异常
#define ERR_CODE_SEGMENT               0x40       //代码段异常
#define ERR_HTM_OVT                    0x41       //HTM_OVT异常
#define ERR_HTM_IVT                    0x42       //HTM_IVT异常
#define ERR_CAN_OVT                    0x43       //CAN_OVT异常
#define ERR_CAN_IVT                    0x44       //CAN_IVT异常
#define ERR_TASKQUE                    0x45       //TASKQUE异常
#define ERR_COMP_PTR                   0x46       //元件指针异常
#define ERR_CONST_DATA                 0x47       //初始化后不再变化的数据发生了异常(系统、应用数据)

#define ERR_DATA_ABORT                 0x50       //数据中止异常
#define ERR_PREFETCH_ABORT             0x51       //取指中止异常
#define ERR_UNDEF_INSTR                0x52       //非法指令异常
#define ERR_L1_PARITY                  0x53       //L1 cache奇偶校验错
#define ERR_L2_PARITY                  0x54       //L2 cache奇偶校验错
#define ERR_OCM_PARITY                 0x55       //OCM奇偶校验错
#define ERR_DDR_ECC                    0x56       //DDR ECC错误

#define MAX_BACKTRACE_LEVEL            8          //函数调用关系回溯级别
#define PC_INFO_NUM                    16         //异常时上招PC指针附近的16个32bit

#define USED_FLAG                      0x5555AAAA //异常记录标志
#define MAX_EXCEPT_NUM                 0x04       //最多记录4条
#define MAX_EXCEPT_INDEX               (MAX_EXCEPT_NUM - 1)

#define FORMAT_VERSION                 100        //1.00版本，格式升级需要修改

#define TIMER_TICK_10MS                3333333UL  //10ms，与定时器的TICK长度相关，zynq7015 Tick是3ns

/*===============================Exception=============================*/

typedef struct 
{
/*data abort*/
    Uint32 DFSR;
    Uint32 DFAR;
/*prefetch abort*/
    Uint32 IFSR;
    Uint32 IFAR;
/*ocm parity err*/
    Uint32 OCM_ERR_STAT;
    Uint32 OCM_ERR_ADDR;
    
/*L2 cache int_stat*/
    Uint32 L2CC_INT_STAT;

/*DDR uncorrectable err*/
    Uint32 UNCORR_ECC_LOG_REG;
    Uint32 UNCORR_ECC_ADDR_REG;
    Uint32 UNCORR_ECC_DATA_REG;
    Uint32 ECC_STATS_REG;
    Uint32 CORR_ECC_LOG_REG;
    Uint32 CORR_ECC_ADDR_REG;
    Uint32 CORR_ECC_DATA_REG;
    
/*Reserved*/
    Uint32 reserved[4];
} EXCEPTION_REC;

typedef struct
{
    Uint32 utc_sec;                               //时标S
    Uint16 local_ms;                              //时标ms
    
    Uint16 err_code;                              //中断源，按bit定义
    
    Uint32 info1;                                 //pc指针
    Uint32 info2;                                 //低8位存储异常类型，最高8位存储核号（从0开始）
    Uint32 info3;                                 //任务函数

    EXCEPTION_REC exception_record;               //详细异常信息
    
    Uint32 pc_context[PC_INFO_NUM];               //PC指针附近的内容
    Uint32 call_stack[MAX_BACKTRACE_LEVEL];       //函数调用栈
}EXCEPTION_UNIT;

typedef struct
{
    Uint32 used_flag;     //异常记录头标志，固定为USED_FLAG
    Uint16 board_type;    //低8位用于区分CPU型号,高8位用于区分插件型号（暂时不用）
    Uint16 format_version;//格式版本，100代表1.00

    Uint16 err_code;
    Uint8  max_num;
    Uint8  curr_wrbuf_ptr;
    EXCEPTION_UNIT  except_save[MAX_EXCEPT_NUM];
}EXCEPTION_BUFF;
/////////////////////////////////////////////////////////
extern EXCEPTION_REC exception_record;
extern EXCEPTION_BUFF  except_status;
extern Uint16 int_trace;
extern Uint32 htm0_int_cnt;
extern Uint32 htm1_int_cnt; 
extern Uint16 htm0_err_irq_cnt;
extern Uint16 htm1_err_irq_cnt;
extern Uint8  fpga_no_int;
extern Uint32 current_func_save;
extern Uint8  htm1_int_err;
/////////////////////////////////////////////////////////
extern void readExceptStatus(void);
extern void checkExceptionStatus(void);
extern void enterIntIsr(Uint8 int_type);
extern void exitIntIsr(Uint8 int_type);

/*-------------------------------------------------------------------------------*/
#endif
