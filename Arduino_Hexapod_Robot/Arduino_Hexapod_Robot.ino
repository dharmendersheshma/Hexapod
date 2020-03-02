#include <Servo.h>

#define ledB 10

// Create servo object

//Leg 3
Servo s24;
Servo s23;
Servo s22;

//Leg2
Servo s21;
Servo s20;
Servo s19;

//Leg 1
Servo s18;
Servo s17;
Servo s16;

//Leg 5
Servo s7;
Servo s8;
Servo s9;

//Leg 4
Servo s10;
Servo s11;
Servo s12;

//Leg 6
Servo s1;
Servo s2;
Servo s3;

int i1L1 = 0;
int i2L1 = 0;
int i3L1 = 0;
int i4L1 = 0;
int i5L1 = 0;
int i6L1 = 0;

int i1L2 = 0;
int i2L2 = 0;
int i3L2 = 0;
int i4L2 = 0;
int i5L2 = 0;
int i6L2 = 0;
boolean l1status = LOW;
boolean l2status = LOW;
boolean aStatus = LOW;
boolean attStatus = LOW;
int k = 0;
int a = 0;
int aa = 0;
int period = 1000;
unsigned long time_now = 0;

float distance;
long duration;
int dataIn;
int m = 0;
int h = 0;
int t = 0;
int att = 0;
int speedV = 30;

void setup() {
  pinMode(ledB, OUTPUT);

  //Allocate servos to pins using attach fn
  
  // Leg 4
  s10.attach(31);
  s11.attach(32);
  s12.attach(33); //rot
  // Leg 5
  s7.attach(28);
  s8.attach(29);
  s9.attach(30); //rot
  // Leg 6
  s1.attach(22);
  s2.attach(23);
  s3.attach(24); //rot
  // Leg 1
  s18.attach(39);
  s17.attach(38);
  s16.attach(37); //rot
  // Leg 2
  s21.attach(42);
  s20.attach(41);
  s19.attach(40); //rot
  // Leg 3
  s24.attach(45);
  s23.attach(44);
  s22.attach(43); //rot

  // == Move to initial position
  
  // Leg 4
  s10.write(60);
  s11.write(105);
  s12.write(100);
  // Leg 5
  s7.write(80);
  s8.write(105);
  s9.write(60);
  // Leg 6
  s1.write(70);
  s2.write(0);
  s3.write(60);

  // Leg 1
  s18.write(90);
  s17.write(75);
  s16.write(60);
  // Leg 2
  s21.write(120);
  s20.write(75);
  s19.write(60);
  // Leg 3
  s24.write(90);
  s23.write(75);
  s22.write(60);

  delay(3000);
}
void loop() {

  // Change dataIn for different actions of robot
    dataIn = 2;
    if (dataIn == 2) {
      m = 2;           //Move forward
    }
    if (dataIn == 3) {
      m = 3;            // Rotate left
    }
    if (dataIn == 4) {
      m = 4;            //Rotate right
    }
    if (dataIn == 5) {  
      m = 5;            //Move reverse
    }
   
  
  // Move forward
  if (m == 2) {
    moveLeg1();
    moveLeg3();
    moveLeg5();
    if (l1status == HIGH) {   
      moveLeg2();
      moveLeg4();
      moveLeg6();
    } 
  }
  // Rotate left
  if (m == 3) {
    moveLeg1();
    moveLeg3();
    moveLeg5Left();
    if (l1status == HIGH) {
      moveLeg2();
      moveLeg4Left();
      moveLeg6Left();
    }
  }
  // Rotate right
  if (m == 4) {
    moveLeg1Right();
    moveLeg3Right();
    moveLeg5();
    if (l1status == HIGH) {
      moveLeg2Right();
      moveLeg4();
      moveLeg6();
    }
  }
  // Move reverse
  if (m == 5) {
    moveLeg1Rev();
    moveLeg3Rev();
    moveLeg5Rev();
    if (l1status == HIGH) {
      moveLeg2Rev();
      moveLeg4Rev();
      moveLeg6Rev();
    }
  }
  

  // Initial and resting position 
  if (dataIn == 0) {
    initialPosition();
/*
    // Monitor the battery voltage
    int sensorValue = analogRead(A3);
    float voltage = sensorValue * (5.00 / 1023.00) * 2.9; // Convert the reading values from 5v to suitable 12V i
    Serial.println(voltage);
    // If voltage is below 11V turn on the LED
    if (voltage < 11) {
      digitalWrite(ledB, HIGH);
    }
    else {
      digitalWrite(ledB, LOW);
    }
    */
  }  
  delay(speedV);
}
  

