#ifndef EASYTIME_H
#define EASYTIME_H

#include <types/Publishable.h>
#include <string>

class TimePeriod;

class EasyTime : public Publishable
{

private:
    static const int MINS_PER_HOUR = 60;

    static const int HOURS_PER_DAY = 24;

    int hour;

    int minute;

    void normalize();

public:
    EasyTime(EasyTime *time);

    EasyTime(const int hour, const int minute);

    bool isAfter(EasyTime *t);

    bool isBefore(EasyTime *t);

    bool isIn(TimePeriod *tp);

    EasyTime *shift(const int hours, const int minutes);

    EasyTime *shift(EasyTime *et);

    EasyTime *blur(const int blurMinutes);

    int getHour();

    int getMinute();

    int getTimeInSeconds();

    std::string toString() override;

    std::string getType() override;

    bool EasyTime::equals(Publishable *o);
};

#endif
