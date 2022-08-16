#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRA = 1<<PA0;
	
	while(1)
	{
		PORTA = 1 << PA0;
		_delay_ms(1000);
		PORTA = ~(1 << PA0);
		_delay_ms(1000);
	}
}
