

const unsigned char blinkx[]        	={"                "};  

const unsigned char StatusMessage[][17]	={
                                     	"Inspect Stop    ",      //000                               
                                     	"InverterStop    ",      //001                               
                                      	"INVFloorStop    ",      //002                               		                                  
										"Emgency Stop    ",      //003                               
										"GOV Error       ",      //004                               
										"MotorOverheat   ",      //005                                                                           
										"Slip Stop       ",      //006                               
										"ULS Stop        ",      //007                                                                     
										"DLS Stop        ",      //008                               
										"LuLd Off Stop   ",      //009
										"NextFloorStop   ",      //010
										"InPort Error    ",      //011
										"HallDoor Stop   ",      //012
										"CarDoor  Stop   ",      //013
										"Relevel Error   ",      //014
										"NoEncoderPulse  ",      //015
										"EncoderAB Err   ",      //016
										"SpeedPortErr    ",      //017
										"Min Dec Length  ",      //018
										"System Error    ",      //019
										"AtButton Off    ",      //020
										"Flr Match Err   ",      //021
										"Inv Comm Err    ",      //022
										"BkMgt Err       ",      //023
										"Bk On/Off Err   ",      //024
										"Sus Error       ",      //025
										"Sds Error       ",      //026
										"LuLdChangeErr   ",      //027 
										"Ld On Error	   ",      //028
										"Ld Off Error    ",      //029
										"Lu On Error     ",      //030
										"Lu Off Error    ",      //031
										"LuLdOnOff Err   ",      //032
										"CarDoorJumper   ",      //033                                                                           
										"HallDoorJump    ",      //034
										"CarHallJumper   ",      //035
										"Earthquake      ",      //036
										"DZ Error        ",      //037
										"No Close End    ",      //038
										"039             ",      //039
										"040             ",      //040
										"041             ",      //041
										"Tunning..Wait...",      //042
										"FHM_Error       ",      //043
										"044             ",      //044
										"045             ",      //045
										"OverLoad Stop   ",      //046
										"Parking Mode    ",      //047
										"Fire            ",      //048
										"Water_Sensing   ",      //049                                       
										"050             ",      //050
										"VIP Drive       ",      //051                                     
										"FHM_Mode        ",      //052                                     
										"Manual Up       ",      //053
										"Manual Dn       ",      //054
										"Manual Mode     ",      //055
										"Safety Open     ",      //056
										"Open Door       ",      //057
										"Close Door      ",      //058                                     
										"Auto Up         ",      //059                                     
										"Auto Dn         ",      //060                                     
										"Slow Speed      ",      //061
										"Wait LuLd       ",      //062
										"063             ",      //063
										"No Define       ",      //064
										"Auto Ready      "       //065
                                    	};                                       


