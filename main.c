/**
 * @file main.c
 * @author Mohamed ashraf (wx@wx.com)
 * @brief main entrypoint for the library
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) Wx 2023
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "rsa_int.h"

/**
 * @brief main entry point function
 * 
 * @return int 
 */
int main(void)
{
    generate_keys("Hello? I am mohamed ashraf ");

    printf("\n");
    /* Run forever */
    while(1) {;}

    return 0;
}