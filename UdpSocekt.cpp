//
// Created by haim on 12/22/16.
//

#include <sys/socket.h>
#include "UdpSocekt.h"
#include <iostream>

UdpSocekt::UdpSocekt() {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock < 0){
        perror("Error establishing connection");
        exit(1);
    }

}

int UdpSocekt::sendInfo() {
    return 0;
}

int UdpSocekt::getInfo() {
    return 0;
}

void UdpSocekt::closeSocket() {

}

UdpSocekt::~Socket() {

}



