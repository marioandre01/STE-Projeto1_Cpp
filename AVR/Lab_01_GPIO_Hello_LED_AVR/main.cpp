#include<avr/io.h>

int main(void) {

	//Low = 0; High = 1
	//INPUT = 0; OUTPUT = 1

	//setup - configuração dos pinos

	//--pino 8-- DDH5 pino 8 da placa
	//pino 8 como saída
	DDRH |= (1 << DDH5); // faz um OR no bit 5 de DDRH para virar 1

	//pino 8 definido como LOW
	PORTH &= ~(1 << PH5);

	//--pino 9-- DDH6 pino 9 da placa
	//pino 9 como saída
	DDRH |= (1 << DDH6); // faz um OR no bit 6 de DDRH para virar 1

	//pino 9 definido como LOW
	PORTH &= ~(1 << PH6);

	//--pino 2-- DDE4 pino 2 da placa
	//pino 2 como entrada
	DDRE &= ~(1 << DDE4);

	//--pino 3-- DDE5 pino 3 da placa
	//pino 3 como entrada
	DDRE &= ~(1 << DDE5);

	//Loop
	while (1) {

		if (PINE & (1 << PINE4)) { //lê pino 2
			PORTH |= 1 << PH5; //Define pino 8 como HIGH, liga o led
		} else {
			PORTH &= ~(1 << PH5); //Define pino 8 como LOW, desliga o led
		}

		if (PINE & (1 << PINE5)) { //lê pino 3
			PORTH |= 1 << PH6; //Define pino 9 como HIGH, liga o led
		} else {
			PORTH &= ~(1 << PH6); //Define pino 9 como LOW, desliga o led
		}

	}
	return 0;
}
