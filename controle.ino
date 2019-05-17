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
int allmotor = 0b000;
//Variavel Global
int protocolo;
int comando;
int estado =0;
int CalculoProt(int Nome, int mot ){
  int x;
  x = Nome*8 + mot;
  return x;
}

void setup() {
  Serial.begin(19200);
  pinMode(2,INPUT);
  pinMode(8,OUTPUT);
  protocolo = CalculoProt(TRVL,motor1); //Manda ao contrário 0b0000001 , esse 1 vai primeiro
  
}

void loop() {
  estado = digitalRead(2);
  if(estado == HIGH){
    Serial.write(protocolo);
    Serial.write(0b11111111);
    Serial.write(0b11111111);
    digitalWrite(8, HIGH);
  }
  else{
     digitalWrite(8, LOW);
  }
}
