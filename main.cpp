
//#include <gtest/gtest.h>
#include "Management.h"
#include <stdlib.h>


/**
 * the main function.
 * recives the grid size and the point to search.
 * @return 0;
 */
int main(int argc, char* argv[]) {
    //get the port
    if(argc < 2 ){
        return 0; //todo 0 or -1 ?
    }
    int portNum = atoi(argv[1]);
    Socket* sock = new Udp(true,portNum);
    sock->initialize();
    //run the program
    Management management(sock);
    management.getMap();
    management.manage();
    return 0;
}