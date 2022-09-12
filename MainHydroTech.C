#include <AFMotor.h>
#include <Servo.h>

#define bomba 22 //Pinagem Bomba
#define PinsensorA A8 //Pinagem sensor de umidade do solo
int umidade; 

#define motor 21 //Pinagem servo motor

Servo servo1;

//Pinagem motores DC
AF_DCMotor motor1(1); 
AF_DCMotor motor2(4);
 
void setup()
{
  //Velocidade dos motores DC
  motor1.setSpeed(200); 
  motor2.setSpeed(200);
  
  //Configuração Inicial do servo motor
  servo1.attach(motor);
  servo1.write(0);

  //Configuração da bomba de irrigação
  pinMode (bomba , OUTPUT);

  Serial.begin(9600);
  
}
 
void loop()
{

  int N = 3; //Número de idas para frente
  
  for (int cont = 0; cont < N; cont++)
  {
    //Motores indo para frente
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
    
    delay(2000); //Tempo de rotação dos motores

    //Motores Parados
    motor1.run(RELEASE);
    motor2.run(RELEASE);

    delay(1000); //Tempo de espera para a próxima ação

    servo1.write(17); //Servo abaixa com o sensor de umidade

    delay(1000); //Espera para a próxima ação

    umidade = analogRead (A8); //Medição da umidade
    Serial.write(umidade);

    //Condição umidade baixa
    if (umidade > 700)
        {
           digitalWrite (bomba, HIGH); //Bomba ligada
           delay(2000); //Tempo de funcionamento da bomba
           digitalWrite (bomba, LOW); //Bomba desligada
         }

    //Condição umidade boa
    else
        {
           digitalWrite(bomba, LOW); //bomba desligada
        }
  
  delay(2000); //Espera para a próxima ação

  servo1.write(0); //Servo levanta o sensor de umidade 

  delay(2000); // Espera para os motores voltarem a ir para frente 
  }

  //Motores voltando 
  motor1.run(FORWARD);
  motor2.run(FORWARD);
 
  delay(6000); //Tempo de rotação dos motores para a volta

  //Motores parados
  motor1.run(RELEASE); 
  motor2.run(RELEASE);

  delay (2000); //Tempo de espera para reiniciar o ciclo
}
