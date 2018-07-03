/*
 Fading

 This example shows how to fade an LED using the analogWrite() function.

 The circuit:
 * LED attached from digital pin 9 to ground.

 Created 1 Nov 2008
 By David A. Mellis
 modified 30 Aug 2011
 By Tom Igoe

 http://www.arduino.cc/en/Tutorial/Fading

 This example code is in the public domain.

 */


int motorPin2 = 2; //motores
int motorPin3 = 3;
int motorPin4 = 4;
//int motorPin5 = 5;
int capacitorPin = 6;// PWM com valor de 50% para emular o banco de capacitores
int analogPin = A0;
int val = 0;
int reading = 0;

long previousMillis = 0;
long interval = 500; 
void setup() {
  pinMode(capacitorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
//  val = analogRead(analogPin);
//
//  //garantir que não apareça valor 0 por questões do módulo IRAM, não é o ideal
//  if(val == 0){
//      val = 20;
//  }
//  if(val == 1023){
//      val = 1000;
//  }

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
 
    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
 
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
  }
  
  analogWrite(capacitorPin, 127); //50%
  analogWrite(motorPin2, val);
  analogWrite(motorPin3, val);
  analogWrite(motorPin4, val);
  //analogWrite(motorPin5, val/4);
  reading = val;
  Serial.println(reading);
  
}


