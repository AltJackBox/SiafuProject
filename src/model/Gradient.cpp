#include <model/Gradient.h>
#include <model/World.h>
#include <model/Position.h>
#include <exceptions/PositionOnAWallException.h>

#include <vector>
#include <set>
#include <exception>
#include <iostream>
#include <algorithm>
#include <limits.h>

#include <fstream>

const int Gradient::UNREACHABLE = INT_MAX;

const int Gradient::POSSIBLE_DIRS = 8;

const int Gradient::STRAIGHT_DISTANCE = 10;

const int Gradient::DIAGONAL_DISTANCE = 14;

void Gradient::calculateGradient(World *world, Position *relevantPos)
{
    bool doneCalculating = false;
    bool foundRelevantPos = false;
    bool firstIteration = false; // check if the first iteration has been done, in order to avoid destruction of center

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            distance.push_back(UNREACHABLE);
        }
    }
    std::set<Position *> pending;
    std::set<Position *> next;
    std::vector<std::string> insertedPositions;

    distance[center->getRow() * w + center->getCol()] = 0;
    pending.insert(center);

    while (!doneCalculating)
    {
        for (auto pos : pending)
        {
            int distanceStraight = distance[pos->getRow() * w + pos->getCol()] + STRAIGHT_DISTANCE;
            int distanceDiagonal = distance[pos->getRow() * w + pos->getCol()] + DIAGONAL_DISTANCE;

            for (int dir = 0; dir < POSSIBLE_DIRS; dir += 2)
            {
                try
                {
                    Position* newPos = pos->calculateMove(dir);
                    if (newPos == nullptr) {
                        throw PositionOnAWallException();
                    }
                    if (distanceStraight < distance[newPos->getRow() * w + newPos->getCol()])
                    {
                        distance[newPos->getRow() * w + newPos->getCol()] = distanceStraight;
                        if (std::find(insertedPositions.begin(), insertedPositions.end(), newPos->toString()) == insertedPositions.end())
                        {
                            next.insert(newPos);
                            insertedPositions.push_back(newPos->toString());
                        }
                    }
                }
                catch (const PositionUnreachableException & err)
                {
                    continue;
                }
            }
            for (int dir = 1; dir < POSSIBLE_DIRS; dir += 2)
            {
                try
                {
                    Position* newPos = pos->calculateMove(dir);
                    if (newPos == nullptr) {
                        throw PositionOnAWallException();
                    }
                    if (distanceDiagonal < distance[newPos->getRow() * w + newPos->getCol()])
                    {
                        distance[newPos->getRow() * w + newPos->getCol()] = distanceDiagonal;
                        if (std::find(insertedPositions.begin(), insertedPositions.end(), newPos->toString()) == insertedPositions.end())
                        {
                            next.insert(newPos);
                            insertedPositions.push_back(newPos->toString());
                        }
                    }
                }
                catch (const PositionUnreachableException & e)
                {
                    continue;
                }
            }
            if ((relevantPos != nullptr) && (pending.find(relevantPos) != pending.end()))
            {
                foundRelevantPos = true;
                doneCalculating = true;
            }
        }

        if (firstIteration) {
            std::for_each(pending.begin(), pending.end(), [](Position* obj){ delete obj; });
        } else {
            firstIteration = true;
        }
        pending = next;
        next.clear();
        insertedPositions.clear();
        if (pending.empty())
        {
            doneCalculating = true;
        }
    }

    if (relevantPos != nullptr && !foundRelevantPos)
    {
        throw PositionUnreachableException();
    }
}

Gradient::Gradient(Position *center, World *world) : Gradient(center, world, nullptr)
{
}

Gradient::Gradient(Position *center, World *world, Position *relevantPos)
{
    h = world->getHeight();
    w = world->getWidth();

    this->center = center;

    calculateGradient(world, relevantPos);
}

Gradient::Gradient(Position *center, int h, int w, std::vector<int> distance)
{
    this->center = center;
    this->h = h;
    this->w = w;
    this->distance = distance;
}

std::string Gradient::toString()
{
    return center->toString();
}

int Gradient::getHeight()
{
    return h;
}

int Gradient::getWidth()
{
    return w;
}

int Gradient::pointFrom(Position *pos, int preferredDir)
{

    std::vector<int> optimalDirs(POSSIBLE_DIRS);
    int min = distance[pos->getRow() * w + pos->getCol()];
    int grad;

    if (min == 0)
    {
        return -1;
    }

    for (int dir = 0; dir < POSSIBLE_DIRS; dir++)
    {
        Position *aux;

        try
        {
            aux = pos->calculateMove(dir);
            if (aux == nullptr) {
                throw PositionOnAWallException();
            }
            grad = distance[aux->getRow() * w + aux->getCol()];
            if (grad == min)
            {
                optimalDirs.push_back(dir);
            }
            else if (grad < min)
            {
                min = grad;
                optimalDirs.clear();
                optimalDirs.push_back(dir);
            }
        }
        catch (const PositionUnreachableException &e)
        {
            continue;
        }
    }

    if (preferredDir != -1 && std::find(optimalDirs.begin(), optimalDirs.end(), preferredDir) != optimalDirs.end())
    {
        return preferredDir;
    }
    else
    {
        return optimalDirs.at(0);
    }
}

int Gradient::distanceFrom(Position *pos)
{
    return distance[pos->getRow() * w + pos->getCol()];
}

std::vector<int> Gradient::getDistance()
{
    return distance;
}

Position *Gradient::getCenter()
{
    return center;
}
