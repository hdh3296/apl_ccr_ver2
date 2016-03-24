

#include    <pic18.h>
//#include    "..\..\system_com\memory_map.h"
//#include    "..\comm_4480\iodef.h"
#include 	"you_can.h"


#define		CPU45K80	1
#define		U_COMPILER		1


#if defined(CPU65K80)  || defined(CPU45K80)

#define	TXB0REQ		TXB0CONbits.TXREQ // Transmit Request Status bit

#define	RXB0FUL		RXB0CONbits.RXFUL
#define	RXB0FILHIT0 RXB0CONbits.FILHIT0
#define	RXB0FILHIT1 RXB0CONbits.FILHIT1
#define	RXB0FILHIT2 RXB0CONbits.FILHIT2
#define	RXB0RTRRO 	RXB0CONbits.RXRTRRO

#define	TXB1REQ		TXB1CONbits.TXREQ
#define	RXB1FUL		RXB1CONbits.RXFUL
#define	RXB1FILHIT0 RXB1CONbits.FILHIT0
#define	RXB1FILHIT1 RXB1CONbits.FILHIT1
#define	RXB1FILHIT2 RXB1CONbits.FILHIT2
#define	RXB1RTRRO 	RXB1CONbits.RXRTRRO


#define	RXB0M0		RXB0CONbits.RXM0
#define	RXB0M1		RXB0CONbits.RXM1
#define	RXB0DBEN	RXB0CONbits.RB0DBEN



#define	RXB1M0		RXB1CONbits.RXM0
#define	RXB1M1		RXB1CONbits.RXM1
#define	RXB1DBEN	RXB1CONbits.RB1DBEN


#define	RXB0IF		PIR5bits.RXB0IF
#define	RXB1IF		PIR5bits.RXB1IF


#define	RXF0EXIDEN	RXF0SIDLbits.EXIDEN
#define	RXF1EXIDEN	RXF1SIDLbits.EXIDEN
#define	RXF2EXIDEN	RXF2SIDLbits.EXIDEN
#define	RXF3EXIDEN	RXF3SIDLbits.EXIDEN
#define	RXF4EXIDEN	RXF4SIDLbits.EXIDEN
#define	RXF5EXIDEN	RXF5SIDLbits.EXIDEN



#define	TXB0IE		TXBIEbits.TXB0IE
#define	TXB1IE		TXBIEbits.TXB1IE
#define	TXB2IE		TXBIEbits.TXB2IE

#define	RXB0IE		BIE0bits.RXB0IE
#define	RXB1IE		BIE0bits.RXB1IE


#define	TXB2REQ		TXB2CONbits.TXREQ

#define	TXB0RTR		TXB0DLCbits.TXRTR

#endif






extern     	void         	MyLampCheck(void);
extern		unsigned char  	SyncButtonCheck(unsigned char src);

extern		void			CmdSetupChk(unsigned char id);


extern      unsigned    char    CallMeAdr;
extern  	unsigned    char    LocalNumber;
extern      unsigned    char    SrcAddress;

extern      bit    MaskSetBit;              //new

unsigned    char    NoCanInt = 0;
unsigned    int     CanTime = 0;
unsigned    char    CAN_RcvBuf[MAX_SAVE_BUF];
unsigned    char    bCanTxAct;
unsigned    char    CanKeyValue[8];
unsigned    char    CanCmd;
unsigned    char    Company;
unsigned    char    SelHostAdr;
unsigned    char    CanDataCnt0;
unsigned    char    CanDatacnt1;
unsigned    char    CAN_ReceivedAdr;
unsigned    char    CanReceiveCnt;
unsigned    long    EidBuffer;
unsigned    int     SidBuffer;
unsigned    long    RxEidBuffer;
unsigned    int     RxSidBuffer;

unsigned    char    Tx1ConfirmCnt = 0;
unsigned    char    Tx0ConfirmCnt = 0;

