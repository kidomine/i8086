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

/* Some pre-processing directives */
/* Status register flags. */
#define I86_SR_OF_OVERFLOW_FLAG        0x0800
#define I86_SR_DF_DIRECTION_FLAG       0x0400
#define I86_SR_IF_INTERRUPT_FLAG       0x0200
#define I86_SR_TF_TRAP_FLAG            0x0100
#define I86_SR_SF_SIGN_FLAG            0x0080
#define I86_SR_ZF_ZERO_FLAG            0x0040
#define I86_SR_AF_AUXILLARY_FLAG       0x0010
#define I86_SR_PF_PARITY_FLAG          0x0004
#define I86_SR_CF_CARRY_FLAG           0x0001

/* Shifts for the status register flags. */
#define I86_SR_OF_OVERFLOW_FLAG_SHIFT  11
#define I86_SR_DF_DIRECTION_FLAG_SHIFT 10
#define I86_SR_IF_INTERRUPT_FLAG_SHIFT 9
#define I86_SR_TF_TRAP_FLAG_SHIFT      8
#define I86_SR_SF_SIGN_FLAG_SHIFT      7
#define I86_SR_ZF_ZERO_FLAG_SHIFT      6
#define I86_SR_AF_AUXILLARY_FLAG_SHIFT 4
#define I86_SR_PF_PARITY_FLAG_SHIFT    2
#define I86_SR_CF_CARRY_FLAG_SHIFT     0

/* Some basic type definitions. */
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


/* API used to print the content of a given register. */
extern void
i86_cpu_print_register(void *id, i86_register16_t *reg);

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
