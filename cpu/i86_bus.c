/*
 * i8086/i86_bus.c
 *
 *   Created on: Aug 8, 2016 11:21:11 PM
 *       Author: yan@artemis
 *
 *  Description: Implementation of the CPU's bus unit.
 *    Reference:
 */

#include <stdlib.h>
#include "i86_logger.h"
#include "i86_bus.h"

typedef struct _i86_bus_t
{
    /* program counter */
    i86_register16_t ip; // instruction pointer

    /* segment registers */
    i86_register16_t cs;     // code segment
    i86_register16_t ds;     // data segment
    i86_register16_t es;     // extra segment
    i86_register16_t ss;     // stack segment

    uint32_t address_bus;    /* 20-bit */
    uint16_t data_bus;       /* 16-bit */
    uint16_t control_bus;    /* 16-bit? */
};

/* BUS constructor/destructor */
i86_bus_t
i86_bus_create(void)
{
    i86_bus_t bus = NULL;

    bus = (struct _i86_bus_t *)malloc(sizeof(struct _i86_bus_t));

    return bus;
}

void
i86_bus_destroy(i86_bus_t *bus)
{
    if(bus != NULL)
    {
        if(*bus != NULL)
        {
            free(*bus);
            *bus = NULL;
        } else {
            i86_logger("invalid BUS instance!");
        }
    } else {
        i86_logger("no BUS instance provided!");
    }
}

void
i86_bus_print_registers(i86_bus_t bus)
{
    i86_logger("Segment registers:\n");
    i86_logger("    cs: 0x.8x\n", bus->cs);
    i86_logger("    ds: 0x.8x\n", bus->ds);
    i86_logger("    es: 0x.8x\n", bus->es);
    i86_logger("    ss: 0x.8x\n", bus->ss);

    i86_logger("Program counter: 0x.8x\n", bus->ip);
}


/* API to set the value of the program counter. */
void
i86_cpu_set_reg_pc_ip(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->bus->ip, value);
}

/* APIs to set the value of the segment registers. */
void
i86_cpu_set_reg_sr_cs(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->bus->cs, value);
}

void
i86_cpu_set_reg_sr_ds(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->bus->ds, value);
}

void
i86_cpu_set_reg_sr_es(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->bus->es, value);
}

void
i86_cpu_set_reg_sr_ss(i86_cpu_t cpu, uint16_t value)
{
    i86_register_set_reg(&cpu->bus->ss, value);
}

/* API to get the value of the program counter. */
uint16_t
i86_cpu_get_reg_pc_ip(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->bus->ip);
}

/* APIs to set the value of the segment registers. */
uint16_t
i86_cpu_get_reg_sr_cs(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->bus->cs);
}

uint16_t
i86_cpu_get_reg_sr_ds(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->bus->ds);
}

uint16_t
i86_cpu_get_reg_sr_es(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->bus->es);
}

uint16_t
i86_cpu_get_reg_sr_ss(i86_cpu_t cpu)
{
    return i86_register_get_reg(&cpu->bus->ss);
}
