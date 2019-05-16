; JSTICK.ASM
;
; by Les Bird for Witchaven
;
; Copyright (c) 1995 IntraCorp, Inc.
;
; ***********************************************************************
; *     void jstick()   - this 'C' callable routine reads the position  *
; *                       of joystick #1 attached to a game-port (0x201)*
; *                       and returns the X position in variable _joyx  *
; *                       and the Y position in variable _joyy and the  *
; *                       button status in variable _joyb               *
; *                                                                     *
; *     _joyb   - xxxx.0000                                             *
; *                 ||                                                  *
; *                 |`-- 0 if joystick #1, button #1 pressed            *
; *                 `--- 0 if joystick #1, button #2 pressed            *
; *                                                                     *
; *     'C' example:                                                    *
; *                                                                     *
; *     extern                                                          *
; *     int joyb,joyx,joyy;                                             *
; *                                                                     *
; *     void                                                            *
; *     main(void)                                                      *
; *     {                                                               *
; *          jstick();                                                  *
; *          printf("Joystick X position = %d",joyx);                   *
; *          printf("Joystick Y position = %d",joyy);                   *
; *          printf("Joystick button stat= %d",joyb);                   *
; *     }                                                               *
; *                                                                     *
; ***********************************************************************
;
.386p
;
JOYPORT equ     201H            ; game-port I/O address
;
_DATA   SEGMENT DWORD PUBLIC 'DATA'
;
EXTRN   _joyb:BYTE      ;   db      0               ; joystick button status
EXTRN   _joyx:WORD      ;   dw      0               ; joystick X position
EXTRN   _joyy:WORD      ;   dw      0               ; joystick Y position
joydn   db      ?               ; internal compare value
joycr   dw      ?               ; internal counter
;
_DATA   ENDS
;
_TEXT   SEGMENT BYTE PUBLIC 'CODE'
        ASSUME  cs:_TEXT, ds:_DATA
;
PUBLIC  jstick_
jstick_ PROC    near
;
        pushf
        push    ebp
        cli
        mov     bx,0
        mov     cx,800h
        mov     joycr,cx
        xor     cx,cx
        mov     dx,JOYPORT
        in      al,dx
        mov     _joyb,al
        and     al,0fh
        mov     joydn,al
        out     dx,al
jloop:  in      al,dx
        push    ax
        and     al,0fh
        cmp     al,joydn
        pop     ax
        jz      jretrn
        dec     joycr
        jz      jretrn
        push    ax
        and     al,1
        pop     ax
        jz      jupdy
        inc     bx
jupdy:  and     al,2
        jz      jloop
        inc     cx
        jmp     jloop
jretrn: mov     _joyx,bx
        mov     _joyy,cx
        pop     ebp
        popf
        ret
;
jstick_ ENDP
;
_TEXT   ENDS
;
        END
