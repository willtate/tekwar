#ifndef SMACKH
#define SMACKH

#ifndef __RAD__
#define __RAD__

#define RADCOPYRIGHT "Copyright (c) RAD Software, 1994-95."


//  __RAD386__ means 386 code (DOS, Win386, Win32s)
//  __RADWIN__ means Windows code (Win16, Win386, Win32s)
//  __RADNORMALWIN__ means normal Windows (Win16, Win32s)
//  __RADNT__ means Win32s code


#ifdef __386__
  #define __RAD386__
#endif

#ifdef _Windows    //For Borland
  #ifdef __WIN32__
    #define WIN32
  #else
    #define __WINDOWS__
  #endif
#endif


#ifdef _WIN32           //For MS
  #define __RADWIN__
  #define __RADNORMALWIN__
  #define __RADNT__
  #define __RAD386__
#else
  #ifdef __NT__
    #define __RADNT__
    #define __RAD386__
    #define __RADWIN__
    #define __RADNORMALWIN__
  #else
    #ifdef __WINDOWS_386__
      #define __RADWIN__
      #define __RAD386__
    #else
      #ifdef __WINDOWS__
	#define __RADWIN__
	#define __RADNORMALWIN__
      #else 
	#ifdef WIN32
	  #define __RADWIN__
	  #define __RADNORMALWIN__
	  #define __RADNT__
	  #define __RAD386__
	#endif
      #endif
    #endif
  #endif
#endif

#ifdef __RADWIN__
  #define INCLUDE_MMSYSTEM_H
  #include "windows.h"
  #include "windowsx.h"
#endif

#ifdef __RADWIN__
  #ifdef __RAD386__
    #ifdef __RADNT__
      #define RADEXPLINK __cdecl
      #ifdef __WATCOMC__
	#define RADLINK __pascal
      #else
	#define RADLINK
      #endif
    #else
      #define RADLINK __pascal
      #define RADEXPLINK __far __pascal
    #endif
  #else
    #define RADLINK __far __pascal
    #define RADEXPLINK __export __far __pascal
  #endif
#else
  #define RADLINK __pascal
  #define RADEXPLINK __pascal
#endif

#ifdef __cplusplus
  #define RCFUNC extern "C"
  #define RCSTART extern "C" {
  #define RCEND }
#else
  #define RCFUNC 
  #define RCSTART 
  #define RCEND 
#endif

RCSTART

#define s8 signed char
#define u8 unsigned char
#define u32 unsigned long
#define s32 signed long

