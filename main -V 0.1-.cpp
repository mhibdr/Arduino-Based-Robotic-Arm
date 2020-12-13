// Die liberiry, die wie es benuzen werden

#include <Arduino.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <math.h>

// PIN-Definition

#define S1PIN 0x0a
#define S2PIN 0x0b
#define S3PIN 0x0c
#define S4PIN 0x0d
#define S5PIN 0x09
#define STATE 0x08
#define Joy_Y A0
#define Joy_X A1
#define Joy_B A2
#define PotM  A3
#define L1    200 // Test
#define L2    150 // Test
#define L3    130
#define bthRX 0x3
#define bthTX 0x2
/*
#define MAX_SAngle    90
#define MAX_Speed    10
#define MIN_Speed    2000
#define MAX_Distance 350
*/

// Varibalen und device definition

SoftwareSerial bth( bthTX , bthRX ); //  Arduino RX  , TX
Servo S1 , S2 , S3 , S4 , S5;
String com;
int S1POS , S2POS , S3POS , S4POS , S5POS;
int S1PPOS , S2PPOS , S3PPOS , S4PPOS , S5PPOS;
int X_Cordinates , Y_Cordintes , Z_Cordinates;
int Joy_X_Val , Joy_Y_Val , Joy_B_Val ;
int delay_val = 20;
float angle1 , angle2 , angle3;
float Distance , H;
int joy = 0;

int connectionstate = LOW;

// wenn Atduion ist zu erste dingen die gemacht werden

void setup() {
  
  S1.attach(S1PIN);
  S1PPOS = S1.read();
  S2.attach(S2PIN);
  S2PPOS = S2.read();
  S3.attach(S3PIN);
  S3PPOS = S3.read();
  S4.attach(S4PIN);
  S4PPOS = S4.read();
  S5.attach(S5PIN);
  S5PPOS = S5.read();


  pinMode (STATE , INPUT);
  pinMode (Joy_X, INPUT);
  pinMode (Joy_Y, INPUT);
  pinMode (Joy_B, INPUT);
  pinMode (PotM , INPUT);

  bth.begin(9600);    // Fur HC-06 aber wenn wir HC-05 Benuztuen verden es soll 34800 sein  
  bth.setTimeout(1);
}

//Unser Robot funktonen

