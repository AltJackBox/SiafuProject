#ifndef EASYTIME_H
#define EASYTIME_H

#include <types/Publishable.h>
#include <string>

class EasyTime : public Publishable
{

    /** Minutes per hour. */
private:
    static const int MINS_PER_HOUR = 60;

    static const int HOURS_PER_DAY = 24;

    static const int SECONDS_PER_MINUTE = 60;

    static const int SECONDS_PER_DAY = 86400;

    //Random rand = new Random();

    int hour;

    int minute;

    int seconds;

    void normalize()                    // CHECK THIS AGAIN
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

public:
    EasyTime(EasyTime* time);

    EasyTime(const int hour, const int minute);

    bool isAfter( EasyTime* t);

    bool isBefore( EasyTime* t);

    // bool isIn( TimePeriod tp)
    // {
    //     EasyTime start = tp.getStart();
    //     EasyTime end = tp.getEnd();

    //     if (end.isAfter(start))
    //     { // We went over 00h00

    //         if (isAfter(tp.getStart()) && isBefore(tp.getEnd()))
    //         {
    //             return true;
    //         }
    //     }
    //     else if (isAfter(tp.getStart()) || isBefore(tp.getEnd()))
    //     {
    //         return true;
    //     }

    //     return false;
    // }

    EasyTime* shift(const int hours, const int minutes);

    EasyTime* shift( EasyTime* et);

    EasyTime* blur(const int blurMinutes);

    int getHour();

    int getMinute();

    int getTimeInSeconds();


    std::string toString();

};

#endif
