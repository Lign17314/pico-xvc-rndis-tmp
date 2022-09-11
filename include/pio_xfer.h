#ifndef __PIO_XFER_H__
#define __PIO_XFER_H__

#include <stdlib.h>
#include <stdio.h>

#include "pico/stdlib.h"
#include "tdata.pio.h"
#include "tms.pio.h"

#define PIN_SCK 0 // output
#define PIN_TDI 1 // output
#define PIN_TDO 2 // input
#define PIN_TMS 4 // output
#define PIO_CLKDIV 50
typedef struct pio_xfer_inst
{
    PIO pio;
    uint sm_data;
    uint sm_tms;
    uint tck_pin;
    uint tms_pin;
    uint tdi_pin;
    uint tdo_pin;
} pio_xfer_inst_t;

int pio_xfer_rw(uint32_t *tx_data, uint32_t *tx_tms, uint32_t *tdi, int nbits);
int pio_xfer_init(void);
#define USE_PIO
void gpio_xfer_init(void);
uint8_t *gpio_xfer(int len, uint8_t *buffer);
#endif