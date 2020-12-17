/****************************************Copyright (c)**************************************************
**                                       合智电力
**                                      平台软件部
**                                 http://www.hz-ieds.com
**
**  文件名: ads1247_smp.c
**  版  本: V1.00
**  作  者: 
**  日  期: 2017年3月1日
**  描  述: 1247采样元件
**  修改记录：
**  ====|==============|========|=========================================== 
**  版本|      日期    |  作者  | 修改内容                      
**  ====|==============|========|===========================================  
**  1.00|   2017-3-1   |    | 初次创建                                            
********************************************************************************************************/

/**********************************  Include  ********************************/
#include <stdlib.h>
#include "DcSmp.h"

/**********************************  Define  *********************************/             
#define TEMP_MEASURE_SHIFT_CNT  10000                            //任务周期1ms，10S测温一次
#define RTD_CHECK_SHIFT_CNT     100                              //任务周期1ms，100ms检查一次RTD   
                                                             
#define MAX_FILTER_CNT          30                               //最大消抖次数
#define FILTER_COEF_STEP        15                               //滤波系数变化步长
#define MAX_FILTER_COEF         150                              //最大滤波系数
                                                             
#define SMPL_DATA_BUF_SIZE      8                                //采样缓冲区大小
#define SHIFT_LEN               3                                //用于将除法改为移位操作
 
#define NOW     1                                                //当前值
#define PREV    0                                                //上次值

/******************************  Local Variable  *****************************/
//采样相关变量
Uint8 data_index[2] = {0,0};                                     //[0]:通道0数据索引;[1]:通道1数据索引
volatile int32 AD_Buf[2][SMPL_DATA_BUF_SIZE];                    //各通道采样缓冲区
volatile int32 channel_buf[2];                                   //各通道当前采样值 
volatile int32 data_sums[2];                                     //各通道采样累加和
volatile int32 AD_Avg[2];                                        //各通道采样平均值

//系统监视相关变量
Uint8 ch_smpl_error = 0;                                      //通道采样错误
Uint8 ch_pwr_error = 0;                                       //通道电源错误
Uint8 ch_coef_error = 0;                                      //补偿系数错误
Uint8 error_flag = 0;                                         //总错误标志
Uint32 error_code = 0;                                        //错误码,按bit定义
Uint8 adc_data_jump_cnt[2];                                   //跳码计数
                                                                            
//滤波器相关变量                                              
Uint8 filter_coef[2]= {0};                                    //RC滤波系数
Uint8 filter_cnt[2] = {0};                                    //消抖计数器
int32 delta_value[2][2];                                      //通道采样变化量，[0]历史值;[1]:当前值
int32 filter_out[2][2];                                       //RC滤波器输出，[0]历史值;[1]:当前值
int32 filter_in[2] = {0};                                     //RC滤波器输入

/******************************  Extern Variable  ****************************/
extern int16 ch_offset[2];                                    //零漂
extern Uint16 ch_gain[2];                                     //增益

/******************************  Local Function  *****************************/
void  getInitBoardTempSmplData(const int32 *smpl_avg);
Uint8 checkADPwr(void);
Uint8 getSamples(int32 *smpl_buf);
void  processSamples(int32 *smpl_avg);
void  fix_filter_coef(Uint8 *coef, Uint8 *cnt, int32 *delta_data);
void  rc_filter(Uint8 coef, int32 data_in, int32 *data_out);
/******************************  Extern Function  ****************************/
extern void delayUs(Uint32 count);

/******************************  code  ****************************/
/***********************************************************************************************************
**函数原型      :   void changeMeasureMode(Uint8 mode, const int32 *dc_type)
**输入参数      :   mode：测量模式，分为正常采样模式、测量AVDD、测量DVDD、测量VREF、测量板卡温度
                    dc_type：通道类型
**输出参数      :   无
**返回值        :   无
**功能描述      :   根据当前测量状态设置基准源和AD芯片测量模式
************************************************************************************************************/
void changeMeasureMode(Uint8 mode, const int32 *dc_type)
{
    //其他测量使用内部基准输入作为基准
    ads1247SetMeasureMode(mode, ADS1247_ONBOARD_REF);//if ((mode == ADS1247_NORMAL_MEASURE) && IS_RTD_TYPE(dc_type[i])),RTD测量使用REF0输入作为基准
}


