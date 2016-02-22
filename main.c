
#include    <pic18.h>

#include	"main.h"
#include	"Commom.h"
#include   	"analog.h"
#include	"serial.h"
#include   	"Com2_Port.h"
#include   	"Pwm1.h"

#include    "system\system.h" // �δ� ���� 
#include    "loader_45k80\loader_45k80_main.h"




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
    _LED_CDS_IN_DAY  = 1; // CPU RUN
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


/*
unsigned int ReSettingDayNigntChk(void)
{
    if (PIN_RB5_NoUse)
    {
        SettingReadyTime = 0;
        NightDaySetTime = 0;
        bNightDay = 0;
        NightSetTime = 0;
        bNight = 0;
        _LED_CDS_IN_NIG = 1;
        return(0);
    }


    if (!PIN_MODE_1 && PIN_MODE_0)
    {
        if ((NightSetTime > 5) && (!bNight))
        {
            bNight = 1;
            new_value[0] = AdValue[0];
            CompanyWrite();
            LoadSetupValue();
        }
        if (bNight)	_LED_CDS_IN_NIG = 0;
    }
    else if (!PIN_MODE_0 && PIN_MODE_1)
    {
        if ((NightDaySetTime > 5) && (!bNightDay))
        {
            bNightDay = 1;
            new_value[1] = AdValue[0];
            CompanyWrite();
            LoadSetupValue();
        }
        if (bNightDay)	_LED_CDS_IN_NIG = 0;
    }
    else
    {
        NightDaySetTime = 0;
        bNightDay = 0;

        NightSetTime = 0;
        bNight = 0;

        if (SettingReadyTime > 4)
        {
            _LED_CDS_IN_NIG = !_LED_CDS_IN_NIG;
            SettingReadyTime = 0;
        }
    }

    return(0);
}
*/


