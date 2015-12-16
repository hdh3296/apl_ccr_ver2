

#include    <pic18.h>

#include        "com1_port.h"
#include        "ladder_cmd.h"
#include        "MyMessage.h"
#include        "setup.h"


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


#define     DIGIT_EDIT              0
#define     DIGIT_ALPHAR_EDIT       1
#define     TABLE_EDIT              2
#define     TOGGLE_EDIT             3
#define     DIGIT_STRING_EDIT       4
#define     CLOCK_EDIT              5
#define     NO_EDIT                 6



#define 	SECONDLINE_CURSOR       1

#define 	FIRSTLINE_BASE       	2
#define 	SECONDLINE_BASE       	18



#define     BIT_TYPE		1
#define     BYTE_TYPE		2
#define     INT_TYPE		3
#define     LONG_TYPE		4


#define     DIVIDE_0		0
#define     DIVIDE_10		1
#define     DIVIDE_100		2
#define     DIVIDE_1000		3


unsigned char	LadderBuf[17];
unsigned char	New485Ladder[MAX_LADDER_BUF]={0};      


unsigned int   GroupBaseAddr;
unsigned int   LadderGroup;
unsigned int   LadderGroupSub;

unsigned int   LadderKey;
unsigned int   EnterKey;




//unsigned int   DigitData;
//unsigned int   DigitMaxValue;
//unsigned int   DigitMinValue;
unsigned int   OrgNcNo;

unsigned int   LadderKeyTime;
unsigned int   LadderTime=0;

unsigned int   BefDspMode=0;
unsigned int   SaveVerify=0;


unsigned long   EditDigitData;
unsigned long   EditDigitMaxValue;
unsigned long   EditDigitMinValue;

unsigned int   EditDigitCursor;
unsigned int   EditDigitShiftCnt;
unsigned int   EditCursor;
unsigned int   EditStatus;
unsigned int   EditStart;
unsigned int   EditShiftCnt;
unsigned int   EditDivide;
unsigned int   EditDataType;
unsigned int   EditFlashAddr;


unsigned int   MaxSubMenu;
unsigned int   MemPointer;



	
bit	bMoveCar=0;

					



unsigned char	arabianm[10];

unsigned int  Decimal_Sort(unsigned long val)
{
	arabianm[0] = (unsigned char)((val / (unsigned long)1000000000) + '0');                     
    val =(unsigned long)(val % (unsigned long)1000000000);

	arabianm[1] = (unsigned char)((val / (unsigned long)100000000) + '0');                     
    val =(unsigned long)(val % (unsigned long)100000000);

	arabianm[2] = (unsigned char)((val / (unsigned long)10000000) + '0');                     
    val =(unsigned long)(val % (unsigned long)10000000);

	arabianm[3] = (unsigned char)((val / (unsigned long)1000000) + '0');                     
    val =(unsigned long)(val % (unsigned long)1000000);


	arabianm[4] = (unsigned char)((val / (unsigned long)100000) + '0');                     
    val =(unsigned long)(val % (unsigned long)100000);


	arabianm[5] = (unsigned char)((val / (unsigned long)10000) + '0');                     
    val =(unsigned long)(val % (unsigned long)10000);

	arabianm[6] = (unsigned char)((val / (unsigned long)1000) + '0');                     
    val =(unsigned long)(val % (unsigned long)1000);

	arabianm[7] = (unsigned char)((val / (unsigned long)100) + '0');                     
    val =(unsigned long)(val % (unsigned long)100);

	arabianm[8] = (unsigned char)((val / (unsigned long)10) + '0');                     
	arabianm[9] = (unsigned char)((val % (unsigned long)10) + '0');          

	return(0);           
}




unsigned int  Deciml_Dsp(unsigned int total_dig,unsigned int dp)
{
    unsigned int i,j;
    unsigned char tempbuf[10];
		
	if(dp == 0)			return(0);
	if(dp >= total_dig)	return(0);

	for(i=0;i<total_dig;i++){
		tempbuf[i]=New485Ladder[SECONDLINE_BASE+EditStart+i];                       
	}


	j=(total_dig-dp);
	New485Ladder[SECONDLINE_BASE+EditStart+j]='.';            
           
	for(i=j;i<total_dig;i++){
		New485Ladder[SECONDLINE_BASE+EditStart+i+1]=tempbuf[i];                       
	}
	return(0);
}



void  One_Dig_Dsp(unsigned long val,unsigned int dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+EditStart+0] = arabianm[9];                      
}


void  Two_Dig_Dsp(unsigned  long val,unsigned int dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+EditStart+0] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+EditStart+1] = arabianm[9];                     
	Deciml_Dsp(EditDigitShiftCnt,dp);
}


void  Three_Dig_Dsp(unsigned  long val,unsigned int dp)
{
		
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+EditStart+0] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+EditStart+1] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+EditStart+2] = arabianm[9];                     

	Deciml_Dsp(EditDigitShiftCnt,dp);
}


void   Four_Dig_Dsp(unsigned  long val,unsigned int dp)
{

	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+EditStart+0] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+EditStart+1] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+EditStart+2] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+EditStart+3] = arabianm[9];                     

	Deciml_Dsp(EditDigitShiftCnt,dp);
}


void Five_Dig_Dsp(unsigned  long val,unsigned int dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+EditStart+0] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+EditStart+1] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+EditStart+2] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+EditStart+3] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+EditStart+4] = arabianm[9];                     

	Deciml_Dsp(EditDigitShiftCnt,dp);
}


void Six_Dig_Dsp(unsigned  long val,unsigned int dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+EditStart+0] = arabianm[4];                     
	New485Ladder[SECONDLINE_BASE+EditStart+1] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+EditStart+2] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+EditStart+3] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+EditStart+4] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+EditStart+5] = arabianm[9];                     

	Deciml_Dsp(EditDigitShiftCnt,dp);
}


void Seven_Dig_Dsp(unsigned  long val,unsigned int dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+EditStart+0] = arabianm[3];                     
	New485Ladder[SECONDLINE_BASE+EditStart+1] = arabianm[4];                     
	New485Ladder[SECONDLINE_BASE+EditStart+2] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+EditStart+3] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+EditStart+4] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+EditStart+5] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+EditStart+6] = arabianm[9];                     

	Deciml_Dsp(EditDigitShiftCnt,dp);
}


void Eight_Dig_Dsp(unsigned long val,unsigned int dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+EditStart+0] = arabianm[2];                     
	New485Ladder[SECONDLINE_BASE+EditStart+1] = arabianm[3];                     
	New485Ladder[SECONDLINE_BASE+EditStart+2] = arabianm[4];                     
	New485Ladder[SECONDLINE_BASE+EditStart+3] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+EditStart+4] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+EditStart+5] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+EditStart+6] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+EditStart+7] = arabianm[9];                     

	Deciml_Dsp(EditDigitShiftCnt,dp);

}



void Nine_Dig_Dsp(unsigned long val,unsigned int dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+EditStart+0] = arabianm[1];                     
	New485Ladder[SECONDLINE_BASE+EditStart+1] = arabianm[2];                     
	New485Ladder[SECONDLINE_BASE+EditStart+2] = arabianm[3];                     
	New485Ladder[SECONDLINE_BASE+EditStart+3] = arabianm[4];                     
	New485Ladder[SECONDLINE_BASE+EditStart+4] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+EditStart+5] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+EditStart+6] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+EditStart+7] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+EditStart+8] = arabianm[9];                     
	Deciml_Dsp(EditDigitShiftCnt,dp);
}


void Ten_Dig_Dsp(unsigned long val,unsigned int dp)
{
	Decimal_Sort(val);
	New485Ladder[SECONDLINE_BASE+EditStart+0] = arabianm[0];                     
	New485Ladder[SECONDLINE_BASE+EditStart+1] = arabianm[1];                     
	New485Ladder[SECONDLINE_BASE+EditStart+2] = arabianm[2];                     
	New485Ladder[SECONDLINE_BASE+EditStart+3] = arabianm[3];                     
	New485Ladder[SECONDLINE_BASE+EditStart+4] = arabianm[4];                     
	New485Ladder[SECONDLINE_BASE+EditStart+5] = arabianm[5];                     
	New485Ladder[SECONDLINE_BASE+EditStart+6] = arabianm[6];                     
	New485Ladder[SECONDLINE_BASE+EditStart+7] = arabianm[7];                     
	New485Ladder[SECONDLINE_BASE+EditStart+8] = arabianm[8];                     
	New485Ladder[SECONDLINE_BASE+EditStart+9] = arabianm[9];                     
	Deciml_Dsp(EditDigitShiftCnt,dp);
}



