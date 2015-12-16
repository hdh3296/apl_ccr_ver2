




#include    <pic18.h>

#include        "loader_45k80.h"
#include        "com1_port.h"
#include        "ladder_cmd.h"



void    UserBaudRate(void)
{
	unsigned char val;

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


unsigned int  Loader_Com_Init(void)
{
	UserBaudRate();
    Init_Com1();

	Com1SerialTime=0;		

	TXIE=0;
	RCIE=1;

	Com1RxTxStatus=STX_CHK;

	Ladder485Init();

	return(0); 
}




void   LdDataTx(void)
{
    unsigned int i;
         
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
        if(New485Ladder[i+0] > 0x80)    	Com1TxBuffer[2+i]=New485Ladder[i+0] - 0x80;
        else                            	Com1TxBuffer[2+i]=New485Ladder[i+0];

        if(New485Ladder[i+0] == 0)    	    Com1TxBuffer[2+i]=New485Ladder[i+0]=' ';
    }


/*
	if(bExportData){
		DataDumpToLoader();
	}
	else if(bImportData){
		DataReqToLoader();
	}
*/


////////////   	Chksum_Sum2();   	

	Chksum_Sum();
	Com1TxCnt=44;
	Com1TxThisPt=0;
	Com1TxStart();




/*
    RxBuffer2[0]  = ACK;
    RxBuffer2[1]  = cF_COMPANY;

	RxBuffer2[36] = ' ';                     
	RxBuffer2[37] = ' ';                     
	RxBuffer2[38] = ' ';                     
	RxBuffer2[39] = ' ';                     
	RxBuffer2[40] = ' ';                     

	RxBuffer2[41]=ETX;
	RxBuffer2[42]=0;


    for(i=0;i<36;i++){
        if(New485Ladder[i+0] > 0x80)    	RxBuffer2[2+i]=New485Ladder[i+0] - 0x80;
        else                            	RxBuffer2[2+i]=New485Ladder[i+0];

        if(New485Ladder[i+0] == 0)    	    RxBuffer2[2+i]=New485Ladder[i+0]=' ';
    }

	if(bExportData){
		DataDumpToLoader();
	}
	else if(bImportData){
		DataReqToLoader();
	}

	Serial2();
*/

}


unsigned int  Loader_Func(void)
{
	unsigned int i;

    if(Com1RxTxStatus==RX_GOOD){
	     for(i=0;((Com1RxBuffer[i] > 0) && (i < COM1_MAX_RX_BUF));i++){                   
	         LadderBuf[i]=Com1RxBuffer[i];
	     }


//		if(bExportData || bImportData){
//			NewLoaderChk();
//		}
//        LadderBuf[C_SAVE_DATA+0]=RxBuffer2[2];


//		if(Com1RxBuffer[1] == COMPANY_ID)


        LadderBuf[C_SAVE_DATA+0]=Com1RxBuffer[2];

        NewFlashData();
        Com1RxTxStatus=STX_CHK;                        
    }         
  
                        
    if((Com1RxTxStatus != TX_SET) && (Com1SerialTime > 10)){
        if(LadderTime>100){
            LadderBuf[C_SAVE_DATA+0]='N';      
            NewFlashData();
            LadderTime=0;
        }
        LdDataTx();
        Com1SerialTime=0;
    }       

	return(0);        
}



unsigned int	Loader_Msec1_Interrpt(void)
{
	Com1SerialTime++;
        
	if(LadderTime  < 20002)  LadderTime++;

	return(0);	
}



unsigned int	Loader_Com_Interrpt(void)
{

	if((RCIE)&&(RCIF))										/*receive interrupt routine*/
	{
        RCIF=0;
        USART1_RXC();
	}	

	if((TXIE)&&(TXIF))										/*transmit interrupt routine*/
	{
        TXIF=0;
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