const unsigned char GroupLineMessage[][17]={
                                    "FL:00           ",//0
///////////////////////////////////////////////////////////                                                                                                           
                                    "USER:Version    ",//1  
                                    "USER:BoardId    ",//2 
                                    "USER:Passward   ",//3  
                                    "USER:UserLamp1  ",//4  
                                    "USER:UserLamp2  ",//5  
                                    "USER:SerialNm   ",//6  
                                    "USER:Normal Dsp ",//7  
                                    "USER:DriveMethod",//8 
                                    "USER:Fhm Run    ",//9 
                                    "USER:SubMenu On ",//10 
                                    "USER:Engineer Nm",//11 
                                    "USER:Tt Use Time",//12 
                                    "USER:Init Data  ",//13 
                                    "USER:Group Nm   ",//14 
                                    "USER:Local Nm   ",//15 
                                    "USER:Inv InBd Tp",//16
                                    "USER:Call(c-f-f)",//17
                                    "USER:hh-mm-ss   ",//18 
                                    "USER:yy-mm-dd   ",//19
                                    "USER:ErrStCnt   ",//20  
                                    "USER:Company    ",//21									  
                                    "USER:OutDate    ",//22  
                                    "USER:UserLamp3  ",//23  
                                    "USER:UserLamp4  ",//24  
                                    "USER:C-K-H-O-B-R",//25 
                                    "USER:User4      ",//26 
                                    "USER:User5      ",//27 
                                    "USER:User6      ",//28 
                                    "USER:F-Error(00)",//29 
                                    "USER:SenPosi(00)",//30 
                                    "USER:System Mode",//31  
                                    "USER: Stop Pulse",//32 
///////////////////////////////////////////////////////////                                    
///////////////////////////////////////////////////////////   
                                                                    
                                    "TMR:Op Wait Time",// 1
                                    "TMR:Op Total Tm ",// 2
                                    "TMR:No Use Time ",// 3
                                    "TMR:NextFlr Time",// 4
                                    "TMR:LuLdOff Time",// 5
                                    "TMR:Fan Off Time",// 6
                                    "TMR:Lit Off Time",// 7
                                    "TMR:OpClWaitTime",// 8
                                    "TMR:PowerRunTime",// 9
                                    "TMR:Dir Set Time",//10
                                    "TMR:Voice OnTime",//11
                                    "TMR:Brk Mgt Time",//12
                                    "TMR:ReOpen  Time",//13
                                    "TMR:P4  On  Time",//14
                                    "TMR:U/D On  Time",//15
                                    "TMR:Bk2 On  Time",//16
                                    "TMR:Bk1 On  Time",//17
                                    "TMR:Run On  Time",//18
                                    "TMR:Run Off Time",//19
                                    "TMR:Bk1 Off Time",//20
                                    "TMR:Bk2 Off Time",//21
                                    "TMR:U/D Off Time",//22
                                    "TMR:P4  Off Time",//23
                                    "TMR:Sol On  Time",//24
                                    "TMR:Door St Time",//25
                                    "TMR:Stop9   Time",//26
                                    "TMR:Stop10  Time",//27
                                    "TMR:Stop11  Time",//28
                                    "TMR:Stop12  Time",//29
                                    "TMR:Stop13  Time",//30
                                    "TMR:Stop14  Time",//31
                                    "TMR:Stop15  Time",//32            
/*                                                                               
///////////////////////////////////////////////////////////                                                                                                           
///////////////////////////////////////////////////////////                                                                                                           
                                    "ONOFF2:FHM Chk  ",//1 
                                    "ONOFF2:DrJmpChk ",//2 
                                    "ONOFF2:EncoderPh",//3 
                                    "ONOFF2:WardPrior",//4  
                                    "ONOFF2:NonStop  ",//5  
                                    "ONOFF2:OpenTotal",//6  
                                    "ONOFF2:WaitTotal",//7  
                                    "ONOFF2:ClosTotal",//8  
                                    "ONOFF2:C_Dr1 Chk",//9  
                                    "ONOFF2:C_Dr2 Chk",//10  
                                    "ONOFF2:H_Dr1 Chk",//11
                                    "ONOFF2:H_Dr2 Chk",//12 
                                    "ONOFF2:S_Sft Chk",//13
                                    "ONOFF2:MgtMonChk",//14
                                    "ONOFF2:Encod Chk",//15
                                    "ONOFF2:ReleveChk",//16
                                    "ONOFF2:OilLopeTy",//17
                                    "ONOFF2:1 CallChk",//18
                                    "ONOFF2:ManSusChk",//19
                                    "ONOFF2:BrkMonChk",//20
                                    "ONOFF2:KidKeyClr",//21
                                    "ONOFF2:F_CarKey ",//22
                                    "ONOFF2:SingleCar",//23
                                    "ONOFF2:OpOutSet ",//24
                                    "ONOFF2:SftUse RL",//25
                                    "ONOFF2:Floor Sel",//26
                                    "ONOFF2:RunningOp",//27
                                    "ONOFF2:Not Use  ",//28
                                    "ONOFF2:Not Use  ",//29
                                    "ONOFF2:Not Use  ",//30
                                    "ONOFF2:Copy_Encd",//31
                                    "ONOFF2:Work Mode",//32
///////////////////////////////////////////////////////////                          
///////////////////////////////////////////////////////////                          
                                    "NcNo1:EMG       ",//1  
                                    "NcNo1:PRK       ",//2  
                                    "NcNo1:AT        ",//3  
                                    "NcNo1:UB        ",//4  
                                    "NcNo1:DB        ",//5  
                                    "NcNo1:OLS       ",//6  
                                    "NcNo1:GS        ",//7  
                                    "NcNo1:HDS       ",//8  
                                    "NcNo1:SUS       ",//9  
                                    "NcNo1:SDS       ",//10 
                                    "NcNo1:SFT       ",//11 
                                    "NcNo1:OVL       ",//12 
                                    "NcNo1:ULS       ",//13 
                                    "NcNo1:DLS       ",//14 
                                    "NcNo1:LU        ",//15 
                                    "NcNo1:LD        ",//16 
                                    "NcNo1:RG        ",//17 
                                    "NcNo1:BAT       ",//18 
                                    "NcNo1:PAS       ",//19 
                                    "NcNo1:FIR       ",//20 
                                    "NcNo1:WAT       ",//21 
                                    "NcNo1:FUL       ",//22 
                                    "NcNo1:MM        ",//23 
                                    "NcNo1:TH        ",//24
                                    "NcNo1:FR1       ",//25 
                                    "NcNo1:FR2       ",//26
                                    "NcNo1:BMR       ",//27 
                                    "NcNo1:BML       ",//28
                                    "NcNo1:SU1       ",//29 
                                    "NcNo1:SD1       ",//30
                                    "NcNo1:DZ        ",//31 
                                    "NcNo1:INV       ",//32 
///////////////////////////////////////////////////////////                                                                                                           
///////////////////////////////////////////////////////////                                                                                                           
                                    "INP1:EMG        ",//1  
                                    "INP1:PRK        ",//2  
                                    "INP1:AT         ",//3  
                                    "INP1:UP         ",//4  
                                    "INP1:DN         ",//5  
                                    "INP1:OLS        ",//6  
                                    "INP1:GS         ",//7  
                                    "INP1:HDS        ",//8  
                                    "INP1:SUS        ",//9  
                                    "INP1:SDS        ",//10 
                                    "INP1:SFT        ",//11 
                                    "INP1:OVL        ",//12 
                                    "INP1:ULS        ",//13 
                                    "INP1:DLS        ",//14 
                                    "INP1:LU         ",//15 
                                    "INP1:LD         ",//16 
                                    "INP1:RG         ",//17 
                                    "INP1:BAT        ",//18 
                                    "INP1:PAS        ",//19 
                                    "INP1:FIR        ",//20 
                                    "INP1:WAT        ",//21 
                                    "INP1:FUL        ",//22 
                                    "INP1:MM         ",//23 
                                    "INP1:TH         ",//24
                                    "INP1:FR1        ",//25 
                                    "INP1:FR2        ",//26
                                    "INP1:BMR        ",//27 
                                    "INP1:BML        ",//28
                                    "INP1:SU1        ",//29 
                                    "INP1:SD1        ",//30
                                    "INP1:DZ         ",//31 
                                    "INP1:INV        ",//32 
///////////////////////////////////////////////////////////                                                                                                           
///////////////////////////////////////////////////////////                                                                                                   
                                    "ER:NO ERRORE(01)",//1  
                                    "ER:NO ERRORE(02)",//2  
                                    "ER:NO ERRORE(03)",//3  
                                    "ER:NO ERRORE(04)",//4  
                                    "ER:NO ERRORE(05)",//5  
                                    "ER:NO ERRORE(06)",//6  
                                    "ER:NO ERRORE(07)",//7  
                                    "ER:NO ERRORE(08)",//8  
                                    "ER:NO ERRORE(09)",//9 
                                    "ER:NO ERRORE(10)",//10 
                                    "ER:NO ERRORE(11)",//11 
                                    "ER:NO ERRORE(12)",//12 
                                    "ER:NO ERRORE(13)",//13 
                                    "ER:NO ERRORE(14)",//14 
                                    "ER:NO ERRORE(15)",//15 
                                    "ER:NO ERRORE(16)",//16 
                                    "ER:NO ERRORE(17)",//17 
                                    "ER:NO ERRORE(18)",//18 
                                    "ER:NO ERRORE(19)",//19 
                                    "ER:NO ERRORE(20)",//20 
                                    "ER:NO ERRORE(21)",//21 
                                    "ER:NO ERRORE(22)",//22 
                                    "ER:NO ERRORE(23)",//23 
                                    "ER:NO ERRORE(24)",//24 
                                    "ER:NO ERRORE(25)",//25 
                                    "ER:NO ERRORE(26)",//26 
                                    "ER:NO ERRORE(27)",//27 
                                    "ER:NO ERRORE(28)",//28 
                                    "ER:NO ERRORE(29)",//29 
                                    "ER:NO ERRORE(30)",//30 
                                    "ER:NO ERRORE(31)",//31 
                                    "ER:NO ERRORE(32)",//32 
*/
                                };





						
