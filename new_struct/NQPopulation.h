#ifndef NQPopulation_H
#define NQPopulation_H

#include <iostream>
#include <cstdlib>
#include <time.h>
#include "Population.h"
#include "NQChromosome.h"

class NQPopulation : public Population {
	NQChromosome *best; // point the best chromosome in this population
	NQChromosome **individuals; // all the chromosomes in this population, see as indiviodual organism
	NQChromosome **buffer; // buffer chromosomes, used in swapping etc.
public:
	// Class constructor
	NQPopulation(int size, int geneCount) : Population(size) {
		individuals = new NQChromosome * [size];
		buffer = new NQChromosome * [size];
		
		for(int i=0; i < getSize(); i++) {
			individuals[i]= new NQChromosome(geneCount);
			buffer[i]= new NQChromosome(geneCount);
		}
	}

	// Class destructor
	virtual ~NQPopulation() {
		for(int i=0; i < getSize(); i++)
			delete individuals[i];
		
		delete [] individuals;
		delete [] buffer;
	}

	NQChromosome* getBest() { return best; }
	void setBest(NQChromosome* newBest) { best = newBest; }

	NQChromosome** getIndividuals() { return individuals; }
	NQChromosome* getIndividuals(int pos) { return individuals[pos]; }
	void setIndividuals(NQChromosome** newIndiv) { individuals = newIndiv; }
	void setIndividuals(int pos, NQChromosome* newChrom) { individuals[pos] = newChrom; }

	NQChromosome** getBuffer() { return buffer; }
	NQChromosome* getBuffer(int pos) { return buffer[pos]; }
	void setBuffer(NQChromosome** newBuffer) { buffer = newBuffer; }
	void setBuffer(int pos, NQChromosome* newBuffer) { buffer[pos] = newBuffer; }

	virtual int evaluate();
	virtual void crossover(int count);
	virtual void populationSelection(int tmSize, bool isElitist);
	virtual NQChromosome* tournamentSelection(int tmSize);
	virtual void mutate(double prob);
};

int NQPopulation::evaluate() {
	NQChromosome *bestIndividual = individuals[0];
	bestIndividual->evaluate();

	for(int i=0; i < getSize(); i++){
		individuals[i]->evaluate();
		if(individuals[i]->getFitness() <= bestIndividual->getFitness()) {
			bestIndividual = individuals[i];
		}
	}

	this->setBest(bestIndividual);
	return best->getFitness();
}

void NQPopulation::crossover(int count){
	/* 
	* The last element of the array individuals can't take part in crossover, which means that 
	* the second last element can't be the "left" element in the crossover. 
	* To make sure that this also applies to odd sizes count can't be greater than size-2 
	*/

	if(count > this->getSize()-2)
		count = this->getSize()-2;
	
	for(int i=0; i < count; i+=2)
		individuals[i]->crossover(individuals[i+1]);
}

void NQPopulation::populationSelection(int tmSize, bool isElitist) {
	int i = this->getSize()-1;

	if(isElitist) {
		setBuffer(i, getBest());
	}
	while(--i >= 0)
		setBuffer(i, tournamentSelection(tmSize));
}

NQChromosome* NQPopulation::tournamentSelection(int tmSize) {
	NQChromosome *compIndiv, *tournamentBest;

	tournamentBest = this->getIndividuals((int)(rand()%getSize()));
	while(--tmSize > 0) {
		compIndiv = this->getIndividuals((int)(rand()%getSize()));
		if(tournamentBest->getFitness() > compIndiv->getFitness())
			tournamentBest = compIndiv;
	}

	return tournamentBest;
}

void NQPopulation::mutate(double prob){
	for(int i=0; i < this->getSize()-1; i++)
		individuals[i]->mutate(prob);
}


#endif // NQPopulation_H