/***********************************************************************************************************
**函数原型      :   Uint8 checkVddPwr(Uint8 pwr)
**输入参数      :   pwr：测量电压类型
                        ADS1247_AVDD_MEASURE
                        ADS1247_DVDD_MEASURE
**输出参数      :   无
**返回值        :   电源错误状态，对应通道为1说明电源异常
**功能描述      :   测试AD芯片电源电压是否正常
************************************************************************************************************/

Uint8 checkVddPwr(Uint8 pwr)
{
    Uint8 i = 0;
    Uint8 power_error = 0;
    int32 chip_vdd = 0;                   //AD芯片电源     
    int32 smpl_avg[2] = {0};              //各通道采样平均值
    
    //测试VDD
    changeMeasureMode(pwr, NULL);
    delayUs(500);
 
    processSamples((int32 *)smpl_avg);
    
    if (smpl_avg[0] >= 0)
    {
        chip_vdd = (smpl_avg[0]>>10);
    }
    else
    {
        chip_vdd = -(-smpl_avg[0]>>10);
    }

    if ((chip_vdd > VDD_THRESHOLD_H) || (chip_vdd < VDD_THRESHOLD_L))
    {
        power_error |= BIT(0);
    }
        
    return power_error;
}

/***********************************************************************************************************
**函数原型      :   Uint8 checkADPwr(void)
**输入参数      :   无
**输出参数      :   无
**返回值        :   电源状态，对应bit位置1说明该路电源异常
**功能描述      :   测试AD芯片AVDD/DVDD电源电压是否正常
************************************************************************************************************/
Uint8 checkADPwr(void)
{
    Uint8 pwr_error = 0;
    
    //测试AVDD
    pwr_error = checkVddPwr(ADS1247_AVDD_MEASURE);
    
    //测试DVDD
    pwr_error |= checkVddPwr(ADS1247_DVDD_MEASURE);
    
    if (pwr_error)
    {
        error_code |= BIT(PWR_ERR);
    }
    
    return pwr_error;
}


/***********************************************************************************************************
**函数原型      :   int16 calcBoardTemperature(Uint8 start_no, Uint8 end_no, const int32 *smpl_buf)
**输入参数      :   start_no：起始通道
                    end_no：结束通道
                    smpl_buf：各通道温度采样值
**输出参数      :   无
**返回值        :   板卡摄氏温度*10,正常范围-40~150，异常则返回0x7fff
**功能描述      :   计算当前板卡温度
************************************************************************************************************/
int16 calcBoardTemperature(Uint8 start_no, Uint8 end_no, const int32 *smpl_buf)
{
    Uint8 i = 0;
    Uint8 valid_ch_num = 0;
    int16 chip_temp[AD_CHIP_NUM] = {0};//AD芯片温度
    int32 temp_sum = 0;
            
    for (i = start_no; i <= end_no; i++)
    {
        if ((ch_smpl_error & BIT(i)) != 0)
        {
            continue;
        }
        
        if (smpl_buf[i] >= 0)
        {
            chip_temp[i] = ((smpl_buf[i]*395)>>16) - 2665; 
        }
        else
        {
            chip_temp[i] = -((-smpl_buf[i]*395)>>16) - 2665;
        }
        valid_ch_num++;
        temp_sum += chip_temp[i];
    }

    //计算所有通道温度平均值
    if (valid_ch_num != 0)
    {
        return (int16)(temp_sum/valid_ch_num);
    }
    else
    {
        return 0x7FFF;//异常则返回最大值，用于区分正常温度
    }
}

/***********************************************************************************************************
**函数原型      :   void getInitBoardTempSmplData(const int32 *smpl_avg)
**输入参数      :   无
**输出参数      :   smpl_avg：所有通道采样数据平均值
**返回值        :   无
**功能描述      :   获取初始化状态下各AD芯片温度原始采样值
************************************************************************************************************/
void getInitBoardTempSmplData(const int32 *smpl_avg)
{
    changeMeasureMode(ADS1247_TEMP_MEASURE, NULL);
    
    delayUs(500);
 
    processSamples((int32 *)smpl_avg);
}

