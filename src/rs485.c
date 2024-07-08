#include "rs485.h"
#include "mgos.h"

bool rs485_begin(struct rs485_port port, int baudRate, int dataBits, int stopBits, enum Parity parity) {
    mgos_gpio_set_mode(port.directionPin, MGOS_GPIO_MODE_OUTPUT);

    struct mgos_uart_config ucfg;
    mgos_uart_config_set_defaults(port.uartNumber, &ucfg);
    
    ucfg.baud_rate = baudRate;
    ucfg.dev.rx_gpio = port.rxPin;
    ucfg.dev.tx_gpio = port.txPin;
    ucfg.num_data_bits = dataBits;
    ucfg.stop_bits = stopBits;
    ucfg.parity = parity;

    bool initSuccess = mgos_uart_configure(port.uartNumber, &ucfg);

    mgos_uart_set_rx_enabled(port.uartNumber, true);

    return initSuccess;
}

void begin_transmission(struct rs485_port port) {
    mgos_gpio_write(port.directionPin, true);
    mgos_msleep(1);
}

void end_transmission(struct rs485_port port) {
    mgos_msleep(1);
    mgos_gpio_write(port.directionPin, false);
}

void rs485_write(struct rs485_port port, void* data, size_t length) {
    begin_transmission(port);
    mgos_uart_write(port.uartNumber, data, length);
    mgos_uart_flush(port.uartNumber);
    end_transmission(port);
}

int rs485_available(struct rs485_port port) {
    return mgos_uart_read_avail(port.uartNumber);
}

uint8_t rs485_read_byte(struct rs485_port port) {
    uint8_t byte = 0;
    mgos_uart_read(port.uartNumber, &byte, 1);
    return byte;
}

void rs485_clear_buffer(struct rs485_port port) {
    char buffer[mgos_uart_read_avail(port.uartNumber)];
    mgos_uart_read(port.uartNumber, buffer, mgos_uart_read_avail(port.uartNumber));
}

bool mgos_rs485_init(void) {
    return true;
}