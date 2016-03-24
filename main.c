
//////////////////////////////////////////
//										//
//	APL CCR ������ �߿��� �Դϴ�. 			//
//										//					
//////////////////////////////////////////



#include    <pic18.h>

#include	"main.h"
#include	"Commom.h"
#include   	"analog.h"
#include	"serial.h"
#include   	"Com2_Port.h"
#include   	"Pwm1.h"

#include    "system\system.h" // �δ� ����
#include    "loader_45k80\loader_45k80_main.h"
#include   	"can_4480\you_can.h"








void    InitPort(void)
{
    TRISA = 0xff;
    TRISB = 0xff;
    TRISC = 0xff;
    TRISD = 0xff;
    TRISE = 0xff;

    LATA = 0xff;
    LATB = 0xff;
    LATC = 0xff;
    LATD = 0xff;
    LATE = 0xff;

    PIN_A_IN_TRIS = 1;
    PIN_V_IN_TRIS = 1;
    PIN_RA2_NoUse_TRIS = 1;
    PIN_RA3_NoUse_TRIS = 1;
    PIN_RA5_NoUse_TRIS = 1;

    PIN_IN_DAY_TRIS = 1;
    PIN_IN_NIGHT_TRIS = 1;
    PIN_CAN_TX_TRIS = 0;
    PIN_CAN_RX_TRIS = 1;
    PIN_IN_BLINK_TRIS = 1;
    PIN_RB5_NoUse_TRIS = 1;
    PIN_PGC_TRIS = 1;
    PIN_PGD_TRIS = 1;

    PIN_MODE_0_TRIS = 1;
    PIN_MODE_1_TRIS = 1;
    PIN_MODE_2_TRIS = 0;
    PIN_MODE_3_TRIS = 0;
    PIN_MODE_4_TRIS = 1;
    PIN_RC5_NoUse_TRIS = 1;
    PIN_TX_232_TRIS = 0;
    PIN_RX_232_TRIS = 1;

    PIN_LED_ON_TRIS = 0;
    PIN_LED_RUN0_TRIS = 0;
    PIN_LED_RUN1_TRIS = 0;
    PIN_LED_RUN2_TRIS = 0;
    PIN_PWM_TRIS = 0;
    PIN_LED_RUN3_TRIS = 0;
    PIN_LED_RUN4_TRIS = 0;
    PIN_TX_DP_TRIS = 1;

    PIN_1PPS_TRIS = 1;
    PIN_RE1_NoUse_TRIS = 1;
    PIN_RE2_NoUse_TRIS = 1;


    // APL LAMP ����
    _LAMP_ON = 0;
    _PWM = 0;
    // LED : 1 = Led Off
    _LED_CPU_RUN  = 1; // CPU RUN
    _LED_CDS_IN_NIG = 1; // Night ���� LED
    _LED_TEST = 1;
    _LED_LAMP_ON = 1;// APL Lamp On ��Ƽ LED
    _LED_GPS_GOOD = 1;// GPS RX2 ���Ž�, 'A' ����Ÿ ���� ���� LED
}








// GPS ���� ���ŵ� �޽��� üũ�Ѵ�.
// 1�ʸ��� High ���� ���ŵȴ�.
// High Edge ���� üũ�Ѵ�.
void ChkGpsPPS1(void)
{
    if (_PPS_GPS)
    {
        if (bPPS_On == FALSE)
        {
            bPPS_Edge = TRUE;
        }
        bPPS_On = TRUE;
    }
    else
    {
        bPPS_On = FALSE;
    }
}




void LedBlinkModeInit(void)
{
    unsigned char	i;

    for (i = 0;i < LED_ONOFF_CNT;i++)
    {
        OnTime[i] = 0x0;
        LedCycle_Msec = 0;
    }
}



