// motor a aka left
#define enA 9
#define in1 8
#define in2 7

// Motor B connections aka right
#define enB 3
#define in3 5
#define in4 4

int speedonlimit = 517; //when the motors turn forward
int speedofflimit = 490; // when the motor start turning backward

int rightonlimit = 522; //when motors start turning right
int leftonlimit = 502; //when motors start turning left

int maxforwardspeed = 255; //max forward speed
int maxbackspeed = 64; //max backward speed

int forwardmotorstart = 43; //at what pwm value the motors start at
int backwardmotorstart = 33;

int MaxTurningInPlaceSpeed = 180;  //max speed that it can turn in place
int turningstart = 20;



void setup() {
  Serial.begin(9600); //start serial comunication with computer
  pinMode(A0, INPUT); //right/left analog input
  pinMode(A1, INPUT); //up/down analog input
 
  pinMode(enB, OUTPUT); //pwm pin for motor b
  pinMode(enA, OUTPUT); //pwm pin for motor a
  
  pinMode(in1, OUTPUT); //direction control pins
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}



void loop() {
  int turn = analogRead(A0);
  int speed = analogRead(A1);

  if(speed > speedofflimit && speed < speedonlimit) { //turning in place 
    if(turn > rightonlimit) { //turn right
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      
      int rightspeed = map(turn, rightonlimit, 1024, turningstart, MaxTurningInPlaceSpeed);
      
      analogWrite(enB, rightspeed);  
      analogWrite(enA, rightspeed);        
      } 
           
    else if(turn < leftonlimit) { //turn left
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      
      int leftspeed = map(turn, leftonlimit, 0, turningstart, MaxTurningInPlaceSpeed);
      
      analogWrite(enB, leftspeed); // right motor
      analogWrite(enA, leftspeed);  //left motor 
      }

    else{
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);      
      }    
    }


  else if(speed > speedonlimit){ //forward driving
      digitalWrite(in1, HIGH); //spins motors forward 
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);  
          
      int forwardspeed = map(speed, speedonlimit, 1024, forwardmotorstart, maxforwardspeed);
      
      if(turn > rightonlimit) { //turn right
        int forwardright = map(turn, rightonlimit, 1024, 0, forwardspeed);
        analogWrite(enB, forwardspeed - forwardright);
        analogWrite(enA, forwardspeed);       
        }
        
      else if(turn < leftonlimit) { //turn left
        int forwardleft = map(turn, leftonlimit, 0, 0, forwardspeed);
        analogWrite(enB, forwardspeed); //right motor
        analogWrite(enA, forwardspeed - forwardleft);  // left motor       
        } 
               
      else{ //forward no tank turning
        analogWrite(enB, forwardspeed); //right motor
        analogWrite(enA, forwardspeed);  // left motor  
        } 
    }

  

  else if(speed < speedofflimit){ //backward driving
      digitalWrite(in1, LOW); //spins motors backwards 
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      
      int backwardspeed = map(speed, speedofflimit, 0, backwardmotorstart, maxbackspeed); 

      if(turn > rightonlimit) { //turn right
        int backwardright = map(turn, rightonlimit, 1024, 0, backwardspeed);
        analogWrite(enB, backwardspeed - backwardright); //right motor
        analogWrite(enA, backwardspeed);  //left motor        
        }

      else if(turn < leftonlimit) { //turn left
        int backwardleft = map(turn, leftonlimit, 0, 0, backwardspeed);
        analogWrite(enB, backwardspeed); //right motor
        analogWrite(enA, backwardspeed - backwardleft);  // left motor       
        }
        
      else{ //forward no tank turning
        analogWrite(enB, backwardspeed); //right motor
        analogWrite(enA, backwardspeed);  // left motor 
        }
    }  


   else{ //turns motors off
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);     
      }
}


/*
void loop() {
  while(1) {
  int throttle = (analogRead(A1) - 512), turn = (analogRead(A0) - 512);
  int mB_speed = (throttle + turn), mA_speed = (throttle - turn);
  if (mB_speed > 0) {
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
  }
  else {
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
  }

  if (mA_speed > 0) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
  }
  else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
  }
    mB_speed /= 2;
    mA_speed /= 2;
   
    if (mB_speed >= 255) {mB_speed = 255;}
    else if (mB_speed <= -255) {mB_speed = -255;}
    if (mA_speed >= 255) {mA_speed = 255;}
    else if (mA_speed <= -255) {mA_speed = -255;}
     if (mB_speed < 0) {mB_speed *= -1;}
     if (mA_speed < 0) {mA_speed *= -1;}
    analogWrite(enB, mB_speed);
    analogWrite(enA, mA_speed);
    
  }
}
*/
