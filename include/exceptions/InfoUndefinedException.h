#ifndef INFOUNDEFINEDEXCEPTION_H
#define INFOUNDEFINEDEXCEPTION_H

#include <exception>
#include <string>

class InfoUndefinedException : public std::exception
{
private:
    std::string m_error{};

public:

    InfoUndefinedException(std::string infoVariable) : m_error{"Unknown context variable: " + infoVariable + "."}
    {
    }

    virtual const char *what() const noexcept override { return m_error.c_str(); }
};

#endif