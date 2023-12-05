#define FOSC 16000000  // Fréquence du quartz (Clock Speed)
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1
#define FRAMING_ERROR (1 << FE0)
#define PARITY_ERROR (1 << UPE0)
#define DATA_OVERRUN (1 << DOR0)

int flag;  // Variable pour stocker la donnée reçue
char byteReceive;


ISR(USART0_RX_vect) {
  // Lecture de la donnée reçue
  char status = UCSR0A;
  byteReceive = UDR0;
  if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == 0) {
    // Traitement des données reçues (ajout de 1 et renvoi)
    USART_Transmit1(byteReceive + 1);
  } else {
    // Gestion des erreurs
   // USART_putsln("Error");
  }
}

ISR(USART1_RX_vect) {
  // Lecture de la donnée reçue
  char status = UCSR1A;
  byteReceive = UDR1;
  if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN)) == 0) {
    // Traitement des données reçues (ajout de 1 et renvoi)
    USART_Transmit0(byteReceive + 1);
  } else {
    // Gestion des erreurs
   // USART_putsln("Error");
  }
}

int main(void) {
  USART_Init(MYUBRR);

  sei();

  while (1) {
    // Votre code principal ici
    
    _delay_ms(1);
  }
}
