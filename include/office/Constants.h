#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <types/EasyTime.h>
#include <types/Publishable.h>
#include <vector>
#include <map>

class Constants
{

public:
    /** Probability of fever. */
    static constexpr double FEVER_PROBABILITY = 0.415;

    /** Average days of the fever duration. */
    static constexpr int FEVER_MIN_DURATION = 7;

    static constexpr int FEVER_MAX_DURATION = 14;

    /** Probability of symptoms. */
    static constexpr double SYMPTOMS_PROBABILITY = 0.70;

    /** Average days for symptoms to start. */
    static constexpr int SYMPTOMS_MIN_DAYS_TO_START = 4;

    static constexpr int SYMPTOMS_MAX_DAYS_TO_START = 6;

    /** Average days of the symptoms duration. */
    static constexpr int SYMPTOMS_MIN_DURATION = 10;

    static constexpr int SYMPTOMS_MAX_DURATION = 15;

    /** Days for transmission to start. */
    static constexpr int TRANSMISSION_DAYS_TO_START = 2;

    /** Average days of the transmission duration. */
    static constexpr int TRANSMISSION_DURATION = 14;

    /**  Reduction in risk with a physical distance of 1 m */
    static constexpr double PHYSICAL_DISTANCE_REDUCTION_RISK_1M = 0.82;

    /**  Reduction in risk with a physical distance of 2 m */
    static constexpr double PHYSICAL_DISTANCE_REDUCTION_RISK_2M = 0.9676;

    /**  Reduction in risk with a physical distance of 3 m */
    static constexpr double PHYSICAL_DISTANCE_REDUCTION_RISK_3M = 0.994168;

    /**  Reduction in risk with a N95 mask */
    static constexpr double N95_MASK_REDUCTION_RISK = 0.96;

    /**  Reduction in risk with other mask */
    static constexpr double OTHER_MASK_REDUCTION_RISK = 0.67;

    /**  Reduction in risk with eye protection */
    static constexpr double EYE_PROTECTION_REDUCTION_RISK = 0.78;

    /**  Reduction in risk when he/she wash hands */
    static constexpr double WASH_HANDS_REDUCTION_RISK = 0.78;

    /**  Preventive measure of increasing physical distance in 1 meter before and after the first case */
    static constexpr double BFC_PHYSICAL_DISTANCE_1M = 0.00;

    static constexpr double AFC_PHYSICAL_DISTANCE_1M = 0.50;

    /**  Preventive measure of increasing physical distance in 2 meters before and after the first case */
    static constexpr double BFC_PHYSICAL_DISTANCE_2M = 0.00;

    static constexpr double AFC_PHYSICAL_DISTANCE_2M = 0.50;

    /**  Preventive measure of increasing physical distance in 3 meters before and after the first case */
    static constexpr double BFC_PHYSICAL_DISTANCE_3M = 0.00;

    static constexpr double AFC_PHYSICAL_DISTANCE_3M = 0.00;

    /**  Preventive measure of using others masks before and after the first case */
    static constexpr double BFC_USE_OF_OTHER_MASK = 0.50;

    static constexpr double AFC_USE_OF_OTHER_MASK = 0.00;

    /**  Preventive measure of using N95/PFF2 masks before and after the first case */
    static constexpr double BFC_USE_OF_N95_MASK = 0.00;

    static constexpr double AFC_USE_OF_N95_MASK = 1.00;

    /**  Preventive measure of using eye protection before and after the first case */
    static constexpr double BFC_USE_OF_EYE_PROTECTION = 0.00;

    static constexpr double AFC_USE_OF_EYE_PROTECTION = 0.90;

    /**  Preventive measure of washing hands before and after the first case */
    static constexpr double BFC_WASH_HANDS = 0.00;

    static constexpr double AFC_WASH_HANDS = 0.00;

    /** Infection chance through contact */
    static constexpr double INFECTION_CHANCE_THROUGH_CONTACT = 0.0040;

