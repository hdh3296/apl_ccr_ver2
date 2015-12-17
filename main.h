
#include	"AllCommom.h"


extern volatile bit RB0x                @ ((unsigned)&PORTB*8)+0;
extern volatile bit RB1x                @ ((unsigned)&PORTB*8)+1;

// Pic18f45k80 PIN Name
#define PIN_A_IN				RA0
#define PIN_V_IN 				RA1 	
#define PIN_RA2_NoUse 			RA2	
#define PIN_RA3_NoUse 			RA3		
#define PIN_RA5_NoUse			RA5
	
#define PIN_IN_DAY 				RB0x
#define PIN_IN_NIGHT 			RB1x	
#define PIN_CAN_TX 				RB2	 	
#define PIN_CAN_RX 				RB3	
#define PIN_IN_BLINK 			RB4	
#define PIN_RB5_NoUse 			RB5
#define PIN_PGC 				RB6
#define PIN_PGD 				RB7
	
#define PIN_MODE_0 				RC0	
#define PIN_MODE_1 				RC1	
#define PIN_MODE_2 				RC2	
#define PIN_MODE_3 				RC3	
#define PIN_MODE_4	 			RC4	
#define PIN_RC5_NoUse	 		RC5	
#define PIN_TX_232	 			RC6	// CCP3/CK1/TX1/CANTX	
#define PIN_RX_232	 			RC7	// CANRX/RX1/DT1/CCP4

#define PIN_LED_ON 				RD0 // APL_LAMP ON
#define PIN_LED_RUN0 			RD1	
#define PIN_LED_RUN1 			RD2	
#define PIN_LED_RUN2 			RD3
#define PIN_PWM 				RD4
#define PIN_LED_RUN3 			RD5
#define PIN_LED_RUN4 			RD6	// 통신 TX2 
#define PIN_TX_DP 				RD7	// 통신 RX2

#define PIN_1PPS 				RE0
#define PIN_RE1_NoUse 			RE1	
#define PIN_RE2_NoUse 			RE2
#define PIN_MCLR				RE3


// Tris
#define PIN_A_IN_TRIS 			TRISA0 	// in	
#define PIN_V_IN_TRIS 			TRISA1 	// in
#define PIN_RA2_NoUse_TRIS 		TRISA2 	//
#define PIN_RA3_NoUse_TRIS 		TRISA3 	//
#define PIN_RA5_NoUse_TRIS		TRISA5 	//

#define PIN_IN_DAY_TRIS 		TRISB0 	// in
#define PIN_IN_NIGHT_TRIS 		TRISB1 	// in
#define PIN_CAN_TX_TRIS 		TRISB2 	// out
#define PIN_CAN_RX_TRIS 		TRISB3 	// in
#define PIN_IN_BLINK_TRIS 		TRISB4 	// in
#define PIN_RB5_NoUse_TRIS 		TRISB5 	//
#define PIN_PGC_TRIS 			TRISB6 	//	
#define PIN_PGD_TRIS 			TRISB7 	//
	
#define PIN_MODE_0_TRIS 		TRISC0 	// in	
#define PIN_MODE_1_TRIS 		TRISC1 	// in	
#define PIN_MODE_2_TRIS 		TRISC2 	// in	
#define PIN_MODE_3_TRIS 		TRISC3	// in
#define PIN_MODE_4_TRIS	 		TRISC4	// in 
#define PIN_RC5_NoUse_TRIS		TRISC5	//
#define PIN_TX_232_TRIS	 		TRISC6	// out
#define PIN_RX_232_TRIS	 		TRISC7	// in

#define PIN_LED_ON_TRIS 		TRISD0	// out
#define PIN_LED_RUN0_TRIS 		TRISD1	// out
#define PIN_LED_RUN1_TRIS 		TRISD2	// out
#define PIN_LED_RUN2_TRIS 		TRISD3	// out
#define PIN_PWM_TRIS 			TRISD4	// out
#define PIN_LED_RUN3_TRIS 		TRISD5	// out
#define PIN_LED_RUN4_TRIS 		TRISD6	// out
#define PIN_TX_DP_TRIS 			TRISD7  // in	

