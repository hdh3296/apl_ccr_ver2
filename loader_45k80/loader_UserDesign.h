
// "640 byte(=64 * 10 ) 플레시 확보해 놓는다."  or  "160 long = (64/4) * 10"  
#define	MAX_FLASH_BLOCK_NM		1 // --> 버그 : 특정 개수 이상 블락 개수를 설정하면 Write 시 문제 생긴다.
// 전체 메뉴 갯수(현재 상태 제외)  
#define	MAX_MENU			50

#ifndef	__LOADER_USERDESIGN

#define	__LOADER_USERDESIGN

extern	uint16_t DefaultDisplay(void);



/////////////////////////////////////////////////////////////////////
////////////////////user message  set//////////////////////////////

// 상태 메시지  
const uint8_t StatusMessage[][17]	={
                                     	"Wait_Ready      ",      // 0                              
                                     	"Now Setting     ",      // 1                               
                                     	"Day Running     ",      // 2                               
                                     	"Twilight Running",      // 3                               
                                     	"Night Running   ",      // 4                               
                                     	"Day Not Set     ",      // 5                               
                                     	"Twilight Not Set",      // 6                               
                                     	"Night Not Set   ",      // 7                               
                                     	"CDS Error       ",      //000                               
                                     	"Right-Down      ",      //000                               
                                     	"Down            ",      //000                               
                                     	"Up              ",      //000
                                     	"Basket Home     ",      //000                               
                                     	"Inspect Stop    ",      //000                               
                                     	"InverterStop    ",      //001                               
                                      	"INVFloorStop    ",      //002                               		                                  
										"Emgency Stop    ",      //003                               
										"GOV Error       ",      //004                               
										"MotorOverheat   ",      //005                                                                           
                                    	};                                       

// 메뉴 이름 
const uint8_t GroupLineMessage[][17]={
                                    "USER:Version    ",// 1  // group0
                                    "USER:Display Sel",// 2 
                                    "USER:Initial    ",// 3  
                                    "USER:Read/Write ",// 4  
                                    "USER:FlashingCNT",// 5  
                                    "USER:FlashingRat",// 6  
                                    "USER:SEL SETMODE",// 6 
                                    "USER:SET VAL DAY",// 7  
                                    "USER:SET VAL TWL",// 8 
                                    "USER:SET VAL NIG",// 8 
                                    "USER:Max SET DAY",// 7  
                                    "USER:Max SET TWL",// 8 
                                    "USER:Max SET NIG",// 8 
                                    "USER:EveryOn DAY",// 7  
                                    "USER:EveryOn TWL",// 8 
                                    "USER:EveryOn NIG",// 8 
                                    "USER:SDutycycleD",// 8 
                                    "USER:SDutycycleT",// 8 
                                    "USER:SDutycycleN",// 8 
                                    "View:DuCy_D_SVal",// 9  // group1
                                    "View:DuCy_T_SVal",// 10 
                                    "View:DuCy_N_SVal",// 11  
                                    "View:GIJUN_Volt ",// 12  
                                    "BAS1:VIB_TIME   ",// 13  
                                    "BAS1:REPEAT_CNT ",// 14  
                                    "BAS1:Not Use1   ",// 15  
                                    "BAS1:Not Use2   ",// 16 
                                    "BAS2:X_LENGTH   ",// 17  //group2
                                    "BAS2:Z_LENGTH   ",// 18 
                                    "BAS2:X_Z_LENGTH ",// 19  
                                    "BAS2:Z_X_LENGTH ",// 20  
                                    "BAS2:VIB_TIME   ",// 21  
                                    "BAS2:REPEAT_CNT ",// 22  
                                    "BAS2:Not Use1   ",// 23  
                                    "BAS2:Not Use2   ",// 24 
                                    "BAS3:X_LENGTH   ",// 25  // group3
                                    "BAS3:Z_LENGTH   ",// 26 
                                    "BAS3:X_Z_LENGTH ",// 27  
                                    "BAS3:Z_X_LENGTH ",// 28  
                                    "BAS3:VIB_TIME   ",// 29  
                                    "BAS3:REPEAT_CNT ",// 30  
                                    "BAS3:Not Use1   ",// 31  
                                    "BAS3:Not Use2   ",// 32 

                                    "Running Basket  ",// 0   // default group
                  			};


