#include "driver_init.h"
#include <peripheral_clk_config.h>
#include <utils.h>
#include <hal_init.h>
#include <hpl_gclk_base.h>
#include <hpl_pm_base.h>

struct usart_sync_descriptor USART_0;

void USART_0_PORT_init(void) {
	gpio_set_pin_function(PB22, PINMUX_PB22D_SERCOM5_PAD2); /* TX */
	gpio_set_pin_function(PB23, PINMUX_PB23D_SERCOM5_PAD3); /* RX */
}

void USART_0_CLOCK_init(void) {
	_pm_enable_bus_clock(PM_BUS_APBC, SERCOM5); // gave the did you mean and points back to this
	_gclk_enable_channel(SERCOM5_GCLK_ID_CORE, CONF_GCLK_SERCOM5_CORE_SRC);
}

void USART_0_init(void) {
	USART_0_CLOCK_init();
        // this hangs:
	usart_sync_init(&USART_0, SERCOM5, (void *)NULL); // hangs here except for init_mcu() path
	// USART_0_PORT_init();
}

void system_init(void)
{
	init_mcu();
	gpio_set_pin_direction(PA16, GPIO_DIRECTION_OUT);
	gpio_set_pin_level(PA16, false);
	gpio_set_pin_function(PA16, GPIO_PIN_FUNCTION_OFF); // aha what's this
	gpio_set_pin_direction(PA17, GPIO_DIRECTION_OUT);
	gpio_set_pin_level(PA17, false);
	gpio_set_pin_function(PA17, GPIO_PIN_FUNCTION_OFF); // aha what's this
	USART_0_init();
}
