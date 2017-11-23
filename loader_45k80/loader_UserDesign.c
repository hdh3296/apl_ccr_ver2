
#include        "loader_45k80_main.h"

uint8_t		UserSystemStatus=0;


uint8_t		UserRam_8[VARIABLE_8_END];
uint16_t	UserRam_16[VARIABLE_16_END];
uint32_t	UserRam_32[VARIABLE_32_END];




Menu_Status	MenuStatus[MAX_MENU];


/////////////////////////////////////////////////////
// ����Ʈ ���� 
#define		DFL_SETUP					0x55						//default val 85
#define		DFL_VERSION					0							//version

#define		DFL_DUTY_CNT				40
#define		DFL_DUTY_RATE				25

#define     DFL_SETMODE_SEL				0

#define     DFL_EveryOnSetD				0
#define     DFL_EveryOnSetT				0
#define     DFL_EveryOnSetN				0


#define     DFL_bSave_GIJUN				0 // FALSE



#define 	DFL_SETCURR_DAY				2000				
#define 	DFL_SETCURR_TWL				1000	
#define 	DFL_SETCURR_NIG				300	

#define 	DFL_MSETCURR_DAY			5000				
#define 	DFL_MSETCURR_TWL			4000	
#define 	DFL_MSETCURR_NIG			3000	

#define 	DFL_SET_DUTYCYCLED			0				
#define 	DFL_SET_DUTYCYCLET			0	
#define 	DFL_SET_DUTYCYCLEN			0

#define 	DFL_SET_stDUTYCYCLE_D			0
#define 	DFL_SET_stDUTYCYCLE_T			0
#define 	DFL_SET_stDUTYCYCLE_N			0

#define 	DFL_SET_GIJUN_V			600










#define		DFL_BAS1_X_LENGTH			2800   //11234      //2800
#define		DFL_BAS1_Z_LENGTH			2300	
#define		DFL_BAS1_X_Z_UP_LENGTH		800
#define		DFL_BAS1_Z_X_DOWN_LENGTH	1500
#define		DFL_BAS1_VIBRATION_TIME		5
#define		DFL_BAS1_REPETE_TIME		1
#define		DFL_BAS1_NOT_USE1			0
#define		DFL_BAS1_NOT_USE1			0


#define		DFL_BAS2_X_LENGTH			(DFL_BAS1_X_LENGTH + 2800)
#define		DFL_BAS2_Z_LENGTH			2300	
#define		DFL_BAS2_X_Z_UP_LENGTH		800
#define		DFL_BAS2_Z_X_DOWN_LENGTH	(DFL_BAS1_X_LENGTH + 1500)
#define		DFL_BAS2_VIBRATION_TIME		5
#define		DFL_BAS2_REPETE_TIME		1
#define		DFL_BAS2_NOT_USE1			0
#define		DFL_BAS2_NOT_USE1			0


#define		DFL_BAS3_X_LENGTH			(DFL_BAS2_X_LENGTH + 2800)
#define		DFL_BAS3_Z_LENGTH			2300	
#define		DFL_BAS3_X_Z_UP_LENGTH		800
#define		DFL_BAS3_Z_X_DOWN_LENGTH	(DFL_BAS2_X_LENGTH + 1500)
#define		DFL_BAS3_VIBRATION_TIME		5 
#define		DFL_BAS3_REPETE_TIME		1
#define		DFL_BAS3_NOT_USE1			0
#define		DFL_BAS3_NOT_USE1			0





uint16_t ByteType_DIGIT_STRING_EDIT_Set(uint16_t main_gr,uint16_t sub_gr,uint16_t divide)
{

	MenuStatus[UserMenuSerialNm].M_EditGroupNm=main_gr;
	MenuStatus[UserMenuSerialNm].M_EditSubNm=sub_gr;

	MenuStatus[UserMenuSerialNm].M_EditCursor=0;
    MenuStatus[UserMenuSerialNm].M_EditStatus=DIGIT_STRING_EDIT;
    MenuStatus[UserMenuSerialNm].M_EditStart=3;
	MenuStatus[UserMenuSerialNm].M_EditShiftCnt=3;
	MenuStatus[UserMenuSerialNm].M_EditDivide=divide;				
	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=9;
	MenuStatus[UserMenuSerialNm].M_EditDigitMinValue=0;
	MenuStatus[UserMenuSerialNm].M_EditDataType=BYTE_TYPE;

	if(MenuStatus[UserMenuSerialNm].M_EditDivide > 0)	
		MenuStatus[UserMenuSerialNm].M_EditShiftCnt=(MenuStatus[UserMenuSerialNm].M_EditShiftCnt+1);
	
	return(0);
}


