const int NUMBER_OF_ELEMENTS = 10;
const int MAX_SIZE = 12;

char descriptions [NUMBER_OF_ELEMENTS] [MAX_SIZE] = { 
 { "Furnace on" }, 
 { "Furnace off" }, 
 { "Set clock" }, 
 { "Pump on" }, 
 { "Pump off" }, 
 { "Password:" }, 
 { "Accepted" }, 
 { "Rejected" }, 
 { "Fault" }, 
 { "Service rqd" }, 
 };


void setup ()
  {
  Serial.begin (115200);
  Serial.println ();
  
  for (int i = 0; i < NUMBER_OF_ELEMENTS; i++)
    Serial.println (descriptions [i]);
  }  // end of setup

void loop ()
  {
    
  }  // end of loop
