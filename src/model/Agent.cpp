#include <model/Agent.h>
#include <model/World.h>
#include <model/Position.h>
#include <exceptions/InfoFieldsLockedException.h>
#include <exceptions/InfoUndefinedException.h>
#include <exceptions/InitializationRequiredException.h>
#include <exceptions/PositionOnAWallException.h>
#include <office/Constants.h>
#include <exception>
#include <stdlib.h>
#include <random>

Place *Agent::DEFAULT_DESTINATION = nullptr;

World *Agent::world;

bool Agent::infoFieldsLocked = false;

std::set<std::string> Agent::INFO_FIELDS;

Agent::~Agent()
{
    if (pos)
    {
        delete pos;
        pos = nullptr;
    }
    // erasing entries which contains places, because all places of the world have already been deleted at this point
    info.erase(Fields::DESIRED_TOILET);
    info.erase(Fields::DESK);
    info.erase(Fields::SEAT);
    info.erase(Fields::TEMPORARY_DESTINATION);
    info.erase(Fields::WAITING_PLACE);
    for (std::pair<const std::string, Publishable *> &inf : info)
    {
        if (inf.second)
        {
            delete inf.second;
            inf.second = nullptr;
        }
    }
    info.clear();
}

void Agent::basicChecks(World *thisAgentsWorld)
{
    if (world == nullptr)
    {
        throw InitializationRequiredException("You need to initialize the agents.");
    }
    if (world != thisAgentsWorld)
    {
        throw std::runtime_error("All your users must belong to the same world");
    }
}

Agent::Agent(std::string name, Position *start, World *world) : Agent(name, start, world, 0)
{
}

Agent::Agent(std::string name, Position *start, World *world, int zPriority)
{
    basicChecks(world);
    this->name = name;
    this->dir = 0;
    this->pos = start;
    this->destination = getDefaultPlace(start, world);
    this->atDestination = true;
    this->zPriority = zPriority;
}

bool Agent::isAtDestination()
{
    return atDestination;
}

std::string Agent::toString()
{
    return getName();
}

void Agent::setName(std::string name)
{
    this->name = name;
}

std::string Agent::getName()
{
    return name;
}

int Agent::getZPriority()
{
    return zPriority;
}

void Agent::setZPriority(int zPriority)
{
    this->zPriority = zPriority;
}

Place *Agent::getDestination()
{
    return destination;
}

int Agent::getSpeed()
{
    return speed;
}

void Agent::setSpeed(int speed)
{
    this->speed = speed;
}

void Agent::setDestination(Place *destination)
{
    if (this->destination != nullptr && this->destination->equals(destination))
    {
        return;
    }
    else
    {
        atDestination = false;
        this->destination = destination;
    }
}

int Agent::getDir()
{
    return dir;
}

void Agent::setDir(int newDir)
{
    dir = newDir % POSSIBLE_DIRECTIONS;
    if (dir < 0)
    {
        dir += POSSIBLE_DIRECTIONS;
    }
}

Position *Agent::getPos()
{
    return pos;
}

void Agent::setPos(Position *pos)
{
    this->pos = pos;
}

void Agent::set(std::string key, Publishable *value)
{
    if (infoFieldsLocked && (info.find(key) == info.end()))
    {
        throw InfoFieldsLockedException(key);
    }
    INFO_FIELDS.insert(key);
    std::pair<std::string, Publishable *> pair;
    pair = std::make_pair(key, value);
    info[pair.first] = pair.second;
}

bool Agent::checkAllInfoFieldsPresent()
{
    std::set<std::string> keys;
    for (std::map<std::string, Publishable *>::iterator it = info.begin(); it != info.end(); ++it)
    {
        keys.insert(it->first);
    }
    return keys == INFO_FIELDS;
}

Publishable *Agent::get(std::string key)
{
    if (info.find(key) == info.end())
    {
        throw InfoUndefinedException(key);
    }
    return info.at(key);
}

void Agent::turn(int turn)
{
    setDir(dir + turn);
}

