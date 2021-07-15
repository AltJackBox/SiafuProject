#include <Calendar.h>

Calendar::Calendar()
{
    hour = 6;
    minute = 0;
    second = 0;
}

void Calendar::reset()
{
    hour = 0;
    minute = 0;
    second = 0;
}

void Calendar::add(int increaseSec)
{
    second += increaseSec;
    if (second >= SECONDS_PER_MINUTE)
    {
        minute += (second / SECONDS_PER_MINUTE);
        second = second % SECONDS_PER_MINUTE;
    }
    if (minute >= MINS_PER_HOUR)
    {
        hour += (minute / MINS_PER_HOUR);
        minute = minute % MINS_PER_HOUR;
    }
    if (hour >= HOURS_PER_DAY)
    {
        hour = hour % HOURS_PER_DAY;
    }
}

int Calendar::getSec(){
    return second;
}

int Calendar::getMin(){
    return minute;
}

int Calendar::getHour(){
    return hour;
}

std::string Calendar::toString() {
    return std::to_string(hour) + ":" + std::to_string(minute) + ":" + std::to_string(second);
}