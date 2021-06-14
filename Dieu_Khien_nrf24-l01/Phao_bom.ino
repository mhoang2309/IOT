#include <VirtualWire.h>
int btn = 9;
byte text[2] = {0, 0};
void setup()
{
  Serial.begin(9600);
  Serial.println("Ready.........");
  vw_set_ptt_inverted(true);
  vw_setup(1024);
  vw_set_tx_pin(7);
  pinMode(btn, INPUT);
} 

void loop()
{
  if(digitalRead(btn)==LOW){
      text[0]=0;
      vw_send((byte *)text, sizeof(text));
  vw_wait_tx();
    Serial.println(text[0]);
//  Serial.println(digitalRead(btn));
  //delay(10);
  }
   if(digitalRead(btn)==HIGH){
   text[0]=1;
      vw_send((byte *)text, sizeof(text));
  vw_wait_tx();
    Serial.println(text[0]);
 // Serial.println(digitalRead(btn));
 // delay(10);
   }
   text[1]=0;
      vw_send((byte *)text, sizeof(text));
  vw_wait_tx();
    Serial.println(text[1]);
//  Serial.println(digitalRead(btn));
  //delay(10);
   text[1]=1;
      vw_send((byte *)text, sizeof(text));
  vw_wait_tx();
    Serial.println(text[1]);
 // Serial.println(digitalRead(btn));
 // delay(10);
 text[1]=0;
      vw_send((byte *)text, sizeof(text));
  vw_wait_tx();
}
/*  if(digitalRead(btn)==LOW){
    text[0]='0';
      vw_send((byte *)text, sizeof(text));
  vw_wait_tx();
    Serial.println(text[0]);
  Serial.println(digitalRead(btn));
  }
    if(digitalRead(btn)==HIGH){
      text[0]='1';
      vw_send((byte *)text, sizeof(text));
  vw_wait_tx();
    Serial.println(text[0]);
  Serial.println(digitalRead(btn));
  }*/
