#include "Management.h"
#include "StandardTaxi.h"
#include "LuxuryTaxi.h"
#include "Thread_Runner.h"
#include "Thread_Manage.h"
#include <stdexcept>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include "easylogging++.h"
//BOOST_CLASS_EXPORT_GUID(StandardTaxi, "StandardTaxi")
#define BUFFERSIZE 200000

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
    //this->taxiCenter = new TaxiCenter(this->lg.createNewMap("Square"));
    Thread_Runner *thread_runner1 = Thread_Runner::getInstance(this->taxiCenter, this->socket);

    int userChoice = this->getUserChoise();
    //preform the mission
    while (userChoice != 7) {
        LINFO << " this is main thread: " << " start of switch case with mission: " << userChoice;
        cin.ignore();
        switch (userChoice) {
            //create driver
            case 1: {
                LINFO << " this is main thread: " << " create threads ";
                this->parseDriver();
                break;
            }
                //create trip and calculate bfs
            case 2: {
                LINFO << " this is main thread: " << " create and calculate trip ";

                this->parseTrip();
                break;
            }
                //create taxi
            case 3: {
                LINFO << " this is main thread: " << " create taxi ";
                getline(cin, userInput);
                Taxi *taxi = this->parseTaxi(userInput);
                taxi->setLocation(Point(0, 0));
                this->taxiCenter->addTaxi(taxi);
                break;
            }
                //print the wanted taxi's location
            case 4: {
                cin >> userInput;
                //c = userInput.c_str();
                //int id = atoi(c);
                //LINFO << " ask location for id : " << id;
                //this->parseLocation(id);

                break;
            }
                //move all taxi's
            case 9: {
                LINFO << " this is main thread: " << " move all ";
                LINFO << " this is main thread: " << " send all threads go ";
                this->taxiCenter->moveAll();
                break;
            }
            default:
                break;
        }
        LINFO << " this is main thread: " << " get next mission in server ";
        //get the next input
        userChoice = this->getUserChoise();
    }
    LINFO << " this is main thread: " << " closing program ";
    //close the program and delete all memory
    Thread_Manage *thraed_mannage = Thread_Manage::getInstance();
    queue<string> **mymap = thraed_mannage->getThreadMasseges();
    //iterate over the driver*
    for (int i = 0; i < thraed_mannage->getNumDrivers(); i++) {
        LINFO << " sending driver no:    " << i << " End_Communication";
        mymap[i]->push("End_Communication");
    }

    long size = thraed_mannage->getThreadList()->size();
    LINFO << " this is main thread: " << " son thread no: " << size;
    std::list<pthread_t *> *l = thraed_mannage->getThreadList();
    //while (1){};
    for (int i = 0; i < size; i++) {
        pthread_t *t = l->front();
        LINFO << " this is main thread: " << " wait to thread no: " << t;
        pthread_join(*t, NULL);
        l->pop_front();
        delete t;
    }
    delete l;

    LINFO << " this is main thread: " << " finish with all threads";
    delete thraed_mannage;
    delete thread_runner1;
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
    queue<string> **mymap = thread_manage->getThreadMasseges();

    if ((id < 0) || (id > thread_manage->getNumDrivers())) {
        throw invalid_argument("wrong coordinate");
    }
    mymap[id]->push("GiveLocation");


}


/**
 * getting the driver from the client
 * saving the driver to the taxi center and attaching a
 * taxi to him
 */
