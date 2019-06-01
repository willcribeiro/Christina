int X0 = 2;
int X1 = 3;
int X2 = 4;
int X3 = 5;
void setup() {
  Serial.begin(9600);
  pinMode((X0,X1,X2,X3),OUTPUT);
}

void loop() {
  char x;
  Serial.println("ENtra ai");
  if(Serial.available()> 0){
    x = Serial.read();
    
    delay(100);
    Serial.println(x);
    if(x == '1'){
      digitalWrite(X0,LOW);
      digitalWrite(X1,LOW);
      digitalWrite(X2,LOW);
      digitalWrite(X3,HIGH);
      Serial.println("Entrei");
      Serial.println("---------x----------x");
      delay(1000);
    }    
    else{
      Serial.println(x);
      delay(1000);
    }
  }
  else{
      digitalWrite(X0,LOW);
      digitalWrite(X1,LOW);
      digitalWrite(X2,LOW);
      digitalWrite(X3,LOW);
      }


}
