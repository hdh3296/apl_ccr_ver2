
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


	// APL LAMP 제어 
	_LAMP_ON = 0;  			
	_PWM = 0; 
	// LED : 1 = Led Off
	_LED_CDS_DAY  = 1; // CPU RUN				
	_LED_CDS_NIGHT = 1; // Night 상태 LED 				
	_LED_TEST = 1;	
	_LED_LAMP_ON = 1;// APL Lamp On 듀티 LED			
	_LED_GPS_GOOD = 1;// GPS RX2 수신시, 'A' 데이타 수신 상태 LED 					
}








// GPS 에서 수신된 펄스를 체크한다.
// 1초마다 High 값이 수신된다.
// High Edge 값을 체크한다.
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
        _LED_CDS_NIGHT = 1;
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
        if (bNight)	_LED_CDS_NIGHT = 0;
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
        if (bNightDay)	_LED_CDS_NIGHT = 0;
    }
    else
    {
        NightDaySetTime = 0;
        bNightDay = 0;

        NightSetTime = 0;
        bNight = 0;

        if (SettingReadyTime > 4)
        {
            _LED_CDS_NIGHT = !_LED_CDS_NIGHT;
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
				OutPwm();
			}
			else if(AdValue[2] > AdValue[3]){
				if(DutyCycle > 0x0)	DutyCycle--;
				else				DutyCycle=0;

				OutPwm();
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
			OutPwm();
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
			_LED_CDS_NIGHT=1;

			SLEEP();
		}

	}
}

*/

/*
void SetApaLamp(void)
{
    if (bAn2_Updated) // PIN_RA2_NoUse 아날로그 값이 업데이트 됬으면 ?
    {
        bAn2_Updated = FALSE;

        if (stApl[0].bSetSwPushOK)		SetAVoltage = SetA1_Volt;
        else if (stApl[2].bSetSwPushOK)	SetAVoltage = SetA3_Volt;
        // Ad2 와 Ad3(또는 Ad4) 값을 비교하여 Pwm 듀티 값을 증가 또는 감소 한다.
        DutyCycle = GetDutyByCompareCurrent(DutyCycle, SetAVoltage, A_IN_Volt, CurDayNight);

    }
    _LAMP_ON = ON_lamp; // 실제 APL 램프 ON
    OutPwm(DutyCycle);
    bPwmOn = TRUE;
}
*/
/*
// APL Lamp 출력 함수이다.
void ApaLampOnOff(void)
{
    // bBlink_DutyOn 상태 (-On듀티상태-)에서
    // _LAMP_ON 및 PIN_PWM 출력을 내보내면 LAMP에 실제로 불이 켜진다.
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
                if (bAn2_Updated) // PIN_RA2_NoUse 아날로그 값이 업데이트 됬으면 ?
                {
                    bAn2_Updated = FALSE;

                    if (CurDayNight == DAY) 	SetAVoltage = SetA1_Volt;
                    else 					SetAVoltage = SetA3_Volt;
                    // Ad2 와 Ad3(또는 Ad4) 값을 비교하여 Pwm 듀티 값을 증가 또는 감소 한다.
                    DutyCycle = GetDutyByCompareCurrent(DutyCycle, SetAVoltage, A_IN_Volt, CurDayNight);
                }
            }
        }
        _LAMP_ON = ON_lamp; // 실제 APL 램프 ON
        OutPwm(DutyCycle);
        bPwmOn = TRUE;
        _LED_LAMP_ON = ON_runled1; // 상태 LED 깜빡 깜빡 !!!

    }
    else
    {
        if (bPwmOn)
        {
            PwmOff();
            DutyCycle = 0x3ff;
            OutPwm(DutyCycle);
        }
        bPwmOn = FALSE;
        _PWM = 0;
        _LAMP_ON = OFF_lamp;
        _LED_LAMP_ON = OFF_runled1;
        bAgoBlkLedOff = TRUE;
    }
}
*/

