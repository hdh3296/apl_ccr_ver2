


#include        "loader_45k80_main.h"
#include		"..\main.h"
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////
//////////////////////////////////////

#define     ONEKEY                  '1'      
#define     TWOKEY                  '2'      
#define     THREEKEY                '3'      
#define     FOURKEY                 '4'
#define     FIVEKEY                 '5'      
#define     SIXKEY                  '6'
#define     SEVENKEY                '7'      
#define     EIGHTKEY                '8'      
#define     NINEKEY                 '9'      
#define     ZEROKEY                 '0'
#define     ENTKEY                  'e'      
#define     MENUKEY                 'm'      
#define     ESCKEY                  'c'      
#define     UPKEY                   'u'      
#define     DOWNKEY                 'd'
#define     LEFTKEY                 'l'      
#define     RIGHTKEY                'r'
#define     ENTKEY                  'e'      


Menu_Status	CurMenuStatus;

uint16_t   	UserMenuSerialNm;
uint16_t   	ThisSelMenuNm;

uint8_t		LoaderBitAreaSram1;

uint8_t		LoaderBuf[17];
uint8_t		New485Ladder[MAX_LADDER_BUF]={0};      


uint32_t	ThisDigitData;

uint16_t   	LoaderKey;
uint16_t   	EnterKey;
uint16_t   	LoaderKeyTime;
uint16_t   	LoaderTime=0;
uint16_t   	BefDspMode=0;
uint16_t   	SaveVerify=0;
uint16_t	MemPointer;
uint8_t		arabianm[10];

uint16_t	CurKeyPoint=0;

	


const uint8_t blinkx[]        	={"                "};  
					




uint16_t  Decimal_Sort(uint32_t val)
{
	arabianm[0] = (uint8_t)((val / (uint32_t)1000000000) + '0');                     
    val =(uint32_t)(val % (uint32_t)1000000000);

	arabianm[1] = (uint8_t)((val / (uint32_t)100000000) + '0');                     
    val =(uint32_t)(val % (uint32_t)100000000);

	arabianm[2] = (uint8_t)((val / (uint32_t)10000000) + '0');                     
    val =(uint32_t)(val % (uint32_t)10000000);

	arabianm[3] = (uint8_t)((val / (uint32_t)1000000) + '0');                     
    val =(uint32_t)(val % (uint32_t)1000000);


	arabianm[4] = (uint8_t)((val / (uint32_t)100000) + '0');                     
    val =(uint32_t)(val % (uint32_t)100000);


	arabianm[5] = (uint8_t)((val / (uint32_t)10000) + '0');                     
    val =(uint32_t)(val % (uint32_t)10000);

	arabianm[6] = (uint8_t)((val / (uint32_t)1000) + '0');                     
    val =(uint32_t)(val % (uint32_t)1000);

	arabianm[7] = (uint8_t)((val / (uint32_t)100) + '0');                     
    val =(uint32_t)(val % (uint32_t)100);

	arabianm[8] = (uint8_t)((val / (uint32_t)10) + '0');                     
	arabianm[9] = (uint8_t)((val % (uint32_t)10) + '0');          

	return(0);           
}




uint16_t  Deciml_Dsp(uint16_t total_dig, uint16_t dp)
{
    uint16_t i,j;
    uint8_t tempbuf[10];
		
	if(dp == 0)			return(0);
	if(dp >= total_dig)	return(0);

	for(i=0; i<total_dig; i++){
		tempbuf[i]=New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + i];                       
	}


	j=(total_dig-dp);
	New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + j]='.';            
           
	for(i=j; i<total_dig; i++){
		New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + i + 1] = tempbuf[i];                       
	}




	
	return(0);
}



void  One_Dig_Dsp(uint32_t val,uint16_t dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = arabianm[9];                      
}


void  Two_Dig_Dsp(uint32_t val,uint16_t dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = arabianm[9];                     
	Deciml_Dsp(CurMenuStatus.M_EditDigitShiftCnt,dp);
}


void  Three_Dig_Dsp(uint32_t val, uint16_t dp)
{
		
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+2] = arabianm[9];                     



	

	Deciml_Dsp(CurMenuStatus.M_EditDigitShiftCnt,dp);
}




void   Four_Dig_Dsp(uint32_t val,uint16_t dp)
{

	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+2] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+3] = arabianm[9];     

		

	Deciml_Dsp(CurMenuStatus.M_EditDigitShiftCnt, dp);
}


