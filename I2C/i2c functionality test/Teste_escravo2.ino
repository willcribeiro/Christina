//Programa: Comunicacao I2C Arduino e Raspberry Pi
//Autor: Arduino e Cia
#include <Wire.h>
char str[15];
int valor;
void setup()
{
  Serial.begin(9600);
  Wire.begin(0x18);
  Wire.onRequest(requestEvent);
}
void requestEvent()
{
  valor = analogRead(A0);
  Serial.println("Requisicao recebida!");
  Serial.println(valor);
  sprintf(str, "Valor: %4dn", valor);
  Wire.write(str);
}
void loop()
{
  delay(50);
  }
