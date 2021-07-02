#include <office/AgentModel.h>
#include <office/Constants.h>
#include <model/World.h>
#include <model/Agent.h>
#include <model/Position.h>
#include <types/EasyTime.h>
#include <types/Text.h>
#include <types/TimePeriod.h>
#include <types/BooleanType.h>
#include <behaviormodels/BaseAgentModel.h>
#include <Calendar.h>
#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <random>
#include <cmath>

void AgentModel::createWorker(std::vector<Agent *> people, const std::string type, const std::string bedLocation, const std::string seatLocation)
{
    int bedIndex = 0;
    int seatIndex = 0;
    std::vector<Place *> beds;
    std::vector<Place *> seats;
    try
    {
        std::vector<Place *> beds = world->getPlacesOfType(bedLocation);
        std::vector<Place *> seats = world->getPlacesOfType(seatLocation);
    }
    catch (std::exception &e)
    {
        std::cerr << "RuntimeException : No beds or seats defined\n";
    }

    int i = 0;
    while (bedIndex != beds.size() && seatIndex != seats.size())
    {
        Place *desk = beds[bedIndex];
        Place *seat = seats[seatIndex];

        Agent *a = new Agent(type + " - " + std::to_string(i + 1), desk->getPos(), world);
        //a->setVisible(true);
        EasyTime *wakeUpTime = (new EasyTime(Constants::AVERAGE_WAKE_UP_TIME))->blur(Constants::WAKE_UP_START_BLUR);
        EasyTime *sleepTime = (new EasyTime(wakeUpTime))->shift(Constants::AVERAGE_WAKE_HOURS, 0)->blur(Constants::SLEEP_END_BLUR);
        EasyTime *toiletInterval = (new EasyTime(Constants::AVERAGE_TOILET_INTERVAL))->blur(Constants::TOILET_BLUR);

        a->set(Fields::TYPE, new Text(type));
        a->set(Fields::SEAT, seat);
        a->set(Fields::DESK, desk);
        a->set(Fields::WAKE_UP_TIME, wakeUpTime);
        a->set(Fields::SLEEP_TIME, sleepTime);
        a->set(Fields::ACTIVITY, ActivityManager::getActivity("LEAVING_WORK"));
        a->set(Fields::TOILET_INTERVAL, toiletInterval);
        a->set(Fields::NEXT_TOILET_VISIT, (new EasyTime(wakeUpTime))->shift(toiletInterval));
        a->set(Fields::DESIRED_TOILET, new Text("None"));
        a->set(Fields::NEXT_EVENT_TIME, new Text("None"));
        a->set(Fields::TOILET_DURATION, new Text("None"));
        a->set(Fields::WAITING_PLACE, new Text("None"));
        a->set(Fields::EVENT, new Text("None"));
        a->set(Fields::TEMPORARY_DESTINATION, new Text("None"));

        a->set(Fields::BODYTEMPERATURE, new Text("36.5"));   // ºC
        a->set(Fields::BLOODPRESSURE, new Text("120 / 80")); // mmHg / mmHg
        a->set(Fields::BLOODOXYGEN, new Text("95.3"));       // %
        //a->set(GLUCOSE, new Text("90.1")); // mg/dL
        //a->set(PACEMAKERACTIVE, new Text("0"));

        a->set(Fields::FEVER, boolSort(Fields::FEVER));
        a->set(Fields::FEVER_DURATION, intSort(Fields::FEVER_DURATION));

        a->set(Fields::SYMPTOMS, boolSort(Fields::SYMPTOMS));
        a->set(Fields::SYMPTOMS_DURATION, intSort(Fields::SYMPTOMS_DURATION));
        a->set(Fields::SYMPTOMS_DAYS_TO_START, intSort(Fields::SYMPTOMS_DAYS_TO_START));

        a->set(Fields::ABFC_USE_OF_N95_MASK, boolSort(Fields::ABFC_USE_OF_N95_MASK));
        a->set(Fields::AAFC_USE_OF_N95_MASK, boolSort(Fields::AAFC_USE_OF_N95_MASK));

        a->set(Fields::ABFC_USE_OF_OTHER_MASK, boolSort(Fields::ABFC_USE_OF_OTHER_MASK));
        a->set(Fields::AAFC_USE_OF_OTHER_MASK, boolSort(Fields::AAFC_USE_OF_OTHER_MASK));

        a->set(Fields::ABFC_USE_OF_EYE_PROTECTION, boolSort(Fields::ABFC_USE_OF_EYE_PROTECTION));
        a->set(Fields::AAFC_USE_OF_EYE_PROTECTION, boolSort(Fields::AAFC_USE_OF_EYE_PROTECTION));

        a->set(Fields::ABFC_WASH_HANDS, boolSort(Fields::ABFC_WASH_HANDS));
        a->set(Fields::AAFC_WASH_HANDS, boolSort(Fields::AAFC_WASH_HANDS));

        a->set(Fields::ABFC_PHYSICAL_DISTANCE, intSort(Fields::ABFC_PHYSICAL_DISTANCE));
        a->set(Fields::AAFC_PHYSICAL_DISTANCE, intSort(Fields::AAFC_PHYSICAL_DISTANCE));

        a->set(Fields::SITUATION, new Text(healthy));
        a->set(Fields::INFECTION_DETECTED, new Text(std::to_string(false)));
        a->set(Fields::DAYS_AFTER_INFECTION, new Text(std::to_string(0)));
        a->set(Fields::INFECTION_TIME, new Text(""));

        a->setSpeed(Constants::DEFAULT_SPEED);
        people.push_back(a);
        i++;
        bedIndex++;
        seatIndex++;
    }
}

