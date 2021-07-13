#ifndef NULLPOINTEREXCEPTION_H
#define NULLPOINTEREXCEPTION_H

#include <exception>
#include <string>


class NullPointerException : public std::exception
{
private:
	std::string m_error{};
 
public:
	NullPointerException() : m_error{"NullPointerException"}
	{
	}

    NullPointerException(std::string msg) : m_error{msg}
	{
	}
 
	virtual const char* what() const noexcept override { return m_error.c_str(); }
};

#endif