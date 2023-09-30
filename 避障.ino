#include <Ultrasonic.h>
Ultrasonic ultrasonic(12, 13);

byte motorPin_F1 = 4;
byte motorPin_B1 = 6;
byte motorPin_F2 = 10;
byte motorPin_B2 = 9;   //馬達
const int trigPin = 13;    //超音波模組觸發
const int echoPin = 12;    //超音波模組接收腳
unsigned long duration , cm , inches;    
int distance;


int Speed = 140;
  
void setup() {
  // 定義輸入和輸出 
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);          
  pinMode(echoPin, INPUT);
  
  pinMode( motorPin_F1 , OUTPUT);
  pinMode( motorPin_B1 , OUTPUT);
  pinMode( motorPin_F2 , OUTPUT);
  pinMode( motorPin_B2 , OUTPUT); 

}

void loop() {
  //印出超音波感測出前方障礙物的距離
  distance = ultrasonic.read();
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  delay(500);

  //超音波感測器
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);     // 給 Trig 高電位，持續 10微秒
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin , INPUT);
  duration = pulseIn(echoPin, HIGH);
  cm = (duration/2) / 29.1;     // 將時間換算成距離 cm

  if(cm > 25){
    motorForward(); 
  }
  else{
    motorStop();
    delay(100);
    motorBackward();
    delay(1000);
    motorStop();
    delay(50);
    motorRight();
    delay(500);
  }
}

void motorStop(){
  digitalWrite( motorPin_F1 , LOW);
  digitalWrite( motorPin_B1 , LOW);
  digitalWrite( motorPin_F2 , LOW);
  digitalWrite( motorPin_B2 , LOW);
}

void motorBackward(){
  digitalWrite( motorPin_F1 , LOW);
  analogWrite( motorPin_B1 , Speed+10);
  digitalWrite( motorPin_F2 , LOW);
  analogWrite( motorPin_B2 , Speed);
}

void motorForward(){
  analogWrite( motorPin_F1 , Speed+10);
  digitalWrite( motorPin_B1 , LOW);
  analogWrite( motorPin_F2 , Speed);
  digitalWrite( motorPin_B2 , LOW);
}

// 右轉   
void motorRight(){
  digitalWrite( motorPin_F1 , LOW);
  digitalWrite( motorPin_B1 , LOW);
  analogWrite( motorPin_F2 , Speed);
  digitalWrite( motorPin_B2 , LOW);
}

// 左轉
void motorLeft(){
  analogWrite( motorPin_F1 , Speed);
  digitalWrite( motorPin_B1 , LOW);  
  digitalWrite( motorPin_F2 ,LOW);
  digitalWrite( motorPin_B2 ,LOW);
}
