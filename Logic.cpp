#include <sstream>
#include "Logic.h"
#include <stdlib.h>
#include <stdexcept>


/**
 * the constructor
 */

Logic::Logic() {

}

/**
 * the constructor
 */
Logic::Logic(vector<int> sizes) {
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
int Logic::setObstacle(int numObstacle) {
    //getting the obstacles
    string input;
    string streamCut;
    int firstNum;
    int secondNum;
    char seperator;
    int vals[2] = {};
    cin.ignore();
    for (int j = 0; j < numObstacle; j++) {
        if(!cin >> firstNum >> seperator >> secondNum){
            return -1;
        }
        if(seperator != ','){
            return -1;
        }
        Point p(firstNum, secondNum);
        this->obstacle.push_back(p);
    }
    return 0;
}

/**
 * implements the validation interface
 * checks that the is with correct arguments
 */
int Logic::validate() {
    if ((sizeX < 0) || (sizeY < 0)) {
        return -1;
    }
    return 0;
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
Map* Logic::createNewMap(string s) {
    return this->mpFactory.createMapSearchable(s, this->sizeX, this->sizeY
                                               , 0, 0, this->getObstacle());
}

/**
 * @return - the obstacle list on map
 */
list <Point> Logic::getObstacle() {
    return obstacle;
}
