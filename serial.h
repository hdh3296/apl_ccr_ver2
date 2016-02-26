
#include	"AllCommom.h"


#ifndef _SERIAL_H_
#define _SERIAL_H_

#define com2BAUD 19200      
//#define FOSC 8000000L
#define com2FOSC 32000000L
#define com2NINE 0     /* Use 9bit communication? FALSE=8bit */
#define com2OUTPUT 0
#define com2INPUT 1

#define com2DIVIDER ((int)(com2FOSC/(16UL * com2BAUD) -1))
#define com2HIGH_SPEED 1

#if com2NINE == 1
#define com2NINE_BITS 0x40
#else
#define com2NINE_BITS 0
#endif

#if com2HIGH_SPEED == 1
#define com2SPEED 0x4
#else
#define com2SPEED 0
#endif

/*
void init_comms(void);
void putch(unsigned char);
unsigned char getch(void);
unsigned char getche(void);
*/


//////////////////////////////////////////////////
//////////////////////////////////////////////////

#define         EOT             0x04
#define         ETX             0x03
#define         ENQ             0x05
#define         ACK             0x06


#define         STX_CHK         0
#define         ADDRESS_CHK     1
#define         COMMAND_CHK     2
#define         DATACNT_CHK     3
#define         DATA_CHK        4
#define         CHKSUM_CHK      5
#define         ETX_CHK         6
#define         RX_ERROR        7
#define         RX_GOOD         8
#define         TX_SET          9
#define         CHKSUM_LOW_CHK  10
#define         CHKSUM_HIGH_CHK 11
#define         TX_ALL          12

#define         BCC1_CHK        13
#define         BCC2_CHK        14

//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////


#endif
