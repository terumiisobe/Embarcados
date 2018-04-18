#include <stdio.h>
#include <stdbool.h>
#include "cmsis_os.h"
#include "TM4C129.h"
#include "grlib/grlib.h"
#include "cfaf128x128x16.h"
#include "math.h"
#include "message.h"
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

int threadFlag = 1;

unsigned int message_int[35];
unsigned int message_decoded[35];
int penultimo = 33;
int ultimo = 34;
unsigned int keyContender;
bool isPrime = false;
bool isMessageDecoded = false;

unsigned int lastPrime;
unsigned int decodingStart;
	


void getLastPrime(unsigned int number) {
	
	unsigned int primeContender = number - 1;
	unsigned int primeContenderSqrt;
	unsigned int dividerTest;
	
	bool isPrime;
	bool requiresFurtherAnalysis;
	
	int i;
	
	isPrime = false;
	while (!isPrime)
	{
		isPrime = true;
		requiresFurtherAnalysis = true;
		primeContenderSqrt = sqrt(primeContender);
	
		for(i = 0; i < nPrimes; i++)
		{
			if (primes[i] > primeContenderSqrt)
			{
				requiresFurtherAnalysis = false;
				break;
			}
			
			if (primeContender % primes[i] == 0)
			{
				requiresFurtherAnalysis = false;
				isPrime = false;
				break;
			}
		}
		
		if (requiresFurtherAnalysis)
		{
			dividerTest = primes[i - 1] + 2;
			
			while (dividerTest < primeContenderSqrt)
			{
				if (primeContender % dividerTest == 0)
				{
					isPrime = false;
					break;
				}
				
				dividerTest += 2;
			}
		}
		
		if (!isPrime)
		{
			if (primeContender % 2 == 0)
				primeContender--;
			else
				primeContender -= 2;
		}
	}
	
	lastPrime = primeContender;
}

void displaySetup() {
	
	GrStringDraw(&sContext,"Key: ", -1, 0, 0, true);
	GrStringDraw(&sContext,"Decoding", -1, 0, (sContext.psFont->ui8Height+2)*1, true);
}


/*------Geração da chave------*/ 
void Thread1 (void const *argument) { 
	
	int char_i, int_i = 0;
	int msg_length = message_length;
	
	bool isKeyContenderOdd = false;
	
	unsigned char message_char[140];
	
	// Copying to working array.
	for (char_i = 0; char_i < msg_length; char_i++)
		message_char[char_i] = message5[char_i];
	
	// Loading message to int type.
	for (char_i = 0; char_i < msg_length; char_i += 4)
		message_int[int_i++] = *(unsigned int *) (message_char + char_i);
	
	// Printing display static messages.
	displaySetup();
	
	decodingStart = osKernelSysTick();
	
	// Setting starting point.
	keyContender = message_int[0] - 127;
	
	// Getting the last prime prior to the starting keyContender.
	getLastPrime(keyContender);

  while (1)
	{
		while (threadFlag != 1)
			osThreadYield();
		
		if (isPrime)
			lastPrime = keyContender;
		
		if (isKeyContenderOdd)
		{
			keyContender += 2;
		}
		else if (keyContender % 2 == 0)
		{
			keyContender++;
			isKeyContenderOdd = true;
		}
		else
		{
			keyContender += 2;
			isKeyContenderOdd = true;
		}
		
		threadFlag = 5;
		osThreadYield();
  }
}

/*------Verificação da chave (primo)------*/

//searches for prime dividers in the primes vector
void Thread5 (void const *argument) {
	
	int i;
	unsigned int keyContenderSqrt;
	unsigned int dividerTest;
	
	bool requiresFurtherAnalysis;
	
  while (1)
	{
		while (threadFlag != 5)
			osThreadYield();
		
		keyContenderSqrt = sqrt(keyContender);
		requiresFurtherAnalysis = true;
		isPrime = true;
	
		for(i = 0; i < nPrimes; i++)
		{
			if (primes[i] > keyContenderSqrt)
			{
				requiresFurtherAnalysis = false;
				break;
			}
			if (keyContender % primes[i] == 0)
			{
				requiresFurtherAnalysis = false;
				isPrime = false;
				break;
			}
		}
		
		if (requiresFurtherAnalysis)
		{
			dividerTest = primes[i - 1] + 2;
			
			while (dividerTest < keyContenderSqrt)
			{
				if (keyContender % dividerTest == 0)
				{
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

/*------Decodificação------*/
void Thread2 (void const *argument) {
	
	int i;
	
  while (1)
	{
			while (threadFlag != 2)
				osThreadYield();
			
			for(i = 0; i < 33; i++)
			{
				if (i % 2 == 0) 
					message_decoded[i] = message_int[i] - keyContender;
				else
					message_decoded[i] = message_int[i] + keyContender;
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
	
	unsigned int firstTestOp;
	
  while (1)
	{
			while (threadFlag != 3)
				osThreadYield();
			
			firstTestOp = keyContender / 2 + keyContender;

			if (message_int[33] == firstTestOp)
				threadFlag = 4;
			else
				threadFlag = 6;
			
			osThreadYield();
  }
}

/*------Teste ultima word------*/
//o quadrado da chave dividido pelo primo anterior a chave codificado
void Thread4 (void const *argument) {
	
	unsigned int secondTestOp;
	
  while (1)
	{
			while (threadFlag != 4)
				osThreadYield();
		
			secondTestOp = keyContender * keyContender / lastPrime - keyContender;
			
			if (message_int[34] == secondTestOp)
					isMessageDecoded = true;
			
			threadFlag = 6;
			
			osThreadYield();
  }
}

/*------Escrita no console------*/
void Thread6 (void const *argument) {
		
	
	int i;
	int lineToPrint, columnToPrint;
	char buffer[10];
	char msgCharacter[2];
	
	float decodingTime;
	
	msgCharacter[1] = '\0';
	
  while (1)
	{
		while (threadFlag != 6)
			osThreadYield();
		
		intToString(keyContender, buffer, 10, 10, 3);
		
		GrStringDraw(&sContext, buffer, -1, (sContext.psFont->ui8MaxWidth)*6, (sContext.psFont->ui8Height+2)*0, true);
		
		lineToPrint = 2;
		columnToPrint = 0;
		
		for (i = 0; i < 33; i++)
		{
			msgCharacter[0] = (char) message_decoded[i];
						
			GrStringDraw(&sContext, msgCharacter, -1, (sContext.psFont->ui8MaxWidth) * columnToPrint, (sContext.psFont->ui8Height+2) * lineToPrint, true);
			
			columnToPrint++;
			
			if (columnToPrint == 17)
			{
				lineToPrint++;
				columnToPrint = 0;
			}
		}
		
		if (isMessageDecoded)
		{
			decodingTime = (float)(osKernelSysTick() - decodingStart) / 120000000;
			
			GrStringDraw(&sContext, "Done    ", -1, 0, (sContext.psFont->ui8Height+2)*1, true);
			
			floatToString(decodingTime, buffer, 10, 10, 1, 5);
			
			GrStringDraw(&sContext, "Time in seconds:", -1, 0, (sContext.psFont->ui8Height+2)*5, true);
			GrStringDraw(&sContext, buffer, -1, 0, (sContext.psFont->ui8Height+2)*6, true);
			
			while (1);	// Infinite loop;
		}
		
		threadFlag = 1;
		osThreadYield();
  }
}
