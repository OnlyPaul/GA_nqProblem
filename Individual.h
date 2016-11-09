#ifndef Individual_H
#define Individual_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>

class Individual {
public:
	int fitness;
	int cnt; //number of genes (= n)
	int *genes; //(x) position of queen in rows

	// Class constructor
	Individual(int ngenes) {
		this->cnt = ngenes;
		genes = new int[ngenes];

		for(int i=0; i<ngenes; i++){
			genes[i]  = int((rand()%ngenes));
		}

		fitness = -1; //fitness unknown
	}

	/*Individual& operator=(const Individual& rhs) {
		fitness = rhs->fitness;
		cnt = rhs->cnt;

		for(int i=0; i<cnt; i++)
			genes[i] = rhs->genes[i];
	}*/

	// Class destructor
	~Individual() { delete[] genes; }

	void evaluation();
	void crossover(Individual *individual);
	void mutation(double probability);
	void copyFrom(Individual *source);
	void print();
};

void Individual::evaluation(){
	int distance; // distance between queens
	int counter = 0; // how many queen in same row/diagonal = fitness = collisions

	if (fitness >= 0)
		return;

	for(int i=0; i < cnt; i++) {
		for(int j=i+1; j < cnt; j++) {
			distance = std::abs(genes[i] - genes[j]);

			if((distance == 0) || (distance == j-i))
				counter++;
		}
	}

	fitness = counter;
}

void Individual::crossover(Individual *individual) {
	int crossoverpoint = (int)(rand()%cnt ); //point of crossover
	int help;

	for(int i=crossoverpoint; i<cnt; i++) {
		help = this->genes[i];
		this->genes[i]=individual->genes[i];
		individual->genes[i]=help;
	}

	this->fitness = -1; //invalidate fitness
	individual->fitness = -1; //invalidate fitness
 }

void Individual::mutation(double probability) {
	if (((double)rand()/RAND_MAX)>=probability) {
		//std::cout << "nope" << std::endl;
		return;
	}

	do {
		this->genes[int(rand()%cnt)]=int(rand()%cnt);
	} while(((double)rand()/RAND_MAX)<probability);

	this->fitness=-1;
}

void Individual::copyFrom(Individual *source) {
	fitness = source->fitness;
		cnt = source->cnt;

	for(int i=0; i<cnt; i++)
		genes[i] = source->genes[i];
}

void Individual::print() {
	for(int i=0; i<cnt; i++)
		std::cout << genes[i] << " ";
	
	std::cout << std::endl;

	for(int j=0; j<cnt; j++) {
		for(int k=0; k<cnt; k++) {
			if(k==genes[j]) {
				std::cout <<" Q ";
			} else {
				std::cout << " . ";
			}
		}
		std::cout << std::endl;
    }
}

#endif // Individual_H