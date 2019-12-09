
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

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
//Variavel Global
int i = 0;
float Pi = 3.1415926535;
int RD = 8;
int RE = 8;
int CE = 36;
float X = 0;
float Y = 0;
float teta = 0;
int B = 40;
char Protocolo[8];
float Rot1, Rot2 = 0; //Rotacao dos motores

int odometria(int ND, int NE) {
  //Serial.println(ND);
  //Serial.println(NE);
  X = X + (RD * ND + RE * NE) * (Pi / CE) * cos(teta);
  Y = Y + (RD * ND + RE * NE) * (Pi / CE) * sin(teta);
  teta = teta + (RD * ND - RE * NE) * (2 * Pi / CE) / B;
  Serial.print("X eh ");
  Serial.println(X);
  Serial.print("Y eh ");
  Serial.println(Y);
  Serial.print("Teta eh ");
  Serial.println(teta);
  return;
}

void funcoes(char nome[8]) {

  if (nome[0] == '1') {
    QuerryPosition(nome);  //Ler enconder
  }
  else if (nome[0] == '4') {
    travel(nome);           //Envio de rotacao
  }
  else if (nome[0] == '5') {
    ClearPosition(nome);    //Limpar encoder
  }
  else if (nome[0] == '8') {
    SpeedMax(nome);    //Define speed maxima
  }

}
void ClearPosition(char comando[8]) {
  if (comando[1] == '0') {
    Rot1 = 0;             //Motor1
    Rot2 = 0;   //Motor2
  }
  else if (comando[1] == '1') {
    Rot1 = 0;
  }
  else if (comando[1] == '2') {
    Rot2 = 0;
  }
}

void travel(char comando[8]) {
  int numero, rotacao;
  numero = (comando[3] - '0') * (pow(10, 4)) + (comando[4] - '0') * (pow(10, 3)) + (comando[5] - '0') * (pow(10, 2)) + (comando[6] - '0') * (10) + (comando[7] - '0'); //transformando o numero em um só
  //rotacao = numero * 36;  //9 para uma rotação
  rotacao = numero;
  if (rotacao > 32767) {
    rotacao = 32767;
  }
  int k1 = rotacao & 0x00FF;
  int k2 = rotacao >> 8;

  byte x = k2; //max 254
  byte y = k1; //max 255

  if (comando[2] == '1') {  //Se for negativo, complemento A1
    x = ~x;
    y = ~y;
  }
  if (comando[1] == '0') {  //Mover  as 2 rodas
    odometria(rotacao, rotacao);
    Serial1.write(0b00100100);
    delay(10);
    Serial1.write(~x);
    delay(10);
    Serial1.write(~y);
    delay(10);
    Serial1.write(0b00100010);
    delay(10);
    Serial1.write(x);
    delay(10);
    Serial1.write(y);
  }
  else if (comando[1] == '1') { //Mover a roda 1
    odometria(0, rotacao);
    Serial1.write(0b00100100);
    Serial1.write(~x); //Teste de movimentacao
    Serial1.write(~y);
  }
  else if (comando[1] == '2') { //Mover a roda 2
    odometria(rotacao, 0);
    Serial1.write(0b00100010);
    Serial1.write(x); //Teste de movimentacao
    Serial1.write(y);
  }
}
void QuerryPosition(char comando[8]) {

  if (comando[1] == '0') {      //Collect info about all motors
    Serial.println(Rot1);
    Serial.println(Rot2);
  }
  else if (comando[1] == '1') { //Colet infoabout motor 1
    Serial.println(Rot1);
  }
  else if (comando[1] == '2') { //Colet infoabout motor 2
    Serial.println(Rot2);
  }
}
void SpeedMax(char comando[8]) {

  int numero, rotacao;
  numero = (comando[3] - '0') * (pow(10, 4)) + (comando[4] - '0') * (pow(10, 3)) + (comando[5] - '0') * (pow(10, 2)) + (comando[6] - '0') * (10) + (comando[7] - '0'); //transformando o numero em um só
  int k1 = numero & 0x00FF;
  int k2 = numero >> 8;
  byte x = k2; //max 254
  byte y = k1; //max 255


  Serial.print("Entrei");

  if (numero == 0) {
    char movimento[8] = {'4', '0', '0', '0', '0', '0',  '0', '0'};
  }
  if (comando[1] == '0') {
    Serial1.write(0b01000000);
    Serial1.write(x);
    Serial1.write(y);
    if (comando[2] == '1') {
      Rot1 = Rot1 - 0.24;
      Rot2 = Rot2 - 0.24;
      char movimento[8] = {'4', '0', '1', '0', '0', '0',  '0', '9'};

      travel(movimento);
    }
    else {
      Rot1 = Rot1 + 0.24;
      Rot2 = Rot2 + 0.24;

      char movimento[8] = {'4', '0', '0', '0', '0', '0',  '0', '9'};
      travel(movimento);

    }


  }
  else if (comando[1] == '1') {
    Serial1.write(0b01000100);
    Serial1.write(x);
    Serial1.write(y);
    if (comando[2] == '1') {
      Rot1 = Rot1 - 0.24;

      char movimento[8] = {'4', '1', '1', '0', '0', '0',  '0', '9'};
      travel(movimento);
    }
    else {
      Rot1 = Rot1 + 0.24;

      char movimento[8] = {'4', '1', '0', '0', '0', '0',  '0', '9'};
      travel(movimento);

    }
  }

  else if (comando[1] == '2') {
    Serial1.write(0b01000010);
    Serial1.write(x);
    Serial1.write(y);
    if (comando[2] == '1') {
      Rot2 = Rot2 - 0.24;

      char movimento[8] = {'4', '2', '1', '0', '0', '0',  '0', '9'};
      travel(movimento);
    }
    else {
      Rot2 = Rot2 + 0.24;

      char movimento[8] = {'4', '2', '0', '0', '0', '0',  '0', '9'};
      travel(movimento);

    };
  }

}