void Management::parseDriver() {
    //set the variables
    int numOfDrivers = this->parseNumOfDrivers();
    if (numOfDrivers == -1) {
        return;
    }
    this->socket->setBackLog(numOfDrivers);
    Thread_Manage *thread_manage = Thread_Manage::getInstance();
    thread_manage->setInitialMessagesQueues(numOfDrivers);

    Thread_Runner *thread_runner1 = Thread_Runner::getInstance(this->taxiCenter, this->socket);
    //a loop that gets the drivers and send taxi's
    std::list<pthread_t *> *list1 = new list<pthread_t *>;
    thread_manage->setThreadList(list1);
    //todo verify that the connection will be for this num of drivers or will need to erase to queue list and create one in matching size
    //todo verify that the divers id will be in order otherwise will need to switch to map !!
    for (int j = 0; j < numOfDrivers; ++j) {
        Driver *d = this->getDriver();
        thread_runner1->pushInitialDriver(d);
        thread_runner1->pushNotActiveDriver(d);
    }
    for (int j = 0; j < numOfDrivers; ++j) {
        pthread_t *t = new pthread_t;
        thread_manage->addThread(t);
        LINFO << " this is main thread: " << " create threads no:" << t;
        int status = pthread_create(t, NULL, Thread_Runner::runHelper, thread_runner1);//
    }
}

/**
 * getting the user's string and creating a trip from it
 */
void Management::parseTrip() {
    int id;
    int startX;
    int startY;
    int endX;
    int endY;
    int psgNum;
    double tarrif;
    unsigned int time;

    if (cin >> id >> startX >> startY >> endX >> endY >> psgNum >> tarrif >> time) {

        //todo what if there is more junk input after the correct one? cin ignore will fix that?
        Trip trip(id, startX, startY, endX, endY, psgNum, tarrif, time);
        //make sure the info is good

        int check = trip.validate();
        if (check == -1) {
            cout << -1 << endl;
            return;
        }
        Map *m = this->taxiCenter->getMap();
        if ((trip.getStartP().getX() > m->getSizeX()) ||
            (trip.getStartP().getY() > m->getSizeY())) {
            cout << -1 << endl;
            return;
        }
        Point endP = trip.getEndP();
        if ((trip.getEndP().getX() > m->getSizeX()) ||
            (trip.getEndP().getY() > m->getSizeY())) {
            cout << -1 << endl;
            return;
        }

        pthread_t *thread = new pthread_t;
        Thread_Runner *thread_runner1 = Thread_Runner::getInstance(this->taxiCenter, this->socket);
        thread_runner1->addTripToCalculate(trip);
        unsigned int trip_Time = trip.getTime();
        LINFO << " this is thread no:    " << pthread_self() << " got a trip for time " << trip_Time;
        Trip_Info *trip_info = new Trip_Info(trip_Time, thread);
        thread_runner1->addTripInfo(trip_info);
        int status = pthread_create(thread, NULL, Thread_Runner::tripHelper, thread_runner1);
        pthread_join(*thread, NULL);
    } else {
        cout << -1 << endl;
        return;
    }
}


/**
 * getting the obstacles from the user
 */
int Management::getObstacles() {
    int numOfObstacle;
    int checker = 0;
    if (cin >> numOfObstacle) {
        if (numOfObstacle >= 0) {
            checker = this->lg.setObstacle(numOfObstacle);
        } else {
            checker = -1;
        }
    } else {
        cin.ignore();
        checker = -1;
    }

    return checker;

}

/**
 * creating a map
 */
int Management::getMap() {
    int check = this->setLogicAndMap();
    if (check == -1) {
        cout << -1 << endl;
    }
    return check;
}

/**
 * creating a map and putting it in the taxi center
 */
int Management::setLogicAndMap() {
    int checker = 0;

    this->lg = Logic(getSizes());
    checker = lg.validate();

    if (checker == -1) {
        return -1;
    }
    checker = this->getObstacles();
    LINFO << " this is main thread: " << " creating map in size ";
    // << lg.getSizeX() << " on " << lg.getSizeY();
    if (checker == -1) {
        return -1;
    }
    Map *map1 = this->lg.createNewMap("Square");
    checker = map1->validate();
    if (checker == -1) {
        delete map1;
    } else {
        this->taxiCenter = new TaxiCenter(map1);
    }
    LINFO << " this is main thread: " << " finish creating";
    return checker;


}

