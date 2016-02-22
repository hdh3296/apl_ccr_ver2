

#include    <pic18.h>

#include    "..\system\system.h"

#include    "loader_UserDesign.h"
#include	"loader_cmd.h"
#include	"loader_com1_port.h"
#include	"loader_serial.h"
#include	"loader_setup.h"
#include	"loader_flash.h"



extern	uint16_t	Loader_Com_Init(void);
extern	uint16_t	Loader_Func(void);
extern	uint16_t	Loader_Msec1_Interrpt(void);
extern	uint16_t	Loader_Com_Interrpt(void);


extern	uint8_t		UserSystemStatus;
extern	uint8_t		UserRam_8[];
extern	uint16_t	UserRam_16[];
extern	uint32_t	UserRam_32[];



extern	uint8_t	LoaderBitAreaSram1;


#define  bExportData		GET_BITFIELD(&LoaderBitAreaSram1).bit0
#define  bImportData        GET_BITFIELD(&LoaderBitAreaSram1).bit1


	






