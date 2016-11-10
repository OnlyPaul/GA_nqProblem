#include <iostream>
#include <cstdlib>
#include <time.h>
#include "NQPopulation.h"

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

	/*NQChromosome *a = new NQChromosome(10);
	NQChromosome *b = new NQChromosome(10);
	a->print();
	a->crossover(b);
	a->mutate(0.4);
	a->print();

	delete a;
	delete b;*/

	int loopCount = 60000;

	NQPopulation *pop = new NQPopulation(100,8);

	while (pop->evaluate() != 0 && --loopCount >= 0) {
		pop->populationSelection(50, true);
		pop->crossover(8);
		pop->mutate(0.3);
	}

	if(pop->getBest()->getFitness() == 0)
		pop->getBest()->print();
	else
		cout << "The puzzle is not solved." << endl;

	return 0;
}