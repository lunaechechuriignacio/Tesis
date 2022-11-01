
#include <relay.h>

relay::relay() {
    port=0;
    number=0;
    status=0;
    time=0;
    time_start="";
    time_finish="";
    automatic= false;    
}

int relay::getPort(){
    return port;
}

void relay::setPort(int newPort){
    port=newPort;
}

int relay::getNumber(){
    return number;
}

void relay::setNumber(int newNumber){
     number=newNumber;
}

int relay::getStatus(){
    return status;
}

void relay::setStatus(int newStatus){
     status=newStatus;
}

String relay::getTimeStart (){
        return time_start;
}
void relay::setTimeStart (String time){
     time_start=time;
}
         
String relay::getTimeFinish (){
     return time_finish;
     }
     
void relay::setTimeFinish (String time){
     time_finish=time;
}

bool relay::getAutomatic(){
     return automatic;
}

void relay::setAutomatic(bool newAutomatic){
     automatic=newAutomatic;
}    

