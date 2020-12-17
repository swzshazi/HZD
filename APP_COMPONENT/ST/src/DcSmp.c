/****************************************Copyright (c)**************************************************
**                                       ���ǵ���
**                                      ƽ̨�����
**                                 http://www.hz-ieds.com
**
**  �ļ���: ads1247_smp.c
**  ��  ��: V1.00
**  ��  ��: 
**  ��  ��: 2017��3��1��
**  ��  ��: 1247����Ԫ��
**  �޸ļ�¼��
**  ====|==============|========|=========================================== 
**  �汾|      ����    |  ����  | �޸�����                      
**  ====|==============|========|===========================================  
**  1.00|   2017-3-1   |    | ���δ���                                            
********************************************************************************************************/

/**********************************  Include  ********************************/
#include <stdlib.h>
#include "DcSmp.h"

/**********************************  Define  *********************************/             
#define TEMP_MEASURE_SHIFT_CNT  10000                            //��������1ms��10S����һ��
#define RTD_CHECK_SHIFT_CNT     100                              //��������1ms��100ms���һ��RTD   
                                                             
#define MAX_FILTER_CNT          30                               //�����������
#define FILTER_COEF_STEP        15                               //�˲�ϵ���仯����
#define MAX_FILTER_COEF         150                              //����˲�ϵ��
                                                             
#define SMPL_DATA_BUF_SIZE      8                                //������������С
#define SHIFT_LEN               3                                //���ڽ�������Ϊ��λ����
 
#define NOW     1                                                //��ǰֵ
#define PREV    0                                                //�ϴ�ֵ

/******************************  Local Variable  *****************************/
//������ر���
Uint8 data_index[2] = {0,0};                                     //[0]:ͨ��0��������;[1]:ͨ��1��������
volatile int32 AD_Buf[2][SMPL_DATA_BUF_SIZE];                    //��ͨ������������
volatile int32 channel_buf[2];                                   //��ͨ����ǰ����ֵ 
volatile int32 data_sums[2];                                     //��ͨ�������ۼӺ�
volatile int32 AD_Avg[2];                                        //��ͨ������ƽ��ֵ

//ϵͳ������ر���
Uint8 ch_smpl_error = 0;                                      //ͨ����������
Uint8 ch_pwr_error = 0;                                       //ͨ����Դ����
Uint8 ch_coef_error = 0;                                      //����ϵ������
Uint8 error_flag = 0;                                         //�ܴ����־
Uint32 error_code = 0;                                        //������,��bit����
Uint8 adc_data_jump_cnt[2];                                   //�������
                                                                            
//�˲�����ر���                                              
Uint8 filter_coef[2]= {0};                                    //RC�˲�ϵ��
Uint8 filter_cnt[2] = {0};                                    //����������
int32 delta_value[2][2];                                      //ͨ�������仯����[0]��ʷֵ;[1]:��ǰֵ
int32 filter_out[2][2];                                       //RC�˲��������[0]��ʷֵ;[1]:��ǰֵ
int32 filter_in[2] = {0};                                     //RC�˲�������

/******************************  Extern Variable  ****************************/
extern int16 ch_offset[2];                                    //��Ư
extern Uint16 ch_gain[2];                                     //����

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
**����ԭ��      :   void changeMeasureMode(Uint8 mode, const int32 *dc_type)
**�������      :   mode������ģʽ����Ϊ��������ģʽ������AVDD������DVDD������VREF�������忨�¶�
                    dc_type��ͨ������
**�������      :   ��
**����ֵ        :   ��
**��������      :   ���ݵ�ǰ����״̬���û�׼Դ��ADоƬ����ģʽ
************************************************************************************************************/
void changeMeasureMode(Uint8 mode, const int32 *dc_type)
{
    //��������ʹ���ڲ���׼������Ϊ��׼
    ads1247SetMeasureMode(mode, ADS1247_ONBOARD_REF);//if ((mode == ADS1247_NORMAL_MEASURE) && IS_RTD_TYPE(dc_type[i])),RTD����ʹ��REF0������Ϊ��׼
}


