#ifndef ParaException
#define ParaException

class ParameterAgainstNatureException : public std::exception {
public:
	virtual const char* what() const noexcept override { 
		return "Something goes against nature. Object cannot be casted.";
	}
};
#endif // ParaException


#ifndef CHROMOSOME1D_H
#define CHROMOSOME1D_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include <time.h>

template <typename E>
class Chromosome1D {
	int fitness;
	int geneCount;
	E *genes; // represent gene/position/value in form of an array, datatype can be varied

public:
	// class constructor: construct a dynamic array of genes
	Chromosome1D(int geneCount) {
		if(geneCount <= 0) throw ParameterAgainstNatureException();
		this->geneCount = geneCount;
		genes = new E[geneCount];

		for (int i=0; i < geneCount; i++)
			genes[i] = (int)((rand()%geneCount));

		this->fitness = -1; //fitness unknown
	}

	// class destructor is virtual, and can be overridden
	virtual ~Chromosome1D() { delete [] genes; }

	int getFitness() const { return fitness; }
	void setFitness(int newFitness) { fitness = newFitness; }

	int getGeneCount() const { return geneCount; }
	void setGeneCount(int newGeneCount) { geneCount = newGeneCount; }

	E* getGenes() { return genes; }
	E getGenes(const int pos) const { return genes[pos]; }
	void setGenes(const E* newGenes) { genes = newGenes; }
	void setGenes(const int pos, E newVal) { genes[pos] = newVal; }

	virtual void evaluate() = 0;
	/* virtual void crossover(Chromosome1D *chromosome) {
		throw "Cannot match chromosome type.";
	} */
	virtual bool mutate(double prob) = 0;
	virtual std::string toString() = 0;
};

#endif // CHROMOSOME1D_H