
	AREA    |.text|, CODE, READONLY, ALIGN=2
		
	GLOBAL panImage
		
	EXTERN airplaneImage
	EXTERN carImage
	EXTERN tipo
	EXTERN direcao
	
	THUMB

panImage
	
	ldr R0, =tipo
	ldrb R1, [R0]
	cmp R1, #1			; 0 means carImage and 1 means airplaneImage
	beq airplane

	mov R4, #96			; Number of columns in the image.
	mov R3, #64			; Setting line as multiplier.
	ldr R2, =carImage
	ldr R1, =direcao	
	ldrb R0, [R1]
	cmp R0, #1			; 0 means left and 1 means right
	beq right			
	; index = linha * 96 + coluna	
	
	mov R3, #0				; Setting line as multiplier
left
	mov R8, #1				; Column index. Comeca na segunda coluna 1
	mul R5, R4, R3			
	add R5, R2
	add R5, R8
	ldrb R6, [R5]
	
	add R5, #1
	
 	ldrb R7, [R5]
	strb R6, [R5]
	
new_column_left
	add R8, #1 
	
	add R5, #2
	ldrb R6, [R5]
	sub R5, #1
	strb R6, [R5]
	
	cmp R8, #95
	bne new_column_left
	
	add R5, #1				; Got to the last column.
	strb R7, [R5]			; Saving the buffer in the last column.
	cmp R3,#63
	add R3,#1
	bne left				; Repeat for the next line.
	
	bx lr
	
right
	sub R3, #1
	mov R8, #94				; Column index. Comeca na penultima coluna 94
	mul R5, R4, R3			; Getting line index. line * 96
	add R5, R2				; Getting the address for the line.
	add R5, R8				; Getting the full address. line * 96 + column
	ldrb R6, [R5]			; Loading byte at R6.
	
	add R5, #1				; Going to next column
	
	ldrb R7, [R5]			; R7 acting as a Buffer
	strb R6, [R5]

new_column_right
	sub R8, #1
	
	sub R5, #2
	ldrb R6, [R5]
	add R5, #1
	strb R6, [R5]
	
	cmp R8, #0
	bne new_column_right
	
	sub R5, #1				; Got to the last column.
	strb R7, [R5]			; Saving the buffer in the last column.
	cmp R3,#0
	bne right				; Repeat for the next line.
	
	bx lr

airplane
	ldr R5, =airplaneImage
    ldr R1, =direcao	
	ldrb R0, [R1]
	cmp R0, #1				; 0 means up and 1 means down
	beq down			

	MOV R0, #0  
new_R0_loop

    CMP R0, #96
    beq end_of_mov
    
    MOV R2, #63
    MOV R3, #96
    MUL R1, R2, R3 
    ADD R1, R0
    ADD R1, R5
    
    ldrb R4, [R1]
    SUB R6, R1, #96
    
    MOV R8, #63
    
new_line_loop

    CMP R8, #0
    beq end_of_lines
    
    ldrb R7, [R6]
    strb R4, [R6]
    
    ADD R4, R7, #0
    
    SUB R6, #96
    
    SUB R8, #1
    
    b new_line_loop
    
end_of_lines

    strb R7, [R1]
    
    ADD R0, #1
    b new_R0_loop
    
end_of_mov
    
 	bx lr
	
    
down
	MOV R0, #0
    
down_column_loop

    CMP R0, #96
    beq end_of_down

    ADD R2, R5, R0
    ldrb R3, [R2]
    ADD R4, R2, #96
    
    MOV R1, #0
    
down_line_loop

    cmp R1, #63
    beq down_end_line_loop
    
    ldrb R6, [R4]
    strb R3, [R4]
    add R3, R6, #0
    
    add R4, #96
    
    add R1, #1
    b down_line_loop
    
down_end_line_loop

    strb R6, [R2]
    
    add R0, #1
    b down_column_loop
    
end_of_down
	
	bx lr

	END