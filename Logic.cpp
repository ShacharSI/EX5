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
void Logic::setObstacle(int numObstacle) {
    //getting the obstacles
    string input;
    string streamCut;
    int vals[2] = {};
    cin.ignore();
    for (int j = 0; j < numObstacle; j++) {
        getline(cin, input);
        string::size_type position = input.find(",");
        vals[0] = atoi(input.substr(0, position).c_str());
        vals[1] = atoi(input.substr(position + 1, input.size() - 1 - position).c_str());
        Point p(vals[0], vals[1]);
        this->obstacle.push_back(p);
    }
}

/**
 * implements the validation interface
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