void AgentModel::handleInfection(std::vector<Agent *> agents, EasyTime *now)
{

    if (lastHandleInfectionExecution.empty())
    {
        printDayInfo();
        int agentIndex = 0;
        while (agentIndex != agents.size())
        {
            Agent *a = agents[agentIndex];
            if (agentName(a).compare("2") == 0)
            {
                print("Agent 2 is infected", now);
                infect(a, now, -1);
            }
            agentIndex++;
        }
    }

    if (lastHandleInfectionExecution.empty() || !(lastHandleInfectionExecution.compare(now->toString()) == 0))
    {

        if (now->toString().compare((new EasyTime(0, 0))->toString()) == 0)
        {
            day++;
            // writeDailyData(agents);
            printDayInfo();
        }

        //The 1 day delay is due to the exams
        isInfectionDetected(agents, now);

        increaseDaysAfterInfection(agents, now);

        infectingOthers(agents, now);
        cure(agents, now);

        //writeData(agents, now);

        for (int i = 0; i < agents.size(); i++)
        {
            for (int j = i + 1; j < agents.size(); j++)
            {
                if (agentCanInfectOthers(agents[i]) && agentCanBeInfected(agents[j]))
                {
                    willTheAgentBeInfected(agents[i], agents[j], now);
                }
                else if (agentCanInfectOthers(agents[j]) && agentCanBeInfected(agents[i]))
                {
                    willTheAgentBeInfected(agents[j], agents[i], now);
                }
            }
        }
        lastHandleInfectionExecution = now->toString();
    }
}

AgentModel::AgentModel(World *world) : BaseAgentModel(world)
{
    try
    {
        restHomeDoor = *(world->getPlacesOfType("RestHomeEntrance").begin());
        //apartmentOneDoor = world.getPlacesOfType("ApartmentOneEntrance").iterator().next();
        //apartmentTwoDoor = world.getPlacesOfType("ApartmentTwoEntrance").iterator().next();
        //apartmentThreeDoor = world.getPlacesOfType("ApartmentThreeEntrance").iterator().next();
        //houseDoor = world.getPlacesOfType("HouseEntrance").iterator().next();
    }
    catch (std::exception &e)
    {
        std::cerr << "One or more doors are undefined\n";
    }
}

std::vector<Agent *> AgentModel::createAgents()
{
    std::vector<Agent *> people(Constants::POPULATION);
    createWorker(people, "RestHomeResident", "RestHomeBeds", "RestHomeSeats");
    //createWorker(people, "Student", "StudentDesk");
    return people;
}

void AgentModel::doIteration(std::vector<Agent *> agents)
{
    Calendar *time = world->getTime();
    EasyTime *now = new EasyTime(time->getHour(), time->getMin());

    handleInfection(agents, now);

    int peopleIndex = 0;
    while (peopleIndex != agents.size())
    {
        Agent *a = agents[peopleIndex];
        handlePerson(a, now);
        handlePersonBodySensors(a);
        peopleIndex++;
    }
}

void AgentModel::handlePersonBodySensors(Agent *a)
{
    std::string string = (a->get(Fields::BLOODOXYGEN))->toString();
    std::replace(string.begin(), string.end(), ',', '.');
    double bloodOxygen = std::stod(string);

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);

    bloodOxygen = bloodOxygen < 95 ? bloodOxygen + dis(gen) : bloodOxygen - dis(gen);
    a->set(Fields::BLOODOXYGEN, new Text(std::to_string(bloodOxygen)));

    std::string str = (a->get(Fields::BODYTEMPERATURE))->toString();
    std::replace(str.begin(), str.end(), ',', '.');

    double bodytemperature = std::stod(str);
    bodytemperature = bodytemperature < 36.5 ? bodytemperature + dis(gen) : bodytemperature - dis(gen);
    a->set(Fields::BODYTEMPERATURE, new Text(std::to_string(bodytemperature)));

    //double glucose = Double.parseDouble(a.get(GLUCOSE).tostd::string().replace(',', '.'));
    //glucose = glucose < 95 ? glucose + rand.nextDouble() : glucose - rand.nextDouble();
    //a.set(GLUCOSE, new Text(std::string.format("%.2f",glucose)));
}

