

#include        "loader_45k80_main.h"


void    UserBaudRate(void)
{
	uint8_t val;

	val=1;

	switch(val){
		case	0:	
			Com1BaudRate=9600;
			break;
		case	1:	
			Com1BaudRate=19200;
			break;
		case	2:	
			Com1BaudRate=38400;
			break;
		case	3:	
			Com1BaudRate=57600;
			break;
		default:
			Com1BaudRate=57600;
			break;		
	}			
}


uint16_t  InitComLoader(void)
{
	UserBaudRate();
    Init_Com1();

	Com1SerialTime=0;		

	TXIE=0;
	RCIE=1;

	Com1RxTxStatus=STX_CHK;

	Ladder485Init();

	Menu_Status_Set();

    ThisSelMenuNm=UserMenuSerialNm;

	return(0); 
}




void   LdDataTx(void)
{
    uint16_t i;
         
	Com1TxBuffer[0]=ACK;
	Com1TxBuffer[1]= 'A';

	Com1TxBuffer[36] = ' ';                     
	Com1TxBuffer[37] = ' ';                     
	Com1TxBuffer[38] = ' ';                     
	Com1TxBuffer[39] = ' ';                     
	Com1TxBuffer[40] = ' ';                     

	Com1TxBuffer[41]=ETX;
	Com1TxBuffer[42]=0;

    for(i=0;i<36;i++){
        if(New485Ladder[i+0] > 0x80) 
			Com1TxBuffer[2+i]=New485Ladder[i+0] - 0x80;
        else                            	
			Com1TxBuffer[2+i]=New485Ladder[i+0];

        if(New485Ladder[i+0] == 0)    	    
			Com1TxBuffer[2+i]=New485Ladder[i+0]=' ';
    }

	TxImportExportChk();

	Chksum_Sum();

	for(i=0;Com1TxBuffer[i];i++);
	Com1TxCnt=i;

	Com1TxThisPt=0;
	Com1TxStart();
}








uint16_t  Loader_Func(void)
{
	uint16_t i;

    if(Com1RxTxStatus==RX_GOOD){
		RxImportExportChk();

        LoaderBuf[C_SAVE_DATA+0]=Com1RxBuffer[2];
        NewFlashData();
        Com1RxTxStatus=STX_CHK;                        
    }                                 
    if((Com1RxTxStatus != TX_SET) && (Com1SerialTime > 10)){  
        if(LoaderTime>100){
            LoaderBuf[C_SAVE_DATA+0]='N';      
            NewFlashData();
            LoaderTime=0;
        }
        LdDataTx();
        Com1SerialTime=0;
    }       

	return(0);        
}



uint16_t	Loader_Msec1_Interrpt(void)
{
	Com1SerialTime++;
        
	if(LoaderTime  < 20002)  LoaderTime++;

	return(0);	
}



uint16_t	Loader_Com_Interrpt(void)
{

	if((RC1IE)&&(RC1IF))										/*receive interrupt routine*/
	{
        RC1IF=0;
        USART1_RXC();
	}	

	if((TX1IE)&&(TX1IF))										/*transmit interrupt routine*/
	{
        TX1IF=0;
        USART1_TXC();
	}	

	if(OERR1) {
      	TXEN1=0;
      	TXEN1=1;
      	SPEN1=0;
      	SPEN1=1;
		CREN1=0;
    }

	if( !CREN1)	CREN1=1;
	return(0);
}