unsigned    char    CanLiveTimeAdr[MAX_ELEV];
unsigned    char    EqualDataBuf[8];

//unsigned    char    CarkeyBuf[8];

///////////////////////


void CAN_SetPort(void)//------------------------------------------------------------------------
{
    TRISB3 = 1 ; // CAN RX
    TRISB2 = 0 ; // CAN TX

#ifdef		 U_COMPILER
    CANCONbits.REQOP = 4 ;// Entry Configration Mode

#else
    REQOP2 = 1 ;// Entry Configration Mode
    REQOP1 = 0 ;
    REQOP0 = 0 ;
#endif


}


void CAN_SetBaudrate(void)
{
    SEG2PHTS = 1 ;      // Freely programmable
    SAM      = 1 ;      // Bus Line is sampled three times prior to the sample point

    SEG2PH2	 = 0 ;      // 2Tq
    SEG2PH1	 = 0 ;
    SEG2PH0	 = 1 ;

    PRSEG2	 = 0 ;      // 3xTq
    PRSEG1	 = 1 ;
    PRSEG0	 = 0 ;

    SEG1PH2	 = 0 ;      // 2Tq
    SEG1PH1	 = 0 ;
    SEG1PH0	 = 1 ;


    SJW1    = 0 ;       // 1Tq
    SJW0    = 0 ;


    BRP5    = 0 ;       // Tq = (2x4)/Fosc = (2x4)/8000000 = 1us
    BRP4    = 1 ;
    BRP3    = 0 ;
    BRP2    = 0 ;
    BRP1    = 1 ;  // BRP is setting value 4 when Fosc is 8 Mhz ( tq=0.00000125 )
    BRP0    = 1 ;


    BRP5    = 1 ; // Tq = 0.00000125/2
    BRP4    = 0 ;
    BRP3    = 0 ;
    BRP2    = 1 ;
    BRP1    = 1 ;
    BRP0    = 1 ;

}


void CAN_SetFilter_SUB(char filter_no, unsigned int sid, unsigned long eid)
{
    unsigned int uppereid;
    volatile unsigned char * pt;

    sid     = (sid << 5) & 0xffe0;
    eid     = (eid & 0x0003ffff);
    uppereid = (unsigned int)(eid >> 16);
    sid     = (sid | uppereid);

    uppereid = (unsigned int)(eid);


    switch (filter_no)
    {
    case 0:
        pt = (&RXF0SIDH);
        break;
    case 1:
        pt = (&RXF1SIDH);
        break;
    case 2:
        pt = (&RXF2SIDH);
        break;
    case 3:
        pt = (&RXF3SIDH);
        break;
    case 4:
        pt = (&RXF4SIDH);
        break;
    case 5:
        pt = (&RXF5SIDH);
        break;
    default:
        pt = (&RXF0SIDH);
        break;

    }


    *(pt + 0)  = (unsigned char)(sid >> 8);
    *(pt + 1)  = (unsigned char)(sid | 0x08);
    *(pt + 2)  = (unsigned char)(uppereid >> 8);
    *(pt + 3)  = (unsigned char)(uppereid);

}



void CAN_SetMask_SUB(char mask_no, unsigned int sid, unsigned long eid)
{
    unsigned int uppereid;


    sid     = (sid << 5) & 0xffe0;
    eid     = (eid & 0x0003ffff);
    uppereid = (unsigned int)(eid >> 16);
    sid     = (sid | uppereid);
    uppereid = (unsigned int)(eid);

    switch (mask_no)
    {
    case 0:
        RXM0SIDH = (unsigned char)(sid >> 8);
        RXM0SIDL = (unsigned char)(sid);
        RXM0EIDH = (unsigned char)(uppereid >> 8);
        RXM0EIDL = (unsigned char)(uppereid);
        break;
    case 1:
        RXM1SIDH = (unsigned char)(sid >> 8);
        RXM1SIDL = (unsigned char)(sid);
        RXM1EIDH = (unsigned char)(uppereid >> 8);
        RXM1EIDL = (unsigned char)(uppereid);
        break;
    default:
        RXM0SIDH = (unsigned char)(sid >> 8);
        RXM0SIDL = (unsigned char)(sid);
        RXM0EIDH = (unsigned char)(uppereid >> 8);
        RXM0EIDL = (unsigned char)(uppereid);
        break;
    }
}




