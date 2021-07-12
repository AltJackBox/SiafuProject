#ifndef INFOFIELDSLOCKEDEXCEPTION_H
#define INFOFIELDSLOCKEDEXCEPTION_H

#include <exception>
#include <string>

class InfoFieldsLockedException : public std::exception
{
private:
    std::string m_error{};

public:

    InfoFieldsLockedException(std::string field) : m_error{"Can't add new field: " + field + "."}
    {
    }

    virtual const char *what() const noexcept override { return m_error.c_str(); }
};

#endif