/*
void ModeChk(void)
{
	unsigned char i,j,befmodesw;

	befmodesw=modesw;

	modesw=0;

	if( !PIN_IN_DAY)	modesw=(modesw | 0x01);
	if( !PIN_IN_NIGHT)	modesw=(modesw | 0x02);
	if( !PIN_CAN_TX)	modesw=(modesw | 0x04);
	if( !PIN_CAN_RX)	modesw=(modesw | 0x08);
	if( !PIN_IN_BLINK)	modesw=(modesw | 0x10);


	if( (modesw & 0x1f) != (befmodesw & 0x1f)){
		LedBlinkModeInit();
		i=(modesw & 0x1f);

		switch(i){
			case	0:
				OnTime[0]  		=1000;
				LedCycle_Msec	=4000;
				break;
			case	1:
				OnTime[0]  		=1000;
				LedCycle_Msec	=5000;
				break;
			case	2:
				OnTime[0]  		=1000;
				LedCycle_Msec	=6000;
				break;
			case	3:
				OnTime[0]  		=500;
				OnTime[1]  		=1000;
				OnTime[2]  		=1500;
				LedCycle_Msec	=6000;
				break;
			case	4:						// 7s
				OnTime[0]  		=500;
				OnTime[1]  		=1000;
				OnTime[2]  		=1500;
				OnTime[3]  		=2000;
				OnTime[4]  		=2500;
				LedCycle_Msec	=7000;
				break;
			case	5:						// 8s
				OnTime[0]  		=500;
				OnTime[1]  		=1000;
				OnTime[2]  		=1500;
				OnTime[3]  		=2000;
				OnTime[4]  		=2500;
				OnTime[5]  		=3000;
				OnTime[6]  		=3500;
				LedCycle_Msec	=8000;
				break;
			case	6:						// 20s-5
				OnTime[0]  		=500;
				OnTime[1]  		=1000;
				OnTime[2]  		=1500;
				OnTime[3]  		=2000;
				OnTime[4]  		=2500;
				OnTime[5]  		=3000;
				OnTime[6]  		=3500;
				OnTime[7]  		=4000;
				OnTime[8]  		=4500;
				LedCycle_Msec	=20000;
				break;
			case	7:						// 5s-2
				OnTime[0]  		=500;
				OnTime[1]  		=1000;
				OnTime[2]  		=1500;
				LedCycle_Msec	=5000;
				break;
			case	8:						// 10s-2
				OnTime[0]  		=500;
				OnTime[1]  		=1000;
				OnTime[2]  		=1500;
				LedCycle_Msec	=10000;
				break;
			case	9:						// Q
				OnTime[0]  		=500;
				LedCycle_Msec	=1000;
				break;
			case	10:						// Q3-10s
				OnTime[0]  		=500;
				OnTime[1]  		=1000;
				OnTime[2]  		=1500;
				OnTime[3]  		=2000;
				OnTime[4]  		=2500;
				LedCycle_Msec	=1000;
				break;
			case	11:						// Q6 + LF115s
				OnTime[0]  		=500;
				OnTime[1]  		=1000;
				OnTime[2]  		=1500;
				OnTime[3]  		=2000;
				OnTime[4]  		=2500;
				OnTime[5]  		=3000;
				OnTime[6]  		=3500;
				OnTime[7]  		=4000;
				OnTime[8]  		=4500;
				OnTime[9]  		=5000;
				OnTime[10]  	=5500;
				OnTime[11]  	=6000;
				OnTime[12]  	=8000;
				LedCycle_Msec 	=15000;
				break;
			case	12:						// Q9 + 15s
				OnTime[0]  		=500;
				OnTime[1]  		=1000;
				OnTime[2]  		=1500;
				OnTime[3]  		=2000;
				OnTime[4]  		=2500;
				OnTime[5]  		=3000;
				OnTime[6]  		=3500;
				OnTime[7]  		=4000;
				OnTime[8]  		=4500;
				OnTime[9]  		=5000;
				OnTime[10]  	=5500;
				OnTime[11]  	=6000;
				OnTime[12]  	=6500;
				OnTime[13]  	=7000;
				OnTime[14]  	=7500;
				OnTime[15]  	=8000;
				OnTime[16]  	=8500;
				LedCycle_Msec 	=15000;
				break;
			case	13:						// Mo(A)8s
				OnTime[0]  		=500;
				OnTime[1]  		=1000;
				OnTime[2]  		=3000;
				LedCycle_Msec 	=8000;
				break;
			case	14:						// LF1_10s
				OnTime[0]  		=2000;
				LedCycle_Msec 	=10000;
				break;
			case	15:						// F
				OnTime[0]  		=10000;
				LedCycle_Msec 	=10000;
				break;
			case	17:						// isow4s
				OnTime[0]  		=1000;
				LedCycle_Msec 	=4000;
				break;
			case	18:						// isow6s
				OnTime[0]  		=1000;
				LedCycle_Msec 	=6000;
				break;
			case	19:						// isow8s
				OnTime[0]  		=1000;
				LedCycle_Msec 	=8000;
				break;
			case	20:						// isow10s
				OnTime[0]  		=1000;
				LedCycle_Msec 	=10000;
				break;
			default:
				OnTime[0]  		=0;
				LedCycle_Msec 	=10000;
				break;
		}
	}
}



void ActiveOnChk(void)
{

	bActiveOn=1;

	if(AdValue[0] >= SetNightDayVolt){
		if(DayNightTimer > 5 ){
			DayNightTimer=0;
			_LED_GPS_GOOD = !_LED_GPS_GOOD;
		}

		if(AdValue[0] >= SetNightVolt){
			bActiveOn=1;
			_LED_GPS_GOOD=0;
		}
	}
	else{
		bActiveOn=0;
		_LED_GPS_GOOD=1;
	}

	if(bAn0_Updated){
		bAn0_Updated=0;
		if(WakeupTime < 200) WakeupTime++;
	}
}



void ApaLampOnOff(void)
{
	ActiveOnChk();
	if(bActiveOn || !PIN_RB5_NoUse){
		if(!bPwmOn)	PwmOn();

		if(bAn2_Updated && bAn3_Updated){
			bAn2_Updated=0;
 			bAn3_Updated=0;

			if(AdValue[2] < AdValue[3]){
				if(DutyCycle < 0x3ff)	DutyCycle++;
				else					DutyCycle=0x3ff;
				OutPWM();
			}
			else if(AdValue[2] > AdValue[3]){
				if(DutyCycle > 0x0)	DutyCycle--;
				else				DutyCycle=0;

				OutPWM();
			}
		}

		if(Gms60000 <= OnTime[0]){  		// led on
			_APLLAMP=1;
		}
		else if(Gms60000 <= OnTime[1]){  	// led on
			_APLLAMP=0;
		}
		else if(Gms60000 <= OnTime[2]){  	// led on
			_APLLAMP=1;
		}
		else if(Gms60000 <= OnTime[3]){  	// led on
			_APLLAMP=0;
		}
		else if(Gms60000 <= OnTime[4]){  	// led on
			_APLLAMP=1;
		}
		else if(Gms60000 <= OnTime[5]){  	// led on
			_APLLAMP=0;
		}
		else if(Gms60000 <= OnTime[6]){  	// led on
			_APLLAMP=1;
		}
		else if(Gms60000 <= OnTime[7]){  	// led on
			_APLLAMP=0;
		}
		else if(Gms60000 <= OnTime[8]){  	// led on
			_APLLAMP=1;
		}
		else if(Gms60000 <= OnTime[9]){  	// led on
			_APLLAMP=0;
		}
		else if(Gms60000 <= OnTime[10]){  	// led on
			_APLLAMP=1;
		}
		else if(Gms60000 <= OnTime[11]){  	// led on
			_APLLAMP=0;
		}
		else if(Gms60000 <= OnTime[12]){  	// led on
			_APLLAMP=1;
		}
		else if(Gms60000 <= OnTime[13]){  	// led on
			_APLLAMP=0;
		}
		else if(Gms60000 <= OnTime[14]){  	// led on
			_APLLAMP=1;
		}
		else if(Gms60000 <= OnTime[15]){  	// led on
			_APLLAMP=0;
		}
		else if(Gms60000 <= OnTime[16]){  	// led on
			_APLLAMP=1;
		}
		else{
			_APLLAMP=0;
		}

		bPwmOn=1;
		GPS_ON=0;

		_LED_LAMP_ON= !_APLLAMP;
	}
	else{
		if(bPwmOn){
			PwmOff();
			DutyCycle=0x3ff;
			OutPWM();
		}
		bPwmOn=0;

		PIN_PWM=0;
		_APLLAMP=0;
		GPS_ON=1;

		_LED_LAMP_ON=1;

		if(WakeupTime > 0){
			bAn0_Updated=0;
			CLRWDT();
			MainTimer=0;
			WakeupTime=0;
			_LED_GPS_GOOD=1;
			_LED_CDS_IN_NIG=1;

			SLEEP();
		}

	}
}

*/

