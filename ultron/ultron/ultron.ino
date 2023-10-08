#include<Servo.h>

Servo head;
Servo l_hand;
Servo r_hand;

// define sonar sensor's pins
int trigPin = 4;
int echoPin = 5;
const int irPin = 7;
const int servo1 = 2;
const int servo2 = 8;
const int servo3 = 9;
const int thresholdTemp = 25;
byte val = "";
long duration;
int distance;
void setup() {

  Serial.begin(9600); // for communicating via serial port with Python
  
  // put your setup code here, to run once:
   pinMode(trigPin, OUTPUT); 
   pinMode(echoPin, INPUT);
  head.attach(servo1);
  pinMode(irPin, INPUT);
   head.write(0);
   l_hand.attach(servo2);
   l_hand.write(0);
  r_hand.attach(servo3);
  r_hand.write(0);

}
void hi(){
    head.write(0);
    r_hand.write(90);
    delay(2);
  }
  void Meassure(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    duration =  pulseIn(echoPin, HIGH);
    distance = duration * 0.0344 / 2;
     Serial.print("Distance: ");
    Serial.print(distance); 
    Serial.println(" cm");
    delay(1);
  }
 void Temp(){
  int irValue = analogRead(irPin);
  if (irValue =  thresholdTemp){
    Serial.print("Temperature (c): ");
    Serial.println(thresholdTemp);
  }
   else{
   float tempC = irValue * 0.48875855;
    Serial.println(tempC);
    delay(10); 
 }}
void hands_up(){
  head.write(0);
 r_hand.write(90);
 l_hand.write(90);
 delay(2);
}
void upper_cut(){
  r_hand.write(180);
  delay(2);
}
void punch(){
  l_hand.write(90);
  delay(2);
}
void look_left(){
  head.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available() > 0)  
  {
    val = Serial.read();
    
    if(val == 'T'){
      Temp(); 
    }
    if(val == 'M'){
      Meassure();
    }
    if(val == 'l'){
      look_left();
    }

    if(val == 'h'){
      // do hi
       hi();
    }
    if(val == 'p'){
       punch();
    }
    if(val == 'u'){
      hands_up();
      delay(3);
    }
    if(val == 'U'){
      upper_cut();
      delay(2);
   
    }
  }  
}