void Five_Dig_Dsp(uint32_t val,uint16_t dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+2] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+3] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+4] = arabianm[9];   

	

	Deciml_Dsp(CurMenuStatus.M_EditDigitShiftCnt,dp);
}


void Six_Dig_Dsp(uint32_t val,uint16_t dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = arabianm[4];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+2] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+3] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+4] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+5] = arabianm[9];                     

	Deciml_Dsp(CurMenuStatus.M_EditDigitShiftCnt,dp);
}


void Seven_Dig_Dsp(uint32_t val,uint16_t dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = arabianm[3];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = arabianm[4];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+2] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+3] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+4] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+5] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+6] = arabianm[9];                     

	Deciml_Dsp(CurMenuStatus.M_EditDigitShiftCnt,dp);
}


void Eight_Dig_Dsp(uint32_t val,uint16_t dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = arabianm[2];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = arabianm[3];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+2] = arabianm[4];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+3] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+4] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+5] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+6] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+7] = arabianm[9];                     

	Deciml_Dsp(CurMenuStatus.M_EditDigitShiftCnt,dp);

}



void Nine_Dig_Dsp(uint32_t val,uint16_t dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = arabianm[1];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = arabianm[2];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+2] = arabianm[3];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+3] = arabianm[4];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+4] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+5] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+6] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+7] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+8] = arabianm[9];                     
	Deciml_Dsp(CurMenuStatus.M_EditDigitShiftCnt,dp);
}


void Ten_Dig_Dsp(uint32_t val,uint16_t dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = arabianm[0];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = arabianm[1];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+2] = arabianm[2];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+3] = arabianm[3];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+4] = arabianm[4];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+5] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+6] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+7] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+8] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+9] = arabianm[9];                     
	Deciml_Dsp(CurMenuStatus.M_EditDigitShiftCnt,dp);
}


void  Nine_Dig_Dsp_ext(uint32_t val_h, uint32_t val_m, uint32_t val_s, uint16_t dp)
{

	arabianm[0] = (uint8_t)((val_h / (uint32_t)10) + '0');                     
	arabianm[1] = (uint8_t)((val_h % (uint32_t)10) + '0'); 
	
	arabianm[3] = (uint8_t)((val_m / (uint32_t)10) + '0');                     
	arabianm[4] = (uint8_t)((val_m % (uint32_t)10) + '0'); 

	arabianm[6] = (uint8_t)((val_s / (uint32_t)10) + '0');                     
	arabianm[7] = (uint8_t)((val_s % (uint32_t)10) + '0'); 	

	
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = arabianm[0];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = arabianm[1];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+2] = ':';                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+3] = arabianm[3];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+4] = arabianm[4];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+5] = ':';                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+6] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+7] = arabianm[7]; 

	if (b_gps_in_successed)
	{
		
		New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+8] 	= '(';	
		New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+9] 	= 'O';
		New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+10] = 'R';
		New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+11] = 'G';
		New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+12] = ')';  

	}
	else{
		
		New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+8] 	= '(';	
		New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+9] 	= '.';
		New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+10]	= '.';
		New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+11] = '.';
		New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+12] = ')';  

		
	}
	
	
	
	Deciml_Dsp(CurMenuStatus.M_EditDigitShiftCnt,dp);

}




uint16_t  BitOnOffMessage(uint8_t byte_data)
{
	uint8_t	pt;

	if((CurMenuStatus.M_EditStatus & BIT_ONOFF_EDIT)){
		pt=(uint8_t)(byte_data);
	
	    if(pt & 0x01)  New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = '1';
	    else           New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+0] = '0';
	    if(pt & 0x02)  New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = '2';
	    else           New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+1] = '0';
	    if(pt & 0x04)  New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+2] = '3';
	    else           New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+2] = '0';
	    if(pt & 0x08)  New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+3] = '4';
	    else           New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+3] = '0';
	    if(pt & 0x10)  New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+4] = '5';
	    else           New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+4] = '0';
	    if(pt & 0x20)  New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+5] = '6';
	    else           New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+5] = '0';
	    if(pt & 0x40)  New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+6] = '7';
	    else           New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+6] = '0';
	    if(pt & 0x80)  New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+7] = '8';
	    else           New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+7] = '0';
	}

	return(0);
}



