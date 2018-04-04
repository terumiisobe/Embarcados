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

static void floatToString(float value, char *pBuf, uint32_t len, uint32_t base, uint8_t zeros, uint8_t precision){
	static const char* pAscii = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	uint8_t start = 0xFF;
	if(len < 2)
		return;
	
	if (base < 2 || base > 36)
		return;
	
	if(zeros + precision + 1 > len)
		return;
	
	intToString((int64_t) value, pBuf, len, base, zeros);
	while(pBuf[++start] != '\0' && start < len); 

	if(start + precision + 1 > len)
		return;
	
	pBuf[start+precision+1] = '\0';
	
	if(value < 0)
		value = -value;
	pBuf[start++] = '.';
	while(precision-- > 0){
		value -= (uint32_t) value;
		value *= (float) base;
		pBuf[start++] = pAscii[(uint32_t) value];
	}
}
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
bool stop;

int firstMessage_int[35];
int firstMessage_decoded[35];
int penultimo = 33;
int ultimo = 34;

int primes[5910];		//create prime list
int prime_key;
int prime_index;		//the current prime in the primes vector being tested
bool isPrime = false;
	
/*

2^16 = 65536
quantidade de numeros primos até 2^16 = 5910
ordem das threads no codigo de acordo com a ordem de execução

falta fazer:
-lista de primos em primes[]
-casting do vetor de char firstMessage para int firstMessage_int
-decodificação
-escrever no console
-incluir as outras mensagens 
-TESTAR UHUL

*/

/*------Geração da chave------*/ 
void Thread1 (void const *argument) { 
	
	prime_index = 0;
  while (1) {
			if (threadFlag != 1) osThreadYield();
			
			prime_key = primes[prime_index];		
			prime_index++;
			isPrime = false;	//"we dont know" if the key is a prime
		
			threadFlag = 5;
			osThreadYield();
  }
}

/*------Verificação da chave (primo)------*/

//search for prime_key in the primes vector
void Thread5 (void const *argument) {
	
	int i;
  while (1) {
			if (threadFlag != 5) osThreadYield();

			for(i = 0; i < 5910; i++)
				if(prime_key == primes[i])
					isPrime = true;
			
			threadFlag = 2;
			osThreadYield();
  }
}

/*------Decodificação------*/
void Thread2 (void const *argument) {
	
	//firstMessage_int = (int)firstMessage;//casting?
	int i;
  while (1) {
			if (threadFlag != 2) osThreadYield();
			
			for(i = 0; i < firstMessage_length/4; i++)
			{
				//decode for even and odd word indexes
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
			if(firstMessage_int[penultimo] == (int)(prime_key/2) - prime_key)//index 33
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
	int var;
  while (1) {
			if (threadFlag != 4) osThreadYield();
		
			second_test = false;
			var = (prime_key)*(prime_key)/primes[prime_index-2] + prime_key;//index 34
			if(firstMessage_int[ultimo] == var)
					second_test = true;
			
			threadFlag = 6;
			if(second_test)	//when the second test turns positive the prime_key is correct
				stop = true;
			
			osThreadYield();
  }
}

/*------Escrita no console------*/
void Thread6 (void const *argument) {
			
  while (1) {
			if (threadFlag != 6) osThreadYield();
			
			//convert decoded int message to char again
			//prints characters 
		
			threadFlag = 1;
			osThreadYield();
  }
}
