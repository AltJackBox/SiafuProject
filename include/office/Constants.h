#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <types/EasyTime.h>
#include <types/Publishable.h>

class Constants
{

public:
    /** Probability of fever. */
    static const double FEVER_PROBABILITY = 0.415;

    /** Average days of the fever duration. */
    static const int FEVER_MIN_DURATION = 7;

    static const int FEVER_MAX_DURATION = 14;

    /** Probability of symptoms. */
    static const double SYMPTOMS_PROBABILITY = 0.70;

    /** Average days for symptoms to start. */
    static const int SYMPTOMS_MIN_DAYS_TO_START = 4;

    static const int SYMPTOMS_MAX_DAYS_TO_START = 6;

    /** Average days of the symptoms duration. */
    static const int SYMPTOMS_MIN_DURATION = 10;

    static const int SYMPTOMS_MAX_DURATION = 15;

    /** Days for transmission to start. */
    static const int TRANSMISSION_DAYS_TO_START = 2;

    /** Average days of the transmission duration. */
    static const int TRANSMISSION_DURATION = 14;

    /**  Reduction in risk with a physical distance of 1 m */
    static const double PHYSICAL_DISTANCE_REDUCTION_RISK_1M = 0.82;

    /**  Reduction in risk with a physical distance of 2 m */
    static const double PHYSICAL_DISTANCE_REDUCTION_RISK_2M = 0.9676;

    /**  Reduction in risk with a physical distance of 3 m */
    static const double PHYSICAL_DISTANCE_REDUCTION_RISK_3M = 0.994168;

    /**  Reduction in risk with a N95 mask */
    static const double N95_MASK_REDUCTION_RISK = 0.96;

    /**  Reduction in risk with other mask */
    static const double OTHER_MASK_REDUCTION_RISK = 0.67;

    /**  Reduction in risk with eye protection */
    static const double EYE_PROTECTION_REDUCTION_RISK = 0.78;

    /**  Reduction in risk when he/she wash hands */
    static const double WASH_HANDS_REDUCTION_RISK = 0.78;

    /**  Preventive measure of increasing physical distance in 1 meter before and after the first case */
    static const double BFC_PHYSICAL_DISTANCE_1M = 0.00;

    static const double AFC_PHYSICAL_DISTANCE_1M = 0.50;

    /**  Preventive measure of increasing physical distance in 2 meters before and after the first case */
    static const double BFC_PHYSICAL_DISTANCE_2M = 0.00;

    static const double AFC_PHYSICAL_DISTANCE_2M = 0.50;

    /**  Preventive measure of increasing physical distance in 3 meters before and after the first case */
    static const double BFC_PHYSICAL_DISTANCE_3M = 0.00;

    static const double AFC_PHYSICAL_DISTANCE_3M = 0.00;

    /**  Preventive measure of using others masks before and after the first case */
    static const double BFC_USE_OF_OTHER_MASK = 0.50;

    static const double AFC_USE_OF_OTHER_MASK = 0.00;

    /**  Preventive measure of using N95/PFF2 masks before and after the first case */
    static const double BFC_USE_OF_N95_MASK = 0.00;

    static const double AFC_USE_OF_N95_MASK = 1.00;

    /**  Preventive measure of using eye protection before and after the first case */
    static const double BFC_USE_OF_EYE_PROTECTION = 0.00;

    static const double AFC_USE_OF_EYE_PROTECTION = 0.90;

    /**  Preventive measure of washing hands before and after the first case */
    static const double BFC_WASH_HANDS = 0.00;

    static const double AFC_WASH_HANDS = 0.00;

    /** Infection chance through contact */
    static const double INFECTION_CHANCE_THROUGH_CONTACT = 0.0040;

    /** Infection chance through air */
    static const double INFECTION_CHANCE_THROUGH_AIR = INFECTION_CHANCE_THROUGH_CONTACT / 4;

    /** Scale to real world */
    static const double AREA_SCALE = 2.5;

    /** Time for the daily breakfast. */
    static EasyTime *BREAKFAST_START;

    /** Average duration of breakfast. */
    static EasyTime *BREAKFAST_DURATION;

    /** Blur of the breakfast duration. */
    static const int BREAKFAST_DURATION_BLUR = 10;

    /** Time for the daily lunch. */
    static EasyTime *LUNCH_START;

    /** Average duration of lunch. */
    static EasyTime *LUNCH_DURATION;

    /** Blur of the lunch duration. */
    static const int LUNCH_DURATION_BLUR = 20;

    /** Time for the daily snack. */
    static  EasyTime *SNACK_START;

    /** Average duration of snack. */
    static  EasyTime *SNACK_DURATION;

    /** Blur of the snack duration. */
    static const int SNACK_DURATION_BLUR = 10;

    /** Time for the daily dinner. */
    static  EasyTime *DINNER_START;

    /** Average duration of dinner. */
    static  EasyTime *DINNER_DURATION;

    /** Blur of the dinner duration. */
    static const int DINNER_DURATION_BLUR = 20;

    /** Wander radius when lining for something. */
    static const int INLINE_WANDER = 10;

    /** Average retry time when the toilet line is too long. */
    static const int TOILET_RETRY_BLUR = 90;

    /** Maximum waiting time when in line. */
    static const int MAX_WAIT_TIME = 90;

    /** Name says all. */
    static const int TOILET_VISIT_DURATION = 20;

    /** Default agent speed. */
    static const int DEFAULT_SPEED = 6;

    /** Amount of people. */
    static const int POPULATION = 18;

    /** Agents go to the toilet every TOILET_INTERVAL plus minus some 180 min. */
    static const int TOILET_BLUR = 180;

    /** Blur in minutes from the average sleep time. */
    static const int SLEEP_END_BLUR = 30;

    /** Average amount of awake hours. */
    static const int AVERAGE_WAKE_HOURS = 15;

    /** Agents wake up 30min around the default time. */
    static const int WAKE_UP_START_BLUR = 30;

    /** The average time at which people wake up. */
    static const EasyTime *AVERAGE_WAKE_UP_TIME;

    /** The average interval between toilet visits. */
    static const EasyTime *AVERAGE_TOILET_INTERVAL;
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

/**
	 * List of possible activities. This is implemented as an enum because it
	 * helps us in switch statements. Like the rest of the constants in this
	 * class, they could also have been coded directly in the model
	 */
class Activity : public Publishable
{
    /** Human readable desription of the activity. */
private:
    std::string description;
    /**
		 * Get the description of the activity.
		 * 
		 * @return a std::string describing the activity
		 */

    Activity(const std::string description)
    {
        this->description = description;
    }

public:
    enum Act
    {
        RESTING,
        LEAVING_WORK,
        IN_TOILET,
        GOING_2_TOILET,
        GOING_2_DESK,
        GOING_2_GLOBAL_LUNCH,
        AT_DESK,
        ENTERING_TOILET,
        AT_LUNCH,
        ENTERING_LUNCH
    };

    std::string toString()
    {
        return description;
    }
};

#endif
