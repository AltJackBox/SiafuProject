#ifndef AGENTMODEL_H
#define AGENTMODEL_H

#include <behaviormodels/BaseAgentModel.h>
#include <string>

class Place;
class World;


class AgentModel : public BaseAgentModel
{

private:
    std::string lastHandleInfectionExecution;
    std::string path = System.getProperty("user.home");

    std::string healthy = "Healthy";
    std::string infected = "Infected";
    std::string infecting = "Infecting";
    std::string cured = "Cured";

    bool infectionDetected = false;
    int day = 1;

    /** The door to the places. */
    Place* restHomeDoor;
    // Place apartmentOneDoor;
    // Place apartmentTwoDoor;
    Place* apartmentThreeDoor;
    Place* houseDoor;

    /**
	 * Instantiates this agent model.
	 * 
	 * @param world the simulation's world
	 */
public:
    AgentModel(const World* world)
    {
        super(world);
        try
        {
            restHomeDoor = world.getPlacesOfType("RestHomeEntrance").iterator().next();
            //apartmentOneDoor = world.getPlacesOfType("ApartmentOneEntrance").iterator().next();
            //apartmentTwoDoor = world.getPlacesOfType("ApartmentTwoEntrance").iterator().next();
            //apartmentThreeDoor = world.getPlacesOfType("ApartmentThreeEntrance").iterator().next();
            //houseDoor = world.getPlacesOfType("HouseEntrance").iterator().next();
        }
        catch (PlaceTypeUndefinedException e)
        {
            throw new RuntimeException("One or more doors are undefined", e);
        }
    }

    /**
	 * Create the agents for the simulation. 
	 * 
	 * @return the created agents.
	 */
    @Override public ArrayList<Agent> createAgents()
    {
        ArrayList<Agent> people = new ArrayList<Agent>(POPULATION);
        createWorker(people, "RestHomeResident", "RestHomeBeds", "RestHomeSeats");
        //createWorker(people, "Student", "StudentDesk");
        return people;
    }

    /**
	 * This method creates all the people for the simulation.
	 * 
	 * @param people the array where you need to put your created people
	 * @param type the type of person
	 * @param bedLocation the location of bed 
	 * @param seatLocation the location of seat
	 */
private
    void createWorker(final ArrayList<Agent> people, final std::string type, final std::string bedLocation, final std::string seatLocation)
    {
        Iterator<Place> bedIt;
        Iterator<Place> seatIt;
        try
        {
            bedIt = world.getPlacesOfType(bedLocation).iterator();
            seatIt = world.getPlacesOfType(seatLocation).iterator();
        }
        catch (PlaceTypeUndefinedException e)
        {
            throw new RuntimeException("No beds or seats defined", e);
        }

        int i = 0;
        while (bedIt.hasNext() && seatIt.hasNext())
        {
            Place desk = bedIt.next();
            Place seat = seatIt.next();

            Agent a = new Agent(type + " - " + (i + 1), desk.getPos(), "HumanBlue", world);
            a.setVisible(true);
            EasyTime wakeUpTime = new EasyTime(AVERAGE_WAKE_UP_TIME).blur(WAKE_UP_START_BLUR);
            EasyTime sleepTime = new EasyTime(wakeUpTime).shift(AVERAGE_WAKE_HOURS, 0).blur(SLEEP_END_BLUR);
            EasyTime toiletInterval = new EasyTime(AVERAGE_TOILET_INTERVAL).blur(TOILET_BLUR);

            a.set(TYPE, new Text(type));
            a.set(SEAT, seat);
            a.set(DESK, desk);
            a.set(WAKE_UP_TIME, wakeUpTime);
            a.set(SLEEP_TIME, sleepTime);
            a.set(ACTIVITY, Activity.LEAVING_WORK);
            a.set(TOILET_INTERVAL, toiletInterval);
            a.set(NEXT_TOILET_VISIT, new EasyTime(wakeUpTime).shift(toiletInterval));
            a.set(DESIRED_TOILET, new Text("None"));
            a.set(NEXT_EVENT_TIME, new Text("None"));
            a.set(TOILET_DURATION, new Text("None"));
            a.set(WAITING_PLACE, new Text("None"));
            a.set(EVENT, new Text("None"));
            a.set(TEMPORARY_DESTINATION, new Text("None"));

            a.set(BODYTEMPERATURE, new Text("36.5"));   // ºC
            a.set(BLOODPRESSURE, new Text("120 / 80")); // mmHg / mmHg
            a.set(BLOODOXYGEN, new Text("95.3"));       // %
            //a.set(GLUCOSE, new Text("90.1")); // mg/dL
            //a.set(PACEMAKERACTIVE, new Text("0"));

            a.set(FEVER, boolSort(FEVER));
            a.set(FEVER_DURATION, intSort(FEVER_DURATION));

            a.set(SYMPTOMS, boolSort(SYMPTOMS));
            a.set(SYMPTOMS_DURATION, intSort(SYMPTOMS_DURATION));
            a.set(SYMPTOMS_DAYS_TO_START, intSort(SYMPTOMS_DAYS_TO_START));

            a.set(ABFC_USE_OF_N95_MASK, boolSort(ABFC_USE_OF_N95_MASK));
            a.set(AAFC_USE_OF_N95_MASK, boolSort(AAFC_USE_OF_N95_MASK));

            a.set(ABFC_USE_OF_OTHER_MASK, boolSort(ABFC_USE_OF_OTHER_MASK));
            a.set(AAFC_USE_OF_OTHER_MASK, boolSort(AAFC_USE_OF_OTHER_MASK));

            a.set(ABFC_USE_OF_EYE_PROTECTION, boolSort(ABFC_USE_OF_EYE_PROTECTION));
            a.set(AAFC_USE_OF_EYE_PROTECTION, boolSort(AAFC_USE_OF_EYE_PROTECTION));

            a.set(ABFC_WASH_HANDS, boolSort(ABFC_WASH_HANDS));
            a.set(AAFC_WASH_HANDS, boolSort(AAFC_WASH_HANDS));

            a.set(ABFC_PHYSICAL_DISTANCE, intSort(ABFC_PHYSICAL_DISTANCE));
            a.set(AAFC_PHYSICAL_DISTANCE, intSort(AAFC_PHYSICAL_DISTANCE));

            a.set(SITUATION, new Text(healthy));
            a.set(INFECTION_DETECTED, new Text(std::string.valueOf(false)));
            a.set(DAYS_AFTER_INFECTION, new Text(std::string.valueOf(0)));
            a.set(INFECTION_TIME, new Text(std::string.valueOf("")));

            a.setSpeed(DEFAULT_SPEED);
            people.add(a);
            i++;
        }
    }

