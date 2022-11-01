#ifndef relay_h
#define relay_h

#include "Arduino.h"

class relay {
  public:
      relay();
         int getPort();
         void setPort(int port);
         
         int getNumber();
         void setNumber(int number);
         
         int getStatus();    
         void setStatus(int status);

         int getTime();
         void setTime(int time);
         
         String getTimeStart ();
         void setTimeStart (String time);
         
         String getTimeFinish ();
         void setTimeFinish (String time);

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

