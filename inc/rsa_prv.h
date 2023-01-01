/**
 * @file rsa_prv.h
 * @author Mohamed ashraf (wx@wx.com)
 * @brief rsa interface file
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) Wx 2023
 * 
 * @attention
 *      @todo
 * 
 * 
 */
/** @def Header guards */
#ifndef __RSA_PRV_H__
#define __RSA_PRV_H__

/** @def Handeling name mangle */
#ifdef __cplusplus
extern "C" {
#endif

/*
*--------------------------------------------------------------------------------------
*- Private Macros
*--------------------------------------------------------------------------------------
**/

/** @defgroup Debugging macros */

#if (DEBUGGING_FLAG == DEBUGGING_ACTIVE)
	/** @brief Function like macro used for debug messages
	 * 	@attention 
	 * 		This function like macro is compatible starts from GCC-89/90
	 */
	#define win64_dbg_msg(format, ...) ({ \
						fprintf(stderr, "\n=> File: %s, Function: %s, Line: %d\n DBG_MSG: "format"\n", \
						__FILE__, __FUNCTION__, __LINE__, ## __VA_ARGS__); \
					})
#endif

#if (FULL_ASSERTION_FLAG == FULL_ASSERTION_ACTIVE)

	/** @brief Function like macro used for terminating the program on assertion failure
	 * 	@attention 
	 * 		This function like macro is compatible starts from GCC-89/90
	 */
	#if (DEBUGGING_FLAG == DEBUGGING_ACTIVE)
		#define exit_on_failure(_EXIT_CODE) ({ \
							win64_dbg_msg("ASSERTION_FAILURE - EXIT_CODE=%d", (_EXIT_CODE)); \
							exit((_EXIT_CODE)); \
						})
	#else
			#define exit_on_failure(_EXIT_CODE) ({ \
							exit((_EXIT_CODE)); \
						})
	#endif
	#define DEFAULT_EXIT_CODE (-1)
	/** @brief Function like macro used for assertion statically
	 * 	@attention 
	 * 		This function like macro is compatible starts from GCC-89/90
	 */
	#define STATIC_ASSERT(EXPRESSION, _EXIT_CODE) ({ \
						(EXPRESSION) ? (NULL) : (exit_on_failure(_EXIT_CODE)); \
					})
#endif

/** @defgroup attributs macros */
#define _STATIC_INLINE static inline
#define _FORCE_INLINE __attribute__((always_inline))
#define _FORCE_CONST __attribute__((const))

/** @defgroup Configuration parameters macros */
#define DEBUGGING_INACTIVE          (0x00u)
#define DEBUGGING_ACTIVE            (0x01u)

#define FULL_ASSERTION_INACTIVE     (0x00u)
#define FULL_ASSERTION_ACTIVE       (0x01u)

/** @defgroup Program macros */
#define PRIME_NUMBERS_DB_SIZE 		(0x7Fu)

/*
*--------------------------------------------------------------------------------------
*- Private Data types
*--------------------------------------------------------------------------------------
**/

typedef enum en_PrimeNumbersStatus
{
	numberNotPrime = 0x00u,
  numberIsPrime
}en_PrimeNumbersStatus_t;

typedef uint64_t tLargeRets_t;

/*
*--------------------------------------------------------------------------------------
*- Private Functions Declaration
*--------------------------------------------------------------------------------------
**/

_FORCE_INLINE
_FORCE_CONST
_STATIC_INLINE tLargeRets_t 
getPrimeNumber(void);

_FORCE_INLINE
_FORCE_CONST
_STATIC_INLINE void 
getEncryptionModulus(const uint64_t PrimeNumberA, 
                     const uint64_t PrimeNumberB,
                     uint64_t * const pEncryptionModulus);
_FORCE_INLINE
_STATIC_INLINE uint64_t 
mulMod(uint64_t a, uint64_t b, const uint64_t mod);

_FORCE_INLINE
_STATIC_INLINE uint64_t 
powMod(uint64_t n, uint64_t exp, const uint64_t mod);

_FORCE_INLINE
_STATIC_INLINE en_PrimeNumbersStatus_t 
isPrimeNumber(uint64_t primeNumber);

_FORCE_INLINE
_FORCE_CONST
_STATIC_INLINE tLargeRets_t
getGCD(uint64_t numA, uint64_t numB);




/** @def Handeling name mangle */
#ifdef __cplusplus
}
#endif

#endif /* __RSA_PRV_H__ */