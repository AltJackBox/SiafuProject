#include <office/AgentModel.h>
#include <office/Constants.h>
#include <model/World.h>
#include <model/Agent.h>
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
        }
    }

    if (lastHandleInfectionExecution.empty() || !(lastHandleInfectionExecution.compare(now->toString()) == 0))
    {

        if (now->toString().compare((new EasyTime(0, 0))->toString()) == 0)
        {
            day++;
            writeDailyData(agents);
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

    std::string string = (a->get(Fields::BODYTEMPERATURE))->toString();
    std::replace(string.begin(), string.end(), ',', '.');

    double bodytemperature = std::stod(string);
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

Text* AgentModel::boolSort(std::string op)
{

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);

    bool result = false;
    double random = dis(gen);

    if (op.compare(Fields::FEVER))
    {
        result = random < Constants::FEVER_PROBABILITY;
        return;
    }
    else if (op.compare(Fields::SYMPTOMS))
    {
        result = random < Constants::SYMPTOMS_PROBABILITY;
        return;
    }
    else if (op.compare(Fields::ABFC_USE_OF_N95_MASK))
    {
        result = random < Constants::BFC_USE_OF_N95_MASK;
        return;
    }
    else if (op.compare(Fields::AAFC_USE_OF_N95_MASK))
    {
        result = random < Constants::AFC_USE_OF_N95_MASK;
        return;
    }
    else if (op.compare(Fields::ABFC_USE_OF_OTHER_MASK))
    {
        result = random < Constants::BFC_USE_OF_OTHER_MASK;
        return;
    }
    else if (op.compare(Fields::AAFC_USE_OF_OTHER_MASK))
    {
        result = random < Constants::AFC_USE_OF_OTHER_MASK;
        return;
    }
    else if (op.compare(Fields::ABFC_USE_OF_EYE_PROTECTION))
    {
        result = random < Constants::BFC_USE_OF_EYE_PROTECTION;
        return;
    }
    else if (op.compare(Fields::AAFC_USE_OF_EYE_PROTECTION)){
        result = random < Constants::AFC_USE_OF_EYE_PROTECTION;
        return;
    }
    else if (op.compare(Fields::ABFC_WASH_HANDS)) {
        result = random < Constants::BFC_WASH_HANDS;
        return;
    }
    else if (op.compare(Fields::AAFC_WASH_HANDS)){
        result = random < Constants::AFC_WASH_HANDS;
        return;
    }
    return new Text(std::to_string(result));
}