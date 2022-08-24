#include <avr/io.h>
#include <util/delay.h>

// PWM PA6
// ADC PA1
// LED PA2

const float R2 = 747e3; // R2 in schematic
const float Rth = 1e6;  // If r > 1Mohm, finger not wet.

void init_pwm() {
   DDRA |= (1 << PA6);                    // PA6 as output
   OCR1A = 0x0000;                        // set PWM for 50% duty cycle at 10bit
   TCCR1A |= (1 << COM1A1);               // set non-inverting mode
   TCCR1A |= (1 << WGM11) | (1 << WGM10); // set 10bit phase corrected PWM Mode
   TCCR1B |= (1 << CS11);                 // set prescaler to 8 and starts PWM
}

void set_pwm(float voltage) {
   OCR1A = ( voltage / 5 )* 0x400;
}

void init_adc() {
    ADMUX &= ~(1 << REFS0); // Use 5V as reference
    ADMUX &= ~(1 << REFS1);
    ADMUX |= (1 << MUX0);   // Use ADC1 (PA1)
    ADCSRB |= (1 << ADLAR); // Left adjusted (8bit) operation alright

    ADCSRA |= (1 << ADEN);  // Enable ADC

}

float read_adc() {
    float voltage;
    ADCSRA |= (1 << ADSC);
    while(ADCSRA & (1 << ADSC)) {};
    voltage = ADCH;
    voltage = voltage * 5 / 0xff;
    return voltage;
}

int main(void) {
	DDRA = 1 << PA2; // LED

    init_pwm();
    init_adc();

	while(1)
	{
        float v, r = 0;

        v = read_adc();
        set_pwm(v);
        r = v * (R2/2.5);

		(r > Rth) ? (PORTA &= ~(1 << PA2)) : (PORTA |= 1 << PA2);
	}
}