uint16_t  DigitStringMessage(void)
{
	uint16_t	i,pt;

	if((CurMenuStatus.M_EditStatus & DIGIT_STRING_EDIT)){
		pt=(uint16_t)(ThisDigitData * 17);
		for(i=0;(CurMenuStatus.M_EditStart+i)<16;i++)	New485Ladder[SECONDLINE_BASE+CurMenuStatus.M_EditStart+i] = *(CurMenuStatus.M_EditMsgAddr + pt + i);                     
	}

	return(0);
}



void display_unit(void)
{
	/* user그룹   4,5, 7,8,9, 10,11,12 메뉴의 값에 단위 표시해라 

		단위 표시 자리수 시작값은 메뉴 값의 맨 앞자리가 인덱스 0 이다. 
	*/

	switch	(ThisSelMenuNm){
		case	4:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 4] = 'B'; 
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 5] = 'P';
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 6] = 'M';		
			break;

		case	5:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 4] = '%'; 
			break;
		
		case	6:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 4] = 'B'; 
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 5] = 'P';
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 6] = 'M';		
			break;

		case	7:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 4] = '%'; 
			break;
		
		case	8:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 4] = 'B'; 
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 5] = 'P';
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 6] = 'M';		
			break;

		case	9:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 4] = '%'; 
			break;		
	
		case	11:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 5] = 'm'; 
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 6] = 'A'; 
			break;

		case	12:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 5] = 'm'; 
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 6] = 'A'; 
			break;
			
		case	13:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 5] = 'm'; 
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 6] = 'A'; 
			break;
			
		case	14:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 6] = 'm'; 
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 7] = 'A'; 
			break;

		case	15:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 6] = 'm'; 
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 7] = 'A'; 
			break;
			
		case	16:
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 6] = 'm'; 
			New485Ladder[SECONDLINE_BASE + CurMenuStatus.M_EditStart + 7] = 'A'; 
			break;			

	}

}

void  Integer_Digit(void)
{

	if(ThisDigitData > CurMenuStatus.M_EditDigitMaxValue){	
		ThisDigitData=CurMenuStatus.M_EditDigitMinValue;
	}
	else if(ThisDigitData < CurMenuStatus.M_EditDigitMinValue){
		ThisDigitData=CurMenuStatus.M_EditDigitMaxValue;
	}

	if(CurMenuStatus.M_EditDigitMaxValue < 10){
		CurMenuStatus.M_EditDigitShiftCnt=1;
		One_Dig_Dsp(ThisDigitData,CurMenuStatus.M_EditDivide);
	}
	else if(CurMenuStatus.M_EditDigitMaxValue < 100){
		CurMenuStatus.M_EditDigitShiftCnt=2;
		Two_Dig_Dsp(ThisDigitData,CurMenuStatus.M_EditDivide);
	}
	else if(CurMenuStatus.M_EditDigitMaxValue < 1000){
		CurMenuStatus.M_EditDigitShiftCnt=3;
		Three_Dig_Dsp(ThisDigitData,CurMenuStatus.M_EditDivide);
	}
	else if(CurMenuStatus.M_EditDigitMaxValue < 10000){
		CurMenuStatus.M_EditDigitShiftCnt=4;
		Four_Dig_Dsp(ThisDigitData,CurMenuStatus.M_EditDivide);
	}
	else if(CurMenuStatus.M_EditDigitMaxValue < 100000){
		CurMenuStatus.M_EditDigitShiftCnt=5;
		Five_Dig_Dsp(ThisDigitData,CurMenuStatus.M_EditDivide);
	}
	else if(CurMenuStatus.M_EditDigitMaxValue < 100000){
		CurMenuStatus.M_EditDigitShiftCnt=6;
		Six_Dig_Dsp(ThisDigitData,CurMenuStatus.M_EditDivide);
	}
	else if(CurMenuStatus.M_EditDigitMaxValue < 1000000){
		CurMenuStatus.M_EditDigitShiftCnt=7;
		Seven_Dig_Dsp(ThisDigitData,CurMenuStatus.M_EditDivide);
	}
	else if(CurMenuStatus.M_EditDigitMaxValue < 10000000){
		CurMenuStatus.M_EditDigitShiftCnt=8;
		Eight_Dig_Dsp(ThisDigitData,CurMenuStatus.M_EditDivide);
	}
	else if(CurMenuStatus.M_EditDigitMaxValue < 100000000){
		CurMenuStatus.M_EditDigitShiftCnt=9;
		Nine_Dig_Dsp(ThisDigitData,CurMenuStatus.M_EditDivide);
	}
	else{
		CurMenuStatus.M_EditDigitShiftCnt=10;
		Ten_Dig_Dsp(ThisDigitData,CurMenuStatus.M_EditDivide);
	}

	display_unit();
	

    DigitStringMessage();
	BitOnOffMessage( (uint8_t)ThisDigitData);

}



