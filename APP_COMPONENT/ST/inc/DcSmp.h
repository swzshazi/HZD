
#ifndef __IN_HZ6101_SMPL_H_
#define __IN_HZ6101_SMPL_H_

#include "hzplatform.h"
#include "hzmodule.h"
#include "ads1247.h"

//�忨ͨ�����Ͷ���,����NR4410��ֵ
enum input_type
{
    TYPE_N20_P20mA,     //0:��20mA
    TYPE_N5_P5V,        //1:��5V
    TYPE_N220_P220V,    //2:��220V
    TYPE_N48_P48V,      //3:��48V
    TYPE_N10_P10V,      //4:��10V
    TYPE_PT10,          //5:PT10
    TYPE_PT100,         //6:PT100
    TYPE_PT1000,        //7:PT1000
    TYPE_CU50           //8:CU50
};

//������붨��
enum err_bit_define
{
    TYPE_ERR,           //0:ͨ�����ʹ�
    CHNL_ERR,           //1:����ͨ���쳣
    COEF_ERR,           //2:У��ϵ���쳣
    PWR_ERR,            //3:AD��Դ�쳣
    TEMP_ERR            //4:�¶��쳣
};


#define AD_CHIP_NUM             1       //ģ������ͨ����

#define ACTUAL_TYPE_NUM         3       //ʵ���ڲ��Ķ�ֵ����(0:��20mA;1:��10V;2:��220V)
   
#define NORMAL_SMPL_MODE        0
#define SYS_CHECK_MODE          1
                                
#define NORMAL_MEASURE_MODE     0
#define TEMP_MEASURE_MODE       1
#define RTD_OC_CHECK_MODE       2

#define VDD_THRESHOLD_H         5500   //VDD�������ޣ�5.5V
#define VDD_THRESHOLD_L         4500   //VDD�������ޣ�4.5V

#define DATA_UPDATE_PERIOD      100    //���ݶ�ʱˢ������,����ͨ���л���ʵ��ÿͨ��ˢ������Ϊ200ms

#define IS_RTD_TYPE(type)       ((type) >= TYPE_PT10)

#define CHAN_NUM                2

//����Ԫ��
typedef struct _SAMPLE_
{
    #include "base.h"

    //���ģ����
    int32          dc[2];                       //�����������ѹ���������Ŵ�1000����RTD�����Ŵ�10��
    int16          Temperature_c;               //�忨�¶�*10��
    int32          max_dc[2];
    int32          min_dc[2];
    
    //������� 
    Uint8 Adc_err_flag;                         //1:err,0:OK;    
    Uint8 enable_test;
    
    //����
    Uint16 cold_down_time[2];                   //���������ȴʱ��
    Uint32 dc_type[CHAN_NUM];
        
    //˽�б���
    Uint8 measure_mode;                         //����ģʽ���������������¡�RTD��·���
    Uint8 shift_flag;                           //ʱ��Ƭ�л���־
    Uint8 pga[CHAN_NUM];
                                                
    Uint32 temp_measure_cnt;                    //����ģʽ�л�������
    Uint8  temp_measure_step;                   //���²���ֽ�   
                                                
    Uint32 measure_shift_cnt;                   //����ģʽ�л�������
                                            
    Uint32 data_update_cnt[2];                  //���ݶ�ʱˢ������

} DCSMP;

extern DCSMP *newDCSMP(Component *parent, const char *name);
extern void initDCSMP(DCSMP *dp);
extern void runDCSMP(DCSMP *dp);

#endif
