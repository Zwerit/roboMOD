// left motors
#define l_enA 5
#define l_in1 6
#define l_in2 7

// right motors
#define r_enA 2
#define r_in1 3
#define r_in2 4
String command;
int speed = 85; //initial power output for the motors


void setup() {
  pinMode(l_enA, OUTPUT);
  pinMode(l_in1, OUTPUT);
  pinMode(l_in2, OUTPUT);
  pinMode(r_enA, OUTPUT);
  pinMode(r_in1, OUTPUT);
  pinMode(r_in2, OUTPUT);
  Serial3.begin(9600);
  Serial.begin(115200);
  Serial.println("RoboMOD activated");
  analogWrite(l_enA, speed);
  analogWrite(r_enA, speed);
}

void stopping() {
  digitalWrite(l_in1, LOW);
  digitalWrite(l_in2, LOW);
  digitalWrite(r_in1, LOW);
  digitalWrite(r_in2, LOW);
}
void forward() {
  digitalWrite(l_in1, LOW);
  digitalWrite(l_in2, HIGH);
  digitalWrite(r_in1, LOW);
  digitalWrite(r_in2, HIGH);
}
void left() {
  digitalWrite(l_in1, HIGH);
  digitalWrite(l_in2, LOW);
  digitalWrite(r_in1, LOW);
  digitalWrite(r_in2, HIGH);
  analogWrite(l_enA, 100); //bc of the chassis issue, it needs more power for rotation
  analogWrite(r_enA, 100);

}
void backwards() {
  digitalWrite(l_in1, HIGH);
  digitalWrite(l_in2, LOW);
  digitalWrite(r_in1, HIGH);
  digitalWrite(r_in2, LOW);
}
void right() {
  digitalWrite(l_in1, LOW);
  digitalWrite(l_in2, HIGH);
  digitalWrite(r_in1, HIGH);
  digitalWrite(r_in2, LOW);
  analogWrite(l_enA, 100);//bc of the chassis issue, it needs more power for rotation
  analogWrite(r_enA, 100);
}

void loop() {
  int motorCommand;
  if (Serial3.available()) {
    motorCommand = Serial3.read();
    // Serial.println(motorCommand);
  }
  if (motorCommand == 1) {
    right();
  } else if (motorCommand == 2) {
    left();
  }
  else if (motorCommand == 3)
  {
    forward();
  }
  else if (motorCommand == 4)
  {
    backwards();
  }
  else if (motorCommand == 0)
  {
    stopping();
  }



}
