
#include "board.h"

const led_desc_t LED0 =

    {
        .clk_source = RCC_AHB1Periph_GPIOE,
        .port = GPIOE,
        .pin = GPIO_Pin_5,
        .lvl_on = Bit_RESET,
        .lvl_off = Bit_SET,

};

const led_desc_t LED1 =

    {
        .clk_source = RCC_AHB1Periph_GPIOE,
        .port = GPIOE,
        .pin = GPIO_Pin_6,
        .lvl_on = Bit_RESET,
        .lvl_off = Bit_SET,

};

const led_desc_t LED2 =

    {
        .clk_source = RCC_AHB1Periph_GPIOC,
        .port = GPIOC,
        .pin = GPIO_Pin_13,
        .lvl_on = Bit_RESET,
        .lvl_off = Bit_SET,

};
