

#include    <pic18.h>

#include	"Analog.h"
#include	"main.h"
#include	"Commom.h"





// AD 
void	InitAD(void)
{
    ADCON0 = 0x01;	//ADON = 1;
    ADCON1 = 0x80;  //event= timer1
//	ADCON1=0x0;    //event= timer1

    ADFM = 1;		  						// period is an 8 bit value, right justify to get result from ADRESH
    ADCS2 = 1;  ADCS1 = 1; ADCS0 = 0;  	// 1Tad = 2 usec >= 1.6usec
    ACQT2 = 1;  ACQT1 =  0; ACQT0 = 0; 	// acquisition time >= 16~20 usec

    ANCON0 = 0x0f;  // an0-an4
    ANCON1 = 0x0;		// digital

    ADIP = 0;
    ADIF = 0;
    ADIE = 1;

    DONE = 1;

    bAn0_Updated = 0;
    bAn1_Updated = 0;
    bAn2_Updated = 0;
    bAn3_Updated = 0;
    bAn4_Updated = 0;
    bAn5_Updated = 0;
    bAn6_Updated = 0;
    bAn7_Updated = 0;

	bAdCalcEnable = FALSE;
	BefAdChSel = AdChSel = 0; // ä�� �ʱⰪ PIN_RA2_NoUse	
}




void ADRead(void)
{
    unsigned long LongBuf;
    unsigned int i;

//	i=819; // 5 V ���� ������ �� !

    i = 1240; // 3.3 V ���� ������ �� !
    LongBuf = (unsigned long)InPutAD;
    LongBuf = (LongBuf * 100);	//10mV ����.
    LongBuf = (LongBuf / i);
    AdValue[AdChSel] = (unsigned int)(LongBuf);
    switch (AdChSel)
    {
    case    1: // AN1 : PIN_V_IN
        bAn1_Updated = TRUE;
        CHS2 = 0;
        CHS1 = 1;
        CHS0 = 0;
        AdChSel = 2;
        break;		
    case    2: // AN2 : PIN_RA2_NoUse , ��� ���� �� !!
        bAn2_Updated = TRUE;
        CHS2 = 0;
        CHS1 = 1;
        CHS0 = 1;
        AdChSel = 3;
        break;		
    case    3: // AN3 : VR(����)1 �� �б� ��(High)  ���� �� ! 
        bAn3_Updated = TRUE;
        CHS2 = 1;
        CHS1 = 0;
        CHS0 = 0;
        AdChSel = 4;
        break;
    case    4: // AN4 : VR(����)2 �� �б� ��(Low)  ���� �� !
        bAn4_Updated = TRUE;
        CHS2 = 0;
        CHS1 = 0;
        CHS0 = 1;
        AdChSel = 1;
        break;
    default:
        CHS2 = 0;
        CHS1 = 0;
        CHS0 = 1;
        AdChSel = 1;
        break;
    }
}


bit	IsUdtAd(UINT* arInPut_mV, UCHAR* arIs_AdUpd, UCHAR AdChSel)
{
	unsigned long AdVal;
	unsigned char i;
	unsigned char SUM_CNT;
	
    if (bAdConversion)
    {
		if (bAdCalcEnable == FALSE) // ����� ������ ���� ����Ǵ� ���� ������ �߰� �Ͽ���.
		{
			AdCalcWaitCnt++;
			if (AdCalcWaitCnt >= 3)
			{
				bAdCalcEnable = TRUE;
				AdCalcWaitCnt = 0;
			}
		}
		else
		{	
	        SumAD = SumAD + (unsigned long)ADBuf; // 12��Ʈ AD 
			SumCnt++;

			if (eSETMODE) SUM_CNT = 10;
			else SUM_CNT = 100;

	        if (SumCnt >= SUM_CNT)
	        {
				AdVal = (((SumAD * 1000) / 1240) / SumCnt); // 12��Ʈ 3.3V ���� 
				arInPut_mV[AdChSel] = (unsigned int)AdVal; 

				arIs_AdUpd[AdChSel] = TRUE;
				
	            SumAD = 0;
	            SumCnt = 0;
				
				return TRUE;       
	        }
		}
		
        bAdConversion = FALSE;
        DONE = 1;
    }
    return(FALSE);
}


void GetMyAD(void)
{
	UCHAR ch;

	for (ch=0; ch<ADCH_MAX; ch++)
	{
		if (arIs_AdUpd[ch])
		{
			switch (ch)
			{
			case 0:
				AD_A_IN_mV = arInPut_mV[ch];
				bAD_A_IN_mV_Upd = TRUE;
				break;
			case 1:
				AD_V_IN_mV = arInPut_mV[ch];
				break;
			default:
				break;
			}

			for (ch=0; ch<ADCH_MAX; ch++)	arIs_AdUpd[ch] = FALSE;
			break;
		}
	}	
}


UCHAR ChangeAdChSel(UCHAR AdSel, UCHAR ch)
{	
	static unsigned char cnt = 0;
	
    switch (AdSel)
    {
    case 0: // A_IN
    	cnt++;
        if(cnt > 100)
        {
			AdSel = 1; 
			cnt = 0;
        }
        break;		
    case 1: // V_IN 
        AdSel = 0;
        break;		
    default:
		AdSel = 0;		        
        break;
    }
	return AdSel;
}

void Set_AdCh(UCHAR AdSel)
{
	switch (AdSel)
	{
	case 0:
		CHS4 = 0;
		CHS3 = 0;
        CHS2 = 0;
        CHS1 = 0;
        CHS0 = 0;
		break;
	case 1:
		CHS4 = 0;
		CHS3 = 0;
        CHS2 = 0;
        CHS1 = 0;
        CHS0 = 1;		
		break;
	case 2:
		CHS4 = 0;
		CHS3 = 0;
        CHS2 = 0;
        CHS1 = 1;
        CHS0 = 0;		
		break;
	case 3:
		CHS4 = 0;
		CHS3 = 0;
        CHS2 = 0;
        CHS1 = 1;
        CHS0 = 1;		
		break;
	case 4:
		CHS4 = 0;
		CHS3 = 0;
        CHS2 = 1;
        CHS1 = 0;
        CHS0 = 0;		
		break;
	default:
		CHS4 = 0;
		CHS3 = 0;
        CHS2 = 0;
        CHS1 = 0;
        CHS0 = 0;		
		break;
	}
}




