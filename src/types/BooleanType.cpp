#include <types/BooleanType.h>

BooleanType::BooleanType(const bool val)
{
    this->b = val;
}

std::string BooleanType::toString()
{
    return "" + std::to_string(b);
}

bool BooleanType::getValue()
{
    return b;
}

std::string BooleanType::getType()
{
    return "BooleanType";
}

bool BooleanType::equals(Publishable *o)
{
    if (!(o->getType().compare("BooleanType") == 0))
    {
        return false;
    }
    else
    {
        BooleanType *bt = (BooleanType *)o;
        return (bt->getValue() == b);
    }
}