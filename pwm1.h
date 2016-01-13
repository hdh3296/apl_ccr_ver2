
#include	"AllCommom.h"


#define DUTI_MAX 0x3ff // 1023


unsigned int	DutyCycle;


extern	void InitPwm1(void);
extern  void OutPWM(unsigned int DutyCycle);
extern	void PwmOn(void);
extern	void PwmOff(void);
