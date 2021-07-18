#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

class RandomGenerator {
	
private:
	static int integerGen;
	static int doubleGen;
	
public:
	// Return random integer between 0 and 1
	static int randomInteger() {
		integerGen++;
		switch(integerGen) {
		case 0:
			return 0;
		case 1:
			integerGen = 0;
			return 1;
		default:
			return 0;
		}
	}
	
	// Return random double between 0 and 1
	static double randomDouble() {
		doubleGen++;
		switch(integerGen) {
		case 0:
			return 0.0;
		case 1:
			return 0.25;
		case 2:
			return 0.5;
		case 3:
			return 0.75;
		case 4:
			doubleGen = 0;
			return 1.0;
		default:
			return 0.0;
		}
		
	}

};

#endif