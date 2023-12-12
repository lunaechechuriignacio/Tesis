
#include <Relay.h>

Relay::Relay() {
    port=0;
    number=0;
    status=0;
      
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




