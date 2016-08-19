/*
 * i8086/i86_operand.h
 *
 *   Created on: Jul 2, 2016 9:07:14 AM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference:
 */

#ifndef I86_OPERAND_H_
#define I86_OPERAND_H_

#include "i86_cpu.h"

typedef uint8_t
i86_ope_read_fn(void     *dst,
                uint32_t  dst_len,
                void     *src,
                uint32_t  src_len);

typedef void
i86_ope_write_fn(void     *dst,
                 uint32_t  dst_len,
                 void     *src,
                 uint32_t  src_len);

typedef struct _i86_ope_t
{
    uint8_t           opcode;
    i86_ope_read_fn  *read_cb;
    i86_ope_write_fn *write_cb;
} i86_ope_t;

#endif /* I86_OPERAND_H_ */