/***********************************************************************************************************
**函数原型      :   Uint8 checkBoardTemperature(int16 *ptemperature_c, const int32 *smpl_avg)
**输入参数      :   smpl_avg：所有通道采样数据平均值
**输出参数      :   ptemperature_c：摄氏温度存储地址
**返回值        :   温度错误标志，1表示温度异常，超过150℃或低于-40℃
**功能描述      :   计算板卡温度并判断其合法性
************************************************************************************************************/
Uint8 checkBoardTemperature(int16 *ptemperature_c, const int32 *smpl_avg)
{
    Uint8 error = 0;
    static Uint8 temp_err_cnt = 0;
    
    *ptemperature_c = calcBoardTemperature(0, 0, (int32 *)smpl_avg);
    if ((*ptemperature_c > 1500) || (*ptemperature_c < -400))//合法温度-40~150℃
    {
        temp_err_cnt++;
        if (temp_err_cnt >= 3)
        {
            temp_err_cnt = 0;
            error = 1;
            error_code |= BIT(TEMP_ERR);
        }
    }
    else 
    {
        temp_err_cnt = 0;
        error = 0;
        error_code &= ~BIT(TEMP_ERR);
    }

    return error;
}

/***********************************************************************************************************
**函数原型      :   Uint8 getSamples(int32 *smpl_buf)
**参数说明      :   
**输出参数      :   smpl_bu:各通道采样值
**返回值        :   通道状态
**功能描述      :   读取采样值
************************************************************************************************************/
Uint8 getSamples(int32 *smpl_buf)
{
    Uint8 error = 0;
    int32 ad_result = 0;
    
    //设置采样模式
    if (ch_smpl_error != 0)
    {
        return 1;
    }
    
    if (ads1247ReadADResult(&ad_result) == 0)
    {
        if (ad_result & 0x00800000)//负值
        {                   
            ad_result |= 0xff000000;
        } 
        smpl_buf[0] = ad_result;
        adc_data_jump_cnt[0] = 0;
        error &= ~(BIT(0));
    }
    else
    {
        adc_data_jump_cnt[0]++;
        if (adc_data_jump_cnt[0] >= 3)
        {
            adc_data_jump_cnt[0] = 0;
            error |= BIT(0);//运行过程中损坏
        }
    }    
       
    return error;
}

/***********************************************************************************************************
**函数原型      :   void processSamples(int32 *smpl_avg)
**参数说明      :   start_no:起始通道号
                    end_no:截止通道号
**输出参数      :   smpl_avg:各通道采样平均值
**返回值        :   无
**功能描述      :   初始化阶段进行采样并进行SMPL_DATA_BUF_SIZE次平均滤波
************************************************************************************************************/ 
int32 smpl_buf[2] = {0,0x12345678}; 
void processSamples(int32 *smpl_avg)
{
    Uint8 i;
    Uint8 j;     
    int32 smpl_sum = 0;    
    
    
    //采样SMPL_DATA_BUF_SIZE次
    for (i = 0; i < SMPL_DATA_BUF_SIZE; i++)
    {
        ads1247StartConvert();
        delayUs(1500);
        getSamples((int32 *)smpl_buf); 
        
        smpl_sum += smpl_buf[0];        
    }
    
    if (smpl_sum >= 0)
    {
        smpl_avg[0] = smpl_sum>>SHIFT_LEN;
    }
    else
    {
        smpl_avg[0] = -((-smpl_sum)>>SHIFT_LEN);
    }   
}

/***********************************************************************************************************
**函数原型      :   void fix_filter_coef(Uint8 *coef, Uint8 *cnt, int32 *delta_data)
**参数说明      :   cnt:消抖计数器
                    delta_data:采样值变化量
**输出参数      :   coef:滤波系数 0~255
**返回值        :   无
**功能描述      :   调整一阶滤波系数
************************************************************************************************************/
void fix_filter_coef(Uint8 *coef, Uint8 *cnt, int32 *delta_data)
{
    //相邻两次变化方向相同，认为是真实变化
    if (((delta_data[NOW] >= 0) && (delta_data[PREV] >= 0)) || ((delta_data[NOW] < 0) && (delta_data[PREV] < 0)))
    {
        //消抖滤波
        if (*cnt < MAX_FILTER_CNT)
        {
            if (abs(delta_data[NOW]) > 200)
            {
                *cnt += 10;  
            }       
            else
            {
                *cnt += 1;  
            }
        }   
        else
        {
            *cnt = 0;
            if (*coef < MAX_FILTER_COEF - FILTER_COEF_STEP)
            {
                *coef += FILTER_COEF_STEP;  
            }
            else
            {
                *coef = MAX_FILTER_COEF;
            }
        }
    }           
    else//认为是干扰
    {
        *cnt = 0;
        *coef = 0;
    }
       
    delta_data[PREV] = delta_data[NOW];
}

