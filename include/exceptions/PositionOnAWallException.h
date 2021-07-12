#ifndef POSITIONONAWALLEXCEPTION_H
#define POSITIONONAWALLEXCEPTION_H

#include <exceptions/PositionUnreachableException.h>
#include <exception>
#include <string>
#include <string_view>


class PositionOnAWallException : public PositionUnreachableException
{
private:
	std::string m_error;
 
public:
	PositionOnAWallException() : m_error{"PositionOnAWallException"}
	{
	}
 
	virtual const char* what() const noexcept override { return m_error.c_str(); }
};

#endif