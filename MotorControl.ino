#include <Servo.h>

Servo motor2;
Servo motor3;
Servo motor5;
Servo motor6;
int baseVal;

void motorInit(int safeValParameter, int baseValParameter){
  motor2.attach(A2);        // inicjalizacja silników
  motor3.attach(A3);
  motor5.attach(A5);
  motor6.attach(A6);
  
  int safeVal = safeValParameter;
  
  motor2.write(safeVal);        // podanie bezpiecznych wartości na silniki
  motor3.write(safeVal);
  motor5.write(safeVal);
  motor6.write(safeVal);
  
  baseVal = baseValParameter;
  
  delay(2000);                   // delay wymagany do poprawnego działania
}

void setPowerM2(int val) {
  motor2.write(val);
}

void setPowerM3(int val) {
  motor3.write(val);
}

void setPowerM5(int val) {
  motor5.write(val);
}

void setPowerM6(int val) {
  motor6.write(val);
}

void setPowerAll(int val) {
  motor2.write(val); 
  motor3.write(val); 
  motor5.write(val); 
  motor6.write(val); 
}

void setBaseVal(int newBaseVal) {
  baseVal = newBaseVal; 
}

void setPowerXAxis(int PIDval) {
  PIDval = map(PIDval,getCP()*(-100),getCP()*100, -20, 20);          // od do jakie wartości przyjmuje czujnik na od do jakie wartości dodają się do silników
  setPowerM2(baseVal-PIDval);
  setPowerM3(baseVal+PIDval);
  Serial.print("Na silniki 50+/-: ");
  Serial.println(PIDval);
}

void checkForFailsafe() {                      // mechanizm bezpieczeństwa, w przypadku wykrycia spacji na wejściu szeregowym stopuje silniki i do resetu nic nie robi
  if(Serial.available() > 0)
  {
    char ch = Serial.read();
    if (ch == 32){
      setPowerAll(10);
      Serial.println("Stopped via failsafe");
      while (true) {};
    }
  } 
}