/***********************************************************************************************************
**函数原型      :   void rc_filter(Uint8 coef, int32 data_in, int32 *data_out)
**参数说明      :   coef:滤波系数 0~MAX_FILTER_COEF
                    data_in:滤波输入值
**输出参数      :   data_out:滤波输出值,存储当前值和历史值
**返回值        :   无
**功能描述      :   一阶RC滤波
************************************************************************************************************/
void rc_filter(Uint8 coef, int32 data_in, int32 *data_out)
{
    //一阶低通滤波
    //if (x(n) < y(n-1)) y(n)=y(n-1)-(y(n-1)-x(n))*coef/256
    //else y(n)=y(n-1)+(x(n)-y(n-1))*coef/256
    //+128为了四舍五入，提高精度
    if (data_in < data_out[PREV])
    {
        data_out[NOW] = data_out[PREV] - (((data_out[PREV] - data_in)*coef + 128)>>8);
    }
    else
    {
        data_out[NOW] = data_out[PREV] + (((data_in - data_out[PREV])*coef + 128)>>8);
    }
    
    data_out[PREV] = data_out[NOW];
}



/***********************************************************************************************************
**函数原型      :   void setInternalPGA(Uint8 smpl_mode, const int32 *dc_type)
**输入参数      :   smpl_mode:采样模式
                        自检模式
                        正常采样模式
**输出参数      :   无
**返回值        :   无
**功能描述      :   根据采样模式设置PGA和采样率
************************************************************************************************************/
void setInternalPGA(Uint8 smpl_mode, const int32 *dc_type)
{
    //设置采样模式
    ads1247Config(ADC_GAIN_1, ADC_SPS_1000);//自检状态下PGA均设置成1    
}


/***********************************************************************************************************
**函数原型      :   void setRtdCurrentOut(Uint8 ch_no, Uint8 current)
**输入参数      :   ch_no：通道号
                    current：输出激励电流大小
                        IOUT_OFF   
                        IOUT_50uA  
                        IOUT_100uA 
                        IOUT_250uA 
                        IOUT_500uA 
                        IOUT_750uA 
                        IOUT_1000uA
                        IOUT_1500uA
**输出参数      :   无
**返回值        :   无
**功能描述      :   设置RTD激励电流输出
************************************************************************************************************/
void setRtdCurrentOut(Uint8 current)
{
    ads1247SetIexcPin(AIN3, AIN2);
    ads1247SetIexcVal(current);
}

/***********************************************************************************************************
**函数原型      :   void setNormalSmpl(NR4418_SMPL *dp)
**输入参数      :   dp:元件指针
**输出参数      :   无
**返回值        :   无
**功能描述      :   将各通道设置成正常采样模式
************************************************************************************************************/
void setNormalSmpl(DCSMP *dp)
{
    int i = 0;
    
    for(i=0; i< CHAN_NUM; i++)
    {
        if(dp->dc_type[i] == TYPE_N5_P5V)
            dp->pga[i] = ADC_GAIN_16;
            //dp->pga[i] = ADC_GAIN_8;
        else
            dp->pga[i] = ADC_GAIN_1;    
    }
    
    //测量使用内部基准输入作为基准
    ads1247SetMeasureMode(ADS1247_NORMAL_MEASURE, ADS1247_ONBOARD_REF);
    delayUs(500);
    
    //设置PGA，用于正常采样
    ads1247Config(dp->pga[0], ADC_SPS_5);
    //设置采样通道
    ads1247SelectADChannel(AIN0, AIN2);
    delayUs(500);
}