/*
void SetApaLamp(void)
{
    if (bAn2_Updated) // PIN_RA2_NoUse �Ƴ��α� ���� ������Ʈ ������ ?
    {
        bAn2_Updated = FALSE;

        if (sAPL[0].bSetSwPushOK)		SetAVoltage = SetA1_Volt;
        else if (sAPL[2].bSetSwPushOK)	SetAVoltage = SetA3_Volt;
        // Ad2 �� Ad3(�Ǵ� Ad4) ���� ���Ͽ� Pwm ��Ƽ ���� ���� �Ǵ� ���� �Ѵ�.
        DutyCycle = GetDutyByCompareCurrent(DutyCycle, SetAVoltage, A_IN_Volt, CurDAY_TWL_NIG);

    }
    _LAMP_ON = ON_lamp; // ���� APL ���� ON
    OutPWM(DutyCycle);
    bPwmOn = TRUE;
}
*/
/*
// APL Lamp ��� �Լ��̴�.
void ApaLampOnOff(void)
{
    // bBlink_DutyOn ���� (-On��Ƽ����-)����
    // _LAMP_ON �� PIN_PWM ����� �������� LAMP�� ������ ���� ������.
    if (bBlink_DutyOn)
    {
        if (bPwmOn == FALSE)
            PwmOn();

        if (bAgoBlkLedOff)
        {
            bAgoBlkLedOff = FALSE;
            StartTimer = 0;

            //if (CurDAY_TWL_NIG == DAY)
                //ReadVal(&SavedDutyCycle1, &SavedSetA1_Volt, Saved1Buf, &SetA1_Volt);
            //else
                //ReadVal(&SavedDutyCycle3, &SavedSetA3_Volt, Saved3Buf, &SetA3_Volt);

        }
        else
        {
            if (StartTimer > 100)
            {
                if (bAn2_Updated) // PIN_RA2_NoUse �Ƴ��α� ���� ������Ʈ ������ ?
                {
                    bAn2_Updated = FALSE;

                    if (CurDAY_TWL_NIG == DAY) 	SetAVoltage = SetA1_Volt;
                    else 					SetAVoltage = SetA3_Volt;
                    // Ad2 �� Ad3(�Ǵ� Ad4) ���� ���Ͽ� Pwm ��Ƽ ���� ���� �Ǵ� ���� �Ѵ�.
                    DutyCycle = GetDutyByCompareCurrent(DutyCycle, SetAVoltage, A_IN_Volt, CurDAY_TWL_NIG);
                }
            }
        }
        _LAMP_ON = ON_lamp; // ���� APL ���� ON
        OutPWM(DutyCycle);
        bPwmOn = TRUE;
        _LED_LAMP_ON = ON_runled1; // ���� LED ���� ���� !!!

    }
    else
    {
        if (bPwmOn)
        {
            PwmOff();
            DutyCycle = 0x3ff;
            OutPWM(DutyCycle);
        }
        bPwmOn = FALSE;
        _PWM = 0;
        _LAMP_ON = OFF_lamp;
        _LED_LAMP_ON = OFF_runled1;
        bAgoBlkLedOff = TRUE;
    }
}
*/

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
    unsigned char 	i;
    static 	 bit 	ret;

    ret = FALSE;

    // ��, ����, ���� ����� ��������, ����, ��Ƽ���� ���´�.


    ret = TRUE;
    return(ret);
}


void ProcReadWrite(void)
{
// Read !!!


// Write !!!


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


    while (1)
    {
        CLRWDT();


		Loader_Func(); // �δ� ���� �Լ� 


        ProcReadWrite();


        ProcGPS(); // GPS ��� �� �޽� ���� ó��


        ProcBlink(); // BLink ��� ó��


        ProcDAY_TWL_NIG(); // CDS ��, ����, ���� �ٳ����� �� ó��


        ProcAD();


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
        }
        // �Ϲ� ��� !!!
        else if (sAPL[CurDAY_TWL_NIG].Set_DutyCycle)
        {
            OutAplLamp_WhenNomalMode(CurDAY_TWL_NIG);
            bSetModeReady = TRUE;
        }
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

        msec100++;
        if (msec100 > 100)
        {
            msec100 = 0;
            DayNightTimer++;

            if (SettingReadyTime < 100)	SettingReadyTime++;
            if (NightSetTime < 100)		NightSetTime++;
            if (NightDaySetTime < 100)	NightDaySetTime++;

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




