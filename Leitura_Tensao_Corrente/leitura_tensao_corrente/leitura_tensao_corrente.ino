/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogReadSerial
*/

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
}

float Referencia = 0;
float V_Shunt = 0;
float V_Divisor = 0;

float Volts = 0;
float RawAmp = 0;

float Amp = 0;
float Volt = 0;

float Va = 0;

// the loop routine runs over and over again forever:
void loop() {
  V_Shunt = (analogRead(A0) - analogRead(A1)) * (3.3 / 1023.0);
 //V_Shunt = map(analogRead(A0), 0, 1023, 0, 3);
  Referencia= analogRead(A1);
  Volts = ((V_Shunt - Referencia) * (3.3 / 1023.0));
  Amp = (Volts / 23.6)*100;

  V_Divisor = (analogRead(A2) - analogRead(A1)) * (3.3 / 1023.0);
  //Va = (V_Divisor - Referencia) * (3.3 / 1023.0);

  Va = (V_Divisor) * (2500 + 10000)/(2500) - (V_Shunt);
  //Serial.println(Volt);  
  //Serial.print(V_Divisao); 
  Serial.println(Va);  
  //Serial.print("mA x10: ");   Serial.println(Volt);
  //delay(100);        // delay in between reads for stability
}
