#include <iostream>
#include "Driver.h"
#include "Udp.h"
#include "ManageDriver.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/lexical_cast.hpp>

int main(int argc, char* argv[]) {
    //get the port and ip
    if(argc < 3 ){
        return 0; //todo 0 or -1 ?
    }
    int portNum = atoi(argv[1]);
    Socket* sock = new Udp(true,portNum);
    sock->initialize();
    sock->setIp(argv[2]);
    //get the driver
    string input;
    cin >> input;
    Driver* d = new Driver(input);
    //make sure the info in the driver is good
    try {
        d->validate();
    } catch (const invalid_argument &iaExc) {

    }
    //run the program
    ManageDriver md(input,sock);
    md.manage();
    delete d;
    return 0;
}