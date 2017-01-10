


#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include "Thread_Runner.h"
#include "Management.h"
#include "LuxTaxiFactory.h"
#include <stdlib.h>
#include <cstdlib>
#include "StandardTaxi.h"
#include "LuxuryTaxi.h"
#include "Trip_Info.h"
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
#include <bits/valarray_before.h>

#define BUFFERSIZE 4096

Thread_Runner::Thread_Runner(TaxiCenter *t) {
    this->massege = "";
    this->taxiCenter = t;
    this->socketDesMap = new map<Driver *, int>();
    this->numLiveConnections = 0;
    this->numReadMassage = 0; //todo will update for everyone if not on stack?
}

void *Thread_Runner::run(void *s) {

    Driver *d;
    std::list<Searchable *> list;
    char *buffer = (char *) malloc(4906 * sizeof(char));
    //get the driver from the client
    d = this->getDriver((Socket *) s);
    //run the thread
    while (strcmp(this->massege.c_str(), "End_Communicatipn") != 0) {
        //get a trip
        list = this->checkTrips(d);
        //if we did got a valid trip
        if (list.size() > 0) {
            //set the routh in our driver
            d->setRouth(list);
            this->taxiCenter->setRout(d,list);
            //send the routh to the client
            boost::iostreams::basic_array_source<char> device(buffer, 4096);
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
            boost::archive::binary_iarchive ia(s2);
            ia >> list;
            //todo send list to client

        }
        //if we are still running the program, and we still have a routh to go
        while ((d->getTaxi()->getRouth().size() > 0)
               && (strcmp(this->massege.c_str(), "End_Communication")) != 0) {
            if (strcmp(this->massege.c_str(), "GO") == 0) {
                d->move();

                //todo - get socket descriptor form map
                //todo - send "go" for the client
                this->numReadMassage += 1;
            }
            //if everyone Already seen the massage the reset it
            if (this->numLiveConnections == numReadMassage) {
                this->massege = "";
            }

        }
        if (strcmp(this->massege.c_str(), "End_Communication") == 0) {
            break;
        }
    }

    //todo send end communication to client and close the socket
    free(buffer);
}

Driver *Thread_Runner::getDriver(Tcp *socket) {
    Taxi *t = NULL;
    Driver *d = NULL;
    string serial_str;
    char *buffer = (char *) malloc(BUFFERSIZE * sizeof(char));
    //initialize connection  //todo to this here?
    int connectionDescriptor = socket->acceptClient();
    ssize_t n = socket->rcvDataFrom(buffer, 4096, connectionDescriptor);
    if (n < 0) {
        perror("Error in receive");
    }
    //getting the driver
    boost::iostreams::basic_array_source<char> device(buffer, BUFFERSIZE);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> d;
    pthread_mutex_lock();
    //saving the client's socket descriptor for later communication with him
    this->socketDesMap->insert(std::pair<Driver *, int>(d, connectionDescriptor));
    //note that there is one more client
    this->numLiveConnections += 1;
    //attach a taxi to the driver here and send to client
    t = this->taxiCenter->attachTaxiToDriver(d->getVehicle_id());
    //set the driver's taxi
    d->setTaxi(t);
    pthread_mutex_unlock();
    //serialize the taxi
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << t;
    s.flush();
    //todo send the taxi back to the client


    this->taxiCenter->addDriverToCenter(d);

    free(buffer);
    //return the driver for the thread here to manage
    return d;
}

void *Thread_Runner::getTrip(void *t) {

    Trip *trip;
    trip = (Trip *) t;
    Bfs bfs;
    std::list<Searchable *> list;

    //get the point on the map
    Searchable *start = *this->m->getSearchableByCoordinate(trip->getStartP());
    Searchable *end = *this->m->getSearchableByCoordinate(trip->getEndP());
    //get the rout between points
    list = bfs.findRouth(start, end, this->m);
    //create a trip info class and save it
    unsigned int trip_Time = trip->getTime();
    Trip_Info *trip_info = new Trip_Info(trip_Time, list);
    this->trips.push_front(trip_info);

    return 0; //todo return 0?
}

Map *Thread_Runner::getMap() const {
    return m;
}

std::list<Searchable *> Thread_Runner::checkTrips(Driver *d) {
    std::list<Searchable *> list;
    int size = this->trips.size();
    int trip_Time;
    Trip_Info *trip_info;
    //checking if a trip's time is arrived
    for (int i = 0; i < size; i++) { //todo what if there are a couple of drivers in the same point
        trip_info = this->trips.front();
        trip_Time = trip_info->getTripTime();
        //checking if a trip's start location is equals to the taxi's location
        if (trip_Time == this->taxiCenter->getTime()) {
            if (d->getLocation().equals(trip_info->getRouth().front()->getPoint())) {
                list = trip_info->getRouth();
                trip_info->setTripTime(-1); //todo need this? also.. pop here? also -1 and unsigned
                this->trips.pop_front();
                return list;
            }
        }
        this->trips.pop_front();
        this->trips.push_back(trip_info);
    }
    //return the rout of the trip that is time arrived
    return list;
}

