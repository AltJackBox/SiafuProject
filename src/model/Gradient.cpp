#include <model/Gradient.h>
#include <model/World.h>
#include <model/Position.h>
#include <exceptions/PositionOnAWallException.h>

#include <vector>
#include <exception>
#include <iostream>
#include <algorithm>
#include <unordered_set>
#include <limits.h>

const int Gradient::UNREACHABLE = INT_MAX;

const int Gradient::POSSIBLE_DIRS = 8;

const int Gradient::STRAIGHT_DISTANCE = 10;

const int Gradient::DIAGONAL_DISTANCE = 14;

Gradient::~Gradient()
{
    delete center;
}

struct hashPosition // Hasher function
{
    size_t operator()(Position *p) const
    {
        return p->hashCode();
    }
};

struct keyEqual // Comparison function
{
    size_t operator()(Position *p1, Position *p2) const
    {
        return p1->toString().compare(p2->toString()) == 0;
    }
};

void Gradient::calculateGradient(World *world /*, Position *relevantPos*/)
{
    // int nbLoops = 0;
    // int nbInserted = 0;
    // int nbCatch = 0;

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

    std::unordered_set<Position *, hashPosition, keyEqual> pending;
    std::unordered_set<Position *, hashPosition, keyEqual> next;


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
                    Position *newPos = pos->calculateMove(dir);
                    if (newPos == nullptr)
                    {
                        throw PositionOnAWallException();
                    }
                    if (distanceStraight < distance[newPos->getRow() * w + newPos->getCol()])
                    {
                        distance[newPos->getRow() * w + newPos->getCol()] = distanceStraight;
                        if (next.insert(newPos).second == false)
                        { // not inserted
                            delete newPos;
                            continue;
                        }
                        // nbInserted++;
                        continue;
                        // }
                    }
                    delete newPos;
                }
                catch (const PositionUnreachableException &err)
                {
                    // nbCatch++;
                    continue;
                }
            }
            for (int dir = 1; dir < POSSIBLE_DIRS; dir += 2)
            {
                try
                {
                    Position *newPos = pos->calculateMove(dir);
                    if (newPos == nullptr)
                    {
                        throw PositionOnAWallException();
                    }
                    if (distanceDiagonal < distance[newPos->getRow() * w + newPos->getCol()])
                    {
                        distance[newPos->getRow() * w + newPos->getCol()] = distanceDiagonal;
                        if (next.insert(newPos).second == false)
                        {
                            delete newPos;
                            continue;
                        }
                        // nbInserted++;
                        continue;
                        // }
                    }
                    delete newPos;
                }
                catch (const PositionUnreachableException &e)
                {
                    // nbCatch++;
                    continue;
                }
            }
            // if ((relevantPos != nullptr) && (pending.find(relevantPos) != pending.end()))
            // {
            //     foundRelevantPos = true;
            //     doneCalculating = true;
            // }
        }
        // nbLoops++;
        if (firstIteration)
        {
            std::for_each(pending.begin(), pending.end(), [](Position *obj)
                          { delete obj; });
        }
        else
        {
            firstIteration = true;
        }
        pending = next;
        next.clear();
        if (pending.empty())
        {
            doneCalculating = true;
        }
    }
    // std::cout << "Loops = " << std::to_string(nbLoops) << "\n";
    // std::cout << "Catchs = " << std::to_string(nbCatch) << "\n";
    // std::cout << "Insertions = " << std::to_string(nbInserted) << "\n\n";
    // if (relevantPos != nullptr && !foundRelevantPos)
    // {
    //     throw PositionUnreachableException();
    // }
}

// Gradient::Gradient(Position *center, World *world) : Gradient(center, world, nullptr)
// {
// }

Gradient::Gradient(Position *center, World *world /*, Position *relevantPos*/)
{
    h = world->getHeight();
    w = world->getWidth();

    this->center = center;
    // std::cout << "\n";
    // std::cout << "POSITION = " << center->toString() << "\n";
    calculateGradient(world/*, relevantPos*/);
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

    std::vector<int> optimalDirs;
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
            if (aux == nullptr)
            {
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
            delete aux;
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
