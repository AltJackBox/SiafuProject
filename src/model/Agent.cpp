#include <model/Agent.h>
#include <model/World.h>
#include <model/Position.h>
#include <exception>
#include <stdlib.h>

void Agent::basicChecks(World *thisAgentsWorld)
{
    if (world == NULL)
    {
        std::cerr << "You need to initialize the agents.\n";
    }
    if (world != thisAgentsWorld)
    {
        std::cerr << "All your users must belong to the same world\n";
    }
}

Agent::Agent(std::string name, Position *start, World *world)
{
    Agent(name, start, world, 0);
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
    if (this->destination != NULL && this->destination->equals(destination))
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
    if (infoFieldsLocked && (info.find(key) != info.end()))
    {
        std::cerr << "InfoFieldsLockedException" + key + "\n";
    }
    INFO_FIELDS.insert(key);
    std::pair<std::string, Publishable *> pair;
    pair = std::make_pair(key, value);
    info.insert(pair);
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
        std::cerr << "InfoUndefinedException " + key + "\n";
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
                destination = NULL;
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
        return; // Place reached
    }

    pos = pos->calculateMove(moveDir);
    this->dir = moveDir;
}

void Agent::moveTowardsPlace(Place *place)
{
    try
    {
        moveInDirection(place->pointFrom(pos, dir));
    }
    catch (std::exception &e)
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

void Agent::wander(int soberness)
{
    atDestination = true;
    bool stuck = true;
    int random = rand() % 2;
    int searchDir = (random == 1) ? (-WANDER_TURN) : WANDER_TURN;
    int tries = 0;

    while (stuck && (tries < POSSIBLE_DIRECTIONS))
    {
        Position *target = NULL;

        try
        {
            target = pos->calculateMove(dir);
            pos = target;
            stuck = false;
        }
        catch (std::exception &e)
        {
            turn(searchDir);
            tries++;
        }
    }

    if (tries == POSSIBLE_DIRECTIONS)
    {
        std::cerr << "My name's " + name + " and you've got me stuck in a " + "one pixel wide room! I have rights!\n";
    }
    random = rand() % soberness;
    if (random == 0)
    {
        random = rand() % 2;
        if (random == 1)
        {
            turn(1);
        }
        else
        {
            turn(-1);
        }
    }
}

// bool Agent::isVisible()
// {
//     return visible;
// }

// void setVisible(bool visible)
// {
//     this->visible = visible;
// }


bool Agent::equals(Agent* agent)
{
    if (this == agent)
        return true;
    if (agent == NULL)
        return false;
    if (atDestination != agent->atDestination)
        return false;
    if (destination == NULL)
    {
        if (agent->destination != NULL)
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
    if (pos == NULL)
    {
        if (agent->pos != NULL)
            return false;
    }
    else if (!pos->equals(agent->pos))
        return false;
    if (speed != agent->speed)
        return false;
    // if (visible != agent->visible)
    //     return false;
    if (zPriority != agent->zPriority)
        return false;
    return true;
}