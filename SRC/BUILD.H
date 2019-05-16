#define MAXSECTORS 1024
#define MAXWALLS 8192
#define MAXSPRITES 4096

#define MAXTILES 4096
#define MAXSTATUS 1024
#define MAXPLAYERS 16
#define MAXXDIM 1600
#define MAXYDIM 1200
#define MAXPALOOKUPS 256
#define MAXPSKYTILES 256
#define MAXSPRITESONSCREEN 1024

	//Make all variables in BUILD.H defined in the ENGINE,
	//and externed in GAME
#ifdef ENGINE
	#define EXTERN
#else
	#define EXTERN extern
#endif

//ceilingstat, bit 0: 1 = ceiling parallaxing sky, 0 = not               "P"
//             bit 1: 1 = ceiling groudraw, 0 = not (not supported yet)
//             bit 2: 1 = ceiling swap x&y, 0 = not                      "F"
//             bit 3: 1 = pixel-smooshing mode, 0 = tile-expanding mode  "E"
//             bit 4: 1 = ceiling x-flip                                 "F"
//             bit 5: 1 = ceiling y-flip                                 "F"
//             bit 6: 1 = Relative alignment to first point on wall list "R"
//             bit 7: reserved

//floorstat,   bit 0: 1 = floor parallaxing sky, 0 = not                 "P"
//             bit 1: 1 = floor groudraw, 0 = not                        "G"
//             bit 2: 1 = floor swap x&y, 0 = not                        "F"
//             bit 3: 1 = pixel-smooshing mode, 0 = tile-expanding mode  "E"
//             bit 4: 1 = floor x-flip                                   "F"
//             bit 5: 1 = floor y-flip                                   "F"
//             bit 6: 1 = Relative alignment to first point on wall list "R"
//             bit 7: reserved

typedef struct
{
	unsigned short wallptr, wallnum;
	short ceilingpicnum, floorpicnum;
	short ceilingheinum, floorheinum;
	long ceilingz, floorz;
	signed char ceilingshade, floorshade;
	char ceilingxpanning, floorxpanning;
	char ceilingypanning, floorypanning;
	char ceilingstat, floorstat;
	char ceilingpal, floorpal;
	char visibility;
	short lotag, hitag, extra;
} sectortype;

//cstat, bit 0: 1 = Blocking wall (use with clipmove, getzrange)      "B"
//       bit 1: 1 = bottoms of invisible walls swapped, 0 = not       "2"
//       bit 2: 1 = align picture on bottom (for doors), 0 = top      "O"
//       bit 3: 1 = x-flipped, 0 = normal                             "F"
//       bit 4: 1 = masking wall, 0 = not                             "M"
//       bit 5: 1 = 1-way wall, 0 = not                               "1"
//       bit 6: 1 = Blocking wall (use with hitscan)                  "H"
//       bit 7: 1 = Transluscent, 0 = not                             "T"
//       bit 8: 1 = y-flipped, 0 = normal                             "F"
//       bit 9: reserved
//       bit 10: reserved
//       bit 11: reserved
//       bit 12: reserved
//       bit 13: reserved
//       bit 14: reserved
//       bit 15: reserved

typedef struct
{
	long x, y;
	short point2, nextsector, nextwall;
	short picnum, overpicnum;
	signed char shade;
	char pal;
	short cstat;
	unsigned char xrepeat, yrepeat, xpanning, ypanning;
	short lotag, hitag, extra;
} walltype;

//cstat, bit 0: 1 = Blocking sprite (use with clipmove, getzrange)    "B"
//       bit 1: 1 = 50/50 transluscence, 0 = normal                   "T"
//       bit 2: 1 = x-flipped, 0 = normal                             "F"
//       bit 3: 1 = y-flipped, 0 = normal                             "F"
//       bits 5-4: 00 = FACE sprite (default)                         "R"
//                 01 = WALL sprite (like masked walls)
//                 10 = FLOOR sprite (parallel to ceilings&floors)
//                 11 = SPIN sprite (face sprite that can spin 2draw style - not done yet)
//       bit 6: 1 = 1-sided sprite, 0 = normal                        "1"
//       bit 7: 1 = Real centered centering, 0 = foot center          "C"
//       bit 8: 1 = Blocking sprite (use with hitscan)                "H"
//       bit 9: reserved
//       bit 10: reserved
//       bit 11: reserved
//       bit 12: reserved
//       bit 13: reserved
//       bit 14: reserved
//       bit 15: 1 = Invisible sprite, 0 = not invisible

typedef struct
{
	long x, y, z;
	short cstat;
	signed char shade;
	char pal, clipdist;
	unsigned char xrepeat, yrepeat;
	signed char xoffset, yoffset;
	short picnum, ang, xvel, yvel, zvel, owner;
	short sectnum, statnum;
	short lotag, hitag, extra;
} spritetype;

EXTERN sectortype sector[MAXSECTORS];
EXTERN walltype wall[MAXWALLS];
EXTERN spritetype sprite[MAXSPRITES];

EXTERN long spritesortcnt;
EXTERN spritetype tsprite[MAXSPRITESONSCREEN];

EXTERN char vidoption;
EXTERN long xdim, ydim, ylookup[MAXYDIM+1], numpages;
EXTERN long yxaspect, xyaspect;

EXTERN short numsectors, numwalls;
EXTERN volatile long totalclock;
EXTERN long numframes, randomseed;
EXTERN short sintable[2048];
EXTERN short numpalookups;
EXTERN char *palookup[MAXPALOOKUPS];
EXTERN char parallaxtype;
EXTERN long parallaxyoffs, visibility;

EXTERN long windowx1, windowy1, windowx2, windowy2;
EXTERN short startumost[MAXXDIM], startdmost[MAXXDIM];