    /**
	 * Handle the agents by checking if they need to respond to an event, go
	 * to the toilet or go/come home.
	 * 
	 * @param agents the people in the simulation
	 */
    @Override public void doIteration(final Collection<Agent> agents)
    {
        Calendar time = world.getTime();
        EasyTime now = new EasyTime(time.get(Calendar.HOUR_OF_DAY), time.get(Calendar.MINUTE));

        handleInfection(agents, now);

        Iterator<Agent> peopleIt = agents.iterator();
        while (peopleIt.hasNext())
        {
            Agent a = peopleIt.next();
            handlePerson(a, now);
            handlePersonBodySensors(a);
        }
    }

    /**
	 * Handle the people in the simulation.
	 * 
	 * @param agents the agents to handle
	 * @param now the current time
	 */
private
    void handleInfection(Collection<Agent> agents, EasyTime now)
    {

        if (lastHandleInfectionExecution == null)
        {
            printDayInfo();
            Iterator<Agent> peopleIt = agents.iterator();
            while (peopleIt.hasNext())
            {
                Agent a = peopleIt.next();
                if (agentName(a).equals("2"))
                {
                    print("Agent 2 is infected", now);
                    infect(a, now, -1);
                }
            }
        }

        if (lastHandleInfectionExecution == null || !lastHandleInfectionExecution.equals(now.tostd::string()))
        {

            if (now.tostd::string().equals(new EasyTime(0, 0).tostd::string()))
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

            Agent[] aa = agents.toArray(new Agent[agents.size()]);
            for (int i = 0; i < aa.length; i++)
            {
                for (int j = i + 1; j < aa.length; j++)
                {
                    if (agentCanInfectOthers(aa[i]) && agentCanBeInfected(aa[j]))
                    {
                        willTheAgentBeInfected(aa[i], aa[j], now);
                    }
                    else if (agentCanInfectOthers(aa[j]) && agentCanBeInfected(aa[i]))
                    {
                        willTheAgentBeInfected(aa[j], aa[i], now);
                    }
                }
            }
            lastHandleInfectionExecution = now.tostd::string();
        }
    }

    /**
	 * Handle the body sensors in the simulation.
	 * 
	 * @param a the agent to handle
	 */
private
    void handlePersonBodySensors(final Agent a)
    {

        //The studied medical model that was proposed by health professionals must be developed.
        //Health values must be changed following the proposed standards.
        //Remember that asymptomatics have no significant changes.
        //Remember the probability of fever and others.

        Random rand = new Random();

        double bloodOxygen = Double.parseDouble(a.get(BLOODOXYGEN).tostd::string().replace(',', '.'));
        bloodOxygen = bloodOxygen < 95 ? bloodOxygen + rand.nextDouble() : bloodOxygen - rand.nextDouble();
        a.set(BLOODOXYGEN, new Text(std::string.format("%.2f", bloodOxygen)));

        double bodytemperature = Double.parseDouble(a.get(BODYTEMPERATURE).tostd::string().replace(',', '.'));
        bodytemperature = bodytemperature < 36.5 ? bodytemperature + rand.nextDouble() : bodytemperature - rand.nextDouble();
        a.set(BODYTEMPERATURE, new Text(std::string.format("%.2f", bodytemperature)));

        //double glucose = Double.parseDouble(a.get(GLUCOSE).tostd::string().replace(',', '.'));
        //glucose = glucose < 95 ? glucose + rand.nextDouble() : glucose - rand.nextDouble();
        //a.set(GLUCOSE, new Text(std::string.format("%.2f",glucose)));
    }

