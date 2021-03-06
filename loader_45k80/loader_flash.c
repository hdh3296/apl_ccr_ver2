
#include        "loader_45k80_main.h"
#include		"..\main.h"

#define     ASCTOHEX(x) ((x <= '9') ? (x - '0') : (x - '7')) 


#define BACKUP_COM_BLK      16  //16 byte hex --> ascii 32 byte


uint16_t	LoaderChk=0;
uint16_t	SrcAdrBlk=0;

uint16_t	src,firstdata,seconddata;


void   HextoASCIIByte(void)
{
    
    uint16_t   i;

    i=(src & 0xf0) >> 4;
    if(i<0x0a)   i= i + '0';
    else         i= i + '7';
    firstdata=i;
        
    i=(src & 0x0f);
    if(i<0x0a)   i= i + '0';
    else         i= i + '7';
    seconddata=i;        
}





void	DataLoadSBuf(void)
{

	uint16_t  i,j,k;

	i= ((SrcAdrBlk * BACKUP_COM_BLK)/FLASH_ONE_BLOCK_SIZE);    				//pointer search in block
	FlashBlockRd(i);

	i=((SrcAdrBlk * BACKUP_COM_BLK) % FLASH_ONE_BLOCK_SIZE);			//pointer search in block
    
	for(j=0;j<BACKUP_COM_BLK;j++){										//16 byte load(ascii == 32 byte)
		k=(j * 2);
		src  = (uint8_t)(cSR_ByteData((i + j)));
		HextoASCIIByte();
		
	    Com1TxBuffer[5+k]  = (uint8_t)firstdata;
	    Com1TxBuffer[6+k]  = (uint8_t)seconddata;
	}
	k=(j * 2);

    Com1TxBuffer[5+k]  = ETX;
    Com1TxBuffer[6+k]  = 0;

}



void	IntegerToString(uint16_t i)
{
	i=(i%100);

	Com1TxBuffer[3] = (uint8_t)((i/10)  + '0');                     
	Com1TxBuffer[4] = (uint8_t)((i%10)  + '0');                     
}


void	DataDumpToLoader(void)
{
	if( ((SrcAdrBlk * BACKUP_COM_BLK)  <= (MAX_FLASH_BLOCK_NM * FLASH_ONE_BLOCK_SIZE)) && (LoaderChk < 20) ){
//////////////////////	if((SrcAdrBlk < BACKUP_MAX_BLOCK) && (LoaderChk < 20) ){    // area check and tim out check
	    Com1TxBuffer[0]  = ACK;
	    Com1TxBuffer[1]  = 'W';
	    Com1TxBuffer[2]  = 'F';
		IntegerToString(SrcAdrBlk);
		DataLoadSBuf();
		LoaderChk++;
	}
	else{
		MenuStatus[ThisSelMenuNm].M_EditCurDigitData = 0;
	}	
}




void	ReceiveDataLoad(void)
{
	unsigned int i,j,k;

	j=((SrcAdrBlk * BACKUP_COM_BLK) % FLASH_ONE_BLOCK_SIZE);						//pointer search in block

	for(i=0;i<BACKUP_COM_BLK;i++){
		k=(i*2);

		src  = (uint8_t)(cSR_ByteData((i + j)));

		HextoASCIIByte();

		if( (firstdata  < '0') || (firstdata  > 'F'))	firstdata ='0'; 		
		if( (seconddata < '0') || (seconddata > 'F'))	seconddata='0'; 		
			
		Com1TxBuffer[5+k]=firstdata;
		Com1TxBuffer[6+k]=seconddata;
	}		
	
    Com1TxBuffer[37]  = ETX;
    Com1TxBuffer[38]  = 0;
}




void	DataReqToLoader(void)
{
	if( ((SrcAdrBlk * BACKUP_COM_BLK)  <= (MAX_FLASH_BLOCK_NM * FLASH_ONE_BLOCK_SIZE)) && (LoaderChk < 20) ){
	    Com1TxBuffer[0]  = ACK;
	    Com1TxBuffer[1]  = 'R';
	    Com1TxBuffer[2]  = 'F';
		IntegerToString(SrcAdrBlk);
		ReceiveDataLoad();	
		LoaderChk++;
	}
	else{
		MenuStatus[ThisSelMenuNm].M_EditCurDigitData = 0;
	}		
}




