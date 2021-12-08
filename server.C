/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"

class MyServer : public TCPserver{
public:
    MyServer(int portNmb, int maxDataRecv) : TCPserver(portNmb, maxDataRecv){;};

protected:
string myResponse(string input);

};


int main(){
	srand(time(nullptr));
	TCPserver srv(2025,25);
	srv.run();
}


string MyServer::myResponse(string input){
	if( input.compare(0,4,"eins") == 0 ){
		return string("1");
		}else if( input.compare(0,4,"zwei") == 0 ){
			return string("2");
			} else if( input.compare(0,4,"drei") == 0 ){
				return string("3");
				}else if( input.compare(0,4,"vier") == 0 ){
					return string("4");
					}else if( input.compare(0,4,"fuenf") == 0 ){
						return string("5");
						} else {return string("ERROR");}
};
