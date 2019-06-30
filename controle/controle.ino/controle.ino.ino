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
char Protocolo[8];

void funcoes(char nome[8]) {
  if (nome[0] == '4') {
    travel(nome);
  }
  else if (nome[0] == '1') {
    QuerryPosition(nome);
  }


}
void QuerryPosition(char comando[8]) {
  int XH, XL;

  if (comando[1] == '0') {      //Colet info about all motors
    Serial.write(0b00001000);
  }
  else if (comando[1] == '1') { //Colet infoabout motor 1
    Serial.write(0b00001100);
  }
  else if (comando[1] == '2') { //Colet infoabout motor 2
    Serial.write(0b00001010);

    if (Serial.available() > 0) { //Waiting for receive info
      XH = Serial.read();
      XL = Serial.read();
    }
    Serial.println(XH);
    delay(10);
    Serial.println(XL);
  }
}void travel(char comando[8]){
  byte x = 0; //max 254
  byte y = 63; //max 255
  if(comando[1]=='0') {
    Serial.write(0b00100100);
    Serial.write(~x);
    Serial.write(~y);
    Serial.write(0b00100010);
    Serial.write(x);
    Serial.write(y);
  }
  else if(comando[1] =='1'){
    Serial.write(0b00100100);
    Serial.write(~x);
    Serial.write(~y);
  
  }
  else if(comando[1] =='2'){
    Serial.write(0b00100010);
    Serial.write(x);
    Serial.write(y);
  
  }

}
  void setup() {
    Serial.begin(19200);

  }

  void loop() {
    char x;
    while (Serial.available() > 0) {
      x = Serial.read();
      Protocolo[i] = x;
      i++;
    }

    if (i == 7) {   //Wait for all bits(8 bits)
      funcoes(Protocolo);
      i = 0;
    }
  }