// GPS �޽��� ���� ������ ����� !
// msec ���� 999���� �����ϰ�
// GPS ��,��,�� �������� �ð��� �����Ѵ�.
bit IsDutyOnByGpsTime(void)
{
    static bit bDutyOn;

    //
    if (bPPS_Edge && bPPS_On)
    {
        bPPS_Edge = FALSE;
        if (rx_sec == 59) // ���� 59�� �̸� ?
        {
            Gms1 = 999; // 999 ms �� ����
            Gsec = rx_sec; // Gps Rx �ð� ������ ���ʷ� ����
            Gmin = rx_min;
            Ghour = rx_hour;
            rx_sec = 0;
        }
    }

    Gms1++; // Timer�� ���� 1ms ���� ����
    // ms �� 1000(1��)�̸� �ð� ��(��,��,��)�� 1�� ���� ��Ų��.
    if (Gms1 >= 1000)
    {
        Gms1 = 0;
        Gsec++;
        if (Gsec >= 60)
        {
            Gsec = 0;
            Gmin++;
            if (Gmin >= 60)
            {
                Gmin = 0;
                Ghour++;
                if (Ghour >= 24)
                {
                    Ghour = 0;
                }
            }
        }
    }
    // ms ���� 0 �϶� ZeroTimer�� ����
    if (Gms1 == 0)
    {
        ZeroTimer = (ULONG)((ULONG)Ghour * (ULONG)3600000);
        ZeroTimer = ZeroTimer + (ULONG)((ULONG)Gmin  * (ULONG)60000);
        ZeroTimer = ZeroTimer + (ULONG)((ULONG)Gsec  * (ULONG)1000);
    }
    // ���� �ð����� ms ������ ȯ��
    Gms60000 = (UINT)((ZeroTimer + (ULONG)Gms1) % (ULONG)LED_CYCLE_MSEC);

    if (Gms60000 < LED_ON_DUTY_MSEC)
    {
        bDutyOn = TRUE; // APL LAMP ON
    }
    else
    {
        bDutyOn = FALSE;  // APL LAMP off
    }

    return bDutyOn;
}

// GPS RX2 ��� ���� �޾Ƽ� Com1TxBuffer�� �Ѱ��ش�.
// GPS ���� Good ��ȣ�� ������, ��,��,�� ������ ���� �����Ѵ�.
void ProcGpsRx2Data(void)
{
    unsigned int i;

    if (Com2RxBuffer[18] == 'A') // GPS ���� GOOD !
    {
        _LED_GPS_GOOD = !_LED_GPS_GOOD; // GPS ���� GOOD ���� LED
        i = (Com2RxBuffer[7] - 0x30) * 10;
        i = (Com2RxBuffer[8] - 0x30) + i;
        rx_hour = i;

        i = (Com2RxBuffer[9]  - 0x30) * 10;
        i = (Com2RxBuffer[10] - 0x30) + i;
        rx_min = i;

        i = (Com2RxBuffer[11] - 0x30) * 10;
        i = (Com2RxBuffer[12] - 0x30) + i;
        rx_sec = i;
    }

    for (i = 0; i < Com2RxCurCnt; i++)
        Com1TxBuffer[i] = Com2RxBuffer[i];

    // msec �� 3�ڸ��� ���� Tx���ۿ� ����
    i = (Gms1 % 100);
    Com1TxBuffer[14] = (unsigned char)((Gms1 / 100) + 0x30);
    Com1TxBuffer[15] = (unsigned char)((i / 10) + 0x30);
    Com1TxBuffer[16] = (unsigned char)((i % 10) + 0x30);

    Com2RxBuffer[18] = 0x0;
}



// Blink Led On, Off �Ǻ�
bit IsInput_ON(unsigned char bLedState, unsigned char* Timer)
{
    static bit bInputOn;

    bInputOn = TRUE;
    if (bLedState)	//	High
    {
        if (*Timer > 90) // High �� 90ms ���� �Ǹ� ���̴�.
            bInputOn = FALSE;
    }
    else 	// Low, 60Hz �̸� ���̴�.
    {
        *Timer = 0;
        bInputOn =  TRUE;
    }

    return bInputOn;
}


unsigned char GetDAY_TWL_NIG(void)
{
    static bit bCDS_Day, bCDS_Night;
    unsigned char ret;

    bCDS_Day = IsInput_ON(_CDS_DAY, &CDS_DayTimer);
    bCDS_Night = IsInput_ON(_CDS_NIGHT, &CDS_NightTimer);


    // ������ (�� / ���� / ��)
    if (_DIP_SW2 == DIPSW_ON)
    {
        if ((bCDS_Day) && (bCDS_Night))
            ret = TWL;
        else if (bCDS_Day)
            ret = DAY;
        else if (bCDS_Night)
            ret = NIG;
        else
            ret = DAY;
    }
    // �߱����� (�� / ��)
    else
    {
        if (bCDS_Night)
            ret = NIG;
        else
            ret = DAY;
    }

    return ret;

}