#ifdef __RAD386__
  #define PTR4

  #define u16 unsigned short
  #define s16 signed short

  #ifdef __WATCOMC__

    u32 mult64anddiv(u32 m1,u32 m2,u32 d);
    #pragma aux mult64anddiv = "mul ecx" "div ebx" parm [eax] [ecx] [ebx] modify [EDX eax];

    s32 radabs(s32 ab);
    #pragma aux radabs = "test eax,eax" "jge skip" "neg eax" "skip:" parm [eax];

    #define radabs32 radabs

    u32 DOSOut(char* str);
    #pragma aux DOSOut = "cld" "mov ecx,0xffffffff" "xor eax,eax" "mov edx,edi" "repne scasb" "not ecx" "dec ecx" "mov ebx,1" "mov ah,0x40" "int 0x21" parm [EDI] modify [EAX EBX ECX EDX EDI] value [ecx];
    
    void DOSOutNum(char* str,u32 len);
    #pragma aux DOSOutNum = "mov ah,0x40" "mov ebx,1" "int 0x21" parm [edx] [ecx] modify [eax ebx];

    u32 ErrOut(char* str);
    #pragma aux ErrOut = "cld" "mov ecx,0xffffffff" "xor eax,eax" "mov edx,edi" "repne scasb" "not ecx" "dec ecx" "xor ebx,ebx" "mov ah,0x40" "int 0x21" parm [EDI] modify [EAX EBX ECX EDX EDI] value [ecx];
    
    void ErrOutNum(char* str,u32 len);
    #pragma aux ErrOutNum = "mov ah,0x40" "xor ebx,ebx" "int 0x21" parm [edx] [ecx] modify [eax ebx];

    void radmemset16(void* dest,u16 value,u32 size);
    #pragma aux radmemset16 = "cld" "mov bx,ax" "shl eax,16" "mov ax,bx" "mov bl,cl" "shr ecx,1" "rep stosd" "mov cl,bl" "and cl,1" "rep stosb" parm [EDI] [EAX] [ECX] modify [EAX EDX EBX ECX EDI];
    
    //void radmemset(void* dest,u8 value,u32 size);
    //#pragma aux radmemset = "cld" "mov ah,al" "mov bx,ax" "shl eax,16" "mov ax,bx" "mov bl,cl" "shr ecx,2" "rep stosd" "mov cl,bl" "and cl,3" "rep stosb" parm [EDI] [AL] [ECX] modify [EAX EDX EBX ECX EDI];

    void radmemcpy(void* dest,void* source,u32 size);
    #pragma aux radmemcpy = "cld" "mov bl,cl" "shr ecx,2" "rep movsd" "mov cl,bl" "and cl,3" "rep movsb" parm [EDI] [ESI] [ECX] modify [EBX ECX EDI ESI];

    void __far *radfmemcpy(void __far* dest,void __far* source,u32 size);
    #pragma aux radfmemcpy = "cld" "push es" "push ds" "mov es,cx" "mov ds,dx" "mov ecx,eax" "shr ecx,2" "rep movsd" "mov cl,al" "and cl,3" "rep movsb" "pop ds" "pop es" parm [CX EDI] [DX ESI] [EAX] modify [ECX EDI ESI] value [CX EDI];

    void radmemcpydb(void* dest,void* source,u32 size);  //Destination bigger
    #pragma aux radmemcpydb = "std" "mov bl,cl" "lea esi,[esi+ecx-4]" "lea edi,[edi+ecx-4]" "shr ecx,2" "rep movsd" "and bl,3" "jz dne" "add esi,3" "add edi,3" "mov cl,bl" "rep movsb" "dne:" "cld" parm [EDI] [ESI] [ECX] modify [EBX ECX EDI ESI];

    char* radstrcpy(void* dest,void* source);
    #pragma aux radstrcpy = "cld" "mov edx,edi" "lp:" "mov al,[esi]" "inc esi" "mov [edi],al" "inc edi" "cmp al,0" "jne lp" parm [EDI] [ESI] modify [EAX EDX EDI ESI] value [EDX];

    char __far* radfstrcpy(void __far* dest,void __far* source);
    #pragma aux radfstrcpy = "cld" "push es" "push ds" "mov es,cx" "mov ds,dx" "mov edx,edi" "lp:" "lodsb" "stosb" "test al,0xff" "jnz lp" "pop ds" "pop es" parm [CX EDI] [DX ESI] modify [EAX EDX EDI ESI] value [CX EDX];

    char* radstpcpy(void* dest,void* source);
    #pragma aux radstpcpy = "cld" "lp:" "mov al,[esi]" "inc esi" "mov [edi],al" "inc edi" "cmp al,0" "jne lp" "dec edi" parm [EDI] [ESI] modify [EAX EDI ESI] value [EDI];

    char* radstpcpyrs(void* dest,void* source);
    #pragma aux radstpcpyrs = "cld" "lp:" "lodsb" "stosb" "test al,0xff" "jnz lp" "dec edi" parm [EDI] [ESI] modify [EAX EDI ESI] value [ESI];

    u32 radstrlen(void* dest);
    #pragma aux radstrlen = "cld" "mov ecx,0xffffffff" "xor eax,eax" "repne scasb" "not ecx" "dec ecx" parm [EDI] modify [EAX ECX EDI] value [ECX];
    
    char* radstrcat(void* dest,void* source);
    #pragma aux radstrcat = "cld" "mov ecx,0xffffffff" "mov edx,edi" "xor eax,eax" "repne scasb" "dec edi" "lp:" "lodsb" "stosb" "test al,0xff" "jnz lp" \
      parm [EDI] [ESI] modify [EAX ECX EDI ESI] value [EDX];
    
    char* radstrchr(void* dest,char chr);
    #pragma aux radstrchr = "cld" "lp:" "lodsb" "cmp al,dl" "je fnd" "cmp al,0" "jnz lp" "mov esi,1" "fnd:" "dec esi" parm [ESI] [DL] modify [EAX ESI] value [esi];

    s8 radmemcmp(void* s1,void* s2,u32 len);
    #pragma aux radmemcmp = "cld" "rep cmpsb" "setne al" "jbe end" "neg al" "end:"  parm [EDI] [ESI] [ECX] modify [ECX EDI ESI];

    s8 radstrcmp(void* s1,void* s2);
    #pragma aux radstrcmp = "lp:" "mov al,[esi]" "mov ah,[edi]" "cmp al,ah" "jne set" "cmp al,0" "je set" "inc esi" "inc edi" "jmp lp" "set:" "setne al" "jbe end" "neg al" "end:" \
      parm [EDI] [ESI] modify [EAX EDI ESI];

    s8 radstricmp(void* s1,void* s2);                                                                       
    #pragma aux radstricmp = "lp:" "mov al,[esi]" "mov ah,[edi]" "cmp al,'a'" "jb c1" "cmp al,'z'" "ja c1" "sub al,32" "c1:" "cmp ah,'a'" "jb c2" "cmp ah,'z'" "ja c2" "sub ah,32" "c2:" "cmp al,ah" "jne set" "cmp al,0" "je set" \
      "inc esi" "inc edi" "jmp lp" "set:" "setne al" "jbe end" "neg al" "end:" \
      parm [EDI] [ESI] modify [EAX EDI ESI];

    s8 radstrnicmp(void* s1,void* s2,u32 len);
    #pragma aux radstrnicmp = "lp:" "mov al,[esi]" "mov ah,[edi]" "cmp al,'a'" "jb c1" "cmp al,'z'" "ja c1" "sub al,32" "c1:" "cmp ah,'a'" "jb c2" "cmp ah,'z'" "ja c2" "sub ah,32" "c2:" "cmp al,ah" "jne set" "cmp al,0" "je set" \
      "dec ecx" "jz set" "inc esi" "inc edi" "jmp lp" "set:" "setne al" "jbe end" "neg al" "end:" \
      parm [EDI] [ESI] [ECX] modify [EAX ECX EDI ESI];

    char* radstrupr(void* s1);
    #pragma aux radstrupr = "mov ecx,edi" "lp:" "mov al,[edi]" "cmp al,'a'" "jb c1" "cmp al,'z'" "ja c1" "sub [edi],32" "c1:" "inc edi" "cmp al,0" "jne lp" parm [EDI] modify [EAX EDI] value [ecx];

    char* radstrlwr(void* s1);
    #pragma aux radstrlwr = "mov ecx,edi" "lp:" "mov al,[edi]" "cmp al,'A'" "jb c1" "cmp al,'Z'" "ja c1" "add [edi],32" "c1:" "inc edi" "cmp al,0" "jne lp" parm [EDI] modify [EAX EDI] value [ecx];

    u32 radstru32(void* dest);
    #pragma aux radstru32 = "cld" "xor ecx,ecx" "xor ebx,ebx" "xor edi,edi" "lodsb" "cmp al,45" "jne skip2" "mov edi,1" "jmp skip" "lp:" "mov eax,10" "mul ecx" "lea ecx,[eax+ebx]" \
      "skip:" "lodsb" "skip2:" "cmp al,0x39" "ja dne" "cmp al,0x30" "jb dne" "mov bl,al" "sub bl,0x30" "jmp lp" "dne:" "test edi,1" "jz pos" "neg ecx" "pos:" \
       parm [ESI] modify [EAX EBX EDX EDI ESI] value [ecx];
														     
    u16 GetDS();
    #pragma aux GetDS = "mov ax,ds" value [ax];

    #ifdef __WINDOWS_386__
    
    u32 GetBase(u16 sel);
    #pragma aux GetBase = "mov bx,ax" "mov ax,6" "int 0x31" "shrd eax,ecx,16" "mov ax,dx" parm [ax] modify [ax bx cx dx] value [eax];

    #define _16To32(ptr16) ((void*)(((GetBase((u16)(((u32)(ptr16))>>16))+((u16)(u32)(ptr16)))-GetBase(GetDS()))))

    #endif

    #ifndef __RADWIN__
      #define int86 int386
      #define int86x int386x
    #endif
    
    #define u32regs x
    #define u16regs w
    
  #else
    #define radmemset memset
    #define radmemcpy memcpy

    #define u32regs e
    #define u16regs x
  
  #endif

