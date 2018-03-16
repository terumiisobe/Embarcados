        PUBLIC f_asm
        EXTERN matriz

        #define figura 0x00001000 //0x08 
        
        SECTION .text : CODE (2)
        THUMB
f_asm:
		//movimentaçao da imagem(64x96) inteira diretamente na memoria
		//64(0x40)*96(0x60)=0x1800, ou seja a figura começa em 0x08 e termina em 0x1808
		//ideia: deslocar toda a figura para cima e mover a primeira linha para o final
		
		ldr r0,=figura	//r0 é a figura
		mov r2,#0		//r2 é o contador de deslocamento coluna(0-39)
		mov r4,#60		//r4 é o numero da linha
		
	move_up:
		sub r3,r0,#41h	//r3 é a linha anterior
		ldrb r1,[r0,r2] 
		strb r1,[r3,r2]
		add r2,#1h
		bic r1,r2,#40   //NAND, se r2=40 entao r1=0
		cbnz r1, move_up
		sub r4,#1		//contador da linha
		add r0,#41h   	//desce a linha na figura  
		mov r2,#0		//reseta o offset
		
		cbnz r4,move_up	
		ldr r0,=figura
	move_line:			//chegou aqui->acabou a figura
		mov r4,#17c8h	//primeiro elemento da ultima linha
		ldrb r1,[r0,r2]
		strb r1,[r4,r2]
		add r2,#1h
		bic r3,r2,#40h	//NAND, se r2=40 entao r3=0
		cbnz r3,move_line
		
		bx lr
		
		END
		