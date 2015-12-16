



#define	COMPANY_ID		'A'
#define	TX_DATA_CNT		40     
//#define	TX_DATA_CNT		88     



#define	CPU45K80		1

#define	U_COMPILER		1






#define	MAX_ELEV            4
#define	HOST_DATA_RECOD     42
#define	MAX_SAVE_BUF_CAN    HOST_DATA_RECOD * MAX_ELEV




extern	unsigned int	Loader_Com_Init(void);
extern	unsigned int	Loader_Func(void);
extern	unsigned int	Loader_Msec1_Interrpt(void);
extern	unsigned int	Loader_Com_Interrpt(void);

