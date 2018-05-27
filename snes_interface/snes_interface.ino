#define LATCH 5
#define CLOCK 6
#define SERIAL_DATA 7

volatile uint8_t currently_state = 0;

//https://www.instructables.com/id/Arduino-Timer-Interrupts/

void button_sending();

// put your setup code here, to run once
void setup()
{
  cli();//stop interrupts

  //set timer0 interrupt at 2kHz
  TCCR0A = 0; // set entire TCCR2A register to 0
  TCCR0B = 0; // same for TCCR2B
  TCNT0  = 0; //initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;  // = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  sei();  //allow interrupts
  
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(SERIAL_DATA, INPUT);

  digitalWrite(LATCH, LOW);
  digitalWrite(CLOCK, HIGH);
  
  Serial.begin(9600);
}

// put your main code here, to run repeatedly
void loop(){}

// Timer interrupt at each 500 us 
ISR(TIMER0_COMPA_vect)
{
  // LATCH pulse
  if(currently_state == 0 || currently_state == 1)
  {
    digitalWrite(LATCH, HIGH);
    digitalWrite(CLOCK, HIGH);
  }
  // Buttons reading
  else if(currently_state < 32)// currently_state >= 2
  {
    switch(currently_state % 2)
    {
      case 0:
      {
        digitalWrite(LATCH, LOW);
        digitalWrite(CLOCK, HIGH);
        break;
      }   
      case 1:
      {
        digitalWrite(LATCH, LOW);
        digitalWrite(CLOCK, LOW);
      } 
    }
    button_sending();
  }
  else
  {
    digitalWrite(LATCH, LOW);
    digitalWrite(CLOCK, HIGH);
    currently_state = -1;
  }
  currently_state++;
}

void button_sending()
{
  if(!digitalRead(SERIAL_DATA))
  {
    switch(currently_state)
    {
      case 3: // B button
      {
        Serial.println("B");
        break;
      }
      case 5: // Y button
      {
        Serial.println("Y");
        break;
      }
      case 7: // SELECT button
      {
        Serial.println("SELECT");
        break;
      }
      case 9: // START button
      {
        Serial.println("START");
        break;
      }
      case 11: // UP button
      {
        Serial.println("UP");
        break;
      }
      case 13: // DOWN button
      {
        Serial.println("DOWN");
        break;
      }
      case 15: // LEFT button
      {
        Serial.println("LEFT");
        break;
      }
      case 17: // RIGHT button
      {
        Serial.println("RIGHT");
        break;
      }
      case 19: // A button
      {
        Serial.println("A");
        break;
      }
      case 21: // X button
      {
        Serial.println("X");
        break;
      }
      case 23: // L button
      {
        Serial.println("L");
        break;
      }
      case 25: // R button
      {
        Serial.println("R");
      }
    }
  }
}