/*
	
void    __attribute__((section(".usercode"))) RpmDsp485(void)
{
    unsigned int chun;
    unsigned long tmpcalu;

    tmpcalu=(PulsePer100Msec >> 2); // 4x
    tmpcalu=tmpcalu * 600 * 10;
    tmpcalu=(tmpcalu/(unsigned long)FlashDspCharBuf[ENCODER_PULSE].long_data);

    chun=(unsigned int)tmpcalu;

	Chun_Dsp(chun,1);

	New485Ladder[SECONDLINE_BASE+EditStart+5] = ' ';
	New485Ladder[SECONDLINE_BASE+EditStart+6] = 'R';
	New485Ladder[SECONDLINE_BASE+EditStart+7] = 'p';
	New485Ladder[SECONDLINE_BASE+EditStart+8] = 'm';

}



void    __attribute__((section(".usercode"))) MpmDsp485(unsigned int val)
{
    unsigned int chun;
	
	chun=val;
	Chun_Dsp(chun,1);

	New485Ladder[SECONDLINE_BASE+EditStart+5] = ' ';
	New485Ladder[SECONDLINE_BASE+EditStart+6] = 'm';
	New485Ladder[SECONDLINE_BASE+EditStart+7] = 'p';
	New485Ladder[SECONDLINE_BASE+EditStart+8] = 'm';
}





void    __attribute__((section(".usercode"))) CurEncoderPulse(unsigned long vx)
{

	Chunman_Dsp(vx,0);

    New485Ladder[SECONDLINE_BASE+EditStart+8] ='p';          
    New485Ladder[SECONDLINE_BASE+EditStart+9] ='u';          
    New485Ladder[SECONDLINE_BASE+EditStart+10]='l';          
    New485Ladder[SECONDLINE_BASE+EditStart+11]='s';          
    New485Ladder[SECONDLINE_BASE+EditStart+12]='e';          

}





void    __attribute__((section(".usercode"))) MoveCounterDsp(void)
{
    unsigned long value;


    value=MoveCounterx;

    New485Ladder[SECONDLINE_BASE+EditStart+0]=(value/1000000)  + '0';
    value=value%1000000;              
    New485Ladder[SECONDLINE_BASE+EditStart+1]=(value/100000)   + '0';
    value=value%100000;              
    New485Ladder[SECONDLINE_BASE+EditStart+2]=(value/10000)    + '0';
    value=value%10000;              
    New485Ladder[SECONDLINE_BASE+EditStart+3]=(value/1000)     + '0';
    value=value%1000;              
    New485Ladder[SECONDLINE_BASE+EditStart+4]=(value/100)      + '0';
    value=value%100;                        
    New485Ladder[SECONDLINE_BASE+EditStart+5]=(value/10)       + '0';          
    New485Ladder[SECONDLINE_BASE+EditStart+6]=(value%10)       + '0';          


    New485Ladder[SECONDLINE_BASE+EditStart+7]  =' ';          
    New485Ladder[SECONDLINE_BASE+EditStart+8]  ='m';          
    New485Ladder[SECONDLINE_BASE+EditStart+9]  ='o';          
    New485Ladder[SECONDLINE_BASE+EditStart+10] ='v';          
    New485Ladder[SECONDLINE_BASE+EditStart+11] ='e';          
}



void    __attribute__((section(".usercode"))) ErrCounterDsp(void)
{
    LocalType  value;

    value=eDArry[eErrCntPt];

	Man_Dsp(value,0);

    New485Ladder[SECONDLINE_BASE+EditStart+5]  =' ';          
    New485Ladder[SECONDLINE_BASE+EditStart+6]  ='E';          
    New485Ladder[SECONDLINE_BASE+EditStart+7]  ='r';          
    New485Ladder[SECONDLINE_BASE+EditStart+8]  ='r';          
    New485Ladder[SECONDLINE_BASE+EditStart+9]  ='o';          
    New485Ladder[SECONDLINE_BASE+EditStart+10] ='r';          
}



void    __attribute__((section(".usercode"))) Rs485ComDsp(void)
{
    New485Ladder[SECONDLINE_BASE+EditStart+0]='E';
    New485Ladder[SECONDLINE_BASE+EditStart+1]='/';
    New485Ladder[SECONDLINE_BASE+EditStart+2]='B';
    New485Ladder[SECONDLINE_BASE+EditStart+3]=' ';
    New485Ladder[SECONDLINE_BASE+EditStart+4]=BdName485[ErrBdNamePt][0];
    New485Ladder[SECONDLINE_BASE+EditStart+5]=BdName485[ErrBdNamePt][1];
    New485Ladder[SECONDLINE_BASE+EditStart+6]=BdName485[ErrBdNamePt][2];
}




void    __attribute__((section(".usercode"))) SetBitData(LocalType  pt)
{
    if(pt & 0x01)  New485Ladder[SECONDLINE_BASE+EditStart+0] = '1';
    else           New485Ladder[SECONDLINE_BASE+EditStart+0] = '0';
    if(pt & 0x02)  New485Ladder[SECONDLINE_BASE+EditStart+1] = '2';
    else           New485Ladder[SECONDLINE_BASE+EditStart+1] = '0';
    if(pt & 0x04)  New485Ladder[SECONDLINE_BASE+EditStart+2] = '3';
    else           New485Ladder[SECONDLINE_BASE+EditStart+2] = '0';
    if(pt & 0x08)  New485Ladder[SECONDLINE_BASE+EditStart+3] = '4';
    else           New485Ladder[SECONDLINE_BASE+EditStart+3] = '0';
    if(pt & 0x10)  New485Ladder[SECONDLINE_BASE+EditStart+4] = '5';
    else           New485Ladder[SECONDLINE_BASE+EditStart+4] = '0';
    if(pt & 0x20)  New485Ladder[SECONDLINE_BASE+EditStart+5]= '6';
    else           New485Ladder[SECONDLINE_BASE+EditStart+5]= '0';
    if(pt & 0x40)  New485Ladder[SECONDLINE_BASE+EditStart+6]= '7';
    else           New485Ladder[SECONDLINE_BASE+EditStart+6]= '0';
    if(pt & 0x80)  New485Ladder[SECONDLINE_BASE+EditStart+7]= '8';
    else           New485Ladder[SECONDLINE_BASE+EditStart+7]= '0';
}


void    __attribute__((section(".usercode"))) Input(LocalType  pt)
{
    LocalType  i,tmpedit;

    pt=pt-7;

	for(i=0;i<3;i++)	New485Ladder[SECONDLINE_BASE+EditStart+i]=InputName[pt][i]; 


    New485Ladder[SECONDLINE_BASE+EditStart+3]= ' ';
    New485Ladder[SECONDLINE_BASE+EditStart+4]= ' ';

	tmpedit=EditStart;
	EditStart=(EditStart+5);
	switch(pt){
		case	0:
			i=(LocalType)sRamDArry[I_EMG];
			i= ~i;
			SetBitData(i);
			break;
		case	1:
			i=(LocalType)sRamDArry[I_SU1];
			i= ~i;
			SetBitData(i);
			break;
		case	2:
			i=(LocalType)sRamDArry[I_GR];
			i= ~i;
			SetBitData(i);
			break;
		case	3:
			i=(LocalType)sRamDArry[I_FIRE];
			i= ~i;
			SetBitData(i);
			break;
		case	4:
			i=(LocalType)sRamDArry[I_X_0];
			i= ~i;
			SetBitData(i);
			break;
		case	5:
			i=(LocalType)sRamDArry[I_FS0];
			i= ~i;
			SetBitData(i);
			break;
	}
													
	EditStart=tmpedit;
}




void    __attribute__((section(".usercode"))) MemDsp(void)
{
    LocalType  value,tmpedit;

    New485Ladder[SECONDLINE_BASE+EditStart+0]= 'M';
    New485Ladder[SECONDLINE_BASE+EditStart+1]= ' ';
    New485Ladder[SECONDLINE_BASE+EditStart+2]= ' ';
    New485Ladder[SECONDLINE_BASE+EditStart+3]= ' ';
    New485Ladder[SECONDLINE_BASE+EditStart+4]= ' ';

    value=MemPointer;

    New485Ladder[SECONDLINE_BASE+EditStart+1]=(value/100)      + '0';
    value=value%100;                        
    New485Ladder[SECONDLINE_BASE+EditStart+2]=(value/10)       + '0';          
    New485Ladder[SECONDLINE_BASE+EditStart+3]=(value%10)       + '0';          

	tmpedit=EditStart;
	EditStart=(EditStart+5);

	SetBitData((LocalType)sRamDArry[MemPointer]);

	EditStart=tmpedit;

}



void    __attribute__((section(".usercode"))) SpeedDsp(void)
{
    unsigned int count,tmpspddsp;
    unsigned int chun,bek,sip,il;

    chun=bek=sip=il=0;

	bExportData=0;
	bImportData=0;

	New485Ladder[2+0]='F';
	New485Ladder[2+1]='L';
	New485Ladder[2+2]=':';


	if(sRamDArry[DSP1] == 0)	sRamDArry[DSP1] = '?';	
	if(sRamDArry[DSP2] == 0)	sRamDArry[DSP2] = '?';	
	New485Ladder[2+3]=sRamDArry[DSP1];
	New485Ladder[2+4]=sRamDArry[DSP2];

	New485Ladder[2+5]=' ';

	if(CurMeterPerMin > 1)	tmpspddsp=1;
	else					tmpspddsp=0;

	if( (bCarUpMove || bCarDnMove) || (tmpspddsp > 0) ){ 
	
	    chun=(unsigned int)CurMeterPerMin;
	
	    if(chun)    il=(chun%10);
	    
	    if(chun)    sip=(chun/10);
	    if(sip)     sip=(sip%10);
	
	    if(chun)    bek=(chun/100);
	    if(bek)     bek=(bek%10);;
	
	    if(chun)    chun=chun/1000;
	    if(chun)    chun=(chun%10);
        

   		if(New_Spd_SystemChk()){
			if(PerfectAuto()){
	            New485Ladder[2+6] =chun + '0';
	            New485Ladder[2+7] =bek  + '0';
	            New485Ladder[2+8]=sip   + '0';
	            New485Ladder[2+9]='.';
	            New485Ladder[2+10]=il   + '0';
	            New485Ladder[2+11]='m';
	            New485Ladder[2+12]='p';
	            New485Ladder[2+13]='m';
	            New485Ladder[2+14]=' ';
	            New485Ladder[2+15]=' ';

	            New485Ladder[2+14]='-';
	            New485Ladder[2+15]=' ';
	
				if(bUnd){
	            	New485Ladder[2+15]='D';
				}
				else if(CurSpeed==SPEED_LOW){
	            	New485Ladder[2+15]='L';
				}
				else if(CurSpeed==SPEED_MID){
	            	New485Ladder[2+15]='M';
				}
				else if(CurSpeed==SPEED_HIGH){
	            	New485Ladder[2+15]='H';
				}
				else{
	            	New485Ladder[2+15]='Z';
				}
			}
			else{
	            New485Ladder[2+6]=' ';
	            New485Ladder[2+7]=' ';
	            New485Ladder[2+8] =chun + '0';
	            New485Ladder[2+9] =bek  + '0';
	            New485Ladder[2+10]=sip  + '0';
	            New485Ladder[2+11]='.';
	            New485Ladder[2+12]=il   + '0';
	            New485Ladder[2+13]='m';
	            New485Ladder[2+14]='p';
	            New485Ladder[2+15]='m';
			}
		}
		else{
	           New485Ladder[2+6]=' ';
	           New485Ladder[2+7]=' ';
	           New485Ladder[2+8] =chun + '0';
	           New485Ladder[2+9] =bek  + '0';
	           New485Ladder[2+10]=sip  + '0';
	           New485Ladder[2+11]='.';
	           New485Ladder[2+12]=il   + '0';
	           New485Ladder[2+13]='m';
	           New485Ladder[2+14]='p';
	           New485Ladder[2+15]='m';
		}	 
	}    
	else{
	    New485Ladder[2+6]=' ';
	    New485Ladder[2+7]=' ';
	    New485Ladder[2+8]='E';
	    New485Ladder[2+9]='/';
	    New485Ladder[2+10]='L';
	    New485Ladder[2+11]='.';
	    New485Ladder[2+12]='S';
	    New485Ladder[2+13]='t';
	    New485Ladder[2+14]='o';
	    New485Ladder[2+15]='p';
	}
}



unsigned int __attribute__((section(".usercode"))) TunningMessage(void)
{
	unsigned int i,j;

    j=sRamDArry[mSysStatus];
    for(i=0;i<16;i++)	New485Ladder[SECONDLINE_BASE+i] =StatusMessage[j][i];
	           
	return(0);
}



unsigned int __attribute__((section(".usercode"))) FHM_SuccessDisplay(void)
{
	unsigned int i;
	for(i=0;i<16;i++){
		New485Ladder[SECONDLINE_BASE+i] = FhmSuccessMsg[i];          
	}
	return(0);
}

unsigned int __attribute__((section(".usercode"))) BlinkDisplay(void)
{	

 	if( (sRamDArry[mSysStatus]==sFhmError) && bFhmRun)								return(1);  // blink
	else if(bAutoTunning)															return(0);  // no blink
 	else if(bFhmRun)																return(0);  // no blink
	else if(sRamDArry[mSysStatus] <= sCLE_NO_ON)									return(0);  // no blink


	if(!IN_AUTO){
		if(sRamDArry[mSysStatus]==sREADY){
			if(sRamDArry[mEV_LastErr] != 0xff)	return(1);	// blink
			else								return(0);  // no blink
		}	
		else{
			if((sRamDArry[mSysStatus]==sFireOn) || (sRamDArry[mSysStatus]==sWaterSense) || (sRamDArry[mSysStatus]==sVIP)){
				if(S1_OVERLOAD1)		return(2);  // blink
				else if(bSafety_scrSft)	return(3);  // blink
				else					return(0);  // no blink
			}
		}
	}
	else{
		return(0);  // no blink
	}
}







void  __attribute__((section(".usercode"))) CalendarChk(void)
{
    if(LadderGroupSub==30){
        switch(Cursor){
            case    0:
                if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor] > '2'){
                    New485Ladder[SECONDLINE_BASE+EditStart+Cursor]='0';          
                }
                else if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor] == '2'){
                    if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor+1] > '4'){
                        New485Ladder[SECONDLINE_BASE+EditStart+Cursor+1]='0';          
                    }
                }
                break;
            case    1:
                if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor-1] == '2'){
                    if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor] > '4'){
                        New485Ladder[SECONDLINE_BASE+EditStart+Cursor]='0';          
                    }
                }
                break;
            case    3:
            case    6:
                if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor] > '5')    New485Ladder[SECONDLINE_BASE+EditStart+Cursor]='0';          
                break;
        }
    }
    else if(LadderGroupSub==31){
        switch(Cursor){
            case    3:
                if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor] > '1')    New485Ladder[SECONDLINE_BASE+EditStart+Cursor]='0';          
                else if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor] == '1'){
                    if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor+1] > '2'){
                        New485Ladder[SECONDLINE_BASE+EditStart+Cursor+1]='0';          
                    }
                }
                break;
            case    4:
                if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor-1] == '1'){
                    if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor] > '2'){
                        New485Ladder[SECONDLINE_BASE+EditStart+Cursor]='0';          
                    }
                }
                break;
            case    6:
                if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor] > '3')    New485Ladder[SECONDLINE_BASE+EditStart+Cursor]='0';          
                else if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor] == '3'){
                    if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor+1] > '1'){
                        New485Ladder[SECONDLINE_BASE+EditStart+Cursor+1]='0';          
                    }
                }
                break;
            case    7:
                if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor-1] == '3'){
                    if(New485Ladder[SECONDLINE_BASE+EditStart+Cursor] > '1'){
                        New485Ladder[SECONDLINE_BASE+EditStart+Cursor]='0';          
                    }
                }
                break;
        }
    }
}




unsigned int __attribute__((section(".usercode"))) SensorPositionDisplay(unsigned int pt)
{
    LocalType  i,val;

	New485Ladder[FIRSTLINE_BASE+13]=(unsigned char)((pt/10) + '0');
	New485Ladder[FIRSTLINE_BASE+14]=(unsigned char)((pt%10) + '0');

	EditStart=7;

	i=(pt * 2);
	val=SensorPositionBuf[i];
	if(val > 9999)	val = 9999;	
	Chun_Dsp(val,0);

	i++;
	EditStart=(EditStart + 5);
	val=SensorPositionBuf[i];
	if(val > 9999)	val = 9999;	
	Chun_Dsp(val,0);

	EditStart=0;

	return(0);		
}



unsigned int __attribute__((section(".usercode"))) FinalErrDisplay(unsigned int pt)
{

    LocalType  i,val;
	
	New485Ladder[FIRSTLINE_BASE+13]=(unsigned char)((pt/10) + '0');
	New485Ladder[FIRSTLINE_BASE+14]=(unsigned char)((pt%10) + '0');

	EditStart=8;

    switch(pt){
        case    0:
			EditStart=3;

			i= cF_FLRDSPCH((unsigned long)(F_E_StartFloor));
			i=(i * 2);

            New485Ladder[SECONDLINE_BASE+EditStart+0] = cF_FLRDSPCH((unsigned long)i);          
            New485Ladder[SECONDLINE_BASE+EditStart+1] = cF_FLRDSPCH((unsigned long)(i+1));          


			i= cF_FLRDSPCH((unsigned long)(F_E_DestFloor));
			i=(i * 2);

            New485Ladder[SECONDLINE_BASE+EditStart+3] = cF_FLRDSPCH((unsigned long)i);          
            New485Ladder[SECONDLINE_BASE+EditStart+4] = cF_FLRDSPCH((unsigned long)(i+1));          


			i= cF_FLRDSPCH((unsigned long)(F_E_CurFloor));
			i=(i * 2);

            New485Ladder[SECONDLINE_BASE+EditStart+6] = cF_FLRDSPCH((unsigned long)i);          
            New485Ladder[SECONDLINE_BASE+EditStart+7] = cF_FLRDSPCH((unsigned long)(i+1));          


			i= cF_FLRDSPCH((unsigned long)(F_E_ErrNum));
            New485Ladder[SECONDLINE_BASE+EditStart+10] = 'E';          
            New485Ladder[SECONDLINE_BASE+EditStart+11] = (unsigned char)((i/10) + '0');          
            New485Ladder[SECONDLINE_BASE+EditStart+12] = (unsigned char)((i%10) + '0');          

            break;
        case    1:
			EditStart=3;
			val= cF_FLRDSPCH((unsigned long)(F_E_ErrNum));
            for(i=0;i<13;i++){
                New485Ladder[SECONDLINE_BASE+EditStart+i] =StatusMessage[val][i];          
            }
            break;
        case    2:
			EditStart=3;

			i= cF_FLRDSPCH((unsigned long)(F_E_LuLdFloor));
			i=(i * 2);

            New485Ladder[SECONDLINE_BASE+EditStart+0] = cF_FLRDSPCH((unsigned long)i);          
            New485Ladder[SECONDLINE_BASE+EditStart+1] = cF_FLRDSPCH((unsigned long)(i+1));          


			i= cF_FLRDSPCH((unsigned long)(F_E_InvFloor));
			i=(i * 2);

            New485Ladder[SECONDLINE_BASE+EditStart+3] = cF_FLRDSPCH((unsigned long)i);          
            New485Ladder[SECONDLINE_BASE+EditStart+4] = cF_FLRDSPCH((unsigned long)(i+1));          
            break;
        case    3:
			Chunman_Dsp( GET_LONG_BYTE((unsigned long)(F_E_CurPulse0)),0 );
            break;
        case    4:
			val=iF_FLRDSPCH((unsigned long)(F_E_Mpm0));
			Chun_Dsp(val,1);
            break;
        case    5:			
			EditStart=7;

			i= cF_FLRDSPCH((unsigned long)(F_E_CurMonth));
			i=(i & 0x00ff);
            New485Ladder[SECONDLINE_BASE+EditStart+0] = (unsigned char)((i >> 4)      + '0');          
            New485Ladder[SECONDLINE_BASE+EditStart+1] = (unsigned char)((i &  0x0f)   + '0');          


			i= cF_FLRDSPCH((unsigned long)(F_E_CurDay));
			i=(i & 0x00ff);
            New485Ladder[SECONDLINE_BASE+EditStart+2] = (unsigned char)((i >> 4)      + '0');         
            New485Ladder[SECONDLINE_BASE+EditStart+3] = (unsigned char)((i &  0x0f)   + '0');          

            New485Ladder[SECONDLINE_BASE+EditStart+4] = '/';

          
			i= cF_FLRDSPCH((unsigned long)(F_E_CurHour));
			i=(i & 0x00ff);
            New485Ladder[SECONDLINE_BASE+EditStart+5] = (unsigned char)((i >> 4)      + '0');          
            New485Ladder[SECONDLINE_BASE+EditStart+6] = (unsigned char)((i &  0x0f)   + '0');          

			i= cF_FLRDSPCH((unsigned long)(F_E_CurMin));
			i=(i & 0x00ff);
            New485Ladder[SECONDLINE_BASE+EditStart+7] = (unsigned char)((i >> 4)      + '0');          
            New485Ladder[SECONDLINE_BASE+EditStart+8] = (unsigned char)((i &  0x0f)   + '0');          

            break;

        case    6:
			SetBitData((LocalType)(cF_FLRDSPCH((unsigned long)(F_E_OUT_UP))) );
			break;
        case    7:			// 
			SetBitData((LocalType)(cF_FLRDSPCH((unsigned long)(F_E_OUT_OP))) );
			break;
        case    8:
			SetBitData((LocalType)(cF_FLRDSPCH((unsigned long)(F_E_OUT_FAN))) );
			break;	
        case    9:
			i=(LocalType)(cF_FLRDSPCH((unsigned long)(F_E_IN_EMG)));
			i= ~i;
			SetBitData((LocalType)(i));
			break;	
        case    10:
			i=(LocalType)(cF_FLRDSPCH((unsigned long)(F_E_IN_SUS)));
			i= ~i;
			SetBitData((LocalType)(i));
			break;	
        case    11:
			i=(LocalType)(cF_FLRDSPCH((unsigned long)(F_E_IN_RG)));
			i= ~i;
			SetBitData((LocalType)(i));
			break;	
        case    12:
			i=(LocalType)(cF_FLRDSPCH((unsigned long)(F_E_IN_FR1)));
			i= ~i;
			SetBitData((LocalType)(i));
			break;	
        case    13:
			i=(LocalType)(cF_FLRDSPCH((unsigned long)(F_E_IN_X0)));
			i= ~i;
			SetBitData((LocalType)(i));
			break;	
        case    14:
			i=(LocalType)(cF_FLRDSPCH((unsigned long)(F_E_IN_FS0)));
			i= ~i;
			SetBitData((LocalType)(i));
            break;

	}

	EditStart=0;

	return(0);		
}



void  __attribute__((section(".usercode"))) GetFlashDataToBufRam(unsigned int BytePt)
{
    LocalType  i,j;

    j=((BytePt/64) * 16);

    for(i=0;i<16;i++){
        parameter_mirror[i]=FlashDspCharBuf[j+i].long_data;
    }
}


/////////

void  __attribute__((section(".usercode"))) DspCharSave(unsigned int pt,unsigned int DtNm)
{
    LocalType  i,j,k;

    k=(pt % 64);

    j=((pt/64) * 16);

    for(i=0;i<16;i++){
        parameter_mirror[i]=FlashDspCharBuf[j+i].long_data;
    }

    for(i=0;i<DtNm;i++){
        b_LdTmpBufRam((unsigned long)(pt+i))     = New485Ladder[SECONDLINE_BASE+EditStart+i];
    }
    
    k = New485Ladder[SECONDLINE_BASE+EditStart+1];

    
    if(pt==0){ 
        if(b_LdTmpBufRam(0) == 'B'){             
            if(k == '7')        i=0;  
            else if(k == '6')   i=2;  
            else if(k == '5')   i=4;  
            else if(k == '4')   i=6;  
            else if(k == '3')   i=8;  
            else if(k == '2')   i=10;  
            else if(k == '1')   i=12;
            else                pt=1;  
        }
        else if(b_LdTmpBufRam(0) == '0'){ 
            if(k == '1')        i=14;
            else                pt=1;  
        }
        else                    pt=1;
        
        if(pt==0){
            for(k=0;k<64;k++,i++){
                b_LdTmpBufRam(k)  = DftFlrName[i];
            }
        }
    }

    flash_write_DspChar(pt);
}











void  __attribute__((section(".usercode"))) FlrDspGroup(LocalType offset)
{
    LocalType i;

    i=(offset *2 );
	i=(i+F_FlrDspCh);

    Cursor=0;
    ShiftCnt=2;
    EditStart=7;
    EditStatus=DIGIT_ALPHAR_EDIT;

    New485Ladder[SECONDLINE_BASE+EditStart+0]=cF_FLRDSPCH((unsigned long)(i+0));  
    New485Ladder[SECONDLINE_BASE+EditStart+1]=cF_FLRDSPCH((unsigned long)(i+1));          
}


void  __attribute__((section(".usercode"))) FlrDspGroupSave(LocalType offset)
{
	offset=(offset *2);
	offset=(offset + F_FlrDspCh);
		
    DspCharSave(offset,ShiftCnt);

}





void  __attribute__((section(".usercode"))) FlrGroup(void)
{
    LocalType i;

    
    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=2;
    EditStart=7;
    EditStatus=DIGIT_EDIT;

    DigitMaxValue=cF_TOPFLR+1;
    DigitMinValue=1;

    switch(LadderGroupSub){  
        case    TOP_FLR:      
        case    NO_USE_GO_FLR:
		case	KIDS_KEY_CNT:
		case	X7_SAFE_FLR:
		case	X6_SAFE_FLR:
		case	X5_SAFE_FLR:
            DigitMaxValue=SYSTEM_TOP_FLR+1;
            break;
        case    ONE_STOP_FLR:
		    ShiftCnt=3;
		    EditStart=6;
    		DigitMinValue=0;
            DigitMaxValue=256;
			break;

    }
    DigitData=cF_FLRDSPCH((unsigned long)i);
    DigitData=DigitData+1;
    Integer_Digit();    
}



void  __attribute__((section(".usercode"))) FlrGroupSave(void)
{
    LocalType i;

    DigitData=DigitData-1;

    i=(LadderGroupSub + GroupBaseAddr);
    GetFlashDataToBufRam(F_BLOCK1);
    b_LdTmpBufRam(i)=(LocalType)(DigitData);
    flash_write_DspChar(F_BLOCK1);
}



void  __attribute__((section(".usercode"))) WaitFlrConvStr(LocalType	i)
{
	New485Ladder[SECONDLINE_BASE+EditStart+ (i+0)] =(DigitData / 10)  	+ '0';          
	New485Ladder[SECONDLINE_BASE+EditStart+ (i+1)] =(DigitData % 10)  	+ '0';          
}


void  __attribute__((section(".usercode"))) WaitFlrGroup(void)
{
    LocalType i;
    
    i=((LadderGroupSub * 5) + GroupBaseAddr);

	Cursor=0;
	ShiftCnt=12;
	EditStart=4;
	EditStatus=CLOCK_EDIT;

	if(LadderGroupSub <= 3){
		DigitData=cF_FLRDSPCH((unsigned long)i);
		WaitFlrConvStr(0);

	
		DigitData=cF_FLRDSPCH((unsigned long)(i+1));
		WaitFlrConvStr(2);
		New485Ladder[SECONDLINE_BASE+EditStart+4] ='-';          
	
		DigitData=cF_FLRDSPCH((unsigned long)(i+2));
		WaitFlrConvStr(5);
	
		DigitData=cF_FLRDSPCH((unsigned long)(i+3));
		WaitFlrConvStr(7);
		New485Ladder[SECONDLINE_BASE+EditStart+9]='-';          
	
		DigitData=cF_FLRDSPCH((unsigned long)(i+4));
		DigitData=(DigitData + 1);
		New485Ladder[SECONDLINE_BASE+EditStart+10]=(DigitData / 10)	+ '0';          
		New485Ladder[SECONDLINE_BASE+EditStart+11]=(DigitData % 10)    + '0';          
	}
}



void  __attribute__((section(".usercode"))) WaitFlrConv(LocalType	i)
{
	DigitData=New485Ladder[SECONDLINE_BASE+EditStart + i ]-'0';
    DigitData=(DigitData * 10);      
	DigitData=((New485Ladder[SECONDLINE_BASE+EditStart + (i+1)] -'0') + DigitData);          
}


void  __attribute__((section(".usercode"))) WaitFlrGroupSave(void)
{
    LocalType i;

	if(LadderGroupSub <= 3){

	    i=(LadderGroupSub * 5);
	    GetFlashDataToBufRam(F_BLOCK3);

		WaitFlrConv(0);
	

	    b_LdTmpBufRam((unsigned long)(i))=(LocalType)(DigitData);

	
		i++;
		WaitFlrConv(2);

	    b_LdTmpBufRam((unsigned long)(i))=(LocalType)(DigitData);
	
		i++;
		WaitFlrConv(5);
	    b_LdTmpBufRam((unsigned long)(i))=(LocalType)(DigitData);
	
		i++;
		WaitFlrConv(7);
	    b_LdTmpBufRam((unsigned long)(i))=(LocalType)(DigitData);
	
		i++;
		WaitFlrConv(10);
	    b_LdTmpBufRam((unsigned long)(i))=(LocalType)(DigitData-1);

		flash_write_DspChar(F_BLOCK3);
	}
}





void  __attribute__((section(".usercode"))) TimerGroup(void)
{
    LocalType i;


    switch(LadderGroupSub){        
        case    23:
        case    24:
            Cursor=0;
            ShiftCnt=2;
            EditStart=5;
            EditStatus=DIGIT_EDIT;
            DigitMinValue=0;
            DigitMaxValue=81;
            i=(LadderGroupSub + F_OpWtTm);
			DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
            break;

        case    18:
        case    19:
        case    20:
        case    21:
        case    22:


            Cursor=0;
            ShiftCnt=3;
            EditStart=5;
            EditStatus=DIGIT_EDIT;
            DigitMinValue=0;
            DigitMaxValue=254;
            i=(LadderGroupSub + F_OpWtTm);
			DigitData=cF_FLRDSPCH((unsigned long)i);

            Integer_Digit();
            break;

        case    0:
        case    1:
		case	2:
            i=(LadderGroupSub + F_OpWtTm);
            Cursor=0;
            ShiftCnt=3;
            EditStart=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=254;
            DigitMinValue=0;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();
			break;
        case    3:
            i=(LadderGroupSub + F_OpWtTm);
            Cursor=0;
            EditStart=6;
            EditStatus=DIGIT_EDIT;
            ShiftCnt=3;
            DigitMaxValue=200;
            DigitMinValue=0;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();    
            break;
        case    5:
        case    6:
        case    4:
        case    8:
        case    9:
        case   10:
            i=(LadderGroupSub + F_OpWtTm);
            Cursor=0;
            ShiftCnt=2;
            EditStart=6;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=99;
            DigitMinValue=0;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();    
            break;
        case    7:
        case    11:
        case    12:
            i=(LadderGroupSub + F_OpWtTm);
            Cursor=0;
            ShiftCnt=2;
            EditStart=6;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=20;
            DigitMinValue=0;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();    
            break;
        default:
            i=(LadderGroupSub + F_OpWtTm);
            Cursor=0;
            ShiftCnt=3;
            EditStart=6;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=250;
            DigitMinValue=0;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();    
            break;
    }    
}


void  __attribute__((section(".usercode"))) TimerGroupSave(void)
{
    LocalType i;

    i=(LadderGroupSub + F_OpWtTm);

    GetFlashDataToBufRam(F_BLOCK1);
    b_LdTmpBufRam(i)=(LocalType)(DigitData);
    flash_write_DspChar(F_BLOCK1);
}


void  __attribute__((section(".usercode"))) OnOffGroup(void)
{
    LocalType i,j,BitValue;

    i=((LadderGroupSub/8) + GroupBaseAddr);
    j=(LadderGroupSub%8);
    BitValue=(0x01 << j);

    Cursor=0;
    ShiftCnt=0;
    EditStart=4;
    EditStatus=DIGIT_STRING_EDIT;                   
    DigitMaxValue=2;
    DigitMinValue=0;

    DigitData=cF_FLRDSPCH((unsigned long)i);

    if(DigitData &  BitValue)   DigitData=1;     
    else                        DigitData=0;     

    if((LadderGroup == ONOFF2_GROUP)  && (LadderGroupSub == FHM_CHK)) EditStatus=NO_EDIT;                   

    Integer_Digit();
}




void  __attribute__((section(".usercode"))) OnOffGroupSave(void)
{
    LocalType i,j;
	LocalType block_pt;

	block_pt=(GroupBaseAddr/64);
	block_pt=(block_pt * 64);


    i=((LadderGroupSub/8) + GroupBaseAddr);
    j=(LadderGroupSub%8);

    GetFlashDataToBufRam(block_pt);

    if(DigitData){
        bit_LdTmpBufRamSet(i,j);
    }
    else{
        bit_LdTmpBufRamReset(i,j);
    }
    flash_write_DspChar(block_pt);


    if(LadderGroup == ONOFF1_GROUP){
		ShadowsRamDArry[FLR_ON_OFF0]=cF_NONSERVICE0;
		ShadowsRamDArry[FLR_ON_OFF1]=cF_NONSERVICE1;
		ShadowsRamDArry[FLR_ON_OFF2]=cF_NONSERVICE2;
		ShadowsRamDArry[FLR_ON_OFF3]=cF_NONSERVICE3;
	}
}



void  __attribute__((section(".usercode"))) NcNoGroup(void)
{
    LocalType i,j,BitValue;

    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=0;
    EditStart=4;
    EditStatus=DIGIT_STRING_EDIT;                   
    DigitMaxValue=2;
    DigitMinValue=0;

    DigitData=cF_FLRDSPCH((unsigned long)i);

    if(DigitData &  0x80)       DigitData=1;     
    else                        DigitData=0;     

    Integer_Digit();
}


void  __attribute__((section(".usercode"))) InNcNoGroupSave(void)
{
    LocalType i,j;


    i=(LadderGroupSub + GroupBaseAddr);

    GetFlashDataToBufRam(F_BLOCK4);

    if(DigitData){
        b_LdTmpBufRam(i)=(LocalType)(b_LdTmpBufRam(i) | 0x80);
    }
    else{
        b_LdTmpBufRam(i)=(LocalType)(b_LdTmpBufRam(i) & 0x7f);
    }
    flash_write_DspChar(F_BLOCK4);

}


void  __attribute__((section(".usercode"))) OutNcNoGroupSave(void)
{
    LocalType i,j,selID,real_val;


	selID=CurSelPortIDRead(LadderGroupSub);
	real_val=CurSelOutPortChk(selID);


    i=(LadderGroupSub + GroupBaseAddr);

    GetFlashDataToBufRam(F_BLOCK5);

    if(DigitData){
        b_LdTmpBufRam(i)=(LocalType)(b_LdTmpBufRam(i) | 0x80);
    }
    else{
        b_LdTmpBufRam(i)=(LocalType)(b_LdTmpBufRam(i) & 0x7f);
    }
    flash_write_DspChar(F_BLOCK5);


	selID=CurSelPortIDRead(LadderGroupSub);
	CurSelOutPort(selID,real_val);
}



void  __attribute__((section(".usercode"))) IoGroup(void)
{
    LocalType i;
    
    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=3;
    EditStart=5;
    EditStatus=DIGIT_EDIT;

    DigitMinValue=0;
    if(LadderGroupSub <= 14){
        ShiftCnt=0;
        EditStatus=DIGIT_STRING_EDIT;    

        if(INVERTER_CHECK == IO)      DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
        else                          DigitMaxValue=IO_PORT_MESSAGE_CNT;

        DigitData=cF_FLRDSPCH((unsigned long)i);
        Integer_Digit();
    }
    else if(LadderGroupSub <= 16){               
        ShiftCnt=0;
        EditStatus=DIGIT_STRING_EDIT;                   

        if(INVERTER_CHECK == IO)        DigitMaxValue=ELEV_SPEED_MESSAGE_CNT;
        else                            DigitMaxValue=ELEV_SPEED_MESSAGE_CNT;

        DigitData=cF_FLRDSPCH((unsigned long)i);
        Integer_Digit();
    }
    else if(LadderGroupSub == 20){               
        ShiftCnt=0;
        EditStatus=DIGIT_STRING_EDIT;                   
		DigitMaxValue=AUTO_LANDING_MESSAGE_CNT;

        DigitData=cF_FLRDSPCH((unsigned long)F_AutoLandingMode);
        Integer_Digit();
    }
    else{               
        ShiftCnt=3;
        EditStart=7;
        DigitMaxValue=220;
        DigitData=cF_FLRDSPCH((unsigned long)i);
        Integer_Digit();
    }
}



void  __attribute__((section(".usercode"))) IoGroupSave(void)
{
    LocalType i;

    i=(LadderGroupSub + GroupBaseAddr);

    if(i==16){
        switch(DigitData){
            case    SPEED_30:
                if(cF_SPEED30 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_45:
                if(cF_SPEED45 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_60:
                if(cF_SPEED60 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_90:
                if(cF_SPEED90 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_105:
                if(cF_SPEED105 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_120:
                if(cF_SPEED120 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_150:
                if(cF_SPEED150 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_180:
                if(cF_SPEED180 == 0)    DigitData=SPEED_210;     
                break;
            case    SPEED_210:
                if(cF_SPEED210 == 0)    DigitData=SPEED_210;     
                break;
            default:
                DigitData=SPEED_210;     
                break;
        }
    }
    
    GetFlashDataToBufRam(F_BLOCK2);
    b_LdTmpBufRam(i)=(LocalType)(DigitData);
    flash_write_DspChar(F_BLOCK2);
}





void  __attribute__((section(".usercode"))) DoorGroup(void)
{
    LocalType i;
    
    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=0;
    EditStart=5;
    EditStatus=DIGIT_STRING_EDIT;
    DigitMinValue=0;
	DigitMaxValue=DOOR_SEL_MESSAGE_CNT;

    DigitData=MainSubDoorFlrChk(LadderGroupSub);

    Integer_Digit();
}




LocalType   __attribute__((section(".usercode"))) DoorGroupSave(void)
{
    LocalType i,j,k;

	LocalType block_pt;

	block_pt=(GroupBaseAddr/64);
	block_pt=(block_pt * 64);


	i=0x0;
    k=0x0;

    i=LadderGroupSub/4;
    k=LadderGroupSub%4;

    j=0;

    switch(i){
        case    0:
            j=cF_SUBDOORFLR1;
            break;
        case    1:
            j=cF_SUBDOORFLR2;
            break;
        case    2:
            j=cF_SUBDOORFLR3;
            break;
        case    3:        
            j=cF_SUBDOORFLR4;
            break;
        case    4:
            j=cF_SUBDOORFLR5;
            break;
        case    5:
            j=cF_SUBDOORFLR6;
            break;
        case    6:
            j=cF_SUBDOORFLR7;
            break;
        case    7:        
            j=cF_SUBDOORFLR8;
            break;
        case    8:
            j=cF_SUBDOORFLR9;
            break;
        case    9:
            j=cF_SUBDOORFLR10;
            break;
        case    10:
            j=cF_SUBDOORFLR11;
            break;
        case    11:        
            j=cF_SUBDOORFLR12;
            break;
        case    12:
            j=cF_SUBDOORFLR13;
            break;
        case    13:
            j=cF_SUBDOORFLR14;
            break;
        case    14:
            j=cF_SUBDOORFLR15;
            break;
        case    15:        
            j=cF_SUBDOORFLR16;
            break;
		default:
			return(0);
    }

    switch(k){
        case    0:
            j=(j & 0xfc);
            break;
        case    1:
            j=(j & 0xf3);
			DigitData=(DigitData << 2); 
            break;
        case    2:
            j=(j & 0xcf);
			DigitData=(DigitData << 4); 
            break;
        case    3:        
            j=(j & 0x3f);
			DigitData=(DigitData << 6); 
            break;
    }
	DigitData=(DigitData | j);
	    
	k=(LadderGroupSub/4);
    i=(k + GroupBaseAddr);

    GetFlashDataToBufRam(block_pt);
    b_LdTmpBufRam(i)=(LocalType)(DigitData);
    flash_write_DspChar(block_pt);

	return(0);
}





void  __attribute__((section(".usercode"))) UserGroupSave(void)
{
    LocalType i,j,k,l;
	LocalType block_pt,tmp_new_law,tmp_new_spd,tmp_old_spd;

    GetFlashDataToBufRam(F_BLOCK2);

    switch(LadderGroupSub){
        case    VERSION:
        case    TOTAL_USE_TIME:
            break;
        case    BOARD_ID:
            if((DigitData==0) || (DigitData==3)|| (DigitData==6) ){
                b_LdTmpBufRam(F_ManualSpeed)    = P1_SPD;      
                b_LdTmpBufRam(F_DecreaseSpeed)  = P1P2_SPD;     
                b_LdTmpBufRam(F_FhmSpeed)       = P4_SPD;                     
                b_LdTmpBufRam(F_Speed60)        = P3_SPD;     
                b_LdTmpBufRam(F_ElevSpeed)      = SPEED_60;                                    
            }

            if(DigitData==0){
                DigitData=(LG | MAN_USE);
            }
            else if(DigitData==1){
                DigitData=(IO | MAN_USE);
            }
            else if(DigitData==2){
                DigitData=(D_F | MAN_USE);
            }
            else if(DigitData==3){
                DigitData=(LG | BAGGAGE_USE);
            }
            else if(DigitData==4){
                DigitData=(IO | BAGGAGE_USE);
            }
            else if(DigitData==5){
                DigitData=(D_F | BAGGAGE_USE);
            }
            else if(DigitData==6){
                DigitData=(LG | CARLIFT_USE);
            }
            else if(DigitData==7){
                DigitData=(IO | CARLIFT_USE);
            }
            else if(DigitData==8){
                DigitData=(D_F | CARLIFT_USE);
            }

            i=F_Bd_Id;
            b_LdTmpBufRam(i)=(LocalType)(DigitData);

            flash_write_DspChar(F_BLOCK2);                        
            break;
        case    ALL_MENU_CHK:
            break;
        case    ENGINEER_NM:
             if(   ('1'== New485Ladder[SECONDLINE_BASE+EditStart+0]) 
                && ('2'== New485Ladder[SECONDLINE_BASE+EditStart+1]) 
                && ('3'== New485Ladder[SECONDLINE_BASE+EditStart+2]) 
                && ('4'== New485Ladder[SECONDLINE_BASE+EditStart+3])){

                 LadderGroup=0;
                 LadderGroupSub=0;
            } 
            break;
        case    PASSWARD:
            break;
        case    SERIAL_NM:
            i=F_SerialNm10;
            i_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    USER_LAMP1:
        case    USER_LAMP2:
        case    USER_LAMP3:
        case    USER_LAMP4:
        case    GROUP_NUMBER:
        case    LOCAL_NUMBER:
			if(LadderGroupSub == USER_LAMP1)		i=F_UserLamp1;
			else if(LadderGroupSub == USER_LAMP2)	i=F_UserLamp2;
			else if(LadderGroupSub == USER_LAMP3)	i=F_UserLamp3;
			else if(LadderGroupSub == USER_LAMP4)	i=F_UserLamp4;
			else if(LadderGroupSub == LOCAL_NUMBER)	i=F_LocalNm;
			else									i=F_GroupNm;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    LG_INV_IN_BD:
            i=F_PcbType;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    ERR_ST_CNT:
            i=F_ErrStopCnt;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    SYSTEM_SET:
			if(New_Law_SystemChk())	tmp_new_law=1;
			else					tmp_new_law=0;

			if(New_Spd_SystemChk())	tmp_new_spd=1;
			else					tmp_new_spd=0;

			if(Old_Spd_SystemChk())	tmp_old_spd=1;
			else					tmp_old_spd=0;


            i=F_SystemSet;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);


			//////////////////////////BLOCK1//////////////////////////
			if( (New_Law_SystemChk()) && (tmp_new_law==0)){
    			GetFlashDataToBufRam(F_BLOCK1);
		        bit_LdTmpBufRamSet(F_OnOff0,bDoorJumperOff    		% 8); 
		        bit_LdTmpBufRamSet(F_OnOff1,bBrkMgtUse        		% 8);
		        bit_LdTmpBufRamSet(F_OnOff2,bBrkOpenUse       		% 8);
            	flash_write_DspChar(F_BLOCK1);				
			}
			//////////////////////////BLOCK1//////////////////////////

			if( (New_Spd_SystemChk()) && (tmp_new_spd==0)){
    			GetFlashDataToBufRam(F_BLOCK2);
		        b_LdTmpBufRam(F_ManualSpeed)    = P3_SPD;                   
		        b_LdTmpBufRam(F_BatterySpeed)   = NONE_USE_SPD;      
		        b_LdTmpBufRam(F_DecreaseSpeed)  = P1P2_SPD;                    
		        b_LdTmpBufRam(F_FhmSpeed)       = NONE_USE_SPD;     
		        b_LdTmpBufRam(F_Speed1)        	= P1P3_SPD;     
		        b_LdTmpBufRam(F_Speed2)        	= P2P3_SPD;              
		        b_LdTmpBufRam(F_Speed3)        	= P1P2P3_SPD;                    
		        b_LdTmpBufRam(F_LULD_MPM_SPD3)  = 0;     
		        b_LdTmpBufRam(F_SU2SD2_V_SPD3)	= 0;    
		        b_LdTmpBufRam(F_X0X1_V_SPD3)  	= 0;   
            	flash_write_DspChar(F_BLOCK2);

		        DefaultDecreaseLength_spd3();
		        CaluDecreasePulse();
			}
			else if( (Old_Spd_SystemChk()) && (tmp_old_spd==0)){
    			GetFlashDataToBufRam(F_BLOCK2);
		        b_LdTmpBufRam(F_ManualSpeed)    = P3_SPD;          
		        b_LdTmpBufRam(F_BatterySpeed)   = NONE_USE_SPD;      
		        b_LdTmpBufRam(F_DecreaseSpeed)  = P1P2_SPD;                    
		        b_LdTmpBufRam(F_FhmSpeed)       = NONE_USE_SPD;     
		        b_LdTmpBufRam(F_Etc1Speed)      = NONE_USE_SPD;     
		        b_LdTmpBufRam(F_Etc2Speed)      = NONE_USE_SPD;     
		        b_LdTmpBufRam(F_Speed30)        = NONE_USE_SPD;     
		        b_LdTmpBufRam(F_Speed45)        = NONE_USE_SPD;              
		        b_LdTmpBufRam(F_Speed60)        = NONE_USE_SPD;                    
		        b_LdTmpBufRam(F_Speed90)        = NONE_USE_SPD;     
		        b_LdTmpBufRam(F_Speed105)       = NONE_USE_SPD;     
		        b_LdTmpBufRam(F_Speed120)       = NONE_USE_SPD;     
		        b_LdTmpBufRam(F_Speed150)       = NONE_USE_SPD;     
		        b_LdTmpBufRam(F_Speed180)       = NONE_USE_SPD;     
		        b_LdTmpBufRam(F_Speed210)       = NONE_USE_SPD;    
		        b_LdTmpBufRam(F_ElevSpeed)      = SPEED_60;
		        b_LdTmpBufRam(F_LimitSpeed)     = SPEED_210;
		        b_LdTmpBufRam(F_Su1Sd1_Velocity)= 90;      //mpm
		        b_LdTmpBufRam(F_Su2Sd2_Velocity)= 90;      //mpm
		        b_LdTmpBufRam(F_X0X1_Velocity)  = 210;     //mpm
				
				if(GET_LONG(MPM) == 30){
					b_LdTmpBufRam(F_Speed30)        = P1P2P3_SPD;

		        	b_LdTmpBufRam(F_ElevSpeed)      = SPEED_30;
				}
				else if(GET_LONG(MPM) == 45){
					b_LdTmpBufRam(F_Speed45)        = P1P2P3_SPD;
					b_LdTmpBufRam(F_Speed30)        = P2P3_SPD;

		        	b_LdTmpBufRam(F_ElevSpeed)      = SPEED_45;
				}      
				else if(GET_LONG(MPM) == 60){
					b_LdTmpBufRam(F_Speed60)        = P1P2P3_SPD;
					b_LdTmpBufRam(F_Speed45)        = P2P3_SPD;
					b_LdTmpBufRam(F_Speed30)        = P1P3_SPD;

		        	b_LdTmpBufRam(F_ElevSpeed)      = SPEED_60;
				}      
				else if(GET_LONG(MPM) == 90){
					b_LdTmpBufRam(F_Speed90)        = P1P2P3_SPD;
					b_LdTmpBufRam(F_Speed60)        = P2P3_SPD;
					b_LdTmpBufRam(F_Speed45)        = P1P3_SPD;

		        	b_LdTmpBufRam(F_ElevSpeed)      = SPEED_90;
				}      
				else if(GET_LONG(MPM) == 105){
					b_LdTmpBufRam(F_Speed105)       = P1P2P3_SPD;
					b_LdTmpBufRam(F_Speed60)        = P2P3_SPD;
					b_LdTmpBufRam(F_Speed45)        = P1P3_SPD;

		        	b_LdTmpBufRam(F_ElevSpeed)      = SPEED_105;
				}      
				else if(GET_LONG(MPM) == 120){
					b_LdTmpBufRam(F_Speed120)       = P1P2P3_SPD;
					b_LdTmpBufRam(F_Speed60)        = P2P3_SPD;
					b_LdTmpBufRam(F_Speed45)        = P1P3_SPD;

		        	b_LdTmpBufRam(F_ElevSpeed)      = SPEED_120;
				}      
				else if(GET_LONG(MPM) == 150){
					b_LdTmpBufRam(F_Speed150)       = P1P2P3_SPD;
					b_LdTmpBufRam(F_Speed60)        = P2P3_SPD;
					b_LdTmpBufRam(F_Speed45)        = P1P3_SPD;

		        	b_LdTmpBufRam(F_ElevSpeed)      = SPEED_150;
				}      
				else if(GET_LONG(MPM) == 180){
					b_LdTmpBufRam(F_Speed180)       = P1P2P3_SPD;
					b_LdTmpBufRam(F_Speed60)        = P2P3_SPD;
					b_LdTmpBufRam(F_Speed45)        = P1P3_SPD;

		        	b_LdTmpBufRam(F_ElevSpeed)      = SPEED_180;
				}      


				flash_write_DspChar(F_BLOCK2);


		        DefaultDecreaseLength_old();
		        CaluDecreasePulse();
			}
	
            break;
        case    NORMAL_DSP:
            i=F_NormalDsp;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    COMPANY_NAME:
            i=F_Company;
            b_LdTmpBufRam((unsigned long)i)=(LocalType)(New485Ladder[SECONDLINE_BASE+EditStart+0]);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    VIRTUAL_CALL:
			i=New485Ladder[SECONDLINE_BASE+EditStart+0];
			i=((i - '0') * 100);
			j=New485Ladder[SECONDLINE_BASE+EditStart+1];
			j=((j-'0') * 10);
			k=New485Ladder[SECONDLINE_BASE+EditStart+2];
			k=(k -'0');

			i = (i + j + k);
			if(i <= 254)	sRamDArry[mVFlrCnt]=i;	


//////////////////////////////////////////////////////////
			i=New485Ladder[SECONDLINE_BASE+EditStart+4];
			i=((i - '0') * 10);
			j=New485Ladder[SECONDLINE_BASE+EditStart+5];
			j=(j-'0');
			i=(i+j);

			if(i <= (cF_TOPFLR+1))	sRamDArry[mVFlr1]=i;	
			else					sRamDArry[mVFlr1]=0;	
			i=New485Ladder[SECONDLINE_BASE+EditStart+7];
			i=((i - '0') * 10);
			j=New485Ladder[SECONDLINE_BASE+EditStart+8];
			j=(j-'0');
			i=(i+j);

			if(i <= (cF_TOPFLR+1))	sRamDArry[mVFlr2]=i;	
			else					sRamDArry[mVFlr2]=0;	
            break;
        case    HH_MM_SS:
                DigitData=(New485Ladder[SECONDLINE_BASE+EditStart+0]-'0') << 4;
                sRamDArry[Hour]=DigitData  | (New485Ladder[SECONDLINE_BASE+EditStart+1]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditStart+3]-'0') << 4;
                sRamDArry[Minuate]=DigitData | (New485Ladder[SECONDLINE_BASE+EditStart+4]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditStart+6]-'0') << 4;
                sRamDArry[sec]=DigitData | (New485Ladder[SECONDLINE_BASE+EditStart+7]-'0');
    
                Initialize_DS1302();
            break;
        case    YY_MM_DD:
                DigitData=(New485Ladder[SECONDLINE_BASE+EditStart+0]-'0') << 4;
                sRamDArry[Year]=DigitData | (New485Ladder[SECONDLINE_BASE+EditStart+1]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditStart+3]-'0') << 4;
                sRamDArry[Month]=DigitData | (New485Ladder[SECONDLINE_BASE+EditStart+4]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditStart+6]-'0') << 4;
                sRamDArry[Day]=DigitData | (New485Ladder[SECONDLINE_BASE+EditStart+7]-'0');
    
                Initialize_DS1302();
            break;
        case    OUT_DATE:
                DigitData=(New485Ladder[SECONDLINE_BASE+EditStart+0]-'0') << 4;
                b_LdTmpBufRam(F_year)=DigitData | (New485Ladder[SECONDLINE_BASE+EditStart+1]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditStart+3]-'0') << 4;
                b_LdTmpBufRam(F_month)=DigitData | (New485Ladder[SECONDLINE_BASE+EditStart+4]-'0');
    
                DigitData=(New485Ladder[SECONDLINE_BASE+EditStart+6]-'0') << 4;
                b_LdTmpBufRam(F_day)=DigitData | (New485Ladder[SECONDLINE_BASE+EditStart+7]-'0');

	            flash_write_DspChar(F_BLOCK2);
            break;
        case    DRIVE_METHOD:
			block_pt=(F_NonService0/64);
			block_pt=(block_pt * 64);

            GetFlashDataToBufRam(block_pt);
            i=F_NonService0;

            if(DigitData==1)		DigitData=0x55;  //Â¦¼ö
            else if(DigitData==2)	DigitData=0xaa;	 //È¦¼ö	
            else if(DigitData==0)	DigitData=0xff;  //ÀüÃþ 
			
            b_LdTmpBufRam((unsigned long)(i+0))=(LocalType)(DigitData);
            b_LdTmpBufRam((unsigned long)(i+1))=(LocalType)(DigitData);
            b_LdTmpBufRam((unsigned long)(i+2))=(LocalType)(DigitData);
            b_LdTmpBufRam((unsigned long)(i+3))=(LocalType)(DigitData);        
            b_LdTmpBufRam((unsigned long)(i+4))=(LocalType)(DigitData);
            b_LdTmpBufRam((unsigned long)(i+5))=(LocalType)(DigitData);
            b_LdTmpBufRam((unsigned long)(i+6))=(LocalType)(DigitData);
            b_LdTmpBufRam((unsigned long)(i+7))=(LocalType)(DigitData);        
        
            flash_write_DspChar(block_pt);

			ShadowsRamDArry[FLR_ON_OFF0]=cF_NONSERVICE0;
			ShadowsRamDArry[FLR_ON_OFF1]=cF_NONSERVICE1;
			ShadowsRamDArry[FLR_ON_OFF2]=cF_NONSERVICE2;
			ShadowsRamDArry[FLR_ON_OFF3]=cF_NONSERVICE3;
			ShadowsRamDArry[FLR_ON_OFF4]=cF_NONSERVICE4;
			ShadowsRamDArry[FLR_ON_OFF5]=cF_NONSERVICE5;
			ShadowsRamDArry[FLR_ON_OFF6]=cF_NONSERVICE6;
			ShadowsRamDArry[FLR_ON_OFF7]=cF_NONSERVICE7;
            break;
        case    FHM_RUN_CHK:
            if(DigitData==1){
				sRamDArry[FHM_SEQ]=FHM_SEQ_0;
				LadderKey = 0xff;
			}
			else		sRamDArry[FHM_SEQ]=FHM_SEQ_8;

            LadderGroup=0;
            LadderGroupSub=0;
            break;
        case    INIT_DATA:
            switch(DigitData){
                case    1:
					bSaveFlash=1;
					MoveCounterx=0;
                    break;
                case    2:
					if(!bMoveCar){
						for(i=0;i<E_END;i++){
							eDArry[i]=0;
						}
						sRamDArry[mBefErrCntPt]=0xff;
						bSaveFlash=1;
					}
                    break;
                case    3:
					bExportData=1;
					SrcAdrBlk=0;
					LoaderChk=0;
                    break;
                case    4:
					bImportData=1;
					SrcAdrBlk=0;
					LoaderChk=0;
                    break;
            }
            break;
        case    ENCODER_RATE:
            i=F_StopPulse0;
            i_LdTmpBufRam((unsigned long)i)=(LocalType)(DigitData);
            flash_write_DspChar(F_BLOCK2);
            break;
        case    HALL_IND_SET:
			break;
        default:
            break;

    }
}





void  __attribute__((section(".usercode"))) ELGroup(void)
{
	unsigned long	tmpPlulsex;

    switch(LadderGroupSub){
        case    SUBNM_ENCODER_PULSE:
		    Cursor=0;
		    ShiftCnt=5;
		    EditStart=5;
		    EditStatus=DIGIT_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
		    DigitData=(unsigned int)(GET_LONG((unsigned long)ENCODER_PULSE));    
		    Integer_Digit();
            break;
        case    SUBNM_TM_MPM:
		    Cursor=0;
		    ShiftCnt=3;
		    EditStart=5;
		    EditStatus=DIGIT_EDIT;		
		    DigitMaxValue=211;
		    DigitMinValue=0;
		    DigitData=(unsigned int)(GET_LONG((unsigned long)MPM));    
		    Integer_Digit();
            break;
        case    SUBNM_MOTOR_RPM:
		    Cursor=0;
		    ShiftCnt=5;
		    EditStart=5;
		    EditStatus=DIGIT_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
		    DigitData=(unsigned int)(GET_LONG((unsigned long)RPM));    
		    Integer_Digit();
            break;

        case    SUBNM_MANUAL_PORT:
	    	Cursor=0;
	        ShiftCnt=0;
	    	EditStart=5;
	        EditStatus=DIGIT_STRING_EDIT;   
	    	DigitMinValue=0;
			DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
	        DigitData=cF_FLRDSPCH((unsigned long)F_ManualSpeed);
	        Integer_Digit();
            break;
        case    SUBNM_BATTERY_PORT:
	    	Cursor=0;
	        ShiftCnt=0;
	    	EditStart=5;
	        EditStatus=DIGIT_STRING_EDIT;   
	    	DigitMinValue=0;
			DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
	        DigitData=cF_FLRDSPCH((unsigned long)F_BatterySpeed);
	        Integer_Digit();
            break;
        case    SUBNM_DEC_PORT:
	    	Cursor=0;
	        ShiftCnt=0;
	    	EditStart=5;
	        EditStatus=DIGIT_STRING_EDIT;   
	    	DigitMinValue=0;
			DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
	        DigitData=cF_FLRDSPCH((unsigned long)F_DecreaseSpeed);
	        Integer_Digit();
            break;
        case    SUBNM_FHM_PORT:
	    	Cursor=0;
	        ShiftCnt=0;
	    	EditStart=5;
	        EditStatus=DIGIT_STRING_EDIT;   
	    	DigitMinValue=0;
			DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
	        DigitData=cF_FLRDSPCH((unsigned long)F_FhmSpeed);
	        Integer_Digit();
            break;
        case    SUBNM_LOW_SPD_PORT:
	    	Cursor=0;
	        ShiftCnt=0;
	    	EditStart=5;
	        EditStatus=DIGIT_STRING_EDIT;   
	    	DigitMinValue=0;
			DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
	        DigitData=cF_FLRDSPCH((unsigned long)F_Speed1);
	        Integer_Digit();
            break;
        case    SUBNM_MID_SPD_PORT:
	    	Cursor=0;
	        ShiftCnt=0;
	    	EditStart=5;
	        EditStatus=DIGIT_STRING_EDIT;   
	    	DigitMinValue=0;
			DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
	        DigitData=cF_FLRDSPCH((unsigned long)F_Speed2);
	        Integer_Digit();
            break;
        case    SUBNM_HIGH_SPD_PORT:
	    	Cursor=0;
	        ShiftCnt=0;
	    	EditStart=5;
	        EditStatus=DIGIT_STRING_EDIT;   
	    	DigitMinValue=0;
			DigitMaxValue=IO_PORT_MESSAGE_CNT-1;
	        DigitData=cF_FLRDSPCH((unsigned long)F_Speed3);
	        Integer_Digit();
            break;
        case    SUBNM_LOW_SPD_DEC_LENTH:
		    Cursor=0;
		    ShiftCnt=5;
		    EditStart=5;
		    EditStatus=DIGIT_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
		    DigitData=(unsigned int)(GET_LONG((unsigned long)DEC_LENGTH_SPD_LOW));    
		    Integer_Digit();
            break;
        case    SUBNM_MID_SPD_DEC_LENTH:
		    Cursor=0;
		    ShiftCnt=5;
		    EditStart=5;
		    EditStatus=DIGIT_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
		    DigitData=(unsigned int)(GET_LONG((unsigned long)DEC_LENGTH_SPD_MID));    
		    Integer_Digit();
            break;
        case    SUBNM_HIGH_SPD_DEC_LENTH:
		    Cursor=0;
		    ShiftCnt=5;
		    EditStart=5;
		    EditStatus=DIGIT_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
		    DigitData=(unsigned int)(GET_LONG((unsigned long)DEC_LENGTH_SPD_HIGH));    
		    Integer_Digit();
            break;
        case    SUBNM_BASE_DEC_LENTH:
		    Cursor=0;
		    ShiftCnt=5;
		    EditStart=5;
		    EditStatus=DIGIT_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
		    DigitData=(unsigned int)(GET_LONG((unsigned long)BASE_DEC_LENGTH));    
		    Integer_Digit();
            break;
        case    SUBNM_BASE_DEC_TIME:
		    Cursor=0;
		    ShiftCnt=5;
		    EditStart=5;
		    EditStatus=DIGIT_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
		    DigitData=(unsigned int)(GET_LONG((unsigned long)BASE_DEC_TIME));    
		    Integer_Digit();
            break;
        case    SUBNM_BASE_SCURVE_TIME:
		    Cursor=0;
		    ShiftCnt=5;
		    EditStart=5;
		    EditStatus=DIGIT_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
		    DigitData=(unsigned int)(GET_LONG((unsigned long)BASE_SCURVE_TIME));    
		    Integer_Digit();
            break;
        case    SUBNM_SU2SD2_SPD:
	    	Cursor=0;
	        ShiftCnt=0;
	    	EditStart=5;
	        EditStatus=DIGIT_STRING_EDIT;   
	    	DigitMinValue=0;
			DigitMaxValue=ELEV_SPEED_MESSAGE_CNT_SPD3;
	        DigitData=cF_FLRDSPCH((unsigned long)F_Su2Sd2_Velocity);
	        Integer_Digit();
            break;
        case    SUBNM_X0X1_SPD:
	    	Cursor=0;
	        ShiftCnt=0;
	    	EditStart=5;
	        EditStatus=DIGIT_STRING_EDIT;   
	    	DigitMinValue=0;
			DigitMaxValue=ELEV_SPEED_MESSAGE_CNT_SPD3;
	        DigitData=cF_FLRDSPCH((unsigned long)F_X0X1_Velocity);
	        Integer_Digit();
            break;
        case    SUBNM_LULD_MPM:
		    Cursor=0;
		    ShiftCnt=3;
		    EditStart=5;
		    EditStatus=DIGIT_EDIT;		
		    DigitMaxValue=255;
		    DigitMinValue=0;
	        DigitData=cF_FLRDSPCH((unsigned long)F_LULD_MPM_SPD3);
		    Integer_Digit();
            break;
        case    SUBNM_AUTO_LANDING:
            Cursor=0;
            ShiftCnt=0;
            EditStart=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=AUTO_LANDING_MESSAGE_CNT;
            DigitMinValue=0;
	        DigitData=cF_FLRDSPCH((unsigned long)F_AutoLandingMode);
            Integer_Digit();
			break;				
        case    SUBNM_AUTO_TUN:
            DigitMaxValue=2;

            Cursor=0;
            ShiftCnt=0;
            EditStart=3;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMinValue=0;			
			DigitData=0;
			AutotunUpDn=0;
			sRamDArry[AUTO_TUNING]=AUTOTUN_SEQ_0;
            Integer_Digit();
			break;
        case    SUBNM_FHM:
            Cursor=0;
            ShiftCnt=0;
            EditStart=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=2;
            DigitMinValue=0;
			DigitData=0;	
            Integer_Digit();
			break;		
        case    SUBNM_LOW_SPD_PULSE:
		    Cursor=0;
		    ShiftCnt=0;
		    EditStart=3;
		    EditStatus=NO_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
    		tmpPlulsex=(GET_LONG((unsigned long)DEC_PULSE_SPD_LOW));    
			CurEncoderPulse(tmpPlulsex);
            break;
        case    SUBNM_MID_SPD_PULSE:
		    Cursor=0;
		    ShiftCnt=0;
		    EditStart=3;
		    EditStatus=NO_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
    		tmpPlulsex=(GET_LONG((unsigned long)DEC_PULSE_SPD_MID));    
			CurEncoderPulse(tmpPlulsex);
            break;
        case    SUBNM_HIGH_SPD_PULSE:
		    Cursor=0;
		    ShiftCnt=0;
		    EditStart=3;
		    EditStatus=NO_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
    		tmpPlulsex=(GET_LONG((unsigned long)DEC_PULSE_SPD_HIGH));    
			CurEncoderPulse(tmpPlulsex);
            break;
        case    SUBNM_BASE_PULSE:
		    Cursor=0;
		    ShiftCnt=0;
		    EditStart=3;
		    EditStatus=NO_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;

			if(DaesungAutoLandingModeChk((unsigned char)DS_AUTOLANDING)==1){		
	    		tmpPlulsex=(GET_LONG((unsigned long)BASE_DEC_PULSE));    
			}
			else{
	    		tmpPlulsex=BaseDecPulseX;    
			}

			CurEncoderPulse(tmpPlulsex);
            break;
        case    SUBNM_MPM_VARIABLE:
		    Cursor=0;
		    ShiftCnt=5;
		    EditStart=5;
		    EditStatus=NO_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
		    DigitData=(unsigned int)(GET_LONG((unsigned long)MPM_VARIABLE));    
		    Integer_Digit();
            break;
        case    SUBNM_MM_PER_PULSE:
		    Cursor=0;
		    ShiftCnt=5;
		    EditStart=5;
		    EditStatus=NO_EDIT;		
		    DigitMaxValue=0xffff;
		    DigitMinValue=0;
		    DigitData=(unsigned int)(GET_LONG((unsigned long)MM_PULSE));    
		    Integer_Digit();
            break;
        default:
            break;
    }
}



void  __attribute__((section(".usercode"))) ELGroupSave(void)
{

    LocalType  i,j,k;

	i=0xff;
	j=0xff;

    switch(LadderGroupSub){
        case    SUBNM_ENCODER_PULSE:
			j=( (ENCODER_PULSE) % (ENCODER_PULSE));
			break;
        case    SUBNM_TM_MPM:
			j=( (MPM) % (ENCODER_PULSE));
			break;
        case    SUBNM_MOTOR_RPM:
			j=( (RPM) % (ENCODER_PULSE));
			break;
        case    SUBNM_LOW_SPD_DEC_LENTH:
			j=( (DEC_LENGTH_SPD_LOW) % (ENCODER_PULSE) );
			break;
        case    SUBNM_MID_SPD_DEC_LENTH:
			j=( (DEC_LENGTH_SPD_MID) % (ENCODER_PULSE));
			break;
        case    SUBNM_HIGH_SPD_DEC_LENTH:
			j=( (DEC_LENGTH_SPD_HIGH) % (ENCODER_PULSE));
			break;
        case    SUBNM_BASE_DEC_LENTH:
			j=( (BASE_DEC_LENGTH) % (ENCODER_PULSE));
			break;
        case    SUBNM_BASE_DEC_TIME:
			j=( (BASE_DEC_TIME) % (ENCODER_PULSE));
			break;
        case    SUBNM_BASE_SCURVE_TIME:
			j=( (BASE_SCURVE_TIME) % (ENCODER_PULSE));
			break;
//////////////////////////////////////////////
        case    SUBNM_MANUAL_PORT:
			i=( (F_ManualSpeed) % (F_BLOCK2));
			break;
        case    SUBNM_BATTERY_PORT:
			i=((F_BatterySpeed) % (F_BLOCK2));
			break;
        case    SUBNM_DEC_PORT:
			i=( (F_DecreaseSpeed) % (F_BLOCK2));
			break;
        case    SUBNM_FHM_PORT:
			i=( (F_FhmSpeed) % (F_BLOCK2));
			break;

        case    SUBNM_LOW_SPD_PORT:
			i=( (F_Speed1) % (F_BLOCK2));
			break;
        case    SUBNM_MID_SPD_PORT:
			i=( (F_Speed2) % (F_BLOCK2));
			break;
        case    SUBNM_HIGH_SPD_PORT:
			i=( (F_Speed3) % (F_BLOCK2));
			break;
        case    SUBNM_SU2SD2_SPD:
			i=( (F_Su2Sd2_Velocity) % (F_BLOCK2));
			break;
        case    SUBNM_X0X1_SPD:
			i=( (F_X0X1_Velocity) % (F_BLOCK2));
			break;
        case    SUBNM_LULD_MPM:
			i=((F_LULD_MPM_SPD3) % (F_BLOCK2));
			break;
        case    SUBNM_AUTO_LANDING:
			i=((F_AutoLandingMode) % (F_BLOCK2));
			break;

////////////////////////////////
        case    SUBNM_AUTO_TUN:
            if((sRamDArry[AUTO_TUNING] == AUTOTUN_SEQ_0) && (DigitData > 0)){
                sRamDArry[AUTO_TUNING] = AUTOTUN_SEQ_1;
				AutotunUpDn=DigitData;
                LadderKey=0xff;
            }
            else{
				sRamDArry[AUTO_TUNING] = AUTOTUN_SEQ_0;
				AutotunUpDn=0;
            }

            LadderGroup=0;
            LadderGroupSub=0;
            break;
        case    SUBNM_FHM:
            if(DigitData==1){
				sRamDArry[FHM_SEQ]=FHM_SEQ_0;
				LadderKey = 0xff;
			}
			else				sRamDArry[FHM_SEQ]=FHM_SEQ_8;
            LadderGroup=0;
            LadderGroupSub=0;
            break;
/////////////////////////////////////
		default:
			break;
	}


	if(j != 0xff){
		for(k=0;k<16;k++){
			parameter_mirror[k]=FlashDspCharBuf[ENCODER_PULSE+k].long_data;  
		}
		l_LdTmpBufRam(j)=(unsigned long)DigitData;		
		flash_write(ENCODER_PULSE);
		CaluDecreasePulse();
	}


	if(i != 0xff){
	    GetFlashDataToBufRam(F_BLOCK2);
	    b_LdTmpBufRam(i)=(LocalType)(DigitData);
	    flash_write_DspChar(F_BLOCK2);
	}
        
}




void  __attribute__((section(".usercode"))) ParameterGroup(void)
{
	unsigned long tmpPlulsex;

    LocalType i;
    
    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=5;
    EditStart=5;
    EditStatus=DIGIT_EDIT;

    DigitMaxValue=0xffff;
    DigitMinValue=0;

    DigitData=(unsigned int)(GET_LONG((unsigned long)i));    
    tmpPlulsex=(GET_LONG((unsigned long)i));    

    if(LadderGroupSub==P_TM_MPM){
        DigitMaxValue=211;
        ShiftCnt=3;
    }
    
    Integer_Digit();

	if(LadderGroupSub >= P_MINDEC30){
		EditStatus=NO_EDIT;
		if(LadderGroupSub < P_PAR1){ 
	    	EditStart=3;
			CurEncoderPulse(tmpPlulsex);
		}
	}
}


void  __attribute__((section(".usercode"))) ParameterGroupSave(void)
{
    LocalType  i;

    for(i=0;i<16;i++){
        parameter_mirror[i]=FlashDspCharBuf[ENCODER_PULSE+i].long_data;  
    }

    l_LdTmpBufRam(LadderGroupSub)=(unsigned long)DigitData;

    flash_write(ENCODER_PULSE);

}




void  __attribute__((section(".usercode"))) InportGroup(void)
{
    
    LocalType i;

    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=2;
    EditStart=4;
    EditStatus=DIGIT_STRING_EDIT;

    DigitMaxValue=NO_USE_IN+1;
    DigitMinValue=0;

    DigitData=cF_FLRDSPCH((unsigned long)i);

    if(DigitData & 0x80)    OrgNcNo=0x80;  //
    else                    OrgNcNo=0x00;  //

    DigitData=(DigitData & 0x7f);

    Integer_Digit();    
}





void  __attribute__((section(".usercode"))) InportSave(void)
{
    LocalType i,j,k,ChangeDisable;

    i=(LadderGroupSub + GroupBaseAddr);
    GetFlashDataToBufRam(F_BLOCK4);

    ChangeDisable=0;
    for(k=0;k <(DigitMaxValue-1);k++){
        j=b_LdTmpBufRam(k); //
        j=(j & 0x7f);       //
        if(j == DigitData)  ChangeDisable=1;
    }
    
    if((ChangeDisable==0) || (DigitData == NO_USE_IN) ){    
        if(DigitData == NO_USE_IN) DigitData=(DigitData | 0x80);       //
        else                        DigitData=(DigitData | OrgNcNo);    //

        b_LdTmpBufRam(i)=(LocalType)(DigitData);
        flash_write_DspChar(F_BLOCK4);
    }
}


void  __attribute__((section(".usercode"))) OutportGroup(void)
{
    LocalType i;
    
    i=(LadderGroupSub + GroupBaseAddr);

    Cursor=0;
    ShiftCnt=2;
    EditStart=4;
    EditStatus=DIGIT_STRING_EDIT;
    DigitMinValue=0;
    DigitMaxValue= (NO_USE_OUT+1);

    DigitData=cF_FLRDSPCH((unsigned long)i);

    if(DigitData & 0x80)    OrgNcNo=0x80;  //
    else                    OrgNcNo=0x00;  //
    DigitData=(DigitData & 0x7f);

    Integer_Digit();    
}




void  __attribute__((section(".usercode"))) OutportSave(void)
{
    LocalType i,j,k,ChangeDisable;

    i=(LadderGroupSub + GroupBaseAddr);
    GetFlashDataToBufRam(F_BLOCK5);
    
    ChangeDisable=0;


    for(k=0;k < SILK_EXT_Y0;k++){
        j=b_LdTmpBufRam(k); //
        j=(j & 0x7f);       //
        if(j == DigitData){
  			ChangeDisable=1;
		}
    }
    
    if((ChangeDisable==0) || (DigitData == NO_USE_OUT) ){
        if(DigitData == NO_USE_OUT) DigitData=(DigitData | 0x80);       //
        else                        DigitData=(DigitData | OrgNcNo);    //

        b_LdTmpBufRam(i)=(LocalType)(DigitData);
        flash_write_DspChar(F_BLOCK5);
    }


}






void  __attribute__((section(".usercode"))) ErrorGroup(LocalType offset)
{
    LocalType i,j;

    EditStatus=NO_EDIT;

    offset=offset * ERR_SAVE_WIDE;

    New485Ladder[2]  ='E';          
    New485Ladder[3]  ='R';
    New485Ladder[4]  =':';


    if(eDArry[eSysErCnt + offset + 0] > 0){
        New485Ladder[5]  =(eDArry[eSysErCnt + offset + 0] >> 4  ) + '0';  //month          
        New485Ladder[6]  =(eDArry[eSysErCnt + offset + 0] & 0x0f) + '0';
        New485Ladder[7]  =(eDArry[eSysErCnt + offset + 1] >> 4  ) + '0';  //date          
        New485Ladder[8]  =(eDArry[eSysErCnt + offset + 1] & 0x0f) + '0';
        New485Ladder[9] ='/';          
        New485Ladder[10] =(eDArry[eSysErCnt + offset + 4] >> 4  ) + '0';  //hour         
        New485Ladder[11] =(eDArry[eSysErCnt + offset + 4] & 0x0f) + '0';
        New485Ladder[12] =(eDArry[eSysErCnt + offset + 5] >> 4  ) + '0';  //min         
        New485Ladder[13] =(eDArry[eSysErCnt + offset + 5] & 0x0f) + '0';
        New485Ladder[14] ='/';          



		i=eDArry[eSysErCnt + offset + 2];
		i=(i*2);

		New485Ladder[15]=cF_FLRDSPCH((unsigned long)(i+0));  
    	New485Ladder[16]=cF_FLRDSPCH((unsigned long)(i+1));          

        New485Ladder[17] ='F';

        New485Ladder[SECONDLINE_BASE+0]='E';
        New485Ladder[SECONDLINE_BASE+1]=(LadderGroupSub / 10)+ '0';
        New485Ladder[SECONDLINE_BASE+2]=(LadderGroupSub % 10)+ '0';
        New485Ladder[SECONDLINE_BASE+3]=':';
    
        j=eDArry[eSysErCnt + 3 + offset];
        for(i=0;i<13;i++){
            New485Ladder[SECONDLINE_BASE+i+4] =StatusMessage[j][i];          //error status
        }
    }
    else{
        j=LadderGroup;
        j=((j-1) * 32)+1;

        for(i=0;i<16;i++){
            New485Ladder[i+2]=GroupLineMessage[j][i];
        }
        New485Ladder[15]=(LadderGroupSub / 10)+ '0';
        New485Ladder[16]=(LadderGroupSub % 10)+ '0';

        for(i=0;i<16;i++){
            New485Ladder[SECONDLINE_BASE+i]=GroupLineMessage[j][i];
        }
        New485Ladder[SECONDLINE_BASE+13]=(LadderGroupSub / 10)+ '0';
        New485Ladder[SECONDLINE_BASE+14]=(LadderGroupSub % 10)+ '0';
    }
}









                        





void  __attribute__((section(".usercode"))) Pc_Command(void)
{
    if((CAN2_RxBuf[2] == (CMD_EVEN_ODD)) && (CAN2_RxBuf[3] == 0x00)){
		ShadowsRamDArry[FLR_ON_OFF0] = CAN2_RxBuf[4];
		ShadowsRamDArry[FLR_ON_OFF1] = CAN2_RxBuf[5];
		ShadowsRamDArry[FLR_ON_OFF2] = CAN2_RxBuf[6];
		ShadowsRamDArry[FLR_ON_OFF3] = CAN2_RxBuf[7];		

    }    
    else if((CAN2_RxBuf[2] == (CMD_MORNING)) && (CAN2_RxBuf[3] == 0x00)){		
		CmdFixFlrTime= CAN2_RxBuf[4];
    }    
}

*/




