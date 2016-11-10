#ifndef CHROMOSOME1D_H
#define CHROMOSOME1D_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <time.h>

template <typename E>
class Chromosome1D {
	int fitness;
	int geneCount;
	E *genes;

public:
	Chromosome1D(int geneCount) {
		this->geneCount = geneCount;
		genes = new E[geneCount];

		for (int i=0; i < geneCount; i++)
			genes[i] = (int)((rand()%geneCount));

		this->fitness = -1; //fitness unknown
	}
	virtual ~Chromosome1D() { delete [] genes; }

	int getFitness() { return fitness; }
	void setFitness(int newFitness) { fitness = newFitness; }

	int getGeneCount() { return geneCount; }
	void setGeneCount(int newGeneCount) { geneCount = newGeneCount; }

	E* getGenes() { return genes; }
	E getGenes(const int pos) { return genes[pos]; }
	void setGenes(const E* newGenes) { genes = newGenes; }
	void setGenes(const int pos, E newVal) { genes[pos] = newVal; }

	virtual void evaluate() = 0;
	virtual void crossover(Chromosome1D *chromosome) {
		throw "Cannot match chromosome type.";
	}
	virtual bool mutate(double prob) = 0;
	virtual void print() = 0;
};

#endif // CHROMOSOME1D_H