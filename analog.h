
#include	"AllCommom.h"




#define	AD_SUMCNT		10
#define	nAD_MAX_CHANEL	7


bit	bAn0_Updated = 0;
bit	bAn1_Updated = 0;
bit	bAn2_Updated = 0;
bit	bAn3_Updated = 0;
bit	bAn4_Updated = 0;
bit	bAn5_Updated = 0;
bit	bAn6_Updated = 0;
bit	bAn7_Updated = 0;

bit	bAdConversion = 0;
bit bAdCalcEnable = 0;
unsigned char AdCalcWaitCnt = 0;
bit bUdtAd = 0;


unsigned	long    SumAD	= 0;
unsigned 	long    InPutAD = 0;
unsigned 	int	    ADBuf 	= 0;
unsigned	int	    SumCnt	= 0;
unsigned	int	    nSumCnt	= 0;
unsigned    int   	AdChSel	= 0;
unsigned    int   	BefAdChSel	= 0;

unsigned    int     AdValue[nAD_MAX_CHANEL]; // 채널별 Ad 값 저장 버퍼 

// 5000이면 5V이다.
#define ADCH_MAX	2
unsigned int arInPut_mV[ADCH_MAX] = {0,}; // 각 채널에서 읽어드린 AD 값 
UCHAR arIs_AdUpd[ADCH_MAX] = {0,};


extern void GetMyAD(void);
extern UCHAR ChangeAdChSel(UCHAR AdSel, UCHAR ch);
extern void Set_AdCh(UCHAR AdSel);

extern	void	InitAD(void);
extern	bit		IsUdtAd(UINT* arInPut_mV, UCHAR* arIs_AdUpd, UCHAR AdChSel);




