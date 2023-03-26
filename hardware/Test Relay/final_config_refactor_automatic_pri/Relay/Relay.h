#ifndef Relay_h
#define Relay_h

#include "Arduino.h"

class Relay {
  public:
         Relay();
         int getPort();
         void setPort(int port);
         
         int getNumber();
         void setNumber(int number);
         
         int getStatus();    
         void setStatus(int status);
     
         bool getAutomatic ();
         void setAutomatic (bool automatic);
         
      
   
  private:
           int number;
           int port;
           int status;
           bool automatic;        
     
};
#endif

