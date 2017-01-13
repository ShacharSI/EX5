
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include "Thread_Runner.h"
#include "Thread_Manage.h"
#include "Bfs.h"
#include "StandardTaxi.h"
#include "LuxuryTaxi.h"
#include "easyloggingpp-8.91/easylogging++.h"
#include <fstream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/export.hpp>

BOOST_CLASS_EXPORT_GUID(StandardTaxi, "StandardTaxi")
BOOST_CLASS_EXPORT_GUID(LuxuryTaxi, "lux_taxi")
BOOST_CLASS_EXPORT_GUID(Taxi, "taxi")
BOOST_CLASS_EXPORT_GUID(Driver, "driver")
BOOST_CLASS_EXPORT_GUID(Point, "point")
BOOST_CLASS_EXPORT_GUID(Square, "Square")

#define BUFFERSIZE 4096
Thread_Runner *Thread_Runner::instance = NULL;
Mutex_Locker *Thread_Runner::instanceLocker = new Mutex_Locker();
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

void *Thread_Runner::run(void) {
    LINFO << " this is thread no: " << pthread_self() << " this is the start of the thread";
    Thread_Manage *thread_manage = Thread_Manage::getInstance();
    //create the thread handler
    std::queue<string>* messageQueue = new queue<string>;
    //set driver's thread's queueMessage
    thread_manage->addQueueMessage(pthread_self(), messageQueue);
    //add the thread to threadList
    thread_manage->addThread(pthread_self());
    Driver *d;
    std::list<Searchable *>* list;
    char *buffer = (char *) malloc(BUFFERSIZE * sizeof(char));
    //get the driver from the client
    d = this->getDriver();
    LINFO << " this is thread no: " << pthread_self() << " finish the first connection " ;
    //queue<string>* messageQueue = thread_manage->getThreadsQueue(pthread_self());
    //get client's connectionDescriptor
    int connectionDescriptor = thread_manage->getThreadsSocketDescriptor(pthread_self());
    LINFO << " this is thread no: " << pthread_self() << " got sock descriptor " << connectionDescriptor;
    //run the thread
    string serial_str;
    //hold the thread till accepting new message


    while (messageQueue->empty()){};
    list = this->checkTrips(d);


    while (strcmp(messageQueue->front().c_str(), "End_Communication") != 0) {
        //get a trip

        //if we did got a valid trip
        if (list!= NULL) {
            LINFO << "this is thread no: " << pthread_self() << " got routh in size " << list->size();
            //set the routh in our driver
            d->setRouth(list);
            ssize_t size = this->tcpSock->rcvDataFrom(buffer, 4096, connectionDescriptor);
            if (strcmp(buffer, "sendMeTrip") == 0) {
                //send the routh to the client
                boost::iostreams::back_insert_device<std::string> inserter(serial_str);
                boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
                boost::archive::binary_oarchive oa(s);
                oa << list;
                s.flush();
                int n = tcpSock->sendDataTo(serial_str, serial_str.size(), connectionDescriptor);
                if (n < 0) {
                    perror("Error in Sendto");
                }
            }
        }else{
            LINFO << "this is thread no: " << pthread_self() << " there is no rout yet";
        }
        //if we are still running the program, and we still have a routh to go
        while ((d->getTaxi()->getRouth()!=NULL)&&(d->getTaxi()->getRouth()->size() > 0)
               && (strcmp(messageQueue->front().c_str(), "End_Communication")) != 0) {
            if (strcmp(messageQueue->front().c_str(), "GO") == 0) {
                d->move();
                int n = tcpSock->sendDataTo(messageQueue->front().c_str(), messageQueue->front().size(),
                                            connectionDescriptor);
                if (n < 0) {
                    perror("Error in Send_to");
                }
            }
            if (strcmp(messageQueue->front().c_str(), "GiveLocation") == 0) {
                Point p = d->getLocation();
                cout << p;
            }
            thread_manage->popMessage(pthread_self());
            //hold the thread till accepting new message
            while (messageQueue->empty());
        }

        if (strcmp(messageQueue->front().c_str(), "End_Communication") == 0) {
            break;
        }

        if((strcmp(messageQueue->front().c_str(), "GO") == 0)&&(list == NULL)){
            thread_manage->popMessage(pthread_self());
        }
        if(strcmp(messageQueue->front().c_str(), "GiveLocation") == 0){
            Point p = d->getLocation();
            cout<<p;
            thread_manage->popMessage(pthread_self());
        }
        //hold the thread till accepting new message
        while (messageQueue->empty());
        list = this->checkTrips(d); //todo it's ok here?
    }
    int n = tcpSock->sendDataTo(messageQueue->front().c_str(), messageQueue->front().size(),
                                connectionDescriptor);
    if (n < 0) {
        perror("Error in Send_to");
    }
    thread_manage->popMessage(pthread_self());
    //todo send end communication to client and close the socket
    free(buffer);
}