uint16_t  ReadLongData(uint16_t pt)
{
	ThisDigitData=(uint32_t)(lF_LongData(pt));
	return(0);
}

uint16_t  ReadIntegerData(uint16_t pt)
{
	ThisDigitData=(uint32_t)(iF_IntData(pt));
	return(0);
}

uint16_t  ReadByteData(uint16_t pt)
{
	ThisDigitData=(uint32_t)cF_ByteData(pt);
	return(0);
}




//uint16_t  LoadEditData(uint16_t MainGroup,uint16_t SubGroup)
uint16_t  LoadMenuStatus(uint16_t MainGroup)
{

	CurMenuStatus.M_EditDigitCursor=0;

	CurMenuStatus.M_EditGroupNm=MenuStatus[MainGroup].M_EditGroupNm;
	CurMenuStatus.M_EditSubNm=MenuStatus[MainGroup].M_EditSubNm;
	CurMenuStatus.M_EditCursor=MenuStatus[MainGroup].M_EditCursor;
	CurMenuStatus.M_EditStatus=MenuStatus[MainGroup].M_EditStatus;
	CurMenuStatus.M_EditStart=MenuStatus[MainGroup].M_EditStart;
	CurMenuStatus.M_EditShiftCnt=MenuStatus[MainGroup].M_EditShiftCnt;
	CurMenuStatus.M_EditDivide=MenuStatus[MainGroup].M_EditDivide;				
	CurMenuStatus.M_EditDigitMaxValue=MenuStatus[MainGroup].M_EditDigitMaxValue;
	CurMenuStatus.M_EditDigitMinValue=MenuStatus[MainGroup].M_EditDigitMinValue;
	CurMenuStatus.M_EditDataType=MenuStatus[MainGroup].M_EditDataType;
	CurMenuStatus.M_EditFlashAddr=MenuStatus[MainGroup].M_EditFlashAddr;
	CurMenuStatus.M_EditMsgAddr=MenuStatus[MainGroup].M_EditMsgAddr;
	CurMenuStatus.M_EditGroupMsgAddr=MenuStatus[MainGroup].M_EditGroupMsgAddr;

//	MenuStatus[MainGroup].M_EditCurDigitData=0;

	return(0);

}

uint16_t  LoadEditData(uint16_t MainGroup)
{
	if( (CurMenuStatus.M_EditDataType & BYTE_TYPE)){
		ReadByteData(CurMenuStatus.M_EditFlashAddr);
	}
	else if( (CurMenuStatus.M_EditDataType & INT_TYPE)){
		ReadIntegerData(CurMenuStatus.M_EditFlashAddr);
	}
	else if((CurMenuStatus.M_EditDataType & LONG_TYPE)){
		ReadLongData(CurMenuStatus.M_EditFlashAddr);
	}

    Integer_Digit();
	return(0);
}





uint16_t  SaveData(void)
{
    uint16_t i,j,BlockPt;

	MenuStatus[ThisSelMenuNm].M_EditCurDigitData=ThisDigitData;


    if((CurMenuStatus.M_EditStatus & NO_SAVE))	return(0);

	BlockPt=(CurMenuStatus.M_EditFlashAddr/FLASH_ONE_BLOCK_SIZE);  //?

	FlashBlockRd(BlockPt);
	if( (CurMenuStatus.M_EditDataType & LONG_TYPE)){		
		lSR_LongData(CurMenuStatus.M_EditFlashAddr)=ThisDigitData;
	}
	else if( (CurMenuStatus.M_EditDataType & INT_TYPE)){
		iSR_IntData(CurMenuStatus.M_EditFlashAddr)=ThisDigitData;
	}
	else if( (CurMenuStatus.M_EditDataType & BYTE_TYPE)){
		cSR_ByteData(CurMenuStatus.M_EditFlashAddr)=(uint8_t)(ThisDigitData);		
	}
	else{
		return(0);
	}

	FlashBlockWr(BlockPt);

	return(0);
}





