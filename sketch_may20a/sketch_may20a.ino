// C++ code
//
void setup() {
  pinMode(A0, INPUT);
  pinMode(A5, INPUT);


  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int sensorDireito = analogRead(A0);
  int sensorEsquerdo = analogRead(A5);

  Serial.println(sensorDireito);
  Serial.println(sensorEsquerdo);


  if (sensorDireito < 100 && sensorEsquerdo < 100) {
    irParaFrente();
  } else if (sensorDireito > 100 && sensorEsquerdo < 100) {
    direita();
  } else if (sensorDireito < 100 && sensorEsquerdo > 100) {
    esquerda();
  } else {
    pare();
  }

  delay(10);  // Delay a little bit to improve simulation performance
}


void irParaFrente() {
  digitalWrite(4, HIGH);
  analogWrite(5, 40);
  analogWrite(6, 110);
  digitalWrite(7, LOW);
}

void irParaTras() {
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

void direita() {
  digitalWrite(4, HIGH);
  analogWrite(5, 40);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
}

void esquerda() {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  analogWrite(6, 110);
  digitalWrite(7, LOW);
}

void pare() {
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}