#else
  #define PTR4 __far
  
  #define u16 unsigned int
  #define s16 signed int

  #ifdef __WATCOMC__
    
    s16 radabs(s16 ab);
    #pragma aux radabs = "test ax,ax" "jge skip" "neg ax" "skip:" parm [ax] value [ax];
    
    s32 radabs32(s32 ab);
    #pragma aux radabs32 = "test dx,dx" "jge skip" "neg dx" "neg ax" "sbb dx,0" "skip:" parm [dx ax] value [dx ax];
    
    u32 DOSOut(char far* dest);
    #pragma aux DOSOut = "cld" "and edi,0xffff" "mov dx,di" "mov ecx,0xffffffff" "xor eax,eax" 0x67 "repne scasb" "not ecx" "dec ecx" "mov bx,1" "push ds" "push es" "pop ds" "mov ah,0x40" "int 0x21" "pop ds" "movzx eax,cx" "shr ecx,16" \
			 parm [ES DI] modify [AX BX CX DX DI ES] value [CX AX];
    
    void DOSOutNum(char far* str,u16 len);
    #pragma aux DOSOutNum = "push ds" "mov ds,cx" "mov cx,bx" "mov ah,0x40" "mov bx,1" "int 0x21" "pop ds" parm [cx dx] [bx] modify [ax bx cx];

    u32 ErrOut(char far* dest);
    #pragma aux ErrOut = "cld" "and edi,0xffff" "mov dx,di" "mov ecx,0xffffffff" "xor eax,eax" 0x67 "repne scasb" "not ecx" "dec ecx" "xor bx,bx" "push ds" "push es" "pop ds" "mov ah,0x40" "int 0x21" "pop ds" "movzx eax,cx" "shr ecx,16" \
			 parm [ES DI] modify [AX BX CX DX DI ES] value [CX AX];
    
    void ErrOutNum(char far* str,u16 len);
    #pragma aux ErrOutNum = "push ds" "mov ds,cx" "mov cx,bx" "mov ah,0x40" "xor bx,bx" "int 0x21" "pop ds" parm [cx dx] [bx] modify [ax bx cx];

    void radmemset(void far *dest,u8 value,u32 size);
    #pragma aux radmemset = "cld" "and edi,0ffffh" "shl ecx,16" "mov cx,bx" "mov ah,al" "mov bx,ax" "shl eax,16" "mov ax,bx" "mov bl,cl" "shr ecx,2" 0x67 "rep stosd" "mov cl,bl" "and cl,3" "rep stosb" parm [ES DI] [AL] [CX BX];
    
    void radmemcpy(void far* dest,void far* source,u32 size);
    #pragma aux radmemcpy = "cld" "push ds" "mov ds,dx" "and esi,0ffffh" "and edi,0ffffh" "shl ecx,16" "mov cx,bx" "shr ecx,2" 0x67 "rep movsd" "mov cl,bl" "and cl,3" "rep movsb" "pop ds" parm [ES DI] [DX SI] [CX BX] modify [CX SI DI ES];
    
    char far* radstrcpy(void far* dest,void far* source);
    #pragma aux radstrcpy = "cld" "push ds" "mov ds,dx" "and esi,0xffff" "and edi,0xffff" "mov dx,di" "lp:" "lodsb" "stosb" "test al,0xff" "jnz lp" "pop ds" parm [ES DI] [DX SI] modify [AX DX DI SI ES] value [es dx];

    char far* radstpcpy(void far* dest,void far* source);
    #pragma aux radstpcpy = "cld" "push ds" "mov ds,dx" "and esi,0xffff" "and edi,0xffff" "lp:" "lodsb" "stosb" "test al,0xff" "jnz lp" "dec di" "pop ds" parm [ES DI] [DX SI] modify [DI SI ES] value [es di];

    u32 radstrlen(void far* dest);
    #pragma aux radstrlen = "cld" "and edi,0xffff" "mov ecx,0xffffffff" "xor eax,eax" 0x67 "repne scasb" "not ecx" "dec ecx" "movzx eax,cx" "shr ecx,16" parm [ES DI] modify [AX CX DI ES] value [CX AX];
    
    char far* radstrcat(void far* dest,void far* source);
    #pragma aux radstrcat = "cld" "and edi,0xffff" "mov ecx,0xffffffff" "and esi,0xffff" "push ds" "mov ds,dx" "mov dx,di" "xor eax,eax" 0x67 "repne scasb" "dec edi" "lp:" "lodsb" "stosb" "test al,0xff" "jnz lp" "pop ds" \
      parm [ES DI] [DX SI] modify [AX CX DI SI ES] value [es dx];
    
    char far* radstrchr(void far* dest,char chr);
    #pragma aux radstrchr = "cld" "lp:" 0x26 "lodsb" "cmp al,dl" "je fnd" "cmp al,0" "jnz lp" "xor ax,ax" "mov es,ax" "mov si,1" "fnd:" "dec si" parm [ES SI] [DL] modify [AX SI ES] value [es si];
    
    s8 radstricmp(void far* s1,void far* s2);                                                                       
    #pragma aux radstricmp = "and edi,0xffff" "push ds" "mov ds,dx" "and esi,0xffff" "lp:" "mov al,[esi]" "mov ah,[edi]" "cmp al,'a'" "jb c1" "cmp al,'z'" "ja c1" "sub al,32" "c1:" \
      "cmp ah,'a'" "jb c2" "cmp ah,'z'" "ja c2" "sub ah,32" "c2:" "cmp al,ah" "jne set" "cmp al,0" "je set" \
      "inc esi" "inc edi" "jmp lp" "set:" "setne al" "jbe end" "neg al" "end:" "pop ds" \
      parm [ES DI] [DX SI] modify [AX DI SI];

    u32 radstru32(void far* dest);
    #pragma aux radstru32 = "cld" "xor ecx,ecx" "xor ebx,ebx" "xor edi,edi" "lodsb" "cmp al,45" "jne skip2" "mov edi,1" "jmp skip" "lp:" "mov eax,10" "mul ecx" "lea ecx,[eax+ebx]" \
      "skip:" 0x26 "lodsb" "skip2:" "cmp al,0x39" "ja dne" "cmp al,0x30" "jb dne" "mov bl,al" "sub bl,0x30" "jmp lp" "dne:" "test edi,1" "jz pos" "neg ecx" "pos:" \
      "movzx eax,cx" "shr ecx,16" parm [ES SI] modify [AX BX DX DI SI] value [cx ax];

    u32 mult64anddiv(u32 m1,u32 m2,u32 d);
    #pragma aux mult64anddiv = "shl ecx,16" "mov cx,ax" "shrd eax,edx,16" "mov ax,si" "mul ecx" "shl edi,16" "mov di,bx" "div edi" "shld edx,eax,16" "and edx,0xffff" "and eax,0xffff" parm [cx ax] [dx si] [di bx] \
      modify [ax bx cx dx si di] value [dx ax];
    
  #else
    #define radmemset memset
    #define radmemcpy memcpy
    #define radstrcpy strcpy
  #endif