uint16_t  LaderDsp(void)
{
    uint16_t i,j;

	LoadMenuStatus(ThisSelMenuNm);


    for(i=0;i<MAX_LADDER_BUF-2;i++)   New485Ladder[i]=' ';
    New485Ladder[MAX_LADDER_BUF-1]=0x0;   


	for(i=0;i<16;i++)	New485Ladder[i+2]= *(CurMenuStatus.M_EditGroupMsgAddr + i);                     

    New485Ladder[0]=LoaderKey;    
    New485Ladder[1]=' ';


	New485Ladder[SECONDLINE_BASE+0] =(CurMenuStatus.M_EditSubNm / 10) + '0';              
	New485Ladder[SECONDLINE_BASE+1] =(CurMenuStatus.M_EditSubNm % 10) + '0';;          

	return(0);
}






void  CursorOff(void)
{
    New485Ladder[SECONDLINE_CURSOR]=' ';  
}

void  CursorOn(void)
{
    uint16_t i;

    i=CurMenuStatus.M_EditCursor + CurMenuStatus.M_EditStart;                    
    if(i>0x09)  i=i + '7';
    else        i=i + '0';
    New485Ladder[SECONDLINE_CURSOR]=i;  
}


uint16_t ShiftLeftCur(void)
{
    uint16_t  i;

    if(CurMenuStatus.M_EditShiftCnt==0)     CurMenuStatus.M_EditCursor=0;
    else if(CurMenuStatus.M_EditCursor>0)   CurMenuStatus.M_EditCursor--;
    else                	CurMenuStatus.M_EditCursor=CurMenuStatus.M_EditShiftCnt-1;


    if(CurMenuStatus.M_EditDigitCursor>0)  	CurMenuStatus.M_EditDigitCursor--;
    else                	CurMenuStatus.M_EditDigitCursor=CurMenuStatus.M_EditDigitShiftCnt-1;


    i=SECONDLINE_BASE + CurMenuStatus.M_EditStart + CurMenuStatus.M_EditCursor;


    if((CurMenuStatus.M_EditStatus & DIGIT_EDIT)){
        if((New485Ladder[i] == '.') || (New485Ladder[i] == ('.' + 0x80))){
            if(CurMenuStatus.M_EditShiftCnt==0)     CurMenuStatus.M_EditCursor=0;
            else if(CurMenuStatus.M_EditCursor>0)   CurMenuStatus.M_EditCursor--;
            else                	CurMenuStatus.M_EditCursor=CurMenuStatus.M_EditShiftCnt-1;
        }
    }           
    else if( (CurMenuStatus.M_EditStatus & CLOCK_EDIT)){
        if((New485Ladder[i] == '-') || (New485Ladder[i] == ('-' + 0x80))){
            if(CurMenuStatus.M_EditShiftCnt==0) 	CurMenuStatus.M_EditCursor=0;
            else if(CurMenuStatus.M_EditCursor>0)   CurMenuStatus.M_EditCursor--;
            else                	CurMenuStatus.M_EditCursor=CurMenuStatus.M_EditShiftCnt-1;
        }
    }           
	return(0);
}



uint16_t  ShiftRightCur(void)
{
    uint16_t i;

    if(CurMenuStatus.M_EditShiftCnt==0) CurMenuStatus.M_EditCursor=0;
    else            	CurMenuStatus.M_EditCursor=(CurMenuStatus.M_EditCursor+1) % CurMenuStatus.M_EditShiftCnt; 

	CurMenuStatus.M_EditDigitCursor=(CurMenuStatus.M_EditDigitCursor+1)	% CurMenuStatus.M_EditDigitShiftCnt;


    i=SECONDLINE_BASE + CurMenuStatus.M_EditStart + CurMenuStatus.M_EditCursor;

	if((CurMenuStatus.M_EditStatus & DIGIT_EDIT)){
        if((New485Ladder[i] == '.') || (New485Ladder[i] == ('.' + 0x80))){
            if(CurMenuStatus.M_EditShiftCnt==0) CurMenuStatus.M_EditCursor=0;
            else            	CurMenuStatus.M_EditCursor=(CurMenuStatus.M_EditCursor+1) % CurMenuStatus.M_EditShiftCnt; 
        }
    }           
    else if((CurMenuStatus.M_EditStatus & CLOCK_EDIT)){
        if((New485Ladder[i] == '-') || (New485Ladder[i] == ('-' + 0x80))){
            if(CurMenuStatus.M_EditShiftCnt==0) CurMenuStatus.M_EditCursor=0;
            else            	CurMenuStatus.M_EditCursor=(CurMenuStatus.M_EditCursor+1) % CurMenuStatus.M_EditShiftCnt; 
        }
    }
	return(0);           
}



