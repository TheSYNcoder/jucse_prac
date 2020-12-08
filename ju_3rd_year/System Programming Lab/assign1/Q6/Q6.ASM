.MODEL SMALL
.STACK 100H

.DATA

MSG1 DB "INPUT A CHARACTER :","$"

.CODE


MAIN PROC
        MOV AX,@DATA
        MOV DS,AX
        LEA DX,MSG1
        MOV AH,9
        INT 21H


        ; INPUT A CHARACTER
        MOV AH,1
        INT 21H

        MOV DL, AL ; STORE IN DL FOR PRINTING

        MOV AH, 02H
        INT 21H


        ;EXIT
        MOV AH,4CH
        INT 21H


MAIN ENDP
END MAIN


; MASM Q3.ASM && LINK Q3.OBJ && Q3.EXE
