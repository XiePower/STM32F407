#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx.h"
#include "console_uart.h"

static uart_rx_callback_t rx_callback;// 定义一个全局变量，用于存储接收回调函数的指针

/**
 * @brief 初始化UART复用引脚功能
 * 
 */

static void uart_pin_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	memset(&GPIO_InitStructure, 0, sizeof(GPIO_InitTypeDef)); // 初始化局部变量

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; // AF复用模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); // Changes the mapping（映射） of the specified（指定） pin
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
}

/**
 * @brief 串口配置
 * 
 */
static void uart_lowlevel_init(void)
{
	USART_InitTypeDef USART_InitStructure;
	memset(&USART_InitStructure, 0, sizeof(USART_InitTypeDef));

	USART_InitStructure.USART_BaudRate = 115200;									// 波特率
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 硬件控制流
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_Parity = USART_Parity_No;			// 奇偶校验
	USART_InitStructure.USART_StopBits = USART_StopBits_1;		// 停止位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b; // 数据位
	USART_Init(USART1, &USART_InitStructure);

	USART_Cmd(USART1, ENABLE);
}

/**
 * @brief 串口中断配置
 * 
 */

static void uart_irq_init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	memset(&NVIC_InitStructure, 0, sizeof(NVIC_InitTypeDef));

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 主优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  // 从优先级
	NVIC_Init(&NVIC_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
}

void uart_init(void)
{
	uart_pin_init(); // 初始化UART引脚
	uart_lowlevel_init(); // 初始化UART
	uart_irq_init(); // 初始化UART中断
}

void uart_send(uint8_t data)
{
	USART_SendData(USART1, data);// 发送数据到USART1
	// 等待发送完成
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
}

void uart_recv_callback_register(uart_rx_callback_t cb)// 注册接收回调函数
{
	rx_callback = cb;// 将回调函数指针赋值给全局变量
}

void USART1_IRQHandler(void)//不能被修饰为static，否则不能被其他文件调用，一开始函数拼写错误
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)// 检查接收中断是否发生
	{
		uint8_t data = USART_ReceiveData(USART1);//uint8_t data从USART1读取数据
		if (rx_callback)// 检查回调函数是否已注册
			rx_callback(data);// 调用回调函数处理接收到的数据
		// 清除中断标志位
		USART_ClearITPendingBit(USART1, USART_IT_RXNE); // 清除中断标志位，避免重复进入中断
	}
}
