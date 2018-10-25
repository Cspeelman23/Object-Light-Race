#include <Adafruit_NeoPixel.h>
#define PIN 6
int countB = -1;
int countR = 32;

bool pressB =true;
bool pressR = true;

bool win = false;
int who = 0; //no winner yet
Adafruit_NeoPixel strip = Adafruit_NeoPixel(32, PIN, NEO_GRB + NEO_KHZ800);



void setup() {
  Serial.begin (9600);
  strip.begin();
  strip.show(); // start all pixels "off"
  pinMode(3,INPUT); //red button
  pinMode(2,INPUT); //blue button
  pinMode(6,OUTPUT);
  //pinMode RGB setup
  pinMode(9,OUTPUT);//red
  pinMode(10,OUTPUT);//green
  pinMode(11,OUTPUT);//blue

}
//______________________________
void loop() {

  strip.setBrightness(14);
 int bluebutton = digitalRead(2);
 int redbutton = digitalRead(3);
  
  if(bluebutton == HIGH && pressB==true){
    delay(10);
    pressB= false;
    Serial.println("blue");
    countB++;
    Serial.println(countB);
  }else if(bluebutton == LOW){
    pressB = true;
    
  }
   if(redbutton == HIGH && pressR == true){
    delay(10);
    pressR = false;
    Serial.println("red");
    countR--;
    Serial.println(countR);
  }else if(redbutton == LOW){
    pressR = true;
  }
//_________________________

if(countB <=15){
  strip.setPixelColor(countB,0,0,255);
  strip.show();  
}

if(countR >=16){
  strip.setPixelColor(countR,255,0,0);
  strip.show();  
}
  
//_________________________
  if(countB >= 16 && win==false){
     //digitalWrite(RGB,HIGH);
     Serial.println("BLUE WIN");
     who = 1; //blue wins
     win = true;
  }

  if(countR <= 15 && win==false){
    //digitalWrite(RGB,HIGH);
    Serial.println("RED WIN");
    who = 2; //red wins
    win = true;   
  }

if(win == true){
// don't light up the rest of the loser's lights?
  if(who == 1){//if blue won
        digitalWrite(9,LOW);
        digitalWrite(10,LOW);
        digitalWrite(11,HIGH);//blue
  }
  else if(who == 2){//if red won
        digitalWrite(9,HIGH); //red
        digitalWrite(10,LOW);
        digitalWrite(11,LOW);
  }
  else{//error or magical tie
        digitalWrite(9,LOW);
        digitalWrite(10,HIGH);//green
        digitalWrite(11,LOW);
    }
    delay(5000);
  
    //reset lights
       //RGB
       digitalWrite(9,LOW);
       digitalWrite(10,LOW);
       digitalWrite(11,LOW);//off
       //strip
       for(int i=0; i<32; i++){
          //turn off
           strip.setPixelColor(i, 0, 0, 0);
           //strip.setBrightness(0);
           strip.show();
       }
     countB = -1;
     countR = 32;
     win = false;
    setup () ;
    return ;

  
}


 


  

}