EXTERN short pskyoff[MAXPSKYTILES], pskybits;

EXTERN short headspritesect[MAXSECTORS+1], headspritestat[MAXSTATUS+1];
EXTERN short prevspritesect[MAXSPRITES], prevspritestat[MAXSPRITES];
EXTERN short nextspritesect[MAXSPRITES], nextspritestat[MAXSPRITES];

EXTERN short tilesizx[MAXTILES], tilesizy[MAXTILES];
EXTERN long numtiles, picanm[MAXTILES], waloff[MAXTILES];
EXTERN char loadtilelockmode;

	//These variables are for auto-mapping with the draw2dscreen function.
	//When you load a new board, these bits are all set to 0 - since
	//you haven't mapped out anything yet.  Note that these arrays are
	//bit-mapped.
	//If you want draw2dscreen() to show sprite #54 then you say:
	//   spritenum = 54;
	//   show2dsprite[spritenum>>3] |= (1<<(spritenum&7));
	//And if you want draw2dscreen() to not show sprite #54 then you say:
	//   spritenum = 54;
	//   show2dsprite[spritenum>>3] &= ~(1<<(spritenum&7));
	//Automapping defaults to 0 (do nothing).  If you set automapping to 1,
	//   then in 3D mode, the walls and sprites that you see will show up the
	//   next time you flip to 2D mode.

EXTERN char show2dsector[MAXSECTORS>>3];
EXTERN char show2dwall[MAXWALLS>>3];
EXTERN char show2dsprite[MAXSPRITES>>3];
EXTERN char automapping;

EXTERN char gotpic[MAXTILES>>3];
EXTERN char gotsector[MAXSECTORS>>3];

/*************************************************************************
POSITION VARIABLES:

		POSX is your x - position ranging from 0 to 65535
		POSY is your y - position ranging from 0 to 65535
			(the length of a side of the grid in EDITBORD would be 1024)
		POSZ is your z - position (height) ranging from 0 to 65535, 0 highest.
		ANG is your angle ranging from 0 to 2047.  Instead of 360 degrees, or
			 2 * PI radians, I use 2048 different angles, so 90 degrees would
			 be 512 in my system.

SPRITE VARIABLES:

	EXTERN short headspritesect[MAXSECTORS+1], headspritestat[MAXSTATUS+1];
	EXTERN short prevspritesect[MAXSPRITES], prevspritestat[MAXSPRITES];
	EXTERN short nextspritesect[MAXSPRITES], nextspritestat[MAXSPRITES];

	Example: if the linked lists look like the following:
		 ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿
		 ³      Sector lists:               Status lists:               ³
		 ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´
		 ³  Sector0:  4, 5, 8             Status0:  2, 0, 8             ³
		 ³  Sector1:  16, 2, 0, 7         Status1:  4, 5, 16, 7, 3, 9   ³
		 ³  Sector2:  3, 9                                              ³
		 ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ
	Notice that each number listed above is shown exactly once on both the
		left and right side.  This is because any sprite that exists must
		be in some sector, and must have some kind of status that you define.


Coding example #1:
	To go through all the sprites in sector 1, the code can look like this:

		sectnum = 1;
		i = headspritesect[sectnum];
		while (i != -1)
		{
			nexti = nextspritesect[i];

			//your code goes here
			//ex: printf("Sprite %d is in sector %d\n",i,sectnum);

			i = nexti;
		}

Coding example #2:
	To go through all sprites with status = 1, the code can look like this:

		statnum = 1;        //status 1
		i = headspritestat[statnum];
		while (i != -1)
		{
			nexti = nextspritestat[i];

			//your code goes here
			//ex: printf("Sprite %d has a status of 1 (active)\n",i,statnum);

			i = nexti;
		}

			 insertsprite(short sectnum, short statnum);
			 deletesprite(short spritenum);
			 changespritesect(short spritenum, short newsectnum);
			 changespritestat(short spritenum, short newstatnum);

TILE VARIABLES:
		NUMTILES - the number of tiles found TILES.DAT.
		TILESIZX[MAXTILES] - simply the x-dimension of the tile number.
		TILESIZY[MAXTILES] - simply the y-dimension of the tile number.
		WALOFF[MAXTILES] - the actual 32-bit offset pointing to the top-left
								 corner of the tile.
		PICANM[MAXTILES] - flags for animating the tile.

TIMING VARIABLES:
		TOTALCLOCK - When the engine is initialized, TOTALCLOCK is set to zero.
			From then on, it is incremented 120 times a second by 1.  That
			means that the number of seconds elapsed is totalclock / 120.
		NUMFRAMES - The number of times the draw3dscreen function was called
			since the engine was initialized.  This helps to determine frame
			rate.  (Frame rate = numframes * 120 / totalclock.)

OTHER VARIABLES:

		STARTUMOST[320] is an array of the highest y-coordinates on each column
				that my engine is allowed to write to.  You need to set it only
				once.
		STARTDMOST[320] is an array of the lowest y-coordinates on each column
				that my engine is allowed to write to.  You need to set it only
				once.
		SINTABLE[2048] is a sin table with 2048 angles rather than the
			normal 360 angles for higher precision.  Also since SINTABLE is in
			all integers, the range is multiplied by 16383, so instead of the
			normal -1<sin(x)<1, the range of sintable is -16383<sintable[]<16383
			If you use this sintable, you can possibly speed up your code as
			well as save space in memory.  If you plan to use sintable, 2
			identities you may want to keep in mind are:
				sintable[ang&2047]       = sin(ang * (3.141592/1024)) * 16383
				sintable[(ang+512)&2047] = cos(ang * (3.141592/1024)) * 16383
		NUMSECTORS - the total number of existing sectors.  Modified every time
			you call the loadboard function.
***************************************************************************/
