
//#include <gtest/gtest.h>
#include "Management.h"


/**
 * the main function.
 * recives the grid size and the point to search.
 * @return 0;
 */
int main(int argc, char* argv[]) {

    //testing::InitGoogleTest(&argc,argv);
    Management management;
    management.getMap();
    management.manage();
    //return RUN_ALL_TESTS();
    return 0;
}