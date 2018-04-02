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

int threadDelayTime = 10;
int threadFlag = 0;

void Thread1 (void const *argument) {
			uint32_t time;
  while (1) {
			if (threadFlag != 0) osThreadYield();
		
			//time = osKernelSysTick()/ticks_factor;
			
			threadFlag = (threadFlag + 1) % 6;
			osThreadYield();
  }
}

void Thread2 (void const *argument) {
			uint32_t time;
  while (1) {
			if (threadFlag != 1) osThreadYield();
		
			//time = osKernelSysTick()/ticks_factor;
			
			threadFlag = (threadFlag + 1) % 6;
			osThreadYield();
  }
}

void Thread3 (void const *argument) {
			uint32_t time;
  while (1) {
			if (threadFlag != 2) osThreadYield();
		
			//time = osKernelSysTick()/ticks_factor;
			
			threadFlag = (threadFlag + 1) % 6;
			osThreadYield();
  }
}

void Thread4 (void const *argument) {
			uint32_t time;
  while (1) {
			if (threadFlag != 3) osThreadYield();
		
			//time = osKernelSysTick()/ticks_factor;
			
			threadFlag = (threadFlag + 1) % 6;
			osThreadYield();
  }
}

void Thread5 (void const *argument) {
			uint32_t time;
  while (1) {
			if (threadFlag != 4) osThreadYield();
		
			//time = osKernelSysTick()/ticks_factor;
			
			threadFlag = (threadFlag + 1) % 6;
			osThreadYield();
  }
}

void Thread6 (void const *argument) {
			uint32_t time;
  while (1) {
			if (threadFlag != 5) osThreadYield();
		
			//time = osKernelSysTick()/ticks_factor;
			
			threadFlag = (threadFlag + 1) % 6;
			osThreadYield();
  }
}
