#include <model/CoordinateTools.h>
#include <model/Position.h>
#include <utils.h>
#include <cmath>

CoordinateTools::CoordinateTools(const int height, const int width, const double topRight[], const double bottomRight[], const double bottomLeft[])
{
	this->height = height;

	blLat = bottomLeft[0];
	blLon = bottomLeft[1];

	brLat = bottomRight[0];
	brLon = bottomRight[1];

	trLat = topRight[0];
	trLon = topRight[1];

	// Optimization: check if we need to figure out N/S and E/W everytime,
	// or we are always on the same hemispheres.
	if ( (signum(blLon) != signum(trLon)) || (signum(blLat) != signum(trLat)) || (signum(blLat) != signum(trLat - brLat)) || (signum(blLon) != signum(trLon - brLon)) )
	{
		crossesZeroes = true;
		latHemisphere = "";
		lonHemisphere = "";
	}
	else
	{
		crossesZeroes = false;
		latHemisphere = getHemisphereByLatitude(blLat);
		lonHemisphere = getHemisphereByLongitude(blLon);
	}

	mapWidthDegrees =
		std::sqrt(std::pow(brLat - blLat, 2) + std::pow((brLon - blLon), 2));
	mapHeightDegrees =
		std::sqrt(std::pow(trLat - brLat, 2) + std::pow((trLon - brLon), 2));

	jFactor = mapWidthDegrees / width;
	iFactor = mapHeightDegrees / height;
	xFactor = width / mapWidthDegrees;

	double a = std::acos((brLon - blLon) / mapWidthDegrees);

	cosA = std::cos(a);
	sinA = std::sin(a);

	yOffset = -(blLat * cosA) + (blLon * sinA);
	xOffset = -(blLat * sinA) - (blLon * cosA);
}

double *CoordinateTools::localToCoordinates(int i, int j)
{
	double x = jFactor * j;
	double y = iFactor * (height - i);

	double *coordinate = new double[2];

	coordinate[0] = x * sinA + y * cosA + blLat;

	coordinate[1] = x * cosA - y * sinA + blLon;

	return coordinate;
}

double *CoordinateTools::localToCoordinates(Position *pos)
{
	return localToCoordinates(pos->getRow(), pos->getCol());
}

Position* CoordinateTools::coordinatesToLocal(const double lat, const double lon)
{
	double y = -(lon * sinA) + lat * cosA + yOffset;
	double x = lon * cosA + lat * sinA + xOffset;

	int i = (int)std::floor(height * (1 - (y / mapHeightDegrees)));
	int j = (int)std::floor(xFactor * x);

	return new Position(i, j);
}

std::string CoordinateTools::getHemisphereByLatitude(const double latitude)
{
	if (latitude < 0)
	{
		return "S";
	}
	else
	{
		return "N";
	}
}

std::string CoordinateTools::getHemisphereByLongitude(const double longitude)
{
	if (longitude < 0)
	{
		return "W";
	}
	else
	{
		return "E";
	}
}