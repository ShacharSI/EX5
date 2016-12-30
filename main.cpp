
//#include <gtest/gtest.h>
#include "Management.h"


/**
 * the main function.
 * recives the grid size and the point to search.
 * @return 0;
 */
int main(int argc, char* argv[]) {
    Socket* sock = new Udp(true,5006);
    sock->initialize();
    Management management(sock);
    management.getMap();
    management.manage();
    return 0;
}