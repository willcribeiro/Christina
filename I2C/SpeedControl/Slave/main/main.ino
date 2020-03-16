#include <Wire.h>
// Variavel Global
float Pi = 3.1415926535;
int RD = 8;  //right wheel
int RE = 8;  //Leftwhell
int CE = 36;
float X = 0;
float Y = 0;
float teta = 0;
int B = 40;
int WD = 36, WE = 36; //Velocidade padrão das rodas
char str[15];
int Vk, Wk;
float T = 0.08;

//-----------------------------FUNCAO DE MOVIMENTACAO DE PULSO-----------------------------------
void travel(int comando[2]) { //controll the position
  int numero, rotacao;
  numero = comando[1];
  rotacao = abs(comando[1]);
  if (rotacao > 32767) {
    rotacao = 32767;
  }
  //convert the number
  int k1 = rotacao & 0x00FF;
  int k2 = rotacao >> 8;

  byte x = k2; //max 254
  byte y = k1; //max 255

  if (comando[1] < 0) { //If negative, complement A1
    x = ~x;
    y = ~y;
  }
  if (comando[0] == 9) {  //Move the 2 wheels
    Serial.write(0b00100100);
    Serial.write(~x);
    Serial.write(~y);
    Serial.write(0b00100010);
    Serial.write(x);
    Serial.write(y);
  }
  else if (comando[0] == 1) { //Move the rigth wheel
    Serial.write(0b00100100);
    Serial.write(~x);
    Serial.write(~y);
  }
  else if (comando[0] == 2) { //Move the left wheel
    Serial.write(0b00100010);
    Serial.write(x);
    Serial.write(y);
  }
}
//-----------------------------FIM DA FUNCAO DE MOVIMENTACAO DE PULSO-----------------------------------

//-----------------------------FUNCAO DE CONTROLE DE VELOCIDADE-----------------------------------------

void SpeedMax(int numero[2]) {  //Controll the speed
  //Converter vel.  angular em Numero de pulsos : rpm -> pulsos/0.5s
  int N_P = abs(numero[1]) * 0.3;

  int k1 = N_P & 0x00FF;
  int k2 = N_P >> 8;
  byte x = k2; //max 254
  byte y = k1; //max 255

  if (numero[1] >= 0) { //If forward
    if (numero[0] == 9) {
      Serial.write(0b01000000);
      Serial.write(x);
      Serial.write(y);

      int movimento[2] = {9, 18};
      travel(movimento);
    }
    if (numero[0] == 1) {
      Serial.write(0b01000100);
      Serial.write(x);
      Serial.write(y);
      //Para que ambas as rodas terminem iguais
      WD = abs(numero[1]);
      convert(1);

    }
    if (numero[0] == 2) {
      Serial.write(0b01000010);
      Serial.write(x);
      Serial.write(y);
      //Para que ambas as rodas terminem iguais
      WE = abs(numero[1]);
      convert(1);

    }
  }
  else {
    if (numero[0] == 9) { //If backward
      Serial.write(0b01000000);
      Serial.write(x);
      Serial.write(y);

      int movimento[2] = {9, -18};
      travel(movimento);
    }
    if (numero[0] == 1) {
      Serial.write(0b01000100);
      Serial.write(x);
      Serial.write(y);

      WD = abs(numero[1]);
      convert(-1);
    }
    if (numero[0] == 2) {
      Serial.write(0b01000010);
      Serial.write(x);
      Serial.write(y);

      WE = abs(numero[1]);
      convert(-1);
    }
  }
}

void convert(int sinal) {
  int pulso = 18;
  if (sinal < 0)
    pulso = -pulso;
  int aux;
  // W1/W2 * X2 = X1
  aux  = (WD / WE) * pulso;
  int movimento[2] = {1, aux};
  travel(movimento);
  int movimento2[2] = {2, pulso};
  travel(movimento2);
}
//-----------------------------FIM DA FUNCAO DE CONTROLE DE VELOCIDADE-----------------------------------------


//----------------------------------------I2C COMUNICACAO------------------------------------------------------
//The protocol receives 3 value,  the fist is what motors. 1 for right,2 for left and 9 for both.
//The second is to identify whether the movement is forward(1) or backward(0)
//The last number is the valor of velocity  1~255
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    int nb1, nb2, nb3, nb4; //motor,sentido, valor, tipo de mov

    nb1 = Wire.read(); // Read fist value
    if (nb1 == 0)
      nb1 = Wire.read();
    nb2 = Wire.read();  // Read fist value
    nb3 = Wire.read();  // Read fist value
    if  (nb2 == 1)
      nb3 = -nb3;


    int vet[4] = {nb1, nb2, nb3, nb4};
    Funcoes(vet);
  }
}
void requestEvent() {
  float data[3];
  data[0] = X;
  data[1] = Y;
  data[2] = teta;
  Wire.write((byte*) &data, 3 * sizeof(float));
}

//----------------------------------------FIM I2C COMUNICACAO------------------------------------------------------

void Funcoes(int protocolo[4]) {
  if (protocolo[2] == 1) protocolo[3] = -protocolo[3];
  int vetor[2] = {protocolo[1], protocolo[3]};
  
  switch (protocolo[4]) {
    case 1:
      // controle de vel.
      SpeedMax(vetor);
    case 2:
      // controle de pulso
      travel(vetor);
  }
}

void setup() {
  Serial.begin(19200);
  Wire.begin(0x18);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
}

void loop() {
  delay(100);
}
