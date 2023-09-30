#include <Ultrasonic.h>
Ultrasonic ultrasonic(12, 13);
//偵測馬達腳位
byte motorPin_F1 = 4;
byte motorPin_B1 = 6;
byte motorPin_F2 = 10;
byte motorPin_B2 = 9;  

int SensorLeft = 3;      //左感測器輸入腳
int SensorRight =11;      //右感測器輸入腳
int SL;                  //左感測器狀態
int SR;                  //右感測器狀態

int Speed = 130;        //設定速度

void setup() {
  // 定義輸入和輸出 
  Serial.begin (9600);
  pinMode(SensorLeft, INPUT);    //Arduino 讀入左右感測器狀態
  pinMode(SensorRight, INPUT);
    
  pinMode( motorPin_F1 , OUTPUT); //Arduino輸出到馬達腳位
  pinMode( motorPin_B1 , OUTPUT);
  pinMode( motorPin_F2 , OUTPUT);
  pinMode( motorPin_B2 , OUTPUT); 

}

void loop() {

  //紅外線感測器
  SL = digitalRead(SensorLeft);      //讀取感測器狀態值
  SR = digitalRead(SensorRight);

//  Serial.print("SL=");               //測試時，印出感測器狀態值
//  Serial.println(SL);
//  Serial.print("SR=");
//  Serial.println(SR);
//  delay(500);

  if (SL == 0 && SR == 0) {       // 當左右感測器回饋值均為 0，即看到的均為白色，車子停止
    motorStop();
    delay(5);
  }

  if (SL == 1 && SR == 0) {        //當左邊感測器看到黑色，回饋值為0，車子左轉
  motorLeft();
  delay(5);
  }

  if (SL == 0 && SR == 1) {         //當右邊感測器看到黑色，回饋值為0，車子右轉
  motorRight();
  delay (5);
  }

  if (SL == 1 && SR == 1) {         //當左右感測器均看到黑色，回饋值均為1，車子往前
  motorForward();
  delay (5);
  }

}

//停止函示
void motorStop(){   
  digitalWrite( motorPin_F1 , LOW);
  digitalWrite( motorPin_B1 , LOW);
  digitalWrite( motorPin_F2 , LOW);
  digitalWrite( motorPin_B2 , LOW);
}
//後退函式
void motorBackward(){
  digitalWrite( motorPin_F1 , LOW);
  analogWrite( motorPin_B1 , Speed);
  digitalWrite( motorPin_F2 , LOW);
  analogWrite( motorPin_B2 , Speed+110);
}
//前進函式
void motorForward(){
  analogWrite( motorPin_F1 , Speed);
  digitalWrite( motorPin_B1 , LOW);
  analogWrite( motorPin_F2 , Speed+110);
  digitalWrite( motorPin_B2 , LOW);
}

// 右轉函式   
void motorRight(){
  digitalWrite( motorPin_F1 , LOW);
  analogWrite( motorPin_B1 , Speed);
  analogWrite( motorPin_F2 , Speed+110);
  digitalWrite( motorPin_B2 , LOW);
}

// 左轉函式
void motorLeft(){
  analogWrite( motorPin_F1 , Speed);
  digitalWrite( motorPin_B1 , LOW);  
  digitalWrite( motorPin_F2 ,LOW);
  analogWrite( motorPin_B2 ,Speed);
}