/*
void CANTxSidEidSet1(char MsgFlag,unsigned int sid, unsigned long eid)
{
    unsigned int uppereid;

    sid     =(sid << 5) & 0xffe0;
    eid     =(eid & 0x0003ffff);
    uppereid=(unsigned int)(eid >> 16);
    sid     =(sid | uppereid);

    uppereid =(unsigned int)(eid);

    switch(MsgFlag)
    {
    case 0:
      TXB0SIDH  = (unsigned char)(sid >> 8);
      TXB0SIDL  = (TXB0SIDL & 0x08) | (unsigned char)(sid);
      TXB0EIDH  = (unsigned char)(uppereid >> 8);
      TXB0EIDL  = (unsigned char)(uppereid);
      break;
    case 1:
      TXB1SIDH  = (unsigned char)(sid >> 8);
      TXB1SIDL  = (TXB1SIDL & 0x08) | (unsigned char)(sid);
      TXB1EIDH  = (unsigned char)(uppereid >> 8);
      TXB1EIDL  = (unsigned char)(uppereid);
      break;
    case 2:
      TXB2SIDH  = (unsigned char)(sid >> 8);
      TXB2SIDL  = (TXB2SIDL & 0x08) | (unsigned char)(sid);
      TXB2EIDH  = (unsigned char)(uppereid >> 8);
      TXB2EIDL  = (unsigned char)(uppereid);
      break;
    default:
      TXB0SIDH  = (unsigned char)(sid >> 8);
      TXB0SIDL  = (TXB0SIDL & 0x08) | (unsigned char)(sid);
      TXB0EIDH  = (unsigned char)(uppereid >> 8);
      TXB0EIDL  = (unsigned char)(uppereid);
      break;
    }
}
*/

/*
void CANTxDLC1(char MsgFlag,unsigned char DataCnt)
{

    switch(MsgFlag)
    {
    case 0:
      TXB0DLC  = (TXB0DLC & 0x40) | DataCnt;
      break;
    case 1:
      TXB1DLC  = (TXB0DLC & 0x40) | DataCnt;
      break;
    case 2:
      TXB2DLC  = (TXB0DLC & 0x40) | DataCnt;
      break;
    default:
      TXB0DLC  = (TXB0DLC & 0x40) | DataCnt;
      break;
    }
}
*/



void CANTxSidEidSet(char MsgFlag, unsigned int sid, unsigned long eid) // MsgFlag=0(기본) , SidBuffer, EidBuffer
{
    unsigned int uppereid;

    sid     = (sid << 5) & 0xffe0;
    eid     = (eid & 0x0003ffff);
    uppereid = (unsigned int)(eid >> 16);
    sid     = (sid | uppereid);

    uppereid = (unsigned int)(eid);


    switch (MsgFlag)
    {
    case 0:
        TXB0SIDH  = (unsigned char)(sid >> 8);
        TXB0SIDL  = (unsigned char)(sid);
        TXB0SIDL  = (TXB0SIDL | 0x08);
        TXB0EIDH  = (unsigned char)(uppereid >> 8);
        TXB0EIDL  = (unsigned char)(uppereid);
        break;
    case 1:
        TXB1SIDH  = (unsigned char)(sid >> 8);
        TXB1SIDL  = (unsigned char)(sid);
        TXB1SIDL  = (TXB1SIDL | 0x08);
        TXB1EIDH  = (unsigned char)(uppereid >> 8);
        TXB1EIDL  = (unsigned char)(uppereid);
        break;
    case 2:
        TXB2SIDH  = (unsigned char)(sid >> 8);
        TXB2SIDL  = (unsigned char)(sid);
        TXB2SIDL  = (TXB2SIDL | 0x08);
        TXB2EIDH  = (unsigned char)(uppereid >> 8);
        TXB2EIDL  = (unsigned char)(uppereid);
        break;
    default:
        TXB0SIDH  = (unsigned char)(sid >> 8);
        TXB0SIDL  = (unsigned char)(sid);
        TXB0SIDL  = (TXB0SIDL | 0x08);
        TXB0EIDH  = (unsigned char)(uppereid >> 8);
        TXB0EIDL  = (unsigned char)(uppereid);
        break;
    }

}



