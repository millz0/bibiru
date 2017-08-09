#include <VarSpeedServo.h>

#define Rtone0 300//50//基準
#define Rtone1 270//66//止
#define Rtone2 285//50//足
#define Rtone3 300//80//腕
#define Rtone4 315//100//頭
#define Rtone5 330//110//箱

#define Wait1 2000
#define Wait2 2000
#define Wait3 2000
#define Wait4 2000
#define Wait5 2000

VarSpeedServo s_s;
VarSpeedServo k_s;
VarSpeedServo ar_s;
VarSpeedServo al_s;

float oto = 0;
float oto2 = 0;
int hf=0;
float ot[21];
void setup() {
 
  Serial.begin(9600) ;          // パソコン(ArduinoIDE)とシリアル通信の準備を行う
 
  pinMode(7, OUTPUT);//足：歩行DC
 
  ADCSRA = ADCSRA & 0xf8;
  ADCSRA = ADCSRA | 0x04;
  
  k_s.attach(5);//蓋閉開38-128
  k_s.write(128, 2, true);
  
  s_s.attach(3);//昇降//0-53-90
  s_s.write(10, 10, true);
  
  ar_s.attach(6);//右腕　サーボ//12-83
  ar_s.write(83, 20, true);
  
  al_s.attach(9);//左腕　サーボ//88-10 閉－開
  al_s.write(10, 20, true);

  digitalWrite(7, HIGH);
  delay(2000);
}

void bb() {
  while (oto >= Rtone1) {
      digitalWrite(7, LOW);
      while (oto >= Rtone2) { //足
          s_s.write(53, 10, true);

          while (oto >= Rtone3) { //腕
              ar_s.write(12, 10, false);
              al_s.write(88, 10, true);

              while (oto >= Rtone4) { //頭
                  s_s.write(90, 10, true);

                  while(oto>=Rtone5){//蓋
                      hf++;
                      k_s.write(40, 50, true);
                      if (delays(Wait5, 5))continue;
                      //delay(2000);
                      k_s.write(120, 10, true);
                      if(hf>2){
                          while(hf>0){
                              hf--;
                              k_s.write(40, 100, true);
                              k_s.write(120, 100, true);
                          }                
                      }             
                      break;                
                  }//5
                  
                  if (oto < Rtone5) {if (delays(Wait4, 4))continue;}
                  //delay(2000);
                  s_s.write(53, 100, true);
                  break;
              }//4
      
              if (oto < Rtone4) {        if (delays(Wait3, 3))continue;      }
              //delay(2000);
              ar_s.write(83, 80, false);
              al_s.write(10, 80, true);
              break;
          }//3
    
          if (oto < Rtone3) {      if (delays(Wait2, 2))continue;    }
          //delay(2000);
          s_s.write(10, 60, true);
          break;
      }//2
  
      if (oto < Rtone2) {    if (delays(Wait1, 1))continue;  }
      //delay(2000);
      digitalWrite(7, HIGH);
      break;
  }
}
int delays(long wait, int lb) {
  uint32_t st = millis();
  wait += st;
  oto2=0;
  while ((wait > millis())) {
      Serial.print(oto2 = analogRead(5));

       switch (lb) {
          case 1: 
                if ((oto2 >= Rtone1) ){oto=oto2;return 1;}  break;
          case 2: 
                if ((oto2 >= Rtone2) ){oto=oto2; return 1;} break;
           case 3: 
                if ((oto2 >= Rtone3)){oto=oto2;return 1;} break;
          case 4: 
                if ((oto2 >= Rtone4) ){oto=oto2;return 1;}  break;
        case 5: 
                if ((oto2 >= Rtone5) ){oto=oto2;return 1; } break;
     }
     
   }

   return 0;
}
void loop() {
  /*
    uint32_t StartTime=millis();
    for(int i=0; i<10000; i++) { oto=analogRead(5);   }  uint32_t EndTime=millis();
    Serial.println(EndTime-StartTime);
  */
  Serial.println(oto = analogRead(5)); // アナログ５番ピン読込み値を表示する
  if (oto > Rtone1) { //停止
    Serial.print(oto); Serial.print(" ");
    Serial.print(ot[0] = analogRead(5)); Serial.print(" ");
    Serial.print(ot[1] = analogRead(5)); Serial.print(" ");
    Serial.print(ot[2] = analogRead(5)); Serial.print(" ");
    Serial.print(ot[3] = analogRead(5)); Serial.print(" ");
    Serial.print( ot[4] = analogRead(5)); Serial.print(" ");
    Serial.print( ot[5] = analogRead(5)); Serial.print(" ");
    Serial.print( ot[6] = analogRead(5)); Serial.print(" ");
    Serial.print( ot[7] = analogRead(5)); Serial.print(" ");
    Serial.print( ot[8] = analogRead(5)); Serial.print(" ");
    Serial.print( ot[9] = analogRead(5)); Serial.print(" ");
    Serial.print(ot[10] = analogRead(5)); Serial.print(" ");
   
    ot[10] = ot[0] + ot[1] + ot[2] + ot[3] + ot[4] + ot[5] + ot[6] + ot[7] + ot[8] + ot[9] + oto;
    oto=ot[10]/11;
    Serial.println(oto);
    bb();
    delay(500);
  }

}
