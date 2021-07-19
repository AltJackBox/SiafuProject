#ifndef AGENTMODEL_H
#define AGENTMODEL_H

#include <behaviormodels/BaseAgentModel.h>
#include <string>

class Place;
class World;
class EasyTime;
class Text;
class Agent;

class AgentModel : public BaseAgentModel
{

private:
    std::string lastHandleInfectionExecution;

    std::string healthy = "Healthy";
    std::string infected = "Infected";
    std::string infecting = "Infecting";
    std::string cured = "Cured";

    bool infectionDetected = false;
    int day = 1;

    Place *restHomeDoor;
    Place *apartmentThreeDoor;
    Place *houseDoor;

    std::vector<Agent*> createWorker(const std::string type, const std::string bedLocation, const std::string seatLocation);

    void handleInfection(std::vector<Agent *> agents, EasyTime *now);

    void handlePersonBodySensors(Agent *a);

    void handlePerson(Agent *a, EasyTime *now);

    void beAtGlobalMeeting(Agent *a);

    void goToGlobalMeeting(Agent *a);

    void handleEvent(Agent *a);

    void beAtToilet(Agent *a, EasyTime *now);

    void arriveAtToilet(Agent *a, EasyTime *now);

    void lineInToilet(Agent *a, EasyTime *now);

    Place *getNearestBathroomNotBusy(Agent *a, std::string bathroomName);

    void goToToilet(Agent *a);

    bool isTimeForToilet(Agent *a, EasyTime *now);

    void goHome(Agent *a);

    void goToSleep(Agent *a);

    void goToDesk(Agent *a);

    void beAtDesk(Agent *a);

    Text *booleanSort(std::string op);

    Text *intSort(std::string op);

    double distanceBetweenAgents(Agent *a, Agent *b);

    std::string agentName(Agent *a);

    void isInfectionDetected(std::vector<Agent *> agents, EasyTime *easyTime);

    void isolateAgent(Agent *a);

    void infect(Agent *a, EasyTime *now);

    void infect(Agent *a, EasyTime *now, int daysAfterInfection);

    void infectingOthers(std::vector<Agent *> agents, EasyTime *now);

    void cure(std::vector<Agent *> agents, EasyTime *now);

    bool agentCanInfectOthers(Agent *a);

    bool agentCanBeInfected(Agent *a);

    bool agentSituation(Agent *a, std::string situation);

    void willTheAgentBeInfected(Agent *infected, Agent *notInfected, EasyTime *now);

    void increaseDaysAfterInfection(std::vector<Agent *> agents, EasyTime *now);

    void print(std::string message, EasyTime *easyTime);

    void printDayInfo();

    void printAgentInfo(Agent *a, int d, EasyTime* n);

public:
    AgentModel(World *world);

    std::vector<Agent *> createAgents() override;

    void doIteration(std::vector<Agent *> agents) override;
};

#endif
