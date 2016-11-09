#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Individual.h"
#include "Population.h"

using namespace std;

int main() {
	srand (time(NULL)); //initiate random number generator
	/*  int cnt;
	cout << "How many queens? " << endl;
	cin >> cnt;
	Population *population = new Population(100, cnt); */
	//Individual * a = new Individual(10);
	//Individual * b = new Individual(10);
	//a->print();
	/*  b->print();
	a->crossover(b);
	a->print();
	b->print(); */
	/*a->mutation(0.4);
	a->print();*/
	//  delete population;

	int loopCount = 60000;

	Population pop(100,8);

	while (pop.evaluation() != 0 && --loopCount >= 0) {
		pop.popSelection(50, true);
		pop.crossover(8);
		pop.mutation(0.3);
	}

	pop.best->print();

	return 0;
}