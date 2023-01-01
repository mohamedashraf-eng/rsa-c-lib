/**
 * @file rsa_int.h
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
#ifndef __RSA_INT_H__
#define __RSA_INT_H__

/** @def Handeling name mangle */
#ifdef __cplusplus
extern "C" {
#endif

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
/**
 * @brief struct to store the algorithm parameters.
*/
typedef struct rsa_parameters
{
	struct 
	{
		uint64_t n;
		uint64_t phi;
		uint64_t e;
	}math_parameters;

	uint64_t publicKey;
	uint64_t privateKey;
}st_rsa_t;

/*
*--------------------------------------------------------------------------------------
*- Public Functions Declaration
*--------------------------------------------------------------------------------------
**/

void 
generate_keys(const uint8_t * const pString);

void 
public_testing(void);



/** @def Handeling name mangle */
#ifdef __cplusplus
}
#endif

#endif /* __RSA_INT_H__ */