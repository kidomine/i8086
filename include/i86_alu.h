/*
 * i8086/i86_alu.h
 *
 *   Created on: Sep 11, 2016 10:42:49 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference:
 */

#ifndef I86_ALU_H_
#define I86_ALU_H_

#include "i86_register.h"

/* Forward declaration for a ALU type. */
typedef struct _i86_alu_t *i86_alu_t;


/* ALU constructor/destructor */
extern i86_alu_t i86_alu_create(void);
extern void      i86_alu_destroy(i86_alu_t *alu);


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

#endif /* I86_ALU_H_ */
