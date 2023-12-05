void USART_Transmit0(unsigned char data) {
  // Attente du buffer de transmission vide
  while (!(UCSR0A & (1 << UDRE0)))    ;
  // Placement des données dans le tampon, envoi des données
  UDR0 = data;
}
