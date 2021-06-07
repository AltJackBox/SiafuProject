#include <model/Position.h>
#include <model/World.h>
#include <iostream>
#include <cmath>

void Position::initialize(World *worldObj, const double topRight[], const double bottomRight[], const double bottomLeft[])
{
    if (worldObj == NULL)
    {
        std::cerr << "Null world received!";
    }
    world = worldObj;
    width = world->getWidth();
    height = world->getHeight();
    // coordinateTools = new CoordinateTools(height, width, topRight, bottomRight, bottomLeft);
    initialized = true;
}

Position::Position(const int i, const int j)
{
    if (!initialized)
    {
        std::cerr << "Position not initialized";
    }

    if ((i >= height) || (i < 0) || (j >= width) || (j < 0))
    {
        std::cerr << "PositionOutOfTheMapException";
    }

    this->i = i;
    this->j = j;
}

// Position::Position(const double lat, const double lon)
//     {
//         this(coordinateTools.coordinatesToLocal(lat, lon));
//     }

std::string Position::toString()
{
    return i + "." + j;
}

Position *Position::calculateMove(const int rawDir)
{
    int dir = ((rawDir % DIRECTIONS) + DIRECTIONS) % DIRECTIONS;

    Position *p = new Position(this->i + COMPASS[dir][0], this->j + COMPASS[dir][1]);

    if (world->isAWall(p))
    {
        std::cerr << "PositionOnAWallException";
    }

    return p;
}

bool Position::equals(Position *p)
{

    if ((p->i == i) && (p->j == j))
    {
        return true;
    }
    else
    {
        return false;
    }
}

int Position::compareTo(const Position *p)
{
    if (p->i > i)
    {
        return -1;
    }
    else if (p->i < i)
    {
        return 1;
    }
    else if (p->j > j)
    {
        return -1;
    }
    else if (p->j < j)
    {
        return 1;
    }
    else
    {
        return (0);
    }
}

bool Position::isNear(const Position *pos)
{
    return isNear(pos, NEAR_DISTANCE);
}

bool Position::isNear(const Position *pos, const int radius)
{
    if (std::abs(pos->j - j) > radius)
    {
        return false;
    }

    if (std::abs(pos->i - i) > radius)
    {
        return false;
    }

    double distanceI = std::pow(pos->i - i, 2);
    double distanceJ = std::pow(pos->j - j, 2);
    double distance = std::sqrt(distanceI + distanceJ);
    if (distance > radius)
    {
        return false;
    }

    return true;
}

// double[] getCoordinates()
// {
//     return coordinateTools.localToCoordinates(this);
// }

int Position::getRow()
{
    return i;
}

void Position::setRow(const int newI)
{
    this->i = newI;
}

int Position::getCol()
{
    return j;
}

void Position::setCol(const int newJ)
{
    this->j = newJ;
}