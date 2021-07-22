#ifndef PUBLISHABLE_H
#define PUBLISHABLE_H

#include <string>

class Publishable
{
    public:
    virtual std::string getType() {
        return "Publishable";
    }
    virtual std::string toString() {
        return "Empty";
    }

    virtual ~Publishable(){}
};

#endif