    /** Infection chance through air */
    static constexpr double INFECTION_CHANCE_THROUGH_AIR = INFECTION_CHANCE_THROUGH_CONTACT / 4;

    /** Scale to real world */
    static constexpr double AREA_SCALE = 2.5;

    /** Time for the daily breakfast. */
    static EasyTime *BREAKFAST_START;

    /** Average duration of breakfast. */
    static EasyTime *BREAKFAST_DURATION;

    /** Blur of the breakfast duration. */
    static constexpr int BREAKFAST_DURATION_BLUR = 10;

    /** Time for the daily lunch. */
    static EasyTime *LUNCH_START;

    /** Average duration of lunch. */
    static EasyTime *LUNCH_DURATION;

    /** Blur of the lunch duration. */
    static constexpr int LUNCH_DURATION_BLUR = 20;

    /** Time for the daily snack. */
    static EasyTime *SNACK_START;

    /** Average duration of snack. */
    static EasyTime *SNACK_DURATION;

    /** Blur of the snack duration. */
    static constexpr int SNACK_DURATION_BLUR = 10;

    /** Time for the daily dinner. */
    static EasyTime *DINNER_START;

    /** Average duration of dinner. */
    static EasyTime *DINNER_DURATION;

    /** Blur of the dinner duration. */
    static constexpr int DINNER_DURATION_BLUR = 20;

    /** Wander radius when lining for something. */
    static constexpr int INLINE_WANDER = 10;

    /** Average retry time when the toilet line is too long. */
    static constexpr int TOILET_RETRY_BLUR = 90;

    /** Maximum waiting time when in line. */
    static constexpr int MAX_WAIT_TIME = 90;

    /** Name says all. */
    static constexpr int TOILET_VISIT_DURATION = 20;

    /** Default agent speed. */
    static constexpr int DEFAULT_SPEED = 6;

    /** Amount of people. */
    static constexpr int POPULATION = 18;

    /** Agents go to the toilet every TOILET_INTERVAL plus minus some 180 min. */
    static constexpr int TOILET_BLUR = 180;

    /** Blur in minutes from the average sleep time. */
    static constexpr int SLEEP_END_BLUR = 30;

    /** Average amount of awake hours. */
    static constexpr int AVERAGE_WAKE_HOURS = 15;

    /** Agents wake up 30min around the default time. */
    static constexpr int WAKE_UP_START_BLUR = 30;

    /** The average time at which people wake up. */
    static EasyTime *AVERAGE_WAKE_UP_TIME;

    /** The average interval between toilet visits. */
    static EasyTime *AVERAGE_TOILET_INTERVAL;

    static void removeConstantsPointers()
    {
        if (BREAKFAST_START)
        {
            delete BREAKFAST_START;
            BREAKFAST_START = nullptr;
        }
        if (BREAKFAST_DURATION)
        {
            delete BREAKFAST_DURATION;
            BREAKFAST_DURATION = nullptr;
        }
        if (LUNCH_START)
        {
            delete LUNCH_START;
            LUNCH_START = nullptr;
        }
        if (LUNCH_DURATION)
        {
            delete LUNCH_DURATION;
            LUNCH_DURATION = nullptr;
        }
        if (SNACK_START)
        {
            delete SNACK_START;
            SNACK_START = nullptr;
        }
        if (SNACK_DURATION)
        {
            delete SNACK_DURATION;
            SNACK_DURATION = nullptr;
        }
        if (DINNER_START)
        {
            delete DINNER_START;
            DINNER_START = nullptr;
        }
        if (DINNER_DURATION)
        {
            delete DINNER_DURATION;
            DINNER_DURATION = nullptr;
        }
        if (AVERAGE_WAKE_UP_TIME)
        {
            delete AVERAGE_WAKE_UP_TIME;
            AVERAGE_WAKE_UP_TIME = nullptr;
        }
        if (AVERAGE_TOILET_INTERVAL)
        {
            delete AVERAGE_TOILET_INTERVAL;
            AVERAGE_TOILET_INTERVAL = nullptr;
        }
    }
};

