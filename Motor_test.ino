/*

String incomingString;


void motorControl(){
  if(Serial.available() > 0)
  {
    char ch = Serial.read();
    if (ch != 32){
      Serial.print("I have received: ");
      Serial.print(ch, DEC);
      Serial.print('\n');
      incomingString += ch; 
   }
   else
   {
      Serial.println("I am printing the entire string");
      Serial.println(incomingString);
      
      int val = incomingString.toInt();
      
      Serial.println("Printing the value: ");
      Serial.println(val);
      
      if (val > -1 && val < 181)
      {
        Serial.println("Value is between 0 and 180");
        myMotor2.write(val);
        myMotor3.write(val);
        myMotor5.write(val);
        myMotor6.write(val);
      }
      else
      {
        Serial.println("Value is NOT between 0 and 180");
        Serial.println("Error with the input");
      }
      incomingString = "";
    }
  }
}
*/
