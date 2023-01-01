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
#ifndef __RSA_CFG_H__
#define __RSA_CFG_H__

/** @def Handeling name mangle */
#ifdef __cplusplus
extern "C" {
#endif

/*
*--------------------------------------------------------------------------------------
*- General Configuration parameters
*--------------------------------------------------------------------------------------
**/

/**
 * @defgroup Configuration Parameters
 *      @arg DEBUGGING_ACTIVE
 *      @arg DEBUGGING_INACTIVE
 */
#define DEBUGGING_FLAG              (DEBUGGING_ACTIVE)
/**
 * @defgroup Configuration Parameters
 *      @arg FULL_ASSERTION_ACTIVE
 *      @arg FULL_ASSERTION_INACTIVE
 */
#define FULL_ASSERTION_FLAG         (FULL_ASSERTION_ACTIVE)


/*
*--------------------------------------------------------------------------------------
*- x Configuration parameters
*--------------------------------------------------------------------------------------
**/


/** @def Handeling name mangle */
#ifdef __cplusplus
}
#endif

#endif /* __RSA_CFG_H__ */