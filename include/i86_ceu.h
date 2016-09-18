/*
 * i8086/i86_ceu.h
 *
 *   Created on: Sep 11, 2016 10:58:39 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference:
 */

#ifndef I86_CEU_H_
#define I86_CEU_H_

#include "i86_register.h"

/* Forward declaration for a CEU type. */
typedef struct _i86_ceu_t *i86_ceu_t;

/* CEU constructor/destructor */
extern i86_ceu_t i86_ceu_create(void);
extern void      i86_ceu_destroy(i86_ceu_t *ceu);
extern void      i86_ceu_print_registers(i86_ceu_t ceu);

/* APIs used to set the CPU registers. */
/* APIs to set the value of the main registers. */
extern void i86_ceu_set_reg_mr_ax(i86_ceu_t ceu, uint16_t value);
extern void i86_ceu_set_reg_mr_ax_al(i86_ceu_t ceu, uint8_t value);
extern void i86_ceu_set_reg_mr_ax_ah(i86_ceu_t ceu, uint8_t value);

extern void i86_ceu_set_reg_mr_bx(i86_ceu_t ceu, uint16_t value);
extern void i86_ceu_set_reg_mr_bx_bl(i86_ceu_t ceu, uint8_t value);
extern void i86_ceu_set_reg_mr_bx_bh(i86_ceu_t ceu, uint8_t value);

extern void i86_ceu_set_reg_mr_cx(i86_ceu_t ceu, uint16_t value);
extern void i86_ceu_set_reg_mr_cx_cl(i86_ceu_t ceu, uint8_t value);
extern void i86_ceu_set_reg_mr_cx_ch(i86_ceu_t ceu, uint8_t value);

extern void i86_ceu_set_reg_mr_dx(i86_ceu_t ceu, uint16_t value);
extern void i86_ceu_set_reg_mr_dx_dl(i86_ceu_t ceu, uint8_t value);
extern void i86_ceu_set_reg_mr_dx_dh(i86_ceu_t ceu, uint8_t value);

/* APIs to set the value of the index registers. */
extern void i86_ceu_set_reg_ir_si(i86_ceu_t ceu, uint16_t value);
extern void i86_ceu_set_reg_ir_di(i86_ceu_t ceu, uint16_t value);
extern void i86_ceu_set_reg_ir_bp(i86_ceu_t ceu, uint16_t value);
extern void i86_ceu_set_reg_ir_sp(i86_ceu_t ceu, uint16_t value);


/* APIs used to get the values of CPU registers. */
/* APIs to get the value of the main registers. */
extern uint16_t i86_ceu_get_reg_mr_ax(i86_ceu_t ceu);
extern uint8_t i86_ceu_get_reg_mr_ax_al(i86_ceu_t ceu);
extern uint8_t i86_ceu_get_reg_mr_ax_ah(i86_ceu_t ceu);
extern uint16_t i86_ceu_get_reg_mr_bx(i86_ceu_t ceu);
extern uint8_t i86_ceu_get_reg_mr_bx_bl(i86_ceu_t ceu);
extern uint8_t i86_ceu_get_reg_mr_bx_bh(i86_ceu_t ceu);
extern uint16_t i86_ceu_get_reg_mr_cx(i86_ceu_t ceu);
extern uint8_t i86_ceu_get_reg_mr_cx_cl(i86_ceu_t ceu);
extern uint8_t i86_ceu_get_reg_mr_cx_ch(i86_ceu_t ceu);
extern uint16_t i86_ceu_get_reg_mr_dx(i86_ceu_t ceu);
extern uint8_t i86_ceu_get_reg_mr_dx_dl(i86_ceu_t ceu);
extern uint8_t i86_ceu_get_reg_mr_dx_dh(i86_ceu_t ceu);

/* APIs to get the value of the index registers. */
extern uint16_t i86_ceu_get_reg_ir_si(i86_ceu_t ceu);
extern uint16_t i86_ceu_get_reg_ir_di(i86_ceu_t ceu);
extern uint16_t i86_ceu_get_reg_ir_bp(i86_ceu_t ceu);
extern uint16_t i86_ceu_get_reg_ir_sp(i86_ceu_t ceu);

#endif /* I86_CEU_H_ */