uint16_t ByteType_DIGIT_EDIT_Set(uint16_t main_gr,uint16_t sub_gr,uint16_t divide)
{
	MenuStatus[UserMenuSerialNm].M_EditGroupNm=main_gr;
	MenuStatus[UserMenuSerialNm].M_EditSubNm=sub_gr;
	
	MenuStatus[UserMenuSerialNm].M_EditCursor=0;
    MenuStatus[UserMenuSerialNm].M_EditStatus=DIGIT_EDIT;
    MenuStatus[UserMenuSerialNm].M_EditStart=3;
	MenuStatus[UserMenuSerialNm].M_EditShiftCnt=3; // �������� �¿�� �Դٰ��� �ϰڴ�. 
	MenuStatus[UserMenuSerialNm].M_EditDivide=divide; // �Ҽ��� 				
	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=255; // �ִ밪 
	MenuStatus[UserMenuSerialNm].M_EditDigitMinValue=0; // �ּҰ� 
	MenuStatus[UserMenuSerialNm].M_EditDataType=BYTE_TYPE; // ����Ʈ ���� �̴�.

	if(MenuStatus[UserMenuSerialNm].M_EditDivide > 0)	
		MenuStatus[UserMenuSerialNm].M_EditShiftCnt=(MenuStatus[UserMenuSerialNm].M_EditShiftCnt+1);
	
	return(0);
}


uint16_t IntType_DIGIT_EDIT_Set(uint16_t main_gr,uint16_t sub_gr,uint16_t divide)
{
	MenuStatus[UserMenuSerialNm].M_EditGroupNm=main_gr;
	MenuStatus[UserMenuSerialNm].M_EditSubNm=sub_gr;
	
	MenuStatus[UserMenuSerialNm].M_EditCursor=0;
    MenuStatus[UserMenuSerialNm].M_EditStatus=DIGIT_EDIT;
    MenuStatus[UserMenuSerialNm].M_EditStart=3;
	MenuStatus[UserMenuSerialNm].M_EditShiftCnt=5;
	MenuStatus[UserMenuSerialNm].M_EditDivide=divide;				
	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=65535;
	MenuStatus[UserMenuSerialNm].M_EditDigitMinValue=0;
	MenuStatus[UserMenuSerialNm].M_EditDataType=INT_TYPE;

	if(MenuStatus[UserMenuSerialNm].M_EditDivide > 0)	
		MenuStatus[UserMenuSerialNm].M_EditShiftCnt=(MenuStatus[UserMenuSerialNm].M_EditShiftCnt+1);
	
	return(0);
}





