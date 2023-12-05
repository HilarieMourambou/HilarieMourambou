unsigned char USART_Receive0(void) {
  // Attente de la réception de données
  while (!(UCSR0A & (1 << RXC0)))    ;
  // Récupération et retour des données reçues depuis le tampon
  return UDR0;
}