void Agent::moveTowardsDestination()
{
    if (isAtDestination())
    {
        return;
    }
    else
    {
        for (int i = 0; i < speed; i++)
        {
            moveTowardsPlace(destination);

            if (pos->equals(destination->getPos()))
            {
                destination = nullptr;
                atDestination = true;
                break;
            }
        }
    }
}

void Agent::moveInDirection(int moveDir)
{
    if (moveDir == -1)
    {
        return;
    }

    Position* aux = pos->calculateMove(moveDir);
    if (aux == nullptr)
    {
        throw PositionOnAWallException();
    }
    delete pos;
    pos = aux;
    this->dir = moveDir;
}

void Agent::moveTowardsPlace(Place *place)
{
    try
    {
        moveInDirection(place->pointFrom(pos, dir));
    }
    catch (const PositionUnreachableException &e)
    {
        {
            std::cerr << "Agent '" + this->getName() + "' can't reach '" + place->getName() + "' at '" + pos->toString() + "'\n";
        }
    }
}

void Agent::wanderAround(Place *place, int radius, int soberness)
{
    atDestination = true;
    if (place->distanceFrom(pos) > radius)
    {
        moveTowardsPlace(place);
    }
    else
    {
        wander(soberness);
    }
}

void Agent::wanderAround(Place *place, int radius)
{
    wanderAround(place, radius, DEFAULT_SOBERNESS);
}

void Agent::wander()
{
    wander(DEFAULT_SOBERNESS);
}

// Random Utilization : Modify the commented lines
void Agent::wander(int soberness)
{
    atDestination = true;
    bool stuck = true;

    // std::random_device rd;  //Will be used to obtain a seed for the random number engine
    // std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    // std::uniform_int_distribution<> dis(0, 1);

    // int random = dis(gen);

    // int searchDir = (random == 1) ? (-WANDER_TURN) : WANDER_TURN;
    int searchDir = (-WANDER_TURN);

    int tries = 0;

    while (stuck && (tries < POSSIBLE_DIRECTIONS))
    {
        Position *target;

        try
        {
            target = pos->calculateMove(dir);
            if (target == nullptr)
            {
                throw PositionOnAWallException();
            }
            delete pos;
            pos = target;
            stuck = false;
        }
        catch (const PositionUnreachableException &e)
        {
            turn(searchDir);
            tries++;
        }
    }

    if (tries == POSSIBLE_DIRECTIONS)
    {
        std::cerr << "My name's " + name + " and you've got me stuck in a " + "one pixel wide room! I have rights!\n";
    }
    // std::uniform_int_distribution<> dissob(0, soberness - 1);
    // random = dissob(gen);
    // if (random == 0)
    // {
    if (soberness == 0)
    {
        // random = dis(gen);
        // if (random == 1)
        // {
        turn(1);
    }
    // else
    // {
    //     turn(-1);
    // }
}

bool Agent::equals(Agent *agent)
{
    if (this == agent)
        return true;
    if (agent == nullptr)
        return false;
    if (atDestination != agent->atDestination)
        return false;
    if (destination == nullptr)
    {
        if (agent->destination != nullptr)
            return false;
    }
    else if (!destination->equals(agent->destination))
        return false;
    if (dir != agent->dir)
        return false;
    if (info.empty())
    {
        if (!agent->info.empty())
            return false;
    }
    else if (!(info == agent->info))
        return false;
    if (name.empty())
    {
        if (!agent->name.empty())
            return false;
    }
    else if (!(name == agent->name))
        return false;
    if (onAuto != true && onAuto != false)
    {
        if (agent->onAuto == true || agent->onAuto == false)
            return false;
    }
    else if (!(onAuto == agent->onAuto))
        return false;
    if (pos == nullptr)
    {
        if (agent->pos != nullptr)
            return false;
    }
    else if (!pos->equals(agent->pos))
        return false;
    if (speed != agent->speed)
        return false;
    if (zPriority != agent->zPriority)
        return false;
    return true;
}