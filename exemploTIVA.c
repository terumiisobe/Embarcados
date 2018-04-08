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
#include "message.h"
#include "__thread.h"

/*----------------------------------------------------------------------------
 * include libraries from drivers
 *----------------------------------------------------------------------------*/

//#include "buttons.h"
//#include "cfaf128x128x16.h"
//#include "joy.h"

//To print on the screen
tContext sContext;

void init_all(){
	cfaf128x128x16Init(); 
	Init_Thread();
}
/*----------------------------------------------------------------------------
 *      Main
 *---------------------------------------------------------------------------*/
int main (void) {
	
		osKernelInitialize();
	
		init_all();
	
		GrContextInit(&sContext, &g_sCfaf128x128x16);
	
		GrFlush(&sContext);
		GrContextFontSet(&sContext, g_psFontFixed6x8);
		
		GrContextForegroundSet(&sContext, ClrWhite);
		GrContextBackgroundSet(&sContext, ClrBlack);
			
		
		osKernelStart();
		
		osDelay(osWaitForever);
}