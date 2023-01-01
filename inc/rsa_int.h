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


/*
*--------------------------------------------------------------------------------------
*- Public Functions Declaration
*--------------------------------------------------------------------------------------
**/

void 
generate_keys(const uint8_t * const pString);



/** @def Handeling name mangle */
#ifdef __cplusplus
}
#endif

#endif /* __RSA_INT_H__ */