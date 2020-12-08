.MODEL SMALL
.STACK 100H

.DATA

MSG DB "ADDING NUMBERS IN VAL1 AND VAL2..",13,10,"$"
VAL1 DB 10H
VAL2 DB 31H
VAL3 DB ? ; EXPECTED 65 OR 41H

.CODE


MAIN PROC
        MOV AX,@DATA
        MOV DS,AX
        LEA DX,MSG
        MOV AH,9
        INT 21H
        MOV AL, VAL1
        ADD AL, VAL2 ; ADDING

        MOV VAL3, AL ; STORING IN VAL3
        MOV DL, VAL3
        MOV AH, 02H
        INT 21H ; PRINTING VAL3
       

        ;EXIT
        MOV AH,4CH
        INT 21H


MAIN ENDP
END MAIN


; MASM Q3.ASM && LINK Q3.OBJ && Q3.EXE
