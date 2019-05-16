;/***************************************************************************
; *   TEKASM.ASM  - assembly code for Tekwar game                           *
; *                                                                         *
; *                                                      3/29/95 Jeff S.    *
; ***************************************************************************/
                
        .586p     ; 386, 486, Pentium

        ; Declare non-parameter registers that you alter as
        ; a #pragma in the C++ file.

        ASSUME  CS:_TEXT
        ASSUME  DS:_DATA

                EXTRN   faketimerhandler_ :BYTE

_DATA           SEGMENT 'DATA' USE32

return_code     dd      0
integer_data    dd      0

_DATA           ENDS


_TEXT           SEGMENT PUBLIC 'CODE' USE32

;
; (template to follow)
;
;     On entry: eax = pointer to integer number,
;               ebx = value to store at address eax.
;
;asm_main_       PROC    NEAR
;                
;                call    protected_code  ; Call your own code...
;                cld                     ; Direction bit must be clear on exit.
;                mov     eax, [return_code]; EAX = return value (if required).
;                ret
;
;asm_main_       ENDP

                PUBLIC  asmwaitvrt_      ; Note underscore AFTER function name.

asmwaitvrt_     PROC    NEAR
                
@@wait:
                xor     edx,edx
                xor     eax,eax
	        xor	dx, 0x03DA

                ; ecx loaded via param
                ; wait for a display signal to make sure the raster isn't 
                ; in the middle of a sync

                ;call    near ptr faketimerhandler_

@@waitnosync:
        	in	al,dx
	        test	al,8
	        jnz	@@waitnosync

@@waitsync:
        	in	al,dx
	        test	al,8
	        jz	@@waitsync

	        loop	@@waitnosync

                cld                      ; Direction bit must be clear on exit.
                ret

asmwaitvrt_     ENDP

                PUBLIC  asmsetpalette_ 

asmsetpalette_  PROC    NEAR
                
                ; pal ptr passed in esi
                xor     eax, eax
	        mov	edx,0x000003C8   ; PEL_WRITE_ADR
	        out	dx,al
	        mov	edx,0x000003C9   ; PEL_DATA

                mov	ecx,0x00000100   ; 256
@@setloop:
        	lodsb
	        out	dx,al
        	lodsb
        	out	dx,al
        	lodsb
        	out	dx,al
        	loop	@@setloop

                cld      
                ret

asmsetpalette_  ENDP

                PUBLIC  asmoverscan_ 

asmoverscan_    PROC    NEAR
                
                ; ovrscn color passed in ebx
                
                mov     edx, 0x000003DA  ; STATUS_REGISTER_1
                in      al,  dx
                mov     edx, 0x000003C0  ; ATR_INDEX
                mov     eax, 0x00000011  ; ATR_OVERSCAN	
                out     dx,  al
                mov     eax, ebx
                out     dx,  al
                mov     eax, 0x20
                out     dx, al
                
                cld
                ret

asmoverscan_    ENDP
 
                PUBLIC  asmoverflash_ 

asmoverflash_   PROC    NEAR
                
                ; ovrscn color passed in ebx
                
                mov     edx, 0x000003DA  ; STATUS_REGISTER_1
                in      al,  dx
                mov     edx, 0x000003C0  ; ATR_INDEX
                mov     eax, 0x00000011  ; ATR_OVERSCAN	
                out     dx,  al
                mov     eax, ebx
                out     dx,  al
                mov     eax, 0x20
                out     dx, al
                
                mov     ecx, 0x00000002
                call    asmwaitvrt_

                mov     edx, 0x000003DA  ; STATUS_REGISTER_1
                in      al,  dx
                mov     edx, 0x000003C0  ; ATR_INDEX
                mov     eax, 0x00000011  ; ATR_OVERSCAN	
                out     dx,  al
                mov     eax, 0x00000000
                out     dx,  al
                mov     eax, 0x20
                out     dx, al

                cld
                ret

asmoverflash_   ENDP

                PUBLIC  asmcpuid_ 

asmcpuid_       PROC    NEAR
                
		mov	bx,sp		        ; save current stack pointer to align it
		and	sp,not 3                ; align stack to avoid AC fault
		db	66h
		pushf			        ; push original EFLAGS
		db	66h
		pop	ax		        ; get original EFLAGS 
		db	66h
		mov	cx,ax		        ; save original EFLAGS
		db	66h		        ; xor EAX,40000h
		xor	ax,0		        ; flip AC bit in EFLAGS
		dw	4		        ; upper 16-bits of xor constant
		db	66h
		push	ax		        ; save for EFLAGS
		db	66h
		popf			        ; copy to EFLAGS
		db	66h
		pushf			        ; push EFLAGS
		db	66h
		pop	ax		        ; get new EFLAGS value
		db	66h
		xor	ax,cx		        ; if AC bit cannot be changed, CPU is
		je	not386   	        ; if CPU is i386, now check for 

                mov     eax, 1                  ; return 1 for 386
                jmp goback

not386:
                mov     eax, 2

goback:
		db	66h
		push	cx			; push ECX
		db	66h
		popf				; restore original EFLAGS register
		mov	sp,bx			; restore original stack pointer
                
                cld
                ret

asmcpuid_       ENDP

_TEXT           ENDS

                END
