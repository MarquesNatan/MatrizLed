#ifndef BOARD_PINOUT_H
#define BOARD_PINOUT_H

/*============================================================================*/
#define LED_HEARTBEAT_PORT              A
#define LED_HEARTBEAT_BIT               0
#define LED_HEARTBEAT_MASK              (1 << LED_HEARTBEAT_BIT)

#define LED_HEARTBEAT2_PORT              B 
#define LED_HEARTBEAT2_BIT              0
#define LED_HEARTBEAT2_MASK             (1 << LED_HEARTBEAT2_BIT)
/*============================================================================*/
                    /* Defines of pins SPI port*/
#define SPI_MOSI_PORT                   C
#define SPI_MOSI_BIT                    5
#define SPI_MOSI_MASK                   (1 << SPI_MOSI_BIT)

#define SPI_MISO_PORT                   C 
#define SPI_MISO_BIT                    4
#define SPI_MISO_MASK                   (1 << SPI_MISO_BIT)

#define SPI_CLOCK_PORT                  C
#define SPI_CLOCK_BIT                   3
#define SPI_CLOCK_MASK                  (1 << SPI_CLOCK_BIT)

#define SPI_SS_PORT                     A 
#define SPI_SS_BIT                      5
#define SPI_SS_MASK                     (1 << SPI_SS_BIT)

/*============================================================================*/
#define _74HC138_A_PORT                  B
#define _74HC138_A_BIT                   0
#define _74HC138_A_MASK                  (1 << _74HC138_A_BIT)

#define _74HC138_B_PORT                  B
#define _74HC138_B_BIT                   1
#define _74HC138_B_MASK                  (1 << _74HC138_B_BIT)

#define _74HC138_C_PORT                  B
#define _74HC138_C_BIT                   2
#define _74HC138_C_MASK                  (1 << _74HC138_C_BIT)

#define _74HC138_G1_PORT                 B
#define _74HC138_G1_BIT                  3
#define _74HC138_G1_MASK                 (1 << _74HC138_G1_BIT)

/*============================================================================*/

#endif