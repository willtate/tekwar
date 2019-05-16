/*----------------------- BEGINNING OF RCS INFO ------------------------
 *
 * $Id: avlib.h 1.4 1995/09/12 13:06:31 GOOSE Exp $
 *
 * $Log: avlib.h $
 * Revision 1.4  1995/09/12  13:06:31  GOOSE
 * Fixed comments
 *
 * Revision 1.3  1995/09/12  12:58:21  GOOSE
 * Initial revision with RCS info added
 *
 *
 --------------------------------------------------------------------*/

#ifndef AVLIB_H
#define AVLIB_H

/* ======================================================================= *
 * Please Read "AvReadme.doc" for usage                                    *
 * ======================================================================= */

/* ======================================================================= *
 * Compiler & Memory Mode Wrappers.                                        *
 * ----------------------------------------------------------------------- */
 
#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER) || defined(__BORLANDC__)
#define REALMODE
#endif

#if defined(REALMODE)
#define FAR __far
#else
#define FAR
#endif

/*-------------------------------------------------------------------------*/
/* Constants*/

#define TSR_SERIAL_LENGTH		14
#define TSR_MAX_LENGTH			80
#define MAX_SP_STRING         80

/*--------------------------------------------------------------------------*/

typedef struct {
	char           copyright[TSR_MAX_LENGTH];	// driver copyright
	short          major;							// driver version number
	short				minor;
	short				count;							// # of available devices
} SpwDrvOpenPacket;



typedef struct {
	char           copyright[TSR_MAX_LENGTH];	// device copyright
	char           serial[TSR_SERIAL_LENGTH];	// device serial number
} SpwDevOpenPacket;


typedef struct {
	long				timestamp;						// time of event
	unsigned short	period;							// period since last MOVEMENT
	unsigned short button;							// button pressed mask
	short          tx;								// Translation X
	short          ty;								//					Y
	short          tz;								//					Z
	short          rx;								// Rotation X
	short          ry;								//				Y
	short          rz;								//				Z
} SpwForcePacket;



typedef struct {
	long           timestamp;						// time of event
	unsigned short period;							// period since last BUTTON
	unsigned short button;							// button pressed mask
} SpwButtonPacket;



typedef struct {
	unsigned long data;								// MUST be TSRCMD_DATA
} SpwCommandPacket;

#define TSRCMD_DATA	0xFF0000FF

  // craig was here
typedef struct {
	int            length;
  //	char           data[MAX_SP_STRING];
   short           data[MAX_SP_STRING];
} SpwPacketUnknown;

//---------------------------------------------------------------------------

typedef union {
	char              padding[128];		/* Extra room for future expansion */

	SpwCommandPacket	command;

	SpwDrvOpenPacket	drvOpen;
	SpwDevOpenPacket	devOpen;

	SpwForcePacket		force;
	SpwButtonPacket	button;
   SpwPacketUnknown  unknown;

} SpwPacket;




// TSR Interrupt Functions
#ifndef TSR_H
#define TSR_DRIVER_CLOSE		 		0x0000
#define TSR_DRIVER_OPEN					0x8001
#define TSR_DEVICE_CLOSE				0x0002
#define TSR_DEVICE_OPEN					0x8003

#define TSR_DEVICE_DISABLE				0x0010
#define TSR_DEVICE_ENABLE				0x0011

#define TSR_DEVICE_GETFORCE			0x8020
#define TSR_DEVICE_GETBUTTONS			0x8021
#endif
/* ======================================================================= *
 * Function Prototypes                                                     *
 * ======================================================================= */

short SpwOpenDriver(SpwPacket FAR *packet);
short SpwCloseDriver(void);

short SpwOpenDevice(short device, SpwPacket FAR *packet);
short SpwCloseDevice(short device);

short SpwEnableDevice(short device);
short SpwDisableDevice(short device);

short SpwGetForce(short device, SpwPacket FAR *packet);
short SpwGetButton(short device, SpwPacket FAR *packet);

short SpwMoveDriver(short vector);
short SpwGetPhysInfo(short device, SpwPacket FAR *packet);
short SpwSetPhysInfo(short device, SpwPacket FAR *packet);
short SpwValidatePhys(void);

short SpwGetVector(void);

/*================== Structures definitions ============================*/

#define SPW_MAXBUF		80

#define sTx		 sData[0]
#define sTy	    sData[1]
#define sTz      sData[2]
#define sRx	    sData[3]
#define sRy	    sData[4]
#define sRz	    sData[5]
#define Speriod  sData[6]

#define fTx		 fData[0]
#define fTy	    fData[1]
#define fTz     fData[2]
#define fRx		 fData[3]
#define fRy		 fData[4]
#define fRz		 fData[5]
#define Fperiod fData[6]

#define ULONG unsigned long

/* Button State table */



enum SpwEventType {
	SPW_NO_EVENT=0,
   SPW_BUTTON_HELD=1,
   SPW_BUTTON_DOWN=2, 
   SPW_BUTTON_UP=4,
   SPW_MOTION=8
};



typedef struct {

	ULONG           old;
	ULONG           current;
	ULONG           pressed;
	ULONG           released;

} ButtonTable;

typedef struct {

	short	type;
	float           fData[7];
	short           sData[7];
	int           	 buttonNumber;
	ButtonTable     buttonState;
  	char            string[SPW_MAXBUF];

} SPW_InputEvent;

short SPW_InputCheckForSpaceball(short);
short SPW_IsInputEvent(short, SPW_InputEvent FAR *);
short SPW_InputShutdown(short);


/* ======================================================================= *
 * Compiler & Memory Mode Wrappers.                                        *
 * ======================================================================= *
 */

#ifdef __cplusplus
};
#endif

/* ======================================================================= */
#endif

