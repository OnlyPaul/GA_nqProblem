#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Environment.h"

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

	/*int loopCount = 60000;

	NQPopulation *pop = new NQPopulation(100,8);

	while (pop->evaluate() != 0 && --loopCount >= 0) {
		pop->populationSelection(50, true);
		pop->crossover(8);
		pop->mutate(0.3);
	}

	if(pop->getBest()->getFitness() == 0)
		pop->getBest()->print();
	else
		cout << "The puzzle is not solved." << endl;*/

	int* answer;
	Environment* a = new Environment(50, 8);

	a->natSelection(50000, 50, true, 0.3);

	answer = a->getAnswer();

	for(int i=0; i < 8; i++)
		cout << answer[i];
	cout << endl;

	cout << a->getBoardAnswer();

	/*for(int i=0; i < getGeneCount(); i++)
		std::cout << getGenes(i) << " ";
	
	std::cout << std::endl;

	for(int j=0; j < getGeneCount(); j++) {
		for(int k=0; k < getGeneCount(); k++) {
			if(k == getGenes(j)) {
				std::cout <<" Q ";
			} else {
				std::cout << " . ";
			}
		}
		std::cout << std::endl;
    }*/



	delete [] answer;

	return 0;
}