void  DigitStringMessage(void)
{
    switch(LadderGroup){
		case    GROUP1_BLOCK:
		case    GROUP2_BLOCK:
		case    GROUP3_BLOCK:
		case    GROUP4_BLOCK:
			break;
    }    
}



void  Integer_Digit(void)
{

	if(EditDigitData > EditDigitMaxValue){	
		EditDigitData=EditDigitMinValue;
	}
	else if(EditDigitData < EditDigitMinValue){
		EditDigitData=EditDigitMaxValue;
	}



	if(EditDigitMaxValue < 10){
		EditDigitShiftCnt=1;
		One_Dig_Dsp(EditDigitData,EditDivide);
	}
	else if(EditDigitMaxValue < 100){
		EditDigitShiftCnt=2;
		Two_Dig_Dsp(EditDigitData,EditDivide);
	}
	else if(EditDigitMaxValue < 1000){
		EditDigitShiftCnt=3;
		Three_Dig_Dsp(EditDigitData,EditDivide);
	}
	else if(EditDigitMaxValue < 10000){
		EditDigitShiftCnt=4;
		Four_Dig_Dsp(EditDigitData,EditDivide);
	}
	else if(EditDigitMaxValue < 100000){
		EditDigitShiftCnt=5;
		Five_Dig_Dsp(EditDigitData,EditDivide);
	}
	else if(EditDigitMaxValue < 100000){
		EditDigitShiftCnt=6;
		Six_Dig_Dsp(EditDigitData,EditDivide);
	}
	else if(EditDigitMaxValue < 1000000){
		EditDigitShiftCnt=7;
		Seven_Dig_Dsp(EditDigitData,EditDivide);
	}
	else if(EditDigitMaxValue < 10000000){
		EditDigitShiftCnt=8;
		Eight_Dig_Dsp(EditDigitData,EditDivide);
	}
	else if(EditDigitMaxValue < 100000000){
		EditDigitShiftCnt=9;
		Nine_Dig_Dsp(EditDigitData,EditDivide);
	}
	else{
		EditDigitShiftCnt=10;
		Ten_Dig_Dsp(EditDigitData,EditDivide);
	}

    DigitStringMessage();
}



