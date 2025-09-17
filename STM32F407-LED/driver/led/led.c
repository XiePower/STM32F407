#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx.h"
#include "led.h"
/** static修饰只是防止在同一文件中互相污染，
 * 文件间调用不能用static修饰
 * const:保护变量，只读不改
*/

/**
 * 用于定义固定宽度的整数类型。
 * 它的主要目的是增强程序在不同平台间的可移植性
 * 确保整数类型的大小不会因编译器或硬件架构的不同而变化
 * eg.uint8_t
 */
// #include "stdint.h"

/**
 * 提供了一组用于处理字符串和内存块的函数。
 * 这些函数涵盖了字符串复制、连接、比较、搜索和内存操作等
 */
// #include "string.h"

/**
 * 支持 bool 数据类型
 */
// #include "stdbool.h"

void led_init(const led_desc_t *desc) 
{
    RCC_AHB1PeriphClockCmd(desc->clk_source, ENABLE);

    GPIO_InitTypeDef g_init;
    memset(&g_init, 0, sizeof(GPIO_InitTypeDef)); // 初始化默认值为0

    g_init.GPIO_Pin = desc->pin;
    g_init.GPIO_Mode = GPIO_Mode_OUT;
    g_init.GPIO_OType = GPIO_OType_PP;
    g_init.GPIO_Speed = GPIO_Medium_Speed;

    GPIO_Init(desc->port, &g_init);

    GPIO_WriteBit(desc->port, desc->pin, desc->lvl_off);
}

void led_deinit(const led_desc_t *desc)
{
    GPIO_WriteBit(desc->port, desc->pin, desc->lvl_off);
}

void led_on(const led_desc_t *desc)
{
    GPIO_WriteBit(desc->port, desc->pin, desc->lvl_on);
}

void led_off(const led_desc_t *desc)
{
    GPIO_WriteBit(desc->port, desc->pin, desc->lvl_off);
}
