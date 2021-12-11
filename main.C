//============================================================================
// Name        : INF3_Prak.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <string>
#include <iostream>

#include <cstdio>      /* printf, NULL */
#include <cstdlib>     /* srand, rand */
#include <ctime>       /* time */

#include <unistd.h>

#include "SHA256.H"
#include "TASK1.H"
#include "TASK2.H"
#include "TASK3.H"
#include "TASK4.H"
#include "TASK5.H"
#include "TASK6.H"

using namespace TASK5;
using namespace std;


int main(){
	ConcreteObserver o1;
	ConcreteObserver o2;
	ConcreteObserver o3;
	ConcreteObserver o4;
	ConcreteSubject subject;

	subject.attach(&o1);
	subject.attach(&o2);
	subject.attach(&o3);
	subject.attach(&o4);

	o1.setSubject(&subject);
	o2.setSubject(&subject);
	o3.setSubject(&subject);
	o4.setSubject(&subject);

	subject.setState("Hello World");

	subject.setState("New Data");



}





