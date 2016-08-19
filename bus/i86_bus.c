/*
 * i8086/i86_bus.c
 *
 *   Created on: Aug 8, 2016 11:21:11 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference:
 */

#include "i86_bus.h"

/* Buses. */
volatile uint32_t address_bus;    /* 20-bit */
volatile uint16_t data_bus;       /* 16-bit */
volatile uint16_t control_bus;    /* 16-bit? */
