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
  value = Serial.Read();
}

void travel(){
  
  env = CalculoProt(TRVL,motor0);
  Serial.write(env);
  Serial.write(0b11111111);
  Serial.write(0b11111111);
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
  int speedH = 0,speedlL = 0,env; //0 =< SPEED =< 65535
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
  protocolo = CalculoProt(TRVL,motor1); //Manda ao contrário 0b0000001 , esse 1 vai primeiro
  
}

void funcoes(String protocolo ){

  if(protocolo == "1"){
    travel();
    }
  
  else if(protocolo == "2"){
    mover();
    }
   else if(protocolo == "3"){
   
    }
   else if(protocolo == "4"){
    mover();
    }
   else if(protocolo == "5"){
    mover();
    }
   else if(protocolo == "6"){
    mover();
    }
   else if(protocolo == "7"){
    mover();
    }
   else if(protocolo == "8"){
    mover();
    }
   else if(protocolo == "9"){
    mover();
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