#endif

RCEND

RCFUNC void PTR4* RADLINK radmalloc(u32 numbytes);
RCFUNC void RADLINK radfree(void PTR4* ptr);
  
#ifdef __WATCOMC__

  char bkbhit();
  #pragma aux bkbhit = "mov ah,1" "int 0x16" "lahf" "shr eax,14" "and eax,1" "xor al,1" ;

  char bgetch();
  #pragma aux bgetch = "xor ah,ah" "int 0x16" "test al,0xff" "jnz done" "mov al,ah" "or al,0x80" "done:" modify [AX];

  void BreakPoint();
  #pragma aux BreakPoint = "int 3";

  u8 radinp(u16 p);
  #pragma aux radinp = "in al,dx" parm [DX];
    
  u8 radtoupper(u8 p);
  #pragma aux radtoupper = "cmp al,'a'" "jb c1" "cmp al,'z'" "ja c1" "sub al,32" "c1:" parm [al] value [al];
    
  //void radoutp(u16 p,u8 v);
  //#pragma aux radoutp = "out dx,al" parm [DX] [AL];

#endif

#endif

RCSTART

#define SMACKVERSION "2.0c"

typedef struct SmackSumTag {
  u32 TotalTime;         // total time
  u32 MS100PerFrame;     // MS*100 per frame (100000/MS100PerFrame=Frames/Sec)
  u32 TotalOpenTime;     // Time to open and prepare for decompression
  u32 TotalFrames;       // Total Frames displayed
  u32 SkippedFrames;     // Total number of skipped frames
  u32 TotalBlitTime;     // Total time spent blitting
  u32 TotalReadTime;     // Total time spent reading 
  u32 TotalDecompTime;   // Total time spent decompressing
  u32 TotalReadSpeed;    // Total io speed (bytes/second)
  u32 SlowestFrameTime;  // Slowest single frame time
  u32 Slowest2FrameTime; // Second slowest single frame time
  u32 SlowestFrameNum;   // Slowest single frame number
  u32 Slowest2FrameNum;  // Second slowest single frame number
  u32 AverageFrameSize;  // Average size of the frame
  u32 HighestMemAmount;  // Highest amount of memory allocated
} SmackSum;

