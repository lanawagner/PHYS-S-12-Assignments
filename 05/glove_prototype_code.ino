#define LED1 9
#define LED2 10
#define BUTTON 2
#define MOTOR 6

int switchState = 0;

void setup() {
  // put your setup code here, to run once:

  pinMode(2, INPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(6, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), blink, RISING);
  Serial.begin(9600);

}

void loop() {

  switchState = digitalRead(2);
  Serial.println(switchState);
  // put your main code here, to run repeatedly:
for (int t = 0; t < 255; t++) {
  if (switchState == HIGH) {
    // the button is  pressed
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(6, HIGH);
  }
  else { // the button is not pressed
      analogWrite(9, t); // red LED
      delay(5);
      digitalWrite(10, LOW); // green LED
      digitalWrite(6, LOW);
    }

  }

}
void blink() {
  switchState = !switchState;
}
