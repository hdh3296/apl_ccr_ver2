


#ifndef	_YOU_CAN_H_
#define	_YOU_CAN_H_

#include	"..\AllCommom.h"



//#include    "..\..\system_com\memory_map.h"

#define     GROUP_NUMBER        0

#define     HOST_BOARD          0x2000
#define     HOST_ADDRESS        0x0000c000

#define     NEW_HOST_ADDRESS    0x0003c000


#define     MAX_ELEV            4
#define     CAN_RCV_DATA        0



#ifdef	FLOOR_64
	#define     HOST_DATA_RECOD     90
	#define     HOST_LAST_DATA      0x80
#else
	#define     HOST_DATA_RECOD     42
	#define     HOST_LAST_DATA      0x08
#endif


#define     MAX_SAVE_BUF        HOST_DATA_RECOD * MAX_ELEV




bit    				MaskSetBit = 0;
unsigned    char    CallMeAdr = 0;

bit bCAN_RxGood;



extern  void    CANTxDLC(char MsgFlag,unsigned char DataCnt);
extern  void    InitCAN(void);
extern  void    CanCheck(void);
extern  unsigned int    CanInterrupt(void);
extern  void    CanTx0(void);
extern  void    CanTx1(void);
extern  void    CanLiveChk(void);
extern  void    CAN_SetFilter_SUB(char filter_no, unsigned int sid, unsigned long eid);
extern  void    CAN_SetMask_SUB(char mask_no, unsigned int sid, unsigned long eid);
extern  void    CAN_ArraryTxSidEid(void);



extern	unsigned    char    NoCanInt;
extern  unsigned    int     CanTime;
extern  unsigned    char    CAN_RcvBuf[MAX_SAVE_BUF];

extern  unsigned    char    bCanTxAct;
extern  unsigned    char    CanKeyValue[8];
extern  unsigned    char    CanCmd;
extern  unsigned    char    Company;
extern  unsigned    char    myAdr;
extern  unsigned    char    CanDataCnt0;
extern  unsigned    char    CanDatacnt1;
extern  unsigned    char    CAN_ReceivedAdr;
extern  unsigned    char    CanLiveTimeAdr[MAX_ELEV];
extern  unsigned    char    EqualDataBuf[8];

extern  unsigned    long    EidBuffer;
extern  unsigned    int     SidBuffer;
extern  unsigned    long    RxEidBuffer;
extern  unsigned    int     RxSidBuffer;

extern  unsigned    char    Tx1ConfirmCnt;
extern  unsigned    char    Tx0ConfirmCnt;


/*
#define     KEY_DOOR    0
#define     KEY_CLEAR   1
#define     KEY_READY   2
#define     KEY_SET     3
#define     KEY_CONFIRM 4

#define     NO_KEY_SET  0xfe
*/

#endif
