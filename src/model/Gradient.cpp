#include <model/Gradient.h>
#include <model/World.h>
#include <model/Position.h>

#include <vector>
#include <set>
#include <exception>
#include <iostream>
#include <algorithm>

void Gradient::calculateGradient(World *world, Position *relevantPos)
{
    distance = new int[h * w];
    bool doneCalculating = false;
    bool foundRelevantPos = false;

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            distance[i * w + j] = UNREACHABLE;
        }
    }
    std::set<Position *> pending;

    std::set<Position *> next;

    distance[center->getRow() * w + center->getCol()] = 0;
    pending.insert(center);

    while (!doneCalculating)
    {
        for (Position *pos : pending)
        {
            int distanceStraight = distance[pos->getRow() * w + pos->getCol()] + STRAIGHT_DISTANCE;
            int distanceDiagonal = distance[pos->getRow() * w + pos->getCol()] + DIAGONAL_DISTANCE;

            for (int dir = 0; dir < POSSIBLE_DIRS; dir += 2)
            {
                try
                {
                    Position *newPos = pos->calculateMove(dir);
                    if (distanceStraight < distance[newPos->getRow() * w + newPos->getCol()])
                    {
                        distance[newPos->getRow() * w + newPos->getCol()] = distanceStraight;
                        next.insert(newPos);
                    }
                }
                catch (const std::exception &e)
                {
                    continue;
                }
            }

            for (int dir = 1; dir < POSSIBLE_DIRS; dir += 2)
            {
                try
                {
                    Position *newPos = pos->calculateMove(dir);
                    if (distanceDiagonal < distance[newPos->getRow() * w + newPos->getCol()])
                    {
                        distance[newPos->getRow() * w + newPos->getCol()] = distanceDiagonal;
                        next.insert(newPos);
                    }
                }
                catch (const std::exception &e)
                {
                    continue;
                }
            }
            if (relevantPos != NULL && pending.find(relevantPos) != pending.end())
            {
                foundRelevantPos = true;
                doneCalculating = true;
            }
        }
        pending = next;
        next.clear();

        if (pending.empty())
        {
            doneCalculating = true;
        }
    }

    if (relevantPos != NULL && !foundRelevantPos)
    {
        std::cerr << "PositionUnreachableException\n";
    }
}

Gradient::Gradient(Position *center, World *world)
{
    Gradient(center, world, NULL);
}

Gradient::Gradient(Position *center, World *world, Position *relevantPos)
{
    // h = world->getHeight();
    // w = world->getWidth();
    this->center = center;

    // calculateGradient(world, relevantPos);
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
        catch (const std::exception &e)
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
