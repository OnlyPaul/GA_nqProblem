#ifndef Environment_H
#define Environment_H

#include <iostream>
#include <cstdlib>
#include <time.h>

class Environment {
public:
	virtual ~Environment() = default;
	virtual populationSelection(int tmSize, bool isElitist) = 0;
	virtual tournamentSelection(int tmSize) = 0
};

#endif // Environment_H