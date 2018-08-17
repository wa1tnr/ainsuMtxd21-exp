#include <atmel_start.h>
#include "pins.h"

int main(void)
{
	/* Initializes MCU, drivers and middleware */
        pins_setup();

	/* Replace with your application code */
	while (1) {
            toggle_d11();
	}
}