void AgentModel::handlePerson(Agent *a, EasyTime *now)
{
    Activity *activity = (Activity *)a->get(Fields::ACTIVITY);
    //std::string name = activity->toString();

    try
    {

        if (activity == ActivityManager::RESTING)
        {
            if (now->isAfter((EasyTime *)a->get(Fields::WAKE_UP_TIME)) && now->isBefore((EasyTime *)a->get(Fields::SLEEP_TIME)))
            {
                goToDesk(a);
                a->set(Fields::NEXT_TOILET_VISIT, (new EasyTime(((EasyTime *)a->get(Fields::WAKE_UP_TIME))))->shift((EasyTime *)a->get(Fields::TOILET_INTERVAL)));
            }
            return;
        }
        else if (activity == ActivityManager::LEAVING_WORK)
        {
            if (a->isAtDestination())
            {
                goToSleep(a);
            }
            return;
        }
        else if (activity == ActivityManager::GOING_2_DESK)
        {
            if (a->isAtDestination())
            {
                beAtDesk(a);
            }
            return;
        }
        else if (activity == ActivityManager::GOING_2_TOILET)
        {
            if (a->isAtDestination())
            {
                lineInToilet(a, now);
            }
            return;
        }
        else if (activity == ActivityManager::GOING_2_GLOBAL_LUNCH)
        {
            if (a->isAtDestination())
            {
                beAtGlobalMeeting(a);
            }
            return;
        }
        else if (activity == ActivityManager::AT_DESK)
        {
            //a.wanderAround((Place) (a.get(WAITING_PLACE)), INLINE_WANDER);
            if (now->isAfter((EasyTime *)a->get(Fields::SLEEP_TIME)) || now->isIn(new TimePeriod(new EasyTime(0, 0), (EasyTime *)a->get(Fields::WAKE_UP_TIME))))
            {
                goHome(a);
            }
            handleEvent(a);
            if (isTimeForToilet(a, now))
            {
                goToToilet(a);
            }
            return;
        }
        else if (activity == ActivityManager::ENTERING_TOILET)
        {
            if (a->isAtDestination())
            {
                arriveAtToilet(a, now);
            }
            return;
        }
        else if (activity == ActivityManager::IN_TOILET)
        {
            beAtToilet(a, now);
            return;
        }
        else
        {
            std::cerr << "RuntimeException : Unknown Activity\n";
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "RuntimeException :Unknown info requested for " + a->toString() + "\n";
    }
}

void AgentModel::beAtGlobalMeeting(Agent *a)
{
    if (((Text *)a->get(Fields::EVENT))->toString().compare("GlobalMeetingEnded") == 0)
    {
        a->set(Fields::EVENT, new Text("None"));
        goToDesk(a);
    }
}

void AgentModel::goToGlobalMeeting(Agent *a)
{
    //a.setImage("HumanYellow");
    a->setDestination((Place *)a->get("TemporaryDestination"));
    a->set(Fields::ACTIVITY, ActivityManager::GOING_2_GLOBAL_LUNCH);
}

void AgentModel::handleEvent(Agent *a)
{
    Publishable *e = a->get(Fields::EVENT);
    if ((e->getType().compare("Text") == 0) && (e->toString().compare("None") == 0))
    {
        return;
    }

    std::string event = e->toString();
    if (event.compare("ConferenceRoomMeeting") == 0)
    {
        goToGlobalMeeting(a);
    }
}

void AgentModel::beAtToilet(Agent *a, EasyTime *now)
{
    if (now->isAfter((EasyTime *)(a->get(Fields::NEXT_EVENT_TIME))))
    {
        goToDesk(a);
        ((Place *)a->get(Fields::DESIRED_TOILET))->set("Busy", new BooleanType(false));
    }
}

void AgentModel::arriveAtToilet(Agent *a, EasyTime *now)
{
    a->set(Fields::ACTIVITY, ActivityManager::IN_TOILET);

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, Constants::TOILET_VISIT_DURATION + 1);

    EasyTime *nextEventTime = (new EasyTime(now))->shift(0, dis(gen));
    if (nextEventTime->toString().compare((new EasyTime(23, 59))->toString()) == 0)
    {
        nextEventTime->shift(0, -1);
    }
    a->set(Fields::NEXT_EVENT_TIME, nextEventTime);
}

