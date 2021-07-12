#ifndef PLACETYPEUNDEFINEDEXCEPTION_H
#define PLACETYPEUNDEFINEDEXCEPTION_H

#include <exception>
#include <string>


class PlaceTypeUndefinedException : public std::exception
{
private:
	std::string m_error{};
 
public:
	PlaceTypeUndefinedException(std::string type) : m_error{ "Places type: " + type + " is undefined." }
	{
	}
 
	virtual const char* what() const noexcept override { return m_error.c_str(); }
};

#endif