.MODEL SMALL
.STACK 100H

.DATA

array db 23, 19, 50, 30, 24, 23, 16, 17, 98, 86

len dw $-array
max db ?
min db ?
prompt1 db "The maximum  number : $"
prompt2 db "The minimum number : $"


linefeed db 13, 10, "$"

.CODE

MAIN PROC
        MOV AX, @DATA
        MOV DS, AX
        LEA SI, array  
        MOV BL, array[SI]
        MOV max, BL
        MOV min, BL
        MOV CX, len
REPEAT:
        MOV AL, array[SI]
        CMP max, AL
        JG CONT1
        MOV max, AL ; UPDATE MAX IF MAX IS SMALL
CONT1: 
        MOV AL, array[SI]
        CMP min, AL
        JL CONT2
        MOV min, AL ; UPDATE MAX IF MAX IS SMALL  
CONT2:
        INC SI
        LOOP REPEAT

        ; MOV AH, 09H
        ; LEA DX, prompt1
        ; INT 21H

        ; MOV AH, 00H
        ; XOR DX, DX

        

        MOV AL , max
        CBW            ; converts from byte to word
        CALL PRINT

        ; MOV AH, 00H
        ; XOR DX, DX

        ; MOV AH, 09H
        ; LEA DX, linefeed
        ; INT 21H

        ; MOV AH, 09H
        ; LEA DX, prompt2
        ; INT 21H

        ; MOV AH, 00H
        ; XOR DX, DX

        MOV AL, min
        CBW             ; converts from byte to word
        CALL PRINT


                
        MOV AH, 4CH
        INT 21H
MAIN ENDP

PRINT PROC

        ;initilize count 
        MOV CX,0 
        MOV DX,0 
label1: 
        ; if ax is zero 
        cmp AX,0 
        je print1       
                
        ;initilize bx to 10 
        mov BX,10         
                
        ; extract the last digit 
        div BX                   
                
        ;push it in the stack 
        push DX               
                
        ;increment the count 
        inc CX               
                
        ;set dx to 0  
        xor DX, DX 
        jmp label1 
        print1: 
        ;check if count  
        ;is greater than zero 
        cmp CX,0 
        je exit
                
        ;pop the top of stack 
        pop DX
                
        ;add 48 so that it  
        ;represents the ASCII 
        ;value of digits 
        add DX,48 
                
        ;interuppt to print a 
        ;character 
        mov AH,02h 
        int 21h 
                
        ;decrease the count 
        dec CX 
        jmp print1 
exit:
        RET
PRINT ENDP
END MAIN