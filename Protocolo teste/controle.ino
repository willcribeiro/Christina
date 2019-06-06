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
int E0 = 2;
int E1 = 3;
int E2 = 4;
int E3 = 5;

int CalculoProt(int Nome, int mot ){ //concatenacao de protocolos
  int x;
  x = Nome*8 + mot;
  return x;
}

void QPosition(){
  int valH,valL,env;
  env = CalculoProt(QPOS,motor0);
  Serial.println("Entrei em 1");
  //ler o valor H e L 
  
}

void QSpeed(){
  int valH,valL,env;
  env = CalculoProt(QSPD,motor0);
  Serial.println("Entrei em 2");
  //ler o valor H e L 
  
}
void CArrival(){
  int tolerance = 0; // 0<= tolerance <= 255
  int env,value;
  env = CalculoProt(QSPD,motor0);
  Serial.write(env);
  Serial.write(tolerance);
  value = Serial.read();
  Serial.println("Entrei em 3");
}

void travel(){
  int env;
  env = CalculoProt(TRVL,motor0);
  Serial.write(env);
  
  Serial.write(0b00000000);
  
  Serial.write(0b01000000);
  
} 

void Clear(){
  int env;
  env = CalculoProt(CLRP,motor0);
  Serial.write(env);
 
}
void SOrienta(){
  int env;
  env = CalculoProt(SREV,motor0);
  Serial.write(env);
  
}
void TxDelay(){
  int env,espera =0; // 0=< delay =< 255
  env = CalculoProt(STXD,motor0);
  Serial.write(env);
  Serial.write(espera);
 
}
void SMax(){
  int speedH = 0,speedL = 0,env; //0 =< SPEED =< 65535
  env = CalculoProt(SMAX,motor0);
  Serial.write(env);
  Serial.write(speedH);
  Serial.write(speedL);
  
  
}
void SpeedRamp(){
  int rate = 0,env; //1 =< rate =< 255
  env = CalculoProt(SSRR,motor0);
  Serial.write(env);
  Serial.write(rate);
}
void setup() {
  Serial.begin(19200);
  pinMode((E0,E1,E2,E3),INPUT);
  
}

void funcoes(char entrada){
  
  if(entrada == '1'){ //0001
    QPosition();
    }
  
  else if(entrada == '2'){
    QSpeed();
    }
   else if(entrada == '3'){
    CArrival();
    }
   else if(entrada == '4'){
    travel();
    }
   else if(entrada == '5'){
    Clear();
    }
   else if(entrada == '6'){
    SOrienta();
    }
   else if(entrada == '7'){
    TxDelay();
    }
   else if(entrada == '8'){
    SMax();
    }
   else if(entrada == '9'){
    SpeedRamp();
    }
}

void leitura(){
  char x;
  while(Serial.available()>0){
    x = Serial.read();
    funcoes(x);
    }
}


void loop() {
  leitura();
  delay(1000);
   
     
}