uint16_t  CusorDataUp(void)
{
    uint16_t i,dp;
    i=SECONDLINE_BASE + CurMenuStatus.M_EditStart + CurMenuStatus.M_EditCursor;

	if( (CurMenuStatus.M_EditStatus & DIGIT_EDIT)){ 
		switch(CurMenuStatus.M_EditDigitShiftCnt-CurMenuStatus.M_EditDigitCursor){
		    case    1:
		        ThisDigitData++;
		        break;
		    case    2:
		        ThisDigitData=ThisDigitData+10;
		        break;                    
		    case    3:
		        ThisDigitData=ThisDigitData+100;
		        break;                    
		    case    4:
		        ThisDigitData=ThisDigitData+1000;
		        break;                    
		    case    5:
		        ThisDigitData=ThisDigitData+10000;
		        break;                    
		    case    6:
		        ThisDigitData=ThisDigitData+100000;
		        break;
		    case    7:
		        ThisDigitData=ThisDigitData+1000000;
		        break;                    
		    case    8:
		        ThisDigitData=ThisDigitData+10000000;
		        break;                    
		    case    9:
		        ThisDigitData=ThisDigitData+100000000;
		        break;                    
		    case    10:
		        ThisDigitData=ThisDigitData+1000000000;
		        break;                    
		}
		Integer_Digit();    
	}
	else if( (CurMenuStatus.M_EditStatus & DIGIT_STRING_EDIT)){ 
	
		i=CurMenuStatus.M_EditDigitMaxValue;
		
		if( i > 0 ){
			ThisDigitData= ( (ThisDigitData+1) % i);
		}
		else	ThisDigitData=0;	

		Integer_Digit();    
	}
	else if( (CurMenuStatus.M_EditStatus & DIGIT_ALPHAR_EDIT)){ 
		New485Ladder[i]++;
		if(New485Ladder[i]>'Z')                      					New485Ladder[i]='0';
		else if((New485Ladder[i]>'9') && (New485Ladder[i]<'A'))  		New485Ladder[i]='A';
		else if(New485Ladder[i] < '0')  								New485Ladder[i]='0';
	}
	else if( (CurMenuStatus.M_EditStatus & CLOCK_EDIT)){ 
	    New485Ladder[i]++;
	    if((New485Ladder[i]<'0'))       New485Ladder[i]='9'; 
	    else if(New485Ladder[i]>'9')    New485Ladder[i]='0'; 
	}
	else if( (CurMenuStatus.M_EditStatus & TABLE_EDIT)){ 

	}
	else if( (CurMenuStatus.M_EditStatus & TOGGLE_EDIT)){ 

	}
	return(0);         
}


uint16_t  CusorDataDn(void)
{
    uint16_t i,dp;

    i=SECONDLINE_BASE + CurMenuStatus.M_EditStart + CurMenuStatus.M_EditCursor;

	if( (CurMenuStatus.M_EditStatus & DIGIT_EDIT)){ 
		switch(CurMenuStatus.M_EditDigitShiftCnt-CurMenuStatus.M_EditDigitCursor){
		    case    1:
		        ThisDigitData--;
		        break;
		    case    2:
		        ThisDigitData=ThisDigitData-10;
		        break;                    
		    case    3:
		        ThisDigitData=ThisDigitData-100;
		        break;                    
		    case    4:
		        ThisDigitData=ThisDigitData-1000;
		        break;                    
		    case    5:
		        ThisDigitData=ThisDigitData-10000;
		        break;                    
		    case    6:
		        ThisDigitData=ThisDigitData-100000;
		        break;
		    case    7:
		        ThisDigitData=ThisDigitData-1000000;
		        break;                    
		    case    8:
		        ThisDigitData=ThisDigitData-10000000;
		        break;                    
		    case    9:
		        ThisDigitData=ThisDigitData-100000000;
		        break;                    
		    case    10:
		        ThisDigitData=ThisDigitData-1000000000;
		        break;                    
		}
		Integer_Digit();    
	}
	else if( (CurMenuStatus.M_EditStatus & DIGIT_STRING_EDIT)){ 
		if(ThisDigitData > CurMenuStatus.M_EditDigitMinValue)   ThisDigitData--; 
		else                            ThisDigitData=(CurMenuStatus.M_EditDigitMaxValue-1);
		Integer_Digit();    
	}
	else if( (CurMenuStatus.M_EditStatus & DIGIT_ALPHAR_EDIT)){ 
		New485Ladder[i]--;
		if((New485Ladder[i]<'0'))                      				New485Ladder[i]='Z'; 
		else if((New485Ladder[i]>'9') && (New485Ladder[i]<'A'))  	New485Ladder[i]='9'; 
		else if(New485Ladder[i]>'Z')  								New485Ladder[i]='Z'; 
	}
	else if( (CurMenuStatus.M_EditStatus & CLOCK_EDIT)){ 
	}
	else if( (CurMenuStatus.M_EditStatus & TABLE_EDIT)){ 
	}
	else if( (CurMenuStatus.M_EditStatus & TOGGLE_EDIT)){ 
	}

	return(0);         
}



