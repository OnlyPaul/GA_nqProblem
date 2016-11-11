#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <time.h>
#include "Environment.h"

using namespace std;

 class FailedArgumentException : public std::exception {
 public:
	virtual const char* what() const noexcept override {
		return "There is no argument given. Input argument 'help' for instruction.";
	}
 };

int main(int argc, char* argv[]) {
	srand (time(NULL)); //initiate random number generator
	int n, popsize, gencnt, tmsize;
	double mutprob;

	if (argc == 2 && strcmp(argv[1], "help") == 0) {
		cout << endl;
		cout << "To solve 'N' queens problem, please run the command:" << endl;
		cout << endl;
		cout << "     ./prog <N> <popsize> <gencnt> <tmsize> <mutprob>" << endl;
		cout << endl;
		cout << "- prog: program's name" << endl;
		cout << "- N: the number of the queens represented in NxN chess board (int)" << endl;
		cout << "- popsize: the number of individuals in the population we simulate (int)" << endl;
		cout << "- gencnt: the number of generation we loop through, generation counts (int)" << endl;
		cout << "- tmsize: size of tournament in the selection process, tournament size (int)" << endl;
		cout << "- mutprob: probability that the gene will mutate, mutation probability (double, range 0-1)" << endl;
		cout << "*note that all the variable must be input respectively to the given order" << endl;
		cout << endl;
		return 0;
	} else if (argc == 6) {
		try {
			n = atoi(argv[1]);
			popsize = atoi(argv[2]);
			gencnt = atoi(argv[3]);
			tmsize = atoi(argv[4]);
			mutprob = atof(argv[5]);

			int* answer;
			Environment* nqueen = new Environment(popsize, n);

			nqueen->natSelection(gencnt, tmsize, true, mutprob);

			answer = nqueen->getAnswer();

			if (answer != NULL) {
				for(int i=0; i < n; i++)
					cout << answer[i] << ' ';
				cout << endl;
      
				cout << nqueen->getBoardAnswer();
			} else {
				cout << endl;
				cout << "Cannot find answer in the scope of the given parameter." << endl;
				cout << endl;
			}

			delete [] answer;
		}
		catch (...) {
			throw FailedArgumentException();
		}
	} else throw FailedArgumentException();

	return 0;
}
