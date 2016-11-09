#ifndef Population_H
#define Population_H

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Individual.h"

class Population{
public:
	int size; //population size
	Individual * best; //individual with the best fitness
	Individual ** individuals; //vector of individuals
	Individual ** buffer; // buffer for individuals

	// Class constructor
	Population(int size, int ngenes) {
		this->size = size;
		individuals = new Individual * [size];
		buffer = new Individual * [size];
		
		for(int i=0; i<size; i++) {
			individuals[i]= new Individual(ngenes);
			buffer[i]= new Individual(ngenes);
		}
	}

	// Class destructor
	~Population() {
		for(int i=0; i<size; i++)
			delete individuals[i];
		
		delete [] individuals;
	}

	int evaluation();
	Individual* tournamentSelection(int tmSize);
	void popSelection(int tmSize, bool elitist);
	void crossover(int count);
	void mutation(double probability);
	
};

int Population::evaluation(){
	Individual *bestIndividual = individuals[0];
	bestIndividual->evaluation();

	for(int i=0; i<size; i++){
		individuals[i]->evaluation();
		if(individuals[i]->fitness <= bestIndividual->fitness){
			bestIndividual = individuals[i];
		}
	}

	this->best = bestIndividual;
	return best->fitness;
}

Individual* Population::tournamentSelection(int tmSize) {
	Individual *compIndiv, *tournamentBest;

	tournamentBest = this->individuals[(int)(rand()%size)];
	while(--tmSize > 0) {
		compIndiv = this->individuals[(int)(rand()%size)];
		if(tournamentBest->fitness > compIndiv->fitness)
			tournamentBest = compIndiv;
	}

	return tournamentBest;
}

void Population::popSelection(int tmSize, bool elitist) {
	int i = this->size-1;
	//Individual **p;

	if(elitist) {
		//buffer[i]->copyFrom(best);
		buffer[i] = best;
	}
	while(--i >= 0)
		buffer[i] = tournamentSelection(tmSize);
	/*p = individuals;
	individuals = buffer;
	buffer = p;
	best = NULL;*/
}

void Population::crossover(int count){
	/* The last element of the array individuals can't take part
	 in crossover, which means that the second last element
	 can't be the "left" element in the crossover. 
	 To make sure that this also applies to odd sizes 
	 count can't be greater than size-2 */

	if(count > this->size-2)
		count = this->size-2;
	
	for(int i=0; i<count; i+=2)
		individuals[i]->crossover(individuals[i+1]);
}

void Population::mutation(double probability){
	for(int i=0; i<this->size-1; i++)
		individuals[i]->mutation(probability);
}

#endif // Population_H