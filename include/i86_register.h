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

typedef uint8_t  _i86_reg8_t;
typedef uint16_t _i86_reg16_t;

typedef struct _i86_register8_t
{
    _i86_reg8_t reg_h;
    _i86_reg8_t reg_l;
} i86_register8_t;

typedef struct _i86_register16_t
{
    union {
        _i86_reg16_t    reg16;
        i86_register8_t reg8;
    } reg;
} i86_register16_t;

/* APIs used to get the values of CPU registers. */
extern uint16_t
i86_register_get_reg(i86_register16_t *reg);

extern uint8_t
i86_register_get_reg_l(i86_register16_t *reg);

extern uint8_t
i86_register_get_reg_h(i86_register16_t *reg);

/* APIs used to set values to the CPU registers. */
extern void
i86_register_set_reg(i86_register16_t *reg, uint16_t value);

extern void
i86_register_set_reg_l(i86_register16_t *reg, uint8_t value);

extern void
i86_register_set_reg_h(i86_register16_t *reg, uint8_t value);

#endif /* I86_REGISTER_H_ */
