		AREA    |.text|, CODE, READONLY, ALIGN=2
		
	GLOBAL panImage
		
	EXTERN airplaneImage
	EXTERN carImage
	EXTERN tipo
	EXTERN direcao
	
	THUMB
		
panImage
	
	ldr R0, =tipo
	cmp R0, #1			; 0 means carImage and 1 means airplaneImage
	beq airplane

	mov R4, #96			; Number of columns in the image.
	mov R3, #64			; Setting line as multiplier.
	ldr R2, =carImage
	ldr R1, =direcao	
	cmp R1, #1			; 0 means left and 1 means right
	beq right			
	; index = linha * 96 + coluna	
	
	mov R3, #0				; Setting line as multiplier
left
	mov R8, #1				; Column index. Comeca na segunda coluna 1
	mul R5, R4, R3			
	add R5, R2
	add R5, R8
	ldrb R6, [R5]
	
	sub R5, #1
	
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
	mov R4, #96			; Number of columns in the image.
	mov R3, #64			; Setting line as multiplier.
	ldr R2, =airplaneImage
	ldr R1, =direcao	
	cmp R1, #1			; 0 means up and 1 means down
	beq down
	; index = coluna * 64 + linha	
up
	mov R4, #0
	mov R8, #1			; Line index. Comeca na segunda linha
	mul R5, R3, R4
	add R5, R2			;Get adress
	add R5, R8			;Get full index
	ldrb R6, [R5]
	
	;sub 
	
down
	
	END
	
