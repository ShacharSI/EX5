#include <sstream>
#include "Logic.h"
#include <stdlib.h>
#include <stdexcept>
#include <limits>


/**
 * the constructor
 */

Logic::Logic() {

}

/**
 * the constructor
 */
Logic::Logic(vector<int> sizes) {
    if(sizes.size() == 2) {
        //takes the parameter from the user ant turn it into info
        this->sizeY = sizes.back();
        sizes.pop_back();
        this->sizeX = sizes.back();
        sizes.pop_back();
    } else{
        this->sizeY = -1;
        this->sizeX = -1;
    }
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

    //cin.ignore();
    for (int j = 0; j < numObstacle; j++) {
        if(cin >> firstNum >> seperator >> secondNum){
            if(seperator != ','){
                return -1;
            }
        } else{
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //todo need this??
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
    if ((sizeX <= 0) || (sizeY <= 0)) {
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