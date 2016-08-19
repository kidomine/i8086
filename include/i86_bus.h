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

extern volatile uint32_t address_bus;    /* 20-bit */
extern volatile uint16_t data_bus;       /* 16-bit */
extern volatile uint16_t control_bus;    /* 16-bit? */

#endif /* I86_BUS_H_ */
