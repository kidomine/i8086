/*
 * i8086/i86_instruction_set.h
 *
 *   Created on: Jul 1, 2016 1:56:21 AM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference:
 */

#ifndef I86_INSTRUCTION_SET_H_
#define I86_INSTRUCTION_SET_H_

#include <stdlib.h>
#include "i86_cpu.h"

typedef void
        i86_iset_fn(i86_cpu_t cpu, uint32_t ope_count, void *ope[]);


#endif /* I86_INSTRUCTION_SET_H_ */
