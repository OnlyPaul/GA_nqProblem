#ifndef ParaException
#define ParaException

class ParameterAgainstNatureException : public std::exception {
public:
	virtual const char* what() const noexcept override { 
		return "Something goes against nature. Object cannot be casted.";
	}
};
#endif // ParaException

#ifndef Population_H
#define Population_H

#include <iostream>
#include <cstdlib>
#include <time.h>

class Population {
	/*
	* note that the chromosomes should be declared in the derived class, due to the various approaches
	* in various problems, we cannot generalize chromosome type in the mother abstract class
	*/

	int size; // population size, number of chromosomes in the system
public:
	// class constructor
	Population(int size) {
		if (size <= 0) throw ParameterAgainstNatureException();

		this->size = size; 
	} 
	virtual ~Population() { }

	int getSize() const { return size; }
	void setSize(int newSize) { size = newSize; }

	// pure virtual functions awaits implementation
	virtual int evaluate() = 0;
	virtual void crossover(int count) = 0;
	virtual void mutate(double prob) = 0;
};


#endif // Population_H