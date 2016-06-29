
//////////////////////////////////////////
//										//
//	APL CCR 통합현 펌웨어 입니다. 			//
//										//
//////////////////////////////////////////



#include    <pic18.h>

#include	"main.h"
#include	"Commom.h"
#include   	"analog.h"
#include	"serial.h"
#include   	"Com2_Port.h"
#include   	"Pwm1.h"

#include    "system\system.h" // 로더 관련
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


    // APL LAMP 제어
    _LAMP_ON = 0;
    _PWM = 0;
    // LED : 1 = Led Off
    _LED_CPU_RUN  = 1; // CPU RUN
    _LED_CAN_TX = 1;
    _LED_CAN_RX = 1;
    _LED_BLK = 1;// APL Lamp On 듀티 LED
    _LED_GPS = 1;// GPS RX2 수신시, 'A' 데이타 수신 상태 LED
}








// GPS 에서 수신된 펄스를 체크한다.
// 1초마다 High 값이 수신된다.
// High Edge 값을 체크한다.
void ChkGpsPPS1(void)
{
    if (_PPS_GPS) // GPS 신호가 터져야 PPS 신호도 온다. PPS 신호는 1초다마 걸린다.
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


// 지피에스 또는 내부 타이머에 의해 램프 온 결정 
// 외부 지피에스 사용시 : 내부 지피에스 디세이블, 캔 1분만다 수신
// 내부 지페이스 사용시 : 232시리얼 수신, PPS에 수신 
// 내부 타이머 작동 
bit IsBlk_DutyOn_ByTimer(void)
{
    static bit bBlk_DutyOn;

// 내부 타이머에 의하여 시,분,초 변수 업데이트 
    Gm1++; // Timer에 의한 1ms 마다 증가
    // ms 가 1000(1초)이면 시간 값(초,분,시)을 1씩 증가 시킨다.
    if (Gm1 >= 1000)
    {
        Gm1 = 0;
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


	if (BlkMode == BM_Master_GPS_IN) // 내부 지피에스 
	{
	    if (bPPS_Edge && bPPS_On) // 1초마다 On 
	    {
	        bPPS_Edge = FALSE;
	        if (rx_sec == 0) // 1분 후 
	        {
				// 내부 GPS 수신 시간 값을 시간 관련 변수에 저장 한다. 
				// 시간 관련 변수들은 내부 타이머에 의하여 갱신 되는 변수들이며, 직접적으로 램프 On 사이클을 작동하기 위하여 사용되어 지는 변수이다. 
	            Gm1 = 0; // 999 ms 로 변경(즉시, 다음에서 내부 타이머에 의하여 999 + 1 = 1000 이 된다.) 
	            Gsec = rx_sec; // 현재 59초, Gps Rx 시간 값들을 차례로 저장
	            Gmin = rx_min;
	            Ghour = rx_hour;
	        }
	    }
	}	
	else if (BlkMode == BM_Master_GPS_EXT) // 외부 지피에스 
	{
		if (bExtGpsUpd)
		{
			bExtGpsUpd = FALSE;

			Ghour	= cRxHour;
	        Gmin 	= cRxMin;
			Gsec 	= cRxSec;        
			Gm1		= 0;			
		}
	}
	else if (BlkMode == BM_Slave_BLK)  
	{
		if (byr1Sec_TimerUpd)	// 1초 다마 캔 수신 타이머
		{
			byr1Sec_TimerUpd = FALSE;
		
			Ghour	= cRxHour;
			Gmin	= cRxMin;
			Gsec	= cRxSec;		 
			Gm1 	= 0;
		} 
	}



// 현재 시간값을 msec 단위로 변환하여 플래싱 On인지 Off 인지 여부를 판단한다.
    // ms 값이 0 일때 시간,분,초 값을 msec값으로 환산 
    // Gm1은 미리세크 이고 0이 되는 순간은 1000미리세크 될 때이면 이때는 1초가 될 때이다. 
    if (Gm1 == 0) // 1초 
    {
		bCanTxAct = TRUE; // 1초 마다 Tx 
		CanCmd = CMD_TIMER_1SEC;
		
        ZeroTimer = (ULONG)((ULONG)Ghour * (ULONG)3600000);
        ZeroTimer = ZeroTimer + (ULONG)((ULONG)Gmin  * (ULONG)60000);
        ZeroTimer = ZeroTimer + (ULONG)((ULONG)Gsec  * (ULONG)1000); // 시,분,초를 다 합쳐서 미리세크로 환산 한 값          
    }
    // 현재 시간값을 msec 단위로 환산하여 플래싱 싸이클 값으로 나눈 나머지로 현재 램프를 On할지 Off할지 여부를 알 수 있다.
    CurTotalGms = ZeroTimer + (ULONG)Gm1;
    Gms60000 = (UINT)((ZeroTimer + (ULONG)Gm1) % (ULONG)Blk_DutyCycle);

    if (Gms60000 < Blk_DutyTime)
    {
        bBlk_DutyOn = TRUE; // APL LAMP ON
    }
    else
    {
        bBlk_DutyOn = FALSE;  // APL LAMP off
    }

	return bBlk_DutyOn;
}



// GPS RX2 통신 값을 받아서 Com1TxBuffer로 넘겨준다.
// GPS 수신 Good 신호를 받으면, 시,분,초 변수에 각각 저장한다.
void ProcGpsRx2Data(void)
{
    unsigned int i;

    if (Com2RxBuffer[18] == 'A') // GPS 수신 GOOD !
    {
        _LED_GPS = !_LED_GPS; // GPS 수신 GOOD 상태 LED
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
    i = (Gm1 % 100);
    Com1TxBuffer[14] = (unsigned char)((Gm1 / 100) + 0x30);
    Com1TxBuffer[15] = (unsigned char)((i / 10) + 0x30);
    Com1TxBuffer[16] = (unsigned char)((i % 10) + 0x30);

    Com2RxBuffer[18] = 0x0;
}



// Blink Led On, Off 판별
bit IsInput_ON(unsigned char bLedState, unsigned char* Timer)
{
    static bit bInputOn;

    bInputOn = TRUE;
    if (bLedState)	//	High
    {
        if (*Timer > 90) // High가 90ms 유지 되면 낮이다.
            bInputOn = FALSE;
    }
    else 	// Low, 60Hz 이면 밤이다.
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


    // 고광도용 (낮 / 저녁 / 밤)
    if (_DIP_SW2 == ON_DIPSW)
    {
        if ((bCDS_Day) && (bCDS_Night))
            ret = TWL;
        else if (bCDS_Day)
            ret = DAY;
        else if (bCDS_Night)
            ret = NIG;
        else
            ret = NONE;
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









// 최초 전원 On시에 셋팅된 값을 토대로 APL 램프의 불을 밝힌다.
void OutLampWhenPowerOn(void)
{
    do
    {
        BefD_T_N = CurD_T_N = GetDAY_TWL_NIG(); // NONE, DAY , TWL , NIG 값 저장
        DutyCycle = sAPL[CurD_T_N].Set_DutyCycle;
        _LAMP_ON = TRUE;
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





// 셋팅 스위치 눌렀을 때 APL 램프 셋팅
void OutAplLamp_WhenSetMode(tag_CurDay Sw_DayNig)
{
    if (bAD_A_IN_mV_Upd)
    {
        bAD_A_IN_mV_Upd = FALSE;
        In_Current = GetInCurrent(AD_A_IN_mV);	// 현재 Setting 및 In 전류 값 가져오기

        sAPL[Sw_DayNig].Set_DutyCycle = DutyCycle = CompareSet_InCurrent(DutyCycle, Sw_DayNig, 0);

//		DutyCycle_Avr = AvrDutyCycle(DutyCycle); // Q??
    }

    OutPWM(DutyCycle);
}


// 현재(실제) APL LAPM On, Off 처리
void OutAplLamp_WhenNomalMode(tag_CurDay CurDayNig)
{
    unsigned int i;

    if (bBlkLedOn) // Blink Led 가 On 일 때
    {
        _LAMP_ON = TRUE; // LAMP ON

        if (bAD_A_IN_mV_Upd)
        {
            bAD_A_IN_mV_Upd = FALSE;
            In_Current = GetInCurrent(AD_A_IN_mV);	// 현재 Setting 및 In 전류 값 가져오기

            if (sAPL[CurDayNig].Set_Current > JUNG_GIJUN)
                DutyCycle = CompareSet_InCurrent(DutyCycle, CurDayNig, 0);
            else
                DutyCycle = CompareSet_InCurrent(DutyCycle, CurDayNig, 100);
        }
        OutPWM(DutyCycle);


    }
    else // Blink Led 가 Off 일 때
    {
        if (bAD_A_IN_mV_Upd)
        {
            bAD_A_IN_mV_Upd = FALSE;
            In_Current = GetInCurrent(AD_A_IN_mV);	// 현재 Setting 및 In 전류 값 가져오기
        }

        _LAMP_ON = FALSE; // LAMP OFF
        if (CurDayNig == DAY) OutPWM(cF_SET_stDUTYCYCLE_D);
		else if(CurDayNig == TWL) OutPWM(cF_SET_stDUTYCYCLE_T);
		else if(CurDayNig == NIG) OutPWM(cF_SET_stDUTYCYCLE_N);
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

// 저장된 값 Read(Load) /////////////////////////////////////
bit ReadSetValueWhenPowerOn(void)
{
    unsigned char     i;
    static   bit     ret;

    ret = FALSE;

    // 낮, 저녁, 밤의 저장된 셋팅전압, 전류, 듀티값을 얻어온다.
    sAPL[DAY].Set_Current = cF_SETCURR_DAY;
    sAPL[TWL].Set_Current = cF_SETCURR_TWL;
    sAPL[NIG].Set_Current = cF_SETCURR_NIG;

    sAPL[DAY].Max_Current = cF_MaxSetA_DAY;
    sAPL[TWL].Max_Current = cF_MaxSetA_TWL;
    sAPL[NIG].Max_Current = cF_MaxSetA_NIG;

    sAPL[DAY].Set_DutyCycle = cF_SET_DUTYCYCLED;
    sAPL[TWL].Set_DutyCycle = cF_SET_DUTYCYCLET;
    sAPL[NIG].Set_DutyCycle = cF_SET_DUTYCYCLEN;

    ret = TRUE;
    return(ret);

}


void ProcReadWrite(void)
{
// Read !!!
    // LED 깜빡이는 1싸이클에 대하여 ON 듀티 시간(msec) 값을 구한다.
    // Lamp Blink에서의 On 주기 시간(msec)
    Blk_1Min_Cnt = cF_BLK_1MIN_CNT; // 1분 기준 몇 회 깜빡일지
    Blk_DutyRate = cF_BLK_DUTYRATE; // 1회 깜빡임에 대하여 On 비율 (%)
    if (Blk_1Min_Cnt >= 1) Blk_DutyCycle = (60000 / (Blk_1Min_Cnt)); // 1회 깜빡임 싸이클 미리세크 
    Blk_DutyTime = (Blk_DutyCycle * Blk_DutyRate) / 100;

    // 각 V_IN 셋팅 값
    sAPL[DAY].Set_Current = cF_SETCURR_DAY;
    sAPL[TWL].Set_Current = cF_SETCURR_TWL;
    sAPL[NIG].Set_Current = cF_SETCURR_NIG;

    sAPL[DAY].Max_Current = cF_MaxSetA_DAY;
    sAPL[TWL].Max_Current = cF_MaxSetA_TWL;
    sAPL[NIG].Max_Current = cF_MaxSetA_NIG;


    // 셋팅모드인지 아닌지에 대한 변수와 현재 볼륨값 변수를 만들자.
    // 셋팅 모드 선택
    eSETMODE = cF_SETMODE_SEL;

    sAPL[DAY].bEveryOnSet = cF_EveryOnSetD;
    sAPL[TWL].bEveryOnSet = cF_EveryOnSetT;
    sAPL[NIG].bEveryOnSet = cF_EveryOnSetN;

// Write !!!
    // Set_DutyCycle 값
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
// Int_Gps : com2 232Rx 데이타 수신
    if (Com2RxStatus == RX_GOOD)
    {
        Com2RxStatus = STX_CHK;

        ProcGpsRx2Data(); // 시간값을 가져온다.
    }

// GPS Puls 체크
    ChkGpsPPS1();

}

// 딥스위치 설정에 따라서 GPS에 의한 내부 타이머를 사용하여 블링크를 할지 
// FU에 의해서 블링크를 할지 결정 된다. 
void ProcBlink(tag_CurDay CurDayNig)
{
// 딥스위치 2번에 따라 Blink를 GPS Time에 의해 할자 FU BLK입력에 의해 할지 결정된다.
// 만일, 딥스위치 3번에 on 되어 있으면 2번 스위치 무시하고 외부 CAN GPS 보드 사용

	bFUOn = IsInput_ON(_IN_FU, &IN_BLK_Timer);

	if ((sAPL[CurDayNig].bEveryOnSet) || bFUOn)
	{
		bBlkLedOn = TRUE;
	}
	else if (BlkMode == BM_Slave_BLK) // slave
	{
		bBlkLedOn = cRxBlkLedOn; // 마스터로부터 CAN 수신된 블링크 값에 의해 블링크 된다. 
	}
    else if (BlkMode == BM_Master_FU) // FU : _IN_FU 입력 상태에 따라서 블링크가 결정 된다. 
    {
//        bBlkLedOn = bFUOn = IsInput_ON(_IN_FU, &IN_BLK_Timer); // 여기에서 입력 값 On, Off 판별 ;
    }
	else // GPS(내부 또는 외부) 또는 내부 타이머에 의해 블링크가 결정 된다. 
    {
        bBlkLedOn = bBlkDutyOn;
    }


// Blink 에 따른 LED 상태
    if (bBlkLedOn)		_LED_BLK = ON_LED; // Run 상태 LED On
    else				_LED_BLK = OFF_LED; // Run 상태 LED Off

// 블링크 LED 상태가 변했으면 캔 tx 

	if (bBlkLedOn != bBefBlk_LedOn)
	{
		bBefBlk_LedOn = bBlkLedOn;
		bCanTxAct = TRUE;
		CanCmd = CMD_BLK_EDGE;	
	}	
}

// CDS 낮, 저녁, 밤 체크 기능
void ProcDAY_TWL_NIG(void)
{
// CDS 값을 읽어셔 표현
	if (myAdr == SLAVE) // slave
    	CurD_T_N = cRxCurD_T_N;
   	else 		
		CurD_T_N = GetDAY_TWL_NIG(); // NONE, DAY , TWL , NIG 값 가져온다.

// 낮, 밤이 바뀔 때 처리
    if (CurD_T_N != BefD_T_N)
    {
        BefD_T_N = CurD_T_N;
    }
}


void ProcAD(void)
{
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
}


// 낮, 박명, 밤 셋팅 최대치를 MAX 셋팅 값에 따라 로더에서 제한 설정 하기 위하여 만든 함수이다.
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

// 낮, 박명, 밤 셋팅 최대치를 MAX 셋팅 값에 따라 설정값 제한하기 위하여 만든 함수이다. 
void EditLoader_SetA_ByMaxSetA(void)
{
    if (bef_MaxSetA_DAY != cF_MaxSetA_DAY ) 
    {
        Loader_ValueSetEdit_sub(7, cF_MaxSetA_DAY);
        bef_MaxSetA_DAY = cF_MaxSetA_DAY;
    }

    if (bef_MaxSetA_TWL != cF_MaxSetA_TWL)
    {
        Loader_ValueSetEdit_sub(8, cF_MaxSetA_TWL);
        bef_MaxSetA_TWL = cF_MaxSetA_TWL;
    }

    if (bef_MaxSetA_NIG != cF_MaxSetA_NIG)
    {
        Loader_ValueSetEdit_sub(9, cF_MaxSetA_NIG);
        bef_MaxSetA_NIG = cF_MaxSetA_NIG;
    }
}


void SelDipSW(void)
{	
// 딥스위치5번 On이면 Slave, off이면 Master
// <<< ?? 최초 전원 온시에만 셋팅 가능하도록 변경할까?
		if (_DIP_SW5 == ON_DIPSW)	myAdr = SLAVE; // slave
		else						myAdr = MASTER; // master			

// 블링크 모드 선택 
		if (myAdr == MASTER) // 마스터 
		{
			if (_DIP_SW3 == OFF_DIPSW) // FU 모드 
			{
				BlkMode = BM_Master_FU;
			}
			else // GPS 모드 
			{
				if (_DIP_SW4 == OFF_DIPSW)	BlkMode = BM_Master_GPS_IN; 	// 내부 GPS 모드 
				else 						BlkMode = BM_Master_GPS_EXT; // 외부 GPS 모드 
			}		
		}
		else // 슬레이브 
		{
			BlkMode = BM_Slave_BLK; 
		}
}


// CAN Rx 상태 LED 처리
bit SaveCANRxData(void)
{
	
	if (bCAN_RxGood)
	{
		bCAN_RxGood = FALSE;

		cRxCMD = CAN_RcvBuf[0]; // cmd 

		if (myAdr == MASTER) // 마스터 
		{	
			// 외부 지피에스 캔으로 수신된 경우 
			if ((BlkMode == BM_Master_GPS_EXT) && (cRxCMD == CMD_EXTGPS))
			{
				cRxHour 	= CAN_RcvBuf[5]; // 시
				cRxMin		= CAN_RcvBuf[6]; // 분
				cRxSec		= CAN_RcvBuf[7]; // 초
				
				bExtGpsUpd = TRUE;

				_LED_CAN_RX = !_LED_CAN_RX;
				return TRUE;
			}
		}
		else // 슬레이브 
		{
			if ((cRxCMD == CMD_BLK_EDGE) || (cRxCMD == CMD_TIMER_1SEC))
			{
				cRxCurD_T_N = CAN_RcvBuf[1]; // 낮,박명,밤 상태 
				cRxBlkLedOn	= CAN_RcvBuf[2]; // 블링크(플래싱)시의 램프 On 상태 
				cRxDReserve0= CAN_RcvBuf[3];
				cRxDReserve1= CAN_RcvBuf[4];
				cRxHour 	= CAN_RcvBuf[5]; // 시
				cRxMin		= CAN_RcvBuf[6]; // 분
				cRxSec		= CAN_RcvBuf[7]; // 초

				if (cRxCMD == CMD_TIMER_1SEC) byr1Sec_TimerUpd = TRUE;
				
				_LED_CAN_RX = !_LED_CAN_RX;
				return TRUE;
			}
		}
	}

	return FALSE;
}



bit LoadCANTxData(unsigned char CanCmd)
{
	// CAN Tx 처리 
	// 내부 타이머에 의해 1초마다 tx를 할 수 있다.
	// fu를 사용 할 때는 fu가 on, off 할 때마다 tx를 해야 한다. 
	if (myAdr == MASTER) // master , 딥스위치 5번이 off인 보드만 tx가능하다. 
	{
		if (bCanTxAct) // 외부 GPS 수신 시 또는 1초마다 참이 되도록 하였다. 내부 GPS 수신시 시, 1분이 되는 순간에도 참이 되도록 해야 한다. 
		{	

			// 낮, 밤, 박명 상태 tx 처리 			        
	        CanDataCnt0 = 8;

			CanKeyValue[0] = CanCmd; // 메인 시시알에서 서브 시시알 또는 지피에스 보드로 tx / 낮,밤,박명 상태 tx 
			
	        CanKeyValue[1] = CurD_T_N; // 낮,밤,박명 상태 
	        CanKeyValue[2] = bBlkLedOn; // 현재 램프 블링크 상태 
	        CanKeyValue[3] = 0;
	        CanKeyValue[4] = 0;
	        CanKeyValue[5] = Ghour; // 내부 타이머 
	        CanKeyValue[6] = Gmin;  // 내부 타이머 
	        CanKeyValue[7] = Gsec;  // 내부 타이머 
			
	        Tx0ConfirmCnt = 1;
			
	        CanTx0();
			
	        if (Tx0ConfirmCnt == 0)
	        {
				bCanTxAct = FALSE;
				_LED_CAN_TX = !_LED_CAN_TX; 
	        }			    
		}	
	}

	return bCanTxAct;
}


void ViewCurData(void)
{
	// 현재 변수 값을 로더에서 보기 위하여 ram 영역 변수에 현재 변수 값들을 저장하고 있다. <<<
	UserRam_16[viewSET_DUTYCYCLE] = DutyCycle;
	UserRam_16[viewIn_Current]	  = In_Current;
	UserRam_16[viewCurDAY_TWL_NIG] = CurD_T_N;
	UserRam_32[ViewZeroTimer] = CurTotalGms; 
	UserRam_8[ViewBlk] = bBlkLedOn;
}


///////////////////////////
//   메인 함수 			  //
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
    InitCom2(); // GPS용 
    InitComLoader(); // 로더 관련
    InitCAN();
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


        Loader_Func(); // 로더 관련 함수
		EditLoader_SetA_ByMaxSetA(); // Max전류값에 따라 셋팅전류 값의 설정할수 있는 값을 제한 한다. 


		ProcReadWrite(); // 쓰기 / 읽기 처리 


		ProcDAY_TWL_NIG(); // CDS 낮, 박명, 밤 처리          


        ProcGPS(); // GPS 시리얼 통신 및 펄스 수신 처리


        ProcBlink(CurD_T_N); // BLink모드별 블링크 처리        


        ProcAD(); // AD 처리         
        

		ViewCurData();
		

		SelDipSW();

// CAN 처리 
		SaveCANRxData();
		LoadCANTxData(CanCmd);		


// CCR 기능 (APL LAMP 출력 제어) ///////////////////////////////////////
        
        if (eSETMODE) // 셋팅 모드 !!!
        {
            _LAMP_ON = TRUE; // LAMP ON
            if (bSetModeReady)
            {
                DutyCycle = 0;
                OutPWM(DutyCycle);
                bSetModeReady = FALSE;
                //SetModeReady_Timer = 0;
            }
            else
            {
                OutAplLamp_WhenSetMode(eSETMODE - 1);
            }

            UserSystemStatus = 1; // 로더에서 현재 상태 값을 보여 주기위한 상태 값이다. <<<
        }
		else if (CurD_T_N == NONE)
		{
			OutPWM(0);
			UserSystemStatus = 8;
		}
        else if (sAPL[CurD_T_N].Set_DutyCycle) // 일반 모드 
        {
            OutAplLamp_WhenNomalMode(CurD_T_N);
            bSetModeReady = TRUE;

            // 로더에서 현재 상태 값을 보여 주기위한 상태 값이다. <<<
            if (CurD_T_N == 0) UserSystemStatus = 2;
            else if (CurD_T_N == 1) UserSystemStatus = 3;
            else if (CurD_T_N == 2) UserSystemStatus = 4;
        }
        else
        {
            // 로더에서 현재 상태 값을 보여 주기위한 상태 값이다. <<<
            if (CurD_T_N == 0) UserSystemStatus = 5;
            else if (CurD_T_N == 1) UserSystemStatus = 6;
            else if (CurD_T_N == 2) UserSystemStatus = 7;
        }
		
    } // end while(1)
}



void interrupt isr(void)
{
    if (TMR0IF)
    {
        TMR0IF = 0 ;
        TMR0L = MSEC_L;
        TMR0H = MSEC_H;


        Loader_Msec1_Interrpt(); // 로더 관련 함수


        // Int_Gps Timer에 의한 Blink 처리
        bBlkDutyOn = IsBlk_DutyOn_ByTimer(); // GPS(내,외) Timer 또는 내부 Timer에 의한 Blink Duty On 여부 


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
        if (msec > 50)
        {
            msec = 0;

            _LED_CPU_RUN = !_LED_CPU_RUN;

        }
		
		myTestTimerTx++;
		if (myTestTimerTx > 1000)
		{
			myTestTimerTx = 0;			
		}


    }


    if (PIR5 > 0)
    {
        CanInterrupt();
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

    Loader_Com_Interrpt(); // 로더 관련 함수
}




