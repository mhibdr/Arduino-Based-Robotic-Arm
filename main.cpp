// Die liberiry, die wie es benuzen werden

#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <math.h>

// PIN-Definition

#define S1PIN 10
#define S2PIN 11
#define S3PIN 12
#define S4PIN 13
#define Joy_Y A0
#define Joy_X A1
#define Joy_B A2
#define PotM  A3
#define L1    200
#define W1    150
#define bthRX 3
#define bthTX 4

// Varibalen und device definition

SoftwareSerial bth( bthRX , bthTX );
Servo S1 , S2 , S3 , S4;
String com;
int S1POS , S2POS , S3POS , S4POS;
int S1PPOS , S2PPOS , S3PPS , S4PPOS;
float angle1 , angle2 , angle3;
int Joy_X_Val = 0;
int Joy_Y_Val = 0;
int delay_val = 0;
float Distance = 0.00;

boolean states = false;

// wenn Atduion ist zu erste dingen die gemacht werden

void setup() {

  S1.attach(S1PIN);
  S2.attach(S2PIN);
  S3.attach(S3PIN);
  S4.attach(S4PIN);

  pinMode (Joy_X, INPUT);
  pinMode (Joy_Y, INPUT);
  pinMode (Joy_B, INPUT);
  pinMode (PotM , INPUT);

  digitalWrite(Joy_B , HIGH);

  Serial.begin(9600);

  bth.begin(38400);  

}

//Unser Robot funktonen

void loop() {

  Joy_X_Val = analogRead(Joy_X);
  Joy_Y_Val = analogRead(Joy_Y);

  if(bth.available() > 0){

    com = bth.readString();

    if(com.startsWith("slide1")){                   // Z servo

      S1POS = com.substring(6 ,com.length()).toInt();
      S1.write(S1POS);
      S1PPOS = S1.read();
      delay(delay_val);
    }

    if(com.startsWith("slide2")){                   // X servo

      S2POS = com.substring(6 ,com.length()).toInt();
      S2.write(S2POS);
      S2PPOS = S2.read();
      delay(delay_val);
    }

    if(com.startsWith("slide3")){                     // Rotation Servo , Y servo

      S3POS = com.substring(6 ,com.length()).toInt();
      S3.write(S3POS);
      S3PPS = S3.read();
      delay(delay_val);
    }

    if(com.startsWith("slide4")){                       // Gripper Servo

      S4POS = com.substring(6 ,com.length()).toInt();
      S4.write(S4POS);
      S4PPOS = S4.read();
      delay(delay_val);
    }

    if(com.startsWith("speed")){                         // Die Geschwindeigkeit des Servo

      delay_val = com.substring(5 , com.length()).toInt();
    }
    
  }

  if(bth.available() < 0){
    angle1 = ((90 - S1POS ) * PI) / 180;
    angle2 = ((90 - S2POS ) * PI) / 180;
    delay_val = analogRead(PotM);

    while(Joy_X_Val > 0 ){

        delay(delay_val);
    }

    while(Joy_Y_Val > 0){
        S3POS++;
        S3.write(S3POS);
        delay(delay_val);
    }

    while(Joy_X_Val < 0){
      
      delay(delay_val);
    }

    while(Joy_Y_Val < 0 ) {
      S3POS--;
      S3.write(S3POS);
      delay(delay_val);
    }
  }
  
}