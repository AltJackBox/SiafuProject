#ifndef POSITIONOUTOFTHEMAPEXCEPTION_H
#define POSITIONOUTOFTHEMAPEXCEPTION_H

#include <exceptions/PositionUnreachableException.h>
#include <exception>
#include <string>


class PositionOutOfTheMapException :  public PositionUnreachableException
{
private:
	std::string m_error{};
 
public:
	PositionOutOfTheMapException() : m_error{"PositionOutOfTheMapException"}
	{
	}
 
	virtual const char* what() const noexcept override { return m_error.c_str(); }
};

#endif