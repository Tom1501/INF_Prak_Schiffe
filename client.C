/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <iostream>
#include <unistd.h> //contains various constants
#include <sstream>

#include "SIMPLESOCKET.H"

using namespace std;

int Random();


	TCPclient c;


int main() {
	srand(time(NULL));

	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2028);

	int A;
	A = Random();
	std::cout << "Anzahl benötigter Schüsse: " << A << std::endl;
}


	int Random(){
	int Count = 0;
	int X, Y;
	string msg;
	msg = "new_game()";
	c.sendData(msg);
	msg = c.receive(32);
	while(1){
		X = (rand()%10)+1;
		Y = (rand()%10)+1;
		std::stringstream ss;
		ss.str("");
		ss << "shoot(" << X << "," << Y << ")";
		msg = ss.str();
		c.sendData(msg);
		Count++;
		msg = c.receive(32);

		if(msg.compare(0,9,"GAME_OVER") == 0){
			goto Part1;
		}
}

	Part1:
		return Count;}

