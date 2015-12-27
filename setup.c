

#include    <pic18.h>

#include	"setup.h"

#define	MAX_FLASH_BLOCK_NM	3

volatile const unsigned char information[]={
												dFW_VERSION,dDuty_Cnt,dDuty_Rate,dSETMODE_SEL,dSET_VAL_DAY_L,dSET_VAL_DAY_H,dSET_VAL_EVE_L,dSET_VAL_EVE_H,dSET_VAL_NIG_L,dSET_VAL_NIG_H,dMaxSetA_Day_L,dMaxSetA_Day_H,dMaxSetA_Eve_L,dMaxSetA_Eve_H,dMaxSetA_Nig_L,dMaxSetA_Nig_H,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
												0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
											   };
												
unsigned char new_value[64];
												
far unsigned char * source_ptr = (far unsigned char *)new_value;                    /*pointers to data*/
far unsigned char * dest_ptr = (far unsigned char *)information;
unsigned int size = 64;						




unsigned int FlashBlockRd(unsigned int BlkNm)
{
    unsigned int i,j;
	if(BlkNm <= MAX_FLASH_BLOCK_NM){	
		j= (BlkNm * 64);		
	    for(i=0;i<size;i++){
	        new_value[i]=information[j+i];
	    }
		return(1);
	}
	return(0);
}


unsigned int  FlashBlockWr(unsigned int BlkNm) 
{
    unsigned int j;
	if(BlkNm <= MAX_FLASH_BLOCK_NM){	
		j= (BlkNm * 64);		
    	flash_write(source_ptr,size,dest_ptr);
		FlashBlockRd(BlkNm);
		return(1);
	}
	return(0);
}



void	SetClearBit(unsigned char *TargetBuf,unsigned char value,unsigned char bitnm)
{
	unsigned char bitvalue;
	bitvalue=0x01;
	bitvalue=(bitvalue << bitnm);

	if( *TargetBuf & bitvalue){
		if(value==1){
			*TargetBuf=( *TargetBuf & ~bitvalue);	
		}				
	}
	else{
		if(value>1){
			*TargetBuf=( *TargetBuf | bitvalue);	
		}				
	}
}



void	SetClearByte(unsigned char *TargetBuf,unsigned char value)
{

	if(value > 0){
		value=(value - 1 );
		if(value != *TargetBuf){
			*TargetBuf=value;
		}
	}

}



/*
void	CmdSetupChk(unsigned char id)
{		

    unsigned char	tmpb;
    unsigned int    IdPt;
   
	IdPt=IsBufferPt(id);

    if((RcvBuf[IdPt+DSP1] == '9') && (RcvBuf[IdPt+DSP2] == '1') && !(RcvBuf[IdPt+1] & S1_AUTO) && ((RcvBuf[IdPt+SL_mCarOpCl] & 0xc0)== 0xc0) ){
		tmpb= (RcvBuf[IdPt+SL_mCarOpCl] & 0x03);
		SetClearBit(&new_value[6],tmpb,0);

		tmpb= (RcvBuf[IdPt+SL_mCarOpCl] & 0x0c);
		tmpb=(tmpb >> 2);
		SetClearBit(&new_value[6],tmpb,1);

		tmpb= (RcvBuf[IdPt+SL_mCarOpCl] & 0x30);
		tmpb=(tmpb >> 4);
		SetClearBit(&new_value[6],tmpb,2);


		tmpb= (RcvBuf[IdPt+SL_mCarKey25] & 0x03);
		SetClearBit(&new_value[6],tmpb,3);

		tmpb= (RcvBuf[IdPt+SL_mCarKey25] & 0x0c);
		tmpb=(tmpb >> 2);
		SetClearBit(&new_value[6],tmpb,4);


		SetClearByte( &new_value[7],RcvBuf[IdPt+SL_mCarKey1]);
		SetClearByte( &new_value[4],RcvBuf[IdPt+SL_mCarKey9]);
		SetClearByte( &new_value[3],RcvBuf[IdPt+SL_mCarKey17]);
		SetClearByte( &new_value[0],(id+1));
	}
 }

*/