void AgentModel::lineInToilet(Agent *a, EasyTime *now)
{
    Publishable *info = a->get(Fields::DESIRED_TOILET);
    Place *toilet;

    if (!(info->getType().compare("Place")))
    {
        //try {
        toilet = getNearestBathroomNotBusy(a, "RestHomeBathroom");
        //toilet = world.getNearestPlaceOfType("RestHomeBathroom", a.getPos());
        //} catch (PlaceNotFoundException e) {
        //	throw new RuntimeException(e);
        //}
        a->set(Fields::DESIRED_TOILET, toilet);
        a->set(Fields::NEXT_EVENT_TIME, (new EasyTime(now))->shift(new EasyTime(0, Constants::MAX_WAIT_TIME)));
    }
    else
    {
        //toilet = (Place) info;
        toilet = getNearestBathroomNotBusy(a, "RestHomeBathroom");
        a->set(Fields::DESIRED_TOILET, toilet);
        a->set(Fields::NEXT_EVENT_TIME, (new EasyTime(now))->shift(new EasyTime(0, Constants::MAX_WAIT_TIME)));
    }

    if (now->isAfter((EasyTime *)a->get(Fields::NEXT_EVENT_TIME)))
    {
        a->set(Fields::NEXT_TOILET_VISIT, (new EasyTime(now))->shift(0, 2 * Constants::TOILET_RETRY_BLUR)->blur(Constants::TOILET_RETRY_BLUR));
        goToDesk(a);
    }
    bool busy = ((BooleanType *)toilet->get("Busy"))->getValue();
    if (busy)
    {
        a->wanderAround((Place *)(a->get(Fields::WAITING_PLACE)), Constants::INLINE_WANDER);
    }
    else
    {
        toilet->set("Busy", new BooleanType(true));
        a->setDestination(toilet);
        a->set(Fields::ACTIVITY, ActivityManager::ENTERING_TOILET);
    }
}

Place *AgentModel::getNearestBathroomNotBusy(Agent *a, std::string bathroomName)
{
    int bathRoomIndex = 0;
    std::vector<Place *> places;
    try
    {
        places = world->getPlacesOfType(bathroomName);
    }
    catch (std::exception &e)
    {
        std::cerr << "RuntimeException : No bathroom defined\n";
    }
    while (bathRoomIndex != places.size())
    {
        Place *bathroom = places[bathRoomIndex];
        if (!((BooleanType *)bathroom->get("Busy"))->getValue())
        {
            return bathroom;
        }
        bathRoomIndex++;
    }

    try
    {
        return world->getNearestPlaceOfType(bathroomName, a->getPos());
    }
    catch (std::exception &e)
    {
        std::cerr << "RuntimeException\n";
    }
    return nullptr;
}

void AgentModel::goToToilet(Agent *a)
{
    try
    {
        a->setDestination(world->getNearestPlaceOfType("RestHomeBathroomEntrance", a->getPos()));
    }
    catch (std::exception &e)
    {
        std::cerr << "RuntimeException\n";
    }
    a->set(Fields::ACTIVITY, ActivityManager::GOING_2_TOILET);
    a->set(Fields::WAITING_PLACE, a->getDestination());
}

bool AgentModel::isTimeForToilet(Agent *a, EasyTime *now)
{
    EasyTime *nextVisit = (EasyTime *)a->get(Fields::NEXT_TOILET_VISIT);
    if (nextVisit->isBefore((EasyTime *)a->get(Fields::WAKE_UP_TIME)))
    {
        nextVisit->shift((EasyTime *)a->get(Fields::TOILET_INTERVAL));
        a->set(Fields::NEXT_TOILET_VISIT, nextVisit);
    }
    if (now->isAfter((EasyTime *)a->get(Fields::NEXT_TOILET_VISIT)))
    {
        a->set(Fields::NEXT_TOILET_VISIT, (new EasyTime(now))->shift((EasyTime *)a->get(Fields::TOILET_INTERVAL)));
        //a->setImage("HumanGreen");
        return true;
    }
    else
    {
        return false;
    }
}

void AgentModel::goHome(Agent *a)
{
    a->setDestination((Place *)a->get(Fields::DESK));
    a->set(Fields::ACTIVITY, ActivityManager::LEAVING_WORK);
}

void AgentModel::goToSleep(Agent *a)
{
    a->set(Fields::ACTIVITY, ActivityManager::RESTING);
    //a->setVisible(true);
}

void AgentModel::goToDesk(Agent *a)
{
    a->set(Fields::ACTIVITY, ActivityManager::GOING_2_DESK);
    //a->setImage("HumanBlue");
    //a->setVisible(true);
    a->setDestination((Place *)a->get(Fields::SEAT));
}

