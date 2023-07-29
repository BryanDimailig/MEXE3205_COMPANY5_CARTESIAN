#include<IRremote.h>
#include <ESP32Servo.h>

int irpin = 21;
int t= 1000;
const int savepb1 = 0xBA45FF00, savepb2 = 0xB946FF00, playpb = 0xE31CFF00, stop = 0xB847FF00;
int save1, save2;
bool savemode1 = false, savemode2 = false, playmode = true;
int aspeed = 20, bspeed = 20;

int apos1, apos2, apos3, apos4;
int astartpos1, astartpos2, astartpos3, astartpos4;

int bpos1, bpos2, bpos3, bpos4;
int bstartpos1, bstartpos2, bstartpos3, bstartpos4;

int pos4, pos5, pos6, pos7;

const int pot1 = 2, spin1 = 4;
float serpos1 = 0, asavepos1 = 0, bsavepos1 = 0;
float val1;
Servo sv1;

const int pot2 = 25, spin2 = 22;
float serpos2 = 0, asavepos2 = 0, bsavepos2 = 0;
float val2;
Servo sv2;

const int pot3 = 26, spin3 = 17;
float serpos3 = 0, asavepos3 = 0, bsavepos3 = 0;
float val3;
Servo sv3;

const int pot4 = 32, spin4 = 19;
float serpos4 = 0, asavepos4 = 0, bsavepos4 = 0;
float val4;
Servo sv4;

IRrecv IR(irpin);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  IR.enableIRIn();
  Serial.begin(9600);
  
  pinMode(pot1, INPUT);
  pinMode(spin1, OUTPUT);
  sv1.attach(spin1);
  sv1.write(serpos1);
  delay(t);

  pinMode(pot2, INPUT);
  pinMode(spin2, OUTPUT);
  sv2.attach(spin2);
  sv2.write(serpos2);
  delay(t);

  pinMode(pot3, INPUT);
  pinMode(spin3, OUTPUT);
  sv3.attach(spin3);
  sv3.write(serpos3);
  delay(t);

  pinMode(pot4, INPUT);
  pinMode(spin4, OUTPUT);
  sv4.attach(spin4);
  sv4.write(serpos4);
  delay(t);
}

void loop() {
  // put your main code here, to run repeatedly:
  val1 = analogRead(pot1);
  serpos1 = ((180./4095.)*val1);
  sv1.write(serpos1);

  val2 = analogRead(pot2);
  serpos2 = ((90./4095.)*val2);
  sv2.write(serpos2);

  val3 = analogRead(pot3);
  serpos3 = ((180./4095.)*val3);
  sv3.write(serpos3);

  val4 = analogRead(pot4);
  serpos4 = ((180./4095.)*val4);
  sv4.write(serpos4);
 
  if(IR.decode()){
    Serial.println(IR.decodedIRData.decodedRawData, HEX);
  {
   if(IR.decodedIRData.decodedRawData == savepb1){
     Serial.println("SLOT1");
     savemode1 = true;
     asavepos1 = serpos1;
     asavepos2 = serpos2;
     asavepos3 = serpos3;
     asavepos4 = serpos4;

     delay(t);
     Serial.print("AsavePos1 = ");
     Serial.println(asavepos1);
     Serial.println();
     Serial.print("AsavePos2 = ");
     Serial.println(asavepos2);
     Serial.println();
     Serial.print("AsavePos3 = ");
     Serial.println(asavepos3);
     Serial.println();
     Serial.print("AsavePos4 = ");
     Serial.println(asavepos4);
     Serial.println();
   }
   if(IR.decodedIRData.decodedRawData == savepb2){
     Serial.println("SLOT2");
     savemode2 = true;
     bsavepos1 = serpos1;
     bsavepos2 = serpos2;
     bsavepos3 = serpos3;
     bsavepos4 = serpos4;
  
     delay(t);
     Serial.print("BsavePos1 = ");
     Serial.println(bsavepos1);
     Serial.println();
     Serial.print("BsavePos2 = ");
     Serial.println(bsavepos2);
     Serial.println();
     Serial.print("BsavePos3 = ");
     Serial.println(bsavepos3);
     Serial.println();
     Serial.print("BsavePos4 = ");
     Serial.println(bsavepos4);
     Serial.println();
   }
   if(IR.decodedIRData.decodedRawData == stop){
     Serial.println("STOP");
     playmode = false;
   }
   if(IR.decodedIRData.decodedRawData == playpb){
     Serial.println("REPLAY");
     playmode = true;
     while(playmode){
       savemode1 = false;
       savemode2 = false;
       astartpos1 = sv1.read();
       for(apos1 = astartpos1; apos1 <= asavepos1; apos1 += aspeed)
       {
        sv1.write(apos1);
        Serial.println("1");
        delay(500);
       }
       astartpos2 = sv2.read();
       for(apos2 = astartpos2; apos2 <= asavepos2; apos2 += aspeed)
       {
        sv2.write(apos2);
        Serial.println("2");
        delay(500);
       }
       astartpos3 = sv3.read();
       for(apos3 = astartpos3; apos3 <= asavepos3; apos3 += aspeed)
       {
        sv3.write(apos3);
        Serial.println("3");
        delay(500);
       }
       astartpos4 = sv4.read();
       for(apos4 = astartpos4; apos4 <= asavepos4; apos4 += aspeed)
       {
        sv4.write(apos4);
        Serial.println("4");
        delay(500);
       }

       //bstartpos1 = sv1.read();
       for(bpos1 = asavepos1; bpos1 <= bsavepos1; bpos1 += bspeed)
       {
        sv1.write(bpos1);
        Serial.println("5");
        delay(500);
       }
       //bstartpos2 = sv2.read();
       for(bpos2 = asavepos2; bpos2 <= bsavepos2; bpos2 += bspeed)
       {
        sv2.write(bpos2);
        Serial.println("6");
        delay(500);
       }
       //bstartpos3 = sv3.read();
       for(bpos3 = asavepos3; bpos3 <= bsavepos3; bpos3 += bspeed)
       {
        sv3.write(bpos3);
        Serial.println("7");
        delay(500);
       }
       //bstartpos4 = sv4.read();
       for(bpos4 = asavepos4; bpos4 <= bsavepos4; bpos4 += bspeed)
       {
        sv4.write(bpos4);
        Serial.println("8");
        delay(500);
       }

       for(pos4 = bpos1; pos4 >= astartpos1; pos4 -= aspeed)
       {
        sv1.write(pos4);
        Serial.println("9");
        delay(500);
       }
       for(pos5 = bpos2; pos5 >= astartpos2; pos5 -= aspeed)
       {
        sv2.write(pos5);
        Serial.println("10");
        delay(500);
       }
       for(pos6 = bpos3; pos6 >= astartpos3; pos6 -= aspeed)
       {
        sv3.write(pos6);
        Serial.println("11");
        delay(500);
       }
       for(pos7 = bpos4; pos7 >= astartpos4; pos7 -= aspeed)
       {
        sv4.write(pos7);
        Serial.println("12");
        delay(500);
       }
       if (IR.decode()) {
       // Check if the received button press interrupts the loop
        if (IR.decodedIRData.decodedRawData == 0xB847FF00) {
        playmode = false;
      }
      IR.resume();  // Receive the next IR signal
    }
   }
   }
  }
   IR.resume();
  }
}