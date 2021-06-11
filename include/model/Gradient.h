#ifndef GRADIENT_H
#define GRADIENT_H

#include <string>


class Position;
class World;

class Gradient {

	private:

    static const int POSSIBLE_DIRS = 8;

    static const int STRAIGHT_DISTANCE = 10;

    static const int DIAGONAL_DISTANCE = 14;

    int* distance;

    int h;

    int w;

    Position* center;

    void calculateGradient(World* world, Position* relevantPos);

	public:

    static const int UNREACHABLE = 2147483647; // maximum value for an int

	Gradient(Position* center, World* world);

	Gradient(Position* center, World* world, Position* relevantPos);

	std::string toString();

	int getHeight();

	int getWidth();

	int pointFrom(Position* pos, int preferredDir);

	int distanceFrom(Position* pos);
};

#endif
