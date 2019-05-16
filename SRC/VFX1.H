/*######################################################################
			Type Declaration Section
########################################################################*/

/* VIP I/O Bus Register offsets */
#define	VIP_AIR		0x0
#define	VIP_CSR		0x1
#define	VIP_DFIN	0x2
#define	VIP_DFOUT	0x4

/* VIP Internal registers */
#define	VIP_SCR		 0
#define	VIP_SSR		 1
#define	VIP_ICR		 2
#define	VIP_ISR		 3
#define	VIP_PSR		 4
#define	VIP_VRR		 5
#define	VIP_PCR		 6
#define	VIP_PPMR	 7
#define	VIP_PRAR	 8
#define	VIP_PWAR	 9
#define	VIP_PCRR	10

// T.S.R. related type defs.
#define SENSE_VECTOR        0x33

#define RESET_DEVICE        0x00
#define GET_DATA_SIZES      0x01
#define SET_DATA_SIZE       0x02
#define GET_CONFIGURATION   0x03
#define SET_CONFIGURATION   0x04
#define REPORT              0x05
#define CONTINUE            0x06
#define RESET_ZERO          0x07
#define SET_ZERO            0x08
#define TEST_DEVICES        0x09
#define GET_DEVICE_DATA     0x70;
#define SET_DEVICE_DATA     0x71;
#define SENSE_DRIVER_STATUS 0x7F
#define SET_VIDEO_PAGE      0x80

#define MIN_SENSE_FUNCTION  0x60
#define MAX_SENSE_FUNCTION  0x70

#define DCHMS   2
#define DCHTD   3
#define DCHPD   4
#define DCALL   0xFF

#define PRDM    "Forte Technologies, Inc.\0"
#define PRDN    "VFX1 CyberPuck\0"

//Address index values for registers.
enum air_enum { SCR, SSR, ICR, ISR, PSR, VRR, PCR, PPRR, PRAR, PWAR, PCRA,
		NOREG };
typedef enum air_enum  AIRVAL;

//Software Command Register codes.
#define CPND  128      //Determines command pending bit mask.
#define CCHK   64      //Determines command check bit mask.
enum cmdcode_enum { NOP, CSTRT, CCONT, RSTRT, RTERM, GSTAT, RSTAT, NOCMD };
typedef enum cmdcode_enum  CMDCODE;

//Software Status Register codes.
enum statcode_enum { SDOK, SDCNC, SDCFL, SDDNR, SDDNE, SDDFL, SDNOR, SDCNV,
        SDSERR };
typedef enum statcode_enum  STATCODE;

//Data fifo selection values (IN = data into the VIP, OUT = data out from VIP)
enum fifodir_enum {IN, OUT, NODIR};
typedef enum fifodir_enum  FIFODIR;

//Packet type values.
enum packtyp_enum {NULLP, SYSI, VNDI, SYSC, HMS, SVM, HTD, HPD};
typedef enum packtyp_enum  PACKTYP;

//Null packet type.
struct cfpack0_struct
{
unsigned char	 psiz;
unsigned char	 ptyp;
};
typedef struct cfpack0_struct NULL_CPKT;

//System info configuration packet type.
struct cfpack1_struct
{
unsigned char	 psiz;
unsigned char	 ptyp;
unsigned char	 dcls;
unsigned char	 dnum;
unsigned char	 sstat;
unsigned char	 vmin;
unsigned char	 vmaj;
char		 vipid[4];
unsigned short	 dfsz;
unsigned short	 dummy;
};
typedef struct cfpack1_struct SYSTEM_CPKT;

// Vendor sizes
#define MN_SIZE     32
#define SNRL_SIZE   16
//Vendor info configuration packet type.
struct cfpack2_struct
{
unsigned char	 psiz;
unsigned char	 ptyp;
unsigned char	 prdm[ MN_SIZE ];
unsigned char	 prdn[ MN_SIZE ];
unsigned char	 prdsn[ SNRL_SIZE ];
unsigned char	 prdrl[ SNRL_SIZE ];
};
typedef struct cfpack2_struct VENDOR_CPKT;

//Head Mounted System Capabilities structure.
struct hmsc_struct
{
unsigned char aoc : 1;	//Audio out capable if set.
unsigned char aic : 1;	//Audio in capable if set.
unsigned char sac : 1;	//Stereo audio capable if set.
unsigned char cic : 1;	//Color image capable if set.
unsigned char sic : 1;	//Stereo image capable if set.
unsigned char hti : 1;	//Head Tracker installed.
unsigned char dum : 2;	//Not used.
};
typedef struct hmsc_struct HMSC;

//Head Mounted System flags structure.
struct hmsf_struct
{
unsigned char dps : 1;	//Disable palette snooping.
unsigned char aic : 1;	//Delayed flip.
unsigned char dum : 5;	//Not used
unsigned char ddsbl: 1;	//Disable device.
};
typedef struct hmsf_struct HMSF;

