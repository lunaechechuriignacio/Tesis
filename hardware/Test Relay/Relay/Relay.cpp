
#include <Relay.h>

Relay::Relay() {
    port=0;
    number=0;
    status=0;
    time=0;
    time_start="";
    time_finish="";
    automatic= false;    
}

int Relay::getPort(){
    return port;
}

void Relay::setPort(int newPort){
    port=newPort;
}

int Relay::getNumber(){
    return number;
}

void Relay::setNumber(int newNumber){
     number=newNumber;
}

int Relay::getStatus(){
    return status;
}

void Relay::setStatus(int newStatus){
     status=newStatus;
}

String Relay::getStartTime (){
        return time_start;
}
void Relay::setStartTime (String time){
     time_start=time;
}
         
String Relay::getEndTime (){
     return time_finish;
     }
     
void Relay::setEndTime (String time){
     time_finish=time;
}

bool Relay::getAutomatic(){
     return automatic;
}

void Relay::setAutomatic(bool newAutomatic){
     automatic=newAutomatic;
}    