uint16_t CusorDigitSet(void)
{
    uint16_t i;
    i=SECONDLINE_BASE + CurMenuStatus.M_EditStart + CurMenuStatus.M_EditCursor;

	if((CurMenuStatus.M_EditStatus & DIGIT_EDIT)){
    	New485Ladder[i]=LoaderKey;
	}
	else if((CurMenuStatus.M_EditStatus & DIGIT_ALPHAR_EDIT)){
    	New485Ladder[i]=LoaderKey;
	}
	return(0); 
}



uint16_t  EditOnCheck(void)
{
    if((CurMenuStatus.M_EditStatus & NO_EDIT)) 	return(0);
    else 										return(1);

}


uint16_t  GroupOnChk(void)
{
	return(1);

}



uint16_t  MenuOnChk(void)
{
	return(1);

}



void  NewMenuStart(void)
{

    EnterKey=0;
    CurMenuStatus.M_EditCursor=0;
    CurMenuStatus.M_EditShiftCnt=0;
    CurMenuStatus.M_EditStatus=0;
    CurMenuStatus.M_EditStart=0;

}


uint16_t  GroupSelect_Init(void)
{
	if(ThisSelMenuNm==UserMenuSerialNm){
		ThisSelMenuNm=(UserMenuSerialNm-1);
		CurMenuStatus.M_EditGroupNm=0xff;
		CurMenuStatus.M_EditSubNm=0xff;
	}
	return(0);
}


uint16_t  GroupSelect(uint16_t UpDn)
{
	uint16_t	i,m_gr,s_gr;

	GroupSelect_Init();

	i=0;
	do{
		if(UpDn)	ThisSelMenuNm=(ThisSelMenuNm + 1) % UserMenuSerialNm;
		else{
			if(ThisSelMenuNm == 0)	ThisSelMenuNm=(UserMenuSerialNm-1);
			else					ThisSelMenuNm--;
		}
		m_gr = MenuStatus[ThisSelMenuNm].M_EditGroupNm;
		s_gr = MenuStatus[ThisSelMenuNm].M_EditSubNm;
		if((m_gr != CurMenuStatus.M_EditGroupNm) && (s_gr==0)){
			i=GroupOnChk(); 
		} 
	}while(i==0);

	NewMenuStart();
	CursorOff();

	return(0);
}



uint16_t  SubSelect(uint16_t UpDn)
{
	uint16_t	i,m_gr;

	GroupSelect_Init();

	i=0;
	do{
		if(UpDn)	ThisSelMenuNm=(ThisSelMenuNm + 1) % UserMenuSerialNm;
		else{
			if(ThisSelMenuNm == 0)	ThisSelMenuNm=(UserMenuSerialNm-1);
			else					ThisSelMenuNm--;
		}

		m_gr = MenuStatus[ThisSelMenuNm].M_EditGroupNm;
		if(m_gr == CurMenuStatus.M_EditGroupNm){
           	i=1; 
		} 
	}while(i==0);

	NewMenuStart();
	CursorOff();

	return(0);
}






