/* Filename:LoRaUnpack.c */
/* for git test */
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "hzplatform.h"
#include "LoRaUnpack.h"

void FrameCheck(LoRaUnpack *dp);
void Read_and_UnpackData(LoRaUnpack *dp);

LoRaUnpack *newLoRaUnpack(Component *parent, const char *name)
{
    LoRaUnpack *dp;
    dp = (LoRaUnpack *)calloc(1, sizeof(LoRaUnpack));
    if (!dp)
    {
        return NULL;
    }

    dp->type_name = "LoRaUnpack";
    dp->parent = parent;
    dp->name = name;
    dp->InitComponent = (void *)initLoRaUnpack;

    registerComponent((Component *)dp);

    registerVarIn((Component *)dp, (void **)&(dp->ReadBuffer), "ReadBuffer", T_UINT32, LEVEL2); //数据缓冲区
    registerVarIn((Component *)dp, (void **)&(dp->WriteIndex), "WriteIndex", T_UINT16, LEVEL2); //解包写位置指示

    registerVarOut((Component *)dp, (void *)&(dp->ReadIndex), "ReadIndex", T_UINT16, LEVEL2); //解包读位置指示

    // registerVarOut((Component *)dp, (void *)&(dp->devicetemp), "pos_devicetemp", T_FLOAT, LEVEL2); //设备温度
    // registerVarOut((Component *)dp, (void *)&(dp->asx), "pos_asx", T_FLOAT, LEVEL2);               //加速度x
    // registerVarOut((Component *)dp, (void *)&(dp->asy), "pos_asy", T_FLOAT, LEVEL2);               //加速度y
    // registerVarOut((Component *)dp, (void *)&(dp->asz), "pos_asz", T_FLOAT, LEVEL2);               //加速度z
    // registerVarOut((Component *)dp, (void *)&(dp->anglex), "pos_anglex", T_FLOAT, LEVEL2);         //绕x轴
    // registerVarOut((Component *)dp, (void *)&(dp->angley), "pos_angley", T_FLOAT, LEVEL2);         //绕y轴
    // registerVarOut((Component *)dp, (void *)&(dp->anglez), "pos_anglez", T_FLOAT, LEVEL2);         //绕z轴
    registerVarOut((Component *)dp, (void *)&(dp->islinkcount), "islinkcount", T_UINT16, LEVEL2);   //传感器在线数量
    //传感器ID注册
    registerParameter((Component *)dp,(void *)&(dp->SF6_FACTORY_ID),"SF6_FACTORY_ID min=0 max=0xffff default=0x485a option=1", T_UINT16);
    registerParameter((Component *)dp,(void *)&(dp->SF6_S1_ID),"SF6_S1_ID min=0 max=0xffffffff default=0x08200001 option=1", T_UINT32);
    registerParameter((Component *)dp,(void *)&(dp->SF6_S2_ID),"SF6_S2_ID min=0 max=0xffffffff default=0x08200002 option=1", T_UINT32);
    registerParameter((Component *)dp,(void *)&(dp->SF6_S3_ID),"SF6_S3_ID min=0 max=0xffffffff default=0x08200003 option=1", T_UINT32);
    registerParameter((Component *)dp,(void *)&(dp->SF6_S4_ID),"SF6_S4_ID min=0 max=0xffffffff default=0x08200004 option=1", T_UINT32);
    registerParameter((Component *)dp,(void *)&(dp->SF6_S5_ID),"SF6_S5_ID min=0 max=0xffffffff default=0x08200005 option=1", T_UINT32);
    registerParameter((Component *)dp,(void *)&(dp->SF6_S6_ID),"SF6_S6_ID min=0 max=0xffffffff default=0x08200006 option=1", T_UINT32);
    registerParameter((Component *)dp,(void *)&(dp->SF6_S7_ID),"SF6_S7_ID min=0 max=0xffffffff default=0x08200007 option=1", T_UINT32);
    registerParameter((Component *)dp,(void *)&(dp->SF6_S8_ID),"SF6_S8_ID min=0 max=0xffffffff default=0x08200008 option=1", T_UINT32);
    registerParameter((Component *)dp,(void *)&(dp->SF6_S9_ID),"SF6_S9_ID min=0 max=0xffffffff default=0x08200009 option=1", T_UINT32);
    registerParameter((Component *)dp,(void *)&(dp->SF6_S10_ID),"SF6_S10_ID min=0 max=0xffffffff default=0x0820000a option=1", T_UINT32);
    registerParameter((Component *)dp,(void *)&(dp->linktimeoutset),"linktimeoutset min=0 max=180000 default=3 option=1", T_FLOAT);

    //registerParameter((Component *)dp,(void *)&(dp->maxdensity),"maxdensity min=0 max=200000000 default=620000 option=1", T_FLOAT);
    registerParameter((Component *)dp,(void *)&(dp->mindensity),"mindensity min=0 max=200000000 default=590000 option=1", T_FLOAT);
    //传感器输出
    //S1——OUTPUT
    registerVarOut((Component *)dp, (void *)&(dp->SF6_battery_s1), "SF6_battery_s1", T_UINT8, LEVEL2);  //电源监视
    registerVarOut((Component *)dp, (void *)&(dp->sf6temp_s1), "sf6temp_s1", T_FLOAT, LEVEL2);          //温度值
    registerVarOut((Component *)dp, (void *)&(dp->sf6press_s1), "sf6press_s1", T_FLOAT, LEVEL2);        //压力值
    registerVarOut((Component *)dp, (void *)&(dp->sf6density_s1), "sf6density_s1", T_FLOAT, LEVEL2);    //归一化压力

    registerVarOut((Component *)dp, (void *)&(dp->linkstate_s1), "linkstate_s1", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->Overalarm_s1), "Overalarm_s1", T_UINT8, LEVEL2);
    //S2——OUTPUT
    registerVarOut((Component *)dp, (void *)&(dp->SF6_battery_s2), "SF6_battery_s2", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6temp_s2), "sf6temp_s2", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6press_s2), "sf6press_s2", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6density_s2), "sf6density_s2", T_FLOAT, LEVEL2);

    registerVarOut((Component *)dp, (void *)&(dp->linkstate_s2), "linkstate_s2", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->Overalarm_s2), "Overalarm_s2", T_UINT8, LEVEL2);
    //S3——OUTPUT
    registerVarOut((Component *)dp, (void *)&(dp->SF6_battery_s3), "SF6_battery_s3", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6temp_s3), "sf6temp_s3", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6press_s3), "sf6press_s3", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6density_s3), "sf6density_s3", T_FLOAT, LEVEL2);

    registerVarOut((Component *)dp, (void *)&(dp->linkstate_s3), "linkstate_s3", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->Overalarm_s3), "Overalarm_s3", T_UINT8, LEVEL2);
    //S4——OUTPUT
    registerVarOut((Component *)dp, (void *)&(dp->SF6_battery_s4), "SF6_battery_s4", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6temp_s4), "sf6temp_s4", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6press_s4), "sf6press_s4", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6density_s4), "sf6density_s4", T_FLOAT, LEVEL2);

    registerVarOut((Component *)dp, (void *)&(dp->linkstate_s4), "linkstate_s4", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->Overalarm_s4), "Overalarm_s4", T_UINT8, LEVEL2);
    //S5——OUTPUT
    registerVarOut((Component *)dp, (void *)&(dp->SF6_battery_s5), "SF6_battery_s5", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6temp_s5), "sf6temp_s5", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6press_s5), "sf6press_s5", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6density_s5), "sf6density_s5", T_FLOAT, LEVEL2);

    registerVarOut((Component *)dp, (void *)&(dp->linkstate_s5), "linkstate_s5", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->Overalarm_s5), "Overalarm_s5", T_UINT8, LEVEL2);
    //S6——OUTPUT
    registerVarOut((Component *)dp, (void *)&(dp->SF6_battery_s6), "SF6_battery_s6", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6temp_s6), "sf6temp_s6", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6press_s6), "sf6press_s6", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6density_s6), "sf6density_s6", T_FLOAT, LEVEL2);

    registerVarOut((Component *)dp, (void *)&(dp->linkstate_s6), "linkstate_s6", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->Overalarm_s6), "Overalarm_s6", T_UINT8, LEVEL2);
    //S7——OUTPUT
    registerVarOut((Component *)dp, (void *)&(dp->SF6_battery_s7), "SF6_battery_s7", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6temp_s7), "sf6temp_s7", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6press_s7), "sf6press_s7", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6density_s7), "sf6density_s7", T_FLOAT, LEVEL2);

    registerVarOut((Component *)dp, (void *)&(dp->linkstate_s7), "linkstate_s7", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->Overalarm_s7), "Overalarm_s7", T_UINT8, LEVEL2);
    //S8——OUTPUT
    registerVarOut((Component *)dp, (void *)&(dp->SF6_battery_s8), "SF6_battery_s8", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6temp_s8), "sf6temp_s8", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6press_s8), "sf6press_s8", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6density_s8), "sf6density_s8", T_FLOAT, LEVEL2);

    registerVarOut((Component *)dp, (void *)&(dp->linkstate_s8), "linkstate_s8", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->Overalarm_s8), "Overalarm_s8", T_UINT8, LEVEL2);
    //S9——OUTPUT
    registerVarOut((Component *)dp, (void *)&(dp->SF6_battery_s9), "SF6_battery_s9", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6temp_s9), "sf6temp_s9", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6press_s9), "sf6press_s9", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6density_s9), "sf6density_s9", T_FLOAT, LEVEL2);

    registerVarOut((Component *)dp, (void *)&(dp->linkstate_s9), "linkstate_s9", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->Overalarm_s9), "Overalarm_s9", T_UINT8, LEVEL2);
    //S10——OUTPUT
    registerVarOut((Component *)dp, (void *)&(dp->SF6_battery_s10), "SF6_battery_s10", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6temp_s10), "sf6temp_s10", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6press_s10), "sf6press_s10", T_FLOAT, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->sf6density_s10), "sf6density_s10", T_FLOAT, LEVEL2);

    registerVarOut((Component *)dp, (void *)&(dp->linkstate_s10), "linkstate_s10", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->Overalarm_s10), "Overalarm_s10", T_UINT8, LEVEL2);

    
    //Debug
    registerVarOut((Component *)dp, (void *)&(dp->SF6_ID_CHECK), "idcheck", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->err_code), "errcode", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->checkresult), "checkresult", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->timeout), "timeout", T_UINT16, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->diff), "diff", T_UINT16, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->IDrecv), "IDRECV", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->bufferstate), "bufferstate", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->Readbuf), "dp->Readbuf", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->ls), "ls", T_UINT16, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->var_type), "vartype", T_UINT16, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->linkstate), "linkstate", T_UINT8, LEVEL2);
    registerVarOut((Component *)dp, (void *)&(dp->linktimeout), "linktimeout", T_UINT16, LEVEL2);

    return dp;
}

