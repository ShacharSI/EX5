#include "Management.h"
#include <stdlib.h>
#include <cstdlib>
#include "StandardTaxi.h"
#include "LuxuryTaxi.h"
#include "Thread_Runner.h"
#include "Thread_Manage.h"
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(StandardTaxi, "StandardTaxi")
BOOST_CLASS_EXPORT_GUID(LuxuryTaxi, "lux_taxi")
BOOST_CLASS_EXPORT_GUID(Taxi, "taxi")
BOOST_CLASS_EXPORT_GUID(Driver, "driver")
BOOST_CLASS_EXPORT_GUID(Point, "point")
BOOST_CLASS_EXPORT_GUID(Square, "Square")
#define BUFFERSIZE 4096

/**
 * the constructor
 */
Management::Management(Socket *s) {
    this->socket = s;
    this->taxiCenter = NULL;
}

/**
 * the function that runs the all game
 * takes the user's input and doing the matching mission
 */
void Management::manage() {
    char *buffer = (char *) malloc(4096 * sizeof(char));
    Thread_Runner *threader = new Thread_Runner(this->taxiCenter);
    this->thread_runner = threader;
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
                this->parseDriver();
                break;
            }
                //create trip
            case 2: {
                getline(cin, userInput);
                this->parseTrip(userInput);
                break;
            }
                //create taxi
            case 3: {
                getline(cin, userInput);
                Taxi *taxi = this->parseTaxi(userInput);
                taxi->setLocation(Point(0, 0));
                this->taxiCenter->addTaxi(taxi);
                break;
            }
                //print the wanted taxi's location
            case 4: {
                cin >> userInput;
                c = userInput.c_str();
                int id = atoi(c);
                this->parseLocation(id);
                break;
            }
                //move all taxi's
            case 9: {
                this->setClock();
                this->taxiCenter->moveAll();
                //checking if the time to release a trip is right now

                break;
            }
            default:
                break;
        }
        this->assignTrip();
        //get the next input
        cin >> usrChoiceStr;
        c = usrChoiceStr.c_str();
        userChoice = atoi(c);
    }
    //close the program and delete all memory
    string end = "EndCommunication";
    this->socket->sendData(end, end.size());
    ssize_t n = this->socket->reciveData(buffer, 4096);
    if (n < 0) {
        perror("failed receiving");
    }
    if (strcmp(buffer, "Finished") == 0) {
        close(this->socket->getSocketDescriptor());
    }
    Thread_Manage* thread_manage = Thread_Manage::getInstance();
    int size = thread_manage->getThreadList().size();
    list<pthread_t>& l = thread_manage->getThreadList();
    for (int i = 0; i < size; i++) {
        pthread_t t = l.front();
       pthread_join(t,NULL); //todo like this?
    }
    delete(thread_manage);
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
        t = new StandardTaxi(id, Taxi::parseMnfctr((strArray[2])),
                             Taxi::parseColor((strArray[3])), 1);
    }
    if (tarrif == 2) {
        t = new LuxuryTaxi(id, Taxi::parseMnfctr((strArray[2])),
                           Taxi::parseColor((strArray[3])), 2);
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
void Management::parseLocation(int id) {
    Thread_Manage *thread_manage = Thread_Manage::getInstance();
    map<Driver *, queue<std::string>>& mymap = thread_manage->getThreadMasseges();
    for (std::map<Driver *, std::queue<string>>::iterator it = mymap.begin();
         it != mymap.end(); ++it) {
        if (it->first->getId() == id ){
            it->second.push("GiveLocation");
            break;
        }
    }


}


/**
 * getting the driver from the client
 * saving the driver to the taxi center and attaching a
 * taxi to him
 */
void Management::parseDriver() {
    //set the variables
    ssize_t n;
    map<Driver *, int> *socketDesmap = new map<Driver *, int>();
    Taxi *t = NULL;
    Driver *d = NULL;
    string serial_str;
    char *buffer = (char *) malloc(BUFFERSIZE * sizeof(char));
    //get the number of drivers
    string input;
    cin >> input;
    const char *ch = input.c_str();
    int numOfDrivers = atoi(ch);
    this->socket->initialize();
    //a loop that gets the drivers and send taxi's
    for (int j = 0; j < numOfDrivers; ++j) {
        pthread_t t;
        int status = pthread_create(&t, NULL, this->thread_runner->run, NULL);
    }

    free(buffer);
}

/**
 * getting the user's string and creating a trip from it
 */
void Management::parseTrip(string s) {
    string streamCut;
    stringstream tempStr(s);
    int tripInfo[7];
    double tarrif = 0;
    unsigned int time = 0;
    int i = 0;
    //parse the trip info
    while (std::getline(tempStr, streamCut, ',')) {
        const char *c = streamCut.c_str();
        if (i <= 5) {
            tripInfo[i] = atoi(c);
        } else if (i == 6) {
            tarrif = atof(c);
        } else if (i == 7) {
            time = strtol(c, NULL, 0);
        }
        i++;
    }
    //create the trip
    Trip t(tripInfo[0], tripInfo[1], tripInfo[2], tripInfo[3], tripInfo[4], tripInfo[5], tarrif, time);
    //make sure the info is good
    try {
        t.validate();
        Map *m = this->taxiCenter->getMap();
        if ((t.getStartP().getX() > m->getSizeX()) || (t.getStartP().getY() > m->getSizeY())) {
            throw std::invalid_argument("invalid location");
        }
        Point endP = t.getEndP();
        if ((t.getEndP().getX() > m->getSizeX()) || (t.getEndP().getY() > m->getSizeY())) {
            throw std::invalid_argument("invalid location");
        }
    } catch (const std::invalid_argument &iaExc) {
        pthread_t t;
        pthread_create(&t, NULL, this->thread_runner->getTrip, (void *) t);//todo int? int status?
    }
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
    this->getObstacles();
    this->taxiCenter = new TaxiCenter(this->lg.createNewMap("Square"), this->socket);
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
 * the deconstructor
 */
Management::~Management() {
    if (this->taxiCenter != NULL) {
        delete this->taxiCenter;
    }
    delete this->socket;
}
