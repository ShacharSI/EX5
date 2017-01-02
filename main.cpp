
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
    //Algorithm* a = new Bfs;
    //delete a;
    //MapFactory mf;
    //std::list<Point>l;
  //  TaxiCenter* t = new TaxiCenter(mf.createMapSearchable("Square",3,3,0,0,l),sock);
//    delete(t);
     management.manage();
    return 0;
}