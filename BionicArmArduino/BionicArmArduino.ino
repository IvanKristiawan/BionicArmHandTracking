#include <Servo.h>
#define numOfValsRec 5
#define digitsPerValRec 1

Servo servoThumb;
Servo servoIndex;
Servo servoMiddle;
Servo servoRing;
Servo servoPinky;

int valsRec[numOfValsRec];
int stringLength = numOfValsRec * digitsPerValRec + 1;  //$00000
int counter = 0;
bool counterStart = false;
String receivedString;

int pos = 0;  // variable to store the servo position
int lastValsThumb = 0;
int lastValsIndex = 0;
int lastValsMiddle = 0;
int lastValsRing = 0;
int lastValsPinky = 0;

void setup() {
  Serial.begin(9600);
  servoThumb.attach(7);
  servoThumb.write(0);

  servoIndex.attach(9);
  servoIndex.write(0);

  servoMiddle.attach(11);
  servoMiddle.write(0);

  servoRing.attach(8);
  servoRing.write(0);

  servoPinky.attach(10);
  servoPinky.write(0);
}

void receieveData() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '$') {
      counterStart = true;
    }
    if (counterStart) {
      if (counter < stringLength) {
        receivedString = String(receivedString + c);
        counter++;
      }
      if (counter >= stringLength) {
        //$00000
        for (int i = 0; i < numOfValsRec; i++) {
          int num = (i * digitsPerValRec) + 1;
          valsRec[i] = receivedString.substring(num, num + digitsPerValRec).toInt();
        }
        receivedString = "";
        counter = 0;
        counterStart = false;
      }
    }
  }
}

void loop() {
  receieveData();

  if (valsRec[0] == 1 && lastValsThumb != 1) {
    // Move Up
    for (pos = 0; pos <= 180; pos += 1) {
      servoThumb.write(pos);
      delay(1);
    }
    lastValsThumb = 1;
  } else if (valsRec[0] == 0 && lastValsThumb != 0) {
    // Move Down
    for (pos = 180; pos >= 0; pos -= 1) {
      servoThumb.write(pos);
      delay(1);
    }
    lastValsThumb = 0;
  }

  if (valsRec[1] == 1 && lastValsIndex != 1) {
    // Move Up
    for (pos = 0; pos <= 180; pos += 1) {
      servoIndex.write(pos);
      delay(1);
    }
    lastValsIndex = 1;
  } else if (valsRec[1] == 0 && lastValsIndex != 0) {
    // Move Down
    for (pos = 180; pos >= 0; pos -= 1) {
      servoIndex.write(pos);
      delay(1);
    }
    lastValsIndex = 0;
  }

  if (valsRec[2] == 1 && lastValsMiddle != 1) {
    // Move Up
    for (pos = 0; pos <= 180; pos += 1) {
      servoMiddle.write(pos);
      delay(1);
    }
    lastValsMiddle = 1;
  } else if (valsRec[2] == 0 && lastValsMiddle != 0) {
    // Move Down
    for (pos = 180; pos >= 0; pos -= 1) {
      servoMiddle.write(pos);
      delay(1);
    }
    lastValsMiddle = 0;
  }

  if (valsRec[3] == 1 && lastValsRing != 1) {
    // Move Up
    for (pos = 0; pos <= 180; pos += 1) {
      servoRing.write(pos);
      delay(1);
    }
    lastValsRing = 1;
  } else if (valsRec[3] == 0 && lastValsRing != 0) {
    // Move Down
    for (pos = 180; pos >= 0; pos -= 1) {
      servoRing.write(pos);
      delay(1);
    }
    lastValsRing = 0;
  }

  if (valsRec[4] == 1 && lastValsPinky != 1) {
    // Move Up
    for (pos = 0; pos <= 180; pos += 1) {
      servoPinky.write(pos);
      delay(1);
    }
    lastValsPinky = 1;
  } else if (valsRec[4] == 0 && lastValsPinky != 0) {
    // Move Down
    for (pos = 180; pos >= 0; pos -= 1) {
      servoPinky.write(pos);
      delay(1);
    }
    lastValsPinky = 0;
  }
}
