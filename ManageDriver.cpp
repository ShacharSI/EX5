//
// Created by haim on 12/27/16.
//
#define BUUFER_SIZE 200000

#include "Trip.h"
#include "ManageDriver.h"
#include "LuxuryTaxi.h"
#include "StandardTaxi.h"
#include "Square.h"
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
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

using namespace boost;

/**
 * runs the all program
 * getting a taxi then getting a trio
 * then moving the driver and again and again
 * until the sign to stop the program
 */
void ManageDriver::manage() {
    //ask and set taxi
    this->setTaxi();
    Trip trip;
    char *buffer = (char *) malloc(BUUFER_SIZE * sizeof(char));
    int n = 0;
    string serial_str2;
    std::list<std::list<Searchable*>*> lists;
    //ask for trip - send the driver to confirm location
    string askTrip = "sendMeTrip";
    //send the driver
    n = this->socket->sendData(askTrip, askTrip.size());
    if (n == 5) {
        perror("Error in Sendto");
    }

    //get back the list of serchables that represents the routh
    n = this->socket->reciveData(buffer, BUUFER_SIZE);

    if ((n == 8) || (n == 6)) {
        perror("Error in receiving");
    }
    std::list<Searchable *>* moveList = new list<Searchable *>;
    string finish = "Finished";
    while (strcmp(buffer, "End_Communication") != 0) {
        //deserialze trip's routh
        std::list<Searchable *>* list = new std::list<Searchable*>;

        boost::iostreams::basic_array_source<char> device(buffer, BUUFER_SIZE);
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        ia >> *list;
        lists.push_back(list);
        this->copyToList(list,moveList);
        //set the routh
        this->d->setRouth(list);
        //ask the server for permission to move
        string sendMegGo = "sendMeGo";
        //moving the trip entire routh ask for permission every step
        while ((this->d->getTaxi()->getRouth()->size() > 0)
               && (strcmp(buffer, "End_Communication") != 0)) {
            //ask the server for go

            n = this->socket->sendData(sendMegGo, sendMegGo.size());
            if (n == 5) {
                perror("Error in Sendto");
            }
            //get answer from server
            n = this->socket->reciveData(buffer, BUUFER_SIZE);


            if ((n == 8) || (n == 6)) {
                perror("Error in receiving");
            }
            serial_str2 = buffer;
            //if it is go then move
            if (strcmp("Go", buffer) == 0) {
                this->d->getTaxi()->move();
            }
        }
        //if we got the order to stop
        if ((strcmp(buffer, "End_Communication") == 0)) {
            break;
        }
        //ask for next trip

        n = this->socket->sendData(askTrip, askTrip.size());
        if (n == 5) {
            perror("Error in Sendto");
        }
        //get the routh
        n = this->socket->reciveData(buffer, BUUFER_SIZE);


        if (n < 0) {
            perror("Error in receiving");
        }

    };
    //release data
    while(!moveList->empty()){
        Searchable* temp = moveList->front();
        moveList->pop_front();
        delete temp;
    }
    delete moveList;
    while(!lists.empty()){
        std::list<Searchable*>* l = lists.front();
        lists.pop_front();
        delete l;
    }
    free(buffer);
}

/**
 * the destructor
 */
ManageDriver::~ManageDriver() {
    delete this->d;
    delete this->socket;
}

/**
 * asking for a taxi from the server
 * then getting the taxi form him and setting the taxi
 */
void ManageDriver::setTaxi() {
    char *buffer = (char *) malloc(BUUFER_SIZE * sizeof(char));
    ssize_t n = 0;
    Taxi *t = NULL;
    //serialize and send driver
    std::string serial_str;
    iostreams::back_insert_device<std::string> inserter(serial_str);
    iostreams::stream<iostreams::back_insert_device<std::string> > s(inserter);
    archive::binary_oarchive oa(s);
    oa << this->d;
    s.flush();
    n = this->socket->sendData(serial_str, serial_str.size());
    if (n < 0) {
        perror("Error in Sendto");
    }
    //receive the driver's taxi
    n = socket->reciveData(buffer, BUUFER_SIZE);
    if (n < 0) {
        perror("Error in ReciveFrom");
    }
    //deserialize and set taxi //
    iostreams::basic_array_source<char> inserter1(buffer, BUUFER_SIZE);
    iostreams::stream<iostreams::basic_array_source<char> > s1(inserter1);
    archive::binary_iarchive ia1(s1);
    ia1 >> t;
    this->d->setTaxi(t);
    free(buffer);
}

/**
 * the constructor
 */
ManageDriver::ManageDriver(string s, Tcp *soc) {
    this->d = new Driver(s);
    this->socket = soc;
}
/**
 * copy one list into another one
 * @param list src list
 * @param moveList dst list
 */
void ManageDriver::copyToList(std::list<Searchable *> *list, std::list<Searchable *> *moveList) {
    long size = list->size();
    for(int i = 0; i< size; i++){
        Searchable* temp = list->front();
        moveList->push_back(temp);
        list->pop_front();
        list->push_back(temp);
    }
}