typedef struct SmackTag {
  u32 Version;           // SMK2 only right now
  u32 Width;             // Width (1 based, 640 for example)
  u32 Height;            // Height (1 based, 480 for example)
  u32 Frames;            // Number of frames (1 based, 100 = 100 frames)
  u32 MSPerFrame;        // Frame Rate
  u32 FlicType;          // bit 0 set=ring frame
  u32 LargestInTrack[7]; // Largest single size for each track
  u32 tablesize;         // Size of the init tables
  u32 codesize;          // Compression info   
  u32 absize;            // ditto
  u32 detailsize;        // ditto
  u32 typesize;          // ditto
  u32 TrackType[7];      // high byte=0x80-Comp,0x40-PCM data,0x20-16 bit,0x10-stereo
  u32 extra;             // extra value (should be zero)
  u32 NewPalette;        // set to one if the palette changed
  u32 CurPalette;        // 1=first palette, 2=second palette
  u8  Col1[772];         // first palette
  u8  Col2[772];         // second palette          
  u32 FrameNum;          // Frame Number to be displayed
  u32 InBufSize;         // size of the buffer allocated for inbuf
  u32 ExtraBuf;          // size used for extra amount
  u32 LastRectx;         // Rect set in from SmackToBufferRect (X coord)
  u32 LastRecty;         // Rect set in from SmackToBufferRect (Y coord)
  u32 LastRectw;         // Rect set in from SmackToBufferRect (Width)
  u32 LastRecth;         // Rect set in from SmackToBufferRect (Height)
  u32 OpenFlags;         // flags used on open
  u32 LeftOfs;           // Left Offset used in SmackTo
  u32 TopOfs;            // Top Offset used in SmackTo
} Smack;              

