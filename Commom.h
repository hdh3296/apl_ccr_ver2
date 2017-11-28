
#include	"AllCommom.h"

#ifndef _COMMOM_H_
#define _COMMOM_H_



#define SW_DAY	0
#define SW_TWL	1
#define SW_NIG	2

#define	A_SET_V_MAX 3300 // mV

typedef enum{ 	DTN_DAY 	= 0, 
				DTN_TWL 	= 1, 
				DTN_NIG 	= 2, 
				DTN_NONE 	= 3
} Day_Twilight_Night;

Day_Twilight_Night	CurD_T_N = DTN_NONE; // ���� ��, ��, �ڸ� ���� ���� ����  
Day_Twilight_Night	BefD_T_N = DTN_NONE;


typedef struct 
{
	unsigned int	Max_Current;
	unsigned int 	Set_Current; // ��ȯ�� ���������� ���� ���� ��
	unsigned int	Set_DutyCycle;	

	unsigned char   bEveryOnSet;
}tag_Apl;
tag_Apl		sAPL[DTN_NONE] = {
					{0,},	// Set0
					{0,},	// Set1
					{0,},	// Set2
			};



unsigned int AD_A_IN_mV = 0;
unsigned int AD_V_IN_mV = 0;
bit bAD_A_IN_mV_Upd = FALSE;


unsigned int In_Current;  // ��ȯ�� �Է� �ǵ�� ���� ��


bit bSetModeReady= FALSE;
bit bLampOnReady = FALSE;
bit bStTwoEnab = FALSE;
bit bSettingMode = FALSE;

extern void ReadVal(volatile const UCHAR* SavedBuf, UINT* pSetA_Volt, UINT* pDutyCycle);
extern ULONG GetSetCurrent(unsigned int set_mV, unsigned char CurD_T_N);
extern void OutAplLamp_WhenSetMode(Day_Twilight_Night CurD_T_N);
extern unsigned int GetInCurrent(unsigned int AD_A_IN_mV);

#endif