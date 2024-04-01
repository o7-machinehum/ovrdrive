#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include "ovrdrive.h"

void enable_flash(void) {
    PORT_IN1 |= (1 << PIN_IN1);
    PORT_IN2 &= ~(1 << PIN_IN2);
    PORT_INHIBIT &= ~(1 << PIN_INHIBIT);
}

void destroy_flash(void) {
    PORT_IN1 &= ~(1 << PIN_IN1);
    PORT_IN2 |= (1 << PIN_IN2);
}

void inhibit_flash(void) {
    PORT_INHIBIT |= (1 << PIN_INHIBIT);
}

void set_chg(char pin) {
    DDR_CHG  |=  (1 << pin);
    PORT_CHG |= (1 << pin);
}

void clr_chg(void) {
    DDR_CHG  |=  ~(1 << PIN_CHG1);
    DDR_CHG  |=  ~(1 << PIN_CHG2);
    PORT_CHG &= ~(1 << PIN_CHG1);
    PORT_CHG &= ~(1 << PIN_CHG2);
}

bool check_chg(char pin) {
    if(PORT_I_CHG & (1 << pin)) {
        return true;
    }
    return false;
}

int main(void) {
    bool enable = false;
    uint8_t flash = 10;

    DDR_IN1  |= (1 << PIN_IN1);
    DDR_IN2  |= (1 << PIN_IN2);

    DDR_FSD  &= ~(1 << PIN_FSD);
    PORT_FSD |= (1 << PIN_FSD); // Enable pullup

    DDR_INHIBIT  |=  (1 << PIN_INHIBIT);
    PORT_INHIBIT &= ~(1 << PIN_INHIBIT);

    enable_flash();

    DDR_LED      |=  (1 << PIN_LED);
    PORT_LED     &=  ~(1 << PIN_LED);

    DDR_CHG  &=  ~(1 << PIN_CHG1);
    DDR_CHG  &=  ~(1 << PIN_CHG2);

    if(check_chg(PIN_CHG1)) {
        if(check_chg(PIN_CHG2)) {
            // We have plugged in two times rapidly
            enable = true;
        }
        else {
            set_chg(PIN_CHG2);
        }
    }
    else {
        set_chg(PIN_CHG1);
    }

    // Solid LED indicates normal operation
    if(enable) {
        PORT_LED |= (1 << PIN_LED);
        enable_flash();
    }
    else {
        PORT_LED &= ~(1 << PIN_LED);
        inhibit_flash();

        if((PORT_I_FSD & (1 << PIN_FSD)) && !SAFE) {
            while(flash--) {
                _delay_ms(100);
                PORT_LED |= (1 << PIN_LED);
                _delay_ms(100);
                PORT_LED &= ~(1 << PIN_LED);
            }

            destroy_flash();
        }
    }
    
    while(true) {
        _delay_ms(5000);
        clr_chg();
    }
}
