/*
 * i8086/i86_instruction_set.c
 *
 *   Created on: Jun 26, 2016 9:10:29 PM
 *       Author: yan@artemis
 *
 *  Description: Imlementation for the 8086 instruction set.
 *    Reference: http://www.gabrielececchetti.it/Teaching/CalcolatoriElettronici/Docs/i8086_instruction_set.pdf
 */

#include "i86_instruction_set.h"

/*
 * AAA AAD AAM AAS ADC ADD AND
 * CALL CBW CLC CLD CLI CMC CMP CMPSB CMPSW CWD
 */

/* AAA - ASCII Adjust after Addition.
 * Corrects result in AH and AL after addition when working with BCD values.
 */
void
i86_iset_aaa(i86_cpu_t cpu, i86_ope_t ope1, i86_ope_t ope2)
{
    uint8_t ah = i86_cpu_get_reg_mr_ax_ah(cpu);
    uint8_t al = i86_cpu_get_reg_mr_ax_al(cpu);
    uint8_t af = i86_cpu_get_reg_sf_af(cpu);

    if (((0x0f & al) > 9) || (af == 1))
    {
        al = al + 6;
        i86_cpu_set_reg_mr_ax_ah(ah + 1);

        i86_cpu_set_reg_sf_af(1);
        i86_cpu_set_reg_sf_cf(1);
    } else {
        i86_cpu_set_reg_sf_af(0);
        i86_cpu_set_reg_sf_cf(0);
    }

    al = al & 0x0f;
    i86_cpu_set_reg_mr_ax_al(al);

    return;
}


/* AAD - ASCII Adjust before Division.
 * Prepares two BCD values for division.
 */
void
i86_iset_aad(i86_cpu_t cpu, i86_ope_t ope1, i86_ope_t ope2)
{
    uint8_t ah = i86_cpu_get_reg_mr_ax_ah(cpu);
    uint8_t al = i86_cpu_get_reg_mr_ax_al(cpu);

    al = (ah * 10) + al;
    ah = 0;

    i86_cpu_set_reg_mr_ax_al(al);
    i86_cpu_set_reg_mr_ax_ah(ah);

    return;
}


/* AAM - ASCII Adjust after Multiplication.
 * Corrects the result of multiplication of two BCD values.
 */
void
i86_iset_aam(i86_cpu_t cpu, i86_ope_t ope1, i86_ope_t ope2)
{
    uint8_t ah = 0;
    uint8_t al = i86_cpu_get_reg_mr_ax_al(cpu);

    ah = (al / 10);
    al = al - (ah * 10);

    i86_cpu_set_reg_mr_ax_al(al);
    i86_cpu_set_reg_mr_ax_ah(ah);

    return;
}


/* AAS - ASCII Adjust after Subtraction.
 * Corrects result in AH and AL after subtraction when working with BCD values.
 */
void
i86_iset_aas(i86_cpu_t cpu, i86_ope_t ope1, i86_ope_t ope2)
{
    uint8_t ah = i86_cpu_get_reg_mr_ax_ah(cpu);
    uint8_t al = i86_cpu_get_reg_mr_ax_al(cpu);
    uint8_t af = i86_cpu_get_reg_sf_af(cpu);

    if (((0x0f & al) > 9) || (af == 1))
    {
        al = al - 6;
        i86_cpu_set_reg_mr_ax_ah(ah - 1);

        i86_cpu_set_reg_sf_af(1);
        i86_cpu_set_reg_sf_cf(1);
    } else {
        i86_cpu_set_reg_sf_af(0);
        i86_cpu_set_reg_sf_cf(0);
    }

    al = al & 0x0f;
    i86_cpu_set_reg_mr_ax_al(al);

    return;
}


/* ADC - Add with Carry.
 */
void
i86_iset_adc(i86_cpu_t cpu, i86_ope_t ope1, i86_ope_t ope2)
{
    uint8_t   cf   = i86_cpu_get_reg_sf_cf(cpu);
    uint16_t *ope1 = ope[0];
    uint16_t *ope2 = ope[1];

    *ope1 = *ope1 + *ope2 + cf;

    return;
}


/* ADD - Add.
 */
void
i86_iset_add(i86_cpu_t cpu, i86_ope_t ope1, i86_ope_t ope2)
{
    uint16_t *ope1 = ope[0];
    uint16_t *ope2 = ope[1];

    *ope1 = *ope1 + *ope2;

    return;
}


/* AND - Logical AND.
 * Logical AND between all bits of two operands.
 * Result is stored in operand1.
 */
void
i86_iset_and(i86_cpu_t cpu, i86_ope_t ope1, i86_ope_t ope2)
{
    uint16_t *ope1 = ope[0];
    uint16_t *ope2 = ope[1];

    *ope1 = *ope1 & *ope2;

    return;
}
