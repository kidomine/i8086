/*
 * i8086/i86_ceu.c
 *
 *   Created on: Sep 11, 2016 10:55:26 PM
 *       Author: yan@artemis
 *
 *  Description: Implementation of the CPU's execution unit.
 *    Reference:
 */

#include <stdlib.h>
#include "i86_logger.h"
#include "i86_ceu.h"

typedef struct _i86_ceu_t
{
    /* main registers */
    i86_register16_t ax; // primary accumulator
    i86_register16_t bx; // base, accumulator
    i86_register16_t cx; // counter, accumulator
    i86_register16_t dx; // accumulator, other functions

    /* index registers */
    i86_register16_t si; // source index
    i86_register16_t di; // destination index
    i86_register16_t bp; // base pointer
    i86_register16_t sp; // stack pointer
};


/* CEU constructor/destructor */
i86_ceu_t
i86_ceu_create(void)
{
    i86_ceu_t ceu = NULL;

    ceu = (struct _i86_ceu_t *)malloc(sizeof(struct _i86_ceu_t));

    return ceu;
}

void
i86_ceu_destroy(i86_ceu_t *ceu)
{
    if(ceu != NULL)
    {
        if(*ceu != NULL)
        {
            free(*ceu);
            *ceu = NULL;
        } else {
            i86_logger("invalid CEU instance!");
        }
    } else {
        i86_logger("no CEU instance provided!");
    }
}

/* APIs to set the value of the main registers. */
void
i86_cpu_set_reg_mr_ax(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->ceu->ax, value);
}

void
i86_cpu_set_reg_mr_ax_al(i86_cpu_t cpu, uint8_t value)
{
    i86_register_set_reg_l(&cpu->ceu->ax, value);
}

void
i86_cpu_set_reg_mr_ax_ah(i86_cpu_t cpu, uint8_t value)
{
    i86_register_set_reg_h(&cpu->ceu->ax, value);
}

void
i86_cpu_set_reg_mr_bx(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->ceu->bx, value);
}

void
i86_cpu_set_reg_mr_bx_bl(i86_cpu_t cpu, uint8_t value)
{
    i86_register_set_reg_l(&cpu->ceu->bx, value);
}

void
i86_cpu_set_reg_mr_bx_bh(i86_cpu_t cpu, uint8_t value)
{
    i86_register_set_reg_h(&cpu->ceu->bx, value);
}

void
i86_cpu_set_reg_mr_cx(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->ceu->cx, value);
}

void
i86_cpu_set_reg_mr_cx_cl(i86_cpu_t cpu, uint8_t value)
{
    i86_register_set_reg_l(&cpu->ceu->cx, value);
}

void
i86_cpu_set_reg_mr_cx_ch(i86_cpu_t cpu, uint8_t value)
{
    i86_register_set_reg_h(&cpu->ceu->cx, value);
}

void
i86_cpu_set_reg_mr_dx(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->ceu->dx, value);
}

void
i86_cpu_set_reg_mr_dx_dl(i86_cpu_t cpu, uint8_t value)
{
    i86_register_set_reg_l(&cpu->ceu->dx, value);
}

void
i86_cpu_set_reg_mr_dx_dh(i86_cpu_t cpu, uint8_t value)
{
    i86_register_set_reg_h(&cpu->ceu->dx, value);
}

/* APIs to set the value of the index registers. */
void
i86_cpu_set_reg_ir_si(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->ceu->si, value);
}

void
i86_cpu_set_reg_ir_di(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->ceu->di, value);
}

void
i86_cpu_set_reg_ir_bp(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->ceu->bp, value);
}

void
i86_cpu_set_reg_ir_sp(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->ceu->sp, value);
}

/* APIs to get the value of the main registers. */
uint16_t
i86_cpu_get_reg_mr_ax(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->ceu->ax);
}

uint8_t
i86_cpu_get_reg_mr_ax_al(i86_cpu_t cpu)
{
    return i86_register_get_reg_l(&cpu->ceu->ax);
}

uint8_t
i86_cpu_get_reg_mr_ax_ah(i86_cpu_t cpu)
{
    return i86_register_get_reg_h(&cpu->ceu->ax);
}

uint16_t
i86_cpu_get_reg_mr_bx(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->ceu->bx);
}

uint8_t
i86_cpu_get_reg_mr_bx_bl(i86_cpu_t cpu)
{
    return i86_register_get_reg_l(&cpu->ceu->bx);
}

uint8_t
i86_cpu_get_reg_mr_bx_bh(i86_cpu_t cpu)
{
    return i86_register_get_reg_h(&cpu->ceu->bx);
}

uint16_t
i86_cpu_get_reg_mr_cx(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->ceu->cx);
}

uint8_t
i86_cpu_get_reg_mr_cx_cl(i86_cpu_t cpu)
{
    return i86_register_get_reg_l(&cpu->ceu->cx);
}

uint8_t
i86_cpu_get_reg_mr_cx_ch(i86_cpu_t cpu)
{
    return i86_register_get_reg_h(&cpu->ceu->cx);
}

uint16_t
i86_cpu_get_reg_mr_dx(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->ceu->dx);
}

uint8_t
i86_cpu_get_reg_mr_dx_dl(i86_cpu_t cpu)
{
    return i86_register_get_reg_l(&cpu->ceu->dx);
}

uint8_t
i86_cpu_get_reg_mr_dx_dh(i86_cpu_t cpu)
{
    return i86_register_get_reg_h(&cpu->ceu->dx);
}

/* APIs to get the value of the index registers. */
uint16_t
i86_cpu_get_reg_ir_si(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->ceu->si);
}

uint16_t
i86_cpu_get_reg_ir_di(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->ceu->di);
}

uint16_t
i86_cpu_get_reg_ir_bp(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->ceu->bp);
}

uint16_t
i86_cpu_get_reg_ir_sp(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->ceu->sp);
}