/***********************************************************************************************************
**函数原型      :   Uint8 initAdChannels(void)
**输入参数      :   无
**输出参数      :   无
**返回值        :   初始化结果，对应位为1表示相应的AD芯片异常
**功能描述      :   初始化AD芯片，使能内部基准
************************************************************************************************************/
Uint8 initAdChannels(void)
{
    Uint8 i = 0;
    Uint8 error = 0;
    
    if(ads1247Init() != 0)
    {
        error |= BIT(0);
    }
    
    ads1247EnableInternalRef();     //固定使能内部参考
    
    if (error)
    {
        error_code |= BIT(CHNL_ERR);
    }
    
    return error;
}

/***********************************************************************************************************
**函数原型      :   void systemSelfCheck(DCSMP *dp)
**输入参数      :   dp：元件指针
**输出参数      :   无
**返回值        :   无
**功能描述      :   系统自检
************************************************************************************************************/
void systemSelfCheck(DCSMP *dp)
{
    //初始化各芯片
    ch_smpl_error = initAdChannels();
    delayUs(1000);//等待设置生效
    
    //设置PGA，用于自检
    ads1247Config(ADC_GAIN_1, ADC_SPS_1000);                    //自检状态下PGA均设置成1
    delayUs(500); //等待设置生效
    
    //检测AD电源
    ch_pwr_error = checkADPwr();
    dp->Adc_err_flag = (ch_pwr_error != 0);
    
    //检测初始板卡温度
   // getInitBoardTempSmplData((int32 *)AD_Avg);
    //checkBoardTemperature(&dp->Temperature_c, (int32 *)AD_Avg);
    
    //更新总错误标志
    error_flag = (error_code != 0);
}

/*****************************************************************************************
**函数原型      :   void updateOutputData(NR4418_SMPL *dp, int32 new_val, Uint8 ch_no)
**参数说明      :   dp-采样元件地址;
                    new_val-新采样计算值
                    ch_no-采样通道号
**返回值        :   无
**说    明      :   定时周期到或突变量超过0.8%更新输出
                    突变量触发数据更新后，启动冷却计时，在此期间不再更新输出
*****************************************************************************************/
void updateOutputData(DCSMP *dp, int32 new_val, Uint8 ch_no)
{
    Uint16 delta_threshold = 0;
    static Uint16 cold_down_cnt[AD_CHIP_NUM] = {0};
    
    //突变量超过当前值的0.8%立即上送
    delta_threshold = (abs(dp->dc[ch_no])>>7);//0.8%
    if (delta_threshold < 3)
    {
        delta_threshold = 3;
    }
    if (abs(new_val - dp->dc[ch_no]) > delta_threshold)
    {
        //此处清零，防止多余的定时上送
        dp->data_update_cnt[ch_no] = 0;
        //冷却时间结束后才能再次更新输出
        if (cold_down_cnt[ch_no] == 0)
        {
            cold_down_cnt[ch_no] = (dp->cold_down_time[ch_no]>>1);
            dp->dc[ch_no] = new_val;
        }
    }
    
    //冷却时间计时
    if (cold_down_cnt[ch_no] > 0)
    {
        cold_down_cnt[ch_no]--;
    }

    //定时上送
    if (dp->data_update_cnt[ch_no]++ >= DATA_UPDATE_PERIOD)
    {
        dp->data_update_cnt[ch_no] = 0;
        dp->dc[ch_no] = new_val;
    }
}

/***********************************************************************************************************
**函数原型      :   void getBoardTemperature(NR4418_SMPL *dp)
**输入参数      :   dp：元件指针
**输出参数      :   无
**返回值        :   无
**功能描述      :   获取板卡温度状态
************************************************************************************************************/
void getBoardTemperature(DCSMP *dp)
{
    switch (dp->temp_measure_step)
    {
        case 0:
            // 切换至测温模式
            setInternalPGA(SYS_CHECK_MODE, NULL);
            changeMeasureMode(ADS1247_TEMP_MEASURE, NULL);
            dp->temp_measure_step++;
        break;
        
        case 1:
            //启动转换
            ads1247StartConvert(); 
            dp->temp_measure_step++;
        break;
            
        case 2:
            //读取结果并计算温度
            ch_smpl_error |= getSamples((int32 *)channel_buf);
            checkBoardTemperature(&dp->Temperature_c, (int32 *)channel_buf);
            dp->temp_measure_step++;
        break;
        
        case 3:
            //切回正常采样模式
            setInternalPGA( NORMAL_SMPL_MODE, NULL);
            changeMeasureMode(ADS1247_NORMAL_MEASURE, NULL);
            dp->temp_measure_step++;
        break;
        
        case 4:
            ads1247StartConvert();
            dp->measure_mode = NORMAL_MEASURE_MODE;
            dp->temp_measure_step = 0;
        break;

        default :
        break;  
    }
}

