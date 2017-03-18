/*
  Botoes na H2HC

 Permite mapear os botoes da plaquinha H2HC, que sao.

 Botao esquerdo = Pino 10
 Botao direito = Pino 9

 created 13/11/2016
 
 */

// constants won't change. They're used here to
// set pin numbers:
const int buttonPinE = 10;     // the number of the pushbutton pin
const int buttonPinD = 9; 
const int ledPinE =  0;      // the number of the LED pin
const int ledPinD =  3; 


// variables will change:
int buttonStateD = 0;         // variable for reading the pushbutton status
int buttonStateE = 0;


void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPinE, OUTPUT);
  pinMode(ledPinD, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPinE, INPUT);
  pinMode(buttonPinD, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonStateD = digitalRead(buttonPinD);
  buttonStateE = digitalRead(buttonPinE);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonStateD == HIGH) {
    // turn LED on:
    digitalWrite(ledPinD, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPinD, LOW);
  }

  if (buttonStateE == HIGH) {
    // turn LED on:
    digitalWrite(ledPinE, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPinE, LOW);
  }
  
}
