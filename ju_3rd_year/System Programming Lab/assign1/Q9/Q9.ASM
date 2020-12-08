.MODEL SMALL
.STACK 100H

.DATA

MSG1 DB "LOOPING... PRESS Q TO QUIT :",13,10,"$"
LMSG DB "looping .... ENTER Q TO QUIT",13,10,"$"
.CODE


MAIN PROC
        MOV AX,@DATA
        MOV DS,AX
        LEA DX,MSG1
        MOV AH,9
        INT 21H

        

LOOP:
        MOV AH,9
        LEA DX, LMSG
        INT 21H
        MOV AH,1
        INT 21H
        CMP AL, 'Q'
        JNZ LOOP

        ;EXIT
        MOV AH,4CH
        INT 21H


MAIN ENDP
END MAIN


; MASM Q3.ASM && LINK Q3.OBJ && Q3.EXE
