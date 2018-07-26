/*Código feito por Odair do Santos Silva para o projeto de graduação em Engenharia de
Automação pela Universidade Federal do Rio Grande. Código para a leitura de corrente, tensão
e velocidade em RPM de um motor DC*/

#include<DueTimer.h> //biblioteca para fazer interrupções
//#include<FlexiTimer2.h>

//definições das constantes do sistema/código
volatile const float v_arduino = 3.3;
volatile const int range = 1023;
volatile const int Rs = 15; //resistor definido para que a tensão máxima seja 15v
volatile const int R1 = 2460;
volatile const int R2 = 9870;
volatile const float rad_to_rpm = 9.549296596425384;

//definições das variáveis para a leitura da tensão e corrente  
volatile float Referencia = 0;
volatile float LeituraShunt = 0;
volatile float LeituraDivisor = 0;

volatile float Vs = 0;
volatile float V1 = 0;

volatile float Is = 0; // corrente no resistor shunt
volatile float Va = 0; // tensão de interesse, tensão no motor

//definições das variáveis da leitura do RPM
volatile int RPM = 0;
volatile unsigned long pulsos = 0;
volatile unsigned long timeold = 0;
volatile unsigned int pulsos_por_volta = 32;


//definições das variáveis para o uso do IRAM/PWM

volatile int motorPin2 = 2;
volatile int motorPin3 = 3;
volatile int motorPin4 = 4;
volatile int motorPin6 = 6;
volatile int val = 0;
volatile int pwm_leitura = 0;
volatile int pwm1 = 0;
volatile int pwm2 = 0;

volatile float Vcc = 14; //tensão fornecida pela fonte de alimentação

volatile int V_sen = 0;





//configurações para a leitura da corrente, tensão e velocidade utilizando o 
//divisor de tensão e um resistor shunt e um encoder
void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT); //leitura do shunt -> Vs
  pinMode(A1, INPUT); //leitura da referência -> Gnd
  pinMode(A2, INPUT); //leitura da tensão do divisor -> V1
  pinMode(52, INPUT); //leitura do canal do encoder
  
  //chama a função pegaRPM a cada 100ms 
  Timer1.attachInterrupt(pegaRPM).start(100000);
  Timer2.attachInterrupt(mudaPwm).start(1000);
//  FlexiTimer2 :: set (100, pegaRPM); // chama a f u n o flash a cada 2milisegundo
//  FlexiTimer2 :: start ();
  
  //chama a função contador a cada subida de borda do pulso do encoder
  attachInterrupt(digitalPinToInterrupt(52), contador, RISING); 
}

void loop() {

  //leitura do serial monitor para aumentar ou diminuir o pwm
  pwm_leitura = Serial.read();

  //condições para que o pwm não passe de 254 nem diminua menos que 127
  if(pwm_leitura == 'a' && Va <= 11){
    Va++;
  }

  if(pwm_leitura == 'd' && Va >= -11){
    Va--;
  }
  
 
  
  //nesse loop estarão somente os prints
  Serial.print("Va: ");
  Serial.print(Va); //plotta o gráfico da tensão sobre o motor
//  Serial.print("  Tensão de entrada: ");
//  Serial.print(Va); //plotta o gráfico da tensão sobre o motor
//  Serial.print("  Corrente no motor: ");
//  Serial.print(Is); //plotta o gráfico da corrente no motor
  Serial.print("  RPM_Encoder = ");
  Serial.println(RPM, DEC);
//  Serial.print("  RPM_Sensorless = ");
//  Serial.println(V_sen, DEC);
}


//função que faz a leitura dos pinos analógicos e faz as conversões
//necessárias.
//void pegaCorrenteTensao(){
//  //definições de variáveis
//  LeituraShunt = analogRead(A0)*1.15;
//  Referencia = analogRead(A1)*1.15;
//  LeituraDivisor = analogRead(A2)*1.15;
//
//  Vs = (LeituraShunt - Referencia) * (v_arduino / range);
//  Is = (Vs / Rs); //valor da corrente em mA
//
//  V1 = (LeituraDivisor - Referencia) * (v_arduino / range);
//  Va = (V1) * (R1+ R2)/(R1) - (Vs); //valor da tensão em V
//
//  V_sen = (1/0.0666) * (Va - (Is * 16.6)) * rad_to_rpm;
//}

void pegaRPM(){
  //Timer1.stop();
  //FlexiTimer2 :: stop ();
  detachInterrupt(digitalPinToInterrupt(52));

  RPM = (60 * 1000 / pulsos_por_volta) / (millis() - timeold) * pulsos;
  timeold = millis();
  pulsos = 0;
      
  attachInterrupt(digitalPinToInterrupt(52), contador, RISING);
  //FlexiTimer2 :: start ();
  //Timer1.start();
    
}

void mudaPwm(){
  //Vcc = 14
  pwm1 = (Va / Vcc)*127 + 127;
  pwm2 = 254 - pwm1;
  
  //analogWrite(capacitorPin, 127); //50%
  if(Va > 0){
    analogWrite(motorPin2, pwm1*1.4);
    analogWrite(motorPin3, pwm2*1.4);
    }

   if(Va <= 0){
    analogWrite(motorPin2, pwm1*1.4);
    analogWrite(motorPin3, pwm2*1.4);
    }
  //analogWrite(motorPin4, val);
}

void contador(){
  pulsos++;  

//  pegaCorrenteTensao();
}
