#include "Management.h"
#include "StandardTaxi.h"
#include "LuxuryTaxi.h"
#include "Thread_Runner.h"
#include "Thread_Manage.h"
#include "easyloggingpp-8.91/easylogging++.h"
#include <stdexcept>

//BOOST_CLASS_EXPORT_GUID(StandardTaxi, "StandardTaxi")

#define BUFFERSIZE 4096

/**
 * the constructor
 */
Management::Management(Tcp *s) {
    this->socket = s;
    this->taxiCenter = NULL;
}

/**
 * the function that runs the all game
 * takes the user's input and doing the matching mission
 */
void Management::manage() {

    Thread_Runner *thread_runner1 = Thread_Runner::getInstance(this->taxiCenter, this->socket);
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
                //create trip and calculate bfs
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
                this->taxiCenter->moveAll();
                break;
            }
            default:
                break;
        }
        //get the next input
        cin >> usrChoiceStr;
        c = usrChoiceStr.c_str();
        userChoice = atoi(c);
    }
    //close the program and delete all memory
    string end = "EndCommunication";
    Thread_Manage *thread_manage = Thread_Manage::getInstance();
    map<Driver *, queue<std::string>*> mymap = thread_manage->getThreadMasseges();
    for (std::map<Driver *, std::queue<string>*>::iterator it = mymap.begin();
         it != mymap.end(); ++it) {
        it->second->push(end);
    }
    int size = thread_manage->getThreadList().size();
    list <pthread_t> &l = thread_manage->getThreadList();
    for (int i = 0; i < size; i++) {
        pthread_t t = l.front();
        pthread_join(t, NULL); //todo like this?
    }
    delete (thread_manage);
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
    map<Driver *, queue<std::string>*> mymap = thread_manage->getThreadMasseges();
    for (std::map<Driver *, std::queue<string>*>::iterator it = mymap.begin();
         it != mymap.end(); ++it) {
        if (it->first->getId() == id) {
            it->second->push("GiveLocation");
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
    map<Driver *, int> *socketDesmap = new map<Driver *, int>();
    //get the number of drivers
    string input;
    cin >> input;
    const char *ch = input.c_str();
    int numOfDrivers = atoi(ch);
    Thread_Runner *thread_runner1 = Thread_Runner::getInstance(this->taxiCenter, this->socket);
    //a loop that gets the drivers and send taxi's
    for (int j = 0; j < numOfDrivers; ++j) {
        pthread_t t;
        int status = pthread_create(&t, NULL, Thread_Runner::runHelper, thread_runner1);//
    }
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
    Trip trip(tripInfo[0], tripInfo[1], tripInfo[2], tripInfo[3], tripInfo[4],
              tripInfo[5], tarrif, time);
    //make sure the info is good
    try {
        trip.validate();
        Map *m = this->taxiCenter->getMap();
        if ((trip.getStartP().getX() > m->getSizeX()) ||
                (trip.getStartP().getY() > m->getSizeY())) {
            throw std::invalid_argument("invalid location");
        }
        Point endP = trip.getEndP();
        if ((trip.getEndP().getX() > m->getSizeX()) ||
                (trip.getEndP().getY() > m->getSizeY())) {
            throw std::invalid_argument("invalid location");
        }
    } catch (const std::invalid_argument &iaExc) {

    }
    pthread_t thread;
    Thread_Runner *thread_runner1 = Thread_Runner::getInstance(this->taxiCenter, this->socket);
    thread_runner1->addTripToCalculate(trip);
    int status = pthread_create(&thread, NULL, Thread_Runner::tripHelper, thread_runner1);
    pthread_join(thread,NULL); //todo remove this
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
    LINFO << "creating map in size " << lg.getSizeX() << " on "<<lg.getSizeY();//
    this->taxiCenter = new TaxiCenter(this->lg.createNewMap("Square"));
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
