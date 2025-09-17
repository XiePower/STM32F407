#include "stm32f4xx.h"

/**
 * @brief 板集底层初始化
 * 打开时钟
 */

void board_lowlevel_init(void)
{
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);//中断优先级分组
/**
 * @brief Construct a new rcc ahb1periphclockcmd object
 * 
 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
}
