// ---- Program template for Arduino in Tinkercad VT 2020
#include <avr/io.h>
#include <util/delay.h>
 
/* --- Macros preedefind for the compiler
DDRB  Data direction register B
PORTB Outport B
PINB  Inport B
DDRD  Data direction register D
PORTD Outport D
PIND  Inport D
*/

unsigned char input;

void setup() {
  Serial.begin(9600); // If use of Serial monitor
  DDRD = 0xFF
  // If use of Serial monitor Sets pin 2-7 as output-bits and Pin 1 and 0 as 10.
  DDRB=  

}


void loop() {
  
  
  
  delay(500); // Wait for 500 millisecond(s)
  
  
}
 



