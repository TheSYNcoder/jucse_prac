.model SMALL
.stack 100H

;-----------------
;prints second maximum
;----------------

.data

array db 19, 50, 30, 24, 23, 16, 17, 98, 86

len dw $-array
max db 0
smax db 0
min db 100
smin db 100
linefeed db 13, 10, "$"

.code

MAIN PROC
        MOV AX, @DATA
        MOV DS, AX
        LEA SI, array
        MOV AX,0
        MOV AL, array[SI]
        MOV max,AL
        MOV smax, AL
        MOV CX, len

REPEAT:
        MOV AX,0
        MOV AL, array[SI]
        CMP max, AL
        JG CHECKSMAX
        MOV BL, max
        MOV smax, BL
        MOV max, AL ; UPDATE MAX IF MAX IS SMALL
        JMP CONT1

CHECKSMAX:

        CMP smax, AL
        JG CONT1
        MOV smax, AL
CONT1:
        MOV AX,0
        MOV AL, array[SI]
        CMP min, AL
        JL CHECKSMIN
        MOV BL, min
        MOV smin, BL
        MOV min, AL ; UPDATE MAX IF MAX IS SMALL
        JMP CONT2

CHECKSMIN:
        CMP smin, AL
        JL CONT2
        MOV smin, AL
CONT2:
        

        INC SI
        LOOP REPEAT

        ; PRINT MAX AND SECOND MAX
        
    
        MOV AX, 0
        MOV AL , smax
        CALL PRINT
   
        MOV AX, 0
        MOV AL , smin
        CALL PRINT
        ; CALL NEWLINE

        MOV AH, 4CH
        INT 21H
MAIN ENDP

NEWLINE PROC
        MOV DX,0
        MOV AH,0
        MOV AH,9
        LEA DX, linefeed
        INT 21H
NEWLINE ENDP

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