uint16_t Group1_Menu_Status_Set(void)
{
	uint16_t main_gr,sub_gr;

//////////////////////////////////////////////////////////////////////
// main group1
/////////////////////////////////////////////////////////////////////
	UserMenuSerialNm=0;
	main_gr=MAIN_GROUP01;
	sub_gr=0;
/////////////////////////////////////////////////////////////////////
//sub Menu ����
/////////////////////////////////////////////////////////////////////
	ByteType_DIGIT_STRING_EDIT_Set(main_gr,sub_gr,DIVIDE_0);

	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_VERSION; // ���� : ���� ���� �޸� ���� ���� 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm]; // ù�� ǥ�� �̸� 

	MenuStatus[UserMenuSerialNm].M_EditMsgAddr= (uint8_t *)myVersion;
	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=1;	

	UserMenuSerialNm++;
	sub_gr++;
	
/////////////////////////////////////////////////////////////////////
//sub Menu ���� ���� ǥ�� 
/////////////////////////////////////////////////////////////////////
	ByteType_DIGIT_STRING_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_DEFAULT_DSP; // ���� ���� ǥ�� 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditMsgAddr= (uint8_t *)DefaultMsgSel;
	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=9;

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub Menu �ʱ�ȭ
/////////////////////////////////////////////////////////////////////

	ByteType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_INITIAL; // �ʱ�ȭ 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;
	
/////////////////////////////////////////////////////////////////////
//sub Menu 	read / write 
/////////////////////////////////////////////////////////////////////
	// Falsh Read / Write
	ByteType_DIGIT_STRING_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_FLASH_COPY; // read / write 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm]; // ù�� �޴� �̸� ǥ�� 

	MenuStatus[UserMenuSerialNm].M_EditMsgAddr= (uint8_t *)FlashMsgSel; // ��°�� ���� ǥ��  
	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=9;

	MenuStatus[UserMenuSerialNm].M_EditCurDigitData=0xf0;
    MenuStatus[UserMenuSerialNm].M_EditStatus=(MenuStatus[UserMenuSerialNm].M_EditStatus | NO_SAVE);

	UserMenuSerialNm++;
	sub_gr++;

/*
	ByteType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=ByteData004;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;
*/

/////////////////////////////////////////////////////////////////////
//sub Menu ��Ƽ �� 
/////////////////////////////////////////////////////////////////////
	
	ByteType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_DUTY_CNT; // ��Ƽ �� 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;



/////////////////////////////////////////////////////////////////////
//sub Menu ��Ƽ �� 
/////////////////////////////////////////////////////////////////////
	
	ByteType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_DUTY_RATE; // ��Ƽ �� 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=100; // �ִ밪 

	UserMenuSerialNm++;
	sub_gr++;



/////////////////////////////////////////////////////////////////////
//sub Menu ���� ��� ���� 
/////////////////////////////////////////////////////////////////////
	ByteType_DIGIT_STRING_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_SETMODE_SEL; // ���� ��� ���� 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditMsgAddr= (uint8_t *)MsgSelModeSel;
	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=5; // ���� 

	UserMenuSerialNm++;
	sub_gr++;


/////////////////////////////////////////////////////////////////////
//sub Menu ���ð� �� 
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_SETCURR_DAY; // ���ð� �� 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditDigitMinValue=300;	

	UserMenuSerialNm++;
	sub_gr++;


/////////////////////////////////////////////////////////////////////
//sub Menu ���ð� �ڸ� 
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_SETCURR_TWL; // ���ð� �ڸ�  
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditDigitMinValue=300;

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub Menu ���ð� ��
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_SETCURR_NIG; // ���ð� ��
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditDigitMinValue=300;

	UserMenuSerialNm++;
	sub_gr++;


/////////////////////////////////////////////////////////////////////
//sub Menu 	max ���ð� �� 
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_MSETCURR_DAY; // max ���ð� �� 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;


/////////////////////////////////////////////////////////////////////
//sub Menu 	max ���ð� �ڸ� 
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_MSETCURR_TWL; // max ���ð� �ڸ�  
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub Menu 	max ���ð� ��
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_MSETCURR_NIG; // max ���ð� ��
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;	
	

/////////////////////////////////////////////////////////////////////
//sub Menu ������ ON �� 
/////////////////////////////////////////////////////////////////////
	ByteType_DIGIT_STRING_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_EveryOnSetD; 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditMsgAddr= (uint8_t *)MsgSelEveryOnSetD;
	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=2; // ���� 

	UserMenuSerialNm++;
	sub_gr++;	

/////////////////////////////////////////////////////////////////////
//sub Menu ������ ON �ڸ� 
/////////////////////////////////////////////////////////////////////
	ByteType_DIGIT_STRING_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_EveryOnSetT; 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditMsgAddr= (uint8_t *)MsgSelEveryOnSetT;
	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=2; // ���� 

	UserMenuSerialNm++;
	sub_gr++;	

/////////////////////////////////////////////////////////////////////
//sub Menu ������ ON �� 
/////////////////////////////////////////////////////////////////////
	ByteType_DIGIT_STRING_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_EveryOnSetN; 
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditMsgAddr= (uint8_t *)MsgSelEveryOnSetN;
	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=2; // ���� 

	UserMenuSerialNm++;
	sub_gr++;		


/////////////////////////////////////////////////////////////////////
//sub Menu	���� ��� ���� �� PWM ���� �� 
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_SET_stDUTYCYCLE_D; // max ���ð� ��
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=1023; // �ִ밪 

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub Menu	���� ��� ���� �� PWM ���� �� 
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_SET_stDUTYCYCLE_T; // max ���ð� ��
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=1023; // �ִ밪 

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub Menu	���� ��� ���� �� PWM ���� �� 
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_SET_stDUTYCYCLE_N; // max ���ð� ��
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditDigitMaxValue=1023; // �ִ밪 

	UserMenuSerialNm++;
	sub_gr++;	

	return(0);
}





