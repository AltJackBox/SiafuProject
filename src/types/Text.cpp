#include <types/Text.h>

Text::Text(const std::string text)
{
    this->text = text;
}

std::string Text::toString()
{
    return text;
}

std::string Text::getText()
{
    return text;
}

std::string Text::getType() {
    return "Text";
}

bool Text::equals(Publishable *o)
{
    if (!(o->getType().compare("Text") == 0))
    {
        return false;
    }
    else
    {
        Text *t = (Text *)o;
        return (t->getText().compare(text) == 0);
    }
}