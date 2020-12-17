#ifndef _INC_EXCEPTION_LOG_H
#define _INC_EXCEPTION_LOG_H
/////////////////////////////////////////////
/*�쳣��¼λ��DSP����FRAM��ʼ��ַ+15KB-128�ֽڴ�*/
#define EXCEPTION_OFFSET              (0x3C00 - 0x80)
#define EXCEPT_START_ADDR             ((DSP_FRAM_START_ADDR) + (EXCEPTION_OFFSET))

//error_code
#define HARD_ERR_TYPE                  0x10       //Ӳ���쳣(CPU�ṩ)
#define EXCEPT_ERR_TYPE                0x20       //����쳣(CPU�ṩ)
#define ERR_TYPE_NO_FPGA_INT           0x31       //FPGA���ж�
#define ERR_TYPE_FPGA_INT_ERR          0x32       //FPGA�ж��쳣
#define ERR_TYPE_WAIT_OVER             0x33       //��ѭ��
#define ERR_TYPE_HTM1_INT_ERR          0x34       //HTM1�ж��쳣
#define ERR_CODE_SEGMENT               0x40       //������쳣
#define ERR_HTM_OVT                    0x41       //HTM_OVT�쳣
#define ERR_HTM_IVT                    0x42       //HTM_IVT�쳣
#define ERR_CAN_OVT                    0x43       //CAN_OVT�쳣
#define ERR_CAN_IVT                    0x44       //CAN_IVT�쳣
#define ERR_TASKQUE                    0x45       //TASKQUE�쳣
#define ERR_COMP_PTR                   0x46       //Ԫ��ָ���쳣
#define ERR_CONST_DATA                 0x47       //��ʼ�����ٱ仯�����ݷ������쳣(ϵͳ��Ӧ������)

#define ERR_DATA_ABORT                 0x50       //������ֹ�쳣
#define ERR_PREFETCH_ABORT             0x51       //ȡָ��ֹ�쳣
#define ERR_UNDEF_INSTR                0x52       //�Ƿ�ָ���쳣
#define ERR_L1_PARITY                  0x53       //L1 cache��żУ���
#define ERR_L2_PARITY                  0x54       //L2 cache��żУ���
#define ERR_OCM_PARITY                 0x55       //OCM��żУ���
#define ERR_DDR_ECC                    0x56       //DDR ECC����

#define MAX_BACKTRACE_LEVEL            8          //�������ù�ϵ���ݼ���
#define PC_INFO_NUM                    16         //�쳣ʱ����PCָ�븽����16��32bit

#define USED_FLAG                      0x5555AAAA //�쳣��¼��־
#define MAX_EXCEPT_NUM                 0x04       //����¼4��
#define MAX_EXCEPT_INDEX               (MAX_EXCEPT_NUM - 1)

#define FORMAT_VERSION                 100        //1.00�汾����ʽ������Ҫ�޸�

#define TIMER_TICK_10MS                3333333UL  //10ms���붨ʱ����TICK������أ�zynq7015 Tick��3ns

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
    Uint32 utc_sec;                               //ʱ��S
    Uint16 local_ms;                              //ʱ��ms
    
    Uint16 err_code;                              //�ж�Դ����bit����
    
    Uint32 info1;                                 //pcָ��
    Uint32 info2;                                 //��8λ�洢�쳣���ͣ����8λ�洢�˺ţ���0��ʼ��
    Uint32 info3;                                 //������

    EXCEPTION_REC exception_record;               //��ϸ�쳣��Ϣ
    
    Uint32 pc_context[PC_INFO_NUM];               //PCָ�븽��������
    Uint32 call_stack[MAX_BACKTRACE_LEVEL];       //��������ջ
}EXCEPTION_UNIT;

typedef struct
{
    Uint32 used_flag;     //�쳣��¼ͷ��־���̶�ΪUSED_FLAG
    Uint16 board_type;    //��8λ��������CPU�ͺ�,��8λ�������ֲ���ͺţ���ʱ���ã�
    Uint16 format_version;//��ʽ�汾��100����1.00

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
