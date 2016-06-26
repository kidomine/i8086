/*
 * i8086/i86_cpu.c
 *
 *   Created on: Jun 26, 2016 5:57:50 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference: https://en.wikipedia.org/wiki/Intel_8086
 */

#include <stdlib.h>
#include "i86_register.h"
#include "i86_logger.h"

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


/* Definition of a CPU type. */
typedef struct _i86_cpu_t
{
    i86_mode_e mode;

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

    /* program counter */
    i86_register16_t ip; // instruction pointer

    /* segment registers */
    i86_register16_t cs; // code segment
    i86_register16_t ds; // data segment
    i86_register16_t es; // extra segment
    i86_register16_t ss; // stack segment

    /* status registers */
    i86_register16_t sf; // status register flags
} i86_cpu_t;


/* CPU constructor/destructor */
i86_cpu_t
i86_cpu_create(void)
{
    i86_cpu_t cpu = NULL;

    cpu = malloc(sizeof(i86_cpu_t));
    if (cpu == NULL)
    {
        i86_logger("failed to create a CPU instance!");
    }

    memset(cpu, 0x00, sizeof(i86_cpu_t));
    cpu->mode = i86_mode_real;

    return cpu;
}

void
i86_cpu_destroy(i86_cpu_t cpu)
{
    if (cpu == NULL)
    {
        i86_logger("no CPU instance specified!");
    } else {
        free(cpu);
    }
}

void
i86_cpu_set_mode(i86_cpu_t cpu, i86_mode_e mode)
{
    cpu->mode = mode;
}

i86_mode_e
i86_cpu_get_mode(i86_cpu_t cpu)
{
    return cpu->mode;
}


/* API used to display the current CPU values. */

/* Helper API. */
static void
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

void
i86_cpu_print_info(i86_cpu_t cpu)
{
    i86_logger("CPU info for 0x%.8x\n");
    i86_logger("Mode: %d\n\n", cpu->mode);

    i86_logger("Main registers:\n");
    i86_cpu_print_register("    ax", &cpu->ax);
    i86_cpu_print_register("    bx", &cpu->bx);
    i86_cpu_print_register("    cx", &cpu->cx);
    i86_cpu_print_register("    dx", &cpu->dx);

    i86_logger("Index registers:\n");
    i86_logger("    si: 0x.8x\n", cpu->si);
    i86_logger("    di: 0x.8x\n", cpu->di);
    i86_logger("    bp: 0x.8x\n", cpu->bp);
    i86_logger("    sp: 0x.8x\n", cpu->sp);

    i86_logger("Segment registers:\n");
    i86_logger("    cs: 0x.8x\n", cpu->si);
    i86_logger("    ds: 0x.8x\n", cpu->ds);
    i86_logger("    es: 0x.8x\n", cpu->es);
    i86_logger("    ss: 0x.8x\n", cpu->ss);

    i86_logger("Program counter: 0x.8x\n", cpu->ip);
    i86_logger("Status register: 0x.8x\n\n", cpu->sf);
}

/* APIs used to set values to the CPU registers. */
/* Some helper APIs. */
static void
_i86_cpu_set_reg(i86_register16_t *reg, uint16_t value)
{
    reg->reg.reg16 = value;
}

static void
_i86_cpu_set_reg_l(i86_register16_t *reg, uint8_t value)
{
    reg->reg.reg8.reg_l = value;
}

static void
_i86_cpu_set_reg_h(i86_register16_t *reg, uint8_t value)
{
    reg->reg.reg8.reg_h = value;
}

/* APIs to set the value of the main registers. */
void
i86_cpu_set_reg_mr_ax(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->ax, value);
}

void
i86_cpu_set_reg_mr_ax_al(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_l(&cpu->ax, value);
}

void
i86_cpu_set_reg_mr_ax_ah(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_h(&cpu->ax, value);
}

void
i86_cpu_set_reg_mr_bx(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->bx, value);
}

void
i86_cpu_set_reg_mr_bx_bl(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_l(&cpu->bx, value);
}

void
i86_cpu_set_reg_mr_bx_bh(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_h(&cpu->bx, value);
}

void
i86_cpu_set_reg_mr_cx(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->cx, value);
}

void
i86_cpu_set_reg_mr_cx_cl(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_l(&cpu->cx, value);
}

void
i86_cpu_set_reg_mr_cx_ch(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_h(&cpu->cx, value);
}

void
i86_cpu_set_reg_mr_dx(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->dx, value);
}

void
i86_cpu_set_reg_mr_dx_dl(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_l(&cpu->dx, value);
}

void
i86_cpu_set_reg_mr_dx_dh(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_h(&cpu->dx, value);
}

/* APIs to set the value of the index registers. */
void
i86_cpu_set_reg_ir_si(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->si, value);
}

void
i86_cpu_set_reg_ir_di(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->di, value);
}

void
i86_cpu_set_reg_ir_bp(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->bp, value);
}

void
i86_cpu_set_reg_ir_sp(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->sp, value);
}

/* API to set the value of the program counter. */
void
i86_cpu_set_reg_pc_ip(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->ip, value);
}

/* APIs to set the value of the segment registers. */
void
i86_cpu_set_reg_sr_cs(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->cs, value);
}

void
i86_cpu_set_reg_sr_ds(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->ds, value);
}