unsigned int  ReadLongData(unsigned int pt)
{
	unsigned long a,b,c,d;

    a=(unsigned long)information[pt+0];
    b=(unsigned long)information[pt+1];
    c=(unsigned long)information[pt+2];
    d=(unsigned long)information[pt+3];

	b=(b << 8);
	c=(c << 16);
	d=(d << 24);
	EditDigitData=(a | b| c| d);
    EditDataType=LONG_TYPE;

	return(0);
}

unsigned int  ReadIntegerData(unsigned int pt)
{
	unsigned long a,b;

    a=(unsigned long)information[pt+0];
    b=(unsigned long)information[pt+1];
	EditDigitData=(a | (b << 8));	
    EditDataType=INT_TYPE;
	return(0);
}

unsigned int  ReadByteData(unsigned int pt)
{
    EditDigitData=(unsigned long)(information[pt]);
    EditDataType=BYTE_TYPE;
	return(0);
}



void  Group1(void)
{
    unsigned int i,j;

	EditCursor=0;
	EditDigitCursor=0;

    switch(LadderGroupSub){
        case    GROUP1_MENU01:
            EditCursor=0;
            EditStatus=DIGIT_EDIT;
            EditStart=3;
            EditShiftCnt=3;
            EditDivide=DIVIDE_10;				
            EditDigitMaxValue=255;
            EditDigitMinValue=0;
			if(EditDivide > 0)	EditShiftCnt=(EditShiftCnt+1);
	
            EditFlashAddr=ByteData001;
			ReadByteData(EditFlashAddr);
            Integer_Digit();
			break;
		case	GROUP1_MENU02:
            EditCursor=0;
            EditStatus=DIGIT_EDIT;
            EditStart=3;
            EditShiftCnt=5;
            EditDivide=DIVIDE_100;				
            EditDigitMaxValue=65535;
            EditDigitMinValue=0;
			if(EditDivide > 0)	EditShiftCnt=(EditShiftCnt+1);	
            EditFlashAddr=IntzData002;
			ReadIntegerData(EditFlashAddr);
            Integer_Digit();
			break;
		case	GROUP1_MENU03:
            EditCursor=0;
            EditStatus=DIGIT_EDIT;
            EditStart=3;
            EditShiftCnt=10;
            EditDivide=DIVIDE_1000;				
            EditDigitMaxValue=0xffffffff;
            EditDigitMinValue=0;
			if(EditDivide > 0)	EditShiftCnt=(EditShiftCnt+1);	
            EditFlashAddr=longData003;
			ReadLongData(EditFlashAddr);
            Integer_Digit();
            EditShiftCnt=(EditShiftCnt + 1);
			break;
		case	GROUP1_MENU04:
		case	GROUP1_MENU05:
		case	GROUP1_MENU06:
		case	GROUP1_MENU07:
		case	GROUP1_MENU08:
		case	GROUP1_MENU09:
		case	GROUP1_MENU10:
		case	GROUP1_MENU11:
		case	GROUP1_MENU12:
		case	GROUP1_MENU13:
		case	GROUP1_MENU14:
		case	GROUP1_MENU15:
		case	GROUP1_MENU16:
		case	GROUP1_MENU17:
		case	GROUP1_MENU18:
		case	GROUP1_MENU19:
		case	GROUP1_MENU20:
		case	GROUP1_MENU21:
		case	GROUP1_MENU22:
		case	GROUP1_MENU23:
		case	GROUP1_MENU24:
		case	GROUP1_MENU25:
		case	GROUP1_MENU26:
		case	GROUP1_MENU27:
		case	GROUP1_MENU28:
		case	GROUP1_MENU29:
		case	GROUP1_MENU30:
		case	GROUP1_MENU31:
		case	GROUP1_MENU32:
				break;
	}

/*
    switch(LadderGroupSub){
        case    GROUP1_MENU01:
            Cursor=0;
            ShiftCnt=0;
            EditStart=5;
            EditStatus=NO_EDIT;
            DigitMaxValue=0;
            DigitMinValue=0;

            i=F_Ver0;
            New485Ladder[SECONDLINE_BASE+EditStart+0]=cF_FLRDSPCH((unsigned long)(i+0));  
            New485Ladder[SECONDLINE_BASE+EditStart+1]='.';      
            New485Ladder[SECONDLINE_BASE+EditStart+2]=cF_FLRDSPCH((unsigned long)(i+1));  
            New485Ladder[SECONDLINE_BASE+EditStart+3]=cF_FLRDSPCH((unsigned long)(i+2));   

            break;
        case    GROUP1_MENU01:
            Cursor=0;
            ShiftCnt=0;
            EditStart=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=ELEV_BD_ID_MESSAGE_CNT;
            DigitMinValue=0;


            i=F_Bd_Id;
            DigitData=cF_FLRDSPCH((unsigned long)i);

            switch(DigitData){
                case    0x0:
                case    0x1:
                case    0x2:
                    break;
                case    0x4:
                    DigitData=3;    
                    break;
                case    0x5:
                    DigitData=4;    
                    break;
                case    0x6:
                    DigitData=5;    
                    break;
                case    0x8:
                    DigitData=6;    
                    break;
                case    0x9:
                    DigitData=7;    
                    break;
                case    0xa:
                    DigitData=8;    
                    break;
            }

            Integer_Digit();

            break;
        case    GROUP1_MENU01:
            Cursor=0;
            ShiftCnt=4;
            EditStart=5;
            EditStatus=DIGIT_ALPHAR_EDIT;
            DigitMaxValue=0;
            DigitMinValue=0;
            New485Ladder[SECONDLINE_BASE+EditStart+0]='*';  
            New485Ladder[SECONDLINE_BASE+EditStart+1]='*';  
            New485Ladder[SECONDLINE_BASE+EditStart+2]='*';      
            New485Ladder[SECONDLINE_BASE+EditStart+3]='*';      
            break;
        case    GROUP1_MENU01:
            Cursor=0;
            ShiftCnt=5;
            EditStart=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=65535;
            DigitMinValue=0;

            i=F_SerialNm10;
            DigitData=iF_FLRDSPCH((unsigned long)i);
            Integer_Digit();

            break;
        case    GROUP1_MENU01:
        case    GROUP1_MENU01:
        case    GROUP1_MENU01:
        case    GROUP1_MENU01:
            Cursor=0;
            ShiftCnt=0;
            EditStart=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=USER_LAMP_MESSAGE_CNT;
            DigitMinValue=0;

			if(LadderGroupSub == USER_LAMP1)		i=F_UserLamp1;
			else if(LadderGroupSub == USER_LAMP2)	i=F_UserLamp2;
			else if(LadderGroupSub == USER_LAMP3)	i=F_UserLamp3;
			else if(LadderGroupSub == USER_LAMP4)	i=F_UserLamp4;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();

            break;
        case    SYSTEM_SET:
            Cursor=0;
            ShiftCnt=0;
            EditStart=3;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=SYSTEM_SET_MESSAGE_CNT;
            DigitMinValue=0;

            i=F_SystemSet;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();

			break;
        case    ERR_ST_CNT:
            Cursor=0;
            ShiftCnt=3;
            EditStart=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=255;
            DigitMinValue=0;

            i=F_ErrStopCnt;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();

            break;
        case    GROUP_NUMBER:
            Cursor=0;
            ShiftCnt=2;
            EditStart=6;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=31;
            DigitMinValue=0;

            i=F_GroupNm;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();

            break;
        case    LOCAL_NUMBER:
            Cursor=0;
            ShiftCnt=1;
            EditStart=7;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=7;
            DigitMinValue=0;

            i=F_LocalNm;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();

            break;
        case    NORMAL_DSP:                                      //NormalDsp
            Cursor=0;
            ShiftCnt=0;
            EditStart=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=NORMAL_DSP_MESSAGE_CNT;
            DigitMinValue=0;

            i=F_NormalDsp;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();

            break;
        case    COMPANY_NAME:                           
            Cursor=0;
            ShiftCnt=1;
            EditStart=7;
            EditStatus=DIGIT_ALPHAR_EDIT;
            DigitMaxValue=0;
            DigitMinValue=0;

            i=F_Company;
            New485Ladder[SECONDLINE_BASE+EditStart+0]=cF_FLRDSPCH((unsigned long)(i));  

            break;
        case    HH_MM_SS:
            Cursor=0;
            ShiftCnt=8;
            EditStart=5;
            EditStatus=CLOCK_EDIT;

            New485Ladder[SECONDLINE_BASE+EditStart+0] =(sRamDArry[Hour]    >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+1] =(sRamDArry[Hour]    &  0x0f)   + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+2]='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+3] =(sRamDArry[Minuate] >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+4]=(sRamDArry[Minuate] & 0x0f)     + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+5]='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+6]=(sRamDArry[sec]     >> 4)       + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+7]=(sRamDArry[sec]     & 0x0f)     + '0';          

            break;
        case    YY_MM_DD:
            Cursor=0;
            ShiftCnt=8;
            EditStart=5;
            EditStatus=CLOCK_EDIT;

            New485Ladder[SECONDLINE_BASE+EditStart+0] =(sRamDArry[Year]    >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+1] =(sRamDArry[Year]    & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+2]='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+3] =(sRamDArry[Month]   >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+4] =(sRamDArry[Month]   & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+5]='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+6] =(sRamDArry[Day]     >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+7] =(sRamDArry[Day]     & 0x0f)    + '0';          

            break;
        case    OUT_DATE:
            Cursor=0;
            ShiftCnt=8;
            EditStart=5;
            EditStatus=CLOCK_EDIT;

            New485Ladder[SECONDLINE_BASE+EditStart+0] =(cF_year    >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+1] =(cF_year    & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+2]='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+3] =(cF_month   >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+4] =(cF_month   & 0x0f)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+5]='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+6] =(cF_day     >> 4)      + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+7] =(cF_day     & 0x0f)    + '0';          

            break;
        case    DRIVE_METHOD:
            Cursor=0;
            ShiftCnt=0;
            EditStart=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=3;
            DigitMinValue=0;


            if(cF_NONSERVICE0 == 0x55)		DigitData=1;
            else if(cF_NONSERVICE0 == 0xaa)	DigitData=2;
 			else							DigitData=0;

            Integer_Digit();

            break;
        case    FHM_RUN_CHK:
            Cursor=0;
            ShiftCnt=0;
            EditStart=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=2;
            DigitMinValue=0;

			DigitData=0;
            Integer_Digit();

            break;
        case    LG_INV_IN_BD:
            Cursor=0;
            ShiftCnt=0;
            EditStart=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=2;
            DigitMinValue=0;

            i=F_PcbType;
            DigitData=cF_FLRDSPCH((unsigned long)i);
            Integer_Digit();

            break;
        case    ALL_MENU_CHK:
        case    ENGINEER_NM:
            Cursor=0;
            ShiftCnt=4;
            EditStart=5;
            EditStatus=DIGIT_ALPHAR_EDIT;
            DigitMaxValue=0;
            DigitMinValue=0;

            New485Ladder[SECONDLINE_BASE+EditStart+0]='0';  
            New485Ladder[SECONDLINE_BASE+EditStart+1]='0';  
            New485Ladder[SECONDLINE_BASE+EditStart+2]='0';      
            New485Ladder[SECONDLINE_BASE+EditStart+3]='0';      
            break;
        case    TOTAL_USE_TIME:
            Cursor=0;
            ShiftCnt=5;
            EditStart=5;
            EditStatus=NO_EDIT;
            DigitMaxValue=0xffff;
            DigitMinValue=0;

            DigitData=PowerOnTime;
            Integer_Digit();

            break;
        case    INIT_DATA:

            Cursor=0;
            ShiftCnt=0;
            EditStart=5;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=INIT_MESSAGE;
            DigitMinValue=0;
            DigitData=0;
            Integer_Digit();

            break;
        case    VIRTUAL_CALL:

            Cursor=0;
            ShiftCnt=9;
            EditStart=4;
            EditStatus=CLOCK_EDIT;

            if(sRamDArry[mVFlrCnt] > 254)			sRamDArry[mVFlrCnt]=0;
            if(sRamDArry[mVFlr1]   > (cF_TOPFLR+1))	sRamDArry[mVFlr1]=0;
            if(sRamDArry[mVFlr2]   > (cF_TOPFLR+1))	sRamDArry[mVFlr2]=0;
	
			i=sRamDArry[mVFlrCnt];
            New485Ladder[SECONDLINE_BASE+EditStart+0] =(i / 100)	+ '0';
			i=(i % 100);           
            New485Ladder[SECONDLINE_BASE+EditStart+1] =(i / 10)  + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+2] =(i % 10)  + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+3] ='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+4] =(sRamDArry[mVFlr1] / 10)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+5] =(sRamDArry[mVFlr1] % 10)    + '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+6] ='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+7] =(sRamDArry[mVFlr2] / 10)	+ '0';          
            New485Ladder[SECONDLINE_BASE+EditStart+8] =(sRamDArry[mVFlr2] % 10)    + '0';        
 
            break;

        case    HALL_IND_SET:

            Cursor=0;
            ShiftCnt=11;
            EditStart=5;
            EditStatus=CLOCK_EDIT;

            New485Ladder[SECONDLINE_BASE+EditStart+0]  =HibSet[0] + '0';
            New485Ladder[SECONDLINE_BASE+EditStart+1]  ='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+2]  =HibSet[1] + '0';
            New485Ladder[SECONDLINE_BASE+EditStart+3]  ='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+4]  =HibSet[2] + '0';
            New485Ladder[SECONDLINE_BASE+EditStart+5]  ='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+6]  =HibSet[3] + '0';
            New485Ladder[SECONDLINE_BASE+EditStart+7]  ='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+8]  =HibSet[4] + '0';
            New485Ladder[SECONDLINE_BASE+EditStart+9]  ='-';          
            New485Ladder[SECONDLINE_BASE+EditStart+10] =HibSet[5] + '0';

            break;
		case    User_G4:
		case    User_G5:
		case    User_G6:
				break;
		case    FINAL_ERR_DSP:			

            Cursor=0;
            ShiftCnt=0;
            EditStart=0;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=FINAL_ERR_DSP_MESSAGE_CNT;
            DigitMinValue=0;
            DigitData=0;
            Integer_Digit();

			break;
		case    SENSOR_POSITION:

            Cursor=0;
            ShiftCnt=0;
            EditStart=0;
            EditStatus=DIGIT_STRING_EDIT;
            DigitMaxValue=SENSOR_POSITION_MESSAGE_CNT;
            DigitMinValue=0;
            DigitData=0;
            Integer_Digit();

			break;
		case    ENCODER_RATE: 

            Cursor=0;
            ShiftCnt=5;
            EditStart=5;
            EditStatus=DIGIT_EDIT;
            DigitMaxValue=65535;
            DigitMinValue=0;

            i=F_StopPulse0;
            DigitData=iF_FLRDSPCH((unsigned long)i);
            Integer_Digit();

           break;
        default:
            break;
    }
*/

}


