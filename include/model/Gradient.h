#ifndef GRADIENT_H
#define GRADIENT_H

#include <string>
#include <vector>

class Position;
class World;

class Gradient
{

private:

    static const int POSSIBLE_DIRS;

    static const int STRAIGHT_DISTANCE;

    static const int DIAGONAL_DISTANCE;

    std::vector<int> distance;

    int h;

    int w;

    Position *center;

    void calculateGradient(World *world, Position *relevantPos);

public:
    static const int UNREACHABLE;

    Gradient();

    Gradient(Position *center, World *world);

    Gradient(Position *center, World *world, Position *relevantPos);

    Gradient(Position *center, int h, int w, std::vector<int> distance);

    std::string toString();

    int getHeight();

    int getWidth();

    int pointFrom(Position *pos, int preferredDir);

    int distanceFrom(Position *pos);

    std::vector<int> getDistance();

    Position* getCenter();
};

#endif
