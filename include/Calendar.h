#ifndef CALENDAR_H
#define CALENDAR_H

#include <iostream>

class Calendar
{

private:

    int second;
    int minute;
    int hour;

    static const int MINS_PER_HOUR = 60;

    static const int HOURS_PER_DAY = 24;

    static const int SECONDS_PER_MINUTE = 60;

    static const int SECONDS_PER_DAY = 86400;

public:

    Calendar();

    void reset();

    void add(int increaseSec);

    int getSec();

    int getMin();

    int getHour();

    std::string toString();
};

#endif