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

void QPosition(){
  int valH,valL,env;
  env = CalculoProt(QPOS,motor0);
  //ler o valor H e L 
  
}

void QSpeed(){
  int valH,valL,env;
  env = CalculoProt(QSPD,motor0);
  //ler o valor H e L 
  
}
void CArrival(){
  int tolerance = 0; // 0<= tolerance <= 255
  int env,value;
  env = CalculoProt(QSPD,motor0);
  Serial.write(env);
  Serial.write(tolerance);
  value = Serial.read();
}

void travel(){
  int env;
  env = CalculoProt(TRVL,motor0);
  
  Serial.write(0b00100001);
  delay(10);
  Serial.write(0b11111111);
  delay(10);
  Serial.write(0b11111111);
  delay(10);
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
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(9,OUTPUT);
 
}

void funcoes(String protocolo ){

  if(protocolo == "1"){
    QPosition();
    }
  
  else if(protocolo == "2"){
    QSpeed();
    }
   else if(protocolo == "3"){
    CArrival();
    }
   else if(protocolo == "4"){
    travel();
    }
   else if(protocolo == "5"){
    Clear();
    }
   else if(protocolo == "6"){
    SOrienta();
    }
   else if(protocolo == "7"){
     TxDelay();
    }
   else if(protocolo == "8"){
    SMax();
    }
   else if(protocolo == "9"){
    SpeedRamp();
    }
}

void ler(){
  if(Serial.available()>0){
    String x;
    x = Serial.readString();
    funcoes(x);
    }
    return 0;
}

void loop() {
  
  //leituraProtocolo = analogRead(entradaProtocolo);
  //leituraMotor = analogRead(entradaMotor);
   ler();
  
   
     
}
