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
int val = 127;
int reading = 0;
int pwm_leitura = 0;
long previousMillis = 0;
long interval = 500; 
void setup() {
  pinMode(capacitorPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  pwm_leitura = Serial.read();

  if(pwm_leitura == 'a'){
    val++;
  }

  if(pwm_leitura == 'd'){
    val--;
  }

  //garantir que não apareça valor 0 por questões do módulo IRAM, não é o ideal
  if(val <= 1){
      val = 1;
  }
  if(val >= 254){
      val = 254;
  }

  
  analogWrite(capacitorPin, 127); //50%
  analogWrite(motorPin2, val);
  analogWrite(motorPin3, val);
  analogWrite(motorPin4, val);
  //analogWrite(motorPin5, val/4);
  reading = val;
  Serial.println(reading);
  
}