void AgentModel::beAtDesk(Agent *a)
{
    a->set(Fields::ACTIVITY, ActivityManager::AT_DESK);
}

Text *AgentModel::boolSort(std::string op)
{

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);

    bool result = false;
    double random = dis(gen);

    if (op.compare(Fields::FEVER) == 0)
    {
        result = random < Constants::FEVER_PROBABILITY;
    }
    else if (op.compare(Fields::SYMPTOMS) == 0)
    {
        result = random < Constants::SYMPTOMS_PROBABILITY;
    }
    else if (op.compare(Fields::ABFC_USE_OF_N95_MASK) == 0)
    {
        result = random < Constants::BFC_USE_OF_N95_MASK;
    }
    else if (op.compare(Fields::AAFC_USE_OF_N95_MASK) == 0)
    {
        result = random < Constants::AFC_USE_OF_N95_MASK;
    }
    else if (op.compare(Fields::ABFC_USE_OF_OTHER_MASK) == 0)
    {
        result = random < Constants::BFC_USE_OF_OTHER_MASK;
    }
    else if (op.compare(Fields::AAFC_USE_OF_OTHER_MASK) == 0)
    {
        result = random < Constants::AFC_USE_OF_OTHER_MASK;
    }
    else if (op.compare(Fields::ABFC_USE_OF_EYE_PROTECTION) == 0)
    {
        result = random < Constants::BFC_USE_OF_EYE_PROTECTION;
    }
    else if (op.compare(Fields::AAFC_USE_OF_EYE_PROTECTION) == 0)
    {
        result = random < Constants::AFC_USE_OF_EYE_PROTECTION;
    }
    else if (op.compare(Fields::ABFC_WASH_HANDS) == 0)
    {
        result = random < Constants::BFC_WASH_HANDS;
    }
    else if (op.compare(Fields::AAFC_WASH_HANDS) == 0)
    {
        result = random < Constants::AFC_WASH_HANDS;
    }
    return new Text(std::to_string(result));
}

Text *AgentModel::intSort(std::string op)
{
    int result = 0;

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    if (op.compare(Fields::FEVER_DURATION) == 0)
    {
        std::uniform_int_distribution<> dis(0, Constants::FEVER_MAX_DURATION - Constants::FEVER_MIN_DURATION + 1);
        result = dis(gen) + Constants::FEVER_MIN_DURATION;
    }
    else if (op.compare(Fields::SYMPTOMS_DURATION) == 0)
    {
        std::uniform_int_distribution<> dis(0, Constants::SYMPTOMS_MAX_DURATION - Constants::SYMPTOMS_MIN_DURATION + 1);
        result = dis(gen) + Constants::SYMPTOMS_MIN_DURATION;
    }
    else if (op.compare(Fields::SYMPTOMS_DAYS_TO_START) == 0)
    {
        std::uniform_int_distribution<> dis(0, Constants::SYMPTOMS_MAX_DAYS_TO_START - Constants::SYMPTOMS_MIN_DAYS_TO_START + 1);
        result = dis(gen) + Constants::SYMPTOMS_MIN_DAYS_TO_START;
    }
    else if (op.compare(Fields::ABFC_PHYSICAL_DISTANCE) == 0)
    {
        std::uniform_real_distribution<> dis(0.0, 1.0);
        double aux = dis(gen);
        result = aux <= Constants::BFC_PHYSICAL_DISTANCE_1M ? 1 : aux <= Constants::BFC_PHYSICAL_DISTANCE_1M + Constants::BFC_PHYSICAL_DISTANCE_2M                                     ? 2
                                                              : aux <= Constants::BFC_PHYSICAL_DISTANCE_1M + Constants::BFC_PHYSICAL_DISTANCE_2M + Constants::BFC_PHYSICAL_DISTANCE_3M ? 3
                                                                                                                                                                                       : 0;
    }
    else if (op.compare(Fields::AAFC_PHYSICAL_DISTANCE) == 0)
    {
        std::uniform_real_distribution<> dis(0.0, 1.0);
        double aux2 = dis(gen);
        result = aux2 <= Constants::AFC_PHYSICAL_DISTANCE_1M ? 1 : aux2 <= Constants::AFC_PHYSICAL_DISTANCE_1M + Constants::AFC_PHYSICAL_DISTANCE_2M                                     ? 2
                                                               : aux2 <= Constants::AFC_PHYSICAL_DISTANCE_1M + Constants::AFC_PHYSICAL_DISTANCE_2M + Constants::AFC_PHYSICAL_DISTANCE_3M ? 3
                                                                                                                                                                                         : 0;
    }
    return new Text(std::to_string(result));
}

