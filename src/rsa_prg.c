/**
 * @file rsa_prg.c
 * @author Mohamed ashraf (wx@wx.com)
 * @brief rsa program file
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) Wx 2023
 * 
 * @attention
 *      @todo
 * 
 * 
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "rsa_cfg.h"
#include "rsa_prv.h"
#include "rsa_int.h"

/*
*--------------------------------------------------------------------------------------
*- Macros
*--------------------------------------------------------------------------------------
**/



/*
*--------------------------------------------------------------------------------------
*- Data types
*--------------------------------------------------------------------------------------
**/


/*
*--------------------------------------------------------------------------------------
*- Public Functions Implementation
*--------------------------------------------------------------------------------------
**/

void public_testing(void)
{
	uint64_t primeNumberA = getPrimeNumber();;
	uint64_t primeNumberB = getPrimeNumber();;
	uint64_t encMod = 0;

	isPrimeNumber(primeNumberA);
	isPrimeNumber(primeNumberB);

	//getEncryptionModulus(primeNumberA, primeNumberB, &encMod);

	uint64_t gcd = getGCD(primeNumberA, primeNumberB);

}

/*
 *--------------------------------------------------------------------------------------
 *- Private Functions Implementation
 *--------------------------------------------------------------------------------------
**/

_STATIC_INLINE uint64_t 
mulMod(uint64_t a, uint64_t b, const uint64_t mod)
{
	uint64_t res = 0, c; // return (a * b) % mod, avoiding overflow errors while doing modular multiplication.
	for (b %= mod; a; a & 1 ? b >= mod - res ? res -= mod : 0, res += b : 0, a >>= 1, (c = b) >= mod - b ? c -= mod : 0, b += c);
	return res % mod;
}/* mulMod */

_STATIC_INLINE uint64_t 
powMod(uint64_t n, uint64_t exp, const uint64_t mod)
{
	uint64_t res = 1; // return (n ^ exp) % mod
	for (n %= mod; exp; exp & 1 ? res = mulMod(res, n, mod) : 0, n = mulMod(n, n, mod), exp >>= 1);
	return res;
}/* powMod */

/**
 * @brief Miller-Rabin primality test function (it should be a deterministic version).
 * 			  Using the 'repeated squaring' method the algorithm time complexity
 * 				T = `O(k log^3(n))`; k: number of rounds, n: the passed number.
 * 
 */
_STATIC_INLINE en_PrimeNumbersStatus_t
isPrimeNumber(uint64_t primeNumber)
{
	/* Validating */
#if (FULL_ASSERTION_FLAG == FULL_ASSERTION_ACTIVE)
	STATIC_ASSERT((primeNumber > 0x02u), DEFAULT_EXIT_CODE);	
#endif
	/* Function data types */
	en_PrimeNumbersStatus_t primeNumberStatus = numberIsPrime;
	const uint8_t numOfPrimes = 9; 
	uint8_t PrimeNumbers[] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
	uint64_t t = 0x00u;
	uint64_t B = 0x00u;
	uint32_t s = 0x00u;

	/* Function body */
	if (primeNumber > PrimeNumbers[numOfPrimes - 0x01u]) 
	{
		for (t = primeNumber - 1; ~t & 0x01u; t >>= 0x01u, ++s);

		uint64_t i = 0x00u;
		for (; i < numOfPrimes && primeNumberStatus; ++i) 
		{
			B = powMod(PrimeNumbers[i], t, primeNumber);
			if (B != 1) 
			{
				uint32_t b = s;
				for (; b-- && (primeNumberStatus = B + 0x01u != primeNumber);)
				{ B = mulMod(B, B, primeNumber); }

				primeNumberStatus = !primeNumberStatus;
			}
			else {;}
		}
	}
	else {;}

#if (DEBUGGING_FLAG == DEBUGGING_ACTIVE)
	if( (numberIsPrime == primeNumberStatus) )
	{ win64_dbg_msg("Number `%llu` is prime.", primeNumber); }
	else
	{ win64_dbg_msg("Number `%llu` isn't prime.", primeNumber);}
#endif

	return primeNumberStatus; 
}/* isPrimeNumber */

_STATIC_INLINE tLargeRets_t
getPrimeNumber(void)
{
	/* Function data types */
	const uint64_t largePrimeNumbers[PRIME_NUMBERS_DB_SIZE] = {
		396813518307451871u, 
		889483944081239707u, 
		947387063867601961u, 
		782806410827045321u, 
		494997063088224343u, 
		910060599641213897u, 
		/** @todo to be add more / replace with generator */
	};
	
	static uint8_t largePrimeNumbersDBCounter = 0x00u;
	tLargeRets_t primeNumber = 0;

	/* Function body */

	/* Working as circular buffer */
	if( (largePrimeNumbersDBCounter >= PRIME_NUMBERS_DB_SIZE) )
	{ largePrimeNumbersDBCounter = 0;}
	else {;}

	primeNumber = largePrimeNumbers[largePrimeNumbersDBCounter++];

#if (DEBUGGING_FLAG == DEBUGGING_ACTIVE)
	win64_dbg_msg("Generated prime: %llu", primeNumber);
#endif

	return primeNumber;
}/* getPrimeNumber */

_STATIC_INLINE void
getEncryptionModulus(const uint64_t PrimeNumberA, 
                     const uint64_t PrimeNumberB,
                     uint64_t * const pEncryptionModulus)
{
	/* Validating */
#if (FULL_ASSERTION_FLAG == FULL_ASSERTION_ACTIVE)
	STATIC_ASSERT((PrimeNumberA > 0), DEFAULT_EXIT_CODE);
	STATIC_ASSERT((PrimeNumberB > 0), DEFAULT_EXIT_CODE);
	STATIC_ASSERT((pEncryptionModulus != NULL), DEFAULT_EXIT_CODE);	
#endif
	/* Function data types */
	uint64_t encryptionModulus = 0x00u;

	/* Function body */
	encryptionModulus = PrimeNumberA * PrimeNumberB;
	
#if (DEBUGGING_FLAG == DEBUGGING_ACTIVE)
	win64_dbg_msg("Encryption modulus: %llu", encryptionModulus);
#endif

	*pEncryptionModulus = encryptionModulus;

	return;
}/* getEncryptionModulus */

_STATIC_INLINE tLargeRets_t
getGCD(uint64_t numA, uint64_t numB)
{
#if (FULL_ASSERTION_FLAG == FULL_ASSERTION_ACTIVE)
	STATIC_ASSERT((numA != 0), DEFAULT_EXIT_CODE);
	STATIC_ASSERT((numB != 0), DEFAULT_EXIT_CODE);
#endif

	/* Function data types */
	uint64_t tempVar = 0x00u;
	uint64_t tempA = numA;
	uint64_t tempB = numB;

	/* Function body */
	while(1)
	{
		tempVar = tempA % tempB;

		if( (0x00u == tempVar) )
		{ break; }
		else;

		tempA = tempB;
		tempB = tempVar;
	}

#if (DEBUGGING_FLAG == DEBUGGING_ACTIVE)
	win64_dbg_msg("GCD of `%llu`, `%llu` is `%llu`", numA, numB, tempB);
#endif

	return tempB;
}/* getGCD */