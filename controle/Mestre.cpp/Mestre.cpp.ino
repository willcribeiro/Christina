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
  while(Serial.available()> 0){
    x = Serial.read();
    Serial.read(); 
    Serial.println(x);
    Serial.println("wow");
    if(x == '1'){
      
      Serial.println("Entrei funcao 1");
      Serial.println("---------x----------x");
      delay(1000);
     
    }    
    else if(x == '2'){
      
      Serial.println("Entrei funcao 2");
      Serial.println("---------x----------x");
      delay(1000);
     
    }  

    else if(x == '3'){
      
      Serial.println("Entrei funcao 3");
      Serial.println("---------x----------x");
      delay(1000);
     
    }  
   
   
  }
 
}