//Head Mounted System configuration packet type.
#define VMODSIZE  10
struct cfpack3_struct
{
unsigned char	 psiz; //Number of bytes in packet.
unsigned char	 ptyp; //Packet type. 
unsigned char	 dcls; // Device class
unsigned char	 dnum; // Device number
HMSF             hmsf; //Head mounted system flags.
unsigned char    hmss; //Head mounted system status.
unsigned char	 vmin; //Minor version for device.
unsigned char	 vmaj; //Major version for device.
HMSC		     hmsc; //Head mounted system capabilities.
unsigned char	 dtyp; //Display type.
unsigned short	 vmag; //Visual magnification in units of 0.001.
unsigned short	 hfov; //Horizontal full FOV in units of 0.25 deg.
unsigned short	 vfov; //Vertical full FOV in units of 0.25 deg.
unsigned char	 ipd;  //Interpupillary distance in units of 0.5 mm.
signed char	     hoao; //Horizontal optical axis offset in units of .1 mm.
signed char	     voao; //Vertical optical axis offset in units of .1 mm.
signed char	     oar;  //Optical axis rotation in units of 0.25 deg.
unsigned char	 mrr;  //Max refresh rate in Hz.
unsigned char	 cvm;  //Current video mode.
unsigned char	 reserved;	  
unsigned char	 vmsp; //Number of Vesa modes supported.
unsigned short	 vmod[VMODSIZE]; //Supported VESA modes.  Field currently
			   //allows up to 10 supported modes.  Packet in fifo
			   //may have any number of supported modes present.
};
typedef struct cfpack3_struct HMS_CPKT;

//Rotational Coordinate Flags structure.
struct rtcf_struct
{
unsigned char rtc  : 1;  //Return to center device (1=yes).
unsigned char wrp  : 1;  //Coordiante values wrap (1=yes).
unsigned char zpsr : 1;  //Zero position resetable (1=yes).
unsigned char rdg  : 1;  //Rotational data generated (1=yes).
unsigned char dum  : 3;  //Not used.
unsigned char den  : 1;  //Data reporting enabled (1=yes).
};
typedef struct rtcf_struct RTCF;

//Rotation Coordinate Descriptor structure.
struct rtcd_struct
{
signed short	maxv;
signed short	minv;
unsigned short	steps;
RTCF		rcf;
unsigned char	dum;
};
typedef struct rtcd_struct RTCD;

//Head tracker flags structure.
struct htf_struct
{
unsigned char dum  : 7;  //Not used.
unsigned char ddsbl: 1;  //Data reporting enabled (1=yes).
};
typedef struct htf_struct HTF;

//Head Tracker Device configuration packet.
struct cfpack4_struct
{
unsigned char	 psiz;
unsigned char	 ptyp;
unsigned char	 dcls;
unsigned char	 dnum;
HTF              htf; //Head tracker flag (disable device if set).
unsigned char    hts; //Head tracker status.
unsigned char	 vmin; //Minor version for tracker.
unsigned char	 vmaj; //Major version for tracker.
RTCD		 ywcd;
RTCD		 ptcd;
RTCD		 rlcd;
};
typedef struct cfpack4_struct HTD_CPKT;

//Button Descriptor structure.
struct btds_struct
{
unsigned char nbtn;	 //Number of buttons/switches on device.
unsigned char cnck : 1;  //Counts clicks (1=yes).
unsigned char dum  : 6;  //Not used.
unsigned char den  : 1;  //Data reporting enabled (1=yes).
};
typedef struct btds_struct BTDS;

//Hand held device Flags structure.
struct hhpf_struct
{
unsigned char hhpp : 2;  //Hand held pointer prority (0=highest).
unsigned char dum  : 4;  //Not used.
unsigned char ddsbl: 1;  //Data reporting enabled (1=yes).
};
typedef struct hhpf_struct HHPF;

//Hand-held Pointing Device configuration packet.
struct cfpack5_struct
{
unsigned char	 psiz;
unsigned char	 ptyp;
unsigned char	 dcls;
unsigned char	 dnum;
HHPF             hhpf; //Hand held flag (disable device if set).
unsigned char    hhps; //Head tracker status.
unsigned char	 vmin; //Minor version for tracker.
unsigned char	 vmaj; //Major version for tracker.
RTCD		 ywcd;
RTCD		 ptcd;
RTCD		 rlcd;
BTDS		 btcd;
};
typedef struct cfpack5_struct HPD_CPKT;

struct cfpack6_struct
{
unsigned char	 psiz; //Number of bytes in packet.
unsigned char	 ptyp; //Packet type. 
unsigned char	 dcls; // Device class
unsigned char	 dnum; // Device number
HMSF             hmsf; //Head mounted system flags.
unsigned char    vmod; //Head mounted video mode.
};
typedef struct cfpack6_struct SVM_CPKT;