/**
 * @return - a vector with the map sizes given by the user
 */
vector<int> Management::getSizes() {
    vector<int> sizes;
    int firstNum;
    int secondNum;
    //char seperator;
    //cin.ignore();
    if (cin >> firstNum) {
        sizes.push_back(firstNum);
    } else {
        cin.clear();
        cin.ignore();
    }


    if (cin >> secondNum) {
        sizes.push_back(secondNum);
    }
    if (sizes.size() != 2) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    return sizes;
}

/**
 * connect with the client. gets a driver from him and send him taxi.
 * @return the driver from the client
 */
Driver *Management::getDriver() {
    LINFO << " this is thread no:    " << pthread_self() << " getting the driver from client";
    Taxi *t = NULL;
    Driver *d = NULL;
    string serial_str;
    char *buffer = (char *) malloc(BUFFERSIZE * sizeof(char));
    Thread_Manage *thread_manage = Thread_Manage::getInstance();
    int connectionDescriptor = this->socket->acceptClient();
    LINFO << " this is thread no:    " << pthread_self() << "go sock descriptor";

    //Thread_Class *threadClass = new Thread_Class(connectionDescriptor);
    //thread_manage->addThread(pthread_self(), threadClass);
    ssize_t n = this->socket->rcvDataFrom(buffer, BUFFERSIZE, connectionDescriptor);
    if ((n == 8) || (n == 6)) {
        perror("Error in receive");
    }
    LINFO << " this is thread no:    " << pthread_self() << " deserialize the received driver";
    //getting the driver
    boost::iostreams::basic_array_source<char> device(buffer, BUFFERSIZE);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> d;
    LINFO << " this is thread no:    " << pthread_self() << " got a driver with id " << d->getId();
    //attach a taxi to the driver here and send to client
    t = this->taxiCenter->attachTaxiToDriver(d->getVehicle_id());
    //set the driver's taxi
    d->setTaxi(t);
    thread_manage->addDriverDescriptor(d->getId(), connectionDescriptor);
    LINFO << " this is thread no:    " << pthread_self() << " serialize the drivers taxi";
    //serialize the taxi
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << t;
    LINFO << " this is thread no:    " << pthread_self() << " sending back taxi with id " << t->getCarId();
    s.flush();
    n = this->socket->sendDataTo(serial_str, serial_str.size(), connectionDescriptor);
    if (n == 5) {
        perror("Error in Sendto");
    }
    free(buffer);
    LINFO << " this is thread no:    " << pthread_self() << " finish with getDriver func";
    //return the driver for the thread here to manage
    return d;
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

Map *Management::getM() const {
    return m;
}

int Management::getUserChoise() {
    int userChoice;
    bool check = false;
    if (cin >> userChoice) {
        if ((userChoice >= 0) && (userChoice <= 7) && (userChoice != 5)) {
            check = true;
        } else {
            cout << -1 << endl;
        }
    } else {
        cout << -1 << endl;
    }
    if (!check) {
        while (check != true) {
            if (userChoice == 0) {
                cin.clear();
                cin.ignore();
            }
            if (cin >> userChoice) {
                if ((userChoice >= 0) && (userChoice <= 7) && (userChoice != 5)) {
                    check = true;
                } else {
                    cout << -1 << endl;
                }

            } else {
                cout << -1 << endl;
            }
        }
    }
    return userChoice;
}

int Management::parseNumOfDrivers() {
    int userChoice;
    bool check = false;
    if (cin >> userChoice) {
        if ((userChoice >= 0)) { //todo check 0 drivers is wrong?? if it is not good this func will need chanch
            //todo check why 0 time for trip is wrong
            check = true;
        } else {
            cout << -1 << endl;
        }
    } else {
        cout << -1 << endl;
    }
    if (check == true) {
        return userChoice;
    }
    return -1;
}
