/*Código feito por Odair do Santos Silva para o projeto de graduação em Engenharia de
Automação pela Universidade Federal do Rio Grande. Código para a leitura de corrente, tensão
e velocidade em RPM de um motor DC*/

#include<DueTimer.h> //biblioteca para fazer interrupções

//definições das constantes do sistema/código
volatile const float v_arduino = 3.3;
volatile const int range = 1023;
volatile const int Rs = 15; //resistor definido para que a tensão máxima seja 15v
volatile const int R1 = 2460;
volatile const int R2 = 9870;

//definições das variáveis para a leitura da tensão e corrente  
volatile float Referencia = 0;
volatile float LeituraShunt = 0;
volatile float LeituraDivisor = 0;

volatile float Vs = 0;
volatile float V1 = 0;

volatile float Is = 0; // corrente no resistor shunt
volatile float Va = 0; // tensão de interesse, tensão no motor

//definições das variáveis da leitura do RPM
volatile int RPM = 0;;
volatile unsigned long pulsos = 0;
volatile unsigned long timeold = 0;
volatile unsigned int pulsos_por_volta = 32;






//configurações para a leitura da corrente, tensão e velocidade utilizando o 
//divisor de tensão e um resistor shunt e um encoder
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT); //leitura do shunt -> Vs
  pinMode(A1, INPUT); //leitura da referência -> Gnd
  pinMode(A2, INPUT); //leitura da tensão do divisor -> V1
  pinMode(52, INPUT); //leitura do canal do encoder

  //chama a função pegaCorrenteTensao a cada 1ms 
  //Timer0.attachInterrupt(pegaCorrenteTensao).start(10000);
  
  //chama a função pegaRPM a cada 100ms 
  Timer1.attachInterrupt(pegaRPM).start(100000);
  
  //chama a função contador a cada subida de borda do pulso do encoder
  attachInterrupt(digitalPinToInterrupt(52), contador, RISING); 
}

void loop() {
  //nesse loop estarão somente os prints
  Serial.print("Tensão de entrada: ");
  Serial.print(Va); //plotta o gráfico da tensão sobre o motor
  Serial.print("  Corrente no motor: ");
  Serial.print(Is); //plotta o gráfico da corrente no motor
  Serial.print("  RPM = ");
  Serial.println(RPM, DEC);
}


//função que faz a leitura dos pinos analógicos e faz as conversões
//necessárias.
void pegaCorrenteTensao(){
  //definições de variáveis
  LeituraShunt = analogRead(A0);
  Referencia = analogRead(A1);
  LeituraDivisor = analogRead(A2);

  Vs = (LeituraShunt - Referencia) * (v_arduino / range);
  Is = (Vs / Rs)*1000; //valor da corrente em mA

  V1 = (LeituraDivisor - Referencia) * (v_arduino / range);
  Va = (V1) * (R1+ R2)/(R1) - (Vs); //valor da tensão em V
}

void pegaRPM(){
  Timer1.stop();
  detachInterrupt(digitalPinToInterrupt(52));

  RPM = (60 * 1000 / pulsos_por_volta) / (millis() - timeold) * pulsos;
  timeold = millis();
  pulsos = 0;
      
  attachInterrupt(digitalPinToInterrupt(52), contador, RISING);
  Timer1.start();
    
}

void contador(){
  pulsos++;  

  pegaCorrenteTensao();
}
