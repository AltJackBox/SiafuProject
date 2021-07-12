#ifndef INITIALIZATIONREQUIREDEXCEPTION_H
#define INITIALIZATIONREQUIREDEXCEPTION_H

#include <exception>
#include <string>

class InitializationRequiredException : public std::exception
{
private:
    std::string m_error{};

public:

    InitializationRequiredException(std::string msg) : m_error{msg + "\n"}
    {
    }

    virtual const char *what() const noexcept override { return m_error.c_str(); }
};

#endif