// GPS 펄스에 의한 엣지가 생기면 !
// msec 값을 999으로 변경하고
// GPS 시,분,초 변수값에 시간을 저장한다.
bit IsBlink_On(void)
{
    static bit bBlink_DutyOn;

	// 
    if (bPPS_Edge && bPPS_On)
    {
        bPPS_Edge = FALSE;
        if (rx_sec == 59) // 현재 59초 이면 ? 
        {
            Gms1 = 999; // 999 ms 로 변경 
            Gsec = rx_sec; // Gps Rx 시간 값들을 차례로 저장 
            Gmin = rx_min;
            Ghour = rx_hour;
            rx_sec = 0;
        }
    }

    Gms1++; // Timer에 의한 1ms 마다 증가 
    // ms 가 1000(1초)이면 시간 값(초,분,시)을 1씩 증가 시킨다.
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
	// ms 값이 0 일때 ZeroTimer값 갱신 
    if (Gms1 == 0)
    {
        ZeroTimer = (ULONG)((ULONG)Ghour * (ULONG)3600000);
        ZeroTimer = ZeroTimer + (ULONG)((ULONG)Gmin  * (ULONG)60000);
        ZeroTimer = ZeroTimer + (ULONG)((ULONG)Gsec  * (ULONG)1000);
    }
	// 현재 시간값을 ms 단위로 환산
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

// GPS RX2 통신 값을 받아서 Com1TxBuffer로 넘겨준다.
// GPS 수신 Good 신호를 받으면, 시,분,초 변수에 각각 저장한다.
void GpsRx2DataProc(void)
{
    unsigned int i;

    if (Com2RxBuffer[18] == 'A') // GPS 수신 GOOD !
    {
	    _LED_GPS_GOOD = !_LED_GPS_GOOD; // GPS 수신 GOOD 상태 LED
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

    // msec 값 3자리를 각각 Tx버퍼에 저장
    i = (Gms1 % 100);
    Com1TxBuffer[14] = (unsigned char)((Gms1 / 100) + 0x30);
    Com1TxBuffer[15] = (unsigned char)((i / 10) + 0x30);
    Com1TxBuffer[16] = (unsigned char)((i % 10) + 0x30);

    Com2RxBuffer[18] = 0x0;
}



// Blink Led On, Off 판별
bit IsInput_ON(unsigned char bLedState, unsigned char* Timer)
{
    static bit bBlkLedOn;

    bBlkLedOn = TRUE;
    if (bLedState)	//	High
    {
        if (*Timer > 90) // High 가 90ms 유지 되면 낮이다.
            bBlkLedOn = FALSE;
    }
    else 	// Low, 60Hz 이면 밤이다. 
    {
        *Timer = 0;
        bBlkLedOn =  TRUE;
    }

    return bBlkLedOn;
}


unsigned char GetDayEveningNight(void)
{
    static bit bCDS_Day, bCDS_Night;
    unsigned char ret;

    bCDS_Day = IsInput_ON(_CDS_DAY, &CDS_DayTimer);
	bCDS_Night = IsInput_ON(_CDS_NIGHT, &CDS_NightTimer);

    if (bCDS_Day)		_LED_CDS_DAY = LED_CDS_ON;
	else				_LED_CDS_DAY = LED_CDS_OFF;
    if (bCDS_Night) 	_LED_CDS_NIGHT = LED_CDS_ON;
	else				_LED_CDS_NIGHT = LED_CDS_OFF;

	// 고광도용 (낮 / 저녁 / 밤)
	if (_DIP_SW1 == DIPSW_ON)
	{
		if ((bCDS_Day) && (bCDS_Night))
			ret = EVE;	
		else if (bCDS_Day)
			ret = DAY;	
		else if (bCDS_Night)
			ret = NIG;	
		else 
			ret = DAY;
	}
	// 중광도용 (낮 / 밤)
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









// 최초 전원 껐다 켰을 떄 
void PwOffOnLampOut(void)
{
    do
    {
        BefCurDayNight = CurDayNight = GetDayEveningNight(); // NONE, DAY , EVE , NIG 값 저장
		DutyCycle = stApl[CurDayNight].Set_DutyCycle; 
		_LAMP_ON = TRUE;
		ChangPwmCycleRegedit(CurDayNight);
        OutPwm(DutyCycle);
		
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
        if (set_mV <= 0)
            duty = 0;
        if (set_mV >= A_SET_V_MAX)
            duty = DUTI_MAX;
    }

    return duty;
}





// 셋팅 스위치 눌렀을 때 APL 램프 셋팅 
void OnAplLampSet(tag_CurDay Sw_DayNig)
{	
	_LAMP_ON = TRUE; // LAMP ON
	if (bAD_A_IN_mV_Upd)
	{
		bAD_A_IN_mV_Upd = FALSE;		
		In_Current = GetInCurrent(AD_A_IN_mV);	// 현재 Setting 및 In 전류 값 가져오기 
		
		DutyCycle = GetDutyByCmp(stApl[Sw_DayNig].Set_DutyCycle, 
								 stApl[Sw_DayNig].Set_mV, Sw_DayNig, 0);
		stApl[Sw_DayNig].Set_DutyCycle = DutyCycle;
//		DutyCycle_Avr = AvrDutyCycle(DutyCycle); // Q?? 
	}
	ChangPwmCycleRegedit(Sw_DayNig);
	OutPwm(DutyCycle);		
}

// 현재(실제) APL LAPM On, Off 처리 
void OutLampOnOff(tag_CurDay CurDayNig)
{
	if (bBlink_DutyOn) // Blink Led 가 On 일 때
	{	
		_LAMP_ON = TRUE; // LAMP ON
		if (bLampOnReady)
		{
			bLampOnReady = FALSE;
			StDelayTimer = 0; 

//			ReadVal((arSavedBuf + (CurDayNig*4)), &stApl[CurDayNig].Setting_mV, &stApl[CurDayNig].DutyCycle);
//			stApl[CurDayNig].Set_Current = GetSetCurrent(stApl[CurDayNig].Setting_mV, CurDayNig);
			DutyCycle = stApl[CurDayNig].Set_DutyCycle; // 저장된 듀티 값이 현재 듀티 값에 보내진다.
			ChangPwmCycleRegedit(CurDayNig);
			OutPwm(DutyCycle);	

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
					In_Current = GetInCurrent(AD_A_IN_mV);	// 현재 Setting 및 In 전류 값 가져오기 
					
					if (stApl[CurDayNig].Set_Current > JUNG_GIJUN)
						DutyCycle = GetDutyByCmp(DutyCycle, stApl[CurDayNig].Set_mV, CurDayNig, 0);
					else
						DutyCycle = GetDutyByCmp(DutyCycle, stApl[CurDayNig].Set_mV, CurDayNig, 100);
				}
				ChangPwmCycleRegedit(CurDayNig);
				OutPwm(DutyCycle);
			}			
		}
		
	}
	else // Blink Led 가 Off 일 때
	{
		_LAMP_ON = FALSE; // LAMP OFF 
		
		DutyCycle = ((stApl[CurDayNig].Set_DutyCycle * 6) / 100);
		if (DutyCycle >= 20) DutyCycle = DutyCycle + 10;
		else if (DutyCycle >= 10) DutyCycle = DutyCycle - 1;
		else DutyCycle = DutyCycle + 1;
		ChangPwmCycleRegedit(CurDayNig);		
		OutPwm(DutyCycle);	
		bLampOnReady = TRUE;
		
	}
}



// 기준 셋팅값에 따라 PIN_PWM 주기 레지스트 설정 값 변경 
void ChangPwmCycleRegedit(tag_CurDay CurDayNight)
{
	if (stApl[CurDayNight].Set_Current > JUNG_GIJUN)
	{
		if (T2CON != 0x04)
			T2CON = 0x04; // 2000천 간델라 일 떄 !
	}
	else
	{
		if (T2CON != 0x06)
			T2CON = 0x06; // 2000천 간델라 일 떄 !
	}
}

/*
// Tx 에러일 경우 대비, Tx리셋 및 Disable
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

// 셋업 모드에서 셋업 스위치 누르고 뗐을 때 ! 현재 DutyCycle, SetA값 저장 !
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
//   메인 함수 			  //
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
	Loader_Com_Init(); // COM1 초기화 
    ei();

    DONE = 1;	// A/D Conversion Status bit
    TMR0IE = 1;
    SWDTEN = 1;  // Software Controlled Watchdog Timer Enable bit / 1 = Watchdog Timer is on


// 저장된 값 Read(Load) /////////////////////////////////////
	// 낮, 저녁, 밤의 저장된 셋팅전압, 전류, 듀티값을 얻어온다. 
	stApl[DAY].Set_mV = MyReadIntegerData(BLOCK_SET_VALUE_DAY);
	stApl[EVE].Set_mV = MyReadIntegerData(BLOCK_SET_VALUE_EVE);
	stApl[NIG].Set_mV = MyReadIntegerData(BLOCK_SET_VALUE_NIG);
	stApl[DAY].Set_DutyCycle = MyReadIntegerData(BLOCK_SET_DUTYCYCLE_DAY);
	stApl[EVE].Set_DutyCycle = MyReadIntegerData(BLOCK_SET_DUTYCYCLE_EVE);
	stApl[NIG].Set_DutyCycle = MyReadIntegerData(BLOCK_SET_DUTYCYCLE_NIG);
	for (i=0; i<3; i++)
	{	
		stApl[i].Set_Current = GetSetCurrent(stApl[i].Set_mV, i);
	}
    PwOffOnLampOut();
////////////////////////////////////////////////////////////////

    MainTimer = 0;
    msec100 = 0;
	// 깜빡임 기능을 사용할지 여부 
	stApl[0].bBlinkEnab = TRUE;	// TRUE = 깜빡임 ON
	stApl[2].bBlinkEnab = TRUE;	


	//////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////

    while (1)
    {
        CLRWDT();

// 로더를 통해 셋팅하고자 하는 값을 가져온다. ///////////////////////////////
 		Loader_Func(); // 

		// Read !!!
		// LED 깜빡이는 1싸이클에 대하여 ON 듀티 시간(msec) 값을 구한다.
		// Lamp Blink에서의 On 주기 시간(msec)
		DUTY_CNT = MyReadByteData(BLOCK_DUTY_CNT);		
		DUTY_RATE = MyReadByteData(BLOCK_DUTY_RATE);		
		if(DUTY_CNT >= 1) LED_CYCLE_MSEC = (60000 / (DUTY_CNT)); 
		LED_ON_DUTY_MSEC = (LED_CYCLE_MSEC * DUTY_RATE) / 100;

		// 셋팅모드인지 아닌지에 대한 변수와 현재 볼륨값 변수를 만들자.
		// 셋팅 모드 선택 
		eSETMODE = MyReadByteData(BLOCK_SETMODE_SEL);
		// 각 V_IN 셋팅 값 
		stApl[SW_DAY].Set_mV = MyReadIntegerData(BLOCK_SET_VALUE_DAY); // 낮 셋팅 값 
		stApl[SW_EVE].Set_mV = MyReadIntegerData(BLOCK_SET_VALUE_EVE); // 저녁 셋팅 값
		stApl[SW_NIG].Set_mV = MyReadIntegerData(BLOCK_SET_VALUE_NIG); // 밤 셋팅 값

		// Write !!!
		// Set_DutyCycle 값 
		if (eSETMODE != eBefSETMODE)
		{	
			if (eBefSETMODE)
			{
				EditDataType = INT_TYPE;
				if (eBefSETMODE == SETMODE_DAY) EditFlashAddr = BLOCK_SET_DUTYCYCLE_DAY;
				else if (eBefSETMODE == SETMODE_EVE) EditFlashAddr = BLOCK_SET_DUTYCYCLE_EVE;
				else if (eBefSETMODE == SETMODE_NIG) EditFlashAddr = BLOCK_SET_DUTYCYCLE_NIG;
				EditDigitData = stApl[eBefSETMODE - 1].Set_DutyCycle;
				Group1_Save();	
			}
			eBefSETMODE = eSETMODE;
		}

		Multip[DAY] = ((ULONG)MyReadIntegerData(BLOCK_MaxSetADay) * 1000) / A_SET_V_MAX; 
		Multip[EVE] = ((ULONG)MyReadIntegerData(BLOCK_MaxSetAEve) * 1000) / A_SET_V_MAX; 
		Multip[NIG] = ((ULONG)MyReadIntegerData(BLOCK_MaxSetANig) * 1000) / A_SET_V_MAX; 
		
	
// BLink 기능 	////////////////////////////////////////////////
		// Gps : com2 232Rx 데이타 수신
        if (Com2RxStatus == RX_GOOD) // GPS RX2 통신 GOOD !
        {
            Com2RxStatus = STX_CHK;
            GpsRx2DataProc();
        }
		GpsPPS1Chk(); // GPS Puls 체크

		// FU에 의한 Blink 처리 
		bFU_BlkOn = IsInput_ON(_IN_BLINK, &IN_BLK_Timer); // 여기에서 입력 값 On, Off 판별 
		
		// 딥스위치 2번에 따라 Blink를 GPS에 의해 할자 FU에 의해 할지 결정된다.  
		if (_DIP_SW2 == DIPSW_ON) // GPS
		{
			bBlink_DutyOn = bGPS_Blk_ON;
		}
		else // FU : _IN_BLINK 입력 상태 확인 
		{
			bBlink_DutyOn = bFU_BlkOn;
		}
		
		// Blink 에 따른 LED 상태 
		if(bBlink_DutyOn) 	_LED_LAMP_ON = ON_runled1; // Run 상태 LED On
		else 				_LED_LAMP_ON = OFF_runled1; // Run 상태 LED Off

// CDS 낮, 저녁, 밤 체크 기능 ///////////////////////////////////////
		// CDS 값을 읽어셔 표현 
        CurDayNight = GetDayEveningNight(); // NONE, DAY , EVE , NIG 값 가져온다. 
		// 낮, 밤이 바뀔 때 처리 
		if (CurDayNight != BefCurDayNight)
		{
			BefCurDayNight = CurDayNight;
			bLampOnReady = TRUE;
		}		


// AD 처리 ///////////////////////////////////////////////////////
		bUdtAd = IsUdtAd(arInPut_mV, arIs_AdUpd, AdChSel);
        if (bUdtAd) // input AD 값 얻음.
        {			
			GetMyAD(); // 각 AD 값이 Updated 이면, 각 관련 변수에 저장 한다. 		
			AdChSel = ChangeAdChSel(AdChSel, 1); // 채널 변경 	
			Set_AdCh(AdChSel); // 채널 설정 
			
			// AD 채널이 변경 되었다. 
			// 변경시 쓰레기 값이 저장되는 문제 때문에 추가 하였다. 
			if (AdChSel != BefAdChSel)
			{
				bAdCalcEnable = FALSE;
				AdCalcWaitCnt = 0;
				BefAdChSel = AdChSel;
			}
			
			bAdConversion = FALSE;
			DONE = 1;
        }

// CCR 기능 (APL LAMP 출력 제어) ///////////////////////////////////////
		// 셋팅 모드 !!!
		// 셋팅모드에서 ALP Lamp 셋업값 얻어온다.
		if (eSETMODE) 
		{	
			bLampOnReady = TRUE;
			
			if (bSetModeReady)
			{
				bSetModeReady = FALSE;	
				_LAMP_ON = TRUE; // LAMP ON
				T2CON = 0x06; // 2000천 간델라 일 떄 !
				OutPwm(0);	
				SetModeReadyTimer = 0;		
			}
			else if(SetModeReadyTimer > 1000)
			{				
				stApl[eSETMODE-1].Set_Current 
					= GetSetCurrent(stApl[eSETMODE-1].Set_mV, (eSETMODE-1));
				OnAplLampSet(eSETMODE-1);
			}			
		}
		// 일반 모드 !!!
		// 일반 모드에서 APL LAMP On, OFF 처리 
		else 		
		{
			bSetModeReady = TRUE;
			OutLampOnOff(CurDayNight);			
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


        // Gps Timer에 의한 Blink 처리 
		bGPS_Blk_ON = IsBlink_On(); // GPS에 의한 Blimk 이다. 


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
		

        if (CDS_DayTimer < 0xff)
            CDS_DayTimer++;
		if (CDS_NightTimer < 0xff)
            CDS_NightTimer++;
		if (IN_BLK_Timer < 0xff)
            IN_BLK_Timer++;
		
				
		if (SetModeReadyTimer < 0xffff)
            SetModeReadyTimer++;
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

    // GPS Rx2 통신 인터럽트
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




