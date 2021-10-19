#include "stdint.h"
#include <stddef.h>

struct rs485_port {
    uint16_t rxPin;
    uint16_t txPin;
    /**
     * Will be high when transmitting data and low when receiving data
     */
    uint16_t directionPin;
    int uartNumber;
};

/**
 * Initialize an rs485 port
 * This method must be called before the port can be used
 * @param port The port to initialize
 * @param baudRate The communication speed that will be used
 */
void rs485_begin(struct rs485_port port, int baudRate);

/**
 * Write data to an rs485 port
 * @param port The port to send data through
 * @param data A pointer to the beginning of the data to transmit
 * @param length The number of bytes to transmit
 */
void rs485_write(struct rs485_port port, void* data, size_t length);

/**
 * Check if there is any data available to read from an rs485 port
 * @param port The port to check
 * @return The number of bytes available to read
 */
int rs485_available(struct rs485_port port);

/**
 * Read a single byte from an rs485 port
 * @param port The port to read from
 * @return The next byte in the port buffer
 */
uint8_t rs485_read_byte(struct rs485_port port);