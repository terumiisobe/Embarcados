
#ifndef __THREAD_H__
#define __THREAD_H__

#include "cmsis_os.h"
#include "cfaf128x128x16.h"
#include "grlib/grlib.h"
#include <stdio.h>

extern int ticks_factor;
extern FILE *file; 
extern tContext sContext;

extern int Init_Thread(void);														//Thread Initialization

extern void Thread1 (void const *argument);               // thread function
extern void Thread2 (void const *argument);  
extern void Thread3 (void const *argument);  
extern void Thread4 (void const *argument);  
extern void Thread5 (void const *argument);  
extern void Thread6 (void const *argument);  

extern osThreadId tid_Thread1;                            // thread id
extern osThreadId tid_Thread2; 
extern osThreadId tid_Thread3; 
extern osThreadId tid_Thread4; 
extern osThreadId tid_Thread5; 
extern osThreadId tid_Thread6; 

extern int primes[];
extern int nPrimes;


extern char firstMessage[];
extern const unsigned int firstMessage_length;

#endif