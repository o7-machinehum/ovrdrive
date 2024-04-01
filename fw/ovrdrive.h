/* Production Variables */
#define SAFE false // Don't ARM FSD cct. ?

/* IN1 / IN2 DRV8837C */
#define PIN_IN1 PA0
#define DDR_IN1 DDRA
#define PORT_IN1 PORTA
#define PIN_IN2 PA1
#define DDR_IN2 DDRA
#define PORT_IN2 PORTA

/* Flash Inhibit Signal */
#define PIN_INHIBIT PA2
#define DDR_INHIBIT DDRA
#define PORT_INHIBIT PORTA

/* LED */
#define PIN_LED PA7
#define DDR_LED DDRA
#define PORT_LED PORTA

/* Charge Pins*/
#define PIN_CHG1 PB0
#define PIN_CHG2 PB1
#define DDR_CHG DDRB
#define PORT_CHG PORTB
#define PORT_I_CHG PINB

/* Full Self Destruct Select */
#define PIN_FSD PA3
#define DDR_FSD DDRA
#define PORT_FSD PORTA
#define PORT_I_FSD PINA