void  Group2(void)
{
    unsigned int i,j;

    switch(LadderGroupSub){
        case    GROUP2_MENU01:
		case	GROUP2_MENU02:
		case	GROUP2_MENU03:
		case	GROUP2_MENU04:
		case	GROUP2_MENU05:
		case	GROUP2_MENU06:
		case	GROUP2_MENU07:
		case	GROUP2_MENU08:
		case	GROUP2_MENU09:
		case	GROUP2_MENU10:
		case	GROUP2_MENU11:
		case	GROUP2_MENU12:
		case	GROUP2_MENU13:
		case	GROUP2_MENU14:
		case	GROUP2_MENU15:
		case	GROUP2_MENU16:
		case	GROUP2_MENU17:
		case	GROUP2_MENU18:
		case	GROUP2_MENU19:
		case	GROUP2_MENU20:
		case	GROUP2_MENU21:
		case	GROUP2_MENU22:
		case	GROUP2_MENU23:
		case	GROUP2_MENU24:
		case	GROUP2_MENU25:
		case	GROUP2_MENU26:
		case	GROUP2_MENU27:
		case	GROUP2_MENU28:
		case	GROUP2_MENU29:
		case	GROUP2_MENU30:
		case	GROUP2_MENU31:
		case	GROUP2_MENU32:
				break;
	}
}


