#ifndef WORLDMODEL_H
#define WORLDMODEL_H

#include <behaviormodels/BaseWorldModel.h>
#include <types/EasyTime.h>
#include <memory>

class EasyTime;
class BoolType;
class Text;

class WorldModel : public BaseWorldModel
{

private:
    static EasyTime *WAKEUPTIME;

    static EasyTime *SLEEPTIME;

    bool dayEventsPlanned = false;

    std::shared_ptr<EasyTime> breakfastStart = nullptr;

    std::shared_ptr<EasyTime> breakfastEnd = nullptr;

    std::shared_ptr<EasyTime> lunchStart = nullptr;

    std::shared_ptr<EasyTime> lunchEnd = nullptr;

    std::shared_ptr<EasyTime> snackStart = nullptr;

    std::shared_ptr<EasyTime> snackEnd = nullptr;

    std::shared_ptr<EasyTime> dinnerStart = nullptr;

    std::shared_ptr<EasyTime> dinnerEnd = nullptr;

    void terminateGlobalMeeting();

    void organizeGlobalMeeting();

    void planDayEvents();

public:
    WorldModel(World *world) : BaseWorldModel(world) {}

    virtual ~WorldModel();

    static void removeWorldModelPointers(){
        if (WAKEUPTIME) {
            delete WAKEUPTIME;
            WAKEUPTIME = nullptr;
        }
        if (SLEEPTIME) {
            delete SLEEPTIME;
            SLEEPTIME = nullptr;
        }
    }

    void createPlaces(const std::vector<Place *> places) override;

    void doIteration(const std::vector<Place *> places);
};

#endif