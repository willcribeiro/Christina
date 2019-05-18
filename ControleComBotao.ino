int botao = 2;
int led = 8;
int estado = 0;
void setup() {
 Serial.begin(19200);
 pinMode(botao,INPUT);
 pinMode(led,OUTPUT);

}

void loop() {
  estado = digitalRead(botao);
  if(estado == HIGH){
    digitalWrite(led, HIGH);
    //envio dos comandos
    Serial.write(0b00100000);
    Serial.write(0b11111111);
    Serial.write(0b11111111);
    }
  digitalWrite(led, LOW);
}
