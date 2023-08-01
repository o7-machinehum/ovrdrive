#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "ovrdrive.h"

// #define INHIBIT
#define DESTROY

#define DWELL_TIME_US 50
#define CHARGE_TIME_MS 125

void pump(int charge_time) {
    while(charge_time--) {
        PORT_CP |= (1 << PIN_CP);
        _delay_us(500);
        PORT_CP &= ~(1 << PIN_CP);
        _delay_us(500);
    }

    PORT_KILL |= (1 << PIN_KILL);
    _delay_us(DWELL_TIME_US);
    PORT_KILL &= ~(1 << PIN_KILL);
}

bool destroy_signal(void) {
    return true;
}

void destroy(void) {
    int n = 5;

    if(destroy_signal()) {
        while(n--) {
            pump(CHARGE_TIME_MS);
        }
    }
}

void inhibit(void) {
    if(destroy_signal()) {
        PORT_INHIBIT |= (1 << PIN_INHIBIT);
    }
}

int main(void) {
    DDR_CP       |=  (1 << PIN_CP);
    PORT_CP      &= ~(1 << PIN_CP);

    DDR_INHIBIT  |=  (1 << PIN_INHIBIT);
    PORT_INHIBIT &= ~(1 << PIN_INHIBIT);

    DDR_KILL     |=  (1 << PIN_KILL);
    PORT_KILL    &= ~(1 << PIN_KILL);

    DDR_LED      |=  (1 << PIN_LED);

#ifdef INHIBIT
    inhibit();
#endif

#ifdef DESTROY
    destroy();
#endif

    while(1)
    {
        PORT_LED |= (1 << PIN_LED);
        _delay_ms(1000);
        PORT_LED &= ~(1 << PIN_LED);
        _delay_ms(1000);

    }
}