uint16_t  KeyCheck(void)
{
    uint16_t  i,newmenu,ret;

	ret=0;
    newmenu=1;

    LoaderKey = LoaderBuf[C_SAVE_DATA+0];


    switch(LoaderKey){
        case    MENUKEY:
                LoaderKeyTime=0;
				GroupSelect(1);
                break;
        case    ESCKEY:
				if(EnterKey==2){
					EnterKey=1;
				}
				else if(EnterKey==1){
					EnterKey=0;			
					ThisSelMenuNm=UserMenuSerialNm;
				}
				else{
					ThisSelMenuNm=UserMenuSerialNm;

				}

				CurKeyPoint=0;

	            LoaderKeyTime=0;
	            NewMenuStart();
                CursorOff(); 
                break;
        case    UPKEY:
				CurKeyPoint=((CurKeyPoint+1) % 100);
                LoaderKeyTime=0;
                if((EnterKey==1) && (ThisSelMenuNm != UserMenuSerialNm)){
					SubSelect(1);
                    NewMenuStart();
                    CursorOff(); 
                }
                else if(EnterKey==2){
                    CusorDataUp();
					newmenu=0;
                }
                break;
        case    DOWNKEY:
				if(CurKeyPoint > 0)	CurKeyPoint--;
				else				CurKeyPoint=99;

                LoaderKeyTime=0;
                if((EnterKey==1) && (ThisSelMenuNm != UserMenuSerialNm)){
					SubSelect(0);
                    NewMenuStart();
                    CursorOff(); 
                }
                else if(EnterKey==2){
                    CusorDataDn();
					newmenu=0;
                }
                break;
        case    LEFTKEY:
                LoaderKeyTime=0;
                if(EnterKey==1){
					GroupSelect(1);
                }
                else if(EnterKey==2){
                    ShiftLeftCur();
                    CursorOn();
					newmenu=0;
                }
                break;
        case    RIGHTKEY:
                LoaderKeyTime=0;
                if(EnterKey==1){
					GroupSelect(0);
                }
                else if(EnterKey==2){
                    ShiftRightCur();
                    CursorOn();
					newmenu=0;
                }
                break;
        case    ENTKEY:
				newmenu=0;
                LoaderKeyTime=0;
				if((ThisSelMenuNm != UserMenuSerialNm))	EnterKey++;
                if(EnterKey==2){
                    if(!EditOnCheck()){
                        EnterKey=1;
                        CursorOff(); 
                    }
                    else    CursorOn();
                }
                else if(EnterKey==3){
					SaveVerify = 0x55;
                    ret=SaveData();
					SaveVerify = 0x0;
					if(ret==0)	EnterKey=0;	
                }
                break;
        case    ONEKEY:
        case    TWOKEY:
        case    THREEKEY:
        case    FOURKEY:
        case    FIVEKEY:
        case    SIXKEY:
        case    SEVENKEY:
        case    EIGHTKEY:
        case    NINEKEY:
        case    ZEROKEY:   
                LoaderKeyTime=0;
                CusorDigitSet();
				newmenu=0;
                break;
        default:
                LoaderKey = 0xff;
				newmenu=0;
                break;
    }   
	

	if(newmenu){
        for(i=0;i<16;i++){
            New485Ladder[i+2]=blinkx[i];
        }
        for(i=0;i<16;i++){
            New485Ladder[SECONDLINE_BASE+i]=blinkx[i];
        }
	}

    return(0);
}




uint16_t   NewFlashData(void)
{
    uint16_t i,j;


    if((LoaderKeyTime > 36000) && (LoaderKeyTime < 36002)){        
		LoaderKeyTime=36012;

        ThisSelMenuNm=UserMenuSerialNm;
        EnterKey=0;
    }	 



    KeyCheck();

    if(EnterKey==0){
        EnterKey=1;            

    	if(ThisSelMenuNm != UserMenuSerialNm){
			LaderDsp();
			LoadEditData(ThisSelMenuNm);
		}
    }

   	LoaderBuf[C_BASE_MEMORY]=ThisSelMenuNm;              
////   	LoaderBuf[C_OFFSET_MEMORY]=ThisSelMenuNmSub;          


	if(ThisSelMenuNm==UserMenuSerialNm){	  
		DefaultDisplay();
	}


    LoaderTime=0;

    return(0);
}






void   Ladder485Init(void)
{
    uint16_t i;

//    ThisSelMenuNm=UserMenuSerialNm;

    NewMenuStart();

    for(i=0;i<MAX_LADDER_BUF-2;i++)   New485Ladder[i]=' ';

    New485Ladder[MAX_LADDER_BUF-1]=0x0;

}







