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

	NQPopulation *a = new NQPopulation(5,8);

	a->crossover(8);
	a->mutate(0.4);
	cout << a->evaluate() << endl;

	delete a;

	return 0;
}