void CANTxDLC(char MsgFlag, unsigned char DataCnt)
{
    switch (MsgFlag)
    {
    case 0:
        TXB0DLC  = DataCnt;
        break;
    case 1:
        TXB1DLC  = DataCnt;
        break;
    case 2:
        TXB2DLC  = DataCnt;
        break;
    default:
        TXB0DLC  = DataCnt;
        break;
    }
}








/*
void    CanCheck(void)
{

    if(!TXB0REQ && (CanTime >100)){
        TXB0D0=CanBuf[0];
        TXB0D1=CanBuf[1];
        TXB0D2=CanBuf[2];
        TXB0D3=CanBuf[3];
        TXB0D4=CanBuf[4];
        TXB0D5=CanBuf[5];
        TXB0D6=CanBuf[6];
        TXB0D7=CanBuf[7];

        TXB0REQ = 1 ; // 전송 요구 비트 셋
        CanTime=0;
    }

}
*/




void    CanLiveChk(void)
{
    unsigned char id, i;
    unsigned int  IdPt;

    TXERRCNT = 0;
    RXERRCNT = 0;

    for (id = 0;id < MAX_ELEV;id++)
    {
        if (CanLiveTimeAdr[id] > 120)
        {
            IdPt = (id * HOST_DATA_RECOD);
			
            for (i=0; i<HOST_DATA_RECOD; i++)  CAN_RcvBuf[IdPt+i] = 0x0;
            CanLiveTimeAdr[id] = 0;
        }
    }

    if (NoCanInt > 100)
    {
        CAN_Init();
        NoCanInt = 0;
    }
}


void    CAN_ArraryTxSidEid(void)
{
    unsigned int  itmp1, itmp2;
    unsigned long ltmp1;

    itmp1 = (unsigned int)Company; // 회사 아이디 저장 
    itmp2 = (unsigned int)GROUP_NUMBER; // 그룹 넘버 저장 
    itmp2 = (itmp2 << 7);
    SidBuffer = (unsigned int)(itmp2 | itmp1);

    ltmp1 = 0;
    ltmp1 = (ltmp1 | (unsigned long)SelHostAdr);
    ltmp1 = (ltmp1 << 14);
    ltmp1 = (ltmp1 | (unsigned long)CallMeAdr);

    EidBuffer = ltmp1;
}


void    CAN_ArraryRxSidEid(void)
{
    unsigned int  itmp1, itmp2;
    unsigned long ltmp1;
    unsigned char TmpRcvAdr;

    itmp1 = (RXB0SIDH << 8);
    itmp2 = RXB0SIDL;
    RxSidBuffer = (unsigned int)(itmp1 | itmp2);
    RxSidBuffer = (RxSidBuffer >> 5);

    ltmp1 = (unsigned long)(RXB0SIDL & 0x03);
    RxEidBuffer = (ltmp1 << 16);

    ltmp1 = (unsigned long)(RXB0EIDH);
    ltmp1 = (ltmp1 << 8);
    RxEidBuffer = (RxEidBuffer | ltmp1);

    ltmp1 = (unsigned long)(RXB0EIDL);
    RxEidBuffer = (RxEidBuffer | ltmp1);

    TmpRcvAdr = (unsigned char)((RxEidBuffer & HOST_ADDRESS) >> 14);
    CAN_ReceivedAdr = (unsigned char)(TmpRcvAdr & 0x03);
    SrcAddress = (unsigned char)(TmpRcvAdr & 0x03);


    if (MAX_ELEV == 8)
    {
        TmpRcvAdr = (unsigned char)((RxEidBuffer & NEW_HOST_ADDRESS) >> 14);
        CAN_ReceivedAdr = (unsigned char)(TmpRcvAdr & 0x07);
        SrcAddress = (unsigned char)(TmpRcvAdr & 0x07);
    }
}



