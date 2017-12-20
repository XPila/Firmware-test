//swspi.h - software SPI
#ifndef SWSPI_H
#define SWSPI_H

#include <inttypes.h>
#include "config.h"


#if defined(__cplusplus)
extern "C" {
#endif //defined(__cplusplus)


//initialize pins
extern void swspi_ini(void);

//transmit (half dublex mode, miso == mosi)
extern void swspi_tx(uint8_t tx);

//receive (half dublex mode, miso == mosi)
extern uint8_t swspi_rx(void);

#if (SWSPI_MISO != SWSPI_MOSI)
//transmit and receive (full duplex mode)
extern uint8_t swspi_txrx(uint8_t tx);
#endif //(SWSPI_MISO == SWSPI_MOSI)


#if defined(__cplusplus)
}
#endif //defined(__cplusplus)
#endif //SWSPI_H