#define SmackHeaderSize(smk) ((((u8*)&((smk)->extra))-((u8*)(smk)))+4)

//=======================================================================
#define SMACKPRELOADALL  32L   // Preload the entire animation
#define SMACKNOSKIP      64L   // Don't skip frames if falling behind
#define SMACKSIMULATE   128L   // Simulate the speed (call SmackSim first)
#define SMACKFILEHANDLE 256L   // Use when passing in a file handle
#define SMACKTRACK1     512L   // Play audio track 1
#define SMACKTRACK2    1024L   // Play audio track 2
#define SMACKTRACK3    2048L   // Play audio track 3
#define SMACKTRACK4    4096L   // Play audio track 4
#define SMACKTRACK5    8192L   // Play audio track 5
#define SMACKTRACK6   16384L   // Play audio track 6
#define SMACKTRACK7   32768L   // Play audio track 7
#define SMACKTRACKS (SMACKTRACK1|SMACKTRACK2|SMACKTRACK3|SMACKTRACK4|SMACKTRACK5|SMACKTRACK6|SMACKTRACK7)

#define SMACKAUTOEXTRA 0xffffffffL // NOT A FLAG! - Use as extrabuf param 
//=======================================================================
  
#define SMACKSURFACEFAST     0
#define SMACKSURFACESLOW     1
#define SMACKSURFACEDIRECT   2