#define PIN_1PPS_TRIS 			TRISE0	// in
#define PIN_RE1_NoUse_TRIS 		TRISE1	//
#define PIN_RE2_NoUse_TRIS 		TRISE2	//



// AD 입력 
#define _A_IN			PIN_A_IN // AN0		
#define _V_IN			PIN_V_IN // AN1
// APL LAMP 출력 제어 
#define _LAMP_ON		PIN_LED_ON // APL Lamp On/Off  			
#define _PWM			PIN_PWM 
// CDS
#define _IN_DAY			PIN_IN_DAY 				
#define _IN_NIGHT		PIN_IN_NIGHT
// 깜빡임 외부에서 제어 
#define _IN_BLINK		PIN_IN_BLINK 				
// 딥스위치 	
#define _DIP_SW0		PIN_MODE_0 					
#define _DIP_SW1		PIN_MODE_1 					
#define _DIP_SW2		PIN_MODE_2 					
#define _DIP_SW3		PIN_MODE_3 					
#define _DIP_SW4		PIN_MODE_4	 				
// 232통신 			
#define _TX_232			PIN_TX_232	 				// CCP3/CK1/TX1/CANTX	
#define _RX_232			PIN_RX_232	 				// CANRX/RX1/DT1/CCP4
// CAN 통신 
#define _CAN_TX			PIN_CAN_TX 					 	
#define _CAN_RX			PIN_CAN_RX 
// LED
#define _LED_CPU_RUN	PIN_LED_RUN0 // CPU RUN				
#define _LED_NIGHT		PIN_LED_RUN1 // Night 상태 LED 				
#define _LED_GPS_GOOD	PIN_LED_RUN2 	
#define _LED_LAMP_ON	PIN_LED_RUN3 // APL Lamp On 듀티 LED			
#define _LED_TEST 		PIN_LED_RUN4 // GPS RX2 수신시, 'A' 데이타 수신 상태 LED 				
// GPS
#define _RX_GPS			PIN_TX_DP 					// 통신 RX2
#define _PPS_GPS		PIN_1PPS 				
// 기타 			
#define _MCLR			PIN_MCLR	
#define _PGC			PIN_PGC 				
#define _PGD			PIN_PGD 
// 미사용 
#define _NoUse1			PIN_RA2_NoUse 				
#define _NoUse2			PIN_RA3_NoUse 					
#define _NoUse3			PIN_RA5_NoUse
#define _NoUse4			PIN_RC5_NoUse	
#define _NoUse5			PIN_RE1_NoUse 				
#define _NoUse6			PIN_RE2_NoUse 
#define _NoUse7			PIN_RB5_NoUse 


// 미사용(이전) Q??추후 삭제 
#define _SW_SET_HI		_NoUse1
#define _SW_SET_LO		_NoUse2
#define _VR1_SET_HI		_NoUse3
#define _VR2_SET_LO		_NoUse4



	


#define     MSEC_H    0xfc
#define     MSEC_L    0x18



#define SETSW_PUSH		0 // 스위치 눌렀을 때가 0 값이다.

#define	chV_IN	1
#define	chA_IN	2
#define	chVR1	3
#define	chVR2	4


#define LED_NIG_ON	0
#define LED_NIG_OFF	1


#ifndef	ON_lamp
#define	ON_lamp	1
#endif
#ifndef	OFF_lamp
#define	OFF_lamp	0
#endif

#ifndef	ON_runled1
#define	ON_runled1	0
#endif
#ifndef	OFF_runled1
#define	OFF_runled1	1
#endif

#define JUNG_GIJUN 1500


#define		LED_ONOFF_CNT		20

//#define		NIGHT_VOLT			200
//#define		NIGHT_DAY_VOLT		135


unsigned    char  	MainTimer = 0;
unsigned    char	msec100 = 0;


unsigned    char	NightSetTime = 0;
unsigned    char	NightDaySetTime = 0;
unsigned    char	SettingReadyTime = 0;

unsigned    char	DayNightTimer = 0;