void WriteVal(UINT DutyCycle, UINT SetAVoltage, volatile const UCHAR* DestBuf)
{
    unsigned char SrcBuf[4];

    SrcBuf[0] = (far unsigned char)DutyCycle;
    SrcBuf[1] = (far unsigned char)(DutyCycle >> 8);
    SrcBuf[2] = (far unsigned char)SetAVoltage;
    SrcBuf[3] = (far unsigned char)(SetAVoltage >> 8);

    flash_write((const unsigned char *)SrcBuf, 4, (far unsigned char *)DestBuf);
}



void ReadVal(volatile const UCHAR* SavedBuf, UINT* pSetA_Volt, UINT* pDutyCycle)
{
    unsigned int temp;

    temp = 0x0000;
    temp = SavedBuf[1];
    temp = temp << 8;
    *pDutyCycle = temp | ((unsigned int)SavedBuf[0] & 0x00ff);

    temp = 0x0000;
    temp = SavedBuf[3];
    temp = temp << 8;
    *pSetA_Volt = temp | ((unsigned int)SavedBuf[2] & 0x00ff);
}









// ���� ���� On�ÿ� ���õ� ���� ���� APL ������ ���� ������.
void OutLampWhenPowerOn(void)
{
    do
    {
        BefDAY_TWL_NIG = CurDAY_TWL_NIG = GetDAY_TWL_NIG(); // NONE, DAY , TWL , NIG �� ����
        DutyCycle = sAPL[CurDAY_TWL_NIG].Set_DutyCycle;
        _LAMP_ON = TRUE;
        ChangePwmT2CON(CurDAY_TWL_NIG);
        OutPWM(DutyCycle);

        CLRWDT();
    }
    while (OutLampWhenPowerOnTimer < 100);
}


ULONG GetSetCurrent(unsigned int set_mV, unsigned char CurDayNight)
{
    ULONG Set_Current;

    Set_Current = ((((ULONG)set_mV) * Multip[CurDayNight]) / 1000);

    return Set_Current;
}





unsigned int CompareSet_InCurrent(unsigned int duty,
                                  unsigned char DayNig, unsigned int Offset)
{

//	Offset = GetOffSet(sAPL[0].Set_Current);

    if (sAPL[DayNig].Set_Current > In_Current)
    {
        if (sAPL[DayNig].Set_Current > (In_Current + Offset))
        {
            if (duty < DUTI_MAX)	duty++;
        }
    }
    else if (sAPL[DayNig].Set_Current < In_Current)
    {
        if ((sAPL[DayNig].Set_Current + Offset) < In_Current)
        {
            if (duty > 0)		duty--;
        }
    }

    if (AnalogValidTime > 20)
    {
        if (sAPL[DayNig].Set_Current <= 0)
            duty = 0;
    }

    if (duty > DUTI_MAX)	duty = DUTI_MAX;

    return duty;
}





// ���� ����ġ ������ �� APL ���� ����
void OutAplLamp_WhenSetMode(tag_CurDay Sw_DayNig)
{
    if (bAD_A_IN_mV_Upd)
    {
        bAD_A_IN_mV_Upd = FALSE;
        In_Current = GetInCurrent(AD_A_IN_mV);	// ���� Setting �� In ���� �� ��������

        sAPL[Sw_DayNig].Set_DutyCycle = DutyCycle = CompareSet_InCurrent(DutyCycle, Sw_DayNig, 0);

//		DutyCycle_Avr = AvrDutyCycle(DutyCycle); // Q??
    }

    ChangePwmT2CON(Sw_DayNig);
    OutPWM(DutyCycle);
}


