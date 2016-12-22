#include <sstream>
#include "Logic.h"
#include <stdlib.h>
#include <string>
#include <stdexcept>

/**
 * the constructor
 */

Logic::Logic() {

}

/**
 * the constructor
 */
Logic::Logic(vector <int> sizes) {
    string input;
    //takes the parameter from the user ant turn it into info
    this->sizeY = sizes.back();
    sizes.pop_back();
    this->sizeX = sizes.back();
    sizes.pop_back();
}

/**
 * getting the obstacle list parsing it and creating a list of them
 */
void Logic::setObstacle(int numObstacle) {
    string input = "";
    string streamCut = "";
    int vals[2] = {};
    for (int j = 0; j < numObstacle; j++) {
        cin >> input;
        stringstream tempStr(input);
        int i = 0;
        while (std::getline(tempStr, streamCut, ',')) {
            const char* c = streamCut.c_str();
            vals[i] = atoi(c);
            i++;

        }
        Point p(vals[0],vals[1]);
        this->obstacle.push_back(p);
    }
}


/**
 * implement of the validation interface
 * checks that the is with correct arguments
 */
void Logic::validate() {
    if ((sizeX < 0) || (sizeY < 0)) {
        throw invalid_argument("wrong size");
    }
}

/**
 * returns the map x size
 */
int Logic::getSizeX() {
    return this->sizeX;
}

/**
 * returns the map y size
 */
int Logic::getSizeY() {
    return this->sizeY;
}

/**
 * creating a new map acoording to the wanted
 * type(decide by the string) and size
 **/
Map Logic::createNewMap(string s) {
    return this->mpFactory.createMapSearchable(s,this->sizeX, this->sizeY,0,0,this->getObstacle());
}

/**
 * @return - the obstacle list on map
 */
list <Point> Logic::getObstacle() {
    return obstacle;
}
