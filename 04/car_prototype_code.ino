#define LEFT 6
#define RIGHT 5

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEFT, OUTPUT);
  pinMode(RIGHT, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  //make it run for a certain amount of time
  moveStraight(1000);
  stopMove(1000);
  moveLeft(1000);
  stopMove(1000);
  moveRight(1000);
  stopMove(1000);
}

void moveStraight(int t){ 
  Serial.print("moving straight");
  analogWrite(LEFT, 255);
  analogWrite(RIGHT, 255);
  if(t>0) {
  delay(t);
  stopMove(0);
  }
}


void moveLeft(int t){ 
  Serial.print("turning left");
  analogWrite(LEFT, 175);
  analogWrite(RIGHT, 255);
  if(t>0) {
  delay(t);
  stopMove(0);
  }
}

void moveRight(int t){
  Serial.print("turning right");
  analogWrite(LEFT, 255);
  analogWrite(RIGHT, 175);
  if(t>0) {
  delay(t);
  stopMove(0);
  }
}

void stopMove(int t){
  Serial.print("stopping all motion");
  analogWrite(LEFT, 0);
  analogWrite(RIGHT, 0);
  if(t>0) {
  delay(t);
  }
}