const uint8_t myVersion[][17]={
                                    "v2.4.0.8        ", // 버전 정보 표시 
                  			};




const uint8_t  DefaultMsg[][17] ={
                                    	"APL CCR         ",// 0
										"APL CCR         "							
										};



const uint8_t MsgSelModeSel[][17]={
                                    "Running Mode  ",// 0  
                                    "Set DAY Mode  ",// 1 
                                    "Set TWL Mode  ",// 2  
                                    "Set NIG Mode  ",//3  
                  			};

const uint8_t MsgSelEveryOnSetD[][17]={
                                    "Flashing      ",// 0  
                                    "Every On      ",// 1 
                  			};

const uint8_t MsgSelEveryOnSetT[][17]={
                                    "Flashing      ",// 0  
                                    "Every On      ",// 1 
                  			};

const uint8_t MsgSelEveryOnSetN[][17]={
                                    "Flashing      ",// 0  
                                    "Every On      ",// 1 
                  			};





const uint8_t DefaultMsgSel[][17]={
                                    "Cur Status    ",// 0  
                                    "c-Mem Display ",// 1 
                                    "i-Mem Display ",// 2  
                                    "l-Mem Display ",// 3        
                                    "Not Use4      ",// 4  
                                    "Not Use5      ",// 5  
                                    "Not Use6      ",// 6  
                                    "Not Use7      ",// 7 
                                    "Not Use8      ",// 8 
                                    "Not Use9      ",// 9 
                                    "Not Use10     ",// 10 
                  			};

// Flash Read / Write 
const uint8_t FlashMsgSel[][17]={
                                    "Rd/Wr Ready.. ",// 0  
                                    "Read :To Load ",// 1 
                                    "Write:To Main ",// 2  
                                    "Not Use2      ",// 3  
                                    "Not Use3      ",// 4  
                                    "Not Use4      ",// 5  
                                    "Not Use5      ",// 6  
                                    "Not Use6      ",// 7  
                                    "Not Use7      ",// 8 
                                    "Not Use8      ",// 9 
                                    "Not Use9      ",// 9 
                  			};




/////////////////////////////////////////////////////////////////////
////////////////////memory address set//////////////////////////////
// 저장할 번지 
#define  F_VERSION			ByteData001 					// 1
#define  F_WORK_MODE		ByteData002        				// 1
#define  F_DEFAULT_DSP		ByteData003           			// 1
#define  F_FLASH_COPY		ByteData004           			// 1
#define  F_INITIAL			ByteData008           			// 1

#define  F_DUTY_CNT			ByteData009           			// 1
#define  F_DUTY_RATE		ByteData010           			// 1

#define  F_SETMODE_SEL		ByteData011

#define  F_EveryOnSetD		ByteData012
#define  F_EveryOnSetT		ByteData013
#define  F_EveryOnSetN		ByteData014

#define  F_bSave_GIJUN		ByteData015


#define  F_SETCURR_DAY		IntzData009           			// 1
#define  F_SETCURR_TWL		IntzData010           			// 1
#define  F_SETCURR_NIG		IntzData011           			// 1

#define  F_MSETCURR_DAY		IntzData012           			// 1
#define  F_MSETCURR_TWL		IntzData013           			// 1
#define  F_MSETCURR_NIG		IntzData014           			// 1

#define  F_SET_DUTYCYCLED	IntzData015           			
#define  F_SET_DUTYCYCLET	IntzData016	
#define  F_SET_DUTYCYCLEN	IntzData017	

#define  F_SET_stDUTYCYCLE_D	IntzData018	
#define  F_SET_stDUTYCYCLE_T	IntzData019
#define  F_SET_stDUTYCYCLE_N	IntzData020

#define  F_SET_GIJUN_V	IntzData021	












