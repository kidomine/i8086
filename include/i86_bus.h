/*
 * i8086/i86_bus.h
 *
 *   Created on: Aug 8, 2016 11:23:39 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference:
 */

#ifndef I86_BUS_H_
#define I86_BUS_H_

#include <stdint.h>

/* Forward declaration for a BUS type. */
typedef struct _i86_bus_t *i86_bus_t;

/* BUS constructor/destructor */
extern i86_bus_t i86_bus_create(void);
extern void      i86_bus_destroy(i86_bus_t *bus);


/* API to set the value of the program counter. */
extern void i86_set_reg_pc_ip(i86_cpu_t cpu, uint16_t value);

/* APIs to set the value of the segment registers. */
extern void i86_set_reg_sr_cs(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_sr_ds(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_sr_es(i86_cpu_t cpu, uint16_t value);
extern void i86_set_reg_sr_ss(i86_cpu_t cpu, uint16_t value);

/* API to get the value of the program counter. */
extern uint16_t i86_cpu_get_reg_pc_ip(i86_cpu_t cpu);

/* APIs to set the value of the segment registers. */
extern uint16_t i86_cpu_get_reg_sr_cs(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_sr_ds(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_sr_es(i86_cpu_t cpu);
extern uint16_t i86_cpu_get_reg_sr_ss(i86_cpu_t cpu);

#endif /* I86_BUS_H_ */
