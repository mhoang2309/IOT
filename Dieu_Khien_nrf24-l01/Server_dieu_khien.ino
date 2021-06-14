#include <VirtualWire.h>
byte msg[VW_MAX_MESSAGE_LEN];
byte msgLen = VW_MAX_MESSAGE_LEN;
int relay = 13;
int led = 12;
int led1 = 11;
unsigned long time1 = 0;
unsigned long time2 = 0;
unsigned long time3 = 0;
int tem = 0;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
  Serial.println("READY..........");
  vw_setup(1024);
  vw_set_rx_pin(2);
  vw_rx_start();
  pinMode(relay, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
if (vw_get_message(msg, &msgLen))
  {
      digitalWrite(led1, LOW); 
     // digitalWrite(relay, msg[0]);
      digitalWrite(led, msg[1]);
      if(msg[0]==1 && time1==0){
          time1 = millis()/1000;
     // }
     // if(msg[0]==1 && time2==0){
          time2 =time1;
      }
      if(msg[0]==1 && (millis()/1000)-time1>=5 && tem==0)
      digitalWrite(relay, HIGH);
      digitalWrite(led, msg[1]);
      if(msg[0]==0){
        time1=0;
        digitalWrite(relay, LOW);
      }
      if(millis()/1000 - time2 >= 10){
        time2=0;
        tem=1;
        digitalWrite(relay, LOW);
      }
      if(msg[0]==0){
        time1=0;
        tem=0;
        digitalWrite(relay, LOW);
      }
  time3 = millis()/1000;
  }
  else{
    digitalWrite(led1, HIGH);
      if(digitalRead(relay)==HIGH){
        if( millis()/1000 - time3 == 10){
           digitalWrite(relay, LOW);
           
        }
      }
  }
  Serial.print("time:");
   Serial.print(millis()/1000);
   Serial.print("  relay:");
   Serial.print(digitalRead(relay));
  Serial.print("    ");
  Serial.print(msg[0]);
  Serial.print("   time1: ");
  Serial.print(time1);
    Serial.print("   time2: ");
  Serial.print(time2);
    Serial.print("   time3: ");
  Serial.print(time3);
  Serial.println("");
  }
