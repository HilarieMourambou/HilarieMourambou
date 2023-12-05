void USART_Transmit1(unsigned char data) {
  // Attente du buffer de transmission vide
  while (!(UCSR1A & (1 << UDRE1)))    ;
  // Placement des données dans le tampon, envoi des données
  UDR1 = data;
}