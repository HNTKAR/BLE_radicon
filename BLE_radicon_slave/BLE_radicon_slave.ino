#include <SoftwareSerial.h>
#define a_b 3
#define a_a 4
#define b_b 5
#define b_a 6
SoftwareSerial BLE_Serial(A3, A2);
int x;
char y;




void setup() {
  // put your setup code here, to run once:
  BLE_Serial.begin(9600);
  Serial.begin(9600);
  pinMode(a_b, OUTPUT);
  pinMode(a_a, OUTPUT);
  pinMode(b_a, OUTPUT);
  pinMode(b_b, OUTPUT);
}

void loop() {
  if (BLE_Serial.available()) {
    y = BLE_Serial.read();
    switch (y) {
      case 'F':
        control_up();
        break;
      case 'B':
        control_down();
        break;
      case 'S':
        control_stop();
        break;
      case 'L':
        control_left();
        break;
      case 'R':
        control_right();
        break;
    }
    x = 0;
  }
  else {
    x = x + 1;
    if (x >= 20) {
      control_stop();
      x = 0;
      Serial.println("BAD!!");
    }
  }
  delay(50);
}

void control_up() {
  Serial.println("up");
  digitalWrite(a_b,HIGH);
  digitalWrite(a_a,LOW);
  digitalWrite(b_a,LOW);
  digitalWrite(b_b,HIGH);
}

void control_down() {
  Serial.println("down");
  digitalWrite(a_b,LOW);
  digitalWrite(a_a,HIGH);
  digitalWrite(b_a,HIGH);
  digitalWrite(b_b,LOW);
}

void control_stop() {
  Serial.println("stop");
  digitalWrite(a_b,HIGH);
  digitalWrite(a_a,HIGH);
  digitalWrite(b_a,HIGH);
  digitalWrite(b_b,HIGH);
}

void control_left() {
  Serial.println("left");
  digitalWrite(a_b,HIGH);
  digitalWrite(a_a,LOW);
  digitalWrite(b_a,HIGH);
  digitalWrite(b_b,HIGH);
}

void control_right() {
  Serial.println("right");
  digitalWrite(a_b,HIGH);
  digitalWrite(a_a,HIGH);
  digitalWrite(b_a,LOW);
  digitalWrite(b_b,HIGH);
}