double AgentModel::distanceBetweenAgents(Agent *a, Agent *b)
{
    return std::sqrt(std::pow(a->getPos()->getRow() - b->getPos()->getRow(), 2) + std::pow(a->getPos()->getCol() - b->getPos()->getCol(), 2));
}

std::string AgentModel::agentName(Agent *a)
{
    return a->getName().substr(a->getName().find_last_of(' ') + 1);
}

void AgentModel::isInfectionDetected(std::vector<Agent *> agents, EasyTime *easyTime)
{
    int peopleIndex = 0;
    while (peopleIndex != agents.size())
    {
        Agent *a = agents[peopleIndex];
        if (agentCanInfectOthers(a) &&
            std::stoi((a->get(Fields::DAYS_AFTER_INFECTION))->toString()) >= std::stoi((a->get(Fields::SYMPTOMS_DAYS_TO_START))->toString()) &&
            !((a->get(Fields::INFECTION_DETECTED))->toString()).compare("true") == 0)
        {
            infectionDetected = true;
            a->set(Fields::INFECTION_DETECTED, new Text("true"));
            print("Infection detected in agent " + agentName(a), easyTime);
            isolateAgent(a);
        }
        peopleIndex++;
    }
}

void AgentModel::isolateAgent(Agent *a)
{
    // The proposal is to isolate the agent in the simulated world. For now, if the agent is isolated, he/she does not transmit to others
}

void AgentModel::infect(Agent *a, EasyTime *now)
{
    a->set(Fields::SITUATION, new Text(infected));
    a->set(Fields::DAYS_AFTER_INFECTION, new Text("0"));
    a->set(Fields::INFECTION_TIME, new Text((now->shift(23, 55))->toString()));
}

void AgentModel::infect(Agent *a, EasyTime *now, int daysAfterInfection)
{
    a->set(Fields::SITUATION, new Text(infected));
    a->set(Fields::DAYS_AFTER_INFECTION, new Text(std::to_string(daysAfterInfection)));
    a->set(Fields::INFECTION_TIME, new Text((now->shift(23, 55))->toString()));
}

void AgentModel::infectingOthers(std::vector<Agent *> agents, EasyTime *now)
{
    int peopleIndex = 0;
    while (peopleIndex != agents.size())
    {
        Agent *a = agents[peopleIndex];
        if (agentSituation(a, infected) && (std::stoi((a->get(Fields::DAYS_AFTER_INFECTION))->toString()) == Constants::TRANSMISSION_DAYS_TO_START))
        {
            a->set(Fields::SITUATION, new Text(infecting));
            print("Agent " + agentName(a) + " is infecting others", now);
        }
        peopleIndex++;
    }
}

void AgentModel::cure(std::vector<Agent *> agents, EasyTime *now)
{
    int peopleIndex = 0;
    while (peopleIndex != agents.size())
    {
        Agent *a = agents[peopleIndex];
        if (agentSituation(a, infecting) && (std::stoi((a->get(Fields::DAYS_AFTER_INFECTION))->toString()) == Constants::TRANSMISSION_DURATION + Constants::TRANSMISSION_DAYS_TO_START))
        {
            a->set(Fields::SITUATION, new Text(cured));
            print("Agent " + a->toString() + " is cured", now);
        }
        peopleIndex++;
    }
}

bool AgentModel::agentCanInfectOthers(Agent *a)
{
    return agentSituation(a, infecting);
}

bool AgentModel::agentCanBeInfected(Agent *a)
{
    return agentSituation(a, healthy);
}

bool AgentModel::agentSituation(Agent *a, std::string situation)
{
    return (a->get(Fields::SITUATION)->toString()).compare(situation) == 0;
}