void    CAN_SetFilter(void)
{
    unsigned char i;
	
    CAN_ArraryTxSidEid();
	
    for (i = 0;i <= 5;i++)
    {
        CAN_SetFilter_SUB(i, SidBuffer, 0x0);
    }
}


void    CAN_SetMask(void)       //new
{
    CAN_ArraryTxSidEid();

    if (MaskSetBit)
    {
        CAN_SetMask_SUB(0, 0x007f, 0x0);
        CAN_SetMask_SUB(1, 0x007f, 0x0);
    }
    else
    {
        CAN_SetMask_SUB(0, 0x0000, 0x0);
        CAN_SetMask_SUB(1, 0x0000, 0x0);
    }
}


void    LoadCanTxBuf(unsigned char *pt)
{
    unsigned char	i;
	
    for (i=0; i<8; i++)	*(pt + i) = CanKeyValue[i];
}



void    CanTx0(void)
{
    if (!TXB0REQ && bCanTxAct && (CAN_ReceivedAdr == SelHostAdr))
    {
        CAN_ArraryTxSidEid(); // Tx를 위한 SidEidBuffer 세팅  
        CANTxDLC(0, CanDataCnt0); // DLC 세팅  
        CANTxSidEidSet(0, SidBuffer, EidBuffer); // sid, eid 레지스터에 저장 

        CanKeyValue[0] = CanCmd;

        LoadCanTxBuf((unsigned char *)&TXB0D0); // data 레지스터에 저장 

#if  defined(CPU65K80)   ||  defined(CPU45K80)
        IPR5 = 0; // IPR5: PERIPHERAL INTERRUPT PRIORITY REGISTER 5
#else
        IPR3 = 0;
#endif

        TXB0IP = 1; // TXB0IP: CAN Transmit Buffer 0 Interrupt Priority bit
        TXB0REQ = 1 ; // 전송 요구 비트 셋 : TX 시작 하기전 반드시 1로 셋 해줘야만 Tx를 하기 시작한다. 

        CanReceiveCnt = 0;

        if (Tx0ConfirmCnt > 0)    Tx0ConfirmCnt--;
    }
}



void    CanTx1(void)
{
    if (!TXB1REQ && bCanTxAct && (CAN_ReceivedAdr == SelHostAdr))
    {
        CAN_ArraryTxSidEid();
        CANTxDLC(1, CanDatacnt1);
        CANTxSidEidSet(1, SidBuffer, EidBuffer);

        CanKeyValue[0] = CanCmd;

        LoadCanTxBuf((unsigned char *)&TXB1D0);


#if  defined(CPU65K80)   ||  defined(CPU45K80)
        IPR5 = 0;
#else
        IPR3 = 0;
#endif

        TXB1IP = 1;

        TXB1REQ = 1 ; // 전송 요구 비트 셋
        CanReceiveCnt = 0;

        if (Tx1ConfirmCnt > 0)    Tx1ConfirmCnt--;
    }
}




