#ifndef GRADIENT_H
#define GRADIENT_H

#include <string>
#include <boost/archive/text_iarchive.hpp>

class Position;
class World;

class Gradient
{

private:
    // Used to serialize (save & load the instances of Gradient inside files)
    friend class boost::serialization::access;

    template <class GradientArchive>
    void serialize(GradientArchive &ar, const unsigned int version)
    {
        ar &distance;
        ar &h;
        ar &w;
        ar &center;
    }
    // -----------------------------------------------------------------------

    static const int POSSIBLE_DIRS = 8;

    static const int STRAIGHT_DISTANCE = 10;

    static const int DIAGONAL_DISTANCE = 14;

    int *distance;

    int h;

    int w;

    Position *center;

    void calculateGradient(World *world, Position *relevantPos);

public:
    static const int UNREACHABLE = 2147483647; // maximum value for an int

    Gradient();

    Gradient(Position *center, World *world);

    Gradient(Position *center, World *world, Position *relevantPos);

    std::string toString();

    int getHeight();

    int getWidth();

    int pointFrom(Position *pos, int preferredDir);

    int distanceFrom(Position *pos);
};

#endif
