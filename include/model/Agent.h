#ifndef AGENT_H
#define AGENT_H

#include <model/Place.h>
#include <set>
#include <map>
#include <string>
#include <iostream>
#include <iterator>

class Place;
class World;
class Position;
class Publishable;

class Agent
{

private:
    static Place *DEFAULT_DESTINATION;

    static Place *getDefaultPlace(Position *pos, World *world)
    {
        if (DEFAULT_DESTINATION == nullptr)
        {
            DEFAULT_DESTINATION = new Place("StartingPosition", pos, world);
        }
        return DEFAULT_DESTINATION;
    }

    static const int WANDER_TURN = 3;

    static const int DEFAULT_SOBERNESS = 5;

    static const int POSSIBLE_DIRECTIONS = 8;

    static World *world;

    static bool infoFieldsLocked /* = false*/;

    static std::set<std::string> INFO_FIELDS;

    bool onAuto = true;

    std::string name;

    int dir;

    int speed = 1;

    Position *pos;

    bool atDestination;

    Place *destination;

    std::map<std::string, Publishable *> info;

    //bool visible = true;

    int zPriority;

    void basicChecks(World *thisAgentsWorld);

public:
    static void resetAgents()
    {
        infoFieldsLocked = false;
        INFO_FIELDS.empty();
    }

    Agent(std::string name, Position *start, World *world);

    Agent(std::string name, Position *start, World *world, int zPriority);

    static void lockInfoFields()
    {
        infoFieldsLocked = true;
    }

    bool isAtDestination();

    std::string toString();

    void setName(std::string name);

    std::string getName();

    int getZPriority();

    void setZPriority(int zPriority);

    Place *getDestination();

    int getSpeed();

    void setSpeed(int speed);

    void setDestination(Place *destination);

    int getDir();

    void setDir(int newDir);

    Position *getPos();

    void setPos(Position *pos);

    void set(std::string key, Publishable *value);

    bool checkAllInfoFieldsPresent();

    Publishable *get(std::string key);

    void turn(int turn);

    void moveTowardsDestination();

    void moveInDirection(int moveDir);

    void moveTowardsPlace(Place *place);

    void wanderAround(Place *place, int radius, int soberness);

    void wanderAround(Place *place, int radius);

    void wander();

    void wander(int soberness);

    // bool isVisible();

    // void setVisible( bool visible);

    static void initialize(World *agentsWorld)
    {
        world = agentsWorld;
        infoFieldsLocked = false;
    }

    bool equals(Agent *Agent);
};

#endif