// ����(����) APL LAPM On, Off ó��
void OutAplLamp_WhenNomalMode(tag_CurDay CurDayNig)
{
    unsigned int i;

    if (sAPL[CurDayNig].bEveryOnSet)
        bBlink_DutyOn = TRUE;

    if (bBlink_DutyOn) // Blink Led �� On �� ��
    {
        _LAMP_ON = TRUE; // LAMP ON
        if (bLampOnReady)
        {
            bLampOnReady = FALSE;

//			ReadVal((arSavedBuf + (CurDayNig*4)), &sAPL[CurDayNig].Setting_mV, &sAPL[CurDayNig].DutyCycle);
//			sAPL[CurDayNig].Set_Current = GetSetCurrent(sAPL[CurDayNig].Setting_mV, CurDayNig);
            DutyCycle = sAPL[CurDayNig].Set_DutyCycle; // ����� ��Ƽ ���� ���� ��Ƽ ���� ��������.
            ChangePwmT2CON(CurDayNig);
            OutPWM(DutyCycle);
        }
        else
        {
            if (bAD_A_IN_mV_Upd)
            {
                bAD_A_IN_mV_Upd = FALSE;
                In_Current = GetInCurrent(AD_A_IN_mV);	// ���� Setting �� In ���� �� ��������

                if (sAPL[CurDayNig].Set_Current > JUNG_GIJUN)
                    DutyCycle = CompareSet_InCurrent(DutyCycle, CurDayNig, 0);
                else
                    DutyCycle = CompareSet_InCurrent(DutyCycle, CurDayNig, 100);
            }
            ChangePwmT2CON(CurDayNig);
            OutPWM(DutyCycle);
        }

    }
    else // Blink Led �� Off �� ��
    {
        if (bAD_A_IN_mV_Upd)
        {
            bAD_A_IN_mV_Upd = FALSE;
            In_Current = GetInCurrent(AD_A_IN_mV);	// ���� Setting �� In ���� �� ��������
        }

        i = sAPL[CurDayNig].Set_Current;
        if (i >= 6000) DutyCycle = sAPL[CurDayNig].Set_DutyCycle / 20;
        else if (i >= 5000) DutyCycle = 5;
        else if (i >= 4000) DutyCycle = 4;
        else if (i >= 3000) DutyCycle = 4;
        else if (i >= 2000) DutyCycle = 3;
        else if (i >= 1000) DutyCycle = 3;
        else DutyCycle = 3;


        _LAMP_ON = FALSE; // LAMP OFF
        OutPWM(DutyCycle);
        bLampOnReady = TRUE;

    }
}



// ���� ���ð��� ���� PIN_PWM �ֱ� ������Ʈ ���� �� ����
void ChangePwmT2CON(tag_CurDay CurDayNight)
{
    if (sAPL[CurDayNight].Set_Current > JUNG_GIJUN)
    {
        if (T2CON != 0x06)
            T2CON = 0x06; // 2000õ ������ �� �� !
    }
    else
    {
        if (T2CON != 0x06)
            T2CON = 0x06; // 2000õ ������ �� �� !
    }
}

/*
// Tx ������ ��� ���, Tx���� �� Disable
void Chk232TxErr(void)
{
	if (Com1RxStatus == TX_SET)
	{
		if (Com1SerialTime > 3)
		{
			Com1SerialTime = 0;=================
			Com1RxStatus = STX_CHK;
			Com1TxCurCnt = 0;
			Com1TxTotalCnt = 0;
			TX1IE = 0;
		}
	}

}
*/



ULONG GetInCurrent(ULONG CurA_IN_mV)
{
    ULONG In_Current;

    if (CurA_IN_mV >= 600)
        In_Current = (((ULONG)CurA_IN_mV - 600) * 1000) / 60;  // (630 - 600)/60 * 1000 = 500 mA
    else
        In_Current = 0;

    return In_Current;
}

// ����� �� Read(Load) /////////////////////////////////////
bit ReadSetValueWhenPowerOn(void)
{
    unsigned char     i;
    static   bit     ret;

    ret = FALSE;

    // ��, ����, ���� ����� ��������, ����, ��Ƽ���� ���´�.
    sAPL[DAY].Set_Current = cF_SETCURR_DAY;
    sAPL[TWL].Set_Current = cF_SETCURR_TWL;
    sAPL[NIG].Set_Current = cF_SETCURR_NIG;

    sAPL[DAY].Max_Current = cF_MSETCURR_DAY;
    sAPL[TWL].Max_Current = cF_MSETCURR_TWL;
    sAPL[NIG].Max_Current = cF_MSETCURR_NIG;

    sAPL[DAY].Set_DutyCycle = cF_SET_DUTYCYCLED;
    sAPL[TWL].Set_DutyCycle = cF_SET_DUTYCYCLET;
    sAPL[NIG].Set_DutyCycle = cF_SET_DUTYCYCLEN;

    ret = TRUE;
    return(ret);

}