void AgentModel::willTheAgentBeInfected(Agent *infected, Agent *notInfected, EasyTime *now)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

    double noseMouthChance = Constants::INFECTION_CHANCE_THROUGH_CONTACT;
    double eyeChance = Constants::INFECTION_CHANCE_THROUGH_AIR;

    //distance
    double distance = distanceBetweenAgents(infected, notInfected) * Constants::AREA_SCALE;

    if (!infectionDetected)
    {
        distance += std::stoi((notInfected->get(Fields::ABFC_PHYSICAL_DISTANCE))->toString()) * 100;
    }
    else
    {
        distance += std::stoi((notInfected->get(Fields::AAFC_PHYSICAL_DISTANCE))->toString()) * 100;
    }

    noseMouthChance -= (distance < 100 ? noseMouthChance * 0 : distance < 200 ? noseMouthChance * Constants::PHYSICAL_DISTANCE_REDUCTION_RISK_1M
                                                           : distance < 300   ? noseMouthChance * Constants::PHYSICAL_DISTANCE_REDUCTION_RISK_2M
                                                           : distance < 400   ? noseMouthChance * Constants::PHYSICAL_DISTANCE_REDUCTION_RISK_3M
                                                                              : 1.0);
    eyeChance -= (distance < 100 ? eyeChance * 0 : distance < 200 ? eyeChance * Constants::PHYSICAL_DISTANCE_REDUCTION_RISK_1M
                                               : distance < 300   ? eyeChance * Constants::PHYSICAL_DISTANCE_REDUCTION_RISK_2M
                                               : distance < 400   ? eyeChance * Constants::PHYSICAL_DISTANCE_REDUCTION_RISK_3M
                                                                  : 1.0);

    if (!infectionDetected)
    {
        //Infected n95 mask
        noseMouthChance -= ((infected->get(Fields::ABFC_USE_OF_N95_MASK))->toString()).compare("true") == 0 ? noseMouthChance * Constants::N95_MASK_REDUCTION_RISK : 0;
        //notInfected n95 mask
        noseMouthChance -= ((notInfected->get(Fields::ABFC_USE_OF_N95_MASK))->toString()).compare("true") == 0 ? noseMouthChance * Constants::N95_MASK_REDUCTION_RISK : 0;

        //Infected other mask
        noseMouthChance -= ((infected->get(Fields::ABFC_USE_OF_OTHER_MASK))->toString()).compare("true") == 0 ? noseMouthChance * Constants::OTHER_MASK_REDUCTION_RISK : 0;
        //notInfected other mask
        noseMouthChance -= ((notInfected->get(Fields::ABFC_USE_OF_OTHER_MASK))->toString()).compare("true") == 0 ? noseMouthChance * Constants::OTHER_MASK_REDUCTION_RISK : 0;

        //notInfected eye protection
        eyeChance -= ((notInfected->get(Fields::ABFC_USE_OF_EYE_PROTECTION))->toString()).compare("true") == 0 ? eyeChance * Constants::EYE_PROTECTION_REDUCTION_RISK : 0;

        //notInfected wash hands
        noseMouthChance -= ((notInfected->get(Fields::ABFC_WASH_HANDS))->toString()).compare("true") == 0 ? noseMouthChance * Constants::WASH_HANDS_REDUCTION_RISK : 0;
        eyeChance -= ((notInfected->get(Fields::ABFC_WASH_HANDS))->toString()).compare("true") == 0 ? eyeChance * Constants::WASH_HANDS_REDUCTION_RISK : 0;
    }
    else
    {
        //Infected n95 mask
        noseMouthChance -= ((infected->get(Fields::AAFC_USE_OF_N95_MASK))->toString()).compare("true") == 0 ? noseMouthChance * Constants::N95_MASK_REDUCTION_RISK : 0;
        //notInfected n95 mask
        noseMouthChance -= ((notInfected->get(Fields::AAFC_USE_OF_N95_MASK))->toString()).compare("true") == 0 ? noseMouthChance * Constants::N95_MASK_REDUCTION_RISK : 0;

        //Infected other mask
        noseMouthChance -= ((infected->get(Fields::AAFC_USE_OF_OTHER_MASK))->toString()).compare("true") == 0 ? noseMouthChance * Constants::OTHER_MASK_REDUCTION_RISK : 0;
        //notInfected other mask
        noseMouthChance -= ((notInfected->get(Fields::AAFC_USE_OF_OTHER_MASK))->toString()).compare("true") == 0 ? noseMouthChance * Constants::OTHER_MASK_REDUCTION_RISK : 0;

        //notInfected eye protection
        eyeChance -= ((notInfected->get(Fields::AAFC_USE_OF_EYE_PROTECTION))->toString()).compare("true") == 0 ? eyeChance * Constants::EYE_PROTECTION_REDUCTION_RISK : 0;

        //notInfected wash hands
        noseMouthChance -= ((notInfected->get(Fields::AAFC_WASH_HANDS))->toString()).compare("true") == 0 ? noseMouthChance * Constants::WASH_HANDS_REDUCTION_RISK : 0;
        eyeChance -= ((notInfected->get(Fields::AAFC_WASH_HANDS))->toString()).compare("true") == 0 ? eyeChance * Constants::WASH_HANDS_REDUCTION_RISK : 0;
    }

    std::uniform_real_distribution<> dis(0.0, 1.0);

    double aux = dis(gen);
    if (aux <= noseMouthChance)
    {
        infect(notInfected, now);
        print("Agent " + agentName(infected) + " infected agent " + agentName(notInfected) + " through nose/mouth", now);
    }
    else if (aux <= eyeChance)
    {
        infect(notInfected, now);
        print("Agent " + agentName(infected) + " infected agent " + agentName(notInfected) + " through eye", now);
    }
}

