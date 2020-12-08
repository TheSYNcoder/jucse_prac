.model SMALL
.stack 100H

.data

myname DB "Name : Shuvayan Ghosh Dastidar",13,10,"$"
mytitle DB "TITLE : PRINTING NAME AND TITLE$"


.code
        MOV AX, @DATA
        MOV DS, AX

        LEA DX, myname
        MOV AH, 09H
        INT 21H

        LEA DX, mytitle
        INT 21H

        MOV AH, 4CH
        INT 21H

end


; MASM Q1.ASM && LINK Q1.OBJ && Q1.EXE
