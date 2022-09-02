/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdlib.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "tdata.pio.h"

// This program instantiates a PIO SPI with each of the four possible
// CPOL/CPHA combinations, with the serial input and output pin mapped to the
// same GPIO. Any data written into the state machine's TX FIFO should then be
// serialised, deserialised, and reappear in the state machine's RX FIFO.

#define PIN_SCK 18 // output
#define PIN_TDI 16 // output
#define PIN_TDO 16 // input

void pio_tms_set_period(PIO pio, uint sm, uint32_t num)
{
    pio_sm_set_enabled(pio, sm, false);
    pio_sm_put_blocking(pio, sm, (num % 32 == 0 ? 0 : (32 - num % 32)) << 16 | (num - 1));
    pio_sm_exec(pio, sm, pio_encode_pull(false, false));
    pio_sm_exec(pio, sm, pio_encode_out(pio_x, 16));
    pio_sm_exec(pio, sm, pio_encode_out(pio_y, 16));
    pio_sm_set_enabled(pio, sm, true);
}
void write_read_nbits(PIO pio, uint sm, uint32_t *tx, uint32_t *rx, uint16_t nbits)
{
    pio_tms_set_period(pio, sm, nbits);
    int i;
    for (i = 0; i < (nbits + 31) / 32; i++)
    {
        pio_sm_put_blocking(pio, sm, *(tx + i));
        *(rx + i) = pio_sm_get_blocking(pio, sm);
    }
}
int main()
{
    stdio_init_all();

    // float clkdiv = 31.25f; // 1 MHz @ 125 clk_sys
    float clkdiv = 5; // 1 MHz @ 125 clk_sys
    uint cpha0_prog_offs = pio_add_program(pio0, &tdata_program);
    int cpha = 0, cpol = 0;
    printf("CPHA = %d, CPOL = %d\n", cpha, cpol);
    pio_tdata_init(pio0, 0, cpha0_prog_offs, clkdiv, PIN_SCK, PIN_TDI, PIN_TDO);

    while (1)
    {

        uint32_t data[16] = {0};
        for (int i = 0; i < 16; i++)
        {
            data[i] = rand();
        }
        /*
        pio_tms_set_period(spi.pio, spi.sm, 20);

        pio_sm_put_blocking(spi.pio, spi.sm, data_t);
        uint32_t data = pio_sm_get_blocking(spi.pio, spi.sm);*/
        write_read_nbits(pio0, 0, data + 0, data + 2, 50);
        for (int i = 0; i < 4; i++)
        {
            printf("%08x ", data[i]);
        }

        printf("\n");

        sleep_ms(1000);
    }
}
