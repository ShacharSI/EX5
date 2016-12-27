#include "Management.h"
#include "LuxTaxiFactory.h"
#include <stdlib.h>
#include <unistd.h>

#define BUFFERSIZE 4096

/**
 * the constructor
 */
Management::Management(Socket *s) {
    this->clock = 0;
    this->socket = s;
}

/**
 * the function that runs the all game
 * takes the user's input and doing the matching mission
 */
void Management::manage() {
    char *buffer = (char *) malloc(4096 * sizeof(char));
    string userInput;
    string usrChoiceStr;
    int userChoice;
    cin >> usrChoiceStr;
    const char *c = usrChoiceStr.c_str();
    userChoice = atoi(c);
    //preform the mission
    while (userChoice != 7) {
        cin.ignore();
        switch (userChoice) {
            //create driver
            case 1: {
                getline(cin, userInput);
                this->parseDriver(userInput);
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
            case 9: {
                this->setClock();
                this->taxiCenter.moveAll(this->socket);
                break;
            }
            default:
                break;
        }
        //checking if the time to release a trip is right now
        this->assignTrip();
        //get the next input
        cin >> usrChoiceStr;
        c = usrChoiceStr.c_str();
        userChoice = atoi(c);
    }
    //close the program and delete all memory
    this->taxiCenter.deleteMap();
    this->socket->sendData("EndCommunication");
    this->socket->reciveData(buffer, 4096);

    if (strcmp(buffer, "Finished") == 0) {
        //todo close and delete  all !!
    }
    free(buffer);
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
 * getting the driver from the client
 * saving the driver to the taxi center and attaching a
 * taxi to him
 */
void Management::parseDriver(string s) {
    ssize_t n;
    Taxi *t = NULL;
    Driver *d = NULL;
    int vehicle_id;
    string serilazeData;

    char *buffer = (char *) malloc(BUFFERSIZE * sizeof(char));
    string input = "1";
    //cin >> input;
    const char *ch = input.c_str();
    int numOfDrivers = atoi(ch);
    //a loop that gets the drivers and send taxi's
    for (int j = 0; j < numOfDrivers; ++j) {
        n = this->socket->reciveData(buffer, BUFFERSIZE);
        if (n < 0) {
            perror("error receiving");
        }

        //todo serialize vehicle id
        t = this->taxiCenter.attachTaxiToDriver(vehicle_id);
        //todo serialize taxi and send back
        n = this->socket->sendData(serilazeData);

        d->setTaxi(t);
        this->taxiCenter.addDriverToCenter(d);
    }

    free(buffer);

}

/**
 * getting the user's string and creating a trip from it
 */
Trip Management::parseTrip(string s) {

    string streamCut;
    stringstream tempStr(s);
    int tripInfo[7];
    double tarrif = 0;
    int i = 0;
    //parse the info
    while (std::getline(tempStr, streamCut, ',')) {
        const char *c = streamCut.c_str();
        if (i != 5) {
            tripInfo[i] = atoi(c);
        } else {
            tarrif = atof(c);
        }

        i++;
    }
    //create the trip
    Trip t(tripInfo[0], tripInfo[1], tripInfo[2], tripInfo[3], tripInfo[4], tripInfo[5], tarrif,
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
    Socket *s = new Udp(true, 5006);
    this->taxiCenter = TaxiCenter(this->lg.createNewMap("Square"), this->socket);
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

/**
 * inc the clock by one up
 */
void Management::setClock() {
    this->clock += 1;
}

/**
 * checking if the time of any trip arrived
 */
void Management::assignTrip() {
    taxiCenter.assignTrip();
}
