/*
 * i8086/i86_clock.h
 *
 *   Created on: Sep 19, 2016 11:13:22 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference:
 */

#ifndef I86_CLOCK_H_
#define I86_CLOCK_H_

typedef struct _i86_clock_t *i86_clock_t;

extern i86_clock_t i86_clk_create(void);
extern void        i86_clk_destroy(i86_clock_t *clock);
extern void        i86_clk_tick(i86_clock_t clock);

#endif /* I86_CLOCK_H_ */