Smack PTR4* RADEXPLINK SmackOpen(char PTR4* name,u32 flags,u32 extrabuf);
u16  RADEXPLINK SmackDoFrame(Smack PTR4* smk);
void RADEXPLINK SmackNextFrame(Smack PTR4* smk);
u16  RADEXPLINK SmackWait(Smack PTR4* smk);
void RADEXPLINK SmackClose(Smack PTR4* smk);

void RADEXPLINK SmackVolume(Smack PTR4* smk, u32 trackflag,u16 left,u16 right);    

void RADEXPLINK SmackSummary(Smack PTR4* smk,SmackSum PTR4* sum);

u16  RADEXPLINK SmackSoundInTrack(Smack PTR4* smk,u32 trackflags);
u16  RADEXPLINK SmackSoundOnOff(Smack PTR4* smk,u16 on);

void RADEXPLINK SmackToScreen(Smack PTR4* smk,u32 left,u32 top,u32 BytesPS,u16 PTR4* WinTbl,u32 SetBank);
void RADEXPLINK SmackToBuffer(Smack PTR4* smk,u32 left,u32 top,u32 destwidth,u32 destheight,void PTR4* buf,u16 Reversed);
u16  RADEXPLINK SmackToBufferRect(Smack PTR4* smk, u16 SmackSurface);

void RADEXPLINK SmackGoto(Smack PTR4* smk,u32 frame);
void RADEXPLINK SmackColorRemap(Smack PTR4* smk,void PTR4* remap,u16 colors,u16 paltype);
void RADEXPLINK SmackColorTrans(Smack PTR4* smk,void PTR4* trans);
void RADEXPLINK SmackFrameRate(Smack PTR4* smk,u32 forcerate);
void RADEXPLINK SmackSimulate(u32 sim);

u32  RADEXPLINK SmackGetTrackData(Smack PTR4* smk,void PTR4* dest,u32 trackflag);

void RADEXPLINK SmackSoundCheck();

//======================================================================
#ifdef __RADWIN__

  #define INCLUDE_MMSYSTEM_H
  #include "windows.h"
  #include "windowsx.h"

  void RADEXPLINK SmackGet(Smack PTR4* smk,void PTR4* dest);

  #define SmackTimerSetup()
  #define SmackTimerDone()
  #define SmackTimerRead timeGetTime

  //=======================================================================
  #define SMACKAUTOBLIT        0
  #define SMACKFULL320X240BLIT 1
  #define SMACKFULL320X200BLIT 2
  #define SMACKSTANDARDBLIT    3
  #define SMACKVFWBLIT         4 
  #define SMACKWINGBLIT        5
  #define SMACKDCIBLIT         6

  #define WM_SMACKACTIVATE WM_USER+0x5678

  typedef struct SmackBufTag {
    u32 Reversed;             // 1 if the buffer is upside down
    u32 SurfaceType;          // SMACKSURFACExxxx defines
    u32 BlitType;             // SMACKxxxxBLIT defines
    u32 FullScreen;           // 1 if full-screen
    u32 Width;
    u32 Height;
    u32 Zoomed;
    u32 ZWidth;
    u32 ZHeight;
    u32 DispColors;           // colors on the screen
    u32 MaxPalColors;         // total possible colors in palette (usually 256)
    u32 PalColorsInUse;       // Used colors in palette (usually 236)
    u32 StartPalColor;        // first usable color index (usually 10)
    u32 EndPalColor;          // last usable color index (usually 246)
 
    void PTR4* Buffer;
    void PTR4* DIBRestore;
    u32 OurBitmap;
    u32 OrigBitmap;
    u32 OurPalette;
    u32 WinGDC;
    u32 FullFocused;
    u32 ParentHwnd;
    u32 OldParWndProc;
    u32 OldDispWndProc;
    u32 DispHwnd;
    #ifdef __WINDOWS_386__
      u32 WinGBufHandle;
    #endif
    RGBQUAD DIBPalette[256];
  } SmackBuf;

  char PTR4* RADEXPLINK SmackBufferString(char PTR4* dest,WORD BlitType);
  SmackBuf PTR4* RADEXPLINK SmackBufferOpen(  HWND wnd, WORD BlitType, WORD width, WORD height, WORD ZoomW, WORD ZoomH );
  u16  RADEXPLINK SmackBufferBlit( SmackBuf PTR4* sbuf, HDC dc, WORD hwndx, WORD hwndy, WORD subx, WORD suby, WORD subw, WORD subh );
  void RADEXPLINK SmackBufferNewPalette( SmackBuf PTR4* sbuf, void PTR4* pal );
  u16  RADEXPLINK SmackBufferSetPalette( SmackBuf PTR4* sbuf );
  u16  RADEXPLINK SmackBufferFocused( SmackBuf PTR4* sbuf);
  void RADEXPLINK SmackBufferClose( SmackBuf PTR4* sbuf );

  void RADEXPLINK SmackBufferClear( SmackBuf PTR4* destbuf, u8 color);
  void RADEXPLINK SmackBufferToBuffer( SmackBuf PTR4* destbuf, WORD destx, WORD desty, SmackBuf PTR4* sourcebuf,WORD sourcex,WORD sourcey,WORD sourcew,WORD sourceh);
  void RADEXPLINK SmackBufferToBufferTrans( SmackBuf PTR4* destbuf, WORD destx, WORD desty, SmackBuf PTR4* sourcebuf,WORD sourcex,WORD sourcey,WORD sourcew,WORD sourceh,WORD TransColor);
  void RADEXPLINK SmackBufferFromScreen( SmackBuf PTR4* destbuf, HWND hw, WORD x, WORD y);
  void RADEXPLINK SmackBufferCopyPalette( SmackBuf PTR4* destbuf, SmackBuf PTR4* sourcebuf, u16 remap);

  void RADEXPLINK SmackBufferGet( SmackBuf PTR4* sbuf, void PTR4* dest);
  //=======================================================================

