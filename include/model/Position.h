#ifndef POSITION_H
#define POSITION_H

#include <iostream>
#include <model/World.h>
#include <model/CoordinateTools.h>

class World;
class CoordinateTools;

class Position
{

private:
    static const int NEAR_DISTANCE = 15;

    static const long serialVersionUID = 1L;

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