/**
	 * The names of the fields in each agent object.
	 */
class Fields
{

public:
    /** Agent's gender. */
    static std::string GENDER;

    /** Agent's body temperature. */
    static std::string BODYTEMPERATURE;

    /** Agent's blood pressure. */
    static std::string BLOODPRESSURE;

    /** Agent's blood oxygen. */
    static std::string BLOODOXYGEN;

    /** Agent's glucose level. */
    // static  std::string GLUCOSE = "Glucose";

    /** Whether the pacemaker is active or not. */
    // static  std::string PACEMAKERACTIVE = "Pacemaker active";

    /** Physical distance before and after first case */
    static std::string ABFC_PHYSICAL_DISTANCE;

    static std::string AAFC_PHYSICAL_DISTANCE;

    /** Use of N95/PFF2 masks before and after first case */
    static std::string ABFC_USE_OF_N95_MASK;

    static std::string AAFC_USE_OF_N95_MASK;

    /** Use of others masks before and after first case */
    static std::string ABFC_USE_OF_OTHER_MASK;

    static std::string AAFC_USE_OF_OTHER_MASK;

    /** Use of eye protection masks before and after first case */
    static std::string ABFC_USE_OF_EYE_PROTECTION;

    static std::string AAFC_USE_OF_EYE_PROTECTION;

    /** Washing hands before and after first case */
    static std::string ABFC_WASH_HANDS;

    static std::string AAFC_WASH_HANDS;

    /** Fever */
    static std::string FEVER;

    static std::string FEVER_DURATION;

    /** Symptoms */
    static std::string SYMPTOMS;

    static std::string SYMPTOMS_DAYS_TO_START;

    static std::string SYMPTOMS_DURATION;

    /** Infection */
    static std::string DAYS_AFTER_INFECTION;

    static std::string INFECTION_TIME;

    /** Situation */
    static std::string SITUATION; //Healthy, Infected, Infecting, Cured

    static std::string INFECTION_DETECTED;

    /** The agent's current activity. */
    static std::string ACTIVITY;

    /** The agent's type */
    static std::string TYPE;

    /** The type of seat. */
    static std::string SEAT;

    /** The type of desk. */
    static std::string DESK;

    /** The time at which the agent wake up. */
    static std::string WAKE_UP_TIME;

    /** The time at which the agent go to sleep. */
    static std::string SLEEP_TIME;

    /** How often the agent goes to the toilet. */
    static std::string TOILET_INTERVAL;

    /** The time for the next visit to the toilet. */
    static std::string NEXT_TOILET_VISIT;

    /** The toilet for which the agent is queuing. */
    static std::string DESIRED_TOILET;

    /** The time at which the next event occurs. */
    static std::string NEXT_EVENT_TIME;

    /** The time spend in the toilet. */
    static std::string TOILET_DURATION;

    /** The place where the agent is lining. */
    static std::string WAITING_PLACE;

    /** The next upcoming event. */
    static std::string EVENT;

    /** A temporary destination. */
    static std::string TEMPORARY_DESTINATION;
};

class Activity : public Publishable
{
private:
    std::string description;

public:
    Activity(const std::string description);

    ~Activity() {}

    std::string toString();
};

class ActivityManager
{

private:
    static std::map<std::string, Activity *> Activities;

public:
    static Activity *RESTING;
    static Activity *LEAVING_WORK;
    static Activity *IN_TOILET;
    static Activity *GOING_2_TOILET;
    static Activity *GOING_2_DESK;
    static Activity *GOING_2_GLOBAL_LUNCH;
    static Activity *AT_DESK;
    static Activity *ENTERING_TOILET;
    static Activity *AT_LUNCH;
    static Activity *ENTERING_LUNCH;

    static Publishable *getActivity(std::string description)
    {
        return Activities.at(description);
    }

    static void removeFieldsPointers()
    {
        for (std::pair<const std::string, Activity *> &act : Activities)
        {
            if (act.second) {
                delete act.second;
                act.second = nullptr;
            }
        }
    }
};

#endif
