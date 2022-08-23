#include <avr/io.h>
#include <util/delay.h>

void init_pwm() {
   DDRA |= (1 << DDA6);                   // PB1 as output
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
	DDRA = 1 << DDA0;
	DDRA = 1 << DDA2;

    init_pwm();
    init_adc();
	
	while(1)
	{
        set_pwm(read_adc());
		PORTA = 1 << PA2;
		_delay_ms(1000);
		PORTA = ~(1 << PA2);
		_delay_ms(1000);
	}
}