    /**
	 * Handle the people in the simulation.
	 * 
	 * @param a the agent to handle
	 * @param now the current time
	 */
private
    void handlePerson(final Agent a, final EasyTime now)
    {
        if (!a.isOnAuto())
        {
            return; // This guy's being managed by the user interface
        }
        try
        {
            switch ((Activity)a.get(ACTIVITY))
            {
            case RESTING:
                if (now.isAfter((EasyTime)a.get(WAKE_UP_TIME)) && now.isBefore((EasyTime)a.get(SLEEP_TIME)))
                {
                    goToDesk(a);
                    a.set(NEXT_TOILET_VISIT, new EasyTime(((EasyTime)a.get(WAKE_UP_TIME))).shift((EasyTime)a.get(TOILET_INTERVAL)));
                }
                break;
            case LEAVING_WORK:
                if (a.isAtDestination())
                {
                    goToSleep(a);
                }
                break;
            case GOING_2_DESK:
                if (a.isAtDestination())
                {
                    beAtDesk(a);
                }
                break;
            case GOING_2_TOILET:
                if (a.isAtDestination())
                {
                    lineInToilet(a, now);
                }
                break;
            case GOING_2_GLOBAL_LUNCH:
                if (a.isAtDestination())
                {
                    beAtGlobalMeeting(a);
                }
                break;
            case AT_DESK:
                //a.wanderAround((Place) (a.get(WAITING_PLACE)), INLINE_WANDER);
                if (now.isAfter((EasyTime)a.get(SLEEP_TIME)) || now.isIn(new TimePeriod(new EasyTime(0, 0), (EasyTime)a.get(WAKE_UP_TIME))))
                {
                    goHome(a);
                }
                handleEvent(a);
                if (isTimeForToilet(a, now))
                {
                    goToToilet(a);
                }
                break;
            case ENTERING_TOILET:
                if (a.isAtDestination())
                {
                    arriveAtToilet(a, now);
                }
                break;

            case IN_TOILET:
                beAtToilet(a, now);
                break;
            default:
                throw new RuntimeException("Unknown Activity");
            }
        }
        catch (InfoUndefinedException e)
        {
            throw new RuntimeException("Unknown info requested for " + a, e);
        }
    }

    /**
	 * Make the agent stay in the room.
	 * 
	 * @param a the agent that's in the meeting
	 */
private
    void beAtGlobalMeeting(final Agent a)
    {
        if (((Text)a.get(EVENT)).tostd::string().equalsIgnoreCase("GlobalMeetingEnded"))
        {
            a.set(EVENT, new Text("None"));
            goToDesk(a);
        }
    }

    /**
	 * Head for the event in the meeting room.
	 * 
	 * @param a the agent that should go
	 */
private
    void goToGlobalMeeting(final Agent a)
    {
        //a.setImage("HumanYellow");
        a.setDestination((Place)a.get("TemporaryDestination"));
        a.set(ACTIVITY, Activity.GOING_2_GLOBAL_LUNCH);
    }

    /**
	 * See if the agent has an event, and react to it.
	 * 
	 * @param a the agent we need to check
	 */
private
    void handleEvent(final Agent a)
    {
        Object e = a.get(EVENT);
        if (e.equals(new Text("None")))
        {
            return;
        }

        std::string event = e.tostd::string();
        if (event.equalsIgnoreCase("ConferenceRoomMeeting"))
        {
            goToGlobalMeeting(a);
        }
    }

    /**
	 * Have the agent spend some time in the toilet.
	 * 
	 * @param a the agent in need
	 * @param now the current simulation time
	 */
private
    void beAtToilet(final Agent a, final EasyTime now)
    {
        if (now.isAfter((EasyTime)(a.get(NEXT_EVENT_TIME))))
        {
            goToDesk(a);
            ((Place)a.get(DESIRED_TOILET)).set("Busy", new boolType(false));
        }
    }

    /**
	 * Mark the agent as having reached the toilet.
	 * 
	 * @param a the agent in need
	 * @param now the current simulation time
	 */
private
    void arriveAtToilet(final Agent a, final EasyTime now)
    {
        a.set(ACTIVITY, Activity.IN_TOILET);
        Random rand = new Random();
        EasyTime nextEventTime = new EasyTime(now).shift(0, rand.nextInt(TOILET_VISIT_DURATION) + 1);
        if (nextEventTime.tostd::string().equals(new EasyTime(23, 59).tostd::string()))
        {
            nextEventTime.shift(0, -1);
        }
        a.set(NEXT_EVENT_TIME, nextEventTime);
    }

