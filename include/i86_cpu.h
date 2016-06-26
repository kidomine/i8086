/*
 * i8086/i86_cpu.h
 *
 *   Created on: Jun 26, 2016 6:01:17 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference: https://en.wikipedia.org/wiki/Intel_8086
 */

#ifndef I86_CPU_H_
#define I86_CPU_H_

#include "i86_register.h"

/* Execution modes. */
typedef enum _i86_mode_e{
    i86_mode_real = 0,  // real mode
    i86_mode_protected, // protected mode
    i86_mode_long,      // long mode
    i86_mode_virtual86, // virtual 86 mode
    i86_mode_sys_mgt    // system management mode
} i86_mode_e;

/* Forward declaration for a CPU type. */
typedef struct _i86_cpu_t *i86_cpu_t;

/* CPU constructor/destructor */
extern i86_cpu_t i86_cpu_create(void);
extern void i86_cpu_destroy(i86_cpu_t cpu);
extern void i86_cpu_print_info(i86_cpu_t cpu);
extern void i86_cpu_set_mode(i86_cpu_t cpu, i86_mode_e mode);
extern i86_mode_e i86_cpu_get_mode(i86_cpu_t cpu);

/* APIs used to set the CPU registers. */
/* APIs to set the value of the main registers. */
extern void i86_set_reg_mr_ax(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_mr_ax_al(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_mr_ax_ah(i86_cpu_t cpu, uint8_t value);

extern void i86_set_reg_mr_bx(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_mr_bx_bl(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_mr_bx_bh(i86_cpu_t cpu, uint8_t value);

extern void i86_set_reg_mr_cx(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_mr_cx_cl(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_mr_cx_ch(i86_cpu_t cpu, uint8_t value);

extern void i86_set_reg_mr_dx(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_mr_dx_dl(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_mr_dx_dh(i86_cpu_t cpu, uint8_t value);

/* APIs to set the value of the index registers. */
extern void i86_set_reg_ir_si(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_ir_di(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_ir_bp(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_ir_sp(i86_cpu_t cpu, uint16_t value);

/* API to set the value of the program counter. */
extern void i86_set_reg_pc_ip(i86_cpu_t cpu, uint16_t value);

/* APIs to set the value of the segment registers. */
extern void i86_set_reg_sr_cs(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_sr_ds(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_sr_es(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_sr_ss(i86_cpu_t cpu, uint16_t value);

/* APIs to set the flags in the status register. */
extern void i86_set_reg_sf_cf(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_sf_pf(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_sf_af(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_sf_zf(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_sf_sf(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_sf_tf(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_sf_if(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_sf_df(i86_cpu_t cpu, uint8_t value);
extern void i86_set_reg_sf_of(i86_cpu_t cpu, uint8_t value);

/* APIs used to get the values of CPU registers. */
/* APIs to get the value of the main registers. */
extern uint16_t i86_cpu_get_reg_mr_ax(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_mr_ax_al(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_mr_ax_ah(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_mr_bx(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_mr_bx_bl(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_mr_bx_bh(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_mr_cx(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_mr_cx_cl(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_mr_cx_ch(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_mr_dx(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_mr_dx_dl(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_mr_dx_dh(i86_cpu_t cpu);

/* APIs to get the value of the index registers. */
extern uint16_t i86_cpu_get_reg_ir_si(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_ir_di(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_ir_bp(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_ir_sp(i86_cpu_t cpu);

/* API to get the value of the program counter. */
extern uint16_t i86_cpu_get_reg_pc_ip(i86_cpu_t cpu);

/* APIs to set the value of the segment registers. */
extern uint16_t i86_cpu_get_reg_sr_cs(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_sr_ds(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_sr_es(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_sr_ss(i86_cpu_t cpu);

/* APIs to get the flags in the status register. */
extern uint8_t i86_cpu_get_reg_sf_cf(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_sf_pf(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_sf_af(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_sf_zf(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_sf_sf(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_sf_tf(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_sf_if(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_sf_df(i86_cpu_t cpu);
extern uint8_t i86_cpu_get_reg_sf_of(i86_cpu_t cpu);

#endif /* I86_CPU_H_ */