unsigned int	CanInterrupt(void)
{
    unsigned int i, j, hostnm;
    unsigned char *ptr;


    if (IRXIF)
    {
        IRXIF = 0;
    }
    else if (WAKIF)
    {
        WAKIF = 0;
    }
    else if (ERRIF)
    {
        ERRIF = 0;
        if (RXB0OVFL)
        {
            RXB0OVFL = 0;
        }
        if (RXB1OVFL)
        {
            RXB1OVFL = 0;
        }
        if (TXBO)
        {
            TXBO = 0;
        }
        if (TXBP)
        {
            TXBP = 0;
        }
        if (RXBP)
        {
            RXBP = 0;
        }
        if (TXWARN)
        {
            TXWARN = 0;
        }
        if (RXWARN)
        {
            RXWARN = 0;
        }
        if (EWARN)
        {
            EWARN = 0;
        }
        COMSTAT = 0;
    }
    else if (RXB1IF)
    {
        RXB1IF = 0;
    }

    else if (RXB0IF)
    {
        NoCanInt = 0;
		
        CAN_ArraryRxSidEid(); // CAN SID, EID 및 어드레스 저장
        
		// CAN DATA 들을 버퍼에 순서데로 저장한다.  
        ptr = (unsigned char*) & RXB0D0;                        // TXB0D0레지스터 주소를 구하여 ptr변수에 지정
        for (i = 0; i<8; i++)    CAN_RcvBuf[i+CAN_RCV_DATA] = ptr[i];    // Buff배열에 있는 데이터를 TXB0D0~D7까지 차례로 저장

        RXB0IF = 0;
        RXB0FUL = 0;
    }

    return(0);
}





void CAN_Init(void)
{
    unsigned int i;

    CAN_SetPort();
    CAN_SetBaudrate();

    ENDRHI = 1; // CANTX pin will drive when recessive
    CANCAP = 0; // enable CAN Capture mode
    WAKFIL = 0; // CAN bus line filter is not used for wake-up

    /***********************************************/
    RXB0FUL     = 0;   // clear receive buffer0 full flag
    RXB0M1      = 1;   // Receive extended identifier valid messages
    RXB0M0      = 0;   // Receive extended identifier valid messages
    RXB0DBEN    = 0;   // no data write Receive buffer0 to receive buffer1
    RXB0FILHIT0 = 0;    // acceptance filter0
    RXB0RTRRO   = 0;   // No remote transfer request(read only)
    JTOFF       = 0;   // (read only)
    /***********************************************/

    /***********************************************/
    RXB1FUL     = 0 ;
    RXB1M1      = 1 ; // Receive extended identifier valid messages
    RXB1M0      = 0 ;
    RXB1FILHIT2 = 0 ; //filter2
    RXB1FILHIT1 = 1 ;
    RXB1FILHIT0 = 0 ;
    RXB1RTRRO   = 0 ; // No remote transfer request(read Only)
    /***********************************************/

    RXF0EXIDEN = 1;
    RXF1EXIDEN = 1;
    RXF2EXIDEN = 1;
    RXF3EXIDEN = 1;
    RXF4EXIDEN = 1;
    RXF5EXIDEN = 1;


    CAN_SetFilter();
    CAN_SetMask();

    TXB0RTR  = 0;

    TXB0REQ = 0 ;   
    TXB1REQ = 0 ;
    TXB2REQ = 0 ;


    RXB1IP = 0;


#if  defined(CPU65K80)   ||  defined(CPU45K80)
    IPR5 = 0;
#else
    IPR3 = 0;
#endif

    IRXIE       = 0;
    WAKIE       = 0;
    ERRIE       = 1;
    TXB2IE      = 0;
    TXB1IE      = 0;
    TXB0IE      = 0;

    RXB1IE      = 1;
    RXB0IE      = 1;





#ifdef		 U_COMPILER		1
    CANCONbits.REQOP = 0 ;// Entry Configration Mode
#else
    REQOP2 = 0 ;// Entry Configration Mode
    REQOP1 = 0 ;
    REQOP0 = 0 ;
#endif



    for (i = 0; i<MAX_SAVE_BUF; i++)    CAN_RcvBuf[i] = 0;

}//--------------------------------------------------------------------------------------------------