// �׷�2 ���� 
uint16_t Group2_Menu_Status_Set(void)
{
	uint16_t main_gr,sub_gr;


//////////////////////////////////////////////////////////////////////
// main group2
/////////////////////////////////////////////////////////////////////
	main_gr=MAIN_GROUP02;
	sub_gr =0;

/////////////////////////////////////////////////////////////////////
//sub ���� ��Ƽ ����Ŭ �� 
/////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////
//sub �� ��Ƽ ����Ŭ ���� �� 
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_SET_DUTYCYCLED;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditStatus=NO_EDIT;

	UserMenuSerialNm++;
	sub_gr++;



/////////////////////////////////////////////////////////////////////
//sub �ڸ� ��Ƽ ����Ŭ ���� ��
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_SET_DUTYCYCLET;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditStatus=NO_EDIT;

	UserMenuSerialNm++;
	sub_gr++;




/////////////////////////////////////////////////////////////////////
//sub �� ��Ƽ ����Ŭ ���� ��
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_SET_DUTYCYCLEN;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditStatus=NO_EDIT;

	UserMenuSerialNm++;
	sub_gr++;



/////////////////////////////////////////////////////////////////////
//sub ���� ���� ���� �� 
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_SET_GIJUN_V;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	MenuStatus[UserMenuSerialNm].M_EditStatus=NO_EDIT;

	UserMenuSerialNm++;
	sub_gr++;




/////////////////////////////////////////////////////////////////////
//sub group6
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS1_REPETE;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;




/////////////////////////////////////////////////////////////////////
//sub group7
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS1_NOT_USE1;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;


/////////////////////////////////////////////////////////////////////
//sub group8
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS1_NOT_USE2;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;

	return(0);
}



uint16_t Group3_Menu_Status_Set(void)
{
	uint16_t main_gr,sub_gr;


//////////////////////////////////////////////////////////////////////
// main group3
/////////////////////////////////////////////////////////////////////
	main_gr=MAIN_GROUP03;
	sub_gr =0;

/////////////////////////////////////////////////////////////////////
//sub group1
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS2_X_LENGTH;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;


/////////////////////////////////////////////////////////////////////
//sub group2
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS2_Z_LENGTH;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;


/////////////////////////////////////////////////////////////////////
//sub group3
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS2_X_Z_LENGTH;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;


/////////////////////////////////////////////////////////////////////
//sub group4
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS2_Z_X_LENGTH;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;


/////////////////////////////////////////////////////////////////////
//sub group5
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS2_VIB_TIME;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub group6
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS2_REPETE;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub group7
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS2_NOT_USE1;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub group8
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS2_NOT_USE2;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;

	return(0);
}



uint16_t Group4_Menu_Status_Set(void)
{
	uint16_t main_gr,sub_gr;


//////////////////////////////////////////////////////////////////////
// main group1
/////////////////////////////////////////////////////////////////////
	main_gr=MAIN_GROUP04;
	sub_gr =0;

/////////////////////////////////////////////////////////////////////
//sub group4
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS3_X_LENGTH;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub group2
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS3_Z_LENGTH;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;


/////////////////////////////////////////////////////////////////////
//sub group3
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS3_X_Z_LENGTH;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub group4
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS3_Z_X_LENGTH;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;


/////////////////////////////////////////////////////////////////////
//sub group5
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS3_VIB_TIME;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub group6
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS3_REPETE;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub group7
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS3_NOT_USE1;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;

/////////////////////////////////////////////////////////////////////
//sub group8
/////////////////////////////////////////////////////////////////////
	
	IntType_DIGIT_EDIT_Set(main_gr,sub_gr,DIVIDE_0);
	MenuStatus[UserMenuSerialNm].M_EditFlashAddr=F_BAS3_NOT_USE2;
	MenuStatus[UserMenuSerialNm].M_EditGroupMsgAddr= (uint8_t *)GroupLineMessage[UserMenuSerialNm];

	UserMenuSerialNm++;
	sub_gr++;


	MenuStatus[UserMenuSerialNm].M_EditGroupNm=0xff;

	return(0);
}



