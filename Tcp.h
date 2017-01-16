/************************************************************
* File description: TCP header file. the class inherit from	*
* socket. methods of tcp socket type						*
************************************************************/

#ifndef TCP_H_
#define TCP_H_

#include "Socket.h"

class Tcp: public Socket {
private:
    int currentClientDescriptor;
public:
    /***********************************************************************
    * function name: Tcp												   *
    * The Input: Boolean, true - if server, false if client and port number*
    * The output: none										               *
    * The Function operation: creating new Tcp						       *
    ***********************************************************************/
    Tcp(bool isServers, int port_num);
    /***********************************************************************
    * function name: ~Tcp												   *
    * The Input: none													   *
    * The output: none										               *
    * The Function operation: default destructor					       *
    ***********************************************************************/
    virtual ~Tcp();
/***********************************************************************
	* function name: initialize											   *
	* The Input: none              										   *
	* The output: int number representing the return status		           *
	* The Function operation: initialize the Socket object and getting a   *
	* socket descriptor.												   *
	***********************************************************************/
    int initialize();
    /***********************************************************************
    * function name: sendData											   *
    * The Input: string representing the data to send		               *
    * The output: int number representing the return status		           *
    * The Function operation: sending the input data to the socket         *
    * who connect to this socket. 										   *
    ***********************************************************************/
    int sendData(string data, int length);
    /***********************************************************************
    * function name: recive	`											   *
    * The Input: none										               *
    * The output: int number representing the return status	               *
    * The Function operation: getting data from the other socket and print *
    * the data															   *
    ***********************************************************************/

    /***********************************************************************
   * function name: setIp											       *
   * The Input: ip string										           *
   * The Function operation: getting data from the       				   *
   ***********************************************************************/
    void setIp(string ip);

    int reciveData(char* buffer, int size);

    int sendDataTo(string data, int length, int descriptorClient);

    int rcvDataFrom(char *buffer, int size, int descriptorClient);

    int acceptClient();
    void setBackLog(int i);
};

#endif /* TCP_H_ */