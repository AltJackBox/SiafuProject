#include <types/TimePeriod.h>
#include <types/EasyTime.h>

TimePeriod::TimePeriod(EasyTime *start, EasyTime *end)
{
    this->start = start;
    this->end = end;
}

EasyTime *TimePeriod::getStart()
{
    return start;
}

EasyTime *TimePeriod::getEnd()
{
    return end;
}

std::string TimePeriod::getType() 
{
    return "TimePeriod";
}

std::string TimePeriod::toString() 
{
    return start->toString() + "-" + end->toString();
}

bool TimePeriod::equals(Publishable *o)
{
    if (!(o->getType().compare("TimePeriod") == 0))
    {
        return false;
    }
    else
    {
        TimePeriod *tp = (TimePeriod *)o;
        return (tp->getStart()->equals(start) && tp->getEnd()->equals(end));
    }
}