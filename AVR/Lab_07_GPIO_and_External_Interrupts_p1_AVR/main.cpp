#include<avr/io.h>
#include <avr/interrupt.h>

int estado_led = 0;
int debounce_limit = 200;
int ultimo_tempo_interup = 0;
int now = 0;

volatile uint64_t millis_prv = 0;

void millis_init()
{
 TCCR0A = 0;
 // set timer0 with CLKio/8 prescaler
 TCCR0B = _BV(CS01) | _BV(CS00);
 // clear any TOV1 Flag set when the timer overflowed
 TIFR0 &= ~TOV0;
 // set timer0 counter initial value to 0
 TCNT0 = 0x0;
 // enable timer overflow interrupt for Timer0
 TIMSK0 = _BV(TOIE0);
 // clear the Power Reduction Timer/Counter0
 PRR0 &= ~PRTIM0;
}

// TIMER0 interrupt handler
ISR(TIMER0_OVF_vect){
 // reset the counter (overflow is cleared automatically)
 TCNT0 = (uint8_t)(0xFF - ((F_CPU/8)/1000)); // use CLKio/8 prescaler (set CS0n accordingly above)
 millis_prv++;
}

// return elapsed time in milliseconds
uint64_t millis(){
 return millis_prv;
}


void valor_led(int est_led){

	if (est_led == 1) {
		PORTH |= (1 << PH6);
	} else {
		PORTH &= ~(1 << PH6);
	}
}

int debounce() {

	now = millis();
	if ((now - ultimo_tempo_interup) > debounce_limit) {
		ultimo_tempo_interup = now;
		return 1;
	} else {
		return 0;
	}
}

//Interrupção pino 3
ISR(INT5_vect) {
	if (debounce()) {
		estado_led = !estado_led;
	}
}

int main(void) {

	cli(); //desativa interrupção global

	millis_init(); //inicia função miliis()

	//setup - configuração dos pinos
	DDRH |= (1 << DDH6); //pino 9 como saída
	PORTH &= ~(1 << PH6); //pino 9 definido como LOW

	DDRE &= ~(1 << DDE5); //pino 3 como entrada

	EICRB |= (0 << ISC50) | (0 << ISC51);	// Interromper no nivel baixo
	//EICRB = 0;
	EIMSK |= (1 << INT5);	// habilita interrupção INT5 pino 3

	sei(); //ativa interrupção global

	//Loop
	while (1) {
		valor_led(estado_led);
	}
	return 0;
}