uint16_t Group5_Menu_Status_Set(void)
{
	uint16_t main_gr,sub_gr;

/*
//////////////////////////////////////////////////////////////////////
// main group5
/////////////////////////////////////////////////////////////////////
	main_gr=MAIN_GROUP05;

/////////////////////////////////////////////////////////////////////
//sub group1
/////////////////////////////////////////////////////////////////////
	sub_gr =SUB_GROUP01;
	
	MenuStatus[main_gr][sub_gr].M_EditCursor=0;
    MenuStatus[main_gr][sub_gr].M_EditStatus=DIGIT_EDIT;
    MenuStatus[main_gr][sub_gr].M_EditStart=3;
	MenuStatus[main_gr][sub_gr].M_EditShiftCnt=3;
	MenuStatus[main_gr][sub_gr].M_EditDivide=DIVIDE_10;				
	MenuStatus[main_gr][sub_gr].M_EditDigitMaxValue=255;
	MenuStatus[main_gr][sub_gr].M_EditDigitMinValue=0;
	MenuStatus[main_gr][sub_gr].M_EditDataType=BYTE_TYPE;
	MenuStatus[main_gr][sub_gr].M_EditFlashAddr=ByteData001;

	if(MenuStatus[main_gr][sub_gr].M_EditDivide > 0)	
		MenuStatus[main_gr][sub_gr].M_EditShiftCnt=(MenuStatus[main_gr][sub_gr].M_EditShiftCnt+1);


/////////////////////////////////////////////////////////////////////
//sub group2
/////////////////////////////////////////////////////////////////////
	sub_gr =SUB_GROUP02;
	
	MenuStatus[main_gr][sub_gr].M_EditCursor=0;
    MenuStatus[main_gr][sub_gr].M_EditStatus=DIGIT_EDIT;
    MenuStatus[main_gr][sub_gr].M_EditStart=3;
	MenuStatus[main_gr][sub_gr].M_EditShiftCnt=3;
	MenuStatus[main_gr][sub_gr].M_EditDivide=DIVIDE_10;				
	MenuStatus[main_gr][sub_gr].M_EditDigitMaxValue=255;
	MenuStatus[main_gr][sub_gr].M_EditDigitMinValue=0;
	MenuStatus[main_gr][sub_gr].M_EditDataType=BYTE_TYPE;
	MenuStatus[main_gr][sub_gr].M_EditFlashAddr=ByteData002;

	if(MenuStatus[main_gr][sub_gr].M_EditDivide > 0)	
		MenuStatus[main_gr][sub_gr].M_EditShiftCnt=(MenuStatus[main_gr][sub_gr].M_EditShiftCnt+1);


/////////////////////////////////////////////////////////////////////
//sub group3
/////////////////////////////////////////////////////////////////////
	sub_gr =SUB_GROUP03;
	
	MenuStatus[main_gr][sub_gr].M_EditCursor=0;
    MenuStatus[main_gr][sub_gr].M_EditStatus=DIGIT_EDIT;
    MenuStatus[main_gr][sub_gr].M_EditStart=3;
	MenuStatus[main_gr][sub_gr].M_EditShiftCnt=3;
	MenuStatus[main_gr][sub_gr].M_EditDivide=DIVIDE_10;				
	MenuStatus[main_gr][sub_gr].M_EditDigitMaxValue=255;
	MenuStatus[main_gr][sub_gr].M_EditDigitMinValue=0;
	MenuStatus[main_gr][sub_gr].M_EditDataType=BYTE_TYPE;
	MenuStatus[main_gr][sub_gr].M_EditFlashAddr=ByteData003;

	if(MenuStatus[main_gr][sub_gr].M_EditDivide > 0)	
		MenuStatus[main_gr][sub_gr].M_EditShiftCnt=(MenuStatus[main_gr][sub_gr].M_EditShiftCnt+1);


/////////////////////////////////////////////////////////////////////
//sub group4
/////////////////////////////////////////////////////////////////////
	sub_gr =SUB_GROUP04;
	
	MenuStatus[main_gr][sub_gr].M_EditCursor=0;
    MenuStatus[main_gr][sub_gr].M_EditStatus=DIGIT_EDIT;
    MenuStatus[main_gr][sub_gr].M_EditStart=3;
	MenuStatus[main_gr][sub_gr].M_EditShiftCnt=3;
	MenuStatus[main_gr][sub_gr].M_EditDivide=DIVIDE_10;				
	MenuStatus[main_gr][sub_gr].M_EditDigitMaxValue=255;
	MenuStatus[main_gr][sub_gr].M_EditDigitMinValue=0;
	MenuStatus[main_gr][sub_gr].M_EditDataType=BYTE_TYPE;
	MenuStatus[main_gr][sub_gr].M_EditFlashAddr=ByteData004;

	if(MenuStatus[main_gr][sub_gr].M_EditDivide > 0)	
		MenuStatus[main_gr][sub_gr].M_EditShiftCnt=(MenuStatus[main_gr][sub_gr].M_EditShiftCnt+1);


/////////////////////////////////////////////////////////////////////
//sub group5
/////////////////////////////////////////////////////////////////////
	sub_gr =SUB_GROUP05;
	
	MenuStatus[main_gr][sub_gr].M_EditCursor=0;
    MenuStatus[main_gr][sub_gr].M_EditStatus=DIGIT_EDIT;
    MenuStatus[main_gr][sub_gr].M_EditStart=3;
	MenuStatus[main_gr][sub_gr].M_EditShiftCnt=3;
	MenuStatus[main_gr][sub_gr].M_EditDivide=DIVIDE_10;				
	MenuStatus[main_gr][sub_gr].M_EditDigitMaxValue=255;
	MenuStatus[main_gr][sub_gr].M_EditDigitMinValue=0;
	MenuStatus[main_gr][sub_gr].M_EditDataType=BYTE_TYPE;
	MenuStatus[main_gr][sub_gr].M_EditFlashAddr=ByteData005;

	if(MenuStatus[main_gr][sub_gr].M_EditDivide > 0)	
		MenuStatus[main_gr][sub_gr].M_EditShiftCnt=(MenuStatus[main_gr][sub_gr].M_EditShiftCnt+1);



/////////////////////////////////////////////////////////////////////
//sub group6
/////////////////////////////////////////////////////////////////////
	sub_gr =SUB_GROUP06;
	
	MenuStatus[main_gr][sub_gr].M_EditCursor=0;
    MenuStatus[main_gr][sub_gr].M_EditStatus=DIGIT_EDIT;
    MenuStatus[main_gr][sub_gr].M_EditStart=3;
	MenuStatus[main_gr][sub_gr].M_EditShiftCnt=3;
	MenuStatus[main_gr][sub_gr].M_EditDivide=DIVIDE_10;				
	MenuStatus[main_gr][sub_gr].M_EditDigitMaxValue=255;
	MenuStatus[main_gr][sub_gr].M_EditDigitMinValue=0;
	MenuStatus[main_gr][sub_gr].M_EditDataType=BYTE_TYPE;
	MenuStatus[main_gr][sub_gr].M_EditFlashAddr=ByteData006;

	if(MenuStatus[main_gr][sub_gr].M_EditDivide > 0)	
		MenuStatus[main_gr][sub_gr].M_EditShiftCnt=(MenuStatus[main_gr][sub_gr].M_EditShiftCnt+1);




/////////////////////////////////////////////////////////////////////
//sub group7
/////////////////////////////////////////////////////////////////////
	sub_gr =SUB_GROUP07;
	
	MenuStatus[main_gr][sub_gr].M_EditCursor=0;
    MenuStatus[main_gr][sub_gr].M_EditStatus=DIGIT_EDIT;
    MenuStatus[main_gr][sub_gr].M_EditStart=3;
	MenuStatus[main_gr][sub_gr].M_EditShiftCnt=3;
	MenuStatus[main_gr][sub_gr].M_EditDivide=DIVIDE_10;				
	MenuStatus[main_gr][sub_gr].M_EditDigitMaxValue=255;
	MenuStatus[main_gr][sub_gr].M_EditDigitMinValue=0;
	MenuStatus[main_gr][sub_gr].M_EditDataType=BYTE_TYPE;
	MenuStatus[main_gr][sub_gr].M_EditFlashAddr=ByteData007;

	if(MenuStatus[main_gr][sub_gr].M_EditDivide > 0)	
		MenuStatus[main_gr][sub_gr].M_EditShiftCnt=(MenuStatus[main_gr][sub_gr].M_EditShiftCnt+1);

/////////////////////////////////////////////////////////////////////
//sub group8
/////////////////////////////////////////////////////////////////////
	sub_gr =SUB_GROUP08;
	
	MenuStatus[main_gr][sub_gr].M_EditCursor=0;
    MenuStatus[main_gr][sub_gr].M_EditStatus=DIGIT_EDIT;
    MenuStatus[main_gr][sub_gr].M_EditStart=3;
	MenuStatus[main_gr][sub_gr].M_EditShiftCnt=3;
	MenuStatus[main_gr][sub_gr].M_EditDivide=DIVIDE_10;				
	MenuStatus[main_gr][sub_gr].M_EditDigitMaxValue=255;
	MenuStatus[main_gr][sub_gr].M_EditDigitMinValue=0;
	MenuStatus[main_gr][sub_gr].M_EditDataType=BYTE_TYPE;
	MenuStatus[main_gr][sub_gr].M_EditFlashAddr=ByteData008;

	if(MenuStatus[main_gr][sub_gr].M_EditDivide > 0)	
		MenuStatus[main_gr][sub_gr].M_EditShiftCnt=(MenuStatus[main_gr][sub_gr].M_EditShiftCnt+1);


*/
	return(0);
}




