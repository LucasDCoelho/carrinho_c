#include <PID_v1.h>
#include <Servo.h>

// C++ code
//

// Parâmetros PID
double entrada, saida, setpoint = 0;
double Kp = 2, Ki = 0.0, Kd = 4.5;

long distance = 0;

// Instância do PID
PID pid(&entrada, &saida, &setpoint, Kp, Ki, Kd, DIRECT);

// Velocidade base do carrinho
const int VELOCIDADE_BASE = 120;  


Servo servoSensor;

// Pinos do motor (ajuste conforme seu hardware)
const int IN1 = 4;     // Sentido motor esquerdo
const int ENA = 5;     // PWM motor esquerdo
const int ENB = 6;     // PWM motor direito
const int IN2 = 7;     // Sentido motor direito

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN2, OUTPUT);
  servoSensor.attach(11);

  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-100, 100);

  Serial.begin(9600);
  
}

void loop() {

  distance = 0.01723 * readUltrasonicDistance(A0, A1);
  entrada = distance;

  // Debug
  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.print(" cm | PID Saída: ");
  Serial.println(saida);

  // Calcula o PID
  pid.Compute();

  // Aplica a saída para ajustar velocidade
  int velD = constrain(VELOCIDADE_BASE - saida, 0, 255);
  int velE = constrain(VELOCIDADE_BASE + saida, 0, 255);


  if (distance > 20) {
    irParaFrente(velE, velD);
  } else {
    pare();
     for (int ang = 0; ang <= 180; ang += 10) {
    servoSensor.write(ang);
    delay(500);
  }
  for (int ang = 180; ang >= 0; ang -= 10) {
    servoSensor.write(ang);
    delay(500);
  }
  }


  // if (sensorDireito < 100 && sensorEsquerdo < 100) {
  //   irParaFrente(velD, velE);
  // } else if (sensorDireito > 100 && sensorEsquerdo < 100) {
  //   direita(velD, velE);
  // } else if (sensorDireito < 100 && sensorEsquerdo > 100) {
  //   esquerda(velD, velE);
  // } else {
  //   pare();
  // }

  delay(200);  // Delay a little bit to improve simulation performance
}




long readUltrasonicDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}


void irParaFrente(int velEsquerda, int velDireita) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velEsquerda);
  analogWrite(ENB, velDireita);
}

void irParaTras() {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

void direita(int velDireita, int velEsquerda) {
  digitalWrite(4, HIGH);
  analogWrite(5, velEsquerda);
  analogWrite(6, HIGH);
  digitalWrite(7, HIGH);
}

void esquerda(int velDireita, int velEsquerda) {
  digitalWrite(4, LOW);
  analogWrite(5, LOW);
  analogWrite(6, velDireita);
  digitalWrite(7, LOW);
}

void pare() {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}