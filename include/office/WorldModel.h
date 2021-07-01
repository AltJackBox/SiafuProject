#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <behaviormodels/BaseWorldModel.h>

class EasyTime;
class BoolType;
class Text;

class WorldModel : public BaseWorldModel
{

private:
    static EasyTime *WAKEUPTIME;

    static EasyTime *SLEEPTIME;

    bool dayEventsPlanned = false;

    EasyTime *breakfastStart;

    EasyTime *breakfastEnd;

    EasyTime *lunchStart;

    EasyTime *lunchEnd;

    EasyTime *snackStart;

    EasyTime *snackEnd;

    EasyTime *dinnerStart;

    EasyTime *dinnerEnd;

    void terminateGlobalMeeting();

    void organizeGlobalMeeting();

    void planDayEvents();

public:
    WorldModel(World *world) : BaseWorldModel(world) {}

    void createPlaces(const std::vector<Place *> places) override;

    void doIteration(const std::vector<Place *> places);
};

#endif