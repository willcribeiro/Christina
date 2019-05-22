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
int leituraProtocolo = 0;
int leituraMotor = 0;
int entradaProtocolo = A0;
int entradaMotor = A1;
int flag = 0;
int auxProtocolo;
int auxMotor;

int CalculoProt(int Nome, int mot ){ //concatenacao de protocolos
  int x;
  x = Nome*8 + mot;
  return x;
}

void CM1(int nome,int motor){
   int env,ValueH,ValueL;
   env = CalculoProt(nome,motor);
   Serial.write(env);
   delay(10);
   if (Serial.available() > 0) {
    ValueH = Serial.read();
    ValueL = Serial.read();

  }  
}

void mover(int nome, int motor){
  int env,ValueH,ValueL;
  env = CalculoProt(nome,motor);
  Serial.write(env);
  Serial.write(0b11111111);
  Serial.write(0b11111111);
} 
void setup() {
  Serial.begin(19200);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(9,OUTPUT);
  protocolo = CalculoProt(TRVL,motor1); //Manda ao contrário 0b0000001 , esse 1 vai primeiro
  
}

void loop() {
  flag = digitalRead(9);
  leituraProtocolo = analogRead(entradaProtocolo);
  leituraMotor = analogRead(entradaMotor);

  if(flag == 1){  //se o controlador estiver enviando comando

    switch(leituraMotor){
      case 0:
        auxMotor = motor0;
        break;
      case 1:
        auxMotor = motor1;
        break;
      case 2:
        auxMotor = motor2;
        break;
      default:
        auxProtocolo = 0;
        break;
      }
    switch(leituraProtocolo){
      case 1:
        CM1(QPOS,auxMotor); //vai receber 2 valores 8 bits
        break;
      case 2:
        auxProtocolo = QSPD;
        break;
      case 3:
        auxProtocolo = CHFA;
        break;
      case 4:
        auxProtocolo = TRVL;
        break;
      case 5:
        auxProtocolo = CLRP;
        break;
      case 6:
        auxProtocolo = SREV;
        break;
      case 7:
        auxProtocolo = STXD;
        break;
      case 8:
        auxProtocolo = SMAX;
        break;
      case 9:
        auxProtocolo = SSRR;
        break;
      default:
        auxProtocolo = 0;
        break;
      }
  
    
   }
   else{
    delay(10);
    }
   
}
