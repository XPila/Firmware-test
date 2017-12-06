// Software SPI
#ifndef SWSPI_H
#define SWSPI_H

#include <inttypes.h>
#include "config.h"


//initialize gpio
extern void swspi_init(void);
//transmit and receive (full duplex mode)
extern unsigned char swspi_txrx(unsigned char tx);
//transmit (half dublex mode, miso == mosi)
extern void swspi_tx(unsigned char tx);
//receive (half dublex mode, miso == mosi)
extern unsigned char swspi_rx(void);


#endif //SWSPI_H
