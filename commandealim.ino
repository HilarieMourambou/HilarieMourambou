#define FOSC 16000000  // Fréquence du quartz (Clock Speed)
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1

char flag0=0,flag1=0;

char byteReceive;  // Variable pour stocker la donnée reçue

int main(void) {
  USART_Init(MYUBRR);
  sei();  // Activation des interruptions globales

  while (1) {
    // Votre code principal ici
    if(flag0){
      USART1_Transmit(UDR0);
      flag0=0;
    }
    
    if(flag1){
      USART0_Transmit(UDR1);
      flag1=0;
    }
    _delay_ms(1);
  }
}

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

void USART0_Transmit(unsigned char data) {
  // Attente du buffer de transmission vide
  while (!(UCSR0A & (1 << UDRE0)));
  // Placement des données dans le tampon, envoi des données
  UDR0 = data;
}

void USART1_Transmit(unsigned char data) {
  // Attente du buffer de transmission vide
  while (!(UCSR1A & (1 << UDRE1)))    ;
  // Placement des données dans le tampon, envoi des données
  UDR1 = data;
}

ISR(USART0_RX_vect) {
  flag0=1;
}

ISR(USART1_RX_vect) {
  flag1=1;
}