uint16_t Group6_Menu_Status_Set(void)
{
	uint16_t main_gr,sub_gr;

	main_gr=MAIN_GROUP06;
	sub_gr=SUB_GROUP01;


	return(0);
}
uint16_t Group7_Menu_Status_Set(void)
{
	uint16_t main_gr,sub_gr;

	main_gr=MAIN_GROUP07;
	sub_gr=SUB_GROUP01;

	return(0);
}
uint16_t Group8_Menu_Status_Set(void)
{
	uint16_t main_gr,sub_gr;

	main_gr=MAIN_GROUP08;
	sub_gr=SUB_GROUP01;

	return(0);
}
uint16_t Group9_Menu_Status_Set(void)
{
	uint16_t main_gr,sub_gr;

	main_gr=MAIN_GROUP09;
	sub_gr=SUB_GROUP01;

	return(0);
}
uint16_t Group10_Menu_Status_Set(void)
{
	uint16_t main_gr,sub_gr;

	main_gr=MAIN_GROUP10;
	sub_gr=SUB_GROUP01;

	return(0);
}



uint16_t	DefaultValueSet(void)
{
	if(cF_INITIAL == DFL_SETUP)	return(0);
	else{
		cSR_ByteData(F_VERSION)=DFL_VERSION;
		cSR_ByteData(F_INITIAL)=DFL_SETUP; // �ʱ�ȭ �� 

		cSR_ByteData(F_DUTY_CNT) = DFL_DUTY_CNT;
		cSR_ByteData(F_DUTY_RATE) = DFL_DUTY_RATE;
		
		cSR_ByteData(F_SETMODE_SEL) = DFL_SETMODE_SEL;
		
		cSR_ByteData(F_EveryOnSetD) = DFL_EveryOnSetD;
		cSR_ByteData(F_EveryOnSetT) = DFL_EveryOnSetT;
		cSR_ByteData(F_EveryOnSetN) = DFL_EveryOnSetN;

		cSR_ByteData(F_bSave_GIJUN) = DFL_bSave_GIJUN;

		iSR_IntData(F_SETCURR_DAY) = DFL_SETCURR_DAY;
		iSR_IntData(F_SETCURR_TWL) = DFL_SETCURR_TWL;
		iSR_IntData(F_SETCURR_NIG) = DFL_SETCURR_NIG;

		iSR_IntData(F_MSETCURR_DAY) = DFL_MSETCURR_DAY;
		iSR_IntData(F_MSETCURR_TWL) = DFL_MSETCURR_TWL;
		iSR_IntData(F_MSETCURR_NIG) = DFL_MSETCURR_NIG;	

		iSR_IntData(F_SET_DUTYCYCLED) = DFL_SET_DUTYCYCLED;
		iSR_IntData(F_SET_DUTYCYCLET) = DFL_SET_DUTYCYCLET;
		iSR_IntData(F_SET_DUTYCYCLEN) = DFL_SET_DUTYCYCLEN;

		iSR_IntData(F_SET_stDUTYCYCLE_D) = DFL_SET_stDUTYCYCLE_D;
		iSR_IntData(F_SET_stDUTYCYCLE_T) = DFL_SET_stDUTYCYCLE_T;
		iSR_IntData(F_SET_stDUTYCYCLE_N) = DFL_SET_stDUTYCYCLE_N;

		iSR_IntData(F_SET_GIJUN_V) = DFL_SET_GIJUN_V;
 
		FlashBlockWr(0);	 // 0 : ù ���� ����� Write	
	}
	return(0);
}




