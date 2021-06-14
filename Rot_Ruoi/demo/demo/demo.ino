int moter  = 2;
int bientro = A2;
int cambien = 12;
unsigned long time;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(moter, OUTPUT);
pinMode(bientro, INPUT);
pinMode(cambien, INPUT);
digitalWrite(moter, LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
Serial.println(analogRead(bientro));
int i = analogRead(bientro);
int tem = 0;
while(digitalRead(cambien)!= HIGH){
  if(tem == 0){
    time = millis();
    while(digitalRead(cambien)== LOW && (millis()-time)<(i+100)){
      digitalWrite(moter, HIGH);
    }
    digitalWrite(moter, LOW);
    tem = 1;
    //return;
    delay(1000);
    } 
  }
}
