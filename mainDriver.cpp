#include <iostream>
#include "Driver.h"
#include "Udp.h"
#include <stdio.h>
#include "ManageDriver.h"
#include "Tcp.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/lexical_cast.hpp>
/**
 * the main function.
 * run the client
 * @return 0;
 */
int main(int argc, char* argv[]) {
    //get the port and ip
    if(argc < 3 ){
        return 0;
    }
    int portNum = atoi(argv[2]);
    Tcp* sock = new Tcp(false,portNum);
    int check = sock->initialize();
    if(check == 4){
        perror("could not connect");
        return 0;
    }
    sock->setIp(argv[1]);
    //get the driver
    string input;
    cin >> input;
    //run the program
    ManageDriver md(input,sock);
    md.manage();
    return 0;
}