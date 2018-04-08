#include <stdio.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include "TM4C129.h"
#include "grlib/grlib.h"
#include "cfaf128x128x16.h"
#include "math.h"

#include "__thread.h"

// CMSIS RTOS header file
/*----------------------------------------------------------------------------
 *  Transforming int to string
 *---------------------------------------------------------------------------*/
static void intToString(int64_t value, char * pBuf, uint32_t len, uint32_t base, uint8_t zeros){
	static const char* pAscii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	bool n = false;
	int pos = 0, d = 0;
	int64_t tmpValue = value;

	// the buffer must not be null and at least have a length of 2 to handle one
	// digit and null-terminator
	if (pBuf == NULL || len < 2)
			return;

	// a valid base cannot be less than 2 or larger than 36
	// a base value of 2 means binary representation. A value of 1 would mean only zeros
	// a base larger than 36 can only be used if a larger alphabet were used.
	if (base < 2 || base > 36)
			return;

	if (zeros > len)
		return;
	
	// negative value
	if (value < 0)
	{
			tmpValue = -tmpValue;
			value    = -value;
			pBuf[pos++] = '-';
			n = true;
	}

	// calculate the required length of the buffer
	do {
			pos++;
			tmpValue /= base;
	} while(tmpValue > 0);


	if (pos > len)
			// the len parameter is invalid.
			return;

	if(zeros > pos){
		pBuf[zeros] = '\0';
		do{
			pBuf[d++ + (n ? 1 : 0)] = pAscii[0]; 
		}
		while(zeros > d + pos);
	}
	else
		pBuf[pos] = '\0';

	pos += d;
	do {
			pBuf[--pos] = pAscii[value % base];
			value /= base;
	} while(value > 0);
}

/*----------------------------------------------------------------------------
 *      Thread 1 'Thread_Name': Sample thread
 *---------------------------------------------------------------------------*/
int ticks_factor = 10000;
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
int threadFlag = 1;

unsigned int firstMessage_int[35];
unsigned int firstMessage_decoded[35];
int penultimo = 33;
int ultimo = 34;
unsigned int keyContender;
bool isPrime = false;
bool isMessageDecoded = false;

int lastPrime;
	
/*

2^16 = 65536
quantidade de numeros primos atÅE2^16 = 5910
ordem das threads no codigo de acordo com a ordem de execuÁ„o

falta fazer:
-lista de primos em primes[]
-casting do vetor de char firstMessage para int firstMessage_int
-decodificaÁ„o
-escrever no console
-incluir as outras mensagens 
-TESTAR UHUL

*/

/*------GeraÁ„o da chave------*/ 
void Thread1 (void const *argument) { 
	
	int char_i, int_i = 0;
	int msg_length = firstMessage_length;
	
	// Loading message to int type.
	for (char_i = 0; char_i < msg_length; char_i += 4) {
		firstMessage_int[int_i++] = *(unsigned int *) (firstMessage + char_i);
	}
	
	keyContender = firstMessage_int[0] - 300;
	//keyContender = 2;

  while (1) {
			if (threadFlag != 1) osThreadYield();
			
			if (isPrime)
				lastPrime = keyContender;
		
			keyContender++;
		
		
			threadFlag = 5;
			osThreadYield();	
			//osDelay(2000);
  }
}

/*------VerificaÁ„o da chave (primo)------*/

//searches for prime dividers in the primes vector
void Thread5 (void const *argument) {
	
	int i;
	int keyContenderSqrt;
	int dividerTest;
	
	bool requiresFurtherAnalysis;
	
  while (1) {
		if (threadFlag != 5) osThreadYield();
		
		keyContenderSqrt = sqrt(keyContender);
		requiresFurtherAnalysis = true;
		isPrime = true;
	
		for(i = 0; i < nPrimes; i++) {
			if (primes[i] > keyContenderSqrt) {
				requiresFurtherAnalysis = false;
				break;
			}
			if (keyContender % primes[i] == 0) {
				requiresFurtherAnalysis = false;
				isPrime = false;
				break;
			}
		}
		
		if (requiresFurtherAnalysis) {
			
			dividerTest = primes[i - 1] + 2;
			
			while (dividerTest < keyContenderSqrt) {
				if (keyContender % dividerTest == 0) {
					isPrime = false;
					break;
				}
				
				dividerTest += 2;
			}
		}
		
		threadFlag = 2;
		osThreadYield();
  }
}

/*------DecodificaÁ„o------*/
void Thread2 (void const *argument) {
	
	//firstMessage_int = (int)firstMessage;//casting?
	int i;
  while (1) {
			if (threadFlag != 2) osThreadYield();
			
			for(i = 0; i < 35; i++)
			{
				if (i % 2 == 0) 
					firstMessage_decoded[i] = firstMessage_int[i] - keyContender;
				else
					firstMessage_decoded[i] = firstMessage_int[i] + keyContender;
			}
			
			if(isPrime)
				threadFlag = 3; //tests latest words
			else
				threadFlag = 6;	//prints message
			
			osThreadYield();
  }
}

/*------Teste penultima word------*/
//divisao inteira da chave por 2 codificada
void Thread3 (void const *argument) {
	
	bool first_test;
  while (1) {
			if (threadFlag != 3) osThreadYield();
			
			first_test = false;
			if(firstMessage_decoded[penultimo] == (int)(keyContender / 2))
					first_test = true;
			
			if(first_test)
				threadFlag = 4;
			else
				threadFlag = 6;
			
			osThreadYield();
  }
}

/*------Teste ultima word------*/
//o quadrado da chave dividido pelo primo anterior a chave codificado
void Thread4 (void const *argument) {
	
	bool second_test;
	int second_test_op;
  while (1) {
			if (threadFlag != 4) osThreadYield();
		
			second_test = false;
			second_test_op = keyContender * keyContender / lastPrime;
			if(firstMessage_decoded[ultimo] == second_test_op)
					second_test = true;
			
			threadFlag = 6;
			if(second_test)	//when the second test turns positive the prime_key is correct
				isMessageDecoded = true;
			
			osThreadYield();
  }
}

/*------Escrita no console------*/
void Thread6 (void const *argument) {
		
	
	int i;
	int lineToPrint, columnToPrint;
	char buffer[10];
	char* msgCharacter;
	
	GrStringDraw(&sContext,"Key: ", -1, 0, (sContext.psFont->ui8Height+2)*0, true);
	
  while (1) {
		if (threadFlag != 6) osThreadYield();
		
		intToString(keyContender, buffer, 10, 10, 3);
		
		GrStringDraw(&sContext, (char*) buffer, -1, (sContext.psFont->ui8MaxWidth)*6, (sContext.psFont->ui8Height+2)*0, true);
		
		lineToPrint = 2;
		columnToPrint = 0;
		for (i = 0; i < 33; i++) {
			
			msgCharacter = (char*) &firstMessage_decoded[i];
						
			GrStringDraw(&sContext, msgCharacter, -1, (sContext.psFont->ui8MaxWidth)*columnToPrint, (sContext.psFont->ui8Height+2)*lineToPrint, true);
			
			columnToPrint++;
			
			if (columnToPrint == 10) {
				lineToPrint++;
				columnToPrint = 0;
			}
		}				
		
		if (isMessageDecoded) {
			GrStringDraw(&sContext, "Done", -1, 0, (sContext.psFont->ui8Height+2)*1, true);
			while (1);	// Infinite loop;
		}
		
		threadFlag = 1;
		osThreadYield();
  }
}
