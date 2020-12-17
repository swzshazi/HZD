
#ifndef __IN_HZ6101_SMPL_H_
#define __IN_HZ6101_SMPL_H_

#include "hzplatform.h"
#include "hzmodule.h"
#include "ads1247.h"

//板卡通道类型定义,兼容NR4410定值
enum input_type
{
    TYPE_N20_P20mA,     //0:±20mA
    TYPE_N5_P5V,        //1:±5V
    TYPE_N220_P220V,    //2:±220V
    TYPE_N48_P48V,      //3:±48V
    TYPE_N10_P10V,      //4:±10V
    TYPE_PT10,          //5:PT10
    TYPE_PT100,         //6:PT100
    TYPE_PT1000,        //7:PT1000
    TYPE_CU50           //8:CU50
};

//错误代码定义
enum err_bit_define
{
    TYPE_ERR,           //0:通道类型错
    CHNL_ERR,           //1:采样通道异常
    COEF_ERR,           //2:校正系数异常
    PWR_ERR,            //3:AD电源异常
    TEMP_ERR            //4:温度异常
};


#define AD_CHIP_NUM             1       //模拟输入通道数

#define ACTUAL_TYPE_NUM         3       //实际内部的定值数量(0:±20mA;1:±10V;2:±220V)
   
#define NORMAL_SMPL_MODE        0
#define SYS_CHECK_MODE          1
                                
#define NORMAL_MEASURE_MODE     0
#define TEMP_MEASURE_MODE       1
#define RTD_OC_CHECK_MODE       2

#define VDD_THRESHOLD_H         5500   //VDD报警上限，5.5V
#define VDD_THRESHOLD_L         4500   //VDD报警下限，4.5V

#define DATA_UPDATE_PERIOD      100    //数据定时刷新周期,由于通道切换，实际每通道刷新周期为200ms

#define IS_RTD_TYPE(type)       ((type) >= TYPE_PT10)

#define CHAN_NUM                2

//采样元件
typedef struct _SAMPLE_
{
    #include "base.h"

    //输出模拟量
    int32          dc[2];                       //输出变量，电压电流采样放大1000倍，RTD采样放大10倍
    int16          Temperature_c;               //板卡温度*10℃
    int32          max_dc[2];
    int32          min_dc[2];
    
    //输出监视 
    Uint8 Adc_err_flag;                         //1:err,0:OK;    
    Uint8 enable_test;
    
    //参数
    Uint16 cold_down_time[2];                   //输出更新冷却时间
    Uint32 dc_type[CHAN_NUM];
        
    //私有变量
    Uint8 measure_mode;                         //测量模式：正常采样、测温、RTD开路检测
    Uint8 shift_flag;                           //时间片切换标志
    Uint8 pga[CHAN_NUM];
                                                
    Uint32 temp_measure_cnt;                    //测温模式切换计数器
    Uint8  temp_measure_step;                   //测温步骤分解   
                                                
    Uint32 measure_shift_cnt;                   //采样模式切换计数器
                                            
    Uint32 data_update_cnt[2];                  //数据定时刷新周期

} DCSMP;

extern DCSMP *newDCSMP(Component *parent, const char *name);
extern void initDCSMP(DCSMP *dp);
extern void runDCSMP(DCSMP *dp);

#endif
