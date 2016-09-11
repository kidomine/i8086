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
#include "i86_logger.h"

#define REG_HI 1
#define REG_LO 0


/* API used to print the content of a given register. */
void
i86_cpu_print_register(void *id, i86_register16_t *reg)
{
    char buff[I86_LOG_MSG_BUFF_LEN];

    memset(buff, 0x00, I86_LOG_MSG_BUFF_LEN);
    snprintf(buff,
             I86_LOG_MSG_BUFF_LEN,
             "%s : 0x%.4x (l: 0x%.2, h: 0x%.2)\n",
             id,
             reg->reg.reg16,
             reg->reg.reg8.reg_l,
             reg->reg.reg8.reg_h
             );

    i86_logger(buff);
}

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

