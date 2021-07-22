#ifndef BOOLEANTYPE_H
#define BOOLEANTYPE_H

#include <types/Publishable.h>
#include <string>

class BooleanType : public Publishable
{

private:
    bool b;

public:
    BooleanType(const bool val);

    virtual ~BooleanType() {}

    std::string toString() override;

    bool getValue();

    std::string getType() override;

    bool equals(Publishable *o);
};

#endif
