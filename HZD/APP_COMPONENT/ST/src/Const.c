#include "Const.h"

Uint32  fake1_cnt=0;
Uint32  fake2_cnt=LVL2_FAKE_VAL;
Uint16  adjust_fake2=LVL2_FAKE_VAL;
Uint16  use_lvl1_index[64][3];
int32   dx0[64],dx1[64],dx2[64];
Uint16  cal_lvl2_times;
Uint32  cal_lvl2_time[64];

#pragma CODE_SECTION(alarmSta,".rtm_code")
void alarmSta(Uint16 cnt,Uint16 pre_cnt,Uint16 *continue_cnt,Uint16 *hold_cnt,Uint8 *alarm,Uint16 continue_lvl,Uint16 hold_lvl)
{
    if(cnt!=pre_cnt)*continue_cnt+=cnt-pre_cnt;
    else    *continue_cnt=0;
    if(*continue_cnt>continue_lvl)
    {
        *alarm=1;
        *hold_cnt=hold_lvl;
    }
    else
    {
        if(*alarm==1)
        {
            if(*hold_cnt>1)(*hold_cnt)--;
            else  *alarm=0;
        }
    }
}
    
