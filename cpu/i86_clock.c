/*
 * i8086/i86_clock.c
 *
 *   Created on: Sep 19, 2016 11:12:52 PM
 *       Author: yan@artemis
 *
 *  Description:
 *    Reference:
 */

#include <stdlib.h>
#include "i86_logger.h"
#include "i86_clock.h"


typedef struct _i86_clock_t
{
    int a;
};

i86_clock_t
i86_clk_create(void)
{
    i86_clock_t clk = NULL;

    clk = (i86_clock_t) malloc(sizeof(struct _i86_clock_t));
    if(clk != NULL)
    {
        i86_logger("successfully allocated memory for CLK instance!");
    } else {
        i86_logger("failed to allocate memory for CLK instance!");
    }

    return clk;
}

void
i86_clk_destroy(i86_clock_t *clock)
{
    i86_clock_t clk = NULL;

    if(clock != NULL)
    {
        clk = *clock;
        if(clk != NULL)
        {
            free(clk);
            *clock = NULL;
        } else {
            i86_logger("invalid CLK instance!");
        }
    } else {
        i86_logger("invalid CLK container!");
    }
}

void
i86_clk_tick(i86_clock_t clock)
{
    // do tick
}
