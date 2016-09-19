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
#include "i86_logger.h"
#include "i86_alu.h"
#include "i86_bus.h"
#include "i86_ceu.h"
#include "i86_clock.h"

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
extern i86_cpu_t  i86_cpu_create(void);
extern void       i86_cpu_destroy(i86_cpu_t *cpu);
extern void       i86_cpu_print_info(i86_cpu_t cpu);
extern void       i86_cpu_set_mode(i86_cpu_t cpu, i86_mode_e mode);
extern i86_mode_e i86_cpu_get_mode(i86_cpu_t cpu);
extern i86_alu_t  i86_cpu_get_alu(i86_cpu_t cpu);
extern i86_bus_t  i86_cpu_get_bus(i86_cpu_t cpu);
extern i86_ceu_t  i86_cpu_get_ceu(i86_cpu_t cpu);

#endif /* I86_CPU_H_ */
