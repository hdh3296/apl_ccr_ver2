
#include    <pic18.h>

#include	"main.h"
#include	"Commom.h"
#include   	"analog.h"
#include	"serial.h"
#include   	"Com1_Port.h"
#include   	"Com2_Port.h"
#include   	"Pwm1.h"
#include   	"setup.h"
#include    "loader_45k80.h"
#include	"Loader_cmd.h"


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
	_LED_NIGHT = 1; // Night ���� LED 				
	_LED_TEST = 1;	
	_LED_LAMP_ON = 1;// APL Lamp On ��Ƽ LED			
	_LED_GPS_GOOD = 1;// GPS RX2 ���Ž�, 'A' ����Ÿ ���� ���� LED 					
}








// GPS ���� ���ŵ� �޽��� üũ�Ѵ�.
// 1�ʸ��� High ���� ���ŵȴ�.
// High Edge ���� üũ�Ѵ�.
void GpsPPS1Chk(void)
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
        _LED_NIGHT = 1;
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
        if (bNight)	_LED_NIGHT = 0;
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
        if (bNightDay)	_LED_NIGHT = 0;
    }
    else
    {
        NightDaySetTime = 0;
        bNightDay = 0;

        NightSetTime = 0;
        bNight = 0;

        if (SettingReadyTime > 4)
        {
            _LED_NIGHT = !_LED_NIGHT;
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
				PwmOut();
			}
			else if(AdValue[2] > AdValue[3]){
				if(DutyCycle > 0x0)	DutyCycle--;
				else				DutyCycle=0;

				PwmOut();
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
			PwmOut();
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
			_LED_NIGHT=1;

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

        if (stApl[0].bSetSwPushOK)		SetAVoltage = SetA1_Volt;
        else if (stApl[2].bSetSwPushOK)	SetAVoltage = SetA3_Volt;
        // Ad2 �� Ad3(�Ǵ� Ad4) ���� ���Ͽ� Pwm ��Ƽ ���� ���� �Ǵ� ���� �Ѵ�.
        DutyCycle = GetDutyByCompareCurrent(DutyCycle, SetAVoltage, A_IN_Volt, CurDayNight);

    }
    _LAMP_ON = ON_lamp; // ���� APL ���� ON
    PwmOut(DutyCycle);
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

            //if (CurDayNight == DAY)
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

                    if (CurDayNight == DAY) 	SetAVoltage = SetA1_Volt;
                    else 					SetAVoltage = SetA3_Volt;
                    // Ad2 �� Ad3(�Ǵ� Ad4) ���� ���Ͽ� Pwm ��Ƽ ���� ���� �Ǵ� ���� �Ѵ�.
                    DutyCycle = GetDutyByCompareCurrent(DutyCycle, SetAVoltage, A_IN_Volt, CurDayNight);
                }
            }
        }
        _LAMP_ON = ON_lamp; // ���� APL ���� ON
        PwmOut(DutyCycle);
        bPwmOn = TRUE;
        _LED_LAMP_ON = ON_runled1; // ���� LED ���� ���� !!!

    }
    else
    {
        if (bPwmOn)
        {
            PwmOff();
            DutyCycle = 0x3ff;
            PwmOut(DutyCycle);
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
bit IsBlink_On(void)
{
    static bit bBlink_DutyOn;

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
        bBlink_DutyOn = TRUE; // APL LAMP ON
    }
    else
    {
        bBlink_DutyOn = FALSE;  // APL LAMP off
    }

    return bBlink_DutyOn;
}

// GPS RX2 ��� ���� �޾Ƽ� Com1TxBuffer�� �Ѱ��ش�.
// GPS ���� Good ��ȣ�� ������, ��,��,�� ������ ���� �����Ѵ�.
void GpsRx2DataProc(void)
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
bit IsInLED_ON(unsigned char bLedState, unsigned char* Timer)
{
    static bit bBlkLedOn;

    bBlkLedOn = TRUE;
    if (bLedState)	//	High
    {
        if (*Timer > 90) // High �� 90ms ���� �Ǹ� ���̴�.
            bBlkLedOn = FALSE;
    }
    else 	// Low, 60Hz �̸� ���̴�. 
    {
        *Timer = 0;
        bBlkLedOn =  TRUE;
    }

    return bBlkLedOn;
}


unsigned char GetDayEveningNight(void)
{
    static bit bDayLed, bNightLed;
    unsigned char ret;

    bNightLed = IsInLED_ON(_IN_NIGHT, &InDayTimer);

    if (bNightLed)
        ret = NIGHT;	// ��
    else
        ret = DAY;		// ��

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







unsigned int GetDutyByCompareCurrent(unsigned int duty, unsigned int setVolt,
                                     unsigned int inVolt, unsigned char CurDayNight)
{
    long double setCurrent; // ��ȯ�� ���������� ���� ���� ��
    long double inCurrent;  // ��ȯ�� �Է� �ǵ�� ���� ��
    long double OffsetDutyCycle;

    if (CurDayNight == DAY) setCurrent = (long double)setVolt * SET_AMP_PER_VOLT1; // 166 x 4 = 664
    else				   setCurrent = (long double)setVolt * SET_AMP_PER_VOLT3; // 380 x 2 = 760

    inCurrent = (((long double)inVolt - 600) / 60) * 1000;  // (635 - 600)/60 * 1000 = 583

    OffsetDutyCycle = ((setCurrent * 6) / 100) + 40; //

    if (setCurrent > inCurrent) // 760 > 583
    {
        if (setCurrent > (inCurrent + OffsetDutyCycle))   // 760 > (583+82)=645
        {
            if (duty < DUTI_MAX)	duty++;
            else				duty = DUTI_MAX;
        }
    }
    else if (setCurrent < inCurrent)
    {
        if ((setCurrent + OffsetDutyCycle) < inCurrent)
        {
            if (duty > 0)		duty--;
        }
    }

    if (AnalogValidTime > 20)
    {
        if (setVolt <= A_SET_V_MIN)
            DutyCycle = 0;
        if (setVolt >= A_SET_V_MAX)
            DutyCycle = DUTI_MAX;
    }

    return duty;
}


void PwOnAplLamp(void)
{
    do
    {
        BefCurDayNight = CurDayNight = GetDayEveningNight(); // NONE, DAY , EVENING , NIGHT �� ����
        if (CurDayNight == NONE)
            DutyCycle = 0x0;
		else
			DutyCycle = stApl[CurDayNight].Set_DutyCycle; 
		_LAMP_ON = TRUE;
		ChangPwmCycleRegedit(CurDayNight);
        PwmOut(DutyCycle);
		
        CLRWDT();
    }
    while (BeginTimer < 100);
}


ULONG GetSetCurrent(unsigned int set_mV, unsigned char CurDayNight)
{
    ULONG Set_Current;

    Set_Current = ((((ULONG)set_mV) * Multip[CurDayNight]) / 1000);

    return Set_Current;
}





unsigned int GetDutyByCmp(unsigned int duty, unsigned int set_mV,
                                 unsigned char DayNig, unsigned int Offset)
{
	
//	Offset = GetOffSet(stApl[0].Set_Current);	

    if (stApl[DayNig].Set_Current > In_Current) 
    {		
        if (stApl[DayNig].Set_Current > (In_Current + Offset))  
        {
            if (duty < DUTI_MAX)	duty++;
            else					duty = DUTI_MAX;
        }
    }
    else if (stApl[DayNig].Set_Current < In_Current)
    {
        if ((stApl[DayNig].Set_Current + Offset) < In_Current)
        {
            if (duty > 0)		duty--;
        }
    }

    if (AnalogValidTime > 20)
    {
        if (set_mV <= A_SET_V_MIN)
            duty = 0;
        if (set_mV >= A_SET_V_MAX)
            duty = DUTI_MAX;
    }

    return duty;
}





// ���� ����ġ ������ �� APL ���� ���� 
void OnAplLampSet(tag_CurDay Sw_DayNig)
{	
	_LAMP_ON = TRUE; // LAMP ON
	if (bAD_A_IN_mV_Upd)
	{
		bAD_A_IN_mV_Upd = FALSE;		
		In_Current = GetInCurrent(AD_A_IN_mV);	// ���� Setting �� In ���� �� �������� 
		
		DutyCycle = GetDutyByCmp(stApl[Sw_DayNig].Set_DutyCycle, 
								 stApl[Sw_DayNig].Set_mV, Sw_DayNig, 0);
		stApl[Sw_DayNig].Set_DutyCycle = DutyCycle;
//		DutyCycle_Avr = AvrDutyCycle(DutyCycle); // Q?? 
	}
	ChangPwmCycleRegedit(Sw_DayNig);
	PwmOut(DutyCycle);		
}

// ����(����) APL LAPM On, Off ó�� 
void OnOffAplLamp(tag_CurDay CurDayNig)
{
	if (bBlink_DutyOn && (CurDayNig != NONE)) // Blink Led �� On �� ��
	{	
		_LAMP_ON = TRUE; // LAMP ON
		if (bStEnab)
		{
			bStEnab = FALSE;
			StDelayTimer = 0; 

//			ReadVal((arSavedBuf + (CurDayNig*4)), &stApl[CurDayNig].Setting_mV, &stApl[CurDayNig].DutyCycle);
//			stApl[CurDayNig].Set_Current = GetSetCurrent(stApl[CurDayNig].Setting_mV, CurDayNig);
			DutyCycle = stApl[CurDayNig].Set_DutyCycle; // ����� ��Ƽ ���� ���� ��Ƽ ���� ��������.
			ChangPwmCycleRegedit(CurDayNig);
			PwmOut(DutyCycle);	

			if (stApl[CurDayNig].Set_Current > JUNG_GIJUN) StDelayTime = 0;
			else	StDelayTime = 100;	
		}
		else
		{
			if (StDelayTimer >= StDelayTime)
			{
				if (bAD_A_IN_mV_Upd)
				{	
					bAD_A_IN_mV_Upd = FALSE;
					In_Current = GetInCurrent(AD_A_IN_mV);	// ���� Setting �� In ���� �� �������� 
					
					if (stApl[CurDayNig].Set_Current > JUNG_GIJUN)
						DutyCycle = GetDutyByCmp(DutyCycle, stApl[CurDayNig].Set_mV, CurDayNig, 0);
					else
						DutyCycle = GetDutyByCmp(DutyCycle, stApl[CurDayNig].Set_mV, CurDayNig, 100);
				}
				ChangPwmCycleRegedit(CurDayNig);
				PwmOut(DutyCycle);
			}			
		}
		
	}
	else // Blink Led �� Off �� ��
	{
		_LAMP_ON = FALSE; // LAMP OFF 
		
		DutyCycle = ((stApl[CurDayNig].Set_DutyCycle * 6) / 100);
		if (DutyCycle >= 20) DutyCycle = DutyCycle + 10;
		else if (DutyCycle >= 10) DutyCycle = DutyCycle - 1;
		else DutyCycle = DutyCycle + 1;
		ChangPwmCycleRegedit(CurDayNig);		
		PwmOut(DutyCycle);	
		bStEnab = TRUE;
		
	}
}



// ���� ���ð��� ���� PIN_PWM �ֱ� ������Ʈ ���� �� ���� 
void ChangPwmCycleRegedit(tag_CurDay CurDayNight)
{
	if (stApl[CurDayNight].Set_Current > JUNG_GIJUN)
	{
		if (T2CON != 0x04)
			T2CON = 0x04; // 2000õ ������ �� �� !
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
			Com1SerialTime = 0;
			Com1RxStatus = STX_CHK;
			Com1TxCurCnt = 0;
			Com1TxTotalCnt = 0;
			TX1IE = 0;
		}
	}

}
*/

// �¾� ��忡�� �¾� ����ġ ������ ���� �� ! ���� DutyCycle, SetA�� ���� !
void WriteProc(void)
{
	if (stApl[SW_DAY].bSetSw_UpEdge)
	{
		if (stApl[SW_DAY].bWriteEnab)
		{	
			WriteVal(DutyCycle, stApl[SW_DAY].Set_mV, (arSavedBuf + (SW_DAY * 4)));
			stApl[SW_DAY].bSetSw_UpEdge = FALSE;
			stApl[SW_DAY].bWriteEnab = FALSE;
		}
		else
		{
			stApl[SW_DAY].bSetSw_UpEdge = FALSE;
		}
	}
	
	if (stApl[SW_NIG].bSetSw_UpEdge)
	{
		if (stApl[SW_NIG].bWriteEnab)
		{			
			WriteVal(DutyCycle, stApl[SW_NIG].Set_mV, (arSavedBuf + (SW_NIG * 4)));
			stApl[SW_NIG].bSetSw_UpEdge = FALSE;
			stApl[SW_NIG].bWriteEnab = FALSE;
		}
		else
		{
			stApl[SW_NIG].bSetSw_UpEdge = FALSE;
		}		
	}	

}

ULONG GetInCurrent(ULONG CurA_IN_mV)
{
	ULONG In_Current;
	
	if(CurA_IN_mV >= 600) 
		In_Current = (((ULONG)CurA_IN_mV - 600) * 1000) / 60;  // (630 - 600)/60 * 1000 = 500 mA 
	else 
		In_Current = 0;

	return In_Current;
}

///////////////////////////
//   ���� �Լ� 			  //
///////////////////////////

void main(void)
{
    unsigned char i;
	UCHAR ch;

    di();
    Initial();
    InitPort();
    InitTimer0();
    InitAD();
    InitPwm1();
    //UserBaudRate();    
    Com2_Init();
	Loader_Com_Init(); // COM1 �ʱ�ȭ 
    ei();

    DONE = 1;	// A/D Conversion Status bit
    TMR0IE = 1;
    SWDTEN = 1;  // Software Controlled Watchdog Timer Enable bit / 1 = Watchdog Timer is on

// ����� �� Read(Load)
	// ��, ����, ���� ����� ��������, ����, ��Ƽ���� ���´�. 
	stApl[0].Set_mV = (UINT)(ULONG)(information[BLOCK_SET_VALUE_DAY]);
	stApl[1].Set_mV = (UINT)(ULONG)(information[BLOCK_SET_VALUE_EVE]);
	stApl[2].Set_mV = (UINT)(ULONG)(information[BLOCK_SET_VALUE_NIG]);
	stApl[0].Set_DutyCycle = (UINT)(ULONG)(information[BLOCK_SET_DUTYCYCLE_DAY]);
	stApl[1].Set_DutyCycle = (UINT)(ULONG)(information[BLOCK_SET_DUTYCYCLE_EVE]);
	stApl[2].Set_DutyCycle = (UINT)(ULONG)(information[BLOCK_SET_DUTYCYCLE_NIG]);
	for (i=0; i<3; i++)
	{	
		stApl[i].Set_Current = GetSetCurrent(stApl[i].Set_mV, i);
	}
    PwOnAplLamp();


    MainTimer = 0;
    msec100 = 0;
	// ������ ����� ������� ���� 
	stApl[0].bBlinkEnab = TRUE;	// TRUE = ������ ON
	stApl[2].bBlinkEnab = TRUE;	


    while (1)
    {
        CLRWDT();

// �δ��� ���� �����ϰ��� �ϴ� ���� �����´�. 
 		Loader_Func(); // 

		// LED �����̴� 1����Ŭ�� ���Ͽ� ON ��Ƽ �ð�(msec) ���� ���Ѵ�.
		// Lamp Blink������ On �ֱ� �ð�(msec)
		DUTY_CNT = (UCHAR)(ULONG)(information[BLOCK_DUTY_CNT]);
		DUTY_RATE = (UCHAR)(ULONG)(information[BLOCK_DUTY_RATE]);		
		if(DUTY_CNT >= 1) LED_CYCLE_MSEC = (60000 / (DUTY_CNT)); 
		LED_ON_DUTY_MSEC = (LED_CYCLE_MSEC * DUTY_RATE) / 100;

		// ���ø������ �ƴ����� ���� ������ ���� ������ ������ ������.
		// ���� ��� ���� 
		L_SetMode_Sel = (UCHAR)(ULONG)(information[BLOCK_SETMODE_SEL]); 
		// �� V_IN ���� �� 
		L_DaySetValue = (UINT)(ULONG)(information[BLOCK_SET_VALUE_DAY]); 
		stApl[SW_DAY].Set_mV = L_DaySetValue; // �� ���� �� 
		L_EveSetValue = (UINT)(ULONG)(information[BLOCK_SET_VALUE_EVE]); 
		stApl[SW_EVE].Set_mV = L_EveSetValue; // �� ���� ��
		L_NigSetValue = (UINT)(ULONG)(information[BLOCK_SET_VALUE_NIG]); 
		stApl[SW_NIG].Set_mV = L_NigSetValue; // �� ���� ��

		// Set_DutyCycle �� Write
		if (L_SetMode_Sel != Bef_L_SetMode_Sel)
		{	
			if (Bef_L_SetMode_Sel >= 1)
			{
				EditDataType = INT_TYPE;
				if (Bef_L_SetMode_Sel == 1) EditFlashAddr = BLOCK_SET_DUTYCYCLE_DAY;
				else if (Bef_L_SetMode_Sel == 2) EditFlashAddr = BLOCK_SET_DUTYCYCLE_EVE;
				else if (Bef_L_SetMode_Sel == 3) EditFlashAddr = BLOCK_SET_DUTYCYCLE_NIG;
				EditDigitData = stApl[Bef_L_SetMode_Sel - 1].Set_DutyCycle;
				Group1_Save();	
			}
			Bef_L_SetMode_Sel = L_SetMode_Sel;
		}



		
//		Chk232TxErr();	
	
// BLink ��� 	
		// Gps : com2 232Rx ����Ÿ ����
        if (Com2RxStatus == RX_GOOD) // GPS RX2 ��� GOOD !
        {
            Com2RxStatus = STX_CHK;
            GpsRx2DataProc();
        }
		GpsPPS1Chk(); // GPS Puls üũ

// CDS ��, �� üũ ��� 
		// ��, �� üũ 
		// �� �϶� NIG LED ON
        CurDayNight = GetDayEveningNight(); // NONE, DAY , EVENING , NIGHT �� �����´�. 
        if(CurDayNight == NIGHT) 	_LED_NIGHT = LED_NIG_ON;
		else						_LED_NIGHT = LED_NIG_OFF;
		// ��, ���� �ٲ� �� ó�� 
		if (CurDayNight != BefCurDayNight)
		{
			BefCurDayNight = CurDayNight;
			bStEnab = TRUE;
		}		


// AD ó�� 
		bUdtAd = IsUdtAd(arInPut_mV, arIs_AdUpd, AdChSel);
        if(bUdtAd) // input AD �� ����.
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

// CCR ��� (APL LAMP ��� ����) 
		// ���� ��� !!!
		// ���ø�忡�� ALP Lamp �¾��� ���´�.
		if (L_SetMode_Sel) 
		{			
			if (bSetSt)
			{
				bSetSt = FALSE;	
				_LAMP_ON = TRUE; // LAMP ON
				T2CON = 0x06; // 2000õ ������ �� �� !
				PwmOut(0);	
				SetStTimer = 0;		
			}
			else if(SetStTimer > 1000)
			{				
				if(L_SetMode_Sel == 1) // �� 
				{
					stApl[SW_DAY].Set_Current 
						= GetSetCurrent(stApl[SW_DAY].Set_mV, SW_DAY);
					OnAplLampSet(SW_DAY);
				}
				else if(L_SetMode_Sel == 2) // ���� 
				{
					stApl[SW_EVE].Set_Current 
						= GetSetCurrent(stApl[SW_EVE].Set_mV, SW_EVE);
					OnAplLampSet(SW_EVE);
				}				
				else if(L_SetMode_Sel == 3) // �� 
				{
					stApl[SW_NIG].Set_Current 
						= GetSetCurrent(stApl[SW_NIG].Set_mV, SW_NIG);
					OnAplLampSet(SW_NIG);
				}
			}
			bStEnab = TRUE;
		}
		// �Ϲ� ��� !!!
		// �Ϲ� ��忡�� APL LAMP On, OFF ó�� 
		else 		
		{
			OnOffAplLamp(CurDayNight);
			bSetSt = TRUE;
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

		Loader_Msec1_Interrpt(); //

        // Blink ó�� 
		if ((CurDayNight == DAY) && (stApl[SW_DAY].bBlinkEnab == FALSE))	
			bBlink_DutyOn = TRUE; // ������ ���� 
		else if ((CurDayNight == NIGHT) && (stApl[SW_NIG].bBlinkEnab == FALSE))	
			bBlink_DutyOn = TRUE; // ������ ���� 
		else 
			bBlink_DutyOn = IsBlink_On();

		if(bBlink_DutyOn) 	_LED_LAMP_ON = ON_runled1; // Run ���� LED On
		else 				_LED_LAMP_ON = OFF_runled1; // Run ���� LED Off

        Com1SerialTime++;
        Com2SerialTime++;

        if (stApl[0].SetSwCharterTimer < 250)
            stApl[0].SetSwCharterTimer++;
        if (stApl[2].SetSwCharterTimer < 250)
            stApl[2].SetSwCharterTimer++;

        if (BeginTimer < 1000)
            BeginTimer++;

        if (AnalogValidTime < 200)
            AnalogValidTime++;

        if (InDayTimer < 0xff)
            InDayTimer++;
		if (SetStTimer < 0xffff)
            SetStTimer++;
		if (StDelayTimer < 0xffff)
            StDelayTimer++;
		

        msec100++;
        if (msec100 > 100)
        {
            msec100 = 0;
            DayNightTimer++;
            MainTimer++;

            if (SettingReadyTime < 100)	SettingReadyTime++;
            if (NightSetTime < 100)		NightSetTime++;
            if (NightDaySetTime < 100)	NightDaySetTime++;

        }

		if(stApl[SW_DAY].SwPushTimer < 0xffff) stApl[SW_DAY].SwPushTimer++;
		if(stApl[SW_DAY].SwTouchCntTimer < 0xffff) stApl[SW_DAY].SwTouchCntTimer++;
		if(stApl[SW_NIG].SwPushTimer < 0xffff) stApl[SW_NIG].SwPushTimer++;
		if(stApl[SW_NIG].SwTouchCntTimer < 0xffff) stApl[SW_NIG].SwTouchCntTimer++;		
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

	Loader_Com_Interrpt(); //

}




