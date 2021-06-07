#ifndef POSITION_H
#define POSITION_H

#include <string>

class World;

class Position
{

private:
    static const int NEAR_DISTANCE = 15;

    static const long serialVersionUID = 1L;

    static bool initialized;

    //static CoordinateTools coordinateTools;

    static int width;

    static int height;

    static World *world;

    static const int DIRECTIONS = 8;

    const int COMPASS[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

    int i;

    int j;

public:
    void initialize(World *worldObj, const double topRight[], const double bottomRight[], const double bottomLeft[]);

    Position(const int i, const int j);

    // Position(const double lat, const double lon); USES COORDINATE TOOL

    std::string toString();

    Position *calculateMove(const int rawDir);

    bool equals(Position *p);

    int compareTo(const Position* p);

    bool isNear(const Position* pos);

    bool isNear(const Position* pos, const int radius);

    // double[] getCoordinates();

    int getRow();

    void setRow(const int newI);

    int getCol();

    void setCol(const int newJ);
};

#endif