/***********************************************************************************************************
**函数原型      :   void changeMeasureObject(NR4418_SMPL *dp)
**输入参数      :   dp：元件指针
**输出参数      :   无
**返回值        :   无
**功能描述      :   切换采样对象：正常采样、测量板卡温度、测量RTD基准电压
************************************************************************************************************/
void changeMeasureObject(DCSMP *dp)
{
    dp->measure_shift_cnt++;
    
    //切换成测温模式
    if ((dp->measure_shift_cnt % TEMP_MEASURE_SHIFT_CNT) == 0)
    {
        dp->measure_mode = TEMP_MEASURE_MODE;
        
        return;
    }   
}

/***********************************************************************************************************
**函数原型      :   void getNormalSamples(NR4418_SMPL *dp)
**输入参数      :   dp：元件指针
**输出参数      :   无
**返回值        :   无
**功能描述      :   获取正常采样模式下的采样值
************************************************************************************************************/
void getNormalSamples(DCSMP *dp)
{
    Uint8   i,j = 0;    
    int32   no_error_data = 0;
    int32   out_data = 0;
    Uint32  index    = 0;
    static  Uint16 flag = 0;
    
    flag ++;
    if(flag  >  300)
        flag = 0;
    else
        return;
    
    ch_smpl_error |= getSamples((int32 *)channel_buf);
    
    //切换采样通道
    if (dp->shift_flag)
    {
        // 切换到AIN0，AIN2通道
        ads1247Config(dp->pga[0],ADC_SPS_5);
        ads1247SelectADChannel(AIN0, AIN2);
    }
    else 
    {
        // 切换到AIN1，AIN2通道
        ads1247Config(dp->pga[1],ADC_SPS_5); 
        ads1247SelectADChannel(AIN1, AIN2);
    }     
    
    i = dp->shift_flag;
    
    //通道异常或通道输入类型整定错误，闭锁该通道输出
    if ((ch_smpl_error & BIT(0)) != 0)
    {
        //dp->dc[i]= 0;
    }
    else
    {
        //循环递推平均滤波
        index = data_index[i];
        AD_Buf[i][index] = channel_buf[0];
        
        if(dp->enable_test == 1)
        {
            if(channel_buf[0] > dp->max_dc[i])
                dp->max_dc[i] = channel_buf[0];
            else if(channel_buf[0] < dp->min_dc[i])
                dp->min_dc[i] = channel_buf[0];        
        }
        else
        {
            dp->max_dc[i] = -8388607;
            dp->min_dc[i] = 8388607;        
        }
        
        data_sums[i] = 0;
        for (j = 0; j < SMPL_DATA_BUF_SIZE; j++)
        {
            data_sums[i] += AD_Buf[i][j];
        }
        //使用移位减轻CPU负载
        if (data_sums[i] >= 0)
        {
            AD_Avg[i] = data_sums[i]>>SHIFT_LEN;
        }
        else
        {
            AD_Avg[i] = -((-data_sums[i])>>SHIFT_LEN);
        }
        
        dp->dc[i] = AD_Avg[i];
        
        //递推平均滤波后进行一阶RC滤波
        //filter_in[i] = AD_Avg[i];
        //计算本次采样值与上次滤波结果的差值
        //delta_value[i][NOW] = filter_in[i] - filter_out[i][PREV];
        //调整滤波系数
        //fix_filter_coef(&filter_coef[i], &filter_cnt[i], delta_value[i]);
        //一阶RC低通滤波
        //rc_filter(filter_coef[i], filter_in[i], filter_out[i]);
        
        //实际值折算
        //no_error_data = calcActualValue(i, filter_out[i][NOW], dp->dc_type[i]);
        
        //out_data = no_error_data;
        
        //超过变化门槛或定时周期到更新输出
        //updateOutputData(dp, out_data, i);
    }
    
    ads1247StartConvert();
    
    //环形缓冲区，循环指针
    data_index[i] = (data_index[i] + 1) & (SMPL_DATA_BUF_SIZE - 1);
    //切换时间片
    dp->shift_flag = !dp->shift_flag;
                  

    //changeMeasureObject(dp);
}

