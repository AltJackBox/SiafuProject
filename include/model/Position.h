#ifndef POSITION_H
#define POSITION_H

#include <model/World.h>
#include <model/CoordinateTools.h>
#include <iostream>
#include <boost/archive/text_iarchive.hpp>

class World;
class CoordinateTools;

class Position
{

private:
    // Used to serialize (save & load the instances of Gradient inside files)
    friend class boost::serialization::access;

    template <class PositionArchive>
    void serialize(PositionArchive &ar, const unsigned int version)
    {
        ar &i &j &world;
    }
    // -----------------------------------------------------------------------

    static const int NEAR_DISTANCE = 15;

    static bool initialized;

    static CoordinateTools *coordinateTool;

    static int width;

    static int height;

    static World *world;

    static const int DIRECTIONS = 8;

    static const int COMPASS[8][2];

    int i;

    int j;

public:
    static void initialize(World *worldObj, const double topRight[], const double bottomRight[], const double bottomLeft[])
    {
        if (worldObj == NULL)
        {
            std::cerr << "Null world received!";
        }
        world = worldObj;
        width = world->getWidth();
        height = world->getHeight();
        coordinateTool = new CoordinateTools(height, width, topRight, bottomRight, bottomLeft);
        initialized = true;
    }

    Position();

    Position(const int i, const int j);

    Position(const double lat, const double lon);

    Position(Position *p);

    std::string toString();

    Position *calculateMove(const int rawDir);

    bool equals(Position *p);

    int compareTo(const Position *p);

    bool isNear(const Position *pos);

    bool isNear(const Position *pos, const int radius);

    double *getCoordinates();

    int getRow();

    void setRow(const int newI);

    int getCol();

    void setCol(const int newJ);
};

#endif
