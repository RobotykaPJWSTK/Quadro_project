float cP;
float cI;
float cD;
int setpoint;
int *input;
int suma;
int x0;

float getCP() {
  return cP;
}

float getCI() {
  return cI;
}

float getCD() {
  return cD;
}

void setCP(float newCP){  // set wzmocnienie P
  cP=newCP;
}

void setCI(float newCI){  // set wzmocnienie I
  cI=newCI;
}

void setCD(float newCD){  // set wzmocnienie D
  cD=newCD;
}

void setSetpoint(int newSetpoint){    // set pożądana wartość
  setpoint = newSetpoint;
}

void setInput(int *newInput){
  input = newInput;
}

int calcError(int setpoint, int input){
  int error = setpoint - input;
  return error;
}

int calcP(int error){ 
  return error*cP;
}

int calcI(int error){
  suma+=error;
  return cI*suma;
}

int calcD(int error){
  int ret = error - x0;
  x0=error;
  return ret*cD;
}

int calcPID(){ 
  int error = calcError(setpoint, *input);
  return calcP(error)+calcI(error)+calcD(error);
}

void initPID(float newCP, float newCI, float newCD, int setpoint, int *input){      // funkcja służąca do obliczania w loopie
  setCP(newCP);
  setCI(newCI);
  setCD(newCD);
  setSetpoint(setpoint);
  setInput(input);
  x0=0;
  suma=0;
}
  