void
i86_cpu_set_reg_sr_es(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->es, value);
}

void
i86_cpu_set_reg_sr_ss(i86_cpu_t cpu, uint16_t value)
{
    _i86_cpu_set_reg(&cpu->ss, value);
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
    _i86_cpu_set_reg_sf(&cpu->sf, I86_SR_CF_CARRY_FLAG);
}

void
i86_cpu_set_reg_sf_pf(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->sf, I86_SR_PF_PARITY_FLAG);
}

void
i86_cpu_set_reg_sf_af(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->sf, I86_SR_AF_AUXILLARY_FLAG);
}

void
i86_cpu_set_reg_sf_zf(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->sf, I86_SR_ZF_ZERO_FLAG);
}

void
i86_cpu_set_reg_sf_sf(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->sf, I86_SR_SF_SIGN_FLAG);
}

void
i86_cpu_set_reg_sf_tf(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->sf, I86_SR_TF_TRAP_FLAG);
}

void
i86_cpu_set_reg_sf_if(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->sf, I86_SR_IF_INTERRUPT_FLAG);
}

void
i86_cpu_set_reg_sf_df(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->sf, I86_SR_DF_DIRECTION_FLAG);
}

void
i86_cpu_set_reg_sf_of(i86_cpu_t cpu, uint8_t value)
{
    _i86_cpu_set_reg_sf(&cpu->sf, I86_SR_OF_OVERFLOW_FLAG);
}

/* APIs used to get the values of CPU registers. */
/* Some helper APIs. */
static uint16_t
_i86_cpu_get_reg(i86_register16_t *reg)
{
    return reg->reg.reg16;
}

static uint8_t
_i86_cpu_get_reg_l(i86_register16_t *reg)
{
    return reg->reg.reg8.reg_l;
}

static uint8_t
_i86_cpu_get_reg_h(i86_register16_t *reg)
{
    return reg->reg.reg8.reg_h;
}

/* APIs to get the value of the main registers. */
uint16_t
i86_cpu_get_reg_mr_ax(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->ax);
}

uint8_t
i86_cpu_get_reg_mr_ax_al(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_l(&cpu->ax);
}

uint8_t
i86_cpu_get_reg_mr_ax_ah(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_h(&cpu->ax);
}

uint16_t
i86_cpu_get_reg_mr_bx(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->bx);
}

uint8_t
i86_cpu_get_reg_mr_bx_bl(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_l(&cpu->bx);
}

uint8_t
i86_cpu_get_reg_mr_bx_bh(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_h(&cpu->bx);
}

uint16_t
i86_cpu_get_reg_mr_cx(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->cx);
}

uint8_t
i86_cpu_get_reg_mr_cx_cl(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_l(&cpu->cx);
}

uint8_t
i86_cpu_get_reg_mr_cx_ch(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_h(&cpu->cx);
}

uint16_t
i86_cpu_get_reg_mr_dx(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->dx);
}

uint8_t
i86_cpu_get_reg_mr_dx_dl(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_l(&cpu->dx);
}

uint8_t
i86_cpu_get_reg_mr_dx_dh(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_h(&cpu->dx);
}

/* APIs to get the value of the index registers. */
uint16_t
i86_cpu_get_reg_ir_si(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->si);
}

uint16_t
i86_cpu_get_reg_ir_di(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->di);
}

uint16_t
i86_cpu_get_reg_ir_bp(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->bp);
}

uint16_t
i86_cpu_get_reg_ir_sp(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->sp);
}

/* API to get the value of the program counter. */
uint16_t
i86_cpu_get_reg_pc_ip(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->ip);
}

/* APIs to set the value of the segment registers. */
uint16_t
i86_cpu_get_reg_sr_cs(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->cs);
}

uint16_t
i86_cpu_get_reg_sr_ds(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->ds);
}

uint16_t
i86_cpu_get_reg_sr_es(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->es);
}

uint16_t
i86_cpu_get_reg_sr_ss(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg(&cpu->ss);
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
    return _i86_cpu_get_reg_sf(&cpu->sf,
                               I86_SR_CF_CARRY_FLAG,
                               I86_SR_CF_CARRY_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_pf(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->sf,
                               I86_SR_PF_PARITY_FLAG,
                               I86_SR_PF_PARITY_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_af(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->sf,
                               I86_SR_AF_AUXILLARY_FLAG,
                               I86_SR_AF_AUXILLARY_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_zf(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->sf,
                               I86_SR_ZF_ZERO_FLAG,
                               I86_SR_ZF_ZERO_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_sf(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->sf,
                               I86_SR_SF_SIGN_FLAG,
                               I86_SR_SF_SIGN_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_tf(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->sf,
                               I86_SR_TF_TRAP_FLAG,
                               I86_SR_TF_TRAP_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_if(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->sf,
                               I86_SR_IF_INTERRUPT_FLAG,
                               I86_SR_IF_INTERRUPT_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_df(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->sf,
                               I86_SR_DF_DIRECTION_FLAG,
                               I86_SR_DF_DIRECTION_FLAG_SHIFT);
}

uint8_t
i86_cpu_get_reg_sf_of(i86_cpu_t cpu)
{
    return _i86_cpu_get_reg_sf(&cpu->sf,
                               I86_SR_OF_OVERFLOW_FLAG,
                               I86_SR_OF_OVERFLOW_FLAG_SHIFT);
}