void  Group3(void)
{
    unsigned int i,j;

    switch(LadderGroupSub){
        case    GROUP3_MENU01:
		case	GROUP3_MENU02:
		case	GROUP3_MENU03:
		case	GROUP3_MENU04:
		case	GROUP3_MENU05:
		case	GROUP3_MENU06:
		case	GROUP3_MENU07:
		case	GROUP3_MENU08:
		case	GROUP3_MENU09:
		case	GROUP3_MENU10:
		case	GROUP3_MENU11:
		case	GROUP3_MENU12:
		case	GROUP3_MENU13:
		case	GROUP3_MENU14:
		case	GROUP3_MENU15:
		case	GROUP3_MENU16:
		case	GROUP3_MENU17:
		case	GROUP3_MENU18:
		case	GROUP3_MENU19:
		case	GROUP3_MENU20:
		case	GROUP3_MENU21:
		case	GROUP3_MENU22:
		case	GROUP3_MENU23:
		case	GROUP3_MENU24:
		case	GROUP3_MENU25:
		case	GROUP3_MENU26:
		case	GROUP3_MENU27:
		case	GROUP3_MENU28:
		case	GROUP3_MENU29:
		case	GROUP3_MENU30:
		case	GROUP3_MENU31:
		case	GROUP3_MENU32:
				break;
	}
}

