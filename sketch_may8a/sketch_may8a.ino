#include <SoftwareSerial.h>

// Definição dos pinos para comunicação com o módulo Bluetooth
int bluetoothTx = 9;  // Pino TX do módulo Bluetooth conectado ao RX do Arduino
int bluetoothRx = 8;  // Pino RX do módulo Bluetooth conectado ao TX do Arduino

// Inicialização do objeto para comunicação Bluetooth
SoftwareSerial bluetooth(bluetoothRx, bluetoothTx);
char ultimoComando = 0;
char item = 0;

void setup() 
{
  // Inicialização da comunicação serial padrão (para comunicação com o computador via USB)
  Serial.begin(9600);
  
  // Inicialização da comunicação serial com o módulo Bluetooth
  bluetooth.begin(9600);

  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

}


void loop() 
{
    if (bluetooth.available() > 0) {
    item = bluetooth.read();
    Serial.println(item);
  
      
     switch(item){
      case 'w': irParaFrente(); break;
      case 's': irParaTras(); break;
      case 'd': direita(); break;
      case 'a': esquerda(); break;
      case 'p': pare(); break;
      case '0': zeroEsquerda(); break;
      case '1': zeroDireita(); break;
     }

    
  }
}

void irParaFrente(){
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}

void irParaTras(){
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}

void direita(){
  digitalWrite(4, HIGH);
  analogWrite(5, 40);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
}

void esquerda(){
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  analogWrite(6, 40);
  digitalWrite(7, HIGH);
}

void pare(){
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
}

void zeroEsquerda(){
  digitalWrite(4, LOW);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
}

void zeroDireita(){
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(7, HIGH);
}