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

st_rsa_t my_rsa_lib = {0};

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

	getPublicKeyParams(primeNumberA, primeNumberB);
	getPrivateKeyParams(primeNumberA, primeNumberB);
}

void 
generate_keys(const uint8_t * const pString)
{
	/* Validating */
#if (FULL_ASSERTION_FLAG == FULL_ASSERTION_ACTIVE)
	STATIC_ASSERT((pString != NULL), DEFAULT_EXIT_CODE);	
#endif


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
	uint32_t register s = 0x00u;

	/* Function body */
	if (primeNumber > PrimeNumbers[numOfPrimes - 0x01u]) 
	{
		for (t = primeNumber - 1; ~t & 0x01u; t >>= 0x01u, ++s);

		uint64_t register i = 0x00u;
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

_STATIC_INLINE uint64_t
getPrimeNumber(void)
{
	/* Function data types */
	static uint64_t randNumber = 0xFFFFFFFFFFFFFu;
	uint64_t primeNumber = 0;
	en_PrimeNumbersStatus_t numberStatus = numberNotPrime;

	/* Function body */
	/**
	 * @brief Generating prime numbers using simple checker.
	 * 
	 */
	while(numberNotPrime == numberStatus)
	{
		numberStatus = isPrimeNumber(randNumber);

		if( (numberNotPrime == numberStatus) )
		{
			--randNumber;
		}	
		else
		{
			primeNumber = randNumber;
			break;
		}
	}
	--randNumber;

#if (DEBUGGING_FLAG == DEBUGGING_ACTIVE)
	win64_dbg_msg("Generated prime: %llu", primeNumber);
#endif

	return primeNumber;
}/* getPrimeNumber */

_STATIC_INLINE uint64_t 
getEncryptionModulus(const uint64_t PrimeNumberA, 
                     const uint64_t PrimeNumberB)
{
	/* Validating */
#if (FULL_ASSERTION_FLAG == FULL_ASSERTION_ACTIVE)
	STATIC_ASSERT((PrimeNumberA > 0), DEFAULT_EXIT_CODE);
	STATIC_ASSERT((PrimeNumberB > 0), DEFAULT_EXIT_CODE);
#endif
	/* Function data types */
	uint64_t encryptionModulus = 0x00u;
	uint64_t phi = (PrimeNumberA - 0x01u) * (PrimeNumberB - 0x01u);
	uint64_t gcd = 0x00u;

	/* Function body */
	/**
	 * @brief Encryption modulus also referred as 'e', it is the modulus needed
	 * 			  for encrypting and decrypting the message.
	 */
	encryptionModulus = 0x02u;
	
	while(encryptionModulus < phi)
	{
		/**
		 * @brief The encryption modulus must be co-prime to phi,
		 * 			  and smaller than phi.
		 */
		gcd = getGCD(encryptionModulus, phi);
		if( (0x01u == gcd) )
		{ break; }
		else
		{ ++encryptionModulus; }
	}

	my_rsa_lib.math_parameters.phi = phi;

#if (DEBUGGING_FLAG == DEBUGGING_ACTIVE)
	win64_dbg_msg("Encryption modulus: %llu", encryptionModulus);
#endif

#if (FULL_ASSERTION_FLAG == FULL_ASSERTION_ACTIVE)
	STATIC_ASSERT((my_rsa_lib.math_parameters.phi == phi), DEFAULT_EXIT_CODE);
#endif

	return encryptionModulus;
}/* getEncryptionModulus */

_STATIC_INLINE uint64_t
getPublicKeyParams(const uint64_t PrimeNumberA, 
             			 const uint64_t PrimeNumberB)
{
	/* Validating */
#if (FULL_ASSERTION_FLAG == FULL_ASSERTION_ACTIVE)
	STATIC_ASSERT((PrimeNumberA > 0), DEFAULT_EXIT_CODE);
	STATIC_ASSERT((PrimeNumberB > 0), DEFAULT_EXIT_CODE);
#endif

	uint64_t n = PrimeNumberA * PrimeNumberB;
	uint64_t e = getEncryptionModulus(PrimeNumberA, PrimeNumberB);

	my_rsa_lib.math_parameters.n = n;
	my_rsa_lib.math_parameters.e = e;

#if (DEBUGGING_FLAG == DEBUGGING_ACTIVE)
	win64_dbg_msg("n: %llu, e: %llu", n, e);
#endif

#if (FULL_ASSERTION_FLAG == FULL_ASSERTION_ACTIVE)
	STATIC_ASSERT((my_rsa_lib.math_parameters.n == n), DEFAULT_EXIT_CODE);
	STATIC_ASSERT((my_rsa_lib.math_parameters.e == e), DEFAULT_EXIT_CODE);
#endif

}/* getPublicKey */

_FORCE_INLINE
_FORCE_CONST
_STATIC_INLINE uint64_t
getPrivateKeyParams(const uint64_t PrimeNumberA, 
              			const uint64_t PrimeNumberB)
{
	/* Validating */
#if (FULL_ASSERTION_FLAG == FULL_ASSERTION_ACTIVE)
	STATIC_ASSERT((PrimeNumberA > 0), DEFAULT_EXIT_CODE);
	STATIC_ASSERT((PrimeNumberB > 0), DEFAULT_EXIT_CODE);
	STATIC_ASSERT((my_rsa_lib.math_parameters.phi > 0), DEFAULT_EXIT_CODE);
	STATIC_ASSERT((my_rsa_lib.math_parameters.e > 0), DEFAULT_EXIT_CODE);
#endif

	uint64_t k = 0x02u;
	uint64_t phi = my_rsa_lib.math_parameters.phi;
	uint64_t e = my_rsa_lib.math_parameters.e;

	uint64_t d = (uint64_t) (( 0x01u + (k * phi)) / (double)e);

#if (DEBUGGING_FLAG == DEBUGGING_ACTIVE)
	win64_dbg_msg("d: %llu, k: %llu", d, k);
#endif
}/* getPrivateKey */

_STATIC_INLINE uint64_t
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