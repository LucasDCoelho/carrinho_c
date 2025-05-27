#include <PID_v1.h>

// C++ code
//

// Parâmetros PID
double entrada, saida, setpoint = 0;
double Kp = 1.5, Ki = 0.0, Kd = 4.5;

// Instância do PID
PID pid(&entrada, &saida, &setpoint, Kp, Ki, Kd, DIRECT);

// Velocidade base do carrinho
const int VELOCIDADE_BASE = 120;  

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);


  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(-100, 100);

  Serial.begin(9600);
  
}

void loop() {
  int sensorDireito = analogRead(A0);
  int sensorEsquerdo = analogRead(A1);

  Serial.println(sensorDireito);
  Serial.println(sensorEsquerdo);

  entrada = sensorEsquerdo - sensorDireito;

  // Calcula o PID
  pid.Compute();

  // Aplica a saída para ajustar velocidade
  int velD = constrain(VELOCIDADE_BASE - saida, 0, 255);
  int velE = constrain(VELOCIDADE_BASE + saida, 0, 255);


  if (sensorDireito < 100 && sensorEsquerdo < 100) {
    irParaFrente(velD, velE);
  } else if (sensorDireito > 100 && sensorEsquerdo < 100) {
    direita(velD, velE);
  } else if (sensorDireito < 100 && sensorEsquerdo > 100) {
    esquerda(velD, velE);
  } else {
    pare();
  }

  delay(5);  // Delay a little bit to improve simulation performance
}


void irParaFrente(int velEsquerda, int velDireita) {
  digitalWrite(4, HIGH);
  analogWrite(5, velEsquerda);
  analogWrite(6, velDireita);
  digitalWrite(7, LOW);
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