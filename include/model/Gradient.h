#ifndef GRADIENT_H
#define GRADIENT_H

// #include <model/Position.h>
// #include <boost/serialization/serialization.hpp>
// #include <boost/serialization/split_member.hpp>
// #include <boost/serialization/array.hpp>
#include <string>

class Position;
class World;

class Gradient
{

private:
    // Used to serialize (save & load the instances of Gradient inside files)
    // friend class boost::serialization::access;

    // template <class Archive>
    // void save(Archive &ar, const unsigned int version) const
    // {
    //     // invoke serialization of the base class
    //     ar << h;
    //     ar << w;
    //     ar << boost::serialization::make_array<int>(distance, h * w);
    //     ar << centeri;
    //     ar << centerj;
    //     delete center;
    // }

    // template <class Archive>
    // void load(Archive &ar, const unsigned int version)
    // {
    //     // invoke serialization of the base class
    //     ar >> h;
    //     ar >> w;
    //     ar >> boost::serialization::make_array<int>(distance, h * w);
    //     ar >> centeri;
    //     ar >> centerj;
    //     center = new Position(centeri, centerj);
    // }

    // template <class Archive>
    // void serialize(Archive &ar, const unsigned int version)
    // {
    //     //ar & distance & h & w & centeri & centerj;
    //     boost::serialization::split_member(ar, *this, version);
    // }
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

    Gradient(Position *center, int h, int w, int* distance);

    std::string toString();

    int getHeight();

    int getWidth();

    int pointFrom(Position *pos, int preferredDir);

    int distanceFrom(Position *pos);

    int* getDistance();

    Position* getCenter();
};

#endif
