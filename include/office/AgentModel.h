#ifndef AGENTMODEL_H
#define AGENTMODEL_H

#include <behaviormodels/BaseAgentModel.h>
#include <string>

class Place;
class World;
class EasyTime;

class AgentModel : public BaseAgentModel
{

private:
    std::string lastHandleInfectionExecution;
    //std::string path = System.getProperty("user.home");

    std::string healthy = "Healthy";
    std::string infected = "Infected";
    std::string infecting = "Infecting";
    std::string cured = "Cured";

    bool infectionDetected = false;
    int day = 1;

    /** The door to the places. */
    Place *restHomeDoor;
    // Place apartmentOneDoor;
    // Place apartmentTwoDoor;
    Place *apartmentThreeDoor;
    Place *houseDoor;

    void createWorker(const std::vector<Agent *> people, const std::string type, const std::string bedLocation, const std::string seatLocation);

    void handleInfection(std::vector<Agent *> agents, EasyTime *now);

    void handlePersonBodySensors(Agent *a);

    void handlePerson(Agent *a, EasyTime *now);

    void beAtGlobalMeeting(Agent *a);

    void goToGlobalMeeting(Agent *a);

    void handleEvent(Agent *a);

    void beAtToilet(Agent *a, EasyTime *now);

    void arriveAtToilet(Agent *a, EasyTime* now);

    void lineInToilet(Agent *a, EasyTime* now);

    Place* getNearestBathroomNotBusy(Agent *a, std::string bathroomName);

    void goToToilet(Agent *a);

    bool isTimeForToilet(Agent *a, EasyTime* now);

    void goHome(Agent *a);

    void goToSleep(Agent *a);

    void goToDesk(Agent *a);

    void beAtDesk(Agent *a);

    Text boolSort(std::string op);

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
    double distanceBetweenAgents(Agent *a, Agent b)
    {
        return Math.sqrt(Math.pow(a->getPos().getRow() - b.getPos().getRow(), 2) + Math.pow(a->getPos().getCol() - b.getPos().getCol(), 2));
    }

    /**
	 * Return agents name
	 * 
	 * @param a the agent
	 */
private
    std::string agentName(Agent *a)
    {
        return a->getName().substd::string(a->getName().lastIndexOf(' ') + 1);
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
            Agent *a = peopleIt.next();
            if (agentCanInfectOthers(a) &&
                Integer.valueOf(a->get(DAYS_AFTER_INFECTION).tostd::string()) >= Integer.valueOf(a->get(SYMPTOMS_DAYS_TO_START).tostd::string()) &&
                !bool.valueOf(a->get(INFECTION_DETECTED).tostd::string()))
            {
                infectionDetected = true;
                a->set(INFECTION_DETECTED, new Text(std::string.valueOf(true)));
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
    void isolateAgent(Agent *a)
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
    void infect(Agent *a, EasyTime now)
    {
        a->setImage("HumanYellow");
        a->set(SITUATION, new Text(infected));
        a->set(DAYS_AFTER_INFECTION, new Text(std::string.valueOf(0)));
        a->set(INFECTION_TIME, new Text(std::string.valueOf(now.shift(23, 55).tostd::string())));
    }

private
    void infect(Agent *a, EasyTime now, int daysAfterInfection)
    {
        a->setImage("HumanYellow");
        a->set(SITUATION, new Text(infected));
        a->set(DAYS_AFTER_INFECTION, new Text(std::string.valueOf(daysAfterInfection)));
        a->set(INFECTION_TIME, new Text(std::string.valueOf(now.shift(23, 55).tostd::string())));
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
            Agent *a = peopleIt.next();
            if (agentSituation(a, infected) && (Integer.valueOf(a->get(DAYS_AFTER_INFECTION).tostd::string()) == Integer.valueOf(TRANSMISSION_DAYS_TO_START)))
            {
                a->set(SITUATION, new Text(infecting));
                print("Agent " + agentName(a) + " is infecting others", now);
                a->setImage("HumanMagenta");
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
            Agent *a = peopleIt.next();
            if (agentSituation(a, infecting) && (Integer.valueOf(a->get(DAYS_AFTER_INFECTION).tostd::string()) == Integer.valueOf(TRANSMISSION_DURATION) + Integer.valueOf(TRANSMISSION_DAYS_TO_START)))
            {
                a->set(SITUATION, new Text(cured));
                a->setImage("HumanGreen");
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
    bool agentCanInfectOthers(Agent *a)
    {
        return agentSituation(a, infecting); // && !bool.valueOf(a->get(INFECTION_DETECTED).tostd::string());
    }

    /**
	 * Return true if the agent can be infected
	 * 
	 * @param a the agent
	 */
private
    bool agentCanBeInfected(Agent *a)
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
    bool agentSituation(Agent *a, std::string situation)
    {
        return a->get(SITUATION).tostd::string().equals(situation);
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
            Agent *a = peopleIt.next();
            if (now.tostd::string().equals(a->get(INFECTION_TIME).tostd::string()) && (agentSituation(a, infected) || agentSituation(a, infecting)))
            {
                int daysAfterInfection = Integer.parseInt(a->get(DAYS_AFTER_INFECTION).tostd::string());
                a->set(DAYS_AFTER_INFECTION, new Text(std::string.valueOf(daysAfterInfection + 1)));
            }
        }
    }

    /**
	 * Write in EventData->csv and in the console about new infected agents and the beginning of a new day
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
                Agent *a = peopleIt.next();
                csvWriter.print(day + ",");
                csvWriter.print(easyTime.tostd::string() + ",");
                csvWriter.print(agentName(a) + ","); //id

                csvWriter.print(std::string.valueOf(a->get(BLOODOXYGEN)).replace(',', '.') + ","); //blood oxygen
                //csvWriter.print(a->get(BLOODPRESSURE)+","); //blood pressure
                csvWriter.print(std::string.valueOf(a->get(BODYTEMPERATURE)).replace(',', '.') + "\r\n"); //body temperature
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
                Agent *a = peopleIt.next();
                healthy += agentSituation(a, this.healthy) ? 1 : 0;
                infected += agentSituation(a, this.infected) ? 1 : 0;
                infecting += agentSituation(a, this.infecting) ? 1 : 0;
                infectingAndAsymptomatic += agentSituation(a, this.infecting) && !bool.valueOf(a->get(SYMPTOMS).tostd::string()) ? 1 : 0;
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

public:
    AgentModel(World *world);

    std::vector<Agent *> createAgents() override;

    void doIteration(std::vector<Agent *> agents) override;
};

#endif
