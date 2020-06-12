#include <avr/io.h>
#define Fosc 16000000 // Clock Speed
#define BaudRate 9600
#define ValorUBRR (((Fosc/(BaudRate*16UL)))-1) //igual a 103 = 00000000 01100111

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

int main(void) {
	uint8_t u8TempData;
	//Initialize USART0
	USART0Init();
	while (1) {
		// Receive data
		u8TempData = USART0ReceiveByte();

		//Send back to terminal
		USART0SendByte(u8TempData);
	}
}
