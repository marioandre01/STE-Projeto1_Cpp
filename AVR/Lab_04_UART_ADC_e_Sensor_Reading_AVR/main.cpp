#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

#define Fosc 16000000 // Clock Speed
#define BaudRate 9600
#define ValorUBRR (((Fosc/(BaudRate*16UL)))-1) //igual a 103 = 00000000 01100111

const int analogInPin = 0;
int valorPino = 0;
float voltagem;
int valRMS = 0;
int vPwm = 0;

void USART0Init(void) {
// Set baud rate
	UBRR0H = (uint8_t) (ValorUBRR >> 8); //00000000 01100111 = 00000000 00000000 = 00000000
	UBRR0L = (uint8_t) ValorUBRR; //01100111

// Set frame format to 8 data bits, no parity, 1 stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);

//enable transmission and reception
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
}

void USART0SendByte(uint8_t u8Data) {
//wait while previous byte is completed
	while (!(UCSR0A & (1 << UDRE0))) { //enquanto o bit UDRE0 no registrador UCSR0A for 0, ainda ha byte no buffer

	};
// Transmit data
	UDR0 = u8Data;
}

uint8_t USART0ReceiveByte() {
// Wait for byte to be received
	while (!(UCSR0A & (1 << RXC0))) { //enquanto o bit RXC0 no registrador UCSR0A for 0, ainda ha byte no buffer sendo recebido

	};
// Return received data
	return UDR0;
}

void InitADC() {
	// Select Vref=AVcc=5v
	ADMUX |= (1 << REFS0);

	//set prescaller to 128 and enable ADC
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}

uint16_t ReadADC(uint8_t ADCchannel) {
	//select ADC channel with safety mask
	ADMUX = (ADMUX & 0xF0) | (ADCchannel & 0x0F);

	//single conversion mode
	ADCSRA |= (1 << ADSC);

	// wait until ADC conversion is complete
	while ( ADCSRA & (1 << ADSC));

	return ADC;
}

void print(char st[]) {
	int i = 0;

	while (st[i] != 0x00) {
		USART0SendByte(st[i]);
		i++;
	}
}

void print(int num) {
	char myString[7];
	itoa(num, myString, 10);

	int i = 0;

	while (myString[i] != 0x00) {
		USART0SendByte(myString[i]);
		i++;
	}
}

void print(float num) {
	char myString[20];

	dtostrf(num, 4, 2, myString); //converte variavel do tipo float em uma string

	int i = 0;

	while (myString[i] != 0x00) {
		USART0SendByte(myString[i]);
		i++;
	}
}

void println(char s[]) {
	int i = 0;

	while (s[i] != 0x00) {
		USART0SendByte(s[i]);
		i++;
	}
	USART0SendByte(0x0A); //nova linha
	USART0SendByte(0x0D); //retorno do cursor
}

void println(int num) {
	char myString[7];
	itoa(num, myString, 10);

	int i = 0;

	while (myString[i] != 0x00) {
		USART0SendByte(myString[i]);
		i++;
	}
	USART0SendByte(0x0A); //nova linha
	USART0SendByte(0x0D); //retorno do cursor
}

void println(float num) {
	char myString[20];

	dtostrf(num, 4, 2, myString);

	int i = 0;

	while (myString[i] != 0x00) {
		USART0SendByte(myString[i]);
		i++;
	}
	USART0SendByte(0x0A); //nova linha
	USART0SendByte(0x0D); //retorno do cursor
}

float RMS(int repeat) {
	int x = 0;
	long digital_value = 0;
	long accumulated = 0;
	long average = 0;

	do {
		digital_value = ReadADC(analogInPin);
		accumulated += digital_value * digital_value;
		x++;
	} while (x < repeat);

	average = accumulated / repeat;

	return sqrt(average);
}

float volt(float valor) {
	float a1 = 5.0;
	float a2 = 1023.0;
	return (valor * (a1 / a2));

}

float valorPWM(int valor) {
	float a1 = 255;
	float a2 = 1023;
	return (valor * (a1 / a2));

}

// initialize PWM
void pwm_init10() {
	// initialize timer0 in PWM mode
	//TCCR0 |= (1 << WGM00) | (1 << COM01) | (1 << WGM01) | (1 << CS00);

	//--pino 10-- DDH4 pino 10 da placa
	//pino 10 como saída
	DDRB |= (1 << DDB4);

	//TCCR2A –Timer/Counter Control Register A
	// Set Clear OC2A on Compare Match, Fast PWM
	TCCR2A  = ((1 << COM2A1) | (1 << WGM21) | (1 << WGM20)); //0XA3 - configura pino 10 saida pwm e modo fast PWM

	//TCCR2B – Timer/Counter Control Register B
	//sem divisão de prescaling, WGM22 = 0 para Fast PWM
	TCCR2B  = ((1 << CS20)); //0X01

	OCR2A=0; //gera uma saída de forma de onda no pino OC2A.

}

int main(void) {

	//Iniciar USART0
	USART0Init();
	//Iniciar PWM no pino 10
	pwm_init10();
	//Iniciar ADC
	InitADC();


	while (1) {
		//Le pino A0
		valorPino = ReadADC(analogInPin);

		//Valor em volts do valor lido em A0
		voltagem = volt(valorPino);

		//Valor RMS do do valor lido em A0
		valRMS = RMS(30);

		//Valor PWM do do valor lido em A0
		vPwm = valorPWM(valorPino);

		//Atualiza valor PWM no pino 10 para mudar intensidade do led
		OCR2A = vPwm;

		//Imprimir os resultados
		print("Valor analogico = ");
		print(valorPino);

		print("\tValor PWM = ");
		print(vPwm);

		print("\t Valor RMS = ");
		print(valRMS);

		print("\t volts = ");
		println(voltagem);

		_delay_ms(10); // 50ms delay

	}
}