#define  F_BAS1_X_LENGTH	IntzData051           			// 1
#define  F_BAS1_Z_LENGTH	IntzData052           			// 1
#define  F_BAS1_X_Z_LENGTH	IntzData053           			// 1
#define  F_BAS1_Z_X_LENGTH	IntzData054           			// 1
#define  F_BAS1_VIB_TIME	IntzData055           			// 1
#define  F_BAS1_REPETE		IntzData056           			// 1
#define  F_BAS1_NOT_USE1	IntzData057           			// 1
#define  F_BAS1_NOT_USE2	IntzData058           			// 1

#define  F_BAS2_X_LENGTH	IntzData059           			// 1
#define  F_BAS2_Z_LENGTH	IntzData060           			// 1
#define  F_BAS2_X_Z_LENGTH	IntzData061           			// 1
#define  F_BAS2_Z_X_LENGTH	IntzData062           			// 1
#define  F_BAS2_VIB_TIME	IntzData063           			// 1
#define  F_BAS2_REPETE		IntzData064           			// 1
#define  F_BAS2_NOT_USE1	IntzData065           			// 1
#define  F_BAS2_NOT_USE2	IntzData066           			// 1

#define  F_BAS3_X_LENGTH	IntzData067           			// 1
#define  F_BAS3_Z_LENGTH	IntzData068           			// 1
#define  F_BAS3_X_Z_LENGTH	IntzData069           			// 1
#define  F_BAS3_Z_X_LENGTH	IntzData070           			// 1
#define  F_BAS3_VIB_TIME	IntzData071           			// 1
#define  F_BAS3_REPETE		IntzData072           			// 1
#define  F_BAS3_NOT_USE1	IntzData073           			// 1
#define  F_BAS3_NOT_USE2	IntzData074           			// 1






#define  F_TEST_LONG		longData101           			// 1

////////////////////////////////////////////////////////////////////////



// 번지 변수 명을 정의 하였다. 
#define  cF_VERSION				cF_ByteData(F_VERSION)
#define  cF_WORK_MODE			cF_ByteData(F_WORK_MODE)
#define  cF_DEFAULT_DSP			cF_ByteData(F_DEFAULT_DSP)
#define  cF_FLASH_COPY			cF_ByteData(F_FLASH_COPY)
#define  cF_INITIAL				cF_ByteData(F_INITIAL)

#define  cF_BLK_1MIN_CNT			cF_ByteData(F_DUTY_CNT)
#define  cF_BLK_DUTYRATE			cF_ByteData(F_DUTY_RATE)

#define  cF_SETMODE_SEL			cF_ByteData(F_SETMODE_SEL)

#define  cF_EveryOnSetD			cF_ByteData(F_EveryOnSetD)
#define  cF_EveryOnSetT			cF_ByteData(F_EveryOnSetT)
#define  cF_EveryOnSetN			cF_ByteData(F_EveryOnSetN)

#define  cF_bSave_GIJUN			cF_ByteData(F_bSave_GIJUN)


#define  cF_SETCURR_DAY			iF_IntData(F_SETCURR_DAY)
#define  cF_SETCURR_TWL			iF_IntData(F_SETCURR_TWL)
#define  cF_SETCURR_NIG			iF_IntData(F_SETCURR_NIG)

#define  cF_MaxSetA_DAY			iF_IntData(F_MSETCURR_DAY)
#define  cF_MaxSetA_TWL			iF_IntData(F_MSETCURR_TWL)
#define  cF_MaxSetA_NIG			iF_IntData(F_MSETCURR_NIG)

#define  cF_SET_DUTYCYCLED			iF_IntData(F_SET_DUTYCYCLED)
#define  cF_SET_DUTYCYCLET			iF_IntData(F_SET_DUTYCYCLET)
#define  cF_SET_DUTYCYCLEN			iF_IntData(F_SET_DUTYCYCLEN)

