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

         int getTime();
         void setTime(int time);
         
         String getStartTime ();
         void setStartTime (String time);
         
         String getEndTime ();
         void setEndTime (String time);

         bool getAutomatic ();
         void setAutomatic (bool automatic);
         
      
   
  private:
           int number;
           int port;
           int status;
           int time;
           String time_start;
           String time_finish;
           bool automatic;        
     
};
#endif

