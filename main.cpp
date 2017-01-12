
//#include <gtest/gtest.h>
#include "Management.h"
#include <stdlib.h>
#include "easyloggingpp-8.91/easylogging++.h"
#include <pthread.h>
_INITIALIZE_EASYLOGGINGPP

void *checkFunc(void *sock) {
    Socket *s;
    s = (Socket *) sock;
    s->initialize();
}

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
    Tcp*sock = new Tcp(true, portNum);
    int i = pthread_create(&t1, NULL, checkFunc, (void *) sock);
    //sock->initialize();
    //run the program
    Management management(sock);
    management.getMap();
    management.manage();
    return 0;
}

