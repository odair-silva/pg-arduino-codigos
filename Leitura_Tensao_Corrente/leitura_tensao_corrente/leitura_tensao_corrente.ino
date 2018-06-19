// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(A0, INPUT); //leitura do shunt > Vs
  pinMode(A1, INPUT); //leitura da referência > GND
  pinMode(A2, INPUT); //leitura da tensão do divisor > V1

}
//definições das constantes do sistema
const float v_arduino = 3.3;
const int range = 1023;
const int v_max = 15;
const int R1 = 2460;
const int R2 = 9870;
  
float Referencia = 0;
float LeituraShunt = 0;
float LeituraDivisor = 0;

float Vs = 0;
float V1 = 0;

float Is = 0; // corrente no resistor shunt
float Va = 0; // tensão de interesse, tensão no motor

// the loop routine runs over and over again forever:
void loop() {
  //definições de variáveis
  LeituraShunt = analogRead(A0);
  Referencia = analogRead(A1);
  LeituraDivisor = analogRead(A2);

  Vs = (LeituraShunt - Referencia) * (v_arduino / range);
  Is = (Vs / v_max)*1000; //valor da corrente em mA

  V1 = (LeituraDivisor - Referencia) * (v_arduino / range);
  Va = (V1) * (R1+ R2)/(R1) - (Vs);
  
  Serial.println(Va); //plotta o gráfico da tensão sobre o motor
  //Serial.println(Is); //plotta o gráfico da corrente no motor
}
