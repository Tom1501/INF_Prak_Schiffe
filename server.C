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
	MyServer(int portNMB,int maxSizeData):TCPserver(portNMB,maxSizeData){w=NULL;};
protected:
	string myResponse(string input);
	TASK3::ShootResult res;
	TASK3::World *w;
};

int main(){
	srand(time(nullptr));
	MyServer srv(2050,25); // Kommunikationskanal wird aufgebaut
	srv.run();
}



string MyServer::myResponse(string input){
	int a,b,c;
	string responseStr = string("0");
	TASK3::ShootResult A;
	int X,Y;

	if(input.compare(0,4,"cmd(") == 0){
		sscanf(input.c_str() , "cmd(%i,%i,%i)", &a, &b, &c );
		std::cout << " a=" << a << " b=" << b << " c=" << c << std::endl;

		responseStr = string("OK...");
		return responseStr;
	}

	if(input.compare(0,9,"new_game(") == 0){ // Aufruf zum Spielneustart
		if(w==NULL){
			w = new TASK3::World; // Wenn keine Welt existiert, wird eine Welt w erzeugt
		}
		else{
			delete w;
			w = new TASK3::World; // Wenn eine Welt existiert, wird die Welt gelöscht und dann eine neue erstellt
		}
		responseStr = string("Restarted");
		return responseStr;
	}
	else if(input.compare(0,6,"shoot(") == 0){
		sscanf(input.c_str() , " shoot(%i,%i)", &X, &Y );
		A = w->shoot(X,Y); // Schussresultat wird ermittelt
		w->printBoard();
		if(A == TASK3::GAME_OVER){ // Schussresultat wird an den client zurückgegebenS
			return "GAME_OVER";
		}
		else if(A == TASK3::WATER){
			return "WATER";
		}
		else if(A == TASK3::SHIP_HIT){
			return "SHIP_HIT";}
		else if(A == TASK3::SHIP_DESTROYED){
			return "SHIP_DESTROYED";
		}
	}
	else if(input.compare(0,9,"end_game(") == 0){
		delete w; // Welt wird gelöscht
		responseStr = string("BYEBYE");
		return responseStr;
	}
	else{
		responseStr = string("ERROR");
		return responseStr;
	}
}

