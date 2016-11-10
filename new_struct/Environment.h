#ifndef Environment_H
#define Environment_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <time.h>
#include "NQPopulation.h"

/*
* Environment class (or so-called Genetic-Algorithm class) serves as the control sequence of the population.
* Think of this as the interface controlling when the population will evaluate,
* cross over, or mutate. That is, natural selection is the effect from environment to 
* the living organism.
*
* At the same time, Environment encapsulates the chromosomes in the swarm, 
* so that the client program (main program) does not directly access or mess 
* with the interior data
*/
class Environment {
	NQPopulation *crowd;
public:
	// Class constructor
	Environment(int crowdSize, int geneCount) {
		crowd = new NQPopulation(crowdSize, geneCount);
	}

	~Environment() { delete crowd; } // Class destructor

	void natSelection(int cycleCount, int tmSize, bool isElitist, double mutProb) {
		while (crowd->evaluate() != 0 && --cycleCount >= 0) {
			crowd->populationSelection(tmSize, isElitist);
			crowd->crossover(crowd->getSize());
			crowd->mutate(mutProb);
		}
	}

	// return answer to the n-queen puzzle as am integer dynamic array (Genes of the best individual)
	int* getAnswer() { 
		if (crowd->getBest()->getFitness() == 0)
			return crowd->getBest()->getGenes();
		else
			return NULL;
	}

	std::string getStrAnswer() { return crowd->getBest()->toString(); }

	std::string getBoardAnswer() { return crowd->getBest()->toBoard(); }
};

#endif // Environment_H