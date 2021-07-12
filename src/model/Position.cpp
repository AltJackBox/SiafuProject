#include <model/Position.h>
#include <model/World.h>
#include <model/CoordinateTools.h>
#include <exceptions/PositionOnAWallException.h>
#include <exceptions/InitializationRequiredException.h>
#include <exceptions/PositionOutOfTheMapException.h>
#include <iostream>
#include <cmath>

bool Position::initialized = false;

CoordinateTools *Position::coordinateTool;

int Position::width;

int Position::height;

World *Position::world;

const int Position::NEAR_DISTANCE = 15;

const int Position::DIRECTIONS = 8;

const int Position::COMPASS[8][2] = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

Position::Position(const int i, const int j)
{
    if (!initialized)
    {
        throw InitializationRequiredException("Position not initialized");
    }

    if ((i >= height) || (i < 0) || (j >= width) || (j < 0))
    {
        throw PositionOutOfTheMapException();
    }

    this->i = i;
    this->j = j;
}

Position::~Position() {}

Position::Position(const double lat, const double lon) : Position(coordinateTool->coordinatesToLocal(lat, lon))
{
}

Position::Position(Position *p) : Position(p->i, p->j)
{
}

std::string Position::toString()
{
    return std::to_string(i) + "." + std::to_string(j);
}

Position *Position::calculateMove(const int rawDir)
{
    int dir = ((rawDir % DIRECTIONS) + DIRECTIONS) % DIRECTIONS;

    Position *p = new Position(this->i + COMPASS[dir][0], this->j + COMPASS[dir][1]);

    if (world->isAWall(p))
    {
        return nullptr;
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

double *Position::getCoordinates()
{
    return coordinateTool->localToCoordinates(this);
}

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