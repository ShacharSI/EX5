#include "Management.h"
#include "LuxTaxiFactory.h"
#include <stdlib.h>
#include <unistd.h>

/**
 * the constructor
 */
Management::Management() {

}

/**
 * the function that runs the all game
 * takes the user's input and doing the matching mission
 */
void Management::manage() {
    string userInput;
    string usrChoiceStr;
    int userChoice;
    cin >> usrChoiceStr;
    const char *c = usrChoiceStr.c_str();
    userChoice = atoi(c);
    //performe the mission
    while (userChoice != 7) {
        cin.ignore();
        switch (userChoice) {
            //create driver
            case 1: {
                getline(cin, userInput);
                Driver *d = this->parseDriver(userInput);
                this->taxiCenter.addDriverToCenter(d);
                break;
            }
                //create trip
            case 2: {
                getline(cin, userInput);
                Trip t = this->parseTrip(userInput);
                this->taxiCenter.addTrip(t);
                break;
            }
                //create taxi
            case 3: {
                getline(cin, userInput);
                Taxi *taxi = this->parseTaxi(userInput);
                taxi->setLocation(Point(0, 0));
                this->taxiCenter.addTaxi(taxi);
                break;
            }
                //print the wanted taxi's location
            case 4: {
                cin >> userInput;
                c = userInput.c_str();
                int id = atoi(c);
                Point p = this->parseLocation(id);
                cout << p;
                break;
            }
                //move all taxi's
            case 6: {
                this->taxiCenter.moveAll();
                break;
            }
            default:
                break;
        }
        cin >> usrChoiceStr;
        c = usrChoiceStr.c_str();
        userChoice = atoi(c);
    }
    this->taxiCenter.deleteMap();
    return;
}

/**
 * getting the user's string and creating a taxi from it
 */
Taxi *Management::parseTaxi(string s) {
    Taxi *t = NULL;
    string streamCut;
    stringstream tempStr(s);
    string strArray[4];
    int i = 0;
    //parse the string
    while (std::getline(tempStr, streamCut, ',')) {
        string strAfterCut = streamCut;
        strArray[i] = strAfterCut;
        i++;
    }
    //save the val in an array
    const char *c = strArray[0].c_str();
    int id = atoi(c);
    c = strArray[1].c_str();
    int tarrif = atoi(c);
    //create a matching taxi according to tha taarif
    if (tarrif == 1) {
        StndTaxiFactory stndFactory = StndTaxiFactory(1);
        t = stndFactory.createTaxi(id, Taxi::parseMnfctr((strArray[2])),
                                   Taxi::parseColor((strArray[3])));
    }
    if (tarrif == 2) {
        LuxTaxiFactory stndFactory = LuxTaxiFactory(2);
        t = stndFactory.createTaxi(id, Taxi::parseMnfctr((strArray[2])),
                                   Taxi::parseColor((strArray[3])));
    }
    //make sure the info is good
    try {
        t->validate();
    } catch (const std::invalid_argument &iaExc) {

    }
    return t;

}

/**
 * returns the wanted taxi(by id) location
 */
Point Management::parseLocation(int id) {
    return this->taxiCenter.giveLocation(id);
}


/**
 * getting the user's string and creating a driver from it
 */
Driver * Management::parseDriver(string s) {
    string streamCut;

    std::list<Driver *> list;
    string input = "1";
    //cin >> input;
    const char *ch = input.c_str();
    int numOfDrivers = atoi(ch);
    //todo create new proccess???
    for (int j = 0; j < numOfDrivers; ++j) {
        pid_t pid = fork();
        if (pid <0){
            perror("error creating process");
        }
        if (pid == 0) {

            //todo save the driver in list
        } else if (pid > 0){
            continue;
        }
    }

    return  NULL;
}

/**
 * getting the user's string and creating a trip from it
 */
Trip Management::parseTrip(string s) {

    string streamCut;
    stringstream tempStr(s);
    int tripInfo[6];
    double tarrif = 0;
    int i = 0;
    //parse the info
    while (std::getline(tempStr, streamCut, ',')) {
        const char *c = streamCut.c_str();
        if (i < 6) {
            tripInfo[i] = atoi(c);
        } else {
            tarrif = atof(c);
        }

        i++;
    }
    //create the trip
    Trip t(tripInfo[0], tripInfo[1], tripInfo[2], tripInfo[3], tripInfo[4], tripInfo[5], tarrif);
    //make sure the info is good
    try {
        t.validate();
    } catch (const std::invalid_argument &iaExc) {
    }
    return t;
}

/**
 * getting the obstacles from the user
 */
void Management::getObstacles() {
    string input;
    cin >> input;
    const char *c = input.c_str();
    int numOfObstacle = atoi(c);
    if (numOfObstacle > 0) {
        this->lg.setObstacle(numOfObstacle);
    }
}

/**
 * creating a map
 */
void Management::getMap() {
    this->setLogicAndMap();
}

/**
 * creating a map and putting it in the taxi center
 */
void Management::setLogicAndMap() {
    try {
        this->lg = Logic(getSizes());
        lg.validate();
    } catch (const std::invalid_argument &iaExc) {

    }
    getObstacles();
    this->taxiCenter = TaxiCenter(this->lg.createNewMap("Square"));
}

/**
 * @return - a vector with the map sizes given by the user
 */
vector<int> Management::getSizes() {
    string input;
    getline(cin, input);
    string streamCut;
    stringstream tempStr(input);
    vector<int> sizes;
    while (std::getline(tempStr, streamCut, ' ')) {
        const char *c = streamCut.c_str();
        sizes.push_back(atoi(c));
    }

    return sizes;
}