#ifndef TEXT_H
#define TEXT_H

#include <types/Publishable.h>
#include <string>

class Text : public Publishable
{

private:
    std::string text;

public:
    Text(const std::string text);

    virtual ~Text() {}

    std::string toString() override;

    std::string getText();

    std::string getType() override;

    bool equals(Publishable *o);
};

#endif
