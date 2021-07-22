#ifndef TIMEPERIOD_H
#define TIMEPERIOD_H

#include <types/Publishable.h>
#include <string>

class EasyTime;

class TimePeriod : public Publishable
{

private:
    EasyTime* start;

    EasyTime* end;


public:
    TimePeriod( EasyTime* start,  EasyTime* end);

    virtual ~TimePeriod();

    EasyTime* getStart();


    EasyTime* getEnd();

    std::string getType() override;


    std::string toString() override;

    bool equals(Publishable* o);
};

#endif
