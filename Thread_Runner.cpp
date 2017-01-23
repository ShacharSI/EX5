
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include "Thread_Runner.h"
#include "Thread_Manage.h"
#include "Searchable.h"
#include "Bfs.h"
#include "StandardTaxi.h"
#include "LuxuryTaxi.h"
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/export.hpp>
#include "easylogging++.h"
BOOST_CLASS_EXPORT_GUID(StandardTaxi, "StandardTaxi")
BOOST_CLASS_EXPORT_GUID(LuxuryTaxi, "lux_taxi")
BOOST_CLASS_EXPORT_GUID(Taxi, "taxi")
BOOST_CLASS_EXPORT_GUID(Driver, "driver")
BOOST_CLASS_EXPORT_GUID(Point, "point")
BOOST_CLASS_EXPORT_GUID(Square, "Square")

#define BUFFERSIZE 200000
Thread_Runner *Thread_Runner::instance = NULL;
//initialize the mutexes
Mutex_Locker *Thread_Runner::instanceLocker = new Mutex_Locker();
Mutex_Locker *Thread_Runner::printLocker = new Mutex_Locker();
Mutex_Locker *Thread_Runner::tripsLocker = new Mutex_Locker();
Mutex_Locker *Thread_Runner::driverLocker = new Mutex_Locker();
bool Thread_Runner::created = false;

bool Thread_Runner::Occupy() {
    if (!inUse) {
        this->inUse = true;
        return true;
    }
    return false;
}
/**
 * @return an instance of the class
 */
Thread_Runner *Thread_Runner::getInstance(TaxiCenter *c, Tcp *t) {
    if (!Thread_Runner::created) {
        Thread_Runner::instanceLocker->lock();
        if (!Thread_Runner::created) {
            Thread_Runner::instance = new Thread_Runner(c, t);
            Thread_Runner::created = true;
        }
        Thread_Runner::instanceLocker->unlock();
    }
    return instance;
}
/**
 * runs one thread. deal with communication with one client
 */