/*			   

//digitData == 1 
const unsigned char ElevOnOffSetMessage[ELEV_ONOFF_MESSAGE_CNT][12]={   
                                    "FHM No Good",
                                    "Chk DoorJmp",
                                    "B Phase    ", 
                                    "Call But On",   
                                    "NonStop On ",   
                                    "Op TtTm On ",   
                                    "WaitTtTm On",                                      
                                    "Cl TtTm On ",   
                                    "CarDr1  Use",   
                                    "CarDr2  Use",   
                                    "HolDr1  Use",   
                                    "HolDr2  Use",   
                                    "S_Sfty  Use",   
                                    "Mgt Mon On ",   
                                    "Encoder Use",   
                                    "Relevel On ",   
                                    "Lope  Type ",   
                                    "OneCall  On",   
                                    "M/Sus  Stop",   
                                    "Brk Mon On ",   
                                    "KidsClr On ",   
                                    "F_CarKey On",   
                                    "Single Car ",   
                                    "Op Out On  ",   
                                    "Sft Comm On",   
                                    " BCD Floor ",
                                    "Run_Op  On ",   
                                    "Reserve5   ",   
                                    "Reserve4   ",   
                                    "Reserve3   ",   
                                    "EncCopy On",   
                                    "Manual Job ",   
                                };


//digitData == 0 
const unsigned char ElevOnOffResetMessage[ELEV_ONOFF_MESSAGE_CNT][12]={
                                    "FHM Good   ",
                                    "NoChk DrJmp",
                                    "A Phase    ", 
                                    "Cur Ward On",    
                                    "NonStop Off",   
                                    "Op TtTm Off",   
                                    "WaitTtTmOff",                                      
                                    "Cl TtTm Off",   
                                    "C_Dr1 N_Use",   
                                    "C_Dr2 N_Use",   
                                    "H_Dr1 N_Use",   
                                    "H_Dr2 N_Use",   
                                    "S_Sft N_Use",   
                                    "Mgt Mon Off",   
                                    "Encod N_Use",   
                                    "Relevel Off",   
                                    "Oil  P_Type",   
                                    "OneCall Off",   
                                    "M/SusNoStop",   
                                    "Brk Mon Off",   
                                    "KidsClr Off",   
                                    "F_CarKeyOff",   
                                    "Multi Car  ",   
                                    "Op Out Off ",   
                                    "Sft CommOff",   
                                    "DirectFloor",   
                                    "Run_Op Off ",   
                                    "Reserve5   ",   
                                    "Reserve4   ",   
                                    "Reserve3   ",   
                                    "EncCopy Off",   
                                    "Auto Ready ",   
                                };





const unsigned char IOPortMessage[IO_PORT_MESSAGE_CNT][12]={
                                    "-----------",//0
                                    "---------P1",//1
                                    "-------P2--",//2
                                    "-------P2P1",//3
                                    "-----P3----",//4
                                    "-----P3--P1",//5
                                    "-----P3P2--",//6
                                    "-----P3P2P1",//7
                                    "---P4------",//8
                                };

const unsigned char ElevSpeedMessage_spd3[ELEV_SPEED_MESSAGE_CNT_SPD3][12]={
                                    "Not Use    ",    
                                    "Dec/Spd_M_H",
                                    "Dec/Spd_H  ",
                                    "Low_Spd    ",
                                    "Mid_Spd    ", 
                                };

const unsigned char AUTO_LANDING_MSG[AUTO_LANDING_MESSAGE_CNT][12]={
                                    "Not Use    ",    
                                    "YK_ALanding",
//                                    "DS_ALanding",
                                };

const unsigned char ElevSpeedMessage[ELEV_SPEED_MESSAGE_CNT][12]={
                                    "SPEED30    ",
                                    "SPEED45    ",
                                    "SPEED60    ", 
                                    "SPEED90    ",   
                                    "SPEED105   ",    
                                    "SPEED120   ",       
                                    "SPEED150   ",       
                                    "SPEED180   ",       
                                    "SPEED210   ",
                                };




const unsigned char ElevBdIdMessage[ELEV_BD_ID_MESSAGE_CNT][12]={
                                    "LG  Elevato",  //0
                                    "I/O Elevato",  //1
                                    "D_F Elevato",  //2
                                    "LG  Baggage",  //3
                                    "I/O Baggage",  //4
                                    "D_F Baggage",  //5
                                    "LG  CarLift",  //6
                                    "I/O CarLift",  //7
                                    "D_F CarLift",  //8
                                    "Reserve1   ",
                                };


const unsigned char SystemSetMessage[SYSTEM_SET_MESSAGE_CNT][14]={		
                                    "0.O_Law/O_spd",  //0
                                    "1.N_Law/O_spd",  //1
                                    "2.O_Law/N_spd",  //2
                                    "3.N_Law/N_spd",  //3
                                };


const unsigned char SensorPositionMessage[SENSOR_POSITION_MESSAGE_CNT][17]={		
                                    "29.ULS:0000-0000",  //0
                                    "29.SUS:0000-0000",  //1
                                    "29.SU1:0000-0000",  //2
                                    "29.X0 :0000-0000",  //3
                                    "29.DLS:0000-0000",  //3
                                    "29.SDS:0000-0000",  //1
                                    "29.SD1:0000-0000",  //2
                                    "29.X1 :0000-0000",  //3
                                    "29.nu :0000-0000",  //1
                                    "29.nu :0000-0000",  //2
                                };




const unsigned char FinalErrMessage[FINAL_ERR_DSP_MESSAGE_CNT][17]={		
                                    "28.00/00-00.    ",  //0
                                    "28.No Error     ",  //1
                                    "28.00/00        ",  //2
                                    "28.Puls:00000000",  //3
                                    "28.mpm :000.0   ",  //4
                                    "28.D/T:0000/0000",  //5
                                    "28.Up  :00000000",  //6
                                    "28.Op  :00000000",  //7
                                    "28.FAN :00000000",  //8
                                    "28.Emg :00000000",  //9
                                    "28.SUS :00000000",  //10
                                    "28.RG  :00000000",  //11
                                    "28.FR1 :00000000",  //12
                                    "28.X0  :00000000",  //13
                                    "28.FS0 :00000000",  //14
                                };



const unsigned char UserLampMessage[USER_LAMP_MESSAGE_CNT][12]={
                                      "AUTO       ",                                      
                                      "INSPECTION ",                                      
                                      "OVERLOAD   ",                                      
                                      "FIRE       ",                                                                            
                                      "EMERGENCY  ",
                                      "PARKING    ",
                                      "VIP        ",
                                      "USE LAMP   ",
                                      "FULL LAMP  ",
                                      "POWER SAVE ",
                                      "NOT USE    "                                      
                                    };                                       


const unsigned char DriveMethodMessage[3][12]={
                                      "All Drive..",                                      
                                      "1,3,5,7... ",    //È¦¼ö                                   
                                      "2,4,6,8... ",    //Â¦¼ö                                   
                                    };                                       

const unsigned char DoorOnOffMessage[DOOR_SEL_MESSAGE_CNT][12]={
                                      "Not Door   ",    //no door                                 
                                      "MainDoor   ",    //main door                                   
                                      "Sub Door   ",    //sub door                                   
                                      "MainSubDoor",    //main sub door                                   
                                    };                                       


const unsigned char FhmMessage[][12]={
                                      "Fhm Stop   ",                                      
                                      "Fhm Start  ",                                       
                                    };                                       







const unsigned char PcbTypeMessage[2][12]={
                                      "Ext Bd Type",   // extbd/inbd                                    
                                      "In_Bd Type ",                                      
                                    };                                       


const unsigned char InitMessage[INIT_MESSAGE][12]={
                                      "Not Sel Clr",                                      
                                      "MoveCnt Clr",                                      
                                      "ErrMsg  Clr",                                      
                                      "Read Data  ",                                      
                                      "Write Data ",                                                                            
                                      "Reserve3   ",
                                      "Reserve2   ",
                                      "Reserve1   ",
                                    };                                       

const unsigned char NormalDspMessage[NORMAL_DSP_MESSAGE_CNT][12]={
                                      "Cur Status ",                                      
                                      "Mpm        ",                                      
                                      "Rpm        ",                                      
                                      "Time       ",                                                                            
                                      "Date       ",                                                                            
                                      "Date_Time  ",
                                      "Encod Pulse",                                      
                                      "EMG  Input ",  
                                      "SUS  Input ",  
                                      "RG   Input ",  
                                      "FR1  Input ",  
                                      "X0   Input ",  
                                      "FS0  Input ",
                                      "Mem  Dsp   ",     
                                      "Move Counte",
                                      "Err Counter",
                                      "Can Com Chk",
                                      "485 Com Chk",
                                      "Dec  Pulse ",
                                      "Reserve13  ",
                                      "Reserve12  ",
                                      "Reserve11  ",
                                      "Reserve10  ",
                                      "Reserve9   ",
                                      "Reserve8   ",
                                      "Reserve7   ",
                                      "Reserve6   ",
                                      "Reserve5   ",
                                      "Reserve4   ",
                                      "Reserve3   ",
                                      "Reserve2   ",
                                      "Reserve1   ",
                                    };                                       


const unsigned char InputPort1SelMessage[][12]={
                                      "SILK_EMG   ",                                      
                                      "SILK_PRK   ",                                      
                                      "SILK_AT    ",                                      
                                      "SILK_UB    ",                                                                            
                                      "SILK_DB    ",                                                                            
                                      "SILK_OLS   ",
                                      "SILK_GS    ",                                      
                                      "SILK_HDS   ",  
                                      "SILK_SUS   ",  
                                      "SILK_SDS   ",  
                                      "SILK_SFT   ",  
                                      "SILK_OVL   ",  
                                      "SILK_ULS   ",   
                                      "SILK_DLS   ",
                                      "SILK_LU    ",
                                      "SILK_LD    ",
                                      "SILK_RG    ",
                                      "SILK_BAT   ",
                                      "SILK_PAS   ",
                                      "SILK_FIR   ",
                                      "SILK_WAT   ",
                                      "SILK_FUL   ",
                                      "SILK_MM    ",
                                      "SILK_TH    ",
                                      "SILK_FR1   ",
                                      "SILK_FR2   ",
                                      "SILK_BMR   ",
                                      "SILK_BML   ",
                                      "SILK_SU1   ",
                                      "SILK_SD1   ",
                                      "SILK_DZ    ",
                                      "SILK_INV   ",
                                      "SILK_X0    ",                                      
                                      "SILK_X1    ",                                      
                                      "SILK_X2    ",                                      
                                      "SILK_X3    ",                                                                            
                                      "SILK_X4    ",                                                                            
                                      "SILK_X5    ",
                                      "SILK_X6    ",                                      
                                      "SILK_HOS/X7",  
                                      "SILK_W/FS0 ",  
                                      "SILK_SS/FS1",  
                                      "SILK_FS2   ",  
                                      "SILK_FS3   ",  
                                      "SILK_FS4   ",   
                                      "SILK_DER   ",
                                      "SILK_FID   ",
                                      "SILK_UND   ",
                                      "EXT_X0     ",
                                      "EXT_X1     ",
                                      "EXT_X2     ",
                                      "EXT_X3     ",
                                      "EXT_X4     ",
                                      "EXT_X5     ",
                                      "EXT_X6     ",
                                      "EXT_X7     ",
                                      "Not Use    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",
                                      "SILK_NC    ",

                                    };                                       


const unsigned char OutputPortSelMessage[OUTPORT_SEL_MESSAGE_CNT][12]={
                                      "SILK_FAN   ",                                      
                                      "SILK_LIT   ",                                      
                                      "SILK_BUZ   ",                                      
                                      "SILK_BEL   ",                                                                            
                                      "SILK_REL   ",                                                                            
                                      "SILK_ERR   ",
                                      "SILK_HOP   ",                                      
                                      "SILK_HCL   ",  
                                      "SILK_OP    ",  
                                      "SILK_CL    ",  
                                      "SILK_SOP   ",  
                                      "SILK_SCL   ",  
                                      "SILK_BK2   ",   
                                      "SILK_D_S   ",
                                      "SILK_UCM   ",
                                      "SILK_BK1   ",
                                      "SILK_UP    ",
                                      "SILK_DN    ",
                                      "SILK_P1    ",
                                      "SILK_P2    ",
                                      "SILK_P3    ",
                                      "SILK_P4    ",
                                      "SILK_DAC   ",	                                    
									  "SLOW_DOOR  ",
	                                  "VIRTUAL_Y1 ",
	                                  "VIRTUAL_Y2 ",
	                                  "VIRTUAL_Y3 ",
	                                  "VIRTUAL_Y4 ",
	                                  "VIRTUAL_Y5 ",
	                                  "VIRTUAL_Y6 ",
	                                  "VIRTUAL_Y7 ",
                                      "EXT_Y0     ",
                                      "EXT_Y1     ",
                                      "EXT_Y2     ",
                                      "EXT_Y3     ",
                                      "EXT_Y4     ",
                                      "EXT_Y5     ",
                                      "EXT_Y6     ",
                                      "EXT_Y7     ",
                                      "Not Use    ",
                                    };                                       



const unsigned char BdName[][12]={
                                    "M_Hib  :",                                      
                                    "S_Hib  :",                                      
                                    "Voice  :",                                      
                                    "Car    :",                                                                            
                                    "Not Sel:",                                                                            
                                 };




const unsigned char InputName[6][12]={
                                      "EMG",                                      
                                      "SUS",    
                                      "RG ",   
                                      "FR1",                                      
                                      "X0 ",    
                                      "FS0",   
                                    };                                       

*/







