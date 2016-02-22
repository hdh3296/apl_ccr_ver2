
// "640 byte(=64 * 10 ) 플레시 확보해 놓는다."  or  "160 long = (64/4) * 10"  
#define	MAX_FLASH_BLOCK_NM		10  

// 전체 메뉴 갯수(현재 상태 제외)  
#define	MAX_MENU			50

#ifndef	__LOADER_USERDESIGN

#define	__LOADER_USERDESIGN

extern	uint16_t DefaultDisplay(void);



/////////////////////////////////////////////////////////////////////
////////////////////user message  set//////////////////////////////

// 상태 메시지  
const uint8_t StatusMessage[][17]	={
                                     	"Wait_Ready      ",      //000                               
                                     	"System Home.... ",      //000                               
                                     	"Basket1 Home    ",      //000                               
                                     	"Basket  Ready   ",      //000                               
                                     	"Vibration       ",      //000                               
                                     	"Down            ",      //000                               
                                     	"Up              ",      //000                               
                                     	"Up-Right        ",      //000                               
                                     	"Right           ",      //000                               
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
                                    "USER:Basket Sel ",// 2 
                                    "USER:Display Sel",// 3  
                                    "USER:Flash      ",// 4  
                                    "USER:Not Use4   ",// 5  
                                    "USER:Not Use5   ",// 6  
                                    "USER:Not Use6   ",// 7  
                                    "USER:Not Use7   ",// 8 
                                    "BAS1:X_LENGTH   ",// 9  // group1
                                    "BAS1:Z_LENGTH   ",// 10 
                                    "BAS1:X_Z_LENGTH ",// 11  
                                    "BAS1:Z_X_LENGTH ",// 12  
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




const uint8_t  DefaultMsg[][17] ={
                                    	"Running Basket  ",// 0
										"Ready...        "							
										};



const uint8_t BasketWorkSel[][17]={
                                    "BA1-BA2-BA3   ",// 0  
                                    "BA1-BA2       ",// 1 
                                    "BA1-BA3       ",// 2  
                                    "BA2-BA3       ",//3  
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

#define  F_BAS1_X_LENGTH	IntzData009           			// 1
#define  F_BAS1_Z_LENGTH	IntzData010           			// 1
#define  F_BAS1_X_Z_LENGTH	IntzData011           			// 1
#define  F_BAS1_Z_X_LENGTH	IntzData012           			// 1
#define  F_BAS1_VIB_TIME	IntzData013           			// 1
#define  F_BAS1_REPETE		IntzData014           			// 1
#define  F_BAS1_NOT_USE1	IntzData015           			// 1
#define  F_BAS1_NOT_USE2	IntzData016           			// 1


#define  F_BAS2_X_LENGTH	IntzData017           			// 1
#define  F_BAS2_Z_LENGTH	IntzData018           			// 1
#define  F_BAS2_X_Z_LENGTH	IntzData019           			// 1
#define  F_BAS2_Z_X_LENGTH	IntzData020           			// 1
#define  F_BAS2_VIB_TIME	IntzData021           			// 1
#define  F_BAS2_REPETE		IntzData022           			// 1
#define  F_BAS2_NOT_USE1	IntzData023           			// 1
#define  F_BAS2_NOT_USE2	IntzData024           			// 1

#define  F_BAS3_X_LENGTH	IntzData025           			// 1
#define  F_BAS3_Z_LENGTH	IntzData026           			// 1
#define  F_BAS3_X_Z_LENGTH	IntzData027           			// 1
#define  F_BAS3_Z_X_LENGTH	IntzData028           			// 1
#define  F_BAS3_VIB_TIME	IntzData029           			// 1
#define  F_BAS3_REPETE		IntzData030           			// 1
#define  F_BAS3_NOT_USE1	IntzData031           			// 1
#define  F_BAS3_NOT_USE2	IntzData032           			// 1


#define  F_TEST_LONG		longData033           			// 1

////////////////////////////////////////////////////////////////////////



// 번지 변수 명을 정의 하였다. 
#define  cF_VERSION				cF_ByteData(F_VERSION)
#define  cF_WORK_MODE			cF_ByteData(F_WORK_MODE)
#define  cF_DEFAULT_DSP			cF_ByteData(F_DEFAULT_DSP)
#define  cF_FLASH_COPY			cF_ByteData(F_FLASH_COPY)
#define  cF_INITIAL				cF_ByteData(F_INITIAL)


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


#define  lF_TEST_LONG			lF_LongData(LongData033)


////////////////////////////////////////////////////////
/////////////sram memory set- char type/////////////////
////////////////////////////////////////////////////////
#define		UpButtonTime_8		0  	
#define		msec100_8			1  	
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
#define		StartKeyChartTime_16	0
#define		VibTime_16				1
#define		LeftRightMovePulse_16	2	
#define		UpDownMovePulse_16		3	
#define		ReverseTime_16			4

#define		VARIABLE_16_END  		5



#define		VARIABLE_32_END  		1

#endif


