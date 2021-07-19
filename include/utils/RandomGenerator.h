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
		double result;
		switch(doubleGen) {
		case 0:
			result = 0.0;
			break;
		case 1:
			result = 0.25;
			break;
		case 2:
			result = 0.50;
			break;
		case 3:
			result = 0.75;
			break;
		case 4:
			doubleGen = 0;
			result = 1.0;
			break;
		default:
			result = 0.0;
			break;
		}
		doubleGen++;
		return result;
	}

};

#endif