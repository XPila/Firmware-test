AVR atmega2560 kernel for EINSY 3D printer board


MODULES:

config: main configuration file
 lang: C
 source: config.h

timer: 1ms timer driver
 lang: C
 source: config.h

io_atmega2560 - minimalistic direct i/o pin access for mega2560
 lang: C
 source: io_atmega2560.h

rbuf8 - optimized byte-roudbuffer with 8bit pointer
 lang: C
 source: rbuf8.h, rbuf8.c

uart - uart0 and uart1 driver
 lang: C
 source: uart.h, uart.c
 dependency: config.h, io_atmega2560.h

lcd - alfanumeric 20x4 display driver
 lang: C, ASM
 source: lcd.h, lcd.c
 dependency: config.h, io_atmega2560.h

spi - spi driver
 lang: C
 source: spi.h, spi.c

i2c - i2c driver
 lang: C
 source: i2c.h, i2c.c

tmc2130 - tmc2130 quad axis driver
 lang: C
 source: tmc2130.h, tmc2130.c
 dependency: spi.h

pat9125 - pat9125 laser motion sensor driver
 lang: C
 source: pat9125.h, pat9125.c
 dependency: i2c.h

main - main interface, initialization and startup
 lang: C
 source: main.h, main.c
 dependency: config.h, io_atmega2560.h, uart.h, lcd.h,
             spi.h, i2c.h, tmc2130.h, pat9125.h

test - test application
 lang: C++
 source: test.cpp
 dependency: main.h


RAM USAGE:

uart0 rx-buffer     256 bytes
uart0 tx-buffer      32 bytes
uart0 file           16 bytes
uart0 variables       ? bytes

uart1 rx-buffer     256 bytes
uart1 tx-buffer      32 bytes
uart1 file           16 bytes
uart1 variables       ? bytes

lcd input buffer     16 bytes
lcd output buffer   112 bytes
lcd variables         ? bytes

spi variables         ? bytes

i2c variables         ? bytes

tmc2130 variables     ? bytes


FLASH USAGE:
0x00000 .. 0x000c0    - Interrupt vectors
0x000c0 .. 