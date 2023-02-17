#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    _delay_ms(5000);
    DDRA  |=  (1 << PA0); // Charge Pump
    DDRA  |=  (1 << PA2); // Inhibit Signal
    DDRA  |=  (1 << PA3); // Kill signal
    PORTA &= ~ (1 << PA3);

    DDRA  |=  (1 << PA7); // LED
    PORTA &= ~(1 << PA2);

    PORTA |= (1 << PA7);

    uint16_t timer = 5000;
    // PORTA |= (1 << PA3);
    while(1) {};

    while(1)
    {
        PORTA |= (1 << PA0);
        _delay_ms(1);
        PORTA &= ~(1 << PA0);
        _delay_ms(1);
        timer--;

        // if(!timer) {
        //     PORTA |= (1 << PA3);
        //     timer = 5000;
        //     _delay_ms(1000);
        //     PORTA &= ~(1 << PA3);
        // }
    }
}
