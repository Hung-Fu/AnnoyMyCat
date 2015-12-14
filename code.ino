#include<IRremote.h>
#include<Servo.h>

// == IR variable == 
int RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;
//==================

//===== motor variable======
enum Dir{
  STOP,
  FORWARD,                                                                           
  BACKWARD,
  RIGHT,
  LEFT,
  Move_servo
};           

Dir signal = STOP;

int motorIn1 = 7;
int motorIn2 = 8;
int motorIn3 = 12;
int motorIn4 = 13;

int high_v = 100;
// ===================

// =====  servo  variable ====
Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;
int angle = 20;  // from 20 to 120
int direct = 1;

boolean case1_flag = true;

int pos1 = 20;
int pos2 = 20;
int pos3 = 20;
int pos4 = 20;
int time_delay = 0;
int direct1 = 1;
int direct2 = 1;
int direct3 = 1;
int direct4 = 1;

int random_Num;
int random_old = 0;
//==================

void setup() {
  Serial.begin(9600);                       
  irrecv.enableIRIn(); // Start the receiver 
  
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);

  myServo1.attach(5);
  myServo2.attach(6);
  myServo3.attach(9);
  myServo4.attach(10); 
  
  myServo1.write(20);
  myServo2.write(20);
  myServo3.write(20);
  myServo4.write(20);  

}

void moveTire(){
  
  switch(signal){
    case STOP:
      digitalWrite(motorIn1,LOW);
      digitalWrite(motorIn2,LOW);
      digitalWrite(motorIn3,LOW);
      digitalWrite(motorIn4,LOW); 
      delay(150);
      break;
      
    case FORWARD:
      digitalWrite(motorIn1,HIGH);
      digitalWrite(motorIn2,LOW);
      digitalWrite(motorIn3,HIGH);
      digitalWrite(motorIn4,LOW); 
      delay(150);
      break;
      
    case RIGHT:
      digitalWrite(motorIn1,HIGH);
      digitalWrite(motorIn2,LOW);
      digitalWrite(motorIn3,LOW);
      digitalWrite(motorIn4,LOW); 
      delay(150);
      break; 
      
    case BACKWARD:
      digitalWrite(motorIn1,LOW);
      digitalWrite(motorIn2,HIGH);
      digitalWrite(motorIn3,LOW);
      digitalWrite(motorIn4,HIGH); 
      delay(150);
      break;
      
    case LEFT:
      digitalWrite(motorIn1,LOW);
      digitalWrite(motorIn2,LOW);
      digitalWrite(motorIn3,HIGH);
      digitalWrite(motorIn4,LOW); 
      delay(150);
      break;
  }
  
}

void irGet(){
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    long value = results.value;
    
    if(value == 0xFF18E7)
      signal = FORWARD;
    else if (value == 0xFF5AA5)
      signal = RIGHT;
    else if (value == 0xFF4AB5)
      signal = BACKWARD;
    else if (value == 0xFF10EF)
      signal = LEFT;
    else if (value == 0xFF38C7)
      signal = STOP;
    else if (value == 0xFF7A85){
      signal = Move_servo;
      do{
      random_Num = random(4);
      }while(random_Num == random_old);

      random_old = random_Num;
    }
    
    irrecv.resume(); // Receive the next value
  }
} 

void servoMove(){

  if(signal == Move_servo){
      
      switch(random_Num){
        case 0: 
          case_1();  // all down
          break;
            
        case 1:
          case_2();  // wave down
          break;

        case 2:
           case_3();  // servo1 & servo2 down
           break;
           
        case 3:
           case_4(); // servo3 & servo4 down
           break;
           
        default:
           break;
      }
      
  }
  else {
      myServo1.write(20); 
      myServo2.write(20); 
      myServo3.write(20); 
      myServo4.write(20);

      angle = 20;
      pos1 = 20;
      pos2 = 20;
      pos3 = 20;
      pos4 = 20;

      time_delay = 0;
   }

} 

  void case_1(){
    
    if(angle<=20) {
      direct = 1;
    }
    else if(angle >= 120){
      direct = -1;
    }
  
    angle = angle + direct;

    myServo1.write(angle);
    myServo2.write(angle);
    myServo3.write(angle);
    myServo4.write(angle); 

    delay(5);    
  }

  void case_2(){
    
      case_2_servo1();

      time_delay = time_delay + 1;

      case_2_servo2();

      case_2_servo3();
      
      case_2_servo4();

      delay(5);
  }

  void case_2_servo1(){
      if(pos1<=20) {
        direct1 = 1;
      }
      else if(pos1 >= 120){
        direct1 = -1;
      }
  
      pos1 = pos1 + direct1;
      myServo1.write(pos1);
  }

  void case_2_servo2(){
    if(time_delay > 20){
        if(pos2<=20) {
          direct2 = 1;
        }
        else if(pos2 >= 120){
          direct2 = -1;
        }
  
        pos2 = pos2 + direct2;
        myServo2.write(pos2);
    }
  }
  
  void case_2_servo3(){
    if(time_delay > 40){
      if(pos3 <= 20) {
          direct3 = 1;
        }
        else if(pos3 >= 120){
          direct3 = -1;
        }
  
        pos3 = pos3 + direct3;
        myServo3.write(pos3);
    }
  }

  void case_2_servo4(){
    if(time_delay > 60){
        if(pos4<=20) {
            direct4 = 1;
          }
          else if(pos4 >= 120){
            direct4 = -1;
          }
    
          pos4 = pos4 + direct4;
          myServo4.write(pos4);
    }
  }

   void case_3(){
    
    if(angle<=20) {
      direct = 1;
    }
    else if(angle >= 120){
      direct = -1;
    }
  
    angle = angle + direct;
    myServo1.write(angle);
    myServo2.write(angle); 

    delay(5);    
  }

  void case_4(){
    
    if(angle<=20) {
      direct = 1;
    }
    else if(angle >= 120){
      direct = -1;
    }
  
    angle = angle + direct;
    myServo3.write(angle);
    myServo4.write(angle); 

    delay(5);
    
  }
  
  void loop() {
  irGet();
  moveTire();
  servoMove();
  }
