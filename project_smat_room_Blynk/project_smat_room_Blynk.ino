/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You’ll need:
   - Blynk App (download from AppStore or Google Play)
   - NodeMCU board
   - Decide how to connect to Blynk
     (USB, Ethernet, Wi-Fi, Bluetooth, ...)

  There is a bunch of great example sketches included to show you how to get
  started. Think of them as LEGO bricks  and combine them as you wish.
  For example, take the Ethernet Shield sketch and combine it with the
  Servo example, or choose a USB sketch and add a code from SendData
  example.
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SimpleTimer.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "MQ135.h"
#include <Wire.h>
#define PIN_MQ135 A0
#include <Servo.h>
MQ135 mq135_sensor = MQ135(PIN_MQ135);
//BlynkTimer timer;

SimpleTimer timer;
byte degree[8] = {
  0B01110,
  0B01010,
  0B01110,
  0B00000,
  0B00000,
  0B00000,
  0B00000,
  0B00000
};
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "lLsKmvxXb7mBd2X1lSRrjNLJfiylSGMr";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Leeminhho";
char pass[] = "lemin24049898";
//LiquidCrystal_I2C lcd(0x27,16,4);
const int DHTPIN = D4 ;       
const int DHTTYPE = DHT11; 
int giatriquangtro = 0;
DHT dht(DHTPIN, DHTTYPE); // Cau hinh chan DHT 

//SimpleTimer timer;        // Su dung timer
float h = 0;
float t = 0;

//Ham gui du lieu
// Select your pin with physical button
const int btnPin = D0;
const int btnPin1 = D3;
const int btnPin2 = D9;
const int btnPin3 = D10;
//const int quangtro = D8;
const int bell = D6;
//const int b = D6; //Thiết đặt chân analog đọc quang trở
const int a = D5;
int nguoi = 0;
int servoCua = D7;
int servo = D8;
int cambienmua = D2;
Servo myservo1;
Servo myservo2;

WidgetLED led3(V2);
WidgetLED led2(V6);
WidgetLED led4(V7);


// V3 LED Widget represents the physical button state
boolean btnState = false;
boolean btnState1 = false;
boolean btnState2 = false;
void buttonLedWidget()
{
  // Read button
  boolean isPressed = (digitalRead(btnPin) == LOW);

  // If state has changed...
  if (isPressed != btnState) {
    if (isPressed) {
      led3.off();
    } else {
      led3.on();
    }
    btnState = isPressed;
  }

}
void buttonLedWidget1()
{
    // Read button
  boolean isPressed1 = (digitalRead(btnPin1) == LOW);

  // If state has changed...
  if (isPressed1 != btnState1) {
    if (isPressed1) {
      led2.off();
    } else {
      led2.on();
    }
    btnState1 = isPressed1;
  }

}
void buttonLedWidget2()
{
    // Read button
  boolean isPressed2 = (digitalRead(btnPin2) == LOW);

  // If state has changed...
  if (isPressed2 != btnState2) {
    if (isPressed2) {
      led4.off();
    } else {
      led4.on();
    }
    btnState2 = isPressed2;
  }
}
void sendSensor()
{
  h = dht.readHumidity();     //Doc gia tri do am
  t = dht.readTemperature();  //Doc gia tri nhiet do

  // Gan du lieu vao bien virtual de hien thi len blynk
  // Chi nen gan 10 bien tro xuong
  delay(10);
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
  // Luu y nen ban khong du energy thi co the bo qua v2 va v3
  //Blynk.virtualWrite(V2, led);
  //Blynk.virtualWrite(V3, t);
}
void gas(float temperature, float humidity) {
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);
  Blynk.virtualWrite(V3, ppm);
  Blynk.virtualWrite(V4, correctedPPM);
  Blynk.virtualWrite(V5, PIN_MQ135);
  Serial.print("PPM: ");
 Serial.print(ppm);
 Serial.print("\t Corrected PPM: ");
 Serial.print(correctedPPM);
 Serial.println("ppm");
