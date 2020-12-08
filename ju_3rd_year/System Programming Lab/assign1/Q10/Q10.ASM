.MODEL SMALL
.STACK 100H

.DATA

MSG1 DB "PRINTING CHARACTERS FROM A TO Z",13,10,"$"

.CODE


MAIN PROC
        MOV AX,@DATA
        MOV DS,AX
        LEA DX,MSG1
        MOV AH,9
        INT 21H

        MOV DL,'A'
        MOV CX, 1AH
        MOV AH, 2
LOOP:
        
        INT 21H
        INC DL
        DEC CX
        JNZ LOOP

        ;ENDING PROG
        MOV AH, 4CH
        INT 21H


MAIN ENDP
END MAIN


; MASM Q3.ASM && LINK Q3.OBJ && Q3.EXE
