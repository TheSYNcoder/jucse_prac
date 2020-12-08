.model SMALL
.stack 100H

.data

MESSAGE DB "HELLO WORLD !",13,10,"$"



.code
        MOV AX, @DATA
        MOV DS, AX

        LEA DX, MESSAGE
        MOV AH, 09H
        INT 21H
        
        MOV AH, 4CH
        INT 21H

end


; MASM Q1.ASM && LINK Q1.OBJ && Q1.EXE
