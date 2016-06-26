/*
 * i8086/i86_registers.h
 *
 *   Created on: Jun 26, 2016 5:45:58 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference:
 */

#ifndef I86_REGISTER_H_
#define I86_REGISTER_H_

#include <stdint.h>

typedef struct _i86_register8_t
{
    uint8_t reg_h;
    uint8_t reg_l;
} i86_register8_t;

typedef struct _i86_register16_t
{
    union {
        uint16_t        reg16;
        i86_register8_t reg8;
    } reg;

} i86_register16_t;


#endif /* I86_REGISTER_H_ */