void leitura() {

}
void setup() {
  Serial.begin(19200);
  Serial1.begin(19200);
}

void loop() {
  char x;
  //-----------------TESTE DE MOVIMENTACAO PRE DETERMINADA------------------------
  /* char movimento1[8], movimento2[8];
    movimento1[0] = '4';
    movimento1[1] = '1';
    movimento1[2] = '0';
    movimento1[3] = '0';
    movimento1[4] = '0';
    movimento1[5] = '0';
    movimento1[6] = '0';
    movimento1[7] = '3';

    movimento2[0] = '1';
    movimento2[1] = '1';
    movimento2[2] = '0';
    movimento2[3] = '0';
    movimento2[4] = '0';
    movimento2[5] = '0';
    movimento2[6] = '0';
    movimento2[7] = '0';*/
  /*
    char movimento[8] = {'8', '0', '0', '0', '0', '0',  '0', '8'};
    while (Serial.available() > 0) {
    x = Serial.read();
    }
    int lol = 0;
    if (x == '8') {   //Wait for all bits(8 bits)
    while (lol < 25) {

    SpeedMax(movimento);
    delay(50);
    SpeedMax(movimento);
    delay(50);
    SpeedMax(movimento);
    delay(500);
    SpeedMax(movimento);
    delay(50);
    SpeedMax(movimento);
    delay(50);
    SpeedMax(movimento);
    delay(50);
    SpeedMax(movimento);
    delay(4000);
    movimento[7] = '0';
    delay(1000);
    movimento[7] = '8';


    movimento[1] = '1';
    movimento[2] = '1';
    SpeedMax(movimento);
    movimento[1] = '2';
    movimento[2] = '0';
    SpeedMax(movimento);
    delay(10);
    movimento[1] = '1';
    movimento[2] = '1';
    SpeedMax(movimento);
    movimento[1] = '2';
    movimento[2] = '0';
    SpeedMax(movimento);
    delay(10);
    movimento[1] = '1';
    movimento[2] = '1';
    SpeedMax(movimento);
    movimento[1] = '2';
    movimento[2] = '0';
    SpeedMax(movimento);
    delay(5000);
    movimento[1] = '0';
    movimento[2] = '0';

    lol++;

    }

    movimento[0] = '1';
    movimento[1] = '0';
    movimento[2] = '0';
    QuerryPosition(movimento);

    }*/
  /*
    while (Serial.available() > 0) {
    x = Serial.read();
    Protocolo[i] = x;
    i++;
    if (i == 8) {   //Wait for all bits(8 bits)
      funcoes(Protocolo);
      i = 0;
    }
    }*/

  char movimento1[8];
  movimento1[0] = '4';
  movimento1[1] = '0';
  movimento1[2] = '1';
  movimento1[3] = '0';
  movimento1[4] = '0';
  movimento1[5] = '0';
  movimento1[6] = '7';
  movimento1[7] = '2';
  while (Serial.available() > 0) {
    x = Serial.read();
    if (x == '8') {   //Wait for all bits(8 bits)
      for (int k = 0; k < 20; k++) {
        movimento1[1] = '0';
        movimento1[6] = '7';
        movimento1[7] = '2';
        travel(movimento1);
        delay(5000);
        movimento1[1] = '2';
        movimento1[6] = '4';
        movimento1[7] = '5';
        travel(movimento1);
        delay(5000);
      }
    }
  }
}
