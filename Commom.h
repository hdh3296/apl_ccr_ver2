
#include	"AllCommom.h"

#ifndef _COMMOM_H_
#define _COMMOM_H_



#define SW_DAY	0
#define SW_TWL	1
#define SW_NIG	2

#define	A_SET_V_MAX 3300 // mV

typedef enum{DAY = 0, TWL = 1, NIG = 2, NONE = 100} tag_CurDay;
tag_CurDay	CurDAY_TWL_NIG = 100, BefDAY_TWL_NIG = 100;


typedef struct 
{
	unsigned int	Max_Current;
	unsigned int 	Set_Current; // 변환된 볼륨에의한 셋팅 전류 값
	unsigned int	Set_DutyCycle;
		 	
}tag_Apl;
tag_Apl		sAPL[3] = {
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
extern ULONG GetSetCurrent(unsigned int set_mV, unsigned char CurDAY_TWL_NIG);
extern void OutAplLamp_WhenSetMode(tag_CurDay CurDAY_TWL_NIG);
extern void ChangePwmT2CON(tag_CurDay CurDAY_TWL_NIG);
extern ULONG GetInCurrent(ULONG AD_A_IN_mV);

#endif