INIT_CODE
void initLoRaUnpack(LoRaUnpack *dp)
{
    dp->ReadIndex = 0;             //解包读位置初始化
    dp->bufferstate = RECV_ENOUGH; //缓冲区状态

    dp->sensor_type = SF6_SENSOR;  //传感器类型初始化为空
    dp->err_loc = ALLCLEAR;        //错误类型定位为空
    dp->err_code = NO_ERROR;       //错误代码为零
    dp->checkresult = CHECKFAILED; //初始默认校验错误
    dp->var_type = NONE_VAR;       //参量类型为空
    dp->sumcheckrecv = 0;          //读取累加和结果初始化
    dp->sumcheck = 0;              //计算累加和初始化
    dp->CRC16checkrecv = 0;        //读取CRC结果初始化
    dp->CRC16check = 0;            //CRC计算结果初始化
    //解包结果初始化
    dp->device_temp = 0; //设备温度量初始化
    dp->as_x = 0;        //加速度量初始化
    dp->as_y = 0;
    dp->as_z = 0;
    dp->angle_x = 0; //角度量初始化
    dp->angle_y = 0;
    dp->angle_z = 0;
    dp->temp = 0;        //sf6温度初始化
    dp->press = 0;       //sf6压力初始化
    dp->density = 0;     //sf6归一化压力初始化
    dp->POS_battery = 0; //姿态传感器电池状态初始化
    dp->SF6_battery = 0; //sf6传感器电池状态初始化
    //输出的参量值初始化
    dp->asx = 0;
    dp->asy = 0;
    dp->asz = 0;
    dp->devicetemp = 0;
    dp->anglex = 0;
    dp->angley = 0;
    dp->anglez = 0;
    dp->sf6temp = 0;
    dp->sf6press = 0;
    dp->sf6density = 0;

    dp->timeout = 0;
    dp->diff = 0;
    dp->lp1 = 0;
    dp->lp2 = 0;
    dp->lp3 = 0;
    dp->lp4 = 0;
    dp->ls = 0;
    //将传入buffer引出成为数组
    dp->Readbuf = (Uint8 *)dp->ReadBuffer;
    //传感器指定初始化
    dp->SF6_S_LOC = 0;
    //将各个ID存入ID目录下
    dp->SF6_ID_STORE[0] = dp->SF6_S1_ID;
    dp->SF6_ID_STORE[1] = dp->SF6_S2_ID;
    dp->SF6_ID_STORE[2] = dp->SF6_S3_ID;
    dp->SF6_ID_STORE[3] = dp->SF6_S4_ID;
    dp->SF6_ID_STORE[4] = dp->SF6_S5_ID;
    dp->SF6_ID_STORE[5] = dp->SF6_S6_ID;
    dp->SF6_ID_STORE[6] = dp->SF6_S7_ID;
    dp->SF6_ID_STORE[7] = dp->SF6_S8_ID;
    dp->SF6_ID_STORE[8] = dp->SF6_S9_ID;
    dp->SF6_ID_STORE[9] = dp->SF6_S10_ID;
    //传感器连接超时状态初始化
    dp->linktimeout[0] = dp->linktimeoutset+3;
    dp->linktimeout[1] = dp->linktimeoutset+3;
    dp->linktimeout[2] = dp->linktimeoutset+3;
    dp->linktimeout[3] = dp->linktimeoutset+3;
    dp->linktimeout[4] = dp->linktimeoutset+3;
    dp->linktimeout[5] = dp->linktimeoutset+3;
    dp->linktimeout[6] = dp->linktimeoutset+3;
    dp->linktimeout[7] = dp->linktimeoutset+3;
    dp->linktimeout[8] = dp->linktimeoutset+3;
    dp->linktimeout[9] = dp->linktimeoutset+3;

    dp->linkstate[0] = linklost;
    dp->linkstate[1] = linklost;
    dp->linkstate[2] = linklost;
    dp->linkstate[3] = linklost;
    dp->linkstate[4] = linklost;
    dp->linkstate[5] = linklost;
    dp->linkstate[6] = linklost;
    dp->linkstate[7] = linklost;
    dp->linkstate[8] = linklost;
    dp->linkstate[9] = linklost;
    //传感器超限初始化
    dp->Overalarm_s1 = OK;
    dp->Overalarm_s2 = OK;
    dp->Overalarm_s3 = OK;
    dp->Overalarm_s4 = OK;
    dp->Overalarm_s5 = OK;
    dp->Overalarm_s6 = OK;
    dp->Overalarm_s7 = OK;
    dp->Overalarm_s8 = OK;
    dp->Overalarm_s9 = OK;
    dp->Overalarm_s10 = OK;

    dp->linklostcount = 0;
    dp->islinkcount = 0;
    setTask(4, Read_and_UnpackData, dp);
}
//定位当前解包位置，此时不会移动UnpackReadIndex的位置
Uint16 UnpackIndex_add(LoRaUnpack *dp, int index)
{
    int n = 1;
    Uint16 offset = dp->ReadIndex;
    while (n <= index)
    {
        if (offset != Buffer_Length - 1)
        {
            offset++;
        }
        else
        {
            offset = 0;
        }
        n++;
    }
    return offset;
}
//定位当前解包位置，此时UnpackReadIndex会移动
void UnpackIndex_move(LoRaUnpack *dp, int index)
{
    int n = 1;
    while (n <= index)
    {
        if (dp->ReadIndex != Buffer_Length - 1)
        {
            dp->ReadIndex++;
        }
        else
        {
            dp->ReadIndex = 0;
        }
        n++;
    }
}
//错误处理
void ErrorHandler(LoRaUnpack *dp)
{
    switch (dp->err_loc)
    {
    case ALLCLEAR:
        dp->err_code = NO_ERROR;
        break;
    case BUFFERERROR:
        dp->err_code = dp->err_code | BUFFERFULL_ERROR;
        break;
    case LOCATEFAILED:
        dp->err_code = dp->err_code | LOCATE_ERROR;
        break;
    case SUMCHECKFAILED:
        dp->err_code = dp->err_code | SUM_ERROR;
        break;
    case CRC16CHECKFAILED:
        dp->err_code = dp->err_code | CRC_ERROR;
        break;
    case IDCHECKFAILED:
        dp->err_code = dp->err_code | ID_ERROR;
        break;
    default:
        break;
    }
}

