#ifndef POSITIONUNREACHABLEEXCEPTION_H
#define POSITIONUNREACHABLEEXCEPTION_H

#include <exception>
#include <string>


class PositionUnreachableException : public std::exception
{
private:
	std::string m_error{};
 
public:
	PositionUnreachableException() : m_error{"PositionUnreachableException"}
	{
	}
 
	virtual const char* what() const noexcept override { return m_error.c_str(); }
};

#endif