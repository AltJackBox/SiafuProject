#include <office/Constants.h>

/** Time for the daily breakfast. */
const EasyTime Constants::BREAKFAST_START = new EasyTime(8, 0);

/** Average duration of breakfast. */
const EasyTime Constants::BREAKFAST_DURATION = new EasyTime(0, 30);

const EasyTime Constants::LUNCH_START = new EasyTime(12, 0);

/** Average duration of lunch. */
const EasyTime Constants::LUNCH_DURATION = new EasyTime(1, 0);

/** Time for the daily snack. */
const EasyTime Constants::SNACK_START = new EasyTime(16, 0);

/** Average duration of snack. */
const EasyTime Constants::SNACK_DURATION = new EasyTime(0, 30);

/** Time for the daily dinner. */
const EasyTime Constants::DINNER_START = new EasyTime(20, 0);

/** Average duration of dinner. */
const EasyTime Constants::DINNER_DURATION = new EasyTime(1, 0);

const EasyTime Constants::AVERAGE_WAKE_UP_TIME = new EasyTime(7, 0);

/** The average interval between toilet visits. */
const EasyTime Constants::AVERAGE_TOILET_INTERVAL = new EasyTime(4, 0);

/** Agent's gender. */
const std::string Fields::GENDER = "Gender";

/** Agent's body temperature. */
const std::string Fields::BODYTEMPERATURE = "Body temperature";

/** Agent's blood pressure. */
const std::string Fields::BLOODPRESSURE = "Blood pressure";

/** Agent's blood oxygen. */
const std::string Fields::BLOODOXYGEN = "Blood oxygen";

/** Agent's glucose level. */
//  const std::string GLUCOSE = "Glucose";

/** Whether the pacemaker is active or not. */
//  const std::string PACEMAKERACTIVE = "Pacemaker active";

/** Physical distance before and after first case */
const std::string Fields::ABFC_PHYSICAL_DISTANCE = "Physical distance before first case";

const std::string Fields::AAFC_PHYSICAL_DISTANCE = "Physical distance after first case";

/** Use of N95/PFF2 masks before and after first case */
const std::string Fields::ABFC_USE_OF_N95_MASK = "Use of N95/PFF2 mask before the first case";

const std::string Fields::AAFC_USE_OF_N95_MASK = "Use of N95/PFF2 mask after the first case";

/** Use of others masks before and after first case */
const std::string Fields::ABFC_USE_OF_OTHER_MASK = "Use of other mask before the first case";

const std::string Fields::AAFC_USE_OF_OTHER_MASK = "Use of other mask after the first case";

/** Use of eye protection masks before and after first case */
const std::string Fields::ABFC_USE_OF_EYE_PROTECTION = "Use of eye protection before the first case";

const std::string Fields::AAFC_USE_OF_EYE_PROTECTION = "Use of eye protection after the first case";

/** Washing hands before and after first case */
const std::string Fields::ABFC_WASH_HANDS = "Wash hands before the first case";

const std::string Fields::AAFC_WASH_HANDS = "Wash hands after the first case";

/** Fever */
const std::string Fields::FEVER = "Fever";

const std::string Fields::FEVER_DURATION = "Fever duration";

/** Symptoms */
const std::string Fields::SYMPTOMS = "Symptoms";

const std::string Fields::SYMPTOMS_DAYS_TO_START = "Days to start symptoms";

const std::string Fields::SYMPTOMS_DURATION = "Symptoms duration";

/** Infection */
const std::string Fields::DAYS_AFTER_INFECTION = "Days after infection";

const std::string Fields::INFECTION_TIME = "Infection time";

/** Situation */
const std::string Fields::SITUATION = "Situation"; //Healthy, Infected, Infecting, Cured

const std::string Fields::INFECTION_DETECTED = "Infection detected";

/** The agent's current activity. */
const std::string Fields::ACTIVITY = "Activity";

/** The agent's type */
const std::string Fields::TYPE = "Type";

/** The type of seat. */
const std::string Fields::SEAT = "Seat";

/** The type of desk. */
const std::string Fields::DESK = "Desk";

/** The time at which the agent wake up. */
const std::string Fields::WAKE_UP_TIME = "StartWork";

/** The time at which the agent go to sleep. */
const std::string Fields::SLEEP_TIME = "EndWork";

/** How often the agent goes to the toilet. */
const std::string Fields::TOILET_INTERVAL = "ToiletInterval";

/** The time for the next visit to the toilet. */
const std::string Fields::NEXT_TOILET_VISIT = "NextToiletVisit";

/** The toilet for which the agent is queuing. */
const std::string Fields::DESIRED_TOILET = "DesiredToilet";

/** The time at which the next event occurs. */
const std::string Fields::NEXT_EVENT_TIME = "NextEventTime";

/** The time spend in the toilet. */
const std::string Fields::TOILET_DURATION = "ToiletDuration";

/** The place where the agent is lining. */
const std::string Fields::WAITING_PLACE = "WaitingPlace";

/** The next upcoming event. */
const std::string Fields::EVENT = "Event";

/** A temporary destination. */
const std::string Fields::TEMPORARY_DESTINATION = "TemporaryDestination";

Activity::Activity(const std::string description)
{
    this->description = description;
}

std::string Activity::toString()
{
    return description;
}