if(ppm>=15){
  digitalWrite(btnPin,LOW);
  digitalWrite(btnPin1,LOW);
  Blynk.notify("Cảnh báo: có dò khí gas");
  digitalWrite(bell, LOW);
}
else
digitalWrite(bell, HIGH);
}
/*void demnguoi(const int a, const int b){
  if(digitalRead(a)==HIGH&&digitalRead(b)==LOW){
    delay(500);
    if(digitalRead(a)==LOW&&digitalRead(b)==LOW){
      nguoi++;
    }
  }
   if(digitalRead(b)==HIGH&&digitalRead(a)==LOW){
    delay(500);
    if(digitalRead(b)==LOW&&digitalRead(a)==LOW){
      if(nguoi <= 0)
      return;
      nguoi--;
    }
  }
  Serial.println(nguoi);
  lcd.setCursor(0,2);
    lcd.print("So nguoi:  ");
    lcd.print(nguoi);
}*/

void Auto(){
  if(digitalRead(btnPin2) == HIGH){
  //  lcd.setCursor(0,3);
  //  lcd.print("Che do Auto . . .");
    if(digitalRead(a)==HIGH){
    Blynk.notify("Cảnh báo: Có người trong nhà");
    digitalWrite(bell, LOW);

   // giatriquangtro=0;
    return;
    }
   if(digitalRead(a)==LOW){
    digitalWrite(bell, HIGH);
    return;
    }
   /* if(giatriquangtro == 0)
    {
      if (nguoi > 0)
      {
          if(digitalRead(quangtro)==HIGH){
            giatriquangtro=1;
          digitalWrite(btnPin1, LOW);
          }
      }
    }*/
  }
  else{
    // lcd.setCursor(0,3);
   // lcd.print("                 ");
      return;
  }
}
void Cua(){
  if(digitalRead(btnPin3) == HIGH){
    for(int i=0;i<=180;i++){
     myservo2.write(i); 
    }
  }
  if(digitalRead(btnPin3) == LOW){
    for(int j=180;j>=0;j--){
     myservo2.write(j); 
    }
  }
 }
void setup()
{
  // Debug console
  Serial.begin(9600);
 // lcd.init();
 // lcd.backlight();
  //lcd.createChar(1, degree);
  pinMode(PIN_MQ135, INPUT);
  Blynk.begin(auth, ssid, pass);
  dht.begin();                          // Khoi tao DHT
  pinMode(btnPin, INPUT_PULLUP);
 // timer.setInterval(500L, sendSensor); //1s doc cam bien 1 lan
 // timer.setInterval(500L, buttonLedWidget);
  // timer.setInterval(500L, buttonLedWidget1);
    pinMode(btnPin,OUTPUT);
   digitalWrite(btnPin,LOW);
   pinMode(btnPin1,OUTPUT);
   digitalWrite(btnPin1,LOW);
   pinMode(bell,OUTPUT);
   digitalWrite(bell, HIGH);
    pinMode(a, INPUT);
   // Wire.begin(D7, D8); /* join i2c bus with SDA=D7 and SCL=D8 of NodeMCU */
   myservo1.attach(servo);
   myservo2.attach(servoCua);
//  pinMode(b, INPUT);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
// Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  sendSensor();
  buttonLedWidget();
  buttonLedWidget1();
  buttonLedWidget2();
  gas(t,h);
 // timer.run();
  Auto();
   Cua();
  Serial.print("Nhiet Do: ");
  Serial.print(t);
  Serial.print(" Do am: ");
  Serial.print(h);
//  Serial.println(giatriQuangtro);
  Serial.println("");
 /* lcd.setCursor(0,0);
    lcd.print("Nhiet do: ");
    lcd.print(round(t));
    lcd.write(1);
    lcd.print("C");

    lcd.setCursor(0,1);
    lcd.print("Do am: ");
    lcd.print(round(h));
    lcd.print("%");
  //delay (500);*/
 
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
