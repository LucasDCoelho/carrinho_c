#include <SoftwareSerial.h>

// Definição dos pinos para comunicação com o módulo Bluetooth
int bluetoothTx = 9;  // Pino TX do módulo Bluetooth conectado ao RX do Arduino
int bluetoothRx = 8;  // Pino RX do módulo Bluetooth conectado ao TX do Arduino

// Inicialização do objeto para comunicação Bluetooth
SoftwareSerial bluetooth(bluetoothRx, bluetoothTx);


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
    char item = bluetooth.read();
    Serial.println(item);
    if (item == 'w') {
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
    }
    if (item == 'a') {
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      analogWrite(6, 150);
      digitalWrite(7, LOW);
    }
    if (item == 's') {
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
    }
    if (item == 'd') {
      digitalWrite(4, HIGH);
      analogWrite(5, 150);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
    }
    if(item == 'p'){
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
    }
    if(item == '0'){
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
    }
    if(item == '1'){
      digitalWrite(4, HIGH);
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
    }
    delay(10);
  }
}