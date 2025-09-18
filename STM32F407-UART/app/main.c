#include <stdbool.h>// Include stdbool.h for bool type
#include <stdint.h>// Include stdint.h for uint8_t and other types
#include <string.h>// Include string.h for memset
#include "console_uart.h"
#include "shell.h"
#include "ringbuffer8.h"
#include "main.h"

/**
 * 全局变量在开机的时候初始值会初始化为0
 * 局部变量在开机的时候初始值不确定，需要手动初始化
 * 初始化方法：string.h中的memset函数
 */

/**
 * 需要将HSE_VALUE修改为8000000，否则时钟频率会错乱
 * 这一步很重要
 * HSE_VALUE为内部时钟频率
 */

static uint8_t rx_buff[128];   // 申请一个128字节的缓冲区
static ringbuffer8_t rxrb;	   // 创建一个环形缓冲区
static Shell shell;			   // 定义一个shell对象
static char shell_buffer[512]; // 申请一片缓存

extern void board_lowlevel_init(void); // 打开时钟

/**
 * @brief 串口接收数据处理函数
 *
 */
static void uart_rx_handler(uint8_t data) // 把接收到的数据存入其中
{
	if (!rb8_full(rxrb)) // 检查环形缓冲区是否已满
	{
		rb8_put(rxrb, data); // 将接收到的数据放入环形缓冲区
	}
}

// static signed short _shell_read(char *data, unsigned short len) //读取函数
//{
//
// }
//  读取函数不需要实现，因为我们使用的是串口中断接收数据
//  读取函数可以直接从环形缓冲区中获取数据

static signed short _shell_write(char *data, unsigned short len) // 写入函数
{
	for (unsigned short i = 0; i < len; i++) // 遍历数据
	{
		uart_send((uint8_t)data[i]); // 发送数据到串口
	}
	return len; // 返回写入的长度
}

int main(void)
{

	mem_init(); // 初始化系统内存
	/*开启时钟*/
	board_lowlevel_init();						  // 没有现象的原因：把这句初始化放在了后面
	uart_init();								  // 初始化串口
	uart_recv_callback_register(uart_rx_handler); // 注册串口接收回调函数

	rxrb = rb8_new(rx_buff, sizeof(rx_buff)); // 创建一个环形缓冲区

	// 函数注册
	shell.write = _shell_write;
	shellInit(&shell, shell_buffer, sizeof(shell_buffer)); // 初始化shell

	uint8_t rxdata; // 定义一个接收数据的变量
	while (1)
	{
		if (!rb8_empty(rxrb)) // 检查环形缓冲区是否为空
		{
			rb8_get(rxrb, &rxdata);		  // 从环形缓冲区中获取数据
			shellHandler(&shell, rxdata); // 处理接收到的数据
		}
	}
}
