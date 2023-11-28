#define FOSC 16000000  // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC / 16 / BAUD - 1
#define FRAMING_ERROR (1<<FE0)
#define PARITY_ERROR (1<<UPE0)
#define DATA_OVERRUN (1<<DOR0)

int flag;  // Variable pour stocker la donnée reçue
char byteReceive;


int main(void) {

  USART_Init(MYUBRR);

  sei();

  while (1) {

    
    //USART_Transmit(USART_Receive() + 1);
    // USART_Transmit(10);

   // USART_putsln("MOI");
  
    _delay_ms(1);
    
  }
}
void USART_Init(unsigned int ubrr) {
  /*Set baud rate */
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  //Enable receiver and transmitter */
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART_Transmit(unsigned char data) {
  /* Wait for empty transmit buffer */
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  /* Put data into buffer, sends the data */
  UDR0 = data;
}
unsigned char USART_Receive(void) {
  /* Wait for data to be received */
  while (!(UCSR0A & (1 << RXC0)))
    ;
  /* Get and return received data from buffer */
  return UDR0;
}

void USART_puts(unsigned char *str) {
  do {
    USART_Transmit(*str);
  } while (*++str != 0);
}


ISR(USART_RX_vect) {
  // Lire la donnée reçue
  char status=UCSR0A;
  byteReceive = UDR0;
  if ((status & (FRAMING_ERROR | PARITY_ERROR | DATA_OVERRUN))==0) {   
      USART_Transmit(byteReceive+1);   
  }else{
    USART_putsln("Error");
  }
}


void USART_putsln(unsigned char *str) {
    // Envoyer la chaîne
  USART_puts(str);

  // Envoyer un caractère de nouvelle ligne ('\n')
  USART_Transmit('\n');
  USART_Transmit('\r');
}