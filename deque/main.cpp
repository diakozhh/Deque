// deque.cpp: определяет точку входа для приложения.
//
#include <iostream>

#include "deque.h"

#define _CRT_MAP_APPOC
#include <stdlib.h>
#include <crtdbg.h>

template<class elemType>
void dqPrint(const deque<elemType>& d) {
	for (deque<int>::dqIterator dqI = d.dqHead(); dqI != d.dqTail(); dqI.dqNext())
		std::cout << dqI.getElem() << " ";
	std::cout << std::endl;
}

template<class elemType>
deque<elemType> dqSum(deque<elemType>& d1, deque<elemType>& d2) {
	deque<elemType> d = d1 + d2;
	return d;
}

void dqTest() {

	deque<int> d1;
	std::cout << "Empty deque: " << std::endl;
	dqPrint(d1);
	std::cout << std::endl;

	deque<int> d2{0, 1, 2, 3, 4};
	std::cout << "Initializer list constructor: " << std::endl;
	dqPrint(d2);
	std::cout << std::endl;

	std::cout << "Copy constructor: " << std::endl;
	deque<int> d3(d2);
	dqPrint(d2);
	dqPrint(d3);
	std::cout << std::endl;

	std::cout << "Move constructor: " << std::endl;
	deque<int> d4(dqSum(d2, d3));
	dqPrint(d4);
	std::cout << std::endl;

	std::cout << "Copy equality operator: " << std::endl;
	d3 = d2;
	dqPrint(d2);
	dqPrint(d3);
	std::cout << std::endl;

	std::cout << "Move equality operator (return rValue): " << std::endl;
	d3 = dqSum(d2, d3);
	dqPrint(d3);
	std::cout << std::endl;

	std::cout << "Opeartor+: " << std::endl;
	d2 = deque<int>({0, 1, 2, 3, 4});
	d3 = d2;
	deque<int> dqTest(d2);
	dqPrint(d2 + d2);
	dqPrint(d2 + d3);
	dqPrint(d2 + deque<int>({ 1, 1, 1, 0}));

	std::cout << "'dqUnion()' methods and opeartor+: " << std::endl;
	dqTest.dqUnion(dqTest);
	dqPrint(dqTest);
	dqTest + (deque<int>({2, 2, 2, 0}));
	dqPrint(dqTest);
	std::cout << std::endl;

	std::cout << "Operator + to 'elemType': " << std::endl;
	d4 = deque<int>({1, 2, 3, 4});
	int i = 5;
	d4 = d4 + i;
	dqPrint(d4);
}

int main() {
	dqTest();
	_CrtDumpMemoryLeaks();
	return 0;
}
