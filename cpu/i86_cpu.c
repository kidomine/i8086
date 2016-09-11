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
#include "i86_register.h"
#include "i86_logger.h"
#include "i86_alu.h"
#include "i86_bus.h"
#include "i86_ceu.h"


/* Definition of a CPU type. */
typedef struct _i86_cpu_t
{
    i86_mode_e mode;

    i86_ceu_t *ceu;
    i86_alu_t *alu;
    i86_bus_t *bus;
};


/* CPU constructor/destructor */
i86_cpu_t
i86_cpu_create(void)
{
    i86_cpu_t cpu = NULL;

    cpu = malloc(sizeof(i86_cpu_t));
    if (cpu != NULL)
    {
        memset(cpu, 0x00, sizeof(i86_cpu_t));

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
        i86_ceu_destroy(&cpu->bus);
        free(cpu);
    }
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

/* Helper API. */
static void
i86_cpu_print_register(void *id, i86_register16_t *reg)
{
    char buff[I86_LOG_MSG_BUFF_LEN];

    memset(buff, 0x00, I86_LOG_MSG_BUFF_LEN);
    snprintf(buff,
             I86_LOG_MSG_BUFF_LEN,
             "%s : 0x%.4x (l: 0x%.2, h: 0x%.2)\n",
             id,
             reg->reg.reg16,
             reg->reg.reg8.reg_l,
             reg->reg.reg8.reg_h
             );

    i86_logger(buff);
}

void
i86_cpu_print_info(i86_cpu_t cpu)
{
    i86_logger("CPU info for 0x%.8x\n");
    i86_logger("Mode: %d\n\n", cpu->mode);

    i86_logger("Main registers:\n");
    i86_cpu_print_register("    ax", &cpu->ax);
    i86_cpu_print_register("    bx", &cpu->bx);
    i86_cpu_print_register("    cx", &cpu->cx);
    i86_cpu_print_register("    dx", &cpu->dx);

    i86_logger("Index registers:\n");
    i86_logger("    si: 0x.8x\n", cpu->si);
    i86_logger("    di: 0x.8x\n", cpu->di);
    i86_logger("    bp: 0x.8x\n", cpu->bp);
    i86_logger("    sp: 0x.8x\n", cpu->sp);

    i86_logger("Segment registers:\n");
    i86_logger("    cs: 0x.8x\n", cpu->si);
    i86_logger("    ds: 0x.8x\n", cpu->ds);
    i86_logger("    es: 0x.8x\n", cpu->es);
    i86_logger("    ss: 0x.8x\n", cpu->ss);

    i86_logger("Program counter: 0x.8x\n", cpu->ip);
    i86_logger("Status register: 0x.8x\n\n", cpu->sf);
}