//判断当前帧位置碰撞
void IfCollide(LoRaUnpack *dp)
{
    dp->diff = ((*dp->WriteIndex) - dp->ReadIndex) & 0x07ff;
    if (dp->diff < MIN_LENGTH)
    {
        dp->bufferstate = RECV_ERROR;
    }
    else
    {
        dp->bufferstate = RECV_ENOUGH;
    }
}
//定位当前帧头
void LocateFrameStart(LoRaUnpack *dp)
{
    dp->timeout = 2048;
    while (dp->timeout > 0)
    {
        int count = 0;
        if (dp->Readbuf[dp->ReadIndex] == 0x24)
        {
            Uint16 offset = dp->ReadIndex;
            Uint8 stathead[6] = {0x24, 0x50, 0x41, 0x52, 0x41};
            for (count = 0; count < 5; count++)
            {
                if (dp->Readbuf[offset] != stathead[count])
                {
                    break;
                }
                else
                {
                    offset = UnpackIndex_add(dp, count + 1);
                }
            }
        }
        if (count == 5)
        {
            dp->err_code = NO_ERROR;
            dp->checkresult = CHECKPASS;
            break;
        }
        else
        {
            IfCollide(dp);
            if (dp->bufferstate == RECV_ERROR)
            {
                dp->err_loc = LOCATEFAILED;
                ErrorHandler(dp);
                break;
            }
            else
            {
                UnpackIndex_move(dp, 1);
                dp->timeout--;
            }
        }
    }
    if (dp->timeout == 0)
    {
        dp->err_loc = LOCATEFAILED;
        ErrorHandler(dp);
    }
}
/*
//累加和校验
void SumCheck(LoRaUnpack *dp)
{
    if(dp->sensor_type==NONE)
    {
        dp->err_loc=LOCATEFAILED;
        ErrorHandler(dp);
    }
    else
    {
        int i=0;
        Uint16 offset=0;
        switch (dp->sensor_type)
        {
        case POS_SENSOR:
            offset=UnpackIndex_add(dp,56);
            dp->sumcheckrecv=dp->Readbuf[offset];
            for(i=0;i<POS_FRAME_LENGTH;i++)
            {
                offset=UnpackIndex_add(dp,i);
                dp->sumcheck+=dp->Readbuf[offset];
            }
            if(dp->sumcheckrecv!=dp->sumcheck)
            {
                dp->err_loc = SUMCHECKFAILED;
                dp->checkresult = CHECKFAILED;
                ErrorHandler(dp);
            }
            else
            {
                dp->checkresult = CHECKPASS;
            }
            break;
        case SF6_SENSOR:
            offset=UnpackIndex_add(dp,32);
            dp->sumcheck=dp->Readbuf[offset];
            for(i=0;i<SF6_FRAME_LENGTH;i++)
            {
                offset=UnpackIndex_add(dp,i);
                dp->sumcheck+=dp->Readbuf[offset];
            }
            if(dp->sumcheckrecv!=dp->sumcheck)
            {
                dp->err_loc = SUMCHECKFAILED;
                dp->checkresult = CHECKFAILED;
                ErrorHandler(dp);
            }
            else
            {
                dp->checkresult = CHECKPASS;
            }
            break;
        default:
            break;
        }
    }
}
//查表法生成CRC16校验码
Uint16 RTU_CRC(Uint8 * puchMsg,Uint16 usDataLen)
{
   Uint8 uchCRCHi;                // high 字节 of CRC initialized
   Uint8 uchCRCLo;                // low 字节 of CRC initialized
   unsigned uIndex;                       // will index into CRC lookup table

   uchCRCHi = 0xFF;
   uchCRCLo = 0xFF;

   while ( usDataLen-- )
   {
    // calculate the CRC
		uIndex = uchCRCLo ^ (Uint8)( *puchMsg++ );
		uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex];
		uchCRCHi = auchCRCLo[uIndex]; 
   }

   return ( uchCRCHi << 8 | uchCRCLo );
}
//CRC16校验
void CRC16Check(LoRaUnpack *dp)
{
    if(*dp->bufferstate!=RECV_ENOUGH)
    {
        dp->err_loc=BUFFERERROR;
        ErrorHandler(dp);
    }
    else if(dp->checkresult==CHECKFAILED)
    {
        return;
    }
    else
    {
        int i=0;
        Uint16 offset=0,offset1=0,offset2=0;
        switch (dp->sensor_type)
        {
        case POS_SENSOR:
            offset1=UnpackIndex_add(dp,POS_FRAME_LENGTH+6);
            offset2=UnpackIndex_add(dp,POS_FRAME_LENGTH+5);
            dp->CRC16checkrecv=dp->Readbuf[offset1]|dp->Readbuf[offset2]<<8;
            for(i=0;i<POS_CRC_LENGTH;i++)
            {
                offset=UnpackIndex_add(dp,i+1);
                dp->CRCbuffer[i]=dp->Readbuf[offset];
            }
            dp->CRC16check=RTU_CRC(dp->CRCbuffer,POS_CRC_LENGTH);
            if(dp->CRC16checkrecv!=dp->CRC16check)
            {
                dp->err_loc=CRC16CHECKFAILED;
                dp->checkresult=CHECKFAILED;
                ErrorHandler(dp);
            }
            else
            {
                dp->checkresult=CHECKPASS;
            }
            break;
        case SF6_SENSOR:
            offset1=UnpackIndex_add(dp,SF6_FRAME_LENGTH+6);
            offset2=UnpackIndex_add(dp,SF6_FRAME_LENGTH+5);
            dp->CRC16checkrecv=dp->Readbuf[offset1]|dp->Readbuf[offset2]<<8;
            for(i=0;i<SF6_CRC_LENGTH;i++)
            {
                offset=UnpackIndex_add(dp,i+1);
                dp->CRCbuffer[i]=dp->Readbuf[offset];
            }
            dp->CRC16check=RTU_CRC(dp->CRCbuffer,SF6_CRC_LENGTH);
            if(dp->CRC16checkrecv!=dp->CRC16check)
            {
                dp->err_loc=CRC16CHECKFAILED;
                dp->checkresult=CHECKFAILED;
                ErrorHandler(dp);
            }
            else
            {
                dp->checkresult=CHECKPASS;
            }
            break;
        default:
            break;
        }
    }
}
*/
//ID匹配校验
void IDCheck(LoRaUnpack *dp)
{
    if (dp->err_code != NO_ERROR)
    {
        return;
    }
    else
    {
        UnpackIndex_move(dp, 9);
        int i = 0, n = 0, j = 0, nums = 0;
        Uint16 offset = 0;
        for (i = 0; i < 6; i++)
        {
            offset = UnpackIndex_add(dp, i);
            dp->IDrecv[i] = dp->Readbuf[offset];
        }
        for(n = 0; n < 10; n++)
        {
            //首先对定值设置中的ID进行拼接
            dp->SF6_ID_CHECK[0] = (Uint8)(dp->SF6_FACTORY_ID>>8);
            dp->SF6_ID_CHECK[1] = (Uint8)dp->SF6_FACTORY_ID;
            for(j = 0; j < 4; j++)
            {
                dp->SF6_ID_CHECK[j+2] = (Uint8)(dp->SF6_ID_STORE[n]>>((3-j)*8));
            }
            for(nums = 0; nums < 6; nums++)
            {
                if(dp->IDrecv[nums]!=dp->SF6_ID_CHECK[nums])
                {
                    dp->err_loc = LOCATEFAILED;
                    dp->checkresult = CHECKFAILED;
                    ErrorHandler(dp);
                    break;
                }
            }
            if(nums == 6)
            {
                dp->SF6_S_LOC = (Uint16)dp->IDrecv[nums-1]|(Uint16)dp->IDrecv[nums-2]<<8;
                dp->ls++;
                dp->err_code = NO_ERROR;
                dp->checkresult = CHECKPASS;
                break;
            }
        }
        for (i = 0; i < 6; i++)
        {
            dp->IDrecv[i] = 0;
        }
    }
}