uint16_t	ReceiveCmp(void)
{
	uint16_t i,j,k,good;

	good=1;

	j= ((SrcAdrBlk * BACKUP_COM_BLK) % FLASH_ONE_BLOCK_SIZE);  						//pointer search in block
    
	for(i=0;i<BACKUP_COM_BLK;i++){
		k=(i *2);

		src  = (uint8_t)(cSR_ByteData((i + j)));
		HextoASCIIByte();
		
	    if(Com1RxBuffer[5+k]  != (uint8_t)firstdata)  good=0;
	    if(Com1RxBuffer[6+k]  != (uint8_t)seconddata) good=0;	
	}

	if(Com1RxBuffer[0]  != ACK)	good=0;	
	if(Com1RxBuffer[1]  != 'w')	good=0;
	if(Com1RxBuffer[2]  != 'F')	good=0;

	return(good);
}



void  LoaderDataWriteToMe(void)
{

	uint16_t i,j,k,l,pt;

	i=(uint16_t)Com1RxBuffer[3];
    i=ASCTOHEX(i);

	j=(uint16_t)Com1RxBuffer[4];
    j=ASCTOHEX(j);


	SrcAdrBlk=((i * 10) + j);

	if((SrcAdrBlk * BACKUP_COM_BLK)  > (MAX_FLASH_BLOCK_NM * FLASH_ONE_BLOCK_SIZE))		SrcAdrBlk=0;


	if(SrcAdrBlk > 0){
		if( ((SrcAdrBlk * BACKUP_COM_BLK) %  FLASH_ONE_BLOCK_SIZE) == 0 ){
			i=(SrcAdrBlk * BACKUP_COM_BLK)/FLASH_ONE_BLOCK_SIZE;
			i=i-1;
			FlashBlockWr(i); 

			// 2017.08.08 : zero voltage 값만 wrtie 하지 않는다. 
			iSR_IntData(F_SET_GIJUN_V) = ZeroVoltage;
			FlashBlockWr((F_SET_GIJUN_V / FLASH_ONE_BLOCK_SIZE));
			cSR_ByteData(F_bSave_GIJUN) = bZeroVoltageSaved;
			FlashBlockWr((F_bSave_GIJUN / FLASH_ONE_BLOCK_SIZE));
		
		}
	}

	if((SrcAdrBlk * BACKUP_COM_BLK)  == (MAX_FLASH_BLOCK_NM * FLASH_ONE_BLOCK_SIZE)){
		MenuStatus[ThisSelMenuNm].M_EditCurDigitData = 0;
	}
			
	pt=((SrcAdrBlk* BACKUP_COM_BLK) % FLASH_ONE_BLOCK_SIZE);

	for(i=0;i<BACKUP_COM_BLK;i++){
		l=(i*2);
		k=(uint16_t)Com1RxBuffer[5+l];
	    k=ASCTOHEX(k);
		k=((k << 4) & 0xf0);
	
		j=(uint16_t)Com1RxBuffer[6+l];
	    j=ASCTOHEX(j);
		j=(k | j);

		cSR_ByteData((pt+i))=(uint8_t)(j);
	}

}



uint16_t	RxImportExportChk(void)
{
	if(MenuStatus[ThisSelMenuNm].M_EditFlashAddr != F_FLASH_COPY)	return(0);


	if(MenuStatus[ThisSelMenuNm].M_EditCurDigitData == EXPORT_DATA){
		if(ReceiveCmp()){
			SrcAdrBlk++;
		}
		LoaderBuf[C_SAVE_DATA+0]='N';      
		LoaderChk=0;
		LoaderKeyTime=0;
	}

	else if(MenuStatus[ThisSelMenuNm].M_EditCurDigitData == IMPORT_DATA){
		if((Com1RxBuffer[0]  == ACK) && (Com1RxBuffer[1]  == 'r')	&& (Com1RxBuffer[2]  == 'F')){
			SaveVerify=0x55;
			LoaderDataWriteToMe();
			
			SaveVerify=0;
			Com1RxBuffer[0]  = 'n';
 			Com1RxBuffer[1]  = 'n';
			Com1RxBuffer[2]  = 'n';
		}
	
		LoaderBuf[C_SAVE_DATA+0]='N';      
		LoaderChk=0;
		LoaderKeyTime=0;
	}
	return(0);
}



uint16_t	TxImportExportChk(void)
{
	if(MenuStatus[ThisSelMenuNm].M_EditFlashAddr != F_FLASH_COPY)	return(0);

	if(MenuStatus[ThisSelMenuNm].M_EditCurDigitData == EXPORT_DATA){
		DataDumpToLoader();
	}
	else if(MenuStatus[ThisSelMenuNm].M_EditCurDigitData == IMPORT_DATA){
		DataReqToLoader();
	}
	else{
		SrcAdrBlk=0;
	}
	return(0);
}