void *Thread_Runner::run(void) {

    LINFO << " this is thread no:    " << pthread_self() << " this is the start of the thread";
    Thread_Manage *thread_manage = Thread_Manage::getInstance();
    //add the thread to threadList
    Driver *d;
    std::list<Searchable *> *list;
    LINFO << " this is thread no:    " << pthread_self() << " create contact and get driver";
    //get the driver from the client
    d = this->getDriver();
    char *buffer = (char *) malloc(BUFFERSIZE * sizeof(char));
    LINFO << " this is thread no:    " << pthread_self() << " finish the first connection ";
    int time = 0;
    //get client's connectionDescriptor
    int connectionDescriptor = thread_manage->getThreadsSocketDescriptor(d->getId());
    LINFO << " this is thread no:    " << pthread_self() << " got sock descriptor " << connectionDescriptor;
    string serial_str;
    Thread_Manage *manage = Thread_Manage::getInstance();
    std::queue<string> *messageQueue = manage->getThreadsQueue(d->getId());
    //hold the thread till accepting new message
    LINFO << " this is thread no:    " << pthread_self() << " wait for massage";
    while (messageQueue->empty()) {};
    std::list<std::list<Searchable*>*> lists;
    LINFO << " this is thread no:    " << pthread_self() << " getting rout";
    list = this->checkTrips(d,time);

    LINFO << " this is thread no:    " << pthread_self() << " getting in the main loop that manage the driver";
    //running the driver until we got 7 from server
    while (strcmp(messageQueue->front().c_str(), "End_Communication") != 0) {
        //if we got give location
        if (((!messageQueue->empty())
             && strcmp(messageQueue->front().c_str(), "GiveLocation") == 0)) {
            LINFO << " this is thread no:    " << pthread_self() << " print drivers location";
            Thread_Runner::printLocker->lock();
            Point p = d->getLocation();
            cout << p;
            Thread_Runner::printLocker->unlock();
            thread_manage->popMessage(d->getId());
        }
        // if we got go and there is no rout yet
        if (((!messageQueue->empty())
             && (strcmp(messageQueue->front().c_str(), "Go") == 0)
             && (list == NULL))) {
            time += 1;
            thread_manage->popMessage(d->getId());
        }
        //if we did got a valid trip
        if (list != NULL) {
            LINFO << " this is thread no:    " << pthread_self() << " got routh in size " << list->size();
            lists.push_back(list);
            //set the new route in our driver
            d->setRouth(list);
            LINFO << " this is thread no:    " << pthread_self() << " get request for trip from client";
            //get request to trip from client
            ssize_t size = this->tcpSock->rcvDataFrom(buffer, BUFFERSIZE, connectionDescriptor);
            if ((size == 8) || (size == 6)) {
                perror("Error in receive");
            }

            if (strcmp(buffer, "sendMeTrip") == 0) {
                serial_str = "\0";
                //send the rout also to the client
                LINFO << " this is thread no:    " << pthread_self() << " sereialize rout";
                boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << *list;
                s.flush();
                LINFO << " this is thread no:    " << pthread_self() << " sending rout size: " << list->size();
                int n = tcpSock->sendDataTo(serial_str, serial_str.size(), connectionDescriptor);
                if (n == 5) {
                    perror("Error in Sendto");
                }
            }
        } else {
            LINFO << " this is thread no:    " << pthread_self() << " there is no rout yet. keep waiting";
        }
        //if we are still running the program, and we still have a routh to go
        while ((!messageQueue->empty())
               && (d->getTaxi()->getRouth() != NULL)
               && (d->getTaxi()->getRouth()->size() > 0)
               && (strcmp(messageQueue->front().c_str(), "End_Communication")) != 0) {
            LINFO << " this is thread no:    " << pthread_self() << " in the loop that moves the driver";
            //if we got go
            if (((!messageQueue->empty())
                 && (strcmp(messageQueue->front().c_str(), "Go") == 0))) {

                time += 1;
                LINFO << " this is thread no:    " << pthread_self() << " move the driver here";
                //move our driver
                d->move();
                LINFO << " this is thread no:    " << pthread_self() << " got request from client to move";
                //get request to go
                ssize_t size = this->tcpSock->rcvDataFrom(buffer, BUFFERSIZE, connectionDescriptor);
                if ((size == 8) || (size == 6)) {
                    perror("Error in receive");
                }
                //verify the request
                if (strcmp(buffer, "sendMeGo") == 0) {
                    //send go
                    LINFO << " this is thread no:    " << pthread_self() << " send client go";
                    int n = tcpSock->sendDataTo(messageQueue->front().c_str(), messageQueue->front().size(),
                                                connectionDescriptor);
                    if (n == 5) {
                        perror("Error in Send_to");
                    }
                }
                //todo add mutex
                if(d->getTaxi()->getRouth()->size() == 0){
                    this->pushNotActiveDriver(d);
                }
            }
            //if we got give location
            if (((!messageQueue->empty())
                 && (strcmp(messageQueue->front().c_str(), "GiveLocation") == 0))) {

                LINFO << " this is thread no:    " << pthread_self() << " print drivers location";
                Thread_Runner::printLocker->lock();
                Point p = d->getLocation();
                cout << p;
                Thread_Runner::printLocker->unlock();
            }
            thread_manage->popMessage(d->getId());
            LINFO << " this is thread no:    " << pthread_self() << " wait for massage";
            //hold the thread till accepting new message
            while (messageQueue->empty()) {
            };
        }

        if ((!messageQueue->empty())) {
            if ((strcmp(messageQueue->front().c_str(), "End_Communication") == 0)) {
                break;
            }
        }

        //hold the thread till accepting new message
        LINFO << " this is thread no:    " << pthread_self() << " wait for next massage";
        while (messageQueue->empty());
        LINFO << " this is thread no:    " << pthread_self() << " getting rout";
        list = this->checkTrips(d,time);
    }

    LINFO << " this is thread no:    " << pthread_self() << " sending the client end communication";
    ssize_t size = this->tcpSock->rcvDataFrom(buffer, BUFFERSIZE, connectionDescriptor);
    if ((size == 8) || (size == 6)) {
        perror("Error in receive");
    }
    int n = tcpSock->sendDataTo(messageQueue->front().c_str(), messageQueue->front().size(),
                                connectionDescriptor);
    if (n == 5) {
        perror("Error in Send_to");
    }
    thread_manage->popMessage(d->getId());
    free(buffer);
    while(!lists.empty()){
        std::list<Searchable*>* l = lists.front();
        lists.pop_front();
        delete l;
    }
    delete d;

}
/**
 * gets a driver from the initial list of drivers
 * @return the driver from the client
 */
Driver *Thread_Runner::getDriver() {
    //todo add mutex
    Driver * temp = this->initialList->front();
    this->initialList->pop_front();
    return temp;
}
/**
 * creates a thread for bfs calculation
 * add the result to the thread_manage
 */
