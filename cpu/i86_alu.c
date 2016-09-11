/*
 * i8086/i86_alu.c
 *
 *   Created on: Sep 11, 2016 10:55:43 PM
 *       Author: yan@artemis
 *
 *  Description: Implementation of the CPU's arithmetic and logic unit.
 *    Reference:
 */

#include <stdlib.h>
#include "i86_logger.h"
#include "i86_alu.h"

/* Definition of a CPU type. */
typedef struct _i86_alu_t
{
    /* status registers */
    i86_register16_t sf; // status register flags
} i86_alu_t;


/* ALU constructor/destructor */
i86_alu_t
i86_alu_create(void)
{
    i86_alu_t alu = NULL;

    alu = (struct _i86_alu_t *)malloc(sizeof(struct _i86_alu_t));

    return alu;
}

void
i86_alu_destroy(i86_alu_t *alu)
{
    if(alu != NULL)
    {
        if(*alu != NULL)
        {
            free(*alu);
            *alu = NULL;
        } else {
            i86_logger("invalid ALU instance!");
        }
    } else {
        i86_logger("no ALU instance provided!");
    }
}


/* APIs to set the flags in the status register. */
/* Helper API. Toggles the current value of the given register flag. */
static void
_i86_cpu_set_reg_sf(i86_register16_t reg, uint16_t flag)
{
    uint16_t temp = reg->reg.reg16;

    if(temp & flag)
    {
        temp &= (~flag);
    } else {
        temp |= flag;
    }

    reg->reg.reg16 = temp;
}

void
i86_cpu_set_reg_sf_cf(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->alu->sf, I86_SR_CF_CARRY_FLAG);
}

void
i86_cpu_set_reg_sf_pf(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->alu->sf, I86_SR_PF_PARITY_FLAG);
}

void
i86_cpu_set_reg_sf_af(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->alu->sf, I86_SR_AF_AUXILLARY_FLAG);
}

void
i86_cpu_set_reg_sf_zf(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->alu->sf, I86_SR_ZF_ZERO_FLAG);
}

void
i86_cpu_set_reg_sf_sf(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->alu->sf, I86_SR_SF_SIGN_FLAG);
}

void
i86_cpu_set_reg_sf_tf(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->alu->sf, I86_SR_TF_TRAP_FLAG);
}

void
i86_cpu_set_reg_sf_if(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->alu->sf, I86_SR_IF_INTERRUPT_FLAG);
}

void
i86_cpu_set_reg_sf_df(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->alu->sf, I86_SR_DF_DIRECTION_FLAG);
}

void
i86_cpu_set_reg_sf_of(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->alu->sf, I86_SR_OF_OVERFLOW_FLAG);
}

/* APIs to get the flags in the status register. */
/* Helper API. Toggles the current value of the given register flag. */
static uint8_t
_i86_cpu_get_reg_sf(i86_register16_t reg, uint16_t flag, uint16_t shift)
{
    return (reg->reg.reg16 & flag) >> shift;
}

uint8_t
i86_cpu_get_reg_sf_cf(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->alu->sf,
                               I86_SR_CF_CARRY_FLAG,
                               I86_SR_CF_CARRY_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_pf(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->alu->sf,
                               I86_SR_PF_PARITY_FLAG,
                               I86_SR_PF_PARITY_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_af(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->alu->sf,
                               I86_SR_AF_AUXILLARY_FLAG,
                               I86_SR_AF_AUXILLARY_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_zf(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->alu->sf,
                               I86_SR_ZF_ZERO_FLAG,
                               I86_SR_ZF_ZERO_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_sf(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->alu->sf,
                               I86_SR_SF_SIGN_FLAG,
                               I86_SR_SF_SIGN_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_tf(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->alu->sf,
                               I86_SR_TF_TRAP_FLAG,
                               I86_SR_TF_TRAP_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_if(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->alu->sf,
                               I86_SR_IF_INTERRUPT_FLAG,
                               I86_SR_IF_INTERRUPT_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_df(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->alu->sf,
                               I86_SR_DF_DIRECTION_FLAG,
                               I86_SR_DF_DIRECTION_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_of(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->alu->sf,
                               I86_SR_OF_OVERFLOW_FLAG,
                               I86_SR_OF_OVERFLOW_FLAG_SHIFT);
}

