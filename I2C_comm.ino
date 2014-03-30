#include <Wire.h>

int currAngleX = 0;          // zmienne służące do zamiany pomiarów na stopnie
int currAngleY = 0;
int accX = 0;
int accY = 0;
long int lastMillis = -1;

#define DEVICEaddr 0x68

// ############## DEFINICJE AKCELEROMETRU #############################################################################################

#define ACC_X_MSB 0x3B
#define ACC_X_LSB 0x3C
#define ACC_Y_MSB 0x3D
#define ACC_Y_LSB 0x3E
#define ACC_Z_MSB 0x3F
#define ACC_Z_LSB 0x40
#define ACC_SLEEP 0x6B

// ############## DEFINICJE ZYROSKOPU #############################################################################################

#define GYRO_X_MSB 0x43
#define GYRO_X_LSB 0x44
#define GYRO_Y_MSB 0x45
#define GYRO_Y_LSB 0x46
#define GYRO_Z_MSB 0x47
#define GYRO_Z_LSB 0x48


int _accValues[3];
int _gyroValues[3];

// ############################## OPERACJA NA I2C ########################################################################################

void I2C_read(int address, int reg, byte buffer[], int sizeData){
  Wire.beginTransmission(address);            // podanie rejestru a nastepnie odczytanie z niego okreslonej ilosci danych do bufora
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(address, sizeData);
  int currByte = 0;
  while (Wire.available()){
    buffer[currByte] = Wire.read();
    currByte++;
  }
}

void I2C_write(int address, int reg, byte value) {
  Wire.beginTransmission(address);      // podanie rejestru a nastepnie wartosci w celu jej zapisania
  Wire.write(reg);
  Wire.write(value);
  Wire.endTransmission();
}

// ############################## OPERACJE NA ZYROSKOPIE I AKCELEROMETRZE ##################################################################################

void readAcc(int* bufferResult) {
  byte tempBuf[2];                              // kazda wartosc IMU zapisana jest na 2 bajtach, wiec musimy je wszystkie odczytac a nastepnie zamienic na liczby
  I2C_read(DEVICEaddr, ACC_X_MSB, tempBuf, 2);     
  bufferResult[0] = tempBuf[0]<<8;              // zamiana bajtow na int
  bufferResult[0] |= tempBuf[1];
  
  I2C_read(DEVICEaddr, ACC_Y_MSB, tempBuf, 2);    
  bufferResult[1] = tempBuf[0]<<8;
  bufferResult[1] |= tempBuf[1];
  
  I2C_read(DEVICEaddr, ACC_Z_MSB, tempBuf, 2);    
  bufferResult[2] = tempBuf[0]<<8;
  bufferResult[2] |= tempBuf[1];
}

void readGyro(int* bufferResult) {
  byte tempBuf[2];                              // kazda wartosc IMU zapisana jest na 2 bajtach, wiec musimy je wszystkie odczytac a nastepnie zamienic na liczby
  I2C_read(DEVICEaddr, GYRO_X_MSB, tempBuf, 2);     
  bufferResult[0] = tempBuf[0]<<8;              // zamiana bajtow na int
  bufferResult[0] |= tempBuf[1];
  
  I2C_read(DEVICEaddr, GYRO_Y_MSB, tempBuf, 2);    
  bufferResult[1] = tempBuf[0]<<8;
  bufferResult[1] |= tempBuf[1];
  
  I2C_read(DEVICEaddr, GYRO_Z_MSB, tempBuf, 2);    
  bufferResult[2] = tempBuf[0]<<8;
  bufferResult[2] |= tempBuf[1];
}

// ######################################## ZAMIANA NA KAT #############################################################################

void updateAngle() {
  if (lastMillis!=-1){
    int timeSinceLast = millis() - lastMillis;
    int degpsX = _gyroValues[1]/131*0.1;
    int accX = _accValues[0]/16384;
    accX = atan2(accX,0)+PI;
    accX *= RAD_TO_DEG;
    lastMillis = millis();
    currAngleX+=(degpsX*timeSinceLast*currAngleX*0.98)*0.01;
    currAngleX+=timeSinceLast*accX*0.02;
  }
  else { lastMillis = millis(); }
}