#else
  u8 RADEXPLINK LowSoundDriverLoaded();
  u8 RADEXPLINK LowSoundDriverLoad(char PTR4* cfgfilename);
  u8 RADEXPLINK LowSoundDriverUnload();
  void RADEXPLINK LowSoundShutDown();
  
  void cdecl SmackTimerSetup();
  u32  cdecl SmackTimerRead();
  void cdecl SmackTimerDone();

  void cdecl SetSmackAILDigDriver(void* dd,u32 MaxTimerSpeed);//Miles's AIL
  void cdecl SetSmackSOSHandle(u16 SmackHandle,u32 MaxTimerSpeed);//HMI's SOS
#endif

RCEND

#endif

#ifndef SVGAH
#define SVGAH

RCSTART
  
  typedef void (SETBANKTYPE)(u16);
  #pragma aux SETBANKTYPE "*" parm [eax] modify [eax];

  typedef void (SETINITTYPE)();
  #pragma aux SETINITTYPE "*" modify [eax ebx ecx edx];

  #define SVGAMode() (curmodetouse)
  u8    RADLINK SVGASetup(int width,int height);
  char* RADLINK SVGADetected(char* buf);
  void  RADLINK SVGASetText();
  void  RADLINK SVGASetGraph();
  void  RADLINK SVGAClear(u8 col);
  void  RADLINK SVGADetect(u8 dosvga);
  u32   RADLINK SVGABytesPS();
  u16*  RADLINK SVGAWinTbl();
  u32   RADLINK SVGASetBank();

  void  cdecl SVGABlit(void* buf,u32 bleft,u32 btop,u32 subbwidth,u32 subbheight,u32 bwidth,u32 screenleft,u32 screentop);
  void cdecl PaletteSet(void PTR4* pal);

  extern u8 curmodetouse;
  extern u32 BytesPerScanToUse;
  extern u32 WidthToUse;
  extern u32 HeightToUse;
  extern SETBANKTYPE* SetBankToUse;
  extern u16* WinTblToUse;
  extern void* StartVGA;
  extern void* EndVGA;
  extern u32 VGASize;
  extern u8 PaletteSkipZero;
  extern u8 IsBanked;
  extern u8 SVGAVESASetting;

RCEND

#endif

