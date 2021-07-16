#include <office/WorldModel.h>
#include <office/Constants.h>
#include <types/EasyTime.h>
#include <types/Text.h>
#include <types/BooleanType.h>
#include <exceptions/InfoUndefinedException.h>
#include <model/World.h>
#include <model/Agent.h>
#include <model/Place.h>
#include <Calendar.h>
#include <iostream>
#include <vector>
#include <exception>

EasyTime *WorldModel::WAKEUPTIME = new EasyTime(7, 0);

/** Sleep time. */
EasyTime *WorldModel::SLEEPTIME = new EasyTime(23, 0);

void WorldModel::terminateGlobalMeeting()
{
    int index = 0;
    std::vector<Agent *> people = world->getPeople();
    while (index != people.size())
    {
        Agent *p = people[index];
        if (((Text *)p->get(Fields::EVENT))->toString().compare("ConferenceRoomMeeting") == 0)
        {
            p->set(Fields::EVENT, new Text("GlobalMeetingEnded"));
        }
        index++;
    }
}

void WorldModel::organizeGlobalMeeting()
{
    std::vector<Place *> seats;
    try
    {
        seats = world->getPlacesOfType("RestHomeDiningRoomSeats");
    }
    catch (std::exception &e)
    {
        throw std::runtime_error("Error getting seats in World Model");
    }
    int seatsIndex = 0;
    int peopleIndex = 0;
    std::vector<Agent *> people = world->getPeople();
    int seatsLeft = seats.size();
    while (peopleIndex != people.size())
    {
        Agent *p = people[peopleIndex];
        if (seatsLeft > 0)
        {
            seatsLeft--;
            p->set(Fields::EVENT, new Text("ConferenceRoomMeeting"));
            p->set("TemporaryDestination", seats[seatsIndex]);
            seatsIndex++;
        }
        peopleIndex++;
    }
}

void WorldModel::planDayEvents()
{
    breakfastStart = new EasyTime(Constants::BREAKFAST_START);
    breakfastEnd = (new EasyTime(breakfastStart))->shift(Constants::BREAKFAST_DURATION)->blur(Constants::BREAKFAST_DURATION_BLUR);

    lunchStart = new EasyTime(Constants::LUNCH_START);
    lunchEnd = (new EasyTime(lunchStart))->shift(Constants::LUNCH_DURATION)->blur(Constants::LUNCH_DURATION_BLUR);

    snackStart = new EasyTime(Constants::SNACK_START);
    snackEnd = (new EasyTime(snackStart))->shift(Constants::SNACK_DURATION)->blur(Constants::SNACK_DURATION_BLUR);

    dinnerStart = new EasyTime(Constants::DINNER_START);
    dinnerEnd = (new EasyTime(dinnerStart))->shift(Constants::DINNER_DURATION)->blur(Constants::DINNER_DURATION_BLUR);

    dayEventsPlanned = true;
}

void WorldModel::createPlaces(const std::vector<Place *> places)
{
    for (Place *p : places)
    {
        p->set("Busy", new BooleanType(false));
    }
}

void WorldModel::doIteration(const std::vector<Place *> places)
{
    Calendar *time = world->getTime();
    EasyTime *now = new EasyTime(time->getHour(), time->getMin());

    if (now->isAfter(SLEEPTIME) && dayEventsPlanned)
    {
        dayEventsPlanned = false;
    }
    if (now->isBefore(WAKEUPTIME) && !dayEventsPlanned)
    {
        planDayEvents();
    }

    try
    {

        if (breakfastStart != nullptr && now->isAfter(breakfastStart))
        {
            breakfastStart = nullptr;
            organizeGlobalMeeting();
        }

        if (breakfastEnd != nullptr && now->isAfter(breakfastEnd))
        {
            breakfastEnd = nullptr;
            terminateGlobalMeeting();
        }

        if (lunchStart != nullptr && now->isAfter(lunchStart))
        {
            lunchStart = nullptr;
            organizeGlobalMeeting();
        }

        if (lunchEnd != nullptr && now->isAfter(lunchEnd))
        {
            lunchEnd = nullptr;
            terminateGlobalMeeting();
        }

        if (snackStart != nullptr && now->isAfter(snackStart))
        {
            snackStart = nullptr;
            organizeGlobalMeeting();
        }

        if (snackEnd != nullptr && now->isAfter(snackEnd))
        {
            snackEnd = nullptr;
            terminateGlobalMeeting();
        }

        if (dinnerStart != nullptr && now->isAfter(dinnerStart))
        {
            dinnerStart = nullptr;
            organizeGlobalMeeting();
        }

        if (dinnerEnd != nullptr && now->isAfter(dinnerEnd))
        {
            dinnerEnd = nullptr;
            terminateGlobalMeeting();
        }
    }
    catch (const InfoUndefinedException &e)
    {
        throw std::runtime_error("Person's missing information");
    }
}