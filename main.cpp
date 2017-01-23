
//#include <gtest/gtest.h>
#include "Management.h"
#include <stdlib.h>
#include <pthread.h>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/iostreams/stream.hpp>
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

/**
 * the main function.
 * run the server
 * @return 0;
 */
int main(int argc, char *argv[]) {
    pthread_t t1;
    //get the port
    if (argc < 2) {
        return 0;
    }
    LINFO << "This is my first log " << "in main func ";
    int portNum = atoi(argv[1]);
    Tcp* sock = new Tcp(true, portNum);
    sock->initialize();
    //run the program
    Management management(sock);
    management.getMap();
    management.manage();
    LINFO << " This is my last log " << "in main func ";
    return 0;
}
