#include <avr/io.h>
#include <util/delay.h>
#include "ledblink.h"
#include "iessreg.h"

// Define constants for the LEDs
#define LED_YELLOW (1 << SR_LED_YELLOW)
#define LED_GREEN  (1 << SR_LED_GREEN)
#define LED_BLUE   (1 << SR_LED_BLUE)


void led_blink(srr_t *regmdl) {
    const int delay_ms = 143; // Each LED lights up for 143 ms

    // Forward direction
    for (int i = 0; i < 3; i++) {
        *regmdl = 1 << i;  // Turn on only the ith LED
        update_hardware(regmdl);
        _delay_ms(delay_ms);
    }

    // Backward direction, skipping the first and last LEDs as they are already handled
    for (int i = 3 - 2; i > 0; i--) {
        *regmdl = 1 << i;
        update_hardware(regmdl);
        _delay_ms(delay_ms);
    }

    // Clear LEDs at the end of the cycle
    clear(regmdl);
}