void ProcReadWrite(void)
{
// Read !!!
    // LED �����̴� 1����Ŭ�� ���Ͽ� ON ��Ƽ �ð�(msec) ���� ���Ѵ�.
    // Lamp Blink������ On �ֱ� �ð�(msec)
    DUTY_CNT = cF_DUTY_CNT;
    DUTY_RATE = cF_DUTY_RATE;
    if (DUTY_CNT >= 1) LED_CYCLE_MSEC = (60000 / (DUTY_CNT));
    LED_ON_DUTY_MSEC = (LED_CYCLE_MSEC * DUTY_RATE) / 100;

    // �� V_IN ���� ��
    sAPL[DAY].Set_Current = cF_SETCURR_DAY;
    sAPL[TWL].Set_Current = cF_SETCURR_TWL;
    sAPL[NIG].Set_Current = cF_SETCURR_NIG;

    sAPL[DAY].Max_Current = cF_MSETCURR_DAY;
    sAPL[TWL].Max_Current = cF_MSETCURR_TWL;
    sAPL[NIG].Max_Current = cF_MSETCURR_NIG;


    // ���ø������ �ƴ����� ���� ������ ���� ������ ������ ������.
    // ���� ��� ����
    eSETMODE = cF_SETMODE_SEL;

    sAPL[DAY].bEveryOnSet = cF_EveryOnSetD;
    sAPL[TWL].bEveryOnSet = cF_EveryOnSetT;
    sAPL[NIG].bEveryOnSet = cF_EveryOnSetN;

// Write !!!
    // Set_DutyCycle ��
    if (eSETMODE != Bef_eSETMODE)
    {
        if (Bef_eSETMODE)
        {
            if (Bef_eSETMODE == SETMODE_DAY)
            {
                iSR_IntData(F_SET_DUTYCYCLED) = sAPL[Bef_eSETMODE - 1].Set_DutyCycle;
                FlashBlockWr((F_SET_DUTYCYCLED / FLASH_ONE_BLOCK_SIZE));
            }
            else if (Bef_eSETMODE == SETMODE_TWL)
            {
                iSR_IntData(F_SET_DUTYCYCLET) = sAPL[Bef_eSETMODE - 1].Set_DutyCycle;
                FlashBlockWr((F_SET_DUTYCYCLET / FLASH_ONE_BLOCK_SIZE));
            }
            else if (Bef_eSETMODE == SETMODE_NIG)
            {
                iSR_IntData(F_SET_DUTYCYCLEN) = sAPL[Bef_eSETMODE - 1].Set_DutyCycle;
                FlashBlockWr((F_SET_DUTYCYCLEN / FLASH_ONE_BLOCK_SIZE));
            }

        }
        Bef_eSETMODE = eSETMODE;
    }

}


void ProcGPS(void)
{
// Int_Gps : com2 232Rx ����Ÿ ����
    if (Com2RxStatus == RX_GOOD)
    {
        Com2RxStatus = STX_CHK;

        ProcGpsRx2Data(); // �ð����� �����´�.
    }

// GPS Puls üũ
    ChkGpsPPS1();

}

void ProcBlink(void)
{
// ������ġ 2���� ���� Blink�� GPS Time�� ���� ���� FU BLK�Է¿� ���� ���� �����ȴ�.
    if (_DIP_SW3 == DIPSW_ON) // GPS
    {
        bBlink_DutyOn = bDutyOnByGpsTime;
    }
    else // FU : _IN_BLINK �Է� ���� Ȯ��
    {
        bBlink_DutyOn = bBLKInputOn = IsInput_ON(_IN_BLINK, &IN_BLK_Timer); // ���⿡�� �Է� �� On, Off �Ǻ� ;
    }

// Blink �� ���� LED ����
    if (bBlink_DutyOn)	_LED_LAMP_ON = ON_runled1; // Run ���� LED On
    else				_LED_LAMP_ON = OFF_runled1; // Run ���� LED Off

}

