#include <iostream>
#include "Driver.h"
#include "Udp.h"
#include "ManageDriver.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/lexical_cast.hpp>

int main() {
    //todo add main argument for port and ip
    string input;
    cin >> input;
    Driver* d = new Driver(input);
    //make sure the info is good
    try {
        d->validate();
    } catch (const invalid_argument &iaExc) {

    }
    Socket* socket =new Udp(false,5006);
    socket->initialize();
    ManageDriver md(input,socket);
    md.manage();
    delete d;
    return 0;
}