void loop() {

  Joy_X_Val = analogRead(Joy_X);
  Joy_Y_Val = analogRead(Joy_Y);
  Joy_B_Val = analogRead(Joy_B);
  delay_val = analogRead(PotM);
  connectionstate = digitalRead(STATE);
  if(connectionstate == HIGH){
    
    com = bth.readString();

    if(com.startsWith("s1")){            // Z servo
      String CMD = com.substring(2 ,com.length());
      S1POS = CMD.toInt();
      if(S1POS > S1PPOS){
        for(int i = S1PPOS ; i < S1POS ; i++){
          S1.write(i);
          delay(delay_val);
        }
      }
      if(S1POS < S1PPOS){
        for(int i = S1PPOS ; i > S1POS ; i--){
          S1.write(i);
          delay(delay_val);
        }
    }
    S1PPOS = S1POS;
  }

    if(com.startsWith("s2")){                   // X servo
      String CMD = com.substring(2 ,com.length());
      S2POS = CMD.toInt();
      if(S2POS > S2PPOS){
        for(int i = S2PPOS ; i < S2POS ; i++){
          S2.write(i);
          delay(delay_val);
        }
      }
      if(S2POS < S2PPOS){
        for(int i = S2PPOS ; i > S2POS ; i--){
          S2.write(i);
          delay(delay_val);
        }
    }
    S2PPOS = S2POS;
  }

    if(com.startsWith("s3")){                     // Rotation Servo , Y servo
      String CMD = com.substring(2 ,com.length());
      S3POS = CMD.toInt();
      if(S3POS > S3PPOS){
        for(int i = S3PPOS ; i < S3POS ; i++){
          S3.write(i);
          delay(delay_val);
        }
      }
      if(S3POS < S3PPOS){
        for(int i = S3PPOS ; i > S3POS ; i--){
          S3.write(i);
          delay(delay_val);
        }
    }
    S3PPOS = S3POS;
  }

    if(com.startsWith("s4")){                         // Gripper Servo
      String CMD = com.substring(2 ,com.length());
      S4POS = CMD.toInt();
      if(S4POS > S4PPOS){
        for(int i = S4PPOS ; i < S4POS ; i++){
          S4.write(i);
          delay(delay_val);
        }
      }
      if(S4POS < S4PPOS){
        for(int i = S4PPOS ; i > S4POS ; i--){
          S4.write(i);
          delay(delay_val);
        }
    }
    S4PPOS = S4POS;
  }

      if(com.startsWith("s5")){                         // Gripper Servo
      String CMD = com.substring(2 ,com.length());
      S5POS = CMD.toInt();
      if(S5POS > S5PPOS){
        for(int i = S5PPOS ; i < S5POS ; i++){
          S5.write(i);
          delay(delay_val);
        }
      }
      if(S5POS < S5PPOS){
        for(int i = S5PPOS ; i > S5POS ; i--){
          S5.write(i);
          delay(delay_val);
        }
      }
    S5PPOS = S5POS;
  }

    if(com.startsWith("speed")){                         // Die Geschwindeigkeit des Servo
      delay_val = com.substring(5 , com.length()).toInt();
    }
    
    connectionstate = digitalRead(STATE);
  }
 
  // Control with Joystick KY-04
  
  if(connectionstate == LOW){
    angle1 = ((90 - S1POS ) * PI) / 180;
    angle2 = ((90 - S2POS ) * PI) / 180;
    Joy_X_Val = map(Joy_X_Val , 0 , 1023 , 180 , 0);
    Joy_Y_Val = map(Joy_Y_Val , 0 , 1023 , 180 , 0);
    Joy_B_Val = map(Joy_B_Val , 0 , 1023 , 0 , 500);
    delay_val = map(delay_val, 0 , 1023 , 20 , 70);

    if(Joy_X_Val > 0 ){

        delay(delay_val);
    }

    if(Joy_Y_Val > 95 && S3PPOS < 180){
        S3PPOS++;
        S3.write(S3POS);
        delay(delay_val);
    }

    if(Joy_X_Val < 0){
      
      delay(delay_val);
    }

    if(Joy_Y_Val < 95 && S3PPOS > 0) {
      S3PPOS--;
      S3.write(S3POS);
      delay(delay_val);
    }
    
    if(Joy_B_Val < 10 && S4PPOS > 90){
      while(Joy_B_Val < 10){
      S4PPOS--;
      S4.write(S4PPOS);
      delay(20);
   }
   }else if(S4PPOS < 90) {
     S4PPOS++;
     S4.write(S4PPOS);
     delay(20);
   }

  connectionstate = digitalRead(STATE);

  }

}



void InverseKinematik(float X , float Y , float Z){
 /*
  angle1 = acos();
  S2PPOS = (angle1 * 180 / PI).toInt();
  angle2 = 
  S4PPOS = (angle2 * 180 / PI).toInt();
  angle3 = 
  S3PPOS = (angle3 * 180 / PI).toInt();
  */
}

int Vorwartskinematik(int S2PPOS , int  S4PPOS , int S3PPOS){
  
  angle1 = ((S2PPOS * PI) / 180);
  angle2 = ((S4PPOS * PI) / 180);
  angle3 = ((S3PPOS * PI) / 180);
  X_Cordinates = ( L1 * cos(angle1) ) + ( L2 * sin(angle2) );
  Y_Cordintes =  (X_Cordinates * cos(angle3));
  Z_Cordinates = ( L1 * sin(angle1) ) + ( L2 * cos(angle2) ) + L3;
  return X_Cordinates , Y_Cordintes , Z_Cordinates;
}