uint16_t Menu_Status_Set(void)
{
	Group1_Menu_Status_Set();
	Group2_Menu_Status_Set();
	Group3_Menu_Status_Set();
	Group4_Menu_Status_Set();
	Group5_Menu_Status_Set();
	Group6_Menu_Status_Set();
	Group7_Menu_Status_Set();
	Group8_Menu_Status_Set();
	Group9_Menu_Status_Set();
	Group10_Menu_Status_Set();

	DefaultValueSet();

	return(0);
}






//////////////////////////////////////////
//////////////////////////////////////////
uint16_t Default_Cur_State_Display(void)
{
	uint16_t i,j;

	j=UserSystemStatus;
	for(i=0;i<16;i++)	New485Ladder[SECONDLINE_BASE+i] =StatusMessage[j][i];          

	return(0);
}




uint16_t Nm_Display(void)
{	
	New485Ladder[SECONDLINE_BASE+0] =(CurKeyPoint / 10) + '0';              
	New485Ladder[SECONDLINE_BASE+1] =(CurKeyPoint % 10) + '0';          	
	CurMenuStatus.M_EditStart=3;
	return(0);
}



// ���� �ϸ� �׻� �� �Լ��� �θ���.
// ���ÿ� ��� �� �Լ��� �ҷ��� ���÷��� �ϰ� �ִ�. 
uint16_t DefaultDisplay(void)
{
    uint16_t  i,j,k;


	k=cF_DEFAULT_DSP;	
	
	
	if(BefDspMode != k){
		BefDspMode = k;
        for(i=0;i<16;i++){
            New485Ladder[SECONDLINE_BASE+i] =' ';          
        }
	}
	
	if(UserSystemStatus== 0){
		for(i=0;i<16;i++)	New485Ladder[i+2]=DefaultMsg[1][i];
	}
	else{
		for(i=0;i<16;i++)	New485Ladder[i+2]=DefaultMsg[0][i];
	}
	

    switch(k){
        case    0:
			Default_Cur_State_Display(); // ���� ���� ���÷��� 
            break;
        case    1: // ĳ���� Ÿ�� �޸� ���÷��� 
			Nm_Display(); 
			 
			if (CurKeyPoint == 2){
				Nine_Dig_Dsp_ext( (uint32_t)UserRam_8[CurKeyPoint], 
								  (uint32_t)UserRam_8[CurKeyPoint+1],
								  (uint32_t)UserRam_8[CurKeyPoint+2],
								  0 
								 );
			}
			else{
				Three_Dig_Dsp((uint32_t)UserRam_8[CurKeyPoint], 0);   
			}

			
				
			
            break;
        case    2: // ������ Ÿ�� �޸� ���÷��� 
			Nm_Display();
			Five_Dig_Dsp((uint32_t)UserRam_16[CurKeyPoint],0); 
			break;																																																																
        case    3: // long Ÿ�� ���÷��� 
			Nm_Display();
			Ten_Dig_Dsp((uint32_t)UserRam_32[CurKeyPoint],0);     
            break;
        default:
			Default_Cur_State_Display();
            break;

    }

	return(0);		
}
/////////////////////////////////////