/***********************************************************************************************************
**����ԭ��      :   Uint8 checkVddPwr(Uint8 pwr)
**�������      :   pwr��������ѹ����
                        ADS1247_AVDD_MEASURE
                        ADS1247_DVDD_MEASURE
**�������      :   ��
**����ֵ        :   ��Դ����״̬����Ӧͨ��Ϊ1˵����Դ�쳣
**��������      :   ����ADоƬ��Դ��ѹ�Ƿ�����
************************************************************************************************************/

Uint8 checkVddPwr(Uint8 pwr)
{
    Uint8 i = 0;
    Uint8 power_error = 0;
    int32 chip_vdd = 0;                   //ADоƬ��Դ     
    int32 smpl_avg[2] = {0};              //��ͨ������ƽ��ֵ
    
    //����VDD
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
**����ԭ��      :   Uint8 checkADPwr(void)
**�������      :   ��
**�������      :   ��
**����ֵ        :   ��Դ״̬����Ӧbitλ��1˵����·��Դ�쳣
**��������      :   ����ADоƬAVDD/DVDD��Դ��ѹ�Ƿ�����
************************************************************************************************************/
Uint8 checkADPwr(void)
{
    Uint8 pwr_error = 0;
    
    //����AVDD
    pwr_error = checkVddPwr(ADS1247_AVDD_MEASURE);
    
    //����DVDD
    pwr_error |= checkVddPwr(ADS1247_DVDD_MEASURE);
    
    if (pwr_error)
    {
        error_code |= BIT(PWR_ERR);
    }
    
    return pwr_error;
}


/***********************************************************************************************************
**����ԭ��      :   int16 calcBoardTemperature(Uint8 start_no, Uint8 end_no, const int32 *smpl_buf)
**�������      :   start_no����ʼͨ��
                    end_no������ͨ��
                    smpl_buf����ͨ���¶Ȳ���ֵ
**�������      :   ��
**����ֵ        :   �忨�����¶�*10,������Χ-40~150���쳣�򷵻�0x7fff
**��������      :   ���㵱ǰ�忨�¶�
************************************************************************************************************/
int16 calcBoardTemperature(Uint8 start_no, Uint8 end_no, const int32 *smpl_buf)
{
    Uint8 i = 0;
    Uint8 valid_ch_num = 0;
    int16 chip_temp[AD_CHIP_NUM] = {0};//ADоƬ�¶�
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

    //��������ͨ���¶�ƽ��ֵ
    if (valid_ch_num != 0)
    {
        return (int16)(temp_sum/valid_ch_num);
    }
    else
    {
        return 0x7FFF;//�쳣�򷵻����ֵ���������������¶�
    }
}

/***********************************************************************************************************
**����ԭ��      :   void getInitBoardTempSmplData(const int32 *smpl_avg)
**�������      :   ��
**�������      :   smpl_avg������ͨ����������ƽ��ֵ
**����ֵ        :   ��
**��������      :   ��ȡ��ʼ��״̬�¸�ADоƬ�¶�ԭʼ����ֵ
************************************************************************************************************/
void getInitBoardTempSmplData(const int32 *smpl_avg)
{
    changeMeasureMode(ADS1247_TEMP_MEASURE, NULL);
    
    delayUs(500);
 
    processSamples((int32 *)smpl_avg);
}

/***********************************************************************************************************
**����ԭ��      :   Uint8 checkBoardTemperature(int16 *ptemperature_c, const int32 *smpl_avg)
**�������      :   smpl_avg������ͨ����������ƽ��ֵ
**�������      :   ptemperature_c�������¶ȴ洢��ַ
**����ֵ        :   �¶ȴ����־��1��ʾ�¶��쳣������150������-40��
**��������      :   ����忨�¶Ȳ��ж���Ϸ���
************************************************************************************************************/
Uint8 checkBoardTemperature(int16 *ptemperature_c, const int32 *smpl_avg)
{
    Uint8 error = 0;
    static Uint8 temp_err_cnt = 0;
    
    *ptemperature_c = calcBoardTemperature(0, 0, (int32 *)smpl_avg);
    if ((*ptemperature_c > 1500) || (*ptemperature_c < -400))//�Ϸ��¶�-40~150��
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
**����ԭ��      :   Uint8 getSamples(int32 *smpl_buf)
**����˵��      :   
**�������      :   smpl_bu:��ͨ������ֵ
**����ֵ        :   ͨ��״̬
**��������      :   ��ȡ����ֵ
************************************************************************************************************/
Uint8 getSamples(int32 *smpl_buf)
{
    Uint8 error = 0;
    int32 ad_result = 0;
    
    //���ò���ģʽ
    if (ch_smpl_error != 0)
    {
        return 1;
    }
    
    if (ads1247ReadADResult(&ad_result) == 0)
    {
        if (ad_result & 0x00800000)//��ֵ
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
            error |= BIT(0);//���й�������
        }
    }    
       
    return error;
}

/***********************************************************************************************************
**����ԭ��      :   void processSamples(int32 *smpl_avg)
**����˵��      :   start_no:��ʼͨ����
                    end_no:��ֹͨ����
**�������      :   smpl_avg:��ͨ������ƽ��ֵ
**����ֵ        :   ��
**��������      :   ��ʼ���׶ν��в���������SMPL_DATA_BUF_SIZE��ƽ���˲�
************************************************************************************************************/ 
int32 smpl_buf[2] = {0,0x12345678}; 
void processSamples(int32 *smpl_avg)
{
    Uint8 i;
    Uint8 j;     
    int32 smpl_sum = 0;    
    
    
    //����SMPL_DATA_BUF_SIZE��
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
**����ԭ��      :   void fix_filter_coef(Uint8 *coef, Uint8 *cnt, int32 *delta_data)
**����˵��      :   cnt:����������
                    delta_data:����ֵ�仯��
**�������      :   coef:�˲�ϵ�� 0~255
**����ֵ        :   ��
**��������      :   ����һ���˲�ϵ��
************************************************************************************************************/
void fix_filter_coef(Uint8 *coef, Uint8 *cnt, int32 *delta_data)
{
    //�������α仯������ͬ����Ϊ����ʵ�仯
    if (((delta_data[NOW] >= 0) && (delta_data[PREV] >= 0)) || ((delta_data[NOW] < 0) && (delta_data[PREV] < 0)))
    {
        //�����˲�
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
    else//��Ϊ�Ǹ���
    {
        *cnt = 0;
        *coef = 0;
    }
       
    delta_data[PREV] = delta_data[NOW];
}

/***********************************************************************************************************
**����ԭ��      :   void rc_filter(Uint8 coef, int32 data_in, int32 *data_out)
**����˵��      :   coef:�˲�ϵ�� 0~MAX_FILTER_COEF
                    data_in:�˲�����ֵ
**�������      :   data_out:�˲����ֵ,�洢��ǰֵ����ʷֵ
**����ֵ        :   ��
**��������      :   һ��RC�˲�
************************************************************************************************************/
void rc_filter(Uint8 coef, int32 data_in, int32 *data_out)
{
    //һ�׵�ͨ�˲�
    //if (x(n) < y(n-1)) y(n)=y(n-1)-(y(n-1)-x(n))*coef/256
    //else y(n)=y(n-1)+(x(n)-y(n-1))*coef/256
    //+128Ϊ���������룬��߾���
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
**����ԭ��      :   void setInternalPGA(Uint8 smpl_mode, const int32 *dc_type)
**�������      :   smpl_mode:����ģʽ
                        �Լ�ģʽ
                        ��������ģʽ
**�������      :   ��
**����ֵ        :   ��
**��������      :   ���ݲ���ģʽ����PGA�Ͳ�����
************************************************************************************************************/
void setInternalPGA(Uint8 smpl_mode, const int32 *dc_type)
{
    //���ò���ģʽ
    ads1247Config(ADC_GAIN_1, ADC_SPS_1000);//�Լ�״̬��PGA�����ó�1    
}


/***********************************************************************************************************
**����ԭ��      :   void setRtdCurrentOut(Uint8 ch_no, Uint8 current)
**�������      :   ch_no��ͨ����
                    current���������������С
                        IOUT_OFF   
                        IOUT_50uA  
                        IOUT_100uA 
                        IOUT_250uA 
                        IOUT_500uA 
                        IOUT_750uA 
                        IOUT_1000uA
                        IOUT_1500uA
**�������      :   ��
**����ֵ        :   ��
**��������      :   ����RTD�����������
************************************************************************************************************/
void setRtdCurrentOut(Uint8 current)
{
    ads1247SetIexcPin(AIN3, AIN2);
    ads1247SetIexcVal(current);
}

/***********************************************************************************************************
**����ԭ��      :   void setNormalSmpl(NR4418_SMPL *dp)
**�������      :   dp:Ԫ��ָ��
**�������      :   ��
**����ֵ        :   ��
**��������      :   ����ͨ�����ó���������ģʽ
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
    
    //����ʹ���ڲ���׼������Ϊ��׼
    ads1247SetMeasureMode(ADS1247_NORMAL_MEASURE, ADS1247_ONBOARD_REF);
    delayUs(500);
    
    //����PGA��������������
    ads1247Config(dp->pga[0], ADC_SPS_5);
    //���ò���ͨ��
    ads1247SelectADChannel(AIN0, AIN2);
    delayUs(500);
}

/***********************************************************************************************************
**����ԭ��      :   Uint8 initAdChannels(void)
**�������      :   ��
**�������      :   ��
**����ֵ        :   ��ʼ���������ӦλΪ1��ʾ��Ӧ��ADоƬ�쳣
**��������      :   ��ʼ��ADоƬ��ʹ���ڲ���׼
************************************************************************************************************/
Uint8 initAdChannels(void)
{
    Uint8 i = 0;
    Uint8 error = 0;
    
    if(ads1247Init() != 0)
    {
        error |= BIT(0);
    }
    
    ads1247EnableInternalRef();     //�̶�ʹ���ڲ��ο�
    
    if (error)
    {
        error_code |= BIT(CHNL_ERR);
    }
    
    return error;
}

/***********************************************************************************************************
**����ԭ��      :   void systemSelfCheck(DCSMP *dp)
**�������      :   dp��Ԫ��ָ��
**�������      :   ��
**����ֵ        :   ��
**��������      :   ϵͳ�Լ�
************************************************************************************************************/
void systemSelfCheck(DCSMP *dp)
{
    //��ʼ����оƬ
    ch_smpl_error = initAdChannels();
    delayUs(1000);//�ȴ�������Ч
    
    //����PGA�������Լ�
    ads1247Config(ADC_GAIN_1, ADC_SPS_1000);                    //�Լ�״̬��PGA�����ó�1
    delayUs(500); //�ȴ�������Ч
    
    //���AD��Դ
    ch_pwr_error = checkADPwr();
    dp->Adc_err_flag = (ch_pwr_error != 0);
    
    //����ʼ�忨�¶�
   // getInitBoardTempSmplData((int32 *)AD_Avg);
    //checkBoardTemperature(&dp->Temperature_c, (int32 *)AD_Avg);
    
    //�����ܴ����־
    error_flag = (error_code != 0);
}

/*****************************************************************************************
**����ԭ��      :   void updateOutputData(NR4418_SMPL *dp, int32 new_val, Uint8 ch_no)
**����˵��      :   dp-����Ԫ����ַ;
                    new_val-�²�������ֵ
                    ch_no-����ͨ����
**����ֵ        :   ��
**˵    ��      :   ��ʱ���ڵ���ͻ��������0.8%�������
                    ͻ�����������ݸ��º�������ȴ��ʱ���ڴ��ڼ䲻�ٸ������
*****************************************************************************************/
void updateOutputData(DCSMP *dp, int32 new_val, Uint8 ch_no)
{
    Uint16 delta_threshold = 0;
    static Uint16 cold_down_cnt[AD_CHIP_NUM] = {0};
    
    //ͻ����������ǰֵ��0.8%��������
    delta_threshold = (abs(dp->dc[ch_no])>>7);//0.8%
    if (delta_threshold < 3)
    {
        delta_threshold = 3;
    }
    if (abs(new_val - dp->dc[ch_no]) > delta_threshold)
    {
        //�˴����㣬��ֹ����Ķ�ʱ����
        dp->data_update_cnt[ch_no] = 0;
        //��ȴʱ�����������ٴθ������
        if (cold_down_cnt[ch_no] == 0)
        {
            cold_down_cnt[ch_no] = (dp->cold_down_time[ch_no]>>1);
            dp->dc[ch_no] = new_val;
        }
    }
    
    //��ȴʱ���ʱ
    if (cold_down_cnt[ch_no] > 0)
    {
        cold_down_cnt[ch_no]--;
    }

    //��ʱ����
    if (dp->data_update_cnt[ch_no]++ >= DATA_UPDATE_PERIOD)
    {
        dp->data_update_cnt[ch_no] = 0;
        dp->dc[ch_no] = new_val;
    }
}

/***********************************************************************************************************
**����ԭ��      :   void getBoardTemperature(NR4418_SMPL *dp)
**�������      :   dp��Ԫ��ָ��
**�������      :   ��
**����ֵ        :   ��
**��������      :   ��ȡ�忨�¶�״̬
************************************************************************************************************/
void getBoardTemperature(DCSMP *dp)
{
    switch (dp->temp_measure_step)
    {
        case 0:
            // �л�������ģʽ
            setInternalPGA(SYS_CHECK_MODE, NULL);
            changeMeasureMode(ADS1247_TEMP_MEASURE, NULL);
            dp->temp_measure_step++;
        break;
        
        case 1:
            //����ת��
            ads1247StartConvert(); 
            dp->temp_measure_step++;
        break;
            
        case 2:
            //��ȡ����������¶�
            ch_smpl_error |= getSamples((int32 *)channel_buf);
            checkBoardTemperature(&dp->Temperature_c, (int32 *)channel_buf);
            dp->temp_measure_step++;
        break;
        
        case 3:
            //�л���������ģʽ
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
**����ԭ��      :   void changeMeasureObject(NR4418_SMPL *dp)
**�������      :   dp��Ԫ��ָ��
**�������      :   ��
**����ֵ        :   ��
**��������      :   �л������������������������忨�¶ȡ�����RTD��׼��ѹ
************************************************************************************************************/
void changeMeasureObject(DCSMP *dp)
{
    dp->measure_shift_cnt++;
    
    //�л��ɲ���ģʽ
    if ((dp->measure_shift_cnt % TEMP_MEASURE_SHIFT_CNT) == 0)
    {
        dp->measure_mode = TEMP_MEASURE_MODE;
        
        return;
    }   
}

/***********************************************************************************************************
**����ԭ��      :   void getNormalSamples(NR4418_SMPL *dp)
**�������      :   dp��Ԫ��ָ��
**�������      :   ��
**����ֵ        :   ��
**��������      :   ��ȡ��������ģʽ�µĲ���ֵ
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
    
    //�л�����ͨ��
    if (dp->shift_flag)
    {
        // �л���AIN0��AIN2ͨ��
        ads1247Config(dp->pga[0],ADC_SPS_5);
        ads1247SelectADChannel(AIN0, AIN2);
    }
    else 
    {
        // �л���AIN1��AIN2ͨ��
        ads1247Config(dp->pga[1],ADC_SPS_5); 
        ads1247SelectADChannel(AIN1, AIN2);
    }     
    
    i = dp->shift_flag;
    
    //ͨ���쳣��ͨ�����������������󣬱�����ͨ�����
    if ((ch_smpl_error & BIT(0)) != 0)
    {
        //dp->dc[i]= 0;
    }
    else
    {
        //ѭ������ƽ���˲�
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
        //ʹ����λ����CPU����
        if (data_sums[i] >= 0)
        {
            AD_Avg[i] = data_sums[i]>>SHIFT_LEN;
        }
        else
        {
            AD_Avg[i] = -((-data_sums[i])>>SHIFT_LEN);
        }
        
        dp->dc[i] = AD_Avg[i];
        
        //����ƽ���˲������һ��RC�˲�
        //filter_in[i] = AD_Avg[i];
        //���㱾�β���ֵ���ϴ��˲�����Ĳ�ֵ
        //delta_value[i][NOW] = filter_in[i] - filter_out[i][PREV];
        //�����˲�ϵ��
        //fix_filter_coef(&filter_coef[i], &filter_cnt[i], delta_value[i]);
        //һ��RC��ͨ�˲�
        //rc_filter(filter_coef[i], filter_in[i], filter_out[i]);
        
        //ʵ��ֵ����
        //no_error_data = calcActualValue(i, filter_out[i][NOW], dp->dc_type[i]);
        
        //out_data = no_error_data;
        
        //�����仯�ż���ʱ���ڵ��������
        //updateOutputData(dp, out_data, i);
    }
    
    ads1247StartConvert();
    
    //���λ�������ѭ��ָ��
    data_index[i] = (data_index[i] + 1) & (SMPL_DATA_BUF_SIZE - 1);
    //�л�ʱ��Ƭ
    dp->shift_flag = !dp->shift_flag;
                  

    //changeMeasureObject(dp);
}

/***********************************************************************************************************
**����ԭ��      :   void updateErrorFlags(NR4418_SMPL *dp)
**�������      :   dp��Ԫ��ָ��
**�������      :   ��
**����ֵ        :   ��
**��������      :   ���´����־
************************************************************************************************************/
void updateErrorFlags(DCSMP *dp)
{
    Uint8 i = 0;
    
    //����4410������ֻ���ܵĳ����־
    if (ch_smpl_error != 0)
    {
        dp->Adc_err_flag = 1;
        error_code |= BIT(CHNL_ERR);
    }
    
    //���´����־
    error_flag = (error_code != 0);
}

/***********************************************************************************************************
**����ԭ��      :   DCSMP *newDCSMP(Component *parent, const char *name)
**����˵��      :   parent-��Ԫ����ַ��name����Ԫ������
**����ֵ        :   ��Ԫ���ڴ��ַ��
**˵   ��       :   ���캯����Ϊ����Ԫ������һ���ڴ棻
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
**����ԭ��      :   void initDCSMP(DCSMP *dp)
**����˵��      :   Ԫ����ַ
**����ֵ        :   ��
**˵    ��      :   ��ʼ��Ԫ������
*****************************************************************************************/
void initDCSMP(DCSMP *dp)
{
    //ϵͳ�Լ�
    systemSelfCheck(dp);
    
    //����������������
    setNormalSmpl(dp);
    
    dp->shift_flag  = 0;
    dp->enable_test = 0;
    dp->max_dc[0]      = -8388607;
    dp->max_dc[1]      = -8388607;
    dp->min_dc[0]      =  8388607;
    dp->min_dc[1]      =  8388607;
    dp->measure_mode = NORMAL_MEASURE_MODE;
    ads1247StartConvert();

    //����level2������������1ms
    setTask(2, runDCSMP, dp);
}

/*****************************************************************************************
**����ԭ��      :   void runNR4418_SMPL(NR4418_SMPL *dp)
**����˵��      :   dp-����Ԫ����ַ
**����ֵ        :   ��
**˵    ��      :   ���������ڲ���ģ���������·
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