// CDS ��, ����, �� üũ ���
void ProcDAY_TWL_NIG(void)
{
// CDS ���� �о�� ǥ��
    CurDAY_TWL_NIG = GetDAY_TWL_NIG(); // NONE, DAY , TWL , NIG �� �����´�.

// ��, ���� �ٲ� �� ó��
    if (CurDAY_TWL_NIG != BefDAY_TWL_NIG)
    {
        BefDAY_TWL_NIG = CurDAY_TWL_NIG;
        bLampOnReady = TRUE;
    }
}


void ProcAD(void)
{
    bUdtAd = IsUdtAd(arInPut_mV, arIs_AdUpd, AdChSel);
    if (bUdtAd) // input AD �� ����.
    {
        GetMyAD(); // �� AD ���� Updated �̸�, �� ���� ������ ���� �Ѵ�.
        AdChSel = ChangeAdChSel(AdChSel, 1); // ä�� ����
        Set_AdCh(AdChSel); // ä�� ����

        // AD ä���� ���� �Ǿ���.
        // ����� ������ ���� ����Ǵ� ���� ������ �߰� �Ͽ���.
        if (AdChSel != BefAdChSel)
        {
            bAdCalcEnable = FALSE;
            AdCalcWaitCnt = 0;
            BefAdChSel = AdChSel;
        }

        bAdConversion = FALSE;
        DONE = 1;
    }
}


// ��, �ڸ�, �� ���� �ִ�ġ�� MAX ���� ���� ���� �δ����� ���� ���� �ϱ� ���Ͽ� ���� �Լ��̴�.
void Loader_ValueSetEdit_sub(unsigned char ch, unsigned int iValue)
{
    unsigned int i;

    i = MenuStatus[ch].M_EditDigitMaxValue = iValue;

    if (i >= 10000) MenuStatus[ch].M_EditShiftCnt = 5;
    else if (i >= 1000) MenuStatus[ch].M_EditShiftCnt = 4;
    else if (i >= 100) MenuStatus[ch].M_EditShiftCnt = 3;
    else if (i >= 10) MenuStatus[ch].M_EditShiftCnt = 2;
    else MenuStatus[ch].M_EditShiftCnt = 1;

}


void Loader_SetValueEdit(void)
{
    if (bef_MSETCURR_DAY != cF_MSETCURR_DAY)
    {
        Loader_ValueSetEdit_sub(7, cF_MSETCURR_DAY);
        bef_MSETCURR_DAY = cF_MSETCURR_DAY;
    }

    if (bef_MSETCURR_TWL != cF_MSETCURR_TWL)
    {
        Loader_ValueSetEdit_sub(8, cF_MSETCURR_TWL);
        bef_MSETCURR_TWL = cF_MSETCURR_TWL;
    }

    if (bef_MSETCURR_NIG != cF_MSETCURR_NIG)
    {
        Loader_ValueSetEdit_sub(9, cF_MSETCURR_NIG);
        bef_MSETCURR_NIG = cF_MSETCURR_NIG;
    }

}


///////////////////////////
//   ���� �Լ� 			  //
///////////////////////////