#define  cF_SET_stDUTYCYCLE_D		iF_IntData(F_SET_stDUTYCYCLE_D)
#define  cF_SET_stDUTYCYCLE_T		iF_IntData(F_SET_stDUTYCYCLE_T)
#define  cF_SET_stDUTYCYCLE_N		iF_IntData(F_SET_stDUTYCYCLE_N)

#define  cF_SET_F_SET_GIJUN_V			iF_IntData(F_SET_GIJUN_V)









#define  iF_BAS1_X_LENGTH		iF_IntData(F_BAS1_X_LENGTH)
#define  iF_BAS1_Z_LENGTH		iF_IntData(F_BAS1_Z_LENGTH)
#define  iF_BAS1_X_Z_LENGTH		iF_IntData(F_BAS1_X_Z_LENGTH)
#define  iF_BAS1_Z_X_LENGTH		iF_IntData(F_BAS1_Z_X_LENGTH)
#define  iF_BAS1_VIB_TIME		iF_IntData(F_BAS1_VIB_TIME)
#define  iF_BAS1_REPETE			iF_IntData(F_BAS1_REPETE)
#define  iF_BAS1_NOT_USE1		iF_IntData(F_BAS1_NOT_USE1)
#define  iF_BAS1_NOT_USE2		iF_IntData(F_BAS1_NOT_USE2)


#define  iF_BAS2_X_LENGTH		iF_IntData(F_BAS2_X_LENGTH)
#define  iF_BAS2_Z_LENGTH		iF_IntData(F_BAS2_Z_LENGTH)
#define  iF_BAS2_X_Z_LENGTH		iF_IntData(F_BAS2_X_Z_LENGTH)
#define  iF_BAS2_Z_X_LENGTH		iF_IntData(F_BAS2_Z_X_LENGTH)
#define  iF_BAS2_VIB_TIME		iF_IntData(F_BAS2_VIB_TIME)
#define  iF_BAS2_REPETE			iF_IntData(F_BAS2_REPETE)
#define  iF_BAS2_NOT_USE1		iF_IntData(F_BAS2_NOT_USE1)
#define  iF_BAS2_NOT_USE2		iF_IntData(F_BAS2_NOT_USE2)

#define  iF_BAS3_X_LENGTH		iF_IntData(F_BAS3_X_LENGTH)
#define  iF_BAS3_Z_LENGTH		iF_IntData(F_BAS3_Z_LENGTH)
#define  iF_BAS3_X_Z_LENGTH		iF_IntData(F_BAS3_X_Z_LENGTH)
#define  iF_BAS3_Z_X_LENGTH		iF_IntData(F_BAS3_Z_X_LENGTH)
#define  iF_BAS3_VIB_TIME		iF_IntData(F_BAS3_VIB_TIME)
#define  iF_BAS3_REPETE			iF_IntData(F_BAS3_REPETE)
#define  iF_BAS3_NOT_USE1		iF_IntData(F_BAS3_NOT_USE1)
#define  iF_BAS3_NOT_USE2		iF_IntData(F_BAS3_NOT_USE2)






#define  lF_TEST_LONG			lF_LongData(F_TEST_LONG)


////////////////////////////////////////////////////////
/////////////sram memory set- char type/////////////////
////////////////////////////////////////////////////////
#define		UpButtonTime_8	0  	
#define		msec100_8	1  	
#define		sec1_8				2  	
#define		MotorSeq_8			3  	
#define		BasketNm_8			4  	
#define		RepeateCounter_8	5  	
#define		LeftRightCurpt_8	6  	
#define		UpDownCurpt_8		7  	

#define		VARIABLE_8_END  	8



/////////////////////////////////////////////////////////////////
/////////////sram memory set- int type/////////////////////////
/////////////////////////////////////////////////////////////////
#define		viewSET_DUTYCYCLE		0
#define		viewIn_Current			1
#define		viewCurDAY_TWL_NIG		2	
#define		ReverseTime0_16			3	
#define		ReverseTime1_16			4

#define		ViewZeroTimer			0

#define		ViewBlk			0


#define		VARIABLE_16_END  		5



#define		VARIABLE_32_END  		1

#endif