//帧校验，分为累加和校验、CRC16校验、ID匹配检查，三项依次进行，前一项校验出错时不再进行后续校验
void FrameCheck(LoRaUnpack *dp)
{
    //    SumCheck(dp);
    //    CRC16Check(dp);
    IDCheck(dp);
}

void DataUnpack(LoRaUnpack *dp)
{
    if (dp->checkresult != CHECKPASS)
    {
        return;
    }
    else
    {
        UnpackIndex_move(dp, 13);
        Uint16 offset = 0, offset1 = 0, offset2 = 0, offset3 = 0, offset4 = 0;
        Uint8 count = 0, n = 0;
        switch (dp->sensor_type)
        {
        /* case POS_SENSOR:
            while (count < POS_NUM && n < 10)
            {
                IfCollide(dp);
                if (dp->bufferstate != RECV_ENOUGH)
                {
                    dp->err_loc = BUFFERERROR;
                    ErrorHandler(dp);
                    break;
                }
                offset = UnpackIndex_add(dp, 1);
                dp->var_type = dp->Readbuf[dp->ReadIndex] | dp->Readbuf[offset] << 8;
                switch (dp->var_type)
                {
                case BATTERY:
                    offset1 = UnpackIndex_add(dp, 3);
                    dp->POS_battery = dp->Readbuf[offset1];
                    UnpackIndex_move(dp, 4);
                    count++;
                    break;
                case DEVICE_TEMP:
                    offset1 = UnpackIndex_add(dp, 2);
                    offset2 = UnpackIndex_add(dp, 3);
                    offset3 = UnpackIndex_add(dp, 4);
                    offset4 = UnpackIndex_add(dp, 5);
                    dp->device_temp = dp->Readbuf[offset1] | dp->Readbuf[offset2] << 8 | dp->Readbuf[offset3] << 16 | dp->Readbuf[offset4] << 24;
                    UnpackIndex_move(dp, 6);
                    count++;
                    break;
                case AS_X:
                    offset1 = UnpackIndex_add(dp, 2);
                    offset2 = UnpackIndex_add(dp, 3);
                    offset3 = UnpackIndex_add(dp, 4);
                    offset4 = UnpackIndex_add(dp, 5);
                    dp->as_x = dp->Readbuf[offset1] | dp->Readbuf[offset2] << 8 | dp->Readbuf[offset3] << 16 | dp->Readbuf[offset4] << 24;
                    UnpackIndex_move(dp, 6);
                    count++;
                    break;
                case AS_Y:
                    offset1 = UnpackIndex_add(dp, 2);
                    offset2 = UnpackIndex_add(dp, 3);
                    offset3 = UnpackIndex_add(dp, 4);
                    offset4 = UnpackIndex_add(dp, 5);
                    dp->as_y = dp->Readbuf[offset1] | dp->Readbuf[offset2] << 8 | dp->Readbuf[offset3] << 16 | dp->Readbuf[offset4] << 24;
                    UnpackIndex_move(dp, 6);
                    count++;
                    break;
                case AS_Z:
                    offset1 = UnpackIndex_add(dp, 2);
                    offset2 = UnpackIndex_add(dp, 3);
                    offset3 = UnpackIndex_add(dp, 4);
                    offset4 = UnpackIndex_add(dp, 5);
                    dp->as_z = dp->Readbuf[offset1] | dp->Readbuf[offset2] << 8 | dp->Readbuf[offset3] << 16 | dp->Readbuf[offset4] << 24;
                    UnpackIndex_move(dp, 6);
                    count++;
                    break;
                case ANGLE_X:
                    offset1 = UnpackIndex_add(dp, 2);
                    offset2 = UnpackIndex_add(dp, 3);
                    offset3 = UnpackIndex_add(dp, 4);
                    offset4 = UnpackIndex_add(dp, 5);
                    dp->angle_x = dp->Readbuf[offset1] | dp->Readbuf[offset2] << 8 | dp->Readbuf[offset3] << 16 | dp->Readbuf[offset4] << 24;
                    UnpackIndex_move(dp, 6);
                    count++;
                    break;
                case ANGLE_Y:
                    offset1 = UnpackIndex_add(dp, 2);
                    offset2 = UnpackIndex_add(dp, 3);
                    offset3 = UnpackIndex_add(dp, 4);
                    offset4 = UnpackIndex_add(dp, 5);
                    dp->angle_y = dp->Readbuf[offset1] | dp->Readbuf[offset2] << 8 | dp->Readbuf[offset3] << 16 | dp->Readbuf[offset4] << 24;
                    UnpackIndex_move(dp, 6);
                    count++;
                    break;
                case ANGLE_Z:
                    offset1 = UnpackIndex_add(dp, 2);
                    offset2 = UnpackIndex_add(dp, 3);
                    offset3 = UnpackIndex_add(dp, 4);
                    offset4 = UnpackIndex_add(dp, 5);
                    dp->angle_z = dp->Readbuf[offset1] | dp->Readbuf[offset2] << 8 | dp->Readbuf[offset3] << 16 | dp->Readbuf[offset4] << 24;
                    UnpackIndex_move(dp, 6);
                    count++;
                    break;
                default:
                    break;
                }
                n++;
            }
            break; */
        case SF6_SENSOR:
            while (count < SF6_NUM && n < 10)
            {
                offset = UnpackIndex_add(dp, 1);
                dp->var_type = dp->Readbuf[dp->ReadIndex] | dp->Readbuf[offset] << 8;
                switch (dp->var_type)
                {
                case BATTERY:
                    offset1 = UnpackIndex_add(dp, 3);
                    dp->SF6_battery = dp->Readbuf[offset1];
                    UnpackIndex_move(dp, 4);
                    dp->lp1++;
                    count++;
                    break;
                case SF6_TEMP:
                    offset1 = UnpackIndex_add(dp, 2);
                    offset2 = UnpackIndex_add(dp, 3);
                    offset3 = UnpackIndex_add(dp, 4);
                    offset4 = UnpackIndex_add(dp, 5);
                    dp->temp = dp->Readbuf[offset1] | dp->Readbuf[offset2] << 8 | dp->Readbuf[offset3] << 16 | dp->Readbuf[offset4] << 24;
                    UnpackIndex_move(dp, 6);
                    dp->lp2++;
                    count++;
                    break;
                case SF6_PRESS:
                    offset1 = UnpackIndex_add(dp, 2);
                    offset2 = UnpackIndex_add(dp, 3);
                    offset3 = UnpackIndex_add(dp, 4);
                    offset4 = UnpackIndex_add(dp, 5);
                    dp->press = dp->Readbuf[offset1] | dp->Readbuf[offset2] << 8 | dp->Readbuf[offset3] << 16 | dp->Readbuf[offset4] << 24;
                    UnpackIndex_move(dp, 6);
                    dp->lp3++;
                    count++;
                    break;
                case SF6_DENSITY:
                    offset1 = UnpackIndex_add(dp, 2);
                    offset2 = UnpackIndex_add(dp, 3);
                    offset3 = UnpackIndex_add(dp, 4);
                    offset4 = UnpackIndex_add(dp, 5);
                    dp->density = dp->Readbuf[offset1] | dp->Readbuf[offset2] << 8 | dp->Readbuf[offset3] << 16 | dp->Readbuf[offset4] << 24;
                    UnpackIndex_move(dp, 6);
                    dp->lp4++;
                    count++;
                    break;
                default:
                    break;
                }
                n++;
            }
            break;
        default:
            break;
        }
    }
}
//将数据转为浮点型
float HEXTOFLOAT(LoRaUnpack *dp, Uint32 data)
{
    float fdata = 0;
    dp->HEXTOFLOAT.num = data;
    fdata = dp->HEXTOFLOAT.fnum;
    return fdata;
}