void main(void)
{
    unsigned char i;
    UCHAR ch;
    static bit ret;

    di();
    Initial();
    InitPort();
    InitTimer0();
    InitAD();
    InitPwm1();
    //UserBaudRate();
    Com2_Init();
    Loader_Com_Init(); // �δ� ����
    ei();

    DONE = 1;	// A/D Conversion Status bit
    TMR0IE = 1;
    SWDTEN = 1;  // Software Controlled Watchdog Timer Enable bit / 1 = Watchdog Timer is on

    ret = FALSE;
    ret = ReadSetValueWhenPowerOn();
    if (ret)	OutLampWhenPowerOn();
////////////////////////////////////////////////////////////////

    CallMeAdr = 0;


    while (1)
    {
        CLRWDT();


        Loader_Func(); // �δ� ���� �Լ�


        ProcReadWrite();


        ProcGPS(); // GPS ��� �� �޽� ���� ó��


        ProcBlink(); // BLink ��� ó��


        ProcDAY_TWL_NIG(); // CDS ��, ����, ���� �ٳ����� �� ó��


        ProcAD();


        Loader_SetValueEdit();


// CCR ��� (APL LAMP ��� ����) ///////////////////////////////////////
        // ���� ��� !!!
        if (eSETMODE)
        {
            _LAMP_ON = TRUE; // LAMP ON
            if (bSetModeReady)
            {
                T2CON = 0x06; // 2000õ ������ �� �� !
                DutyCycle = 0;
                OutPWM(DutyCycle);
                bSetModeReady = FALSE;
                //SetModeReady_Timer = 0;
            }
            else
            {
                OutAplLamp_WhenSetMode(eSETMODE - 1);
            }

            bLampOnReady = TRUE;

            UserSystemStatus = 1; // �δ����� ���� ���� ���� ���� �ֱ����� ���� ���̴�.
        }
        // �Ϲ� ��� !!!
        else if (sAPL[CurDAY_TWL_NIG].Set_DutyCycle)
        {
            OutAplLamp_WhenNomalMode(CurDAY_TWL_NIG);
            bSetModeReady = TRUE;

            // �δ����� ���� ���� ���� ���� �ֱ����� ���� ���̴�.
            if (CurDAY_TWL_NIG == 0) UserSystemStatus = 2;
            else if (CurDAY_TWL_NIG == 1) UserSystemStatus = 3;
            else if (CurDAY_TWL_NIG == 2) UserSystemStatus = 4;
        }
        else
        {
            // �δ����� ���� ���� ���� ���� �ֱ����� ���� ���̴�.
            if (CurDAY_TWL_NIG == 0) UserSystemStatus = 5;
            else if (CurDAY_TWL_NIG == 1) UserSystemStatus = 6;
            else if (CurDAY_TWL_NIG == 2) UserSystemStatus = 7;
        }

        // ���� ���� ���� �δ����� ���� ���Ͽ� ram ���� ������ ���� ���� ������ �����ϰ� �ִ�.
        UserRam_16[viewSET_DUTYCYCLE] = DutyCycle;
        UserRam_16[viewIn_Current]	  =	In_Current;
        UserRam_16[viewCurDAY_TWL_NIG] = CurDAY_TWL_NIG;

    }
}



void interrupt isr(void)
{
    if (TMR0IF)
    {
        TMR0IF = 0 ;
        TMR0L = MSEC_L;
        TMR0H = MSEC_H;


        Loader_Msec1_Interrpt(); // �δ� ���� �Լ�


        // Int_Gps Timer�� ���� Blink ó��
        bDutyOnByGpsTime = IsDutyOnByGpsTime(); // GPS�� ���� Blink �̴�.


        Com1SerialTime++;
        Com2SerialTime++;

        if (OutLampWhenPowerOnTimer < 1000)
            OutLampWhenPowerOnTimer++;

        if (AnalogValidTime < 200)
            AnalogValidTime++;


        if (CDS_DayTimer < 0xff)
            CDS_DayTimer++;
        if (CDS_NightTimer < 0xff)
            CDS_NightTimer++;
        if (IN_BLK_Timer < 0xff)
            IN_BLK_Timer++;


        if (SetModeReady_Timer < 0xffff)
            SetModeReady_Timer++;

        msec++;
        if (msec > 300)
        {
            msec = 0;

            if (_LED_CPU_RUN) _LED_CPU_RUN = 0;
            else _LED_CPU_RUN = 1;

        }
    }

    // GPS Rx2 ��� ���ͷ�Ʈ
    if ((RC2IE) && (RC2IF))
    {
        RC2IF = 0;
        Com2_Rx();
    }

    if ((TX2IE) && (TX2IF))
    {
        TX2IF = 0;
        Com2_Tx();
    }
    if (OERR2)
    {
        TXEN2 = 0;
        TXEN2 = 1;
        SPEN2 = 0;
        SPEN2 = 1;
        CREN2 = 0;
    }

    if (!CREN2)	CREN2 = 1;


    if ((RC1IE) && (RC1IF))
    {
        RC1IF = 0;
//        Com1_Rx();
    }

    if ((TX1IE) && (TX1IF))
    {
        TX1IF = 0;
//        Com1_Tx();
    }


    if (OERR1)
    {
        TXEN1 = 0;
        TXEN1 = 1;
        SPEN1 = 0;
        SPEN1 = 1;
        CREN1 = 0;
    }

    if (!CREN1)	CREN1 = 1;


    if (ADIF)
    {
        ADIF = 0;
        if (bAdConversion == FALSE)
        {
            ADBuf = ADRES;
            bAdConversion = TRUE;
        }
        DONE = 0;
    }

    Loader_Com_Interrpt(); // �δ� ���� �Լ�
}