Driver *Thread_Runner::getDriver() {
    LINFO << " this is thread no: " << pthread_self() << " getting the driver from client";
    Taxi *t = NULL;
    Driver *d = NULL;
    string serial_str;
    char *buffer = (char *) malloc(BUFFERSIZE * sizeof(char));
    Thread_Manage *thread_manage = Thread_Manage::getInstance();
    int connectionDescriptor = this->tcpSock->acceptClient();
    LINFO << " this is thread no: " << pthread_self() <<
          " create connection to client in sock descriptor " << connectionDescriptor;
    Thread_Class *threadClass = new Thread_Class(connectionDescriptor);
    thread_manage->addThread(pthread_self(), threadClass);
    ssize_t n = this->tcpSock->rcvDataFrom(buffer, 4096, connectionDescriptor);
    if (n < 0) {
        perror("Error in receive");
    }
    //getting the driver
    boost::iostreams::basic_array_source<char> device(buffer, BUFFERSIZE);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> d;
    LINFO << " this is thread no: " << pthread_self() << " got driver with id " << d->getId();
    Thread_Runner::driverLocker->lock();
    //saving the client's socket descriptor for later communication with him
    thread_manage->addDriver(d, connectionDescriptor);
    thread_manage->addDriverAndPthread(pthread_self(),d);
    //attach a taxi to the driver here and send to client
    t = this->taxiCenter->attachTaxiToDriver(d->getVehicle_id());
    //set the driver's taxi
    d->setTaxi(t);
    Thread_Runner::driverLocker->unlock();
    //serialize the taxi
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << t;
    LINFO << " this is thread no: " << pthread_self() << " sending back taxi with id " << t->getCarId();
    s.flush();
    n = this->tcpSock->sendDataTo(serial_str, serial_str.size(), connectionDescriptor);
    if (n < 0) {
        perror("Error in Sendto");
    }
    free(buffer);
    //return the driver for the thread here to manage
    return d;
}

void *Thread_Runner::getTrip(void) {
    LINFO << " this is thread no: " << pthread_self() << " calculating bfs";
    Trip trip;
    Thread_Runner::tripsLocker->lock();
    if (this->tripsToCalculate.size() == 0) {
        pthread_exit(NULL);
    }
    trip = this->tripsToCalculate.front();
    this->tripsToCalculate.pop();
    Thread_Runner::tripsLocker->unlock();
    Bfs *bfs = new Bfs();
    std::list<Searchable *>* list;

    //get the point on the map
    Searchable *start = *this->m->getSearchableByCoordinate(trip.getStartP());
    Searchable *end = *this->m->getSearchableByCoordinate(trip.getEndP());
    //get the route between points
    /*pthread_t t;
    bfsThreadStruct* threadStruct = new bfsThreadStruct;
    threadStruct->start = start;
    threadStruct->end = end;
    threadStruct->map =this->m;
    threadStruct->bfsPointer = bfs;
    threadStruct->list = list;
    pthread_create(&t,NULL,Bfs::findRouthRunner,(void*)threadStruct);*/
    //create a trip info class and save it
    list = bfs->findRouth(start, end, this->m);
    LINFO << " this is thread no: " << pthread_self() << " got a rout in length " << list->size();
    Thread_Runner::tripsLocker->lock();
    unsigned int trip_Time = trip.getTime();
    Trip_Info *trip_info = new Trip_Info(trip_Time, list);
    this->trips.push_front(trip_info);
    Thread_Runner::tripsLocker->unlock();
    return 0;
}


std::list<Searchable *>* Thread_Runner::checkTrips(Driver *d) {
    std::list<Searchable *>* list = NULL;
    long size = this->trips.size();
    int trip_Time;
    Trip_Info *trip_info;
    //checking if a trip's time is arrived
    Thread_Runner::tripsLocker->lock();
    for (int i = 0; i < size; i++) { //todo what if there are a couple of drivers in the same point
        trip_info = this->trips.front();
        trip_Time = trip_info->getTripTime();
        //checking if a trip's start location is equals to the taxi's location
        if (trip_Time == this->taxiCenter->getTime()) {
            if (d->getLocation().equals(trip_info->getRouth()->front()->getPoint())) {
                list = trip_info->getRouth();
                trip_info->setTripTime(-1); //todo need this? also.. pop here? also -1 and unsigned
                this->trips.pop_front();
                return list;
            }
        }
        this->trips.pop_front();
        this->trips.push_back(trip_info);
    }
    Thread_Runner::tripsLocker->unlock();
    //return the route of the trip that is time arrived
    return list;
}

void *Thread_Runner::runHelper(void *v) {
    return ((Thread_Runner *) v)->run();
}

void *Thread_Runner::tripHelper(void *v) {
    return ((Thread_Runner *) v)->getTrip();
}

void Thread_Runner::addTripToCalculate(Trip t) {
    this->tripsToCalculate.push(t);
}

Thread_Runner::~Thread_Runner() {
    delete this->instanceLocker;
    delete this->driverLocker;
    delete this->tripsLocker;

    delete this->instance;

    if (!this->trips.empty()) {
        Trip_Info *temp = this->trips.front();
        this->trips.pop_front();
        delete temp;
    }
}

