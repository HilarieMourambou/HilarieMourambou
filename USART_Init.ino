void USART_Init(unsigned int ubrr) {
  // Initialisation de l'USART 0 (UART sur la carte Arduino Mega)
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);  // Activation du récepteur, de l'émetteur et de l'interruption de réception
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);  // Format de trame: 8 données, 1 bit d'arrêt
  
  // Initialisation de l'USART 1
  UBRR1H = (unsigned char)(ubrr >> 8);
  UBRR1L = (unsigned char)ubrr;
  UCSR1B = (1 << RXEN1) | (1 << TXEN1) | (1 << RXCIE1);  // Activation du récepteur, de l'émetteur et de l'interruption de réception
  UCSR1C = (1 << UCSZ11) | (1 << UCSZ10);  // Format de trame: 8 données, 1 bit d'arrêt
  
  
}