    /**
	 * Make the agent queue to enter the toilet.
	 * 
	 * @param a the agent in need
	 * @param now the current time
	 */
private
    void lineInToilet(final Agent a, final EasyTime now)
    {
        Publishable info = a.get(DESIRED_TOILET);
        Place toilet;

        if (!(info instanceof Place))
        {
            //try {
            toilet = getNearestBathroomNotBusy(a, "RestHomeBathroom");
            //toilet = world.getNearestPlaceOfType("RestHomeBathroom", a.getPos());
            //} catch (PlaceNotFoundException e) {
            //	throw new RuntimeException(e);
            //}
            a.set(DESIRED_TOILET, toilet);
            a.set(NEXT_EVENT_TIME, new EasyTime(now).shift(new EasyTime(0, MAX_WAIT_TIME)));
        }
        else
        {
            //toilet = (Place) info;
            toilet = getNearestBathroomNotBusy(a, "RestHomeBathroom");
            a.set(DESIRED_TOILET, toilet);
            a.set(NEXT_EVENT_TIME, new EasyTime(now).shift(new EasyTime(0, MAX_WAIT_TIME)));
        }

        if (now.isAfter((EasyTime)a.get(NEXT_EVENT_TIME)))
        {
            a.set(NEXT_TOILET_VISIT, new EasyTime(now).shift(0, 2 * TOILET_RETRY_BLUR).blur(TOILET_RETRY_BLUR));
            goToDesk(a);
        }
        bool busy = ((boolType)toilet.get("Busy")).getValue();
        if (busy)
        {
            a.wanderAround((Place)(a.get(WAITING_PLACE)), INLINE_WANDER);
        }
        else
        {
            toilet.set("Busy", new boolType(true));
            a.setDestination(toilet);
            a.set(ACTIVITY, Activity.ENTERING_TOILET);
        }
    }

    /**
	 * Return the nearest toilet from the agent.
	 * 
	 * @param a the agent in need
	 * @param bathroomName the name of the place
	 */
private
    Place getNearestBathroomNotBusy(final Agent a, final std::string bathroomName)
    {
        Iterator<Place> bathRoomIt;
        try
        {
            bathRoomIt = world.getPlacesOfType(bathroomName).iterator();
        }
        catch (PlaceTypeUndefinedException e)
        {
            throw new RuntimeException("No bathroom defined", e);
        }
        while (bathRoomIt.hasNext())
        {
            Place bathroom = bathRoomIt.next();
            if (!((boolType)bathroom.get("Busy")).getValue())
            {
                return bathroom;
            }
        }

        try
        {
            return world.getNearestPlaceOfType(bathroomName, a.getPos());
        }
        catch (PlaceNotFoundException e)
        {
            throw new RuntimeException(e);
        }
    }

    /**
	 * Send the agent to the toilet.
	 * 
	 * @param a the agent that just has to go
	 */
private
    void goToToilet(final Agent a)
    {
        try
        {
            a.setDestination(world.getNearestPlaceOfType("RestHomeBathroomEntrance", a.getPos()));
        }
        catch (PlaceNotFoundException e)
        {
            throw new RuntimeException(e);
        }
        a.set(ACTIVITY, Activity.GOING_2_TOILET);
        a.set(WAITING_PLACE, a.getDestination());
    }

