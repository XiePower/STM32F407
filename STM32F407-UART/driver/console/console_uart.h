#ifndef __CONSOLE_UART_H
#define __CONSOLE_UART_H

#include <stdint.h> //若uint8_t没有被定义，则添加这个头文件

typedef void (*uart_rx_callback_t)(uint8_t data); // 申明一个函数的typedef

void uart_init(void);
void uart_send(uint8_t data);
void uart_recv_callback_register(uart_rx_callback_t cb);// 注册接收回调函数

#endif /* __CONSOLE_UART_H*/
