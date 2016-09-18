/*
 * i8086/i86_cpu.c
 *
 *   Created on: Jun 26, 2016 5:57:50 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference: https://en.wikipedia.org/wiki/Intel_8086
 */

#include <stdlib.h>
#include <string.h>
#include "i86_register.h"
#include "i86_cpu.h"

/* Definition of a CPU type. */
typedef struct _i86_cpu_t
{
    i86_mode_e mode;

    i86_ceu_t ceu;
    i86_alu_t alu;
    i86_bus_t bus;
};


/* CPU constructor/destructor */
i86_cpu_t
i86_cpu_create(void)
{
    i86_cpu_t cpu = NULL;

    cpu = malloc(sizeof(i86_cpu_t));
    if (cpu != NULL)
    {
        memset(cpu, 0x00, sizeof(struct _i86_cpu_t));

        cpu->alu = i86_alu_create();
        if (cpu->alu != NULL)
        {
            cpu->bus = i86_bus_create();
            if (cpu->bus != NULL)
            {
                cpu->ceu = i86_ceu_create();
                if (cpu->ceu != NULL)
                {
                    cpu->mode = i86_mode_real;
                } else {
                    i86_logger("failed to create a CEU instance!");
                    i86_bus_destroy(&cpu->bus);
                    i86_alu_destroy(&cpu->alu);
                    free(cpu);
                }
            } else {
                i86_logger("failed to create a BUS instance!");
                i86_alu_destroy(&cpu->alu);
                free(cpu);
            }
        } else {
            i86_logger("failed to create an ALU instance!");
            free(cpu);
        }
    } else {
        i86_logger("failed to create a CPU instance!");
    }

    return cpu;
}

void
i86_cpu_destroy(i86_cpu_t cpu)
{
    if (cpu == NULL)
    {
        i86_logger("no CPU instance specified!");
    } else {
        i86_alu_destroy(&cpu->alu);
        i86_bus_destroy(&cpu->bus);
        i86_ceu_destroy(&cpu->ceu);
        free(cpu);
    }
}

i86_alu_t
i86_cpu_get_alu(i86_cpu_t cpu)
{
    i86_alu_t alu = NULL;

    if (cpu == NULL)
    {
        i86_logger("no CPU instance specified!");
    } else {
        alu = cpu->alu;
    }

    return alu;
}

i86_bus_t
i86_cpu_get_bus(i86_cpu_t cpu)
{
    i86_bus_t bus = NULL;

    if (cpu == NULL)
    {
        i86_logger("no CPU instance specified!");
    } else {
        bus = cpu->bus;
    }

    return bus;
}

i86_ceu_t
i86_cpu_get_ceu(i86_cpu_t cpu)
{
    i86_ceu_t ceu = NULL;

    if (cpu == NULL)
    {
        i86_logger("no CPU instance specified!");
    } else {
        ceu = cpu->ceu;
    }

    return ceu;
}

void
i86_cpu_set_mode(i86_cpu_t cpu, i86_mode_e mode)
{
    cpu->mode = mode;
}

i86_mode_e
i86_cpu_get_mode(i86_cpu_t cpu)
{
    return cpu->mode;
}

/* API used to display the current CPU values. */
void
i86_cpu_print_info(i86_cpu_t cpu)
{
    i86_logger("CPU info for 0x%.8x\n");
    i86_logger("Mode: %d\n\n", cpu->mode);

    i86_ceu_print_registers(cpu->ceu);
    i86_alu_print_registers(cpu->alu);
    i86_bus_print_registers(cpu->bus);
}