void moveLeg1() {
  // Swing phase - move leg through air - from initial to final position
  // Rise the leg
  if (i1L1 <= 10) {
    s18.write(90 - i1L1 * 2);
    s17.write(75 - i1L1 * 3);
    i1L1++;
  }
  // Rotate the leg
  if (i2L1 <= 30) {
    s16.write(60 - 1.5*i2L1);
    i2L1++;
  }
  // Move back to touch the ground
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  // Stance phase - move leg while touching the ground
  // Rotate back to initial position
  if (i2L1 >= 30) {
    s16.write(30 + 1.5*i4L1);
    i4L1++;
    l1status = HIGH;
  }
  // Reset the counters for repeating the process
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
  // Each iteration or step is executed in the main loop section where there is also a delay time for controlling the speed of movement
}
void moveLeg2() {
  if (i1L2 <= 10) {
    s21.write(120 - i1L2 * 2);
    s20.write(75 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(60 - 1.5*i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(30 + 1.5*i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3() {
  if (i1L1 <= 10) {
    s24.write(90 - i1L1 * 2);
    s23.write(75 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(60 - 1.5*i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(30 + 1.5*i4L1);
  }
}

void moveLeg4() {
  if (i1L2 <= 10) {
    s10.write(60 + i1L2 * 2);
    s11.write(105 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(100 + 1.5*i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(130 - 1.5*i4L2);
  }
}
//Some problem
void moveLeg5() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(105 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(60 + 1.5*i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(90 - 1.5*i4L1);
  }
}

void moveLeg6() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(0 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s3.write(60 + 1.5*i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(30 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s3.write(90 - 1.5*i4L2);
  }
}

void moveLeg1Rev() {
  if (i1L1 <= 10) {
    s18.write(60 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    Serial.println(s17.read());
    i1L1++;
  }
  if (i2L1 <= 30) {
    s16.write(70 + i2L1);
    i2L1++;

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    Serial.println(s17.read());
    i3L1++;
  }
  if (i2L1 >= 30) {
    s16.write(100 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}
void moveLeg2Rev() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(45 + i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(75 - i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3Rev() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(50 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(80 - i4L1);
  }
}

void moveLeg4Rev() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(65 - i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(35 + i4L2);
  }
}

void moveLeg5Rev() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(60 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(30 + i4L1);
  }
}

void moveLeg6Rev() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s3.write(90 - i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s3.write(60 + i4L2);
  }
}

void moveLeg1Right() {
  if (i1L1 <= 10) {
    s18.write(60 - i1L1 * 2);
    s17.write(90 - i1L1 * 3);
    i1L1++;
  }
  if (i2L1 <= 30) {
    s16.write(70 + i2L1);
    i2L1++;

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s18.write(40 + i3L1 * 2);
    s17.write(60 + i3L1 * 3);
    i3L1++;
  }
  if (i2L1 >= 30) {
    s16.write(100 - i4L1);
    i4L1++;
    l1status = HIGH;
  }
  if (i4L1 >= 30) {
    i1L1 = 0;
    i2L1 = 0;
    i3L1 = 0;
    i4L1 = 0;
    i5L1 = 0;
  }
}
void moveLeg2Right() {
  if (i1L2 <= 10) {
    s21.write(50 - i1L2 * 2);
    s20.write(80 - i1L2 * 3);
    i1L2++;
  }
  if (i2L2 <= 30) {
    s19.write(45 + i2L2);
    i2L2++;

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s21.write(30 + i3L2 * 2);
    s20.write(50 + i3L2 * 3);
    i3L2++;
  }
  if (i2L2 >= 30) {
    s19.write(75 - i4L2);
    i4L2++;
  }
  if (i4L2 >= 30) {
    i1L2 = 0;
    i2L2 = 0;
    i3L2 = 0;
    i4L2 = 0;
    i5L2 = 0;
  }
}

void moveLeg3Right() {
  if (i1L1 <= 10) {
    s24.write(50 - i1L1 * 2);
    s23.write(80 - i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s22.write(50 + i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s24.write(30 + i3L1 * 2);
    s23.write(50 + i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s22.write(80 - i4L1);
  }
}

void moveLeg4Left() {
  if (i1L2 <= 10) {
    s10.write(65 + i1L2 * 2);
    s11.write(35 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s12.write(60 - i2L2);

  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s10.write(85 - i3L2 * 2);
    s11.write(65 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s12.write(30 + i4L2);
  }
}

void moveLeg5Left() {
  if (i1L1 <= 10) {
    s7.write(80 + i1L1 * 2);
    s8.write(50 + i1L1 * 3);
  }
  if (i2L1 <= 30) {
    s9.write(60 - i2L1);

  }
  if (i2L1 > 20 & i3L1 <= 10) {
    s7.write(100 - i3L1 * 2);
    s8.write(80 - i3L1 * 3);
  }
  if (i2L1 >= 30) {
    s9.write(30 + i4L1);
  }
}

void moveLeg6Left() {
  if (i1L2 <= 10) {
    s1.write(90 + i1L2 * 2);
    s2.write(45 + i1L2 * 3);
  }
  if (i2L2 <= 30) {
    s3.write(90 - i2L2);
  }
  if (i2L2 > 20 & i3L2 <= 10) {
    s1.write(110 - i3L2 * 2);
    s2.write(75 - i3L2 * 3);
  }
  if (i2L2 >= 30) {
    s3.write(60 + i4L2);
  }
}


void initialPosition() {
  a = 0;
  aa = 0;
  m = 0;
  l1status = LOW;
  l2status = LOW;
  aStatus = LOW;
  attStatus = LOW;

  // Leg 4
  s10.write(60);
  s11.write(105);
  s12.write(100);
  // Leg 5
   s7.write(90);
  s8.write(105);
  s9.write(60);
  // Leg 6
  s1.write(70);
  s2.write(0);
  s3.write(60);

  // Leg 1
  s18.write(90);
  s17.write(75);
  s16.write(60);
  // Leg 2
  s21.write(120);
  s20.write(75);
  s19.write(60);
  // Leg 3
  s24.write(90);
  s23.write(75);
  s22.write(60);

  i1L1 = 0;
  i2L1 = 0;
  i3L1 = 0;
  i4L1 = 0;
  i5L1 = 0;
  i6L1 = 0;

  i1L2 = 0;
  i2L2 = 0;
  i3L2 = 0;
  i4L2 = 0;
  i5L2 = 0;
  i6L2 = 0;
}