void AgentModel::increaseDaysAfterInfection(std::vector<Agent *> agents, EasyTime *now)
{
    int agentIndex = 0;
    while (agentIndex != agents.size())
    {
        Agent *a = agents[agentIndex];
        if (((now->toString()).compare((a->get(Fields::INFECTION_TIME))->toString()) == 0) && (agentSituation(a, infected) || agentSituation(a, infecting)))
        {
            int daysAfterInfection = std::stoi(a->get(Fields::DAYS_AFTER_INFECTION)->toString());
            a->set(Fields::DAYS_AFTER_INFECTION, new Text(std::to_string(daysAfterInfection + 1)));
        }
        agentIndex++;
    }
}

void AgentModel::print(std::string message, EasyTime *easyTime)
{
    int hour = easyTime->getHour();
    int minute = easyTime->getMinute();
    std::string result = ((hour < 10 ? " " : "") + std::to_string(hour)) + ":" + ((minute < 10 ? "0" : "") + std::to_string(minute)) + " - " + message + "\n";
    std::cout << result;
    // writeEventData(result);
}

void AgentModel::printDayInfo()
{
    std::string result = "DAY " + std::to_string(day) + " ----------------------------------------\n";
    std::cout << result;
    // writeEventData(result);
}

// void writeData(std::vector<Agent *> agents, EasyTime *easyTime)
// {
//     PrintWriter csvWriter;
//     std::string filePath = path + "/Desktop/WearableData.csv";
//     try
//     {
//         File file = new File(filePath);
//         if (!file.exists())
//         {
//             file = new File(filePath);
//         }
//         csvWriter = new PrintWriter(new FileWriter(file, true));

//         Iterator<Agent> peopleIt = agents.iterator();
//         while (peopleIt.hasNext())
//         {
//             Agent *a = peopleIt.next();
//             csvWriter.print(day + ",");
//             csvWriter.print(easyTime.tostd::string() + ",");
//             csvWriter.print(agentName(a) + ","); //id

//             csvWriter.print(std::string.valueOf(a->get(BLOODOXYGEN)).replace(',', '.') + ","); //blood oxygen
//             //csvWriter.print(a->get(BLOODPRESSURE)+","); //blood pressure
//             csvWriter.print(std::string.valueOf(a->get(BODYTEMPERATURE)).replace(',', '.') + "\r\n"); //body temperature
//         }
//         csvWriter.close();
//     }
//     catch (Exception e)
//     {
//         e.printStackTrace();
//     }
// }

// void writeDailyData(Collection<Agent> agents)
// {
//     PrintWriter csvWriter;
//     std::string filePath = "DailyData.csv";
//     try
//     {
//         File file = new File(filePath);
//         if (!file.exists())
//         {
//             file = new File(filePath);
//         }
//         csvWriter = new PrintWriter(new FileWriter(file, true));

//         int healthy = 0;
//         int infected = 0;
//         int infecting = 0;
//         int infectingAndAsymptomatic = 0;
//         int cured = 0;

//         Iterator<Agent> peopleIt = agents.iterator();
//         while (peopleIt.hasNext())
//         {
//             Agent *a = peopleIt.next();
//             healthy += agentSituation(a, this.healthy) ? 1 : 0;
//             infected += agentSituation(a, this.infected) ? 1 : 0;
//             infecting += agentSituation(a, this.infecting) ? 1 : 0;
//             infectingAndAsymptomatic += agentSituation(a, this.infecting) && !bool.valueOf(a->get(SYMPTOMS).tostd::string()) ? 1 : 0;
//             cured += agentSituation(a, this.cured) ? 1 : 0;
//         }

//         csvWriter.print(day + ",");
//         csvWriter.print((infectionDetected ? "1" : "0") + ",");
//         csvWriter.print(healthy + ",");
//         csvWriter.print(infected + ",");
//         csvWriter.print(infecting + ",");
//         csvWriter.print(infectingAndAsymptomatic + ",");
//         csvWriter.print(cured + "\r\n");
//         csvWriter.close();
//     }
//     catch (Exception e)
//     {
//         e.printStackTrace();
//     }
// }

// void writeEventData(std::string event)
// {
//     PrintWriter csvWriter;
//     std::string filePath = path + "/Desktop/EventData.csv";
//     try
//     {
//         File file = new File(filePath);
//         if (!file.exists())
//         {
//             file = new File(filePath);
//         }
//         csvWriter = new PrintWriter(new FileWriter(file, true));
//         csvWriter.print(event + "\r\n");
//         csvWriter.close();
//     }
//     catch (Exception e)
//     {
//         e.printStackTrace();
//     }
// }