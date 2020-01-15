#include <Wire.h>
//Instrucao de Querry
int QPOS = 0b00001;
int QSPD = 0b00010;
int CHFA = 0b00011;
//Instrucao de acao
int TRVL = 0b00100;
int CLRP = 0b00101;
//Instrucao de conf
int SREV = 0b00110;
int STXD = 0b00111;
int SMAX = 0b01000;
int SSRR = 0b01001;
//Motores
int motor1 = 0b100;
int motor2 = 0b010;
int motor0 = 0b000;
//Variavel Global
int protocolo;

int CalculoProt(int Nome, int mot ) { //concatenacao de protocolos
  int x;
  x = Nome * 8 + mot;
  return x;
}

void travel(int comando[2]) {
  int numero, rotacao;
  numero = comando[1];
  rotacao = numero * 36;  //9 para uma rotação
  //rotacao = numero;
  if (rotacao > 32767) {
    rotacao = 32767;
  }
  int k1 = rotacao & 0x00FF;
  int k2 = rotacao >> 8;

  byte x = k2; //max 254
  byte y = k1; //max 255


  if (comando[0] == 9) {  //Mover  as 2 rodas
    Serial.write(0b00100100);
    Serial.write(~x);
    Serial.write(~y);
    Serial.write(0b00100010);
    Serial.write(x);
    Serial.write(y);
  }
  else if (comando[0] == 1) { //Mover a roda 1
    Serial.write(0b00100100);
    Serial.write(~x); //Teste de movimentacao
    Serial.write(~y);
  }
  else if (comando[1] == 2) { //Mover a roda 2
    Serial.write(0b00100010);
    Serial.write(x); //Teste de movimentacao
    Serial.write(y);
  }
}

void SpeedMax(int numero[2]) {
  int k1 = numero[1] & 0x00FF;
  int k2 = numero[1] >> 8;
  byte x = k2; //max 254
  byte y = k1; //max 255

  if (numero[0] == 9) {
    Serial.write(0b01000000);
    Serial.write(x);
    Serial.write(y);
    int movimento[2] = {9, 3};
    travel(movimento);
  }
   if (numero[0] == 1) {
    Serial.write(0b01000100);
    Serial.write(x);
    Serial.write(y);
    int movimento[2] = {9, 3};
    travel(movimento);
  }
}

void setup() {

  Serial.begin(19200);
  Wire.begin(0x8);
  Wire.onReceive(receiveEvent);

}


void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    int c = Wire.read(); // receive byte as a character
    if (c == 0) {
      c = Wire.read();
    }
    int b = Wire.read();
    int vet[2] = {c, b};
    //travel(vet);
    SpeedMax(vet);




    // }
    // else if (c == 0) {
    //  Serial.println("Entrei");
    // Serial.println(c);
    //Serial.println(b);
    // SpeedMax(20);
    // }
  }
}

void loop() {
  delay(100);
}


