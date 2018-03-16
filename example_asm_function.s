        PUBLIC f_asm
        EXTERN matriz

        #define figura 0x00001000 //0x08 
        
        SECTION .text : CODE (2)
        THUMB
f_asm:
		//movimentaçao da imagem(64x96) inteira diretamente na memoria
		//64(0x40)*96(0x60)=0x1800, ou seja a figura começa em 0x08 e termina em 0x1808
	next_line:
		mov r0,#0h    //(r0 = y) guarda o valor de y (0-60)
		mov r1,#0h    //(r1 = x) guarda o valor de x (0-40)
		mov r3,0x17c8 //ultima linha
		
		bic r2,r0,#59h //testa se esta na ultima linha NAND(0->sim)
		cbz r2, linha60
		cbnz r0, outras_linhas	 
		linha1:	
			add r4, r3, r1 //offset do x na ultima linha
			mov r2, 
		outras_linhas:	
		linha60:
		
		
        mov r0,#0xaa00 
        mov r1,#0xbb
        orrs r1,r0
        
        ldr r0,=figura
        ldrb r2,[r0,#0]
        ldrb r2,[r0,#6]
        
        ldr r0,=matriz
        bx lr

        END