void  Group4(void)
{
    unsigned int i,j;

    switch(LadderGroupSub){
        case    GROUP4_MENU01:
		case	GROUP4_MENU02:
		case	GROUP4_MENU03:
		case	GROUP4_MENU04:
		case	GROUP4_MENU05:
		case	GROUP4_MENU06:
		case	GROUP4_MENU07:
		case	GROUP4_MENU08:
		case	GROUP4_MENU09:
		case	GROUP4_MENU10:
		case	GROUP4_MENU11:
		case	GROUP4_MENU12:
		case	GROUP4_MENU13:
		case	GROUP4_MENU14:
		case	GROUP4_MENU15:
		case	GROUP4_MENU16:
		case	GROUP4_MENU17:
		case	GROUP4_MENU18:
		case	GROUP4_MENU19:
		case	GROUP4_MENU20:
		case	GROUP4_MENU21:
		case	GROUP4_MENU22:
		case	GROUP4_MENU23:
		case	GROUP4_MENU24:
		case	GROUP4_MENU25:
		case	GROUP4_MENU26:
		case	GROUP4_MENU27:
		case	GROUP4_MENU28:
		case	GROUP4_MENU29:
		case	GROUP4_MENU30:
		case	GROUP4_MENU31:
		case	GROUP4_MENU32:
				break;
	}
}



////////////////////new ladder////////////////////////////
////////////////////new ladder////////////////////////////
////////////////////new ladder////////////////////////////

void  Group1_Save(void)
{
    unsigned int i,j;
    unsigned char a;

	FlashBlockRd(0);
	if(EditDataType == LONG_TYPE){
		a=(unsigned char)(EditDigitData);
		new_value[EditFlashAddr+0]=a;

		a=(unsigned char)(EditDigitData >> 8);
		new_value[EditFlashAddr+1]=a;

		a=(unsigned char)(EditDigitData >> 16);
		new_value[EditFlashAddr+2]=a;

		a=(unsigned char)(EditDigitData >> 24);
		new_value[EditFlashAddr+3]=a;
	}
	else if(EditDataType == INT_TYPE){
		a=(unsigned char)(EditDigitData);
		new_value[EditFlashAddr+0]=a;

		a=(unsigned char)(EditDigitData >> 8);
		new_value[EditFlashAddr+1]=a;
	}
	else{
		new_value[EditFlashAddr]=(unsigned char)(EditDigitData);
	}
	FlashBlockWr(0);

}

void  Group2_Save(void)
{
    unsigned int i,j;

    switch(LadderGroupSub){
        case    GROUP2_MENU01:
		case	GROUP2_MENU02:
		case	GROUP2_MENU03:
		case	GROUP2_MENU04:
		case	GROUP2_MENU05:
		case	GROUP2_MENU06:
		case	GROUP2_MENU07:
		case	GROUP2_MENU08:
		case	GROUP2_MENU09:
		case	GROUP2_MENU10:
		case	GROUP2_MENU11:
		case	GROUP2_MENU12:
		case	GROUP2_MENU13:
		case	GROUP2_MENU14:
		case	GROUP2_MENU15:
		case	GROUP2_MENU16:
		case	GROUP2_MENU17:
		case	GROUP2_MENU18:
		case	GROUP2_MENU19:
		case	GROUP2_MENU20:
		case	GROUP2_MENU21:
		case	GROUP2_MENU22:
		case	GROUP2_MENU23:
		case	GROUP2_MENU24:
		case	GROUP2_MENU25:
		case	GROUP2_MENU26:
		case	GROUP2_MENU27:
		case	GROUP2_MENU28:
		case	GROUP2_MENU29:
		case	GROUP2_MENU30:
		case	GROUP2_MENU31:
		case	GROUP2_MENU32:
				break;
	}
}


void  Group3_Save(void)
{
    unsigned int i,j;

    switch(LadderGroupSub){
        case    GROUP3_MENU01:
		case	GROUP3_MENU02:
		case	GROUP3_MENU03:
		case	GROUP3_MENU04:
		case	GROUP3_MENU05:
		case	GROUP3_MENU06:
		case	GROUP3_MENU07:
		case	GROUP3_MENU08:
		case	GROUP3_MENU09:
		case	GROUP3_MENU10:
		case	GROUP3_MENU11:
		case	GROUP3_MENU12:
		case	GROUP3_MENU13:
		case	GROUP3_MENU14:
		case	GROUP3_MENU15:
		case	GROUP3_MENU16:
		case	GROUP3_MENU17:
		case	GROUP3_MENU18:
		case	GROUP3_MENU19:
		case	GROUP3_MENU20:
		case	GROUP3_MENU21:
		case	GROUP3_MENU22:
		case	GROUP3_MENU23:
		case	GROUP3_MENU24:
		case	GROUP3_MENU25:
		case	GROUP3_MENU26:
		case	GROUP3_MENU27:
		case	GROUP3_MENU28:
		case	GROUP3_MENU29:
		case	GROUP3_MENU30:
		case	GROUP3_MENU31:
		case	GROUP3_MENU32:
				break;
	}
}

void  Group4_Save(void)
{
    unsigned int i,j;

    switch(LadderGroupSub){
        case    GROUP4_MENU01:
		case	GROUP4_MENU02:
		case	GROUP4_MENU03:
		case	GROUP4_MENU04:
		case	GROUP4_MENU05:
		case	GROUP4_MENU06:
		case	GROUP4_MENU07:
		case	GROUP4_MENU08:
		case	GROUP4_MENU09:
		case	GROUP4_MENU10:
		case	GROUP4_MENU11:
		case	GROUP4_MENU12:
		case	GROUP4_MENU13:
		case	GROUP4_MENU14:
		case	GROUP4_MENU15:
		case	GROUP4_MENU16:
		case	GROUP4_MENU17:
		case	GROUP4_MENU18:
		case	GROUP4_MENU19:
		case	GROUP4_MENU20:
		case	GROUP4_MENU21:
		case	GROUP4_MENU22:
		case	GROUP4_MENU23:
		case	GROUP4_MENU24:
		case	GROUP4_MENU25:
		case	GROUP4_MENU26:
		case	GROUP4_MENU27:
		case	GROUP4_MENU28:
		case	GROUP4_MENU29:
		case	GROUP4_MENU30:
		case	GROUP4_MENU31:
		case	GROUP4_MENU32:
				break;
	}
}




unsigned int  SaveData(void)
{
    unsigned int i,ret;

	ret=0;
    switch(LadderGroup){
		case    GROUP1_BLOCK:
			Group1_Save();
			break;
		case    GROUP2_BLOCK:
			Group2_Save();
			break;
		case    GROUP3_BLOCK:
			Group3_Save();
			break;
		case    GROUP4_BLOCK:
			Group4_Save();
			break;
	}

    EditCursor=0;
	return(ret);
}



unsigned int Default_Cur_State_Display(void)
{
	unsigned int i,j;

	j=65;
	for(i=0;i<16;i++)	New485Ladder[SECONDLINE_BASE+i] =StatusMessage[j][i];          		

/*

		i=BlinkDisplay();
		if( i>0){
			if(i==1){
				if(!bDspSeq)	j=sRamDArry[mEV_LastErr];
				else			j=sRamDArry[mSysStatus];
			}
			else if(i==2){
				if(!bDspSeq)	j=sOVL;
				else			j=sRamDArry[mSysStatus];				
			}
			else if(i==3){
				if(!bDspSeq)	j=sSFT;
				else			j=sRamDArry[mSysStatus];				
			}
			else				j=sRamDArry[mSysStatus];

	        for(i=0;i<16;i++)	New485Ladder[SECONDLINE_BASE+i] =StatusMessage[j][i];          		
		}
		else{
			if(bAutoTunning){
				TunningMessage();
			}
			else if( bFhmRun && (sRamDArry[FHM_SEQ] == FHM_SEQ_5)){
				FHM_SuccessDisplay();
			}
			else{
	            j=sRamDArry[mSysStatus];
	            for(i=0;i<16;i++)	New485Ladder[SECONDLINE_BASE+i] =StatusMessage[j][i];          
			}
		}
*/

	return(0);
}


unsigned int DefaultDisplay(void)
{
    unsigned int  i,j,k;

	if(LadderGroup > 0)	return(0);	    

	k=0;    
	EditStart=0;
	if(BefDspMode != k){
		BefDspMode = k;
        for(i=0;i<16;i++){
            New485Ladder[SECONDLINE_BASE+i] =' ';          
        }
	}
	

    switch(k){
        case    0:
			Default_Cur_State_Display();
            break;
        case    1:
            break;
        case    2:
            break;
        case    3:
            break;
        case    4:
            break;
        case    5:
            break;
        case    6:
            break;
        case    7:
        case    8:
        case    9:
        case    10:
        case    11:
        case    12:
            break;
        case    13:
            break;
        case    14:
            break;
        case    15:
			break;
        case    16:
            break;
        case    17:
            break;
        case    18:
        	break;
        default:
            break;
    }

	return(0);		
}



unsigned int  LaderDsp(void)
{
    unsigned int i,j;


    for(i=0;i<MAX_LADDER_BUF-2;i++)   New485Ladder[i]=' ';
    New485Ladder[MAX_LADDER_BUF-1]=0x0;   


    j=LadderGroup;

	if(j>0){    
	    j=(LadderGroupSub + ((j-1) * 32))+1;
	}
	


	for(i=0;i<16;i++){
	    New485Ladder[i+2]=GroupLineMessage[j][i];
	}


    New485Ladder[0]=LadderKey;    
    New485Ladder[1]=' ';

    New485Ladder[SECONDLINE_BASE+0] =(LadderGroupSub/10) + '0';          
    New485Ladder[SECONDLINE_BASE+1] =(LadderGroupSub%10) + '0';          

	return(0);
}






void  CursorOff(void)
{
    New485Ladder[SECONDLINE_CURSOR]=' ';  
}

void  CursorOn(void)
{
    unsigned int i;

    i=EditCursor + EditStart;                    
    if(i>0x09)  i=i + '7';
    else        i=i + '0';
    New485Ladder[SECONDLINE_CURSOR]=i;  
}


unsigned int ShiftLeftCur(void)
{
    unsigned int  i;

    if(EditShiftCnt==0)     EditCursor=0;
    else if(EditCursor>0)   EditCursor--;
    else                	EditCursor=EditShiftCnt-1;


    if(EditDigitCursor>0)  	EditDigitCursor--;
    else                	EditDigitCursor=EditDigitShiftCnt-1;


    i=SECONDLINE_BASE + EditStart + EditCursor;

    if(EditStatus == DIGIT_EDIT){
        if((New485Ladder[i] == '.') || (New485Ladder[i] == ('.' + 0x80))){
            if(EditShiftCnt==0)     EditCursor=0;
            else if(EditCursor>0)   EditCursor--;
            else                	EditCursor=EditShiftCnt-1;
        }
    }           
    else if(EditStatus == CLOCK_EDIT){
        if((New485Ladder[i] == '-') || (New485Ladder[i] == ('-' + 0x80))){
            if(EditShiftCnt==0) 	EditCursor=0;
            else if(EditCursor>0)   EditCursor--;
            else                	EditCursor=EditShiftCnt-1;
        }
    }           
	return(0);
}



