//
// Created by haim on 12/27/16.
//
#define BUUFER_SIZE 4096

#include "ManageDriver.h"
#include "LuxuryTaxi.h"
#include "StandardTaxi.h"
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

BOOST_CLASS_EXPORT_GUID(StandardTaxi, "StandardTaxi");
BOOST_CLASS_EXPORT_GUID(LuxuryTaxi, "lux_taxi");
BOOST_CLASS_EXPORT_GUID(Taxi, "taxi");
BOOST_CLASS_EXPORT_GUID(Driver, "driver");
BOOST_CLASS_EXPORT_GUID(Point, "point");
BOOST_CLASS_EXPORT_GUID(Square, "Square");

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
    std::list<Searchable *> list;
    Trip trip;
    char *buffer = (char *) malloc(BUUFER_SIZE * sizeof(char));
    int n = 0;
    string serial_str2;
    //ask for trip - send the driver to confirm location
    std::string serial_str;
    iostreams::back_insert_device<std::string> inserter(serial_str);
    iostreams::stream<iostreams::back_insert_device<std::string> > s(inserter);
    archive::binary_oarchive oa(s);
    oa << this->d;
    s.flush();
    //send the driver
    n = this->socket->sendData(serial_str, serial_str.size());
    if (n < 0) {
        perror("Error in Sendto");
    }
    //get back the list of serchables that represents the routh
    n = this->socket->reciveData(buffer, BUUFER_SIZE);
    if (n < 0) {
        perror("Error in receiving");
    }
    string finish = "Finished";
    while (strcmp(buffer, "EndCommunication") != 0) {
        //deserialze trip's routh
        boost::iostreams::basic_array_source<char> device(buffer, 4096);
        boost::iostreams::stream<boost::iostreams::basic_array_source<char> > s2(device);
        boost::archive::binary_iarchive ia(s2);
        ia >> list;
        //set the routh
        this->d->setRouth(list);
        //ask the server for permission to move
        string sendMegGo = "sendMeGo";
        //moving the trip entire routh ask for permission every step
        while ((this->d->getTaxi()->getRouth().size() > 0)
               &&(strcmp(buffer, "EndCommunication")!=0)) {
            //ask the server for go
            n = this->socket->sendData(sendMegGo, sendMegGo.size());
            if (n < 0) {
                perror("Error in Sendto");
            }
            //get answer from server
            n = this->socket->reciveData(buffer, BUUFER_SIZE);
            serial_str2 = buffer;
            //if it is go then move
            if (strcmp("Go", buffer) == 0) {
                this->d->getTaxi()->move();
            }
        }
        //if we got the order to stop
        if((strcmp(buffer, "EndCommunication")==0)){
            break;
        }
        //ask for next trip
        std::string serial_str3;
        iostreams::back_insert_device<std::string> inserter2(serial_str3);
        iostreams::stream<iostreams::back_insert_device<std::string> > s3(inserter2);
        archive::binary_oarchive oa2(s3);
        oa2 << this->d;
        s3.flush();
        //send the driver
        n = this->socket->sendData(serial_str3, serial_str3.size());
        if (n < 0) {
            perror("Error in Sendto");
        }
        //get the routh
        n = this->socket->reciveData(buffer, BUUFER_SIZE);
        if (n < 0) {
            perror("Error in receiving");
        }
    };
    //we got "EndCommunication" then send end conformation
    n = this->socket->sendData(finish, finish.size());
    if (n < 0) {
        perror("Error in Sendto");
    }
    close(this->socket->getSocketDescriptor());
    //release data
    delete (this->socket);
    free(buffer);
}

/**
 * the deconstructor
 */
ManageDriver::~ManageDriver() {
    delete (this->d);
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
        //todo exit if failed??
    }
    //deserialize and set taxi
    iostreams::basic_array_source<char> inserter1(buffer, BUUFER_SIZE);
    iostreams::stream<iostreams::basic_array_source<char> > s1(inserter1);
    archive::binary_iarchive ia1(s1);
    ia1 >> t;
    this->d->setTaxi(t);
    free(buffer);
}

ManageDriver::ManageDriver(string s, Socket *soc) {
    this->d = new Driver(s);
    this->socket = soc;
}
