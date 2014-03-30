#include <Servo.h>
#include <PID_v1.h>

int inputMain;                  // sluzy do mapowania na PID

void setup(){
  
  Wire.begin();              // rozpoczecie transmisji I2C oraz szeregowej
  Serial.begin(9600);
  
  motorInit(10,70);                // inicjalizacja silników
  
  initPID(1,0,0,0,&currAngleX);          // inicjalizacja PIDa, parametry w takiej kolejności: cP, cI, cD
  
  I2C_write(DEVICEaddr, ACC_SLEEP, 0);      // ustawienie flagi uspienia akcelerometru na 0
  
  // Wiadomość startowa
  Serial.println("Uruchomiono");
}

void loop(){
  
  checkForFailsafe();
  
  readAcc(_accValues);
  readGyro(_gyroValues);
  
  updateAngle();
  
//  Serial.print("X: ");
//  Serial.print(_accValues[0]);
//  Serial.print(" Y: ");
//  Serial.print(_accValues[1]);
//  Serial.print(" Z: ");
//  Serial.println(_accValues[2]);
  
  //motorControl();
  
  //inputMain = map(_gyroValues[1],-1200,1200, -100, 100);        // skalowanie inputu do PIDa, ACC -16000, 16000
  int result = calcPID();
  
  Serial.print("Angle: ");
  Serial.println(currAngleX);
  
  /*Serial.print("Input: ");
  Serial.println(_gyroValues[1]);
  Serial.print("Output: ");
  Serial.println(result);*/
  setPowerXAxis(result);
  
 
  //delay(1000);
}