unsigned    char	Ghour = 0, Gmin = 0, Gsec = 0; // Gps 로 부터 수신된 RxData 값 
unsigned    int		Gms1 = 0; // 마이컴의 인터럽트에 의한 발생된 msec 값 저장 변수 
unsigned    int		Gms60000 = 0; // 현재 시간값을 ms단위로 환산한 값 저장 변수 


unsigned    char	WakeupTime = 0;
unsigned	char	modesw = 0;
unsigned	int		rx_hour = 0, rx_min = 0, rx_sec = 0;
unsigned	int		OnTime[LED_ONOFF_CNT];
unsigned	int		LedCycle_Msec;
unsigned	int		LedOnDuty_Msec;
unsigned	long	ZeroTimer = 0;
unsigned	long	l_hour, l_min, l_sec;

unsigned    char	NightVolt = 0;
unsigned    char	NightDayVolt = 0;


bit   	FeedbackOn = 0;

bit   	bActiveOn = 0;
bit   	bPwmOn = 0;
bit   	bSearchGps = 0;
bit		bPPS_On = 0;
bit		bPPS_Edge = 0;

bit		bNight = 0;
bit		bNightDay = 0;

bit		bBlink_DutyOn = 0;


unsigned int BeginTimer = 0;
unsigned char InDayTimer = 0;



// 5000이면 5V이다.
unsigned int SetAVoltage=0; 
unsigned int SetA1_Volt=0; // SER A1 Voltage, AN0 , 낮 
unsigned int SetA3_Volt=0; // SER A3 Voltage, AN2 , 밤 
unsigned int A_IN_Volt=0; // PIN_RA2_NoUse Voltage, AN3
unsigned int V_IN_Volt=0; // PIN_V_IN Voltage, AN4

bit bAgoBlkLedOff;

unsigned int AnalogValidTime = 0;


#define WRSIZE	12
volatile const unsigned char  arSavedBuf[WRSIZE] = {0, };



unsigned int SetStTimer = 0;
unsigned int StDelayTimer = 0;
unsigned int StDelayTime = 0;

// 임시 : LCD 로더에서 온값 저장할 변수들
//Flashing Set
unsigned char L_Duty_Cnt = 0;
unsigned char L_Duty_Rate = 0;


unsigned char L_SetMode_Sel = 0;
unsigned char Bef_L_SetMode_Sel = 0;

unsigned int  L_DaySetValue = 0;
unsigned int  L_EveSetValue = 0;
unsigned int  L_NigSetValue = 0;





// Current Set
unsigned int L_MAX_Current_Day = 0;
unsigned int L_MAX_Current_Evening = 0;
unsigned int L_MAX_Current_Night = 0;

// blink Duty 시간 변수들 
UCHAR	DUTY_CNT = 0;  // 1분당  LED ON 횟수
UCHAR   DUTY_RATE = 0;	// LED ON 듀티 비(%)
ULONG   LED_CYCLE_MSEC = 0;
ULONG	LED_ON_DUTY_MSEC = 0; // Lamp Blink에서의 On 주기 시간(ms) 	



extern  void  Initial(void);
extern  void  InitTimer0(void);
extern void    InitPort(void);
extern void  Serial2Check(void);
extern void GpsPPS1Chk(void);
extern void LedBlinkModeInit(void);
extern unsigned int ReSettingDayNigntChk(void);
extern void ApaLampOnOff(void);
extern bit IsBlink_On(void);
extern void GpsRx2DataProc(void);
extern void ChkSetupSw(void);
extern unsigned char GetDayEveningNight(void);
extern void WriteVal(unsigned int DutyCycle, unsigned int SetAVoltage, volatile const unsigned char* DestBuf);
extern void GetAdValue(void);
extern unsigned int GetDutyByCompareCurrent(unsigned int duty, unsigned int setVolt, 
												  unsigned int inVolt, unsigned char CurDayNight);
extern void SetApaLamp(void);
extern void PwOnAplLamp(void);


extern bit IsInLED_ON(unsigned char bLedState, unsigned char* Timer);

extern unsigned int GetDutyByCmp(unsigned int duty, unsigned int set_mV,
                                 unsigned char DayNig, unsigned int Offset);
extern void ChkSwTwoTouch(void);
extern void Chk232TxErr(void);
extern void WriteProc(void);


