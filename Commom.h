
#include	"AllCommom.h"

#ifndef _COMMOM_H_
#define _COMMOM_H_



#define SW_DAY	0
#define SW_EVE	1
#define SW_NIG	2

#define	A_SET_V_MAX 3300 // mV

typedef enum{DAY = 0, EVE = 1, NIG = 2, NONE = 100} tag_CurDay;
tag_CurDay	CurDayNight = 100, BefCurDayNight = 100;


typedef struct 
{
	unsigned int 	Set_mV; // 셋팅값 
	unsigned int 	SwPushTimer;
	unsigned char 	SwTouchCnt;
	unsigned int 	SwTouchCntTimer;
	unsigned char   SetSwCharterTimer;
	unsigned long 	Set_Current; // 변환된 볼륨에의한 셋팅 전류 값
	unsigned int	Set_DutyCycle; 
	
	unsigned char 	bSetSwPushOK	: 1;
	unsigned char 	bSetSw_UpEdge 	: 1;
	unsigned char 	bSwSlightPush 	: 1;
	unsigned char 	bBlinkEnab		: 1;
	unsigned char   bWriteEnab 		: 1;
	
}tag_Apl;
tag_Apl		stApl[3] = {
					{0,},	// Set0
					{0,},	// Set1
					{0,},	// Set2
			};



unsigned int AD_A_IN_mV = 0;
unsigned int AD_V_IN_mV = 0;
bit bAD_A_IN_mV_Upd = FALSE;


ULONG In_Current;  // 변환된 입력 피드백 전류 값


bit bSetModeReady= FALSE;
bit bLampOnReady = FALSE;
bit bStTwoEnab = FALSE;
bit bSettingMode = FALSE;

extern void ReadVal(volatile const UCHAR* SavedBuf, UINT* pSetA_Volt, UINT* pDutyCycle);
extern ULONG GetSetCurrent(unsigned int set_mV, unsigned char CurDayNight);
extern void OnAplLampSet(tag_CurDay CurDayNight);
extern void ChangPwmCycleRegedit(tag_CurDay CurDayNight);
extern ULONG GetInCurrent(ULONG AD_A_IN_mV);

#endif