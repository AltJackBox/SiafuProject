#ifndef COORDINATETOOLS_H
#define COORDINATETOOLS_H

#include <string>

class Position;

class CoordinateTools {
	
	private:

	static const int PRETTY_COORDINATE_PRECISION = 3;

	static const int MINUTES_PER_DEGREE = 60;

	int height;

	double brLat;

	double brLon;

	double blLat;

	double blLon;

	double trLat;

	double trLon;

	double mapHeightDegrees;

	double mapWidthDegrees;


	double jFactor;

	double iFactor;

	double xFactor;

	double yOffset;

	double xOffset;

	std::string latHemisphere;


	std::string lonHemisphere;


	bool crossesZeroes;

	double cosA;

	double sinA;


	public:

	CoordinateTools();

	~CoordinateTools() {};

	CoordinateTools(const int height, const int width, const double topRight[] , const double bottomRight[] , const double bottomLeft[] );

	double* localToCoordinates(int i, int j);

	double* localToCoordinates(Position* pos);

	Position* coordinatesToLocal(const double lat, const double lon);

	std::string getHemisphereByLatitude(const double latitude);

	std::string getHemisphereByLongitude(const double longitude);
};

#endif
