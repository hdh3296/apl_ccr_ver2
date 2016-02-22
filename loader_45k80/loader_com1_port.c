


#include        "loader_45k80_main.h"

/*
#include    "loader_com1_port.h"
#include    "loader_serial.h"
*/

///////////////////////
#define     ASCTOHEX(x) ((x <= '9') ? (x - '0') : (x - '7')) 
#define     L_SHIFT(x)  (x << 4)



uint8_t	Com1TxBuffer[COM1_MAX_TX_BUF];
uint8_t	Com1RxBuffer[COM1_MAX_RX_BUF];
uint8_t	Com1TxCnt=0;
uint8_t	Com1TxThisPt=0;
uint8_t	Com1RxTxStatus=0;
uint8_t	Com1RxCnt=0;
uint8_t	Com1SerialTime=0x0;

uint16_t	Com1BaudRate=19200;
uint16_t  	Crc;  
uint16_t  	Chksum1;  




void    Init_Com1(void)
{
	uint16_t tmpbaudrate;

	SPBRG = DIVIDER;     	

	tmpbaudrate=((uint16_t)(FOSC/(16UL * Com1BaudRate) -1));
	SPBRG = tmpbaudrate;     	

	TXSTA = (SPEED|NINE_BITS|0x20);
	RCSTA = (NINE_BITS|0x90);
	TRISC6=OUTPUT;
	TRISC7=INPUT;

    RCIE=1;	    // USART RX interrupt enable
    TXIE=1;	    // USART TX interrupt enable

    RCIF=0;	    // USART RX interrupt enable
    TXIF=0;	    // USART TX interrupt enable

	UART1MD=0;
	UART2MD=1;
}



void    Crc_Calulate(uint16_t crcdata)
{
	register uint16_t    i;

   Crc=Crc ^ (crcdata & 0x00ff);
   for(i=0;i<=7;i++){
      if( (Crc & 0x0001) == 0x0001)    Crc=(Crc >> 1) ^ 0xA001;
      else Crc=Crc >> 1;
   }
}



uint8_t	Chksum_Sum(void)
{    
    uint8_t	i;
    uint8_t	temp;
    
    Chksum1=0;
    for(i=0;Com1TxBuffer[i];i++){
    Chksum1=Chksum1+Com1TxBuffer[i];
    }
    temp=(Chksum1 & 0xf0) >> 4;
    if(temp < 0x0a) temp=temp+'0';
    else            temp=temp+'7';
    Com1TxBuffer[i]=temp;
    
    temp=(Chksum1 & 0x0f);
    if(temp<0x0a)   temp=temp+'0';        
    else            temp=temp+'7';
    Com1TxBuffer[i+1]=temp;
    Com1TxBuffer[i+2]=0;

	return(0);
}



void    Com1TxStart(void)
{

   	Com1RxTxStatus=TX_SET;   
    TXREG=Com1TxBuffer[Com1TxThisPt];
	Com1TxThisPt++;
	TXIE=1;
}



void USART1_TXC(void)
{					
	if((Com1TxThisPt > Com1TxCnt)){
		Com1RxTxStatus = STX_CHK;
		TXIE=0;
		Com1SerialTime=0;
		Com1TxThisPt=0;
 		Com1TxCnt=0;	
	}
	else{
		
		if(Com1TxThisPt >= COM1_MAX_TX_BUF){
			Com1SerialTime=0;
			Com1TxThisPt=0;
	 		Com1TxCnt=0;	
			TXIE=0;
			Com1RxTxStatus = STX_CHK;
		}
		else{
			TXREG=Com1TxBuffer[Com1TxThisPt];
			Com1TxThisPt++;
			Com1SerialTime=0;
			Com1RxTxStatus = TX_SET;
		}
	}
}





void USART1_RXC(void)
{
   	uint8_t   buf=0;
   	uint8_t   temp=0;


   	buf=RCREG;

    Com1SerialTime=0;


    if(Com1RxTxStatus != TX_SET){   

        if(Com1RxCnt < (COM1_MAX_RX_BUF-1)){
            Com1RxCnt++;
        }
        else{
            Com1RxCnt=0;
        }


        Com1RxBuffer[Com1RxCnt]=buf;


        switch(Com1RxTxStatus){
            case    STX_CHK:
                if((buf==ACK) || (buf==ENQ)){
                    Com1RxTxStatus=ETX_CHK;
                    Com1RxBuffer[0]=buf;
                    Com1RxCnt=0;
                    Chksum1=buf;
                }
                break;
            case    ETX_CHK:
                Chksum1=Chksum1+buf;
                if((buf==ETX) || (buf == EOT)){
                    Com1RxBuffer[Com1RxCnt]=0x0;
                    Com1RxTxStatus=BCC1_CHK;                  
                }
                break;
            case    BCC1_CHK:               

                buf=ASCTOHEX(buf);
                Com1RxBuffer[Com1RxCnt]=0x0;
                temp=(Chksum1 & 0xf0) >> 4; 
           
                if(temp==buf){                 
                    Com1RxTxStatus=BCC2_CHK;                                                                    
                }
                else    Com1RxTxStatus=STX_CHK;                  
                break;
            case    BCC2_CHK :
                buf=ASCTOHEX(buf);
                temp=(Chksum1 & 0x0f);
                Com1RxBuffer[Com1RxCnt]=0x0;
                Com1RxBuffer[COM1_MAX_RX_BUF-1]=0x0;
                if(temp==buf){
/*
                    for(temp=0;((Com1RxBuffer[temp] > 0) && (temp < COM1_MAX_RX_BUF));temp++){                   
                        RcvBuf2[temp]=Com1RxBuffer[temp];
                    }
*/
                    Com1RxTxStatus=RX_GOOD;
                }

                else    Com1RxTxStatus=STX_CHK;                  
                break;              
            case    RX_ERROR:
                Com1RxTxStatus=STX_CHK;
                Com1RxCnt=0;
                break;
            default:
                Com1RxTxStatus=STX_CHK;
                Com1RxCnt=0;
                break;
        }
    }

}





