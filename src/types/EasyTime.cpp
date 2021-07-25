#include <types/EasyTime.h>
#include <types/TimePeriod.h>

void EasyTime::normalize()
{
    hour += minute / MINS_PER_HOUR;
    if (minute < 0)
    {
        minute %= MINS_PER_HOUR;
        minute += MINS_PER_HOUR;
        hour--;
    }
    minute %= MINS_PER_HOUR;

    if (hour < 0)
    {
        hour %= HOURS_PER_DAY;
        hour += HOURS_PER_DAY;
    }
    hour %= HOURS_PER_DAY;
}

EasyTime::EasyTime(std::shared_ptr<EasyTime> time)
{
    this->hour = time->getHour();
    this->minute = time->getMinute();
    normalize();
}

EasyTime::EasyTime(EasyTime *time)
{
    this->hour = time->getHour();
    this->minute = time->getMinute();
    normalize();
}

EasyTime::EasyTime(const int hour, const int minute)
{
    this->hour = hour;
    this->minute = minute;
    normalize();
}

bool EasyTime::isAfter(std::shared_ptr<EasyTime> t)
{
    if (hour > t->hour)
    {
        return true;
    }
    else if ((hour == t->hour) && (minute > t->minute))
    {
        return true;
    }

    return false;
}

bool EasyTime::isBefore(std::shared_ptr<EasyTime>  t)
{
    return !isAfter(t);
}

bool EasyTime::isAfter(EasyTime *t)
{
    if (hour > t->hour)
    {
        return true;
    }
    else if ((hour == t->hour) && (minute > t->minute))
    {
        return true;
    }

    return false;
}

bool EasyTime::isBefore(EasyTime *t)
{
    return !isAfter(t);
}

bool EasyTime::isIn(TimePeriod *tp)
{
    EasyTime* start = tp->getStart();
    EasyTime* end = tp->getEnd();

    if (end->isAfter(start))
    { // We went over 00h00

        if (isAfter(tp->getStart()) && isBefore(tp->getEnd()))
        {
            return true;
        }
    }
    else if (isAfter(tp->getStart()) || isBefore(tp->getEnd()))
    {
        return true;
    }

    return false;
}

EasyTime *EasyTime::shift(const int hours, const int minutes)
{
    this->hour += hours;
    this->minute += minutes;
    normalize();
    return this;
}

EasyTime *EasyTime::shift(EasyTime *et)
{
    return shift(et->getHour(), et->getMinute());
}

// Random utilization : Modify commented lines to use
EasyTime *EasyTime::blur(const int blurMinutes)
{
    // srand(time(0));
    //int minuteShift = (rand() % (blurMinutes - 1)) - (blurMinutes / 2); //Randint is generates numbers between 0 (inclusive) and the specified value (exclusive)
    int minuteShift = blurMinutes - (blurMinutes / 2);
    this->shift(0, minuteShift);
    return this;
}

int EasyTime::getHour()
{
    return hour;
}

int EasyTime::getMinute()
{
    return minute;
}

int EasyTime::getTimeInSeconds()
{
    const int hourToSeconds = 3600;
    const int minuteToSeconds = 60;
    return (hour * hourToSeconds) + (minute * minuteToSeconds);
}

std::string EasyTime::toString()
{
    return std::to_string(hour) + ":" + std::to_string(minute);
}

std::string EasyTime::getType()
{
    return "EasyTime";
}

bool EasyTime::equals(Publishable *o)
{

    if (!( (o->getType()).compare("EasyTime") == 0) )
    {
        return false;
    }
    else
    {
        EasyTime *et = (EasyTime *)o;
        return (et->getHour() == hour && et->getMinute() == minute);
    }
}