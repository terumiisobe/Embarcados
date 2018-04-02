#include <stdio.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include "TM4C129.h"
#include "grlib/grlib.h"
#include "cfaf128x128x16.h"

#include "__thread.h"

// CMSIS RTOS header file

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
int ticks_factor = 10000;
FILE *file;
//tContext sContext;

int Init_Thread (void) {
	
osThreadId tid_Thread1;                            // thread id
osThreadId tid_Thread2; 
osThreadId tid_Thread3; 
osThreadId tid_Thread4; 
osThreadId tid_Thread5; 
osThreadId tid_Thread6; 
	
	osThreadDef (Thread1, osPriorityNormal, 1, 0);     // thread object
	osThreadDef (Thread2, osPriorityNormal, 1, 0);
	osThreadDef (Thread3, osPriorityNormal, 1, 0);
	osThreadDef (Thread4, osPriorityNormal, 1, 0);
	osThreadDef (Thread5, osPriorityNormal, 1, 0);
	osThreadDef (Thread6, osPriorityNormal, 1, 0);
	
  tid_Thread1 = osThreadCreate (osThread(Thread1), NULL);
	tid_Thread2 = osThreadCreate (osThread(Thread2), NULL);
	tid_Thread3 = osThreadCreate (osThread(Thread3), NULL);
	tid_Thread4 = osThreadCreate (osThread(Thread4), NULL);
	tid_Thread5 = osThreadCreate (osThread(Thread5), NULL);
	tid_Thread6 = osThreadCreate (osThread(Thread6), NULL);
	
  if (!tid_Thread1) return(-1);
	if (!tid_Thread2) return(-1);
	if (!tid_Thread3) return(-1);
	if (!tid_Thread4) return(-1);
	if (!tid_Thread5) return(-1);
	if (!tid_Thread6) return(-1);
	
  return(0);
}

void Thread1 (void const *argument) {
			uint32_t time;
  while (1) {
			time = osKernelSysTick()/ticks_factor;
			osDelay(500);
		//fprintf(file, "Thread1 : %i, %i\n", (int)time, (int)osKernelSysTick()/ticks_factor);
		GrStringDraw(&sContext,"Thread 1", -1, 0, (sContext.psFont->ui8Height+2)*0, true);
  }
}

void Thread2 (void const *argument) {
			uint32_t time;
  while (1) {
			time = osKernelSysTick()/ticks_factor;
			osDelay(500);
		//fprintf(file, "Thread2 : %i, %i\n", (int)time, (int)osKernelSysTick()/ticks_factor);
		GrStringDraw(&sContext,"Thread 2", -1, 0, (sContext.psFont->ui8Height+2)*0, true);
  }
}

void Thread3 (void const *argument) {
			uint32_t time;
  while (1) {
			time = osKernelSysTick()/ticks_factor;
			osDelay(500);
		//fprintf(file, "Thread3 : %i, %i\n", (int)time, (int)osKernelSysTick()/ticks_factor);
		GrStringDraw(&sContext,"Thread 3", -1, 0, (sContext.psFont->ui8Height+2)*0, true);
  }
}

void Thread4 (void const *argument) {
			uint32_t time;
  while (1) {
			time = osKernelSysTick()/ticks_factor;
			osDelay(500);
		//fprintf(file, "Thread4 : %i, %i\n", (int)time, (int)osKernelSysTick()/ticks_factor);
		GrStringDraw(&sContext,"Thread 4", -1, 0, (sContext.psFont->ui8Height+2)*0, true);
  }
}

void Thread5 (void const *argument) {
			uint32_t time;
  while (1) {
			time = osKernelSysTick()/ticks_factor;
			osDelay(500);
		//fprintf(file, "Thread5 : %i, %i\n", (int)time, (int)osKernelSysTick()/ticks_factor);
		GrStringDraw(&sContext,"Thread 5", -1, 0, (sContext.psFont->ui8Height+2)*0, true);
  }
}

void Thread6 (void const *argument) {
			uint32_t time;
  while (1) {
			time = osKernelSysTick()/ticks_factor;
			osDelay(500);
		//fprintf(file, "Thread6 : %i, %i\n", (int)time, (int)osKernelSysTick()/ticks_factor);
		GrStringDraw(&sContext,"Thread 6", -1, 0, (sContext.psFont->ui8Height+2)*0, true);
  }
}
