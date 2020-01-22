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
float Pi = 3.1415926535;
int RD = 8;  //right wheel
int RE = 8;  //Leftwhell
int CE = 36; //distance to center
float X = 0;
float Y = 0;
float teta = 0;
int B = 40;

void travel(int comando[2]) { //controll the position
  int numero, rotacao;
  numero = abs(comando[1]);
  rotacao = numero * 36;  //9 para uma rotação

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
  else if (comando[1] == 2) { //Move the left wheel
    Serial.write(0b00100010);
    Serial.write(x);
    Serial.write(y);
  }
}

void SpeedMax(int numero[2]) {  //Controll the speed
  int aux = numero[1];
  numero[1] = abs(numero[1]);
  int k1 = numero[1] & 0x00FF;
  int k2 = numero[1] >> 8;
  byte x = k2; //max 254
  byte y = k1; //max 255

  if (aux >= 0) { //If forward
    if (numero[0] == 9) {
      Serial.write(0b01000000);
      Serial.write(x);
      Serial.write(y);

      int movimento[2] = {9, 1};
      travel(movimento);
    }
    if (numero[0] == 1) {
      Serial.write(0b01000100);
      Serial.write(x);
      Serial.write(y);

      int movimento[2] = {9, 1};
      travel(movimento);
    }
    if (numero[0] == 2) {
      Serial.write(0b01000010);
      Serial.write(x);
      Serial.write(y);

      int movimento[2] = {9, 1};
      travel(movimento);
    }
  }
  else {
    if (numero[0] == 9) { //If backward
      Serial.write(0b01000000);
      Serial.write(x);
      Serial.write(y);

      int movimento[2] = {9, -1};
      travel(movimento);
    }
    if (numero[0] == 1) {
      Serial.write(0b01000100);
      Serial.write(x);
      Serial.write(y);

      int movimento[2] = {9, -1};
      travel(movimento);
    }
    if (numero[0] == 2) {
      Serial.write(0b01000010);
      Serial.write(x);
      Serial.write(y);

      int movimento[2] = {9, -1};
      travel(movimento);
    }
  }

}

int odometria(int ND, int NE) {
  X = X + (RD * ND + RE * NE) * (Pi / CE) * cos(teta);
  Y = Y + (RD * ND + RE * NE) * (Pi / CE) * sin(teta);
  teta = teta + (RD * ND - RE * NE) * (2 * Pi / CE) / B;
  return;
}

void setup() {
  Serial.begin(19200);
  Wire.begin(0x8);
  Wire.onReceive(receiveEvent);
}

//The protocol receives 3 value,  the fist is what motors. 1 for right,2 for left and 9 for both.
//The second is to identify whether the movement is forward(1) or backward(0)
//The last number is the valor of velocity  1~255
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    int nb1 = Wire.read(); // Read fist value
    if (nb1 == 0)
      nb1 = Wire.read();
    int nb2 = Wire.read();  // Read fist value
    int nb3 = Wire.read();  // Read fist value

    if  (nb2 == 1)
      nb3 = -nb3;

    int vet[2] = {nb1, nb3};

    //travel(vet);
    SpeedMax(vet);  //Call the function
  }
}

void loop() {
  delay(100);
}


