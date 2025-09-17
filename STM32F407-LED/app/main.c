 #include <stdbool.h>
 #include <stdint.h>
 #include <string.h>
 #include "main.h"

 int main(void)
 {
	led_init(&LED0);
	led_init(&LED1);
	led_init(&LED2);

	while(1)
	{
		led_on(&LED0);
		led_on(&LED1);
		led_on(&LED2);
		delay();

		led_off(&LED0);
		led_off(&LED1);
		led_off(&LED2);
		delay();
	}
 }
 