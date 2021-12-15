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

#include <iostream>
#include "SIMPLESOCKET.H"
#include "TASK3.H"

class MyServer:public TCPserver{
public:
	MyServer(int portNMB,int maxSizeData):TCPserver(portNMB,maxSizeData){;};
protected:
	string myResponse(string input);
	TASK3::World w;
	TASK3::ShootResult res;
};

int main(){
	srand(time(nullptr));
	MyServer srv(2016,25);
	srv.run();


}



string MyServer::myResponse(string input){
	int a,b,c;
	string responseStr = string("0");
	string responseBye = string("0");
	string responseNew = string("0");
	string responseErr = string("0");

	if(input.compare(0,4,"cmd(") == 0){
		sscanf(input.c_str() , "cmd(%i,%i,%i)", &a, &b, &c );
		std::cout << " a=" << a << " b=" << b << " c=" << c << std::endl;

		responseStr = string("OK...");
		return responseStr;

	}
	int X,Y;


	if(input.compare(0,6,"shoot(") == 0){
		sscanf(input.c_str() , " shoot(%i,%i)", &X, &Y );
		std::cout << " X=" << X << " Y=" << Y << std::endl;
			return responseStr;

	}
		else if(input.compare(0,9,"new_game(") == 0){
			sscanf(input.c_str() , " new_game(");
			TASK3::World w;
			TASK3::ShootResult res;

				do{
					w.printBoard();
					return "Eingabe: X=(Zahl)";
					sscanf(input.c_str() , "X=(%i)", &X);
					return "Eingabe: Y=(Zahl)";
					sscanf(input.c_str() , "Y=(%i)", &Y);
					cout << X << Y << endl;
					res = w.shoot(X,Y);
					cout << "shoot: (" << X << ", " << Y << ") --> " << res << endl;
				}while(res != TASK3::GAME_OVER);
				w.printBoard();
			return responseNew;
		}
		else if(input.compare(0,9,"end_game(") == 0){
			sscanf(input.c_str() , " end_game(");
			responseBye = string("BYEBYE");
			return responseBye;
		}
		else{
			string responseErr = string("ERROR..");
			return responseErr;
		}
}
