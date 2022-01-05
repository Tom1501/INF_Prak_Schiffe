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
#include "TASK3.H"
#include <math.h>
#include <stdio.h>

#include "SIMPLESOCKET.H"

using namespace std;
int Random1();
int Random2();


	TCPclient c;


int main() {
	srand(time(NULL));

	string host = "localhost";
	string msg;
	int runs = 10;
	int SumA = 0, SumB = 0, SumC = 0;
	float CountField[10] = {};
	int A, B, C;
	float mean, SD;

	//connect to host
	c.conn(host , 2044);


		for(int i=0;i<runs;i++){ // Strategie 1 wird i mal ausgeführt und die schüsse im CountField gespeichert
			A = Random1();
			CountField[i+1] = A;
			SumA = SumA + A;
			std::cout << "Anzahl Schüsse bei Zufallsstrategie 1: " << i+1 << ". Versuch: " << A << std::endl;
		}
	mean = SumA/runs; // Summe berechnen
	SD = 0;
		for(int i=0;i<runs;i++){ // Standardabweichung berechnen
			SD += pow(CountField[i+1] - mean, 2);
		}

	std::cout << "Anzahl durchschnittlicher Schüsse bei Zufallsstrategie 1: " << mean << std::endl;

	std::cout << "Standardabweichung: " << sqrt(SD/10) << std::endl;




	for(int i=0;i<runs;i++){ // Strategie 2 wird i mal ausgeführt und die schüsse im CountField gespeichert
		B = Random2();
		CountField[i+1] = B;
		SumB = SumB + B;
		std::cout << "Anzahl benötigter Schüsse bei Zufallsstrategie 2: " << i+1 << ". Versuch: " << B << std::endl;
		}
	mean = SumB/runs; // Summe berechnen
	SD = 0;
		for(int i=0;i<runs;i++){ // Standardabweichung berechnen
			SD += pow(CountField[i+1] - mean, 2);
		}
	std::cout << "Anzahl durchschnittlicher Schüsse bei Zufallsstrategie 2: " << mean << std::endl;
	std::cout << "Standardabweichung: " << sqrt(SD/10) << std::endl;



}




int Random1(){ // Strategie 1 schießt zufällig
	int Count1 = 0;
	int X1, Y1;
	string msg1;
	msg1 = "new_game()";
	c.sendData(msg1);
	msg1 = c.receive(32);
	while(1){
		X1 = (rand()%10)+1;
		Y1 = (rand()%10)+1;
		std::stringstream ss1;
		ss1.str("");
		ss1 << "shoot(" << X1 << "," << Y1 << ")";
		msg1 = ss1.str();
		c.sendData(msg1);
		Count1++;
		msg1 = c.receive(32);

		if(msg1.compare(0,9,"GAME_OVER") == 0){
			return Count1;
		}
	}
}


int Random2(){ // Strategie 2 schießt zufällig, jedoch nicht doppelt auf felder
	int Count2 = 0;
	int X2, Y2;
	std::stringstream ss2;
	string msg2;
	int Field[11][11] = {};
	msg2 = "new_game()";
	c.sendData(msg2);
	msg2 = c.receive(32);
	while(1){
		X2 = (rand()%10)+1;
		Y2 = (rand()%10)+1;
		if(Field [X2] [Y2] == 0){
		ss2.str("");
		ss2 << "shoot(" << X2 << "," << Y2 << ")";
		msg2 = ss2.str();
		c.sendData(msg2);
		msg2 = c.receive(32);
		Field[X2][Y2] = 1;
		Count2++;
		if(msg2.compare(0,9,"GAME_OVER") == 0){
			return Count2;
			}
		}
	}
}
/*
 int Random3(){
		int Count3 = 0;
		int X3, Y3;

		std::stringstream ss3;
		string msg3;
		int Field[11][11] = {};
		msg3 = "new_game()";
		c.sendData(msg3);
		msg3 = c.receive(32);
		while(1){
			X3 = (rand()%10)+1;
			Y3 = (rand()%10)+1;
			TASK3::checkNeighborhood(int X3, int Y3);
			if(Field [X3] [Y3] == 0){
			ss3.str("");
			ss3 << "shoot(" << X3 << "," << Y3 << ")";
			msg3 = ss3.str();
			c.sendData(msg3);
			msg3 = c.receive(32);
			Field[X3][Y3] = 1;
			Count3++;
			if(msg3.compare(0,9,"GAME_OVER") == 0){
				return Count3;
			}
		}

	}
			*/

