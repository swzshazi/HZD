/* File Description   
*  FileName: CableInput.c -- Ӳ���봦��Ԫ��        
*  Fuction: 
*       ���ܣ���ȡӲ���벢�����Ӧ����״̬
*       ���룺���޿��롢����ѹ�忪�롢���ÿ���
*       ���������ѹ��״̬������ѹ��״̬�����ÿ���״̬��ѹ���쳣��
*  apply: ����ģ��
*  author: ZYB 
*  data:  20200816
*/

#include "CableInput.h"
#include "Subroutine.h"

extern void BI_SOE(SOE_VALUE * command, SOE_VALUE * command_old);
// Local functions declaration
CableInput *newCableInput(Component *Parent,const char *Name);
int initCableInput(CableInput * dp);
void runCableInput(CableInput * dp);

/********************************************************************************
*         Input    : Parent componet, CableInput name                            *
*         Output   : CableInput handle                                           *
*         Function : Create the CableInput                                       *
********************************************************************************/
INIT_CODE CableInput *newCableInput(Component *Parent,const char *Name)
{
    Uint8 i;
    char tp_str[150];
    CableInput *dp;
        
    dp=(CableInput *)calloc(1,sizeof(CableInput));
    if (!dp) return NULL;
	
    dp->type_name="CableInput";
    dp->parent=Parent;
    dp->name=Name;
    dp->InitComponent = (int (*)(void *))initCableInput;
	
    registerComponent((Component *)dp);

    // Define input signals      
    registerVarIn((Component *)dp,(void **)&(dp->pOptodc),"pOptodc", T_SOE, LEVEL2);           // ң�ŵ�Դ����
    registerVarIn((Component *)dp,(void **)&(dp->pElecTest),"pElecTest", T_SOE, LEVEL2);       // �������ѹ��
    registerVarIn((Component *)dp,(void **)&(dp->pCutTest),"pCutTest", T_SOE, LEVEL2);         // ͣ�����ѹ��
   
    for ( i=0; i<HdOutBoard; i++ )
	{
		sprintf(tp_str, "pOutBoard%d", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pOutBoard[i]), tp_str, T_SOE, LEVEL2 );       // ����ѹ��
    }

    for ( i=0; i<HdSdByDINum; i++ )
	{
		sprintf(tp_str, "pSdByDI%d", i+1);
		registerVarIn( (Component*)dp, (void**)&(dp->pSdByDI[i]), tp_str, T_SOE, LEVEL2 );       // ���ÿ���
    }

    // Define output signals
    registerVarOut((Component *)dp,(void *)&(dp->opt_err),"opt_err", T_BIT, LEVEL2);                // ����ʧ��澯
    registerVarOut((Component *)dp,(void *)&(dp->test_Elec_out),"test_Elec_out_E", T_SOE, LEVEL2);    // �������ѹ��Ͷ��
    registerVarOut((Component *)dp,(void *)&(dp->test_cut_out),"test_cut_out_E", T_SOE, LEVEL2);      // ͣ�����ѹ��Ͷ��
    registerVarOut((Component *)dp,(void *)&(dp->test_strap_out),"test_strap_out", T_BIT, LEVEL2);  // ����ѹ��Ͷ��

    for ( i=0; i<HdOutBoard; i++ )
	{
		sprintf(tp_str, "OutBoard%d_E", i+1);
        registerVarOut( (Component*)dp, (void*)&(dp->OutBoard[i]), tp_str, T_SOE, LEVEL2 );         // ����ѹ��״̬
    }

    for ( i=0; i<HdSdByDINum; i++ )
	{
		sprintf(tp_str, "SdByDI%d_E", i+1);
        registerVarOut( (Component*)dp, (void*)&(dp->SdByDI[i]), tp_str, T_SOE, LEVEL2 );          // ���ÿ���״̬
    }

    registerVarOut((Component*)dp,(void*)&(dp->OutBoardAlam), "OutBdAlam", T_BIT, LEVEL2);         // ����ѹ���쳣

	registerVarOut((Component*)dp,(void*)&(dp->check_err), "check_err", T_BIT, LEVEL2);            // ��ַУ�����
    
    
    // Define parameters

    return (CableInput *)dp;
}
void CHECK_CableInput_check_task(CableInput *dp)
{
	Uint8 i, BoardState;

    BoardState = 0;
    for ( i = 0; i < HdOutBoard; i++ )
    {
        if ( dp->OutBoard[i].value.c_value == 0 )
        {
            BoardState = 1;
            break;
        }
    }

    if ( BoardState == 1 )
    {
        dp->BoardAlamNum ++;

        if ( dp->BoardAlamNum > HdBoardAlamNum )
        {
            dp->OutBoardAlam = 1;
        }
    }
    else
    {
        dp->BoardAlamNum = 0;
        dp->OutBoardAlam = 0;
    }
     
    if(dp->check_err == 0)
	{
		dp->check_err = check_set_pointer((Uint32)(&dp->start),(Uint32)(&dp->checksum));
	}
}
/********************************************************************************
*         Input    : CableInput handle                                           *
*         Output   : None                                                       *
*         Function : Initialize the CableInput                                   *
********************************************************************************/
INIT_CODE int initCableInput(CableInput * dp)
{
    Uint8 i;
    int16 ret;
    if (dp==NULL) return -1;
  
    // Output variables
    dp->opt_err = 0;
    dp->opt_err_cnt = 0;
    dp->test_strap_out = 0;
    
    // ��ʼ��SOE
    addInValueSoeTime(&(dp->test_Elec_out));
    addInValueSoeTime(&(dp->test_cut_out));

    for ( i=0; i<HdOutBoard; i++ )
	{
        addInValueSoeTime(&(dp->OutBoard[i]));
    }
    
    for( i=0; i<HdSdByDINum; i++ )
    {
        addInValueSoeTime(&(dp->SdByDI[i]));
    }

    // Private variables
	dp->check_err = 0;
  
    init_check_set_pointer((Uint32)(&dp->start), (Uint32)(&dp->checksum));
   
    setTask(2,runCableInput,dp);
	setTask(4, CHECK_CableInput_check_task, dp);
    return 0;
}
/********************************************************************************
*         Input    : CableInput handle                                           *
*         Output   : None                                                       *
*         Function : Run the CableInput                                          *
********************************************************************************/
void runCableInput(CableInput * dp)
{   
	Uint8 i;

    if ((dp->pOptodc->value.c_value) == 1)                                       //�����Դ�����������жϼ��޿���
	{
		dp->opt_err        = 0;
		dp->opt_err_cnt    = 0;
        
        BI_SOE(dp->pCutTest, &(dp->test_cut_out) );
        BI_SOE(dp->pElecTest, &(dp->test_Elec_out) );                    
		dp->test_strap_out = dp->pCutTest->value.c_value | dp->pElecTest->value.c_value;   //�����е磬���������ѹ����

        for ( i = 0; i < HdOutBoard; i++ )
        {
           BI_SOE( dp->pOutBoard[i], &(dp->OutBoard[i]) );   //�����е磬���������ѹ�巵��
        }

        for ( i = 0; i < HdSdByDINum; i++ )
        {
            BI_SOE( dp->pSdByDI[i], &(dp->SdByDI[i]) );    //�����е磬�������ÿ��뷵��
        }
	}
	else
	{
		dp->opt_err_cnt++;
		if (dp->opt_err_cnt>=12000)
		{
			dp->opt_err_cnt=12000;
		    dp->opt_err=1;
		}
	}
	if ( (dp->pCutTest->value.c_value) == 1 ) 									//ֻҪ�����п���,���ϣ����ܹ������
	{
		dp->test_strap_out = 1;
        BI_SOE( dp->pCutTest, &(dp->test_cut_out) );
	}
    else if ( (dp->pElecTest->value.c_value) == 1 )              
    {
        dp->test_strap_out = 1;
        BI_SOE( dp->pElecTest, &(dp->test_Elec_out) );
    } 
}
/*  End of File */
