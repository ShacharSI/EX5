//
// Created by haim6678 on 09/01/17.
//

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include "Thread_Runner.h"
#include "Management.h"
#include "LuxTaxiFactory.h"
#include <stdlib.h>
#include <cstdlib>
#include "StandardTaxi.h"
#include "LuxuryTaxi.h"
#include "Thread_Runner.h"
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

#define BUFFERSIZE 4096

Thread_Runner::Thread_Runner(TaxiCenter *t) {
    this->massege = "";
    this->taxiCenter = t;
    this->socketDesMap = new map<Driver*,int>();
}

void *Thread_Runner::run(void *) {
    //todo create communication
    this->getDriver();
}

void Thread_Runner::getDriver(Socket* socket) {
    ssize_t n;
    Taxi *t = NULL;
    Driver *d = NULL;
    string serial_str;
    char *buffer = (char *) malloc(BUFFERSIZE * sizeof(char));
    int connectionDescriptor = socket->acceptClient();
    ssize_t n = socket->rcvDataFrom(buffer, 4096,connectionDescriptor);
    if (n < 0) {
        perror("Error in receive");
    }
    create connection or get working tcp then input it to the map with the driver

    //getting the driver
    boost::iostreams::basic_array_source<char> device(buffer, BUFFERSIZE);
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
    boost::archive::binary_iarchive ia(s2);
    ia >> d;
    enter the driver and his socket descriptor to the map
    the map will be here or in the taxi center

    //attach a taxi to the driver in our list and return the taxi to send to client
    t = this->taxiCenter->attachTaxiToDriver(d->getVehicle_id());

    //serialize the taxi
    boost::iostreams::back_insert_device<std::string> inserter(serial_str);
    boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
    boost::archive::binary_oarchive oa(s);
    oa << t;
    s.flush();
    //send the taxi to client
    n = this->socket->sendData(serial_str, serial_str.size());
    if (n < 0) {
        perror("error sending");
    }
    d->setTaxi(t);
    this->taxiCenter->addDriverToCenter(d);
    free(buffer);
}

void Thread_Runner::getTrip() {

    //if he finished moving
    if (d->getTaxi()->getRouth().size() == 0) {
        d->inactivate(this->taxiCenter->getNotActiveDriver,
                      this->taxiCenter->getActiveDriver());
    }
    if (this->taxiCenter->getNotActiveDriver()->size() == 0) {
        return;
    }
    long size = this->taxiCenter->getTrips()->size();
    std::list<Searchable *> list;
    std::string serial_str;
    char *buffer = (char *) malloc(4096 * sizeof(char));
    //getting the trip that is time arrived
    for (int i = 0; i < size; i++) {
        Trip temp = this->taxiCenter->getTrips()->front();
        if (temp.getTime() == taxiCenter->getTime()) {
            memset(buffer, 0, 4096);
            //getting the driver from client
            ssize_t n = this->socket->reciveData(buffer, 4096);
            if (n < 0) {
                perror("Error in receive");
            }

            //deserialize the driver
            Driver *d;
            boost::iostreams::basic_array_source<char> device(buffer, 4096);
            boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
            boost::archive::binary_iarchive ia(s2);
            ia >> d;

            list = this->taxiCenter->sendTrip(temp, d);
            delete d;
            //sending back the list for the client
            boost::iostreams::back_insert_device<std::string> inserter(serial_str);
            boost::iostreams::stream<boost::iostreams::back_insert_device<std::string> > s(inserter);
            boost::archive::binary_oarchive oa(s);
            oa << list;
            s.flush();
            n = this->socket->sendData(serial_str, serial_str.size());
            if (n < 0) {
                perror("Error in Sendto");
            }
            //if everything was ok the list would not be empty
            if (list.size() > 0) {
                this->taxiCenter->getTrips()->pop();
                break;
            }
            //continue search for matching trip
        } else {
            this->taxiCenter->getTrips()->pop();
            this->taxiCenter->getTrips()->push(temp);
        }
    }
    free(buffer);
}

