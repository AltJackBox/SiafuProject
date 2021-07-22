#ifndef POSITION_H
#define POSITION_H

#include <model/World.h>
#include <model/CoordinateTools.h>
#include <iostream>

class World;

class Position
{

private:
    static const int NEAR_DISTANCE;

    static bool initialized;

    static CoordinateTools *coordinateTool;

    static int width;

    static int height;

    static World *world;

    static const int DIRECTIONS;

    static const int COMPASS[8][2];

    int i;

    int j;

public:
    static void initialize(World *worldObj, const double topRight[], const double bottomRight[], const double bottomLeft[])
    {
        if (worldObj == nullptr)
        {
            std::cerr << "Null world received!";
            exit(EXIT_FAILURE);
        }
        world = worldObj;
        width = world->getWidth();
        height = world->getHeight();
        coordinateTool = new CoordinateTools(height, width, topRight, bottomRight, bottomLeft);
        initialized = true;
    }

    Position();

    ~Position() {}

    static void removePositionPointers()
    {
        delete coordinateTool;
    }

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