unsigned int  ShiftRightCur(void)
{
    unsigned int i;

    if(EditShiftCnt==0) EditCursor=0;
    else            	EditCursor=(EditCursor+1)%EditShiftCnt; 

	EditDigitCursor=(EditDigitCursor+1)	% EditDigitShiftCnt;


    i=SECONDLINE_BASE + EditStart + EditCursor;

    if(EditStatus == DIGIT_EDIT){
        if((New485Ladder[i] == '.') || (New485Ladder[i] == ('.' + 0x80))){
            if(EditShiftCnt==0) EditCursor=0;
            else            	EditCursor=(EditCursor+1) % EditShiftCnt; 
        }
    }           
    else if(EditStatus == CLOCK_EDIT){
        if((New485Ladder[i] == '-') || (New485Ladder[i] == ('-' + 0x80))){
            if(EditShiftCnt==0) EditCursor=0;
            else            	EditCursor=(EditCursor+1)%EditShiftCnt; 
        }
    }
	return(0);           
}



unsigned int  CusorDataUp(void)
{
    unsigned int i,dp;
    i=SECONDLINE_BASE + EditStart + EditCursor;

    switch(EditStatus){
        case    DIGIT_EDIT:
            switch(EditDigitShiftCnt-EditDigitCursor){
                case    1:
                    EditDigitData++;
                    break;
                case    2:
                    EditDigitData=EditDigitData+10;
                    break;                    
                case    3:
                    EditDigitData=EditDigitData+100;
                    break;                    
                case    4:
                    EditDigitData=EditDigitData+1000;
                    break;                    
                case    5:
                    EditDigitData=EditDigitData+10000;
                    break;                    
                case    6:
                    EditDigitData=EditDigitData+100000;
                    break;
                case    7:
                    EditDigitData=EditDigitData+1000000;
                    break;                    
                case    8:
                    EditDigitData=EditDigitData+10000000;
                    break;                    
                case    9:
                    EditDigitData=EditDigitData+100000000;
                    break;                    
                case    10:
                    EditDigitData=EditDigitData+1000000000;
                    break;                    
            }
            Integer_Digit();    
            break;
        case    DIGIT_STRING_EDIT:
			i=EditDigitMaxValue;

            if( i > 0 ){
				EditDigitData= ( (EditDigitData+1) % i);
            }
			else	EditDigitData=0;	
            Integer_Digit();    
            break;
        case    DIGIT_ALPHAR_EDIT:
            New485Ladder[i]++;
            if(New485Ladder[i]>'Z')                      					New485Ladder[i]='0';
            else if((New485Ladder[i]>'9') && (New485Ladder[i]<'A'))  		New485Ladder[i]='A';
            else if(New485Ladder[i] < '0')  								New485Ladder[i]='0';

            break;
        case    CLOCK_EDIT:
            New485Ladder[i]++;
            if((New485Ladder[i]<'0'))       New485Ladder[i]='9'; 
            else if(New485Ladder[i]>'9')    New485Ladder[i]='0'; 
            break;
        case    TABLE_EDIT:
                break;    
        case    TOGGLE_EDIT:
                break;    
    }
	return(0);         
}


unsigned int  CusorDataDn(void)
{
    unsigned int i,dp;

    i=SECONDLINE_BASE + EditStart + EditCursor;

    switch(EditStatus){
        case    DIGIT_EDIT:
            switch(EditDigitShiftCnt-EditDigitCursor){
                case    1:
                    EditDigitData--;
                    break;
                case    2:
                    EditDigitData=EditDigitData-10;
                    break;                    
                case    3:
                    EditDigitData=EditDigitData-100;
                    break;                    
                case    4:
                    EditDigitData=EditDigitData-1000;
                    break;                    
                case    5:
                    EditDigitData=EditDigitData-10000;
                    break;                    
                case    6:
                    EditDigitData=EditDigitData-100000;
                    break;
                case    7:
                    EditDigitData=EditDigitData-1000000;
                    break;                    
                case    8:
                    EditDigitData=EditDigitData-10000000;
                    break;                    
                case    9:
                    EditDigitData=EditDigitData-100000000;
                    break;                    
                case    10:
                    EditDigitData=EditDigitData-1000000000;
                    break;                    
            }
            Integer_Digit();    
            break;
        case    DIGIT_STRING_EDIT:
            if(EditDigitData > EditDigitMinValue)   EditDigitData--; 
            else                            EditDigitData=(EditDigitMaxValue-1);
            Integer_Digit();    
            break;
        case    DIGIT_ALPHAR_EDIT:
            New485Ladder[i]--;
            if((New485Ladder[i]<'0'))                      				New485Ladder[i]='Z'; 
            else if((New485Ladder[i]>'9') && (New485Ladder[i]<'A'))  	New485Ladder[i]='9'; 
            else if(New485Ladder[i]>'Z')  								New485Ladder[i]='Z'; 
            break;
        case    CLOCK_EDIT:
            break;
        case    TABLE_EDIT:
                break;    
        case    TOGGLE_EDIT:
                break;    
    }
	return(0);         
}


unsigned int CusorDigitSet(void)
{
    unsigned int i;
    i=SECONDLINE_BASE + EditStart + EditCursor;

    switch(EditStatus){
        case    DIGIT_EDIT:
        case    DIGIT_ALPHAR_EDIT:
            New485Ladder[i]=LadderKey;
            break;
    }        
	return(0); 
}



unsigned int  EditOnCheck(void)
{
    unsigned int i;
    
    i=1;
    if(EditStatus==NO_EDIT) return(0);
    if(bMoveCar)            return(0);


	switch(LadderGroup){
		case    GROUP1_BLOCK:
		case    GROUP2_BLOCK:
		case    GROUP3_BLOCK:
		case    GROUP4_BLOCK:
			i=1;
			break;
		default:
			i=0;
			break;	
	}
	return(i);
}


unsigned int  GroupOnChk(void)
{
	unsigned int i;
	i=1;

	switch(LadderGroup){
		case    GROUP1_BLOCK:
		case    GROUP2_BLOCK:
		case    GROUP3_BLOCK:
		case    GROUP4_BLOCK:
			i=1;
			break;
		default:
			i=0;
			break;	
	}
	return(i);
}



unsigned int  MenuOnChk(void)
{
	unsigned int i;
	i=1;

	switch(LadderGroup){
		case    GROUP1_BLOCK:
		case    GROUP2_BLOCK:
		case    GROUP3_BLOCK:
		case    GROUP4_BLOCK:
			i=1;
			break;
		default:
			i=0;
			break;	
	}
	return(i);
}



void  NewMenuStart(void)
{

    EnterKey=0;
    EditCursor=0;
    EditShiftCnt=0;
    EditStatus=0;
    EditStart=0;

	switch(LadderGroup){
		case    GROUP1_BLOCK:
		case    GROUP2_BLOCK:
		case    GROUP3_BLOCK:
		case    GROUP4_BLOCK:
			break;
		default:
			break;	
	}

	MaxSubMenu=32;
	


/*
    
    switch(LadderGroup){
        case    FLR_DSP_GROUP:    
            MaxSubMenu=FLR_DSP_GROUP_MAX;
            break;
        case    FLR_GROUP:
            MaxSubMenu=FLR_GROUP_MAX;
            break;
        case    TIMER_GROUP:
            MaxSubMenu=TIMER_GROUP_MAX;
            break;
        case    SUB_DOOR_GROUP:
            MaxSubMenu=ONOFF1_GROUP_MAX;
            break;
        case    ONOFF1_GROUP:
            MaxSubMenu=ONOFF1_GROUP_MAX;
            break;
        case    ONOFF2_GROUP: 
            MaxSubMenu=ONOFF2_GROUP_MAX;
            break;
        case    NCNO1_GROUP:
            MaxSubMenu=NCNO1_GROUP_MAX;
            break;
        case    NCNO2_GROUP:
            MaxSubMenu=NCNO2_GROUP_MAX;
            break;
        case    NCNO3_GROUP:
//            MaxSubMenu=NCNO3_GROUP_MAX;
            break;
        case    IO_GROUP: 
            MaxSubMenu=IO_GROUP_MAX;
            break;
        case    USER_GROUP:    //save
            MaxSubMenu=USER_GROUP_MAX;
            break;
        case    OPEN_WAIT_GROUP:
            MaxSubMenu=OPEN_WAIT_GROUP_MAX;
            break;
        case    PARAMETER_GROUP:
            MaxSubMenu=PARAMETER_GROUP_MAX;
            break;
        case    INPORT1_GROUP:
            MaxSubMenu=INPORT1_GROUP_MAX;
            break;
        case    INPORT2_GROUP:
            MaxSubMenu=INPORT2_GROUP_MAX;
            break;
        case    OUTPORT_GROUP:
//            MaxSubMenu=OUTPORT_GROUP_MAX;
            break;            
        case    ERROR_GROUP:
            MaxSubMenu=ERROR_GROUP_MAX;
            break;
        case    EL_GROUP:
            MaxSubMenu=EL_GROUP_MAX;
            break;
    }
*/
}




unsigned int  KeyCheck(void)
{
    unsigned int  i,j,newmenu,ret;
    unsigned int  max_group_sel;

	ret=0;


	max_group_sel=MAX_GROUP;


	j=0;
    newmenu=1;

    LadderKey = LadderBuf[C_SAVE_DATA+0];


    switch(LadderKey){
        case    MENUKEY:
                LadderKeyTime=0;
                do{
					j++;
                    i=1;

					LadderGroup=(LadderGroup + 1) % max_group_sel; 	
					LadderGroupSub=0;

                    NewMenuStart();
                    CursorOff();
                    i=GroupOnChk(); 
                }while((i==0) && (j <30));
                break;
        case    ESCKEY:
				if(EnterKey==2){
					EnterKey=1;
				}
				else if(EnterKey==1){
					EnterKey=0;			
					if(LadderGroupSub==0){
						LadderGroup=0;
					}
	                LadderGroupSub=0;

				}
				else{
					LadderGroup=0;
	                LadderGroupSub=0;
				}

	            LadderKeyTime=0;
	            NewMenuStart();
                CursorOff(); 
                break;
        case    UPKEY:
                LadderKeyTime=0;
                if(EnterKey==1){
	                do{
                        LadderGroupSub=(LadderGroupSub+1)% MaxSubMenu;
	                    i=MenuOnChk(); 
	                }while(i==0);
                    NewMenuStart();
                    CursorOff(); 
                }
                else if(EnterKey==2){
                    CusorDataUp();
					newmenu=0;
                }
                break;
        case    DOWNKEY:
                LadderKeyTime=0;
                if(EnterKey==1){
	                do{
	                    if(LadderGroupSub>0)    LadderGroupSub--;
	                    else                    LadderGroupSub=MaxSubMenu-1;                    
	                    i=MenuOnChk(); 
	                }while(i==0);
                    NewMenuStart();
                    CursorOff(); 
                }
                else if(EnterKey==2){
                    CusorDataDn();
					newmenu=0;
                }
                break;
        case    LEFTKEY:
                LadderKeyTime=0;
                if(EnterKey==1){
                    do{
	           			i=1;
                        if(LadderGroupSub==0){
							LadderGroup=(LadderGroup + 1) % max_group_sel; 	
						}
						else{
	                        LadderGroupSub=0;							
						}
                        NewMenuStart();
                        CursorOff(); 
                        i=GroupOnChk(); 

                    }while((i==0));
                }
                else if(EnterKey==2){
                    ShiftLeftCur();
                    CursorOn();
					newmenu=0;
                }
                break;
        case    RIGHTKEY:
                LadderKeyTime=0;
                if(EnterKey==1){
                    do{
                        i=1;
                        if(LadderGroupSub==0){
	                        if(LadderGroup>0)   	LadderGroup--;
	                        else                	LadderGroup=max_group_sel-1;
						}
						else{
	                        LadderGroupSub=0;							
						}

                        NewMenuStart();
                        CursorOff(); 
                        i=GroupOnChk(); 
                    }while((i==0));
                }
                else if(EnterKey==2){
                    ShiftRightCur();
                    CursorOn();
					newmenu=0;
                }
                break;
        case    ENTKEY:
				newmenu=0;
                LadderKeyTime=0;
                EnterKey++;
                if(EnterKey==2){
                    if(!EditOnCheck()){
                        EnterKey=1;
                        CursorOff(); 
                    }
                    else    CursorOn();
                }
                else if(EnterKey==3){
                    if(!bMoveCar){
						SaveVerify = 0x55;
                        ret=SaveData();
						SaveVerify = 0x0;
                    }
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
                LadderKeyTime=0;
                CusorDigitSet();
				newmenu=0;
                break;
        default:
                LadderKey = 0xff;
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




unsigned int   NewFlashData(void)
{
    unsigned int i,j;


    if((LadderKeyTime > 36000) && (LadderKeyTime < 36002)){        
		LadderKeyTime=36012;

        LadderGroup=0;
        LadderGroupSub=0;
        EnterKey=0;
    }	 



    KeyCheck();

    if(EnterKey==0){
        EnterKey=1;            

		LaderDsp();
        
        switch(LadderGroup){
            case    GROUP1_BLOCK:       
                GroupBaseAddr= (GROUP1_MENU01);
                Group1();
                break;
            case    GROUP2_BLOCK:       
                GroupBaseAddr= (GROUP2_MENU01);
                Group2();
                break;
            case    GROUP3_BLOCK:       
                GroupBaseAddr= (GROUP3_MENU01);
                Group3();
                break;
            case    GROUP4_BLOCK:       
                GroupBaseAddr= (GROUP4_MENU01);
                Group4();
                break;
		}



/*
        switch(LadderGroup){
            case    FLR_DSP_GROUP:
//                GroupBaseAddr=F_FlrDspCh;
//                FlrDspGroup(LadderGroupSub);
                break;
            case    FLR_GROUP:
//                GroupBaseAddr=F_TopFlr;
//                FlrGroup();
                break;
            case    TIMER_GROUP:
//                GroupBaseAddr=F_OpWtTm;
//                TimerGroup();
                break;
            case    SUB_DOOR_GROUP:
//                GroupBaseAddr=F_SubDoorFlr1;
//				DoorGroup();
                break;
            case    ONOFF1_GROUP:
//                GroupBaseAddr=F_NonService0;
//                OnOffGroup();
                break;
            case    ONOFF2_GROUP:
//                GroupBaseAddr=F_OnOff0;
//                OnOffGroup();
                break;
            case    NCNO1_GROUP:
//                GroupBaseAddr=EMG_PORT;
//                NcNoGroup();
                break;
            case    NCNO2_GROUP:
//                GroupBaseAddr=X0_PORT;
//                NcNoGroup();
                break;
            case    NCNO3_GROUP:
//                GroupBaseAddr=FAN_PORT;
//                NcNoGroup();
                break;
            case    IO_GROUP:
//                GroupBaseAddr=F_ManualSpeed;
//                IoGroup();
                break;
            case    GROUP1_BLOCK:       //save
//                GroupBaseAddr=F_Ver0;
                Group1();
                break;
            case    OPEN_WAIT_GROUP:
//                GroupBaseAddr=F_0506;
//                WaitFlrGroup();
                break;
            case    PARAMETER_GROUP:
//                GroupBaseAddr=ENCODER_PULSE;
//                ParameterGroup();
                break;
            case    INPORT1_GROUP:
//                GroupBaseAddr=EMG_PORT;
//                InportGroup();
                break;
            case    INPORT2_GROUP:
//                GroupBaseAddr=X0_PORT;
//                InportGroup();
                break;
            case    OUTPORT_GROUP:
//                GroupBaseAddr=FAN_PORT;
//                OutportGroup();
                break;
            case    ERROR_GROUP:
//                ErrorGroup(LadderGroupSub);
                break;
            case    EL_GROUP:
//                GroupBaseAddr=ENCODER_PULSE;
//                ELGroup();
                break;
            default:                
                break;
    
        }
*/

    }

   	LadderBuf[C_BASE_MEMORY]=LadderGroup;              
   	LadderBuf[C_OFFSET_MEMORY]=LadderGroupSub;          


	DefaultDisplay();




/*
	if(bMoveCar){
		SpeedDsp();
       	DefaultDisplay();
		EnterKey=0;
	}
    else if(LadderGroup==0){
		SpeedDsp();
        DefaultDisplay();
	}
*/


    LadderTime=0;




    return(0);
}






void   Ladder485Init(void)
{
    unsigned int i;

    LadderGroup=0;
    LadderGroupSub=0;


    NewMenuStart();

    for(i=0;i<MAX_LADDER_BUF-2;i++)   New485Ladder[i]=' ';

    New485Ladder[MAX_LADDER_BUF-1]=0x0;

}