//处理解包完成的数据
void DataSolution(LoRaUnpack *dp)
{
    if (dp->err_code != NO_ERROR)
    {
        dp->device_temp = 0;
        dp->as_x = 0;
        dp->as_y = 0;
        dp->as_z = 0;
        dp->angle_x = 0;
        dp->angle_y = 0;
        dp->angle_z = 0;
        dp->temp = 0;
        dp->press = 0;
        dp->density = 0;
    }
    else
    {
        switch (dp->sensor_type)
        {
        case POS_SENSOR:
            dp->devicetemp = HEXTOFLOAT(dp, dp->device_temp);
            dp->asx = HEXTOFLOAT(dp, dp->as_x);
            dp->asy = HEXTOFLOAT(dp, dp->as_y);
            dp->asz = HEXTOFLOAT(dp, dp->as_z);
            dp->anglex = HEXTOFLOAT(dp, dp->angle_x);
            dp->angley = HEXTOFLOAT(dp, dp->angle_y);
            dp->anglez = HEXTOFLOAT(dp, dp->angle_z);
            break;
        case SF6_SENSOR:
            dp->sf6temp = HEXTOFLOAT(dp, dp->temp);
            dp->sf6press = HEXTOFLOAT(dp, dp->press);
            dp->sf6density = HEXTOFLOAT(dp, dp->density);
        default:
            break;
        }
    }
}
//将解包好的数据指定给相应的传感器
void DataIssue(LoRaUnpack *dp)
{
    switch (dp->SF6_S_LOC)
    {
    case SF6S1:
        dp->sf6density_s1 = dp->sf6density/1000000;
        dp->sf6press_s1 = dp->sf6press;
        dp->sf6temp_s1 = dp->sf6temp;
        dp->SF6_battery_s1 = dp->SF6_battery;
        dp->linktimeout[0] = 0;
        dp->linkstate[0]=islink;
        if(dp->sf6density_s1 < dp->mindensity)
        {
            dp->Overalarm_s1 = isOver;
        }
        else
        {
            dp->Overalarm_s1 = OK;
        } 
        break;
    case SF6S2:
        dp->sf6density_s2 = dp->sf6density/1000000;
        dp->sf6press_s2 = dp->sf6press;
        dp->sf6temp_s2 = dp->sf6temp;
        dp->SF6_battery_s2 = dp->SF6_battery;
        dp->linktimeout[1] = 0;
        dp->linkstate[0]=islink;
        if(dp->sf6density_s2 < dp->mindensity)
        {
            dp->Overalarm_s2 = isOver;
        }
        else
        {
            dp->Overalarm_s2 = OK;
        } 
        break;
    case SF6S3:
        dp->sf6density_s3 = dp->sf6density/1000000;
        dp->sf6press_s3 = dp->sf6press;
        dp->sf6temp_s3 = dp->sf6temp;
        dp->SF6_battery_s3 = dp->SF6_battery;
        dp->linktimeout[2] = 0;
        dp->linkstate[0]=islink;
        if(dp->sf6density_s3 < dp->mindensity)
        {
            dp->Overalarm_s3 = isOver;
        }
        else
        {
            dp->Overalarm_s3 = OK;
        } 
        break;
    case SF6S4:
        dp->sf6density_s4 = dp->sf6density/1000000;
        dp->sf6press_s4 = dp->sf6press;
        dp->sf6temp_s4 = dp->sf6temp;
        dp->SF6_battery_s4 = dp->SF6_battery;
        dp->linktimeout[3] = 0;
        dp->linkstate[0]=islink;
        if(dp->sf6density_s4 < dp->mindensity)
        {
            dp->Overalarm_s4 = isOver;
        }
        else
        {
            dp->Overalarm_s4 = OK;
        } 
        break;
    case SF6S5:
        dp->sf6density_s5 = dp->sf6density/1000000;
        dp->sf6press_s5 = dp->sf6press;
        dp->sf6temp_s5 = dp->sf6temp;
        dp->SF6_battery_s5 = dp->SF6_battery;
        dp->linktimeout[4] = 0;
        dp->linkstate[0]=islink;
        if(dp->sf6density_s5 < dp->mindensity)
        {
            dp->Overalarm_s5 = isOver;
        }
        else
        {
            dp->Overalarm_s5 = OK;
        } 
        break;
    case SF6S6:
        dp->sf6density_s6 = dp->sf6density/1000000;
        dp->sf6press_s6 = dp->sf6press;
        dp->sf6temp_s6 = dp->sf6temp;
        dp->SF6_battery_s6 = dp->SF6_battery;
        dp->linktimeout[5] = 0;
        dp->linkstate[0]=islink;
        if(dp->sf6density_s6 < dp->mindensity)
        {
            dp->Overalarm_s6 = isOver;
        }
        else
        {
            dp->Overalarm_s6 = OK;
        } 
        break;
    case SF6S7:
        dp->sf6density_s7 = dp->sf6density/1000000;
        dp->sf6press_s7 = dp->sf6press;
        dp->sf6temp_s7 = dp->sf6temp;
        dp->SF6_battery_s7 = dp->SF6_battery;
        dp->linktimeout[6] = 0;
        dp->linkstate[0]=islink;
        if(dp->sf6density_s7 < dp->mindensity)
        {
            dp->Overalarm_s7 = isOver;
        }
        else
        {
            dp->Overalarm_s7 = OK;
        } 
        break;
    case SF6S8:
        dp->sf6density_s8 = dp->sf6density/1000000;
        dp->sf6press_s8 = dp->sf6press;
        dp->sf6temp_s8 = dp->sf6temp;
        dp->SF6_battery_s8 = dp->SF6_battery;
        dp->linktimeout[7] = 0;
        dp->linkstate[0]=islink;
        if(dp->sf6density_s8 < dp->mindensity)
        {
            dp->Overalarm_s8 = isOver;
        }
        else
        {
            dp->Overalarm_s8 = OK;
        } 
        break;
    case SF6S9:
        dp->sf6density_s9 = dp->sf6density/1000000;
        dp->sf6press_s9 = dp->sf6press;
        dp->sf6temp_s9 = dp->sf6temp;
        dp->SF6_battery_s9 = dp->SF6_battery;
        dp->linktimeout[8] = 0;
        dp->linkstate[0]=islink;
        if(dp->sf6density_s9 < dp->mindensity)
        {
            dp->Overalarm_s9 = isOver;
        }
        else
        {
            dp->Overalarm_s9 = OK;
        } 
        break;
    case SF6S10:
        dp->sf6density_s10 = dp->sf6density/1000000;
        dp->sf6press_s10 = dp->sf6press;
        dp->sf6temp_s10 = dp->sf6temp;
        dp->SF6_battery_s10 = dp->SF6_battery;
        dp->linktimeout[9] = 0;
        dp->linkstate[0]=islink;
        if(dp->sf6density_s10 < dp->mindensity)
        {
            dp->Overalarm_s10 = isOver;
        }
        else
        {
            dp->Overalarm_s10 = OK;
        } 
        break;
    
    default:
        break;
    }
    int countlink = 0;
    for(countlink=0;countlink<10;countlink++)
    {
        dp->linktimeout[countlink]++;
    }
}
//检测传感器通信情况
void LinkConditionCheck(LoRaUnpack *dp)
{
    int index = 0;
    dp->linklostcount = 0;
    for(index=0;index<10;index++)
    {
        if(dp->linktimeout[index]>dp->linktimeoutset)
        {
            dp->linkstate[index]=linklost;
            dp->linktimeout[index] = dp->linktimeoutset+3;
            dp->linklostcount++;
        }
    }
    dp->islinkcount = 10 - dp->linklostcount;
    dp->linklostcount = 0;
    //分别引出告警状态
    dp->linkstate_s1 = dp->linkstate[0];
    dp->linkstate_s2 = dp->linkstate[1];
    dp->linkstate_s3 = dp->linkstate[2];
    dp->linkstate_s4 = dp->linkstate[3];
    dp->linkstate_s5 = dp->linkstate[4];
    dp->linkstate_s6 = dp->linkstate[5];
    dp->linkstate_s7 = dp->linkstate[6];
    dp->linkstate_s8 = dp->linkstate[7];
    dp->linkstate_s9 = dp->linkstate[8];
    dp->linkstate_s10 = dp->linkstate[9];
}
//重新初始化,将需要复位的状态复位
void reinitLoRaUnpack(LoRaUnpack *dp)
{
    dp->sensor_type = SF6_SENSOR;
    dp->err_loc = ALLCLEAR;
    dp->err_code = NO_ERROR;
    dp->bufferstate = RECV_ENOUGH;
    dp->checkresult = CHECKFAILED;
    dp->var_type = NONE_VAR;
    dp->sumcheckrecv = 0;
    dp->sumcheck = 0;
    dp->CRC16checkrecv = 0;
    dp->CRC16check = 0;
    dp->device_temp = 0;
    dp->as_x = 0;
    dp->as_y = 0;
    dp->as_z = 0;
    dp->angle_x = 0;
    dp->angle_y = 0;
    dp->angle_z = 0;
    dp->temp = 0;
    dp->press = 0;
    dp->density = 0;
    dp->SF6_S_LOC = 0;
}

void Read_and_UnpackData(LoRaUnpack *dp)
{
    //首先进行一次读写碰撞检测
    IfCollide(dp);
    if (dp->bufferstate != RECV_ENOUGH)
    {
        return;
    }
    else
    {
        LocateFrameStart(dp);
        FrameCheck(dp);
        DataUnpack(dp);
        DataSolution(dp);
        DataIssue(dp);
        LinkConditionCheck(dp);
    }
    reinitLoRaUnpack(dp);
}
