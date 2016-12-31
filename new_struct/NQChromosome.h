#ifndef NQCHROMOSOME_H
#define NQCHROMOSOME_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <time.h>
#include "Chromosome1D.h"

class NQChromosome : public Chromosome1D<int> {
public:
	NQChromosome(int geneCount):Chromosome1D(geneCount) {
		for (int i=0; i < getGeneCount(); i++)
			setGenes(i,(int)((rand()%getGeneCount())));
	}
	NQChromosome(const NQChromosome *nq):Chromosome1D(nq) {}
	~NQChromosome() {}

	virtual void evaluate() override;
	virtual void crossover(NQChromosome *chromosome);
	virtual bool mutate(double prob) override;
	virtual std::string toString() override;
	std::string toBoard();
};

void NQChromosome::evaluate() {
	int distance; // distance between the queens
	int collision = 0; // how many queens threaten this queen
	if (this->getFitness() >= 0) return; // fitness of this queen is determined

	for(int i=0; i < this->getGeneCount(); i++) {
		for(int j=i+1; j < this->getGeneCount(); j++) {
			distance = std::abs(getGenes(i) - getGenes(j));

			if((distance == 0) || (distance == j-i))
				collision++;
		}
	}

	this->setFitness(collision);
}

void NQChromosome::crossover(NQChromosome *chromosome) {
	int crossoverpoint = (int)(rand()%getGeneCount() ); // random
	int help; // swapping buffer

	for(int i=crossoverpoint; i < this->getGeneCount(); i++) {
		help = this->getGenes(i);
		this->setGenes(i, chromosome->getGenes(i));
		chromosome->setGenes(i, help);
	}

	this->setFitness(-1); //invalidate fitness
	chromosome->setFitness(-1); //invalidate fitness
}

bool NQChromosome::mutate(double prob) {
	if (((double)rand()/RAND_MAX)>=prob) return false;

	do {
		this->setGenes(int(rand()%getGeneCount()), int(rand()%getGeneCount()));
	} while(((double)rand()/RAND_MAX)<prob);

	this->setFitness(-1);
	return true;
}

std::string NQChromosome::toString() {
	std::string strOut;

	for(int i=0; i < getGeneCount(); i++)
		strOut += std::to_string(getGenes(i)) + " ";
	strOut += '\n';

	return strOut;
}

std::string NQChromosome::toBoard() {
	std::string strOut;

	for(int j=0; j < getGeneCount(); j++) {
		for(int k=0; k < getGeneCount(); k++) {
			if(k == getGenes(j)) {
				strOut += " Q ";
			} else {
				strOut += " . ";
			}
		}
		strOut +=  '\n';
    }

	return strOut;
}

#endif // NQCHROMOSOME_H
