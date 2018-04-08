import math

primes = [2]
maxPrime = 2**15 + 2**13


primeContender = 3
nPrimes = 1

while primeContender < maxPrime:

    primeContenderSqrt = math.sqrt(primeContender)
    
    isPrime = True
    for p in primes:
        if p > primeContenderSqrt:
            break
        if primeContender % p == 0:
            isPrime = False
            break

    if isPrime:
        primes.append(primeContender)
        nPrimes += 1

    primeContender += 2

print('nPrimes: ', nPrimes)

with open('primes.txt', 'w') as f:
    index = 0
    for p in primes:
        f.write(str(p))
        index += 1
        if index % 12 == 0:
            f.write(',\n')
        else:
            f.write(', ')
            

