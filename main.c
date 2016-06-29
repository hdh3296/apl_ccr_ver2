
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
    _LED_CAN_TX = 1;
    _LED_CAN_RX = 1;
    _LED_BLK = 1;// APL Lamp On ��Ƽ LED
    _LED_GPS = 1;// GPS RX2 ���Ž�, 'A' ����Ÿ ���� ���� LED
}








// GPS ���� ���ŵ� �޽��� üũ�Ѵ�.
// 1�ʸ��� High ���� ���ŵȴ�.
// High Edge ���� üũ�Ѵ�.
void ChkGpsPPS1(void)
{
    if (_PPS_GPS) // GPS ��ȣ�� ������ PPS ��ȣ�� �´�. PPS ��ȣ�� 1�ʴٸ� �ɸ���.
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


// ���ǿ��� �Ǵ� ���� Ÿ�̸ӿ� ���� ���� �� ���� 
// �ܺ� ���ǿ��� ���� : ���� ���ǿ��� ���̺�, ĵ 1�и��� ����
// ���� �����̽� ���� : 232�ø��� ����, PPS�� ���� 
// ���� Ÿ�̸� �۵� 
bit IsBlk_DutyOn_ByTimer(void)
{
    static bit bBlk_DutyOn;

// ���� Ÿ�̸ӿ� ���Ͽ� ��,��,�� ���� ������Ʈ 
    Gm1++; // Timer�� ���� 1ms ���� ����
    // ms �� 1000(1��)�̸� �ð� ��(��,��,��)�� 1�� ���� ��Ų��.
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


	if (BlkMode == BM_Master_GPS_IN) // ���� ���ǿ��� 
	{
	    if (bPPS_Edge && bPPS_On) // 1�ʸ��� On 
	    {
	        bPPS_Edge = FALSE;
	        if (rx_sec == 0) // 1�� �� 
	        {
				// ���� GPS ���� �ð� ���� �ð� ���� ������ ���� �Ѵ�. 
				// �ð� ���� �������� ���� Ÿ�̸ӿ� ���Ͽ� ���� �Ǵ� �������̸�, ���������� ���� On ����Ŭ�� �۵��ϱ� ���Ͽ� ���Ǿ� ���� �����̴�. 
	            Gm1 = 0; // 999 ms �� ����(���, �������� ���� Ÿ�̸ӿ� ���Ͽ� 999 + 1 = 1000 �� �ȴ�.) 
	            Gsec = rx_sec; // ���� 59��, Gps Rx �ð� ������ ���ʷ� ����
	            Gmin = rx_min;
	            Ghour = rx_hour;
	        }
	    }
	}	
	else if (BlkMode == BM_Master_GPS_EXT) // �ܺ� ���ǿ��� 
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
		if (byr1Sec_TimerUpd)	// 1�� �ٸ� ĵ ���� Ÿ�̸�
		{
			byr1Sec_TimerUpd = FALSE;
		
			Ghour	= cRxHour;
			Gmin	= cRxMin;
			Gsec	= cRxSec;		 
			Gm1 	= 0;
		} 
	}



// ���� �ð����� msec ������ ��ȯ�Ͽ� �÷��� On���� Off ���� ���θ� �Ǵ��Ѵ�.
    // ms ���� 0 �϶� �ð�,��,�� ���� msec������ ȯ�� 
    // Gm1�� �̸���ũ �̰� 0�� �Ǵ� ������ 1000�̸���ũ �� ���̸� �̶��� 1�ʰ� �� ���̴�. 
    if (Gm1 == 0) // 1�� 
    {
		bCanTxAct = TRUE; // 1�� ���� Tx 
		CanCmd = CMD_TIMER_1SEC;
		
        ZeroTimer = (ULONG)((ULONG)Ghour * (ULONG)3600000);
        ZeroTimer = ZeroTimer + (ULONG)((ULONG)Gmin  * (ULONG)60000);
        ZeroTimer = ZeroTimer + (ULONG)((ULONG)Gsec  * (ULONG)1000); // ��,��,�ʸ� �� ���ļ� �̸���ũ�� ȯ�� �� ��          
    }
    // ���� �ð����� msec ������ ȯ���Ͽ� �÷��� ����Ŭ ������ ���� �������� ���� ������ On���� Off���� ���θ� �� �� �ִ�.
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



// GPS RX2 ��� ���� �޾Ƽ� Com1TxBuffer�� �Ѱ��ش�.
// GPS ���� Good ��ȣ�� ������, ��,��,�� ������ ���� �����Ѵ�.
void ProcGpsRx2Data(void)
{
    unsigned int i;

    if (Com2RxBuffer[18] == 'A') // GPS ���� GOOD !
    {
        _LED_GPS = !_LED_GPS; // GPS ���� GOOD ���� LED
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
    i = (Gm1 % 100);
    Com1TxBuffer[14] = (unsigned char)((Gm1 / 100) + 0x30);
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
        if (*Timer > 90) // High�� 90ms ���� �Ǹ� ���̴�.
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
        BefD_T_N = CurD_T_N = GetDAY_TWL_NIG(); // NONE, DAY , TWL , NIG �� ����
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

    OutPWM(DutyCycle);
}


// ����(����) APL LAPM On, Off ó��
void OutAplLamp_WhenNomalMode(tag_CurDay CurDayNig)
{
    unsigned int i;

    if (bBlkLedOn) // Blink Led �� On �� ��
    {
        _LAMP_ON = TRUE; // LAMP ON

        if (bAD_A_IN_mV_Upd)
        {
            bAD_A_IN_mV_Upd = FALSE;
            In_Current = GetInCurrent(AD_A_IN_mV);	// ���� Setting �� In ���� �� ��������

            if (sAPL[CurDayNig].Set_Current > JUNG_GIJUN)
                DutyCycle = CompareSet_InCurrent(DutyCycle, CurDayNig, 0);
            else
                DutyCycle = CompareSet_InCurrent(DutyCycle, CurDayNig, 100);
        }
        OutPWM(DutyCycle);


    }
    else // Blink Led �� Off �� ��
    {
        if (bAD_A_IN_mV_Upd)
        {
            bAD_A_IN_mV_Upd = FALSE;
            In_Current = GetInCurrent(AD_A_IN_mV);	// ���� Setting �� In ���� �� ��������
        }

        _LAMP_ON = FALSE; // LAMP OFF
        if (CurDayNig == DAY) OutPWM(cF_SET_stDUTYCYCLE_D);
		else if(CurDayNig == TWL) OutPWM(cF_SET_stDUTYCYCLE_T);
		else if(CurDayNig == NIG) OutPWM(cF_SET_stDUTYCYCLE_N);
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
    // LED �����̴� 1����Ŭ�� ���Ͽ� ON ��Ƽ �ð�(msec) ���� ���Ѵ�.
    // Lamp Blink������ On �ֱ� �ð�(msec)
    Blk_1Min_Cnt = cF_BLK_1MIN_CNT; // 1�� ���� �� ȸ ��������
    Blk_DutyRate = cF_BLK_DUTYRATE; // 1ȸ �����ӿ� ���Ͽ� On ���� (%)
    if (Blk_1Min_Cnt >= 1) Blk_DutyCycle = (60000 / (Blk_1Min_Cnt)); // 1ȸ ������ ����Ŭ �̸���ũ 
    Blk_DutyTime = (Blk_DutyCycle * Blk_DutyRate) / 100;

    // �� V_IN ���� ��
    sAPL[DAY].Set_Current = cF_SETCURR_DAY;
    sAPL[TWL].Set_Current = cF_SETCURR_TWL;
    sAPL[NIG].Set_Current = cF_SETCURR_NIG;

    sAPL[DAY].Max_Current = cF_MaxSetA_DAY;
    sAPL[TWL].Max_Current = cF_MaxSetA_TWL;
    sAPL[NIG].Max_Current = cF_MaxSetA_NIG;


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

// ������ġ ������ ���� GPS�� ���� ���� Ÿ�̸Ӹ� ����Ͽ� ��ũ�� ���� 
// FU�� ���ؼ� ��ũ�� ���� ���� �ȴ�. 
void ProcBlink(tag_CurDay CurDayNig)
{
// ������ġ 2���� ���� Blink�� GPS Time�� ���� ���� FU BLK�Է¿� ���� ���� �����ȴ�.
// ����, ������ġ 3���� on �Ǿ� ������ 2�� ����ġ �����ϰ� �ܺ� CAN GPS ���� ���

	bFUOn = IsInput_ON(_IN_FU, &IN_BLK_Timer);

	if ((sAPL[CurDayNig].bEveryOnSet) || bFUOn)
	{
		bBlkLedOn = TRUE;
	}
	else if (BlkMode == BM_Slave_BLK) // slave
	{
		bBlkLedOn = cRxBlkLedOn; // �����ͷκ��� CAN ���ŵ� ��ũ ���� ���� ��ũ �ȴ�. 
	}
    else if (BlkMode == BM_Master_FU) // FU : _IN_FU �Է� ���¿� ���� ��ũ�� ���� �ȴ�. 
    {
//        bBlkLedOn = bFUOn = IsInput_ON(_IN_FU, &IN_BLK_Timer); // ���⿡�� �Է� �� On, Off �Ǻ� ;
    }
	else // GPS(���� �Ǵ� �ܺ�) �Ǵ� ���� Ÿ�̸ӿ� ���� ��ũ�� ���� �ȴ�. 
    {
        bBlkLedOn = bBlkDutyOn;
    }


// Blink �� ���� LED ����
    if (bBlkLedOn)		_LED_BLK = ON_LED; // Run ���� LED On
    else				_LED_BLK = OFF_LED; // Run ���� LED Off

// ��ũ LED ���°� �������� ĵ tx 

	if (bBlkLedOn != bBefBlk_LedOn)
	{
		bBefBlk_LedOn = bBlkLedOn;
		bCanTxAct = TRUE;
		CanCmd = CMD_BLK_EDGE;	
	}	
}

// CDS ��, ����, �� üũ ���
void ProcDAY_TWL_NIG(void)
{
// CDS ���� �о�� ǥ��
	if (myAdr == SLAVE) // slave
    	CurD_T_N = cRxCurD_T_N;
   	else 		
		CurD_T_N = GetDAY_TWL_NIG(); // NONE, DAY , TWL , NIG �� �����´�.

// ��, ���� �ٲ� �� ó��
    if (CurD_T_N != BefD_T_N)
    {
        BefD_T_N = CurD_T_N;
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

// ��, �ڸ�, �� ���� �ִ�ġ�� MAX ���� ���� ���� ������ �����ϱ� ���Ͽ� ���� �Լ��̴�. 
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
// ������ġ5�� On�̸� Slave, off�̸� Master
// <<< ?? ���� ���� �½ÿ��� ���� �����ϵ��� �����ұ�?
		if (_DIP_SW5 == ON_DIPSW)	myAdr = SLAVE; // slave
		else						myAdr = MASTER; // master			

// ��ũ ��� ���� 
		if (myAdr == MASTER) // ������ 
		{
			if (_DIP_SW3 == OFF_DIPSW) // FU ��� 
			{
				BlkMode = BM_Master_FU;
			}
			else // GPS ��� 
			{
				if (_DIP_SW4 == OFF_DIPSW)	BlkMode = BM_Master_GPS_IN; 	// ���� GPS ��� 
				else 						BlkMode = BM_Master_GPS_EXT; // �ܺ� GPS ��� 
			}		
		}
		else // �����̺� 
		{
			BlkMode = BM_Slave_BLK; 
		}
}


// CAN Rx ���� LED ó��
bit SaveCANRxData(void)
{
	
	if (bCAN_RxGood)
	{
		bCAN_RxGood = FALSE;

		cRxCMD = CAN_RcvBuf[0]; // cmd 

		if (myAdr == MASTER) // ������ 
		{	
			// �ܺ� ���ǿ��� ĵ���� ���ŵ� ��� 
			if ((BlkMode == BM_Master_GPS_EXT) && (cRxCMD == CMD_EXTGPS))
			{
				cRxHour 	= CAN_RcvBuf[5]; // ��
				cRxMin		= CAN_RcvBuf[6]; // ��
				cRxSec		= CAN_RcvBuf[7]; // ��
				
				bExtGpsUpd = TRUE;

				_LED_CAN_RX = !_LED_CAN_RX;
				return TRUE;
			}
		}
		else // �����̺� 
		{
			if ((cRxCMD == CMD_BLK_EDGE) || (cRxCMD == CMD_TIMER_1SEC))
			{
				cRxCurD_T_N = CAN_RcvBuf[1]; // ��,�ڸ�,�� ���� 
				cRxBlkLedOn	= CAN_RcvBuf[2]; // ��ũ(�÷���)���� ���� On ���� 
				cRxDReserve0= CAN_RcvBuf[3];
				cRxDReserve1= CAN_RcvBuf[4];
				cRxHour 	= CAN_RcvBuf[5]; // ��
				cRxMin		= CAN_RcvBuf[6]; // ��
				cRxSec		= CAN_RcvBuf[7]; // ��

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
	// CAN Tx ó�� 
	// ���� Ÿ�̸ӿ� ���� 1�ʸ��� tx�� �� �� �ִ�.
	// fu�� ��� �� ���� fu�� on, off �� ������ tx�� �ؾ� �Ѵ�. 
	if (myAdr == MASTER) // master , ������ġ 5���� off�� ���常 tx�����ϴ�. 
	{
		if (bCanTxAct) // �ܺ� GPS ���� �� �Ǵ� 1�ʸ��� ���� �ǵ��� �Ͽ���. ���� GPS ���Ž� ��, 1���� �Ǵ� �������� ���� �ǵ��� �ؾ� �Ѵ�. 
		{	

			// ��, ��, �ڸ� ���� tx ó�� 			        
	        CanDataCnt0 = 8;

			CanKeyValue[0] = CanCmd; // ���� �ýþ˿��� ���� �ýþ� �Ǵ� ���ǿ��� ����� tx / ��,��,�ڸ� ���� tx 
			
	        CanKeyValue[1] = CurD_T_N; // ��,��,�ڸ� ���� 
	        CanKeyValue[2] = bBlkLedOn; // ���� ���� ��ũ ���� 
	        CanKeyValue[3] = 0;
	        CanKeyValue[4] = 0;
	        CanKeyValue[5] = Ghour; // ���� Ÿ�̸� 
	        CanKeyValue[6] = Gmin;  // ���� Ÿ�̸� 
	        CanKeyValue[7] = Gsec;  // ���� Ÿ�̸� 
			
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
	// ���� ���� ���� �δ����� ���� ���Ͽ� ram ���� ������ ���� ���� ������ �����ϰ� �ִ�. <<<
	UserRam_16[viewSET_DUTYCYCLE] = DutyCycle;
	UserRam_16[viewIn_Current]	  = In_Current;
	UserRam_16[viewCurDAY_TWL_NIG] = CurD_T_N;
	UserRam_32[ViewZeroTimer] = CurTotalGms; 
	UserRam_8[ViewBlk] = bBlkLedOn;
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
    InitCom2(); // GPS�� 
    InitComLoader(); // �δ� ����
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


        Loader_Func(); // �δ� ���� �Լ�
		EditLoader_SetA_ByMaxSetA(); // Max�������� ���� �������� ���� �����Ҽ� �ִ� ���� ���� �Ѵ�. 


		ProcReadWrite(); // ���� / �б� ó�� 


		ProcDAY_TWL_NIG(); // CDS ��, �ڸ�, �� ó��          


        ProcGPS(); // GPS �ø��� ��� �� �޽� ���� ó��


        ProcBlink(CurD_T_N); // BLink��庰 ��ũ ó��        


        ProcAD(); // AD ó��         
        

		ViewCurData();
		

		SelDipSW();

// CAN ó�� 
		SaveCANRxData();
		LoadCANTxData(CanCmd);		


// CCR ��� (APL LAMP ��� ����) ///////////////////////////////////////
        
        if (eSETMODE) // ���� ��� !!!
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

            UserSystemStatus = 1; // �δ����� ���� ���� ���� ���� �ֱ����� ���� ���̴�. <<<
        }
		else if (CurD_T_N == NONE)
		{
			OutPWM(0);
			UserSystemStatus = 8;
		}
        else if (sAPL[CurD_T_N].Set_DutyCycle) // �Ϲ� ��� 
        {
            OutAplLamp_WhenNomalMode(CurD_T_N);
            bSetModeReady = TRUE;

            // �δ����� ���� ���� ���� ���� �ֱ����� ���� ���̴�. <<<
            if (CurD_T_N == 0) UserSystemStatus = 2;
            else if (CurD_T_N == 1) UserSystemStatus = 3;
            else if (CurD_T_N == 2) UserSystemStatus = 4;
        }
        else
        {
            // �δ����� ���� ���� ���� ���� �ֱ����� ���� ���̴�. <<<
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


        Loader_Msec1_Interrpt(); // �δ� ���� �Լ�


        // Int_Gps Timer�� ���� Blink ó��
        bBlkDutyOn = IsBlk_DutyOn_ByTimer(); // GPS(��,��) Timer �Ǵ� ���� Timer�� ���� Blink Duty On ���� 


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




