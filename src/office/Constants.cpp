#include <office/Constants.h>

/** Time for the daily breakfast. */
EasyTime *Constants::BREAKFAST_START = new EasyTime(8, 0);

/** Average duration of breakfast. */
EasyTime *Constants::BREAKFAST_DURATION = new EasyTime(0, 30);

EasyTime *Constants::LUNCH_START = new EasyTime(12, 0);

/** Average duration of lunch. */
EasyTime *Constants::LUNCH_DURATION = new EasyTime(1, 0);

/** Time for the daily snack. */
EasyTime *Constants::SNACK_START = new EasyTime(16, 0);

/** Average duration of snack. */
EasyTime *Constants::SNACK_DURATION = new EasyTime(0, 30);

/** Time for the daily dinner. */
EasyTime *Constants::DINNER_START = new EasyTime(20, 0);

/** Average duration of dinner. */
EasyTime *Constants::DINNER_DURATION = new EasyTime(1, 0);

EasyTime *Constants::AVERAGE_WAKE_UP_TIME = new EasyTime(7, 0);

/** The average interval between toilet visits. */
EasyTime *Constants::AVERAGE_TOILET_INTERVAL = new EasyTime(4, 0);

/** Agent's gender. */
std::string Fields::GENDER = "Gender";

/** Agent's body temperature. */
std::string Fields::BODYTEMPERATURE = "Body temperature";

/** Agent's blood pressure. */
std::string Fields::BLOODPRESSURE = "Blood pressure";

/** Agent's blood oxygen. */
std::string Fields::BLOODOXYGEN = "Blood oxygen";

/** Agent's glucose level. */
//  const std::string GLUCOSE = "Glucose";

/** Whether the pacemaker is active or not. */
//  const std::string PACEMAKERACTIVE = "Pacemaker active";

/** Physical distance before and after first case */
std::string Fields::ABFC_PHYSICAL_DISTANCE = "Physical distance before first case";

std::string Fields::AAFC_PHYSICAL_DISTANCE = "Physical distance after first case";

/** Use of N95/PFF2 masks before and after first case */
std::string Fields::ABFC_USE_OF_N95_MASK = "Use of N95/PFF2 mask before the first case";

std::string Fields::AAFC_USE_OF_N95_MASK = "Use of N95/PFF2 mask after the first case";

/** Use of others masks before and after first case */
std::string Fields::ABFC_USE_OF_OTHER_MASK = "Use of other mask before the first case";

std::string Fields::AAFC_USE_OF_OTHER_MASK = "Use of other mask after the first case";

/** Use of eye protection masks before and after first case */
std::string Fields::ABFC_USE_OF_EYE_PROTECTION = "Use of eye protection before the first case";

std::string Fields::AAFC_USE_OF_EYE_PROTECTION = "Use of eye protection after the first case";

/** Washing hands before and after first case */
std::string Fields::ABFC_WASH_HANDS = "Wash hands before the first case";

std::string Fields::AAFC_WASH_HANDS = "Wash hands after the first case";

/** Fever */
std::string Fields::FEVER = "Fever";

std::string Fields::FEVER_DURATION = "Fever duration";

/** Symptoms */
std::string Fields::SYMPTOMS = "Symptoms";

std::string Fields::SYMPTOMS_DAYS_TO_START = "Days to start symptoms";

std::string Fields::SYMPTOMS_DURATION = "Symptoms duration";

/** Infection */
std::string Fields::DAYS_AFTER_INFECTION = "Days after infection";

std::string Fields::INFECTION_TIME = "Infection time";

/** Situation */
std::string Fields::SITUATION = "Situation"; //Healthy, Infected, Infecting, Cured

std::string Fields::INFECTION_DETECTED = "Infection detected";

/** The agent's current activity. */
std::string Fields::ACTIVITY = "Activity";

/** The agent's type */
std::string Fields::TYPE = "Type";

/** The type of seat. */
std::string Fields::SEAT = "Seat";

/** The type of desk. */
std::string Fields::DESK = "Desk";

/** The time at which the agent wake up. */
std::string Fields::WAKE_UP_TIME = "StartWork";

/** The time at which the agent go to sleep. */
std::string Fields::SLEEP_TIME = "EndWork";

/** How often the agent goes to the toilet. */
std::string Fields::TOILET_INTERVAL = "ToiletInterval";

/** The time for the next visit to the toilet. */
std::string Fields::NEXT_TOILET_VISIT = "NextToiletVisit";

/** The toilet for which the agent is queuing. */
std::string Fields::DESIRED_TOILET = "DesiredToilet";

/** The time at which the next event occurs. */
std::string Fields::NEXT_EVENT_TIME = "NextEventTime";

/** The time spend in the toilet. */
std::string Fields::TOILET_DURATION = "ToiletDuration";

/** The place where the agent is lining. */
std::string Fields::WAITING_PLACE = "WaitingPlace";

/** The next upcoming event. */
std::string Fields::EVENT = "Event";

/** A temporary destination. */
std::string Fields::TEMPORARY_DESTINATION = "TemporaryDestination";

Activity::Activity(const std::string description)
{
    this->description = description;
}

std::string Activity::toString()
{
    return description;
}

Activity *ActivityManager::RESTING = new Activity("Resting");
Activity *ActivityManager::LEAVING_WORK = new Activity("LeavingWork");
Activity *ActivityManager::IN_TOILET = new Activity("InToilet");
Activity *ActivityManager::GOING_2_TOILET = new Activity("Going2Toilet");
Activity *ActivityManager::GOING_2_DESK = new Activity("Going2Desk");
Activity *ActivityManager::GOING_2_GLOBAL_LUNCH = new Activity("Going2GlobalLunch");
Activity *ActivityManager::AT_DESK = new Activity("AtDesk");
Activity *ActivityManager::ENTERING_TOILET = new Activity("EnteringToilet");
Activity *ActivityManager::AT_LUNCH = new Activity("AtLunch");
Activity *ActivityManager::ENTERING_LUNCH = new Activity("EnteringLunch");

std::map<std::string, Activity *> ActivityManager::Activities = {{"Resting", RESTING}, {"LEAVING_WORK", LEAVING_WORK}, {"IN_TOILET", IN_TOILET}, {"GOING_2_TOILET", GOING_2_TOILET}, {"GOING_2_DESK", GOING_2_DESK}, {"GOING_2_GLOBAL_LUNCH", GOING_2_GLOBAL_LUNCH}, {"AT_DESK", AT_DESK}, {"ENTERING_TOILET", ENTERING_TOILET}, {"AT_LUNCH", AT_LUNCH}, {"ENTERING_TOILET", ENTERING_TOILET}};
