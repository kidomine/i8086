/*
 * i8086/i86_reg.c
 *
 *   Created on: Aug 8, 2016 11:56:46 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference:
 */

#include "i86_register.h"

#define REG_HI 1
#define REG_LO 0

/* APIs used to get the values of CPU registers. */
static uint8_t
_i86_register_get_reg_8(i86_register8_t *reg8, uint16_t hilo)
{
    if(REG_HI == hilo)
    {
        return reg8->reg_h;
    } else {
        return reg8->reg_l;
    }
}

uint16_t
i86_register_get_reg(i86_register16_t *reg)
{
    return reg->reg.reg16;
}

uint8_t
i86_register_get_reg_l(i86_register16_t *reg)
{
    return _i86_register_get_reg_8(&reg->reg.reg8, REG_LO);
}

uint8_t
i86_register_get_reg_h(i86_register16_t *reg)
{
    return _i86_register_get_reg_8(&reg->reg.reg8, REG_HI);
}

/* APIs used to set values to the CPU registers. */
static void
_i86_register_set_reg_8(i86_register8_t *reg8, uint16_t hilo, uint8_t value)
{
    if(REG_HI == hilo)
    {
        reg8->reg_h = value;
    } else {
        reg8->reg_l = value;
    }
}

void
i86_register_set_reg(i86_register16_t *reg, uint16_t value)
{
    reg->reg.reg16 = value;
}

void
i86_register_set_reg_l(i86_register16_t *reg, uint8_t value)
{
    _i86_register_set_reg_8(&reg->reg.reg8, REG_LO, value);
}

void
i86_register_set_reg_h(i86_register16_t *reg, uint8_t value)
{
    _i86_register_set_reg_8(&reg->reg.reg8, REG_HI, value);
}