void *Thread_Runner::getTrip(void) {
    LINFO << " this is thread no:    " << pthread_self() << " calculating bfs";
    Trip trip;
    Thread_Runner::tripsLocker->lock();
    if (this->tripsToCalculate.size() == 0) {
        pthread_exit(NULL);
    }
    trip = this->tripsToCalculate.front();
    this->tripsToCalculate.pop();
    Thread_Runner::tripsLocker->unlock();
    Bfs bfs;
    std::list<Searchable *> *list;

    LINFO << " this is thread no:    " << pthread_self() << " getting the trips start and end point";
    //get the point on the map
    Searchable *start = *this->m->getSearchableByCoordinate(trip.getStartP());
    Searchable *end = *this->m->getSearchableByCoordinate(trip.getEndP());

    LINFO << " this is thread no:    " << pthread_self() << " calculating bfs from: ";
    //create a trip info class and save it
    list = bfs.findRouth(start, end, this->m);
    LINFO << " this is thread no:    " << pthread_self() << " got a rout in length " << list->size();
    Thread_Runner::tripsLocker->lock();
    unsigned int trip_Time = trip.getTime();
    LINFO << " this is thread no:    " << pthread_self() << " got a trip for time " << trip_Time;
    Trip_Info *trip_info = new Trip_Info(trip_Time, list);
    this->trips.push_back(trip_info);
    Thread_Runner::tripsLocker->unlock();
    LINFO << " this is thread no:    " << pthread_self() << " finishing !";
    return 0;
}

/**
 * check for trip that its time arrived
 * and than checks if it fits to the driver of the specific thread
 * @return the route of the bfs
 */
std::list<Searchable *> *Thread_Runner::checkTrips(Driver *d,int time) {
    std::list<Searchable *> *list = NULL;
    Thread_Runner::tripsLocker->lock();
    long size = this->trips.size();
    Thread_Runner::tripsLocker->unlock();
    int trip_Time;
    Trip_Info *trip_info;
    //checking if a trip's time is arrived
    Thread_Runner::tripsLocker->lock();
    for (int i = 0; i < size; i++) {
        trip_info = this->trips.front();
        trip_Time = trip_info->getTripTime();
        //checking if a trip's start location is equals to the taxi's location
        if (trip_Time == time) {
            if (d->getLocation().equals(trip_info->getRouth()->front()->getPoint())) {
                if(this->checkFirstDriver(d)) {
                    list = trip_info->getRouth();
                    this->trips.pop_front();
                    delete trip_info;
                    Thread_Runner::tripsLocker->unlock();
                    return list;
                } else{
                    Thread_Runner::tripsLocker->unlock();
                    return NULL;
                }
            }
        }
        this->trips.pop_front();
        this->trips.push_back(trip_info);
    }
    Thread_Runner::tripsLocker->unlock();
    //return the route of the trip that is time arrived
    return list;
}
/**
 * static function that runs the run function
 */

void *Thread_Runner::runHelper(void *v) {
    return ((Thread_Runner *) v)->run();
}
/**
 * static function that runs the getTrip function
 */

void *Thread_Runner::tripHelper(void *v) {
    return ((Thread_Runner *) v)->getTrip();
}
/**
 * add Trip To the queue for future calculation
 * @param t a trip
 */

void Thread_Runner::addTripToCalculate(Trip t) {
    this->tripsToCalculate.push(t);
}
/**
 * d-tor
 */
Thread_Runner::~Thread_Runner() {
    delete this->instanceLocker;
    delete this->driverLocker;
    delete this->tripsLocker;
    delete this->printLocker;

    delete this->notActiveDrivers;
    delete this->initialList;

    if (!this->trips.empty()) {
        Trip_Info *temp = this->trips.front();
        this->trips.pop_front();
        delete temp;
    }
}
/**
 * adds driver to the not-Active Drivers list
 * @param d
 */
void Thread_Runner::pushNotActiveDriver(Driver *d) {
    this->notActiveDrivers->push_back(d);
}
/**
 * check whether the driver is the first driver that arrived to this location
 */
bool Thread_Runner::checkFirstDriver(Driver *d) {
    std::list<Driver*> l;
    bool returnBool = false;
    long size = this->notActiveDrivers->size();
    for (int i = 0; i < size ; ++i) {
        Driver* checkDriver = this->notActiveDrivers->front();
        if((checkDriver->getLocation().equals(d->getLocation()))
           &&(checkDriver->getId() != d->getId())){
            break;
        }
        if(checkDriver->getId() == d->getId()) {
            returnBool = true;
            this->notActiveDrivers->pop_front();
            break;
        }
        this->notActiveDrivers->pop_front();
        l.push_back(d);
    }
    while (!l.empty()){
        Driver* d = l.back();
        this->notActiveDrivers->push_front(d);
        l.pop_back();
    }
    return returnBool;
}
/**
 * add one driver to the initial list of drivers
 */
void Thread_Runner::pushInitialDriver(Driver *d) {
    this->initialList->push_back(d);
}