/***********************************************************************************************************
**函数原型      :   void updateErrorFlags(NR4418_SMPL *dp)
**输入参数      :   dp：元件指针
**输出参数      :   无
**返回值        :   无
**功能描述      :   更新错误标志
************************************************************************************************************/
void updateErrorFlags(DCSMP *dp)
{
    Uint8 i = 0;
    
    //兼容4410，对外只送总的出错标志
    if (ch_smpl_error != 0)
    {
        dp->Adc_err_flag = 1;
        error_code |= BIT(CHNL_ERR);
    }
    
    //更新错误标志
    error_flag = (error_code != 0);
}

/***********************************************************************************************************
**函数原型      :   DCSMP *newDCSMP(Component *parent, const char *name)
**参数说明      :   parent-父元件地址，name－本元件名；
**返回值        :   新元件内存地址；
**说   明       :   构造函数，为采样元件分配一段内存；
************************************************************************************************************/
DCSMP *newDCSMP(Component *parent, const char *name)
{
    char tp_str[100];
    Uint8 i = 0;
    DCSMP *self = (DCSMP *)calloc(1, sizeof(DCSMP));
    if(!self) return NULL;

    self->parent        = (Component*)parent;
    self->name          =  name;
    self->type_name     = "DCSMP";
    self->InitComponent = (void *)initDCSMP;

    registerComponent((Component*)self);
    
    registerVarOut((Component *)self, (void *)&(self->Temperature_c), "brd_temp", T_INT16, LEVEL4);
    registerVarOut((Component *)self, (void *)&(self->Adc_err_flag),  "adc_err", T_UINT8, LEVEL4);
    registerVarOut((Component *)self, (void *)&(self->enable_test),   "test_enable", T_UINT8, LEVEL2);
    
    for(i=0;i<2;i++)
    {
        sprintf(tp_str, "dc_%d", i+1);
        registerVarOut((Component *)self, (void *)&(self->dc[i]),  tp_str, T_INT32, LEVEL2);    
        
        sprintf(tp_str, "max_dc_%d", i+1);
        registerVarOut((Component *)self, (void *)&(self->max_dc[i]),  tp_str, T_INT32, LEVEL2);    
        
        sprintf(tp_str, "min_dc_%d", i+1);
        registerVarOut((Component *)self, (void *)&(self->min_dc[i]),  tp_str, T_INT32, LEVEL2);    
        
        sprintf(tp_str, "dc%d_type default=0 option=1 list=4~20mA 0~5V", i+1);
        registerParameter((Component *)self, (void *)&(self->dc_type[i]), tp_str, T_STR_L);
    }
    
    return self;
}

/*****************************************************************************************
**函数原型      :   void initDCSMP(DCSMP *dp)
**参数说明      :   元件地址
**返回值        :   无
**说    明      :   初始化元件参数
*****************************************************************************************/
void initDCSMP(DCSMP *dp)
{
    //系统自检
    systemSelfCheck(dp);
    
    //设置正常采样参数
    setNormalSmpl(dp);
    
    dp->shift_flag  = 0;
    dp->enable_test = 0;
    dp->max_dc[0]      = -8388607;
    dp->max_dc[1]      = -8388607;
    dp->min_dc[0]      =  8388607;
    dp->min_dc[1]      =  8388607;
    dp->measure_mode = NORMAL_MEASURE_MODE;
    ads1247StartConvert();

    //加入level2任务链表，周期1ms
    setTask(2, runDCSMP, dp);
}

/*****************************************************************************************
**函数原型      :   void runNR4418_SMPL(NR4418_SMPL *dp)
**参数说明      :   dp-采样元件地址
**返回值        :   无
**说    明      :   本函数用于采样模拟量输入回路
*****************************************************************************************/
void runDCSMP(DCSMP *dp)
{
    
    switch (dp->measure_mode)
    {
        case NORMAL_MEASURE_MODE:
            getNormalSamples(dp);
            break;
        default:
            break;
    }

    updateErrorFlags(dp);
}
/* end of file */
