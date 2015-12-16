

#define  ADR_NO_SET         'N'   
#define  ADR_SET_SEND       'S'   
#define  ADR_SET_REC        's'   
#define  ADR_SET_ACK        'A'   
#define  NORMAL             '0'   
#define  WRITE_DATA         'W'   
#define  READ_DATA          'R'   
#define  BIT_WRITE_DATA     'w'   
#define  BIT_READ_DATA      'r'   
#define  LOGADR_CLR         'C'   
#define  NO_DATA            'Z'   
#define  RET_GOOD           'G'   
#define  RET_NOGOOD         'X'   
#define  LONG_READ_DATA     'L'
#define  FLASH_RD_WR        'F'
#define  NEW_FLASH_RD_WR    'f'

#define  LONG_WR_DATA       'M'



#define RCV_GROUP      		0                       
#define RCV_LOGADR     		1                        
#define RCV_ABSADR     		2                        
#define RCV_CMD        		3                       
#define RCV_CMDTYPE    		4                       
#define RCV_BASE_ADR   		5                        
#define RCV_OFFS_ADR   		6 
#define RCV_DATA_CNT   		7                        
#define	RCV_DATA       		8                        


#define	C_CMD       			0
#define	C_CMDTYPE      		    1
#define	C_BASE_MEMORY     		2
#define	C_OFFSET_MEMORY			3
#define	C_DATA_CNT        		4
#define	C_SAVE_DATA       		5


#define	MAX_LADDER_BUF          40



extern void   			Ladder485Init(void);
extern unsigned int     NewFlashData(void);
//extern void     VirtualMoveCntReDsp(void);



extern	unsigned char	New485Ladder[MAX_LADDER_BUF];      
extern	unsigned char	LadderBuf[17];

extern	unsigned int   LadderTime;




/*
	LadderBuf[C_CMD]=RcvBuf[RCV_CMD];               
   	LadderBuf[C_CMDTYPE]=RcvBuf[RCV_CMDTYPE];             
	LadderBuf[C_BASE_MEMORY]=RcvBuf[RCV_BASE_ADR];              
	LadderBuf[C_OFFSET_MEMORY]=RcvBuf[RCV_OFFS_ADR];          
	LadderBuf[C_DATA_CNT]=RcvBuf[RCV_DATA_CNT];
                        
	LadderBuf[C_SAVE_DATA+0]=RcvBuf[RCV_DATA+0];             
	LadderBuf[C_SAVE_DATA+1]=RcvBuf[RCV_DATA+1];             
	LadderBuf[C_SAVE_DATA+2]=RcvBuf[RCV_DATA+2];             
	LadderBuf[C_SAVE_DATA+3]=RcvBuf[RCV_DATA+3];             
	LadderBuf[C_SAVE_DATA+4]=RcvBuf[RCV_DATA+4];                               
*/