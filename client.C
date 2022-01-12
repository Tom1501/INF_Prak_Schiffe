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
int Random1(); // deklaration der drei Strategien
int Random2();
int Inteli();


	TCPclient c;


int main() {
	srand(time(NULL));

	string host = "localhost";
	string msg;
	int runs = 10; // Durchläufe pro Strategie
	int SumA = 0, SumB = 0, SumC = 0; // Summe der Strategiedurchläufe
	float CountField[10] = {}; // Spielfeld zum markieren der genutzten felder
	int A, B, C; // Rückgabewerte der Durchläufe
	float mean, SD; // Statistische auswertung

	//connect to host
	c.conn(host , 2050);

	for(int i=0;i<runs;i++){ // Strategie 1 wird i mal ausgeführt und die schüsse im CountField gespeichert
		A = Random1();
		CountField[i+1] = A;
		SumA = SumA + A;
		std::cout << A << std::endl;
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
		std::cout << B << std::endl;
	}
	mean = SumB/runs; // Summe berechnen
	SD = 0;

		for(int i=0;i<runs;i++){ // Standardabweichung berechnen
			SD += pow(CountField[i+1] - mean, 2);
		}

	std::cout << "Anzahl durchschnittlicher Schüsse bei Zufallsstrategie 2: " << mean << std::endl;
	std::cout << "Standardabweichung: " << sqrt(SD/10) << std::endl;

	for(int i=0;i<runs;i++){ // Strategie 3 wird i mal ausgeführt und die schüsse im CountField gespeichert
		C = Inteli();
		CountField[i+1] = C;
		SumC = SumC + C;
		std::cout << C << std::endl;
	}
	mean = SumC/runs; // Summe berechnen
	SD = 0;
	for(int i=0;i<runs;i++){ // Standardabweichung berechnen
			SD += pow(CountField[i+1] - mean, 2);
	}
	std::cout << "Anzahl durchschnittlicher Schüsse bei Strategie Inteli: " << mean << std::endl;
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

int Inteli(){ // Strategie Merkt sich Treffer und schießt umgebung ab
	int Count3 = 0;
	int X3 = -1, Y3 = 1; // Startkoordinate 1 / 1 muss durch X - 2 korrigiert werden, da bereits vor dem ersten Schuss das Abschussmuster korrigiert wird
	std::stringstream ss3;
	string msg3;
	int Field[11][11] = {}; // Feld zum speichern bereits beschossener Felder
	msg3 = "new_game()";
	c.sendData(msg3);
	msg3 = c.receive(32);
	while(1){ // Schussalgorithmus wird in Dauerschleife ausgeführt
		if(X3 <= 8){ // Schachbrettartiges Abschussmuster
			X3 = X3+2;
		}
		else if((X3>8) && (Y3%2 == 0)){
			Y3 = Y3+1;
			X3 = 1;
		}
		else if((X3>8) && (Y3%2 == 1)){
			Y3 = Y3+1;
			X3 = 2;
		}
		if(Field [X3] [Y3] == 0){
			ss3.str("");
			ss3 << "shoot(" << X3 << "," << Y3 << ")";
			msg3 = ss3.str();
			c.sendData(msg3);
			msg3 = c.receive(32);
			Field[X3][Y3] = 1;
			Count3++;
			if(msg3.compare(0,8,"SHIP_HIT") == 0){ // Wenn Schiff getroffen wird
				int dir = 1; // Korrigiert Schussposition in gewünschte richtung
				while((Field [X3+dir] [Y3] == 0) && (msg3.compare(0,8,"SHIP_HIT") == 0) && ((X3+dir)<11)){ // Schussrichtung rechts, solange schiff getroffen wird.
					ss3.str("");
					ss3 << "shoot(" << X3+dir << "," << Y3 << ")";
					msg3 = ss3.str();
					c.sendData(msg3);
					msg3 = c.receive(32);
					Field[X3+dir][Y3] = 1;
					Count3++;
					dir++;
				}
				dir = 1;
					while((Field [X3-dir] [Y3] == 0) && ((msg3.compare(0,5,"WATER") == 0) ||(msg3.compare(0,8,"SHIP_HIT") ) == 0) && ((X3-dir)>0)){ // Schussrichtung Links
						ss3.str("");
						ss3 << "shoot(" << X3-dir << "," << Y3 << ")";
						msg3 = ss3.str();
						c.sendData(msg3);
						msg3 = c.receive(32);
						Field[X3-dir][Y3] = 1;
						Count3++;
						dir++;
						if(msg3.compare(0,8,"WATER") == 0){ // Schussrichtung beenden, wenn Wasser getroffen wird
							break;
						}
					}
				dir = 1;
					while((Field [X3] [Y3+dir] == 0) && ((msg3.compare(0,5,"WATER") == 0) ||(msg3.compare(0,8,"SHIP_HIT") == 0)) && ((Y3+dir)<11)){ // Schussrichtung Oben
						ss3.str("");
						ss3 << "shoot(" << X3 << "," << Y3+dir << ")";
						msg3 = ss3.str();
						c.sendData(msg3);
						msg3 = c.receive(32);
						Field[X3][Y3+dir] = 1;
						Count3++;
						dir++;
						if(msg3.compare(0,8,"WATER") == 0){
							break;
						}
					}
				dir = 1;
					while((Field [X3] [Y3-dir] == 0) && ((msg3.compare(0,5,"WATER") == 0) ||(msg3.compare(0,8,"SHIP_HIT") == 0)) && ((Y3+dir)>0)){ // Schussrichtung Unten
							ss3.str("");
							ss3 << "shoot(" << X3 << "," << Y3-dir << ")";
							msg3 = ss3.str();
							c.sendData(msg3);
							msg3 = c.receive(32);
							Field[X3][Y3-dir] = 1;
							Count3++;
							dir++;
							if(msg3.compare(0,8,"WATER") == 0){
								break;
							}
						}
				dir = 1;
				if(msg3.compare(0,9,"GAME_OVER") == 0){
					return Count3; // Zählwert zurückgeben, wenn spiel beendet
				}
			}
		}
	}
}
