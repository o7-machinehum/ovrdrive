#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "ovrdrive.h"

void enable_flash(void) {
    PORT_IN1 |= (1 << PIN_IN1);
    PORT_IN2 &= ~(1 << PIN_IN2);
}

void destroy_flash(void) {
    _delay_ms(3000);
    PORT_LED |= (1 << PIN_LED);
    _delay_ms(5000);
    PORT_LED &= ~(1 << PIN_LED);

    // If the pin is high, someone
    // cut the trace, enabling the
    // destructing circuit.
    if((PORT_I_FSD & (1 << PIN_FSD)) && !SAFE) {
        while(true) {
            PORT_IN1 &= ~(1 << PIN_IN1);
            PORT_IN2 |= (1 << PIN_IN2);
            _delay_ms(10);
            PORT_IN1 |= (1 << PIN_IN1);
            PORT_IN2 &= ~(1 << PIN_IN2);
            _delay_ms(10);
        }
    }
}

void inhibit_flash(void) {
    PORT_INHIBIT |= (1 << PIN_INHIBIT);
}

void set_chg(char pin) {
    DDR_CHG  |=  (1 << pin);
    PORT_CHG |= (1 << pin);
}

bool check_chg(char pin) {
    if(PORT_I_CHG & (1 << pin))
        return true;
    return false;
}

int main(void) {
    DDR_IN1  |= (1 << PIN_IN1);
    DDR_IN2  |= (1 << PIN_IN2);

    DDR_FSD  &= ~(1 << PIN_FSD);
    PORT_FSD |= (1 << PIN_FSD); // Enable pullup

    DDR_INHIBIT  |=  (1 << PIN_INHIBIT);
    PORT_INHIBIT &= ~(1 << PIN_INHIBIT);

    DDR_LED      |=  (1 << PIN_LED);
    PORT_LED     &=  ~(1 << PIN_LED);

    DDR_CHG  &=  ~(1 << PIN_CHG1);
    DDR_CHG  &=  ~(1 << PIN_CHG2);

    enable_flash();

    bool enable = false;
    if(check_chg(PIN_CHG1)) {
        if(check_chg(PIN_CHG2)) {
            enable = true;
            PORT_LED |= (1 << PIN_LED);
        }
        else {
            set_chg(PIN_CHG2);
        }
    }
    else {
        set_chg(PIN_CHG1);
    }


    if(enable)
        enable_flash();
    else {
        inhibit_flash();
        destroy_flash();
    }

    while(true) {
        // Twiddle
    }
}
