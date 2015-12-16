

extern	void    		Init_Com1(void);
extern  void 			USART1_TXC(void);
extern  void 			USART1_RXC(void);
extern	void			Com1TxStart(void);
extern	unsigned char	Chksum_Sum(void);


/*
#define RUNLED 			LATC5	//0
#define RXLED       	LATC4 	//0
#define TXLED       	LATD3	//0

#define TX_EN       	LATD2	//0
*/







#define	COM1_MAX_TX_BUF		100
#define	COM1_MAX_RX_BUF		100

extern	unsigned 	char	Com1TxBuffer[COM1_MAX_TX_BUF];
extern	unsigned 	char	Com1RxBuffer[COM1_MAX_RX_BUF];
extern	unsigned 	char	Com1TxCnt;
extern	unsigned 	char	Com1TxThisPt;

extern	unsigned 	char   	Com1RxTxStatus;

extern	unsigned 	char   	Com1RxCnt;
extern	unsigned 	char 	Com1SerialTime;
extern	unsigned 	int		Com1BaudRate;

