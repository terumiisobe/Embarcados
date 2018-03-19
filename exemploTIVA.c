/*============================================================================
 *                    Exemplos de utilização do Kit
 *              EK-TM4C1294XL + Educational BooterPack MKII 
 *---------------------------------------------------------------------------*
 *                    Prof. André Schneider de Oliveira
 *            Universidade Tecnológica Federal do Paraná (UTFPR)
 *===========================================================================
 * Autores das bibliotecas:
 * 		Allan Patrick de Souza - <allansouza@alunos.utfpr.edu.br>
 * 		Guilherme Jacichen     - <jacichen@alunos.utfpr.edu.br>
 * 		Jessica Isoton Sampaio - <jessicasampaio@alunos.utfpr.edu.br>
 * 		Mariana Carrião        - <mcarriao@alunos.utfpr.edu.br>
 *===========================================================================*/
#include "cmsis_os.h"
#include "TM4C129.h"                    // Device header
#include <stdbool.h>
#include "grlib/grlib.h"

/*----------------------------------------------------------------------------
 * include libraries from drivers
 *----------------------------------------------------------------------------*/

#include "buttons.h"
#include "airplane.h"
#include "car.h"
#include "cfaf128x128x16.h"

#define LED_A      0
#define LED_B      1
#define LED_C      2
#define LED_D      3
#define LED_CLK    7

//To print on the screen
tContext sContext;

extern void panImage(void);
int direcao; 
int tipo;

void init_all(){
	cfaf128x128x16Init(); 
	button_init();
}

/*----------------------------------------------------------------------------
 *      Main
 *---------------------------------------------------------------------------*/
int main (void) {

  unsigned char pixelColor;
	int i, j, index;
	int delay = 10000;
	bool s1_press, s2_press;
	bool origColorMode = true; //origColorMode para alterar a coloração da imagem
	
	direcao	= 0;
	tipo = 1;
	
	init_all();
	
	GrContextInit(&sContext, &g_sCfaf128x128x16);
	GrFlush(&sContext);
	
	for(;;){
			
		index = 0;
		panImage();		
		
		for( i = 0; i < 64; i++){
						for( j = 0; j < 96; j++){
							
							pixelColor = carImage[index];
							
							if (pixelColor <= 128 && origColorMode)
									cfaf128x128x16PixelDraw(&sContext, j, i, 0);
							else
									cfaf128x128x16PixelDraw(&sContext, j, i, 0xFFFF);
							
							index++;
						}
		}
		// Delay.
		for (i = 0; i < delay; i++);
	
		s1_press = button_read_s1();
		s2_press = button_read_s2();
		
		if(s1_press) 
			origColorMode = false;
		else 
			origColorMode = true;
		
		if(s2_press)
			delay = 1000;
		else	
			delay = 1000000;

	}
		
}
	
/*	Botoes 	*/			
				
			/*s1_press = button_read_s1();
			s2_press = button_read_s2();

			if (s1_press)
				intToString(1, pbufx, 10, 10, 1);
			else
				intToString(0, pbufx, 10, 10, 1);

			if (s2_press)
				intToString(1, pbufy, 10, 10, 1);
			else
				intToString(0, pbufy, 10, 10, 1);

			GrContextBackgroundSet(&sContext, ClrBlack);
			GrContextForegroundSet(&sContext, ClrWhite);
			GrStringDraw(&sContext,(char*)pbufx, -1, (sContext.psFont->ui8MaxWidth)*6,  (sContext.psFont->ui8Height+2)*8, true);
			GrStringDraw(&sContext,(char*)pbufy, -1,  (sContext.psFont->ui8MaxWidth)*11, (sContext.psFont->ui8Height+2)*8, true);
*/			
			
				