    /**
	 * Decide if it's time for this agent to pay a visit to the toilet.
	 * 
	 * @param a the agent to check
	 * @param now the current time
	 * @return true if the agent has to go
	 */
private
    bool isTimeForToilet(final Agent a, final EasyTime now)
    {
        EasyTime nextVisit = (EasyTime)a.get(NEXT_TOILET_VISIT);
        if (nextVisit.isBefore((EasyTime)a.get(WAKE_UP_TIME)))
        {
            nextVisit.shift((EasyTime)a.get(TOILET_INTERVAL));
            a.set(NEXT_TOILET_VISIT, nextVisit);
        }
        if (now.isAfter((EasyTime)a.get(NEXT_TOILET_VISIT)))
        {
            a.set(NEXT_TOILET_VISIT, new EasyTime(now).shift((EasyTime)a.get(TOILET_INTERVAL)));
            //a.setImage("HumanGreen");
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
	 * Send the agent home.
	 * 
	 * @param a the lucky agent
	 */
private
    void goHome(final Agent a)
    {
        a.setDestination((Place)a.get(DESK));
        a.set(ACTIVITY, Activity.LEAVING_WORK);
    }

    /**
	 * Send the agent to sleep
	 * 
	 * @param a the agent 
	 */
private
    void goToSleep(final Agent a)
    {
        a.set(ACTIVITY, Activity.RESTING);
        //a.setVisible(true);
    }

    /**
	 * Send the agent to his desk.
	 * 
	 * @param a the agent
	 */
private
    void goToDesk(final Agent a)
    {
        a.set(ACTIVITY, Activity.GOING_2_DESK);
        //a.setImage("HumanBlue");
        //a.setVisible(true);
        a.setDestination((Place)a.get(SEAT));
    }

    /**
	 * Make the agent stay by his desk.

	 * 
	 * @param a the hardworking agent
	 */
private
    void beAtDesk(final Agent a)
    {
        a.set(ACTIVITY, Activity.AT_DESK);
    }

    /**
	 * Returns an Text(bool) value
	 * 
	 */
private
    Text boolSort(std::string op)
    {
        Random rand = new Random();
        bool result = false;

        switch (op)
        {
        case FEVER:
            result = rand.nextDouble() < FEVER_PROBABILITY;
            break;
        case SYMPTOMS:
            result = rand.nextDouble() < SYMPTOMS_PROBABILITY;
            break;
        case ABFC_USE_OF_N95_MASK:
            result = rand.nextDouble() < BFC_USE_OF_N95_MASK;
            break;
        case AAFC_USE_OF_N95_MASK:
            result = rand.nextDouble() < AFC_USE_OF_N95_MASK;
            break;

        case ABFC_USE_OF_OTHER_MASK:
            result = rand.nextDouble() < BFC_USE_OF_OTHER_MASK;
            break;
        case AAFC_USE_OF_OTHER_MASK:
            result = rand.nextDouble() < AFC_USE_OF_OTHER_MASK;
            break;

        case ABFC_USE_OF_EYE_PROTECTION:
            result = rand.nextDouble() < BFC_USE_OF_EYE_PROTECTION;
            break;
        case AAFC_USE_OF_EYE_PROTECTION:
            result = rand.nextDouble() < AFC_USE_OF_EYE_PROTECTION;
            break;
        case ABFC_WASH_HANDS:
            result = rand.nextDouble() < BFC_WASH_HANDS;
            break;
        case AAFC_WASH_HANDS:
            result = rand.nextDouble() < AFC_WASH_HANDS;
            break;
        }
        return new Text(std::string.valueOf(result));
    }

    /**
	 * Returns an Text(int) number
	 * 
	 */
private
    Text intSort(std::string op)
    {
        Random rand = new Random();
        int result = 0;

        switch (op)
        {
        case FEVER_DURATION:
            result = rand.nextInt(FEVER_MAX_DURATION - FEVER_MIN_DURATION + 1) + FEVER_MIN_DURATION;
            break;
        case SYMPTOMS_DURATION:
            result = rand.nextInt(SYMPTOMS_MAX_DURATION - SYMPTOMS_MIN_DURATION + 1) + SYMPTOMS_MIN_DURATION;
            break;
        case SYMPTOMS_DAYS_TO_START:
            result = rand.nextInt(SYMPTOMS_MAX_DAYS_TO_START - SYMPTOMS_MIN_DAYS_TO_START + 1) + SYMPTOMS_MIN_DAYS_TO_START;
            break;
        case ABFC_PHYSICAL_DISTANCE:
            double aux = rand.nextDouble();
            result = aux <= BFC_PHYSICAL_DISTANCE_1M ? 1 : aux <= BFC_PHYSICAL_DISTANCE_1M + BFC_PHYSICAL_DISTANCE_2M                          ? 2
                                                       : aux <= BFC_PHYSICAL_DISTANCE_1M + BFC_PHYSICAL_DISTANCE_2M + BFC_PHYSICAL_DISTANCE_3M ? 3
                                                                                                                                               : 0;
            break;
        case AAFC_PHYSICAL_DISTANCE:
            double aux2 = rand.nextDouble();
            result = aux2 <= AFC_PHYSICAL_DISTANCE_1M ? 1 : aux2 <= AFC_PHYSICAL_DISTANCE_1M + AFC_PHYSICAL_DISTANCE_2M                          ? 2
                                                        : aux2 <= AFC_PHYSICAL_DISTANCE_1M + AFC_PHYSICAL_DISTANCE_2M + AFC_PHYSICAL_DISTANCE_3M ? 3
                                                                                                                                                 : 0;
            break;
        }
        return new Text(std::string.valueOf(result));
    }

    /**
	 * Return the distance between two agents
	 * 
	 */
private
    double distanceBetweenAgents(Agent a, Agent b)
    {
        return Math.sqrt(Math.pow(a.getPos().getRow() - b.getPos().getRow(), 2) + Math.pow(a.getPos().getCol() - b.getPos().getCol(), 2));
    }

    /**
	 * Return agents name
	 * 
	 * @param a the agent
	 */
private
    std::string agentName(Agent a)
    {
        return a.getName().substd::string(a.getName().lastIndexOf(' ') + 1);
    }

    /**
	 * Inform the agents of the first case
	 * 
	 * @param agents the agents
	 * @param easyTime the current easy time
	 */
private
    void isInfectionDetected(Collection<Agent> agents, EasyTime easyTime)
    {
        Iterator<Agent> peopleIt = agents.iterator();
        while (peopleIt.hasNext())
        {
            Agent a = peopleIt.next();
            if (agentCanInfectOthers(a) &&
                Integer.valueOf(a.get(DAYS_AFTER_INFECTION).tostd::string()) >= Integer.valueOf(a.get(SYMPTOMS_DAYS_TO_START).tostd::string()) &&
                !bool.valueOf(a.get(INFECTION_DETECTED).tostd::string()))
            {
                infectionDetected = true;
                a.set(INFECTION_DETECTED, new Text(std::string.valueOf(true)));
                print("Infection detected in agent " + agentName(a), easyTime);
                isolateAgent(a);
            }
        }
    }

    /**
	 * Isolate an agent
	 * 
	 * @param a the agent
	 */
private
    void isolateAgent(Agent a)
    {
        // The proposal is to isolate the agent in the simulated world. For now, if the agent is isolated, he/she does not transmit to others
    }

    /**
	 * Infect an agent
	 * 
	 * @param a the agent
	 * @param now the current easy time
	 */
private
    void infect(Agent a, EasyTime now)
    {
        a.setImage("HumanYellow");
        a.set(SITUATION, new Text(infected));
        a.set(DAYS_AFTER_INFECTION, new Text(std::string.valueOf(0)));
        a.set(INFECTION_TIME, new Text(std::string.valueOf(now.shift(23, 55).tostd::string())));
    }

private
    void infect(Agent a, EasyTime now, int daysAfterInfection)
    {
        a.setImage("HumanYellow");
        a.set(SITUATION, new Text(infected));
        a.set(DAYS_AFTER_INFECTION, new Text(std::string.valueOf(daysAfterInfection)));
        a.set(INFECTION_TIME, new Text(std::string.valueOf(now.shift(23, 55).tostd::string())));
    }

    /**
	 * Change the color and situation of an agent when it starts to infect others
	 * 
	 * @param agents the collection of agents
	 * @param now the current easy time
	 */
private
    void infectingOthers(Collection<Agent> agents, EasyTime now)
    {
        Iterator<Agent> peopleIt = agents.iterator();
        while (peopleIt.hasNext())
        {
            Agent a = peopleIt.next();
            if (agentSituation(a, infected) && (Integer.valueOf(a.get(DAYS_AFTER_INFECTION).tostd::string()) == Integer.valueOf(TRANSMISSION_DAYS_TO_START)))
            {
                a.set(SITUATION, new Text(infecting));
                print("Agent " + agentName(a) + " is infecting others", now);
                a.setImage("HumanMagenta");
            }
        }
    }

    /**
	 * Cure the infected agents
	 * 
	 * @param agents the collection of agents
	 * @param now the current easy time
	 */
private
    void cure(Collection<Agent> agents, EasyTime now)
    {
        Iterator<Agent> peopleIt = agents.iterator();
        while (peopleIt.hasNext())
        {
            Agent a = peopleIt.next();
            if (agentSituation(a, infecting) && (Integer.valueOf(a.get(DAYS_AFTER_INFECTION).tostd::string()) == Integer.valueOf(TRANSMISSION_DURATION) + Integer.valueOf(TRANSMISSION_DAYS_TO_START)))
            {
                a.set(SITUATION, new Text(cured));
                a.setImage("HumanGreen");
                print("Agent " + a + " is cured", now);
            }
        }
    }

    /**
	 * Return true if the agent can infect others
	 * 
	 * @param a the agent
	 */
private
    bool agentCanInfectOthers(Agent a)
    {
        return agentSituation(a, infecting); // && !bool.valueOf(a.get(INFECTION_DETECTED).tostd::string());
    }

    /**
	 * Return true if the agent can be infected
	 * 
	 * @param a the agent
	 */
private
    bool agentCanBeInfected(Agent a)
    {
        return agentSituation(a, healthy);
    }

    /**
	 * Return true if the agent is in the situation
	 * 
	 * @param a the agent
	 * @param situation the situation
	 */
private
    bool agentSituation(Agent a, std::string situation)
    {
        return a.get(SITUATION).tostd::string().equals(situation);
    }

    /**
	 * Calculate and infect (or not) a agent
	 * 
	 * @param infected the agent that is infecting others
	 * @param notInfected the agent that is not infected (yet?)
	 * @param now the current easy time
	 */
private
    void willTheAgentBeInfected(Agent infected, Agent notInfected, EasyTime now)
    {
        Random rand = new Random();

        double noseMouthChance = INFECTION_CHANCE_THROUGH_CONTACT;
        double eyeChance = INFECTION_CHANCE_THROUGH_AIR;

        //distance
        double distance = distanceBetweenAgents(infected, notInfected) * AREA_SCALE;

        if (!infectionDetected)
        {
            distance += Integer.valueOf(std::string.valueOf(notInfected.get(ABFC_PHYSICAL_DISTANCE))) * 100;
        }
        else
        {
            distance += Integer.valueOf(std::string.valueOf(notInfected.get(AAFC_PHYSICAL_DISTANCE))) * 100;
        }

        noseMouthChance -= (distance < 100 ? noseMouthChance * 0 : distance < 200 ? noseMouthChance * PHYSICAL_DISTANCE_REDUCTION_RISK_1M
                                                               : distance < 300   ? noseMouthChance * PHYSICAL_DISTANCE_REDUCTION_RISK_2M
                                                               : distance < 400   ? noseMouthChance * PHYSICAL_DISTANCE_REDUCTION_RISK_3M
                                                                                  : 1.0);
        eyeChance -= (distance < 100 ? eyeChance * 0 : distance < 200 ? eyeChance * PHYSICAL_DISTANCE_REDUCTION_RISK_1M
                                                   : distance < 300   ? eyeChance * PHYSICAL_DISTANCE_REDUCTION_RISK_2M
                                                   : distance < 400   ? eyeChance * PHYSICAL_DISTANCE_REDUCTION_RISK_3M
                                                                      : 1.0);

        if (!infectionDetected)
        {
            //Infected n95 mask
            noseMouthChance -= bool.valueOf(infected.get(ABFC_USE_OF_N95_MASK).tostd::string()) ? noseMouthChance * N95_MASK_REDUCTION_RISK : 0;
            //notInfected n95 mask
            noseMouthChance -= bool.valueOf(notInfected.get(ABFC_USE_OF_N95_MASK).tostd::string()) ? noseMouthChance * N95_MASK_REDUCTION_RISK : 0;

            //Infected other mask
            noseMouthChance -= bool.valueOf(infected.get(ABFC_USE_OF_OTHER_MASK).tostd::string()) ? noseMouthChance * OTHER_MASK_REDUCTION_RISK : 0;
            //notInfected other mask
            noseMouthChance -= bool.valueOf(notInfected.get(ABFC_USE_OF_OTHER_MASK).tostd::string()) ? noseMouthChance * OTHER_MASK_REDUCTION_RISK : 0;

            //notInfected eye protection
            eyeChance -= bool.valueOf(notInfected.get(ABFC_USE_OF_EYE_PROTECTION).tostd::string()) ? eyeChance * EYE_PROTECTION_REDUCTION_RISK : 0;

            //notInfected wash hands
            noseMouthChance -= bool.valueOf(notInfected.get(ABFC_WASH_HANDS).tostd::string()) ? noseMouthChance * WASH_HANDS_REDUCTION_RISK : 0;
            eyeChance -= bool.valueOf(notInfected.get(ABFC_WASH_HANDS).tostd::string()) ? eyeChance * WASH_HANDS_REDUCTION_RISK : 0;
        }
        else
        {
            //Infected n95 mask
            noseMouthChance -= bool.valueOf(infected.get(AAFC_USE_OF_N95_MASK).tostd::string()) ? noseMouthChance * N95_MASK_REDUCTION_RISK : 0;
            //notInfected n95 mask
            noseMouthChance -= bool.valueOf(notInfected.get(AAFC_USE_OF_N95_MASK).tostd::string()) ? noseMouthChance * N95_MASK_REDUCTION_RISK : 0;

            //Infected other mask
            noseMouthChance -= bool.valueOf(infected.get(AAFC_USE_OF_OTHER_MASK).tostd::string()) ? noseMouthChance * OTHER_MASK_REDUCTION_RISK : 0;
            //notInfected other mask
            noseMouthChance -= bool.valueOf(notInfected.get(AAFC_USE_OF_OTHER_MASK).tostd::string()) ? noseMouthChance * OTHER_MASK_REDUCTION_RISK : 0;

            //notInfected eye protection
            eyeChance -= bool.valueOf(notInfected.get(AAFC_USE_OF_EYE_PROTECTION).tostd::string()) ? eyeChance * EYE_PROTECTION_REDUCTION_RISK : 0;

            //notInfected wash hands
            noseMouthChance -= bool.valueOf(notInfected.get(AAFC_WASH_HANDS).tostd::string()) ? noseMouthChance * WASH_HANDS_REDUCTION_RISK : 0;
            eyeChance -= bool.valueOf(notInfected.get(AAFC_WASH_HANDS).tostd::string()) ? eyeChance * WASH_HANDS_REDUCTION_RISK : 0;
        }

        double aux = rand.nextDouble();
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

    /**
	 * Increase the DAYS_AFTER_INFECTION value
	 * 
	 * @param agents the collection of agents
	 * @param now the current easy time
	 */
private
    void increaseDaysAfterInfection(Collection<Agent> agents, EasyTime now)
    {
        Iterator<Agent> peopleIt = agents.iterator();
        while (peopleIt.hasNext())
        {
            Agent a = peopleIt.next();
            if (now.tostd::string().equals(a.get(INFECTION_TIME).tostd::string()) && (agentSituation(a, infected) || agentSituation(a, infecting)))
            {
                int daysAfterInfection = Integer.parseInt(a.get(DAYS_AFTER_INFECTION).tostd::string());
                a.set(DAYS_AFTER_INFECTION, new Text(std::string.valueOf(daysAfterInfection + 1)));
            }
        }
    }

    /**
	 * Write in EventData.csv and in the console about new infected agents and the beginning of a new day
	 * 
	 * @param event the information
	 */
private
    void print(std::string message, EasyTime easyTime)
    {
        int hour = easyTime.getHour();
        int minute = easyTime.getMinute();
        std::string result = ((hour < 10 ? " " : "") + hour) + ":" + ((minute < 10 ? "0" : "") + minute) + " - " + message + "\n";
        System.out.print(result);
        writeEventData(result);
    }

    /**
	 * Write in EventData.csv and in the console the current day 
	 * 
	 * @param event the information
	 */
private
    void printDayInfo()
    {
        std::string result = "DAY " + day + " ----------------------------------------\n";
        System.out.print(result);
        writeEventData(result);
    }

    /**
	 * Write in WearableData.csv the collected data from the wearable IoT devices. Day, Hour, Id, blood oxygen and body temperature
	 * 
	 * @param event the information
	 */
private
    void writeData(Collection<Agent> agents, EasyTime easyTime)
    {
        PrintWriter csvWriter;
        std::string filePath = path + "/Desktop/WearableData.csv";
        try
        {
            File file = new File(filePath);
            if (!file.exists())
            {
                file = new File(filePath);
            }
            csvWriter = new PrintWriter(new FileWriter(file, true));

            Iterator<Agent> peopleIt = agents.iterator();
            while (peopleIt.hasNext())
            {
                Agent a = peopleIt.next();
                csvWriter.print(day + ",");
                csvWriter.print(easyTime.tostd::string() + ",");
                csvWriter.print(agentName(a) + ","); //id

                csvWriter.print(std::string.valueOf(a.get(BLOODOXYGEN)).replace(',', '.') + ","); //blood oxygen
                //csvWriter.print(a.get(BLOODPRESSURE)+","); //blood pressure
                csvWriter.print(std::string.valueOf(a.get(BODYTEMPERATURE)).replace(',', '.') + "\r\n"); //body temperature
            }
            csvWriter.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    /**
	 * Write in DailyData.csv the information about the daily medical report. Day, if the infection was detected and number of healthy, infected, infecting, infecting asymptomatic and cured
	 * 
	 * @param event the information
	 */
private
    void writeDailyData(Collection<Agent> agents)
    {
        PrintWriter csvWriter;
        std::string filePath = "DailyData.csv";
        try
        {
            File file = new File(filePath);
            if (!file.exists())
            {
                file = new File(filePath);
            }
            csvWriter = new PrintWriter(new FileWriter(file, true));

            int healthy = 0;
            int infected = 0;
            int infecting = 0;
            int infectingAndAsymptomatic = 0;
            int cured = 0;

            Iterator<Agent> peopleIt = agents.iterator();
            while (peopleIt.hasNext())
            {
                Agent a = peopleIt.next();
                healthy += agentSituation(a, this.healthy) ? 1 : 0;
                infected += agentSituation(a, this.infected) ? 1 : 0;
                infecting += agentSituation(a, this.infecting) ? 1 : 0;
                infectingAndAsymptomatic += agentSituation(a, this.infecting) && !bool.valueOf(a.get(SYMPTOMS).tostd::string()) ? 1 : 0;
                cured += agentSituation(a, this.cured) ? 1 : 0;
            }

            csvWriter.print(day + ",");
            csvWriter.print((infectionDetected ? "1" : "0") + ",");
            csvWriter.print(healthy + ",");
            csvWriter.print(infected + ",");
            csvWriter.print(infecting + ",");
            csvWriter.print(infectingAndAsymptomatic + ",");
            csvWriter.print(cured + "\r\n");
            csvWriter.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    /**
	 * Write in EventData.csv the information about new infected agents and the beginning of a new day. Same as in console 
	 * 
	 * @param event the information
	 */
private
    void writeEventData(std::string event)
    {
        PrintWriter csvWriter;
        std::string filePath = path + "/Desktop/EventData.csv";
        try
        {
            File file = new File(filePath);
            if (!file.exists())
            {
                file = new File(filePath);
            }
            csvWriter = new PrintWriter(new FileWriter(file, true));
            csvWriter.print(event + "\r\n");
            csvWriter.close();
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
};

#endif
