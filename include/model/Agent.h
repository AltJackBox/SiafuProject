#ifndef AGENT_H
#define AGENT_H

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

    Place *getDefaultPlace(Position *pos, World *world);

    static const int WANDER_TURN = 3;

    static const int DEFAULT_SOBERNESS = 5;

    static const int POSSIBLE_DIRECTIONS = 8;

    static World *world;

    bool infoFieldsLocked = false;

    static std::set<std::string> INFO_FIELDS;

    //static const Random RAND = new Random();

    bool onAuto = true;

    std::string name;

    int dir;

    int speed = 1;

    Position *pos;

    bool atDestination;

    Place *destination;

    //private std::string image;

    //private std::string previousImage;

    std::map<std::string, Publishable *> info;

    //bool visible = true;

    int zPriority;

    void basicChecks(World *thisAgentsWorld);

public:
    void resetAgents();

    Agent(std::string name, Position *start, World *world);

    Agent(std::string name, Position *start, World *world, int zPriority);

    void lockInfoFields();

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

    void wanderAround( Place* place,  int radius);

    void wander();

    void wander( int soberness);

    // bool isVisible();

    // void setVisible( bool visible);

    void initialize( World* agentsWorld);

    bool equals(Agent* Agent);
};

#endif
