#ifndef COORDINATETOOLS_H
#define COORDINATETOOLS_H

#include <string>

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
	CoordinateTools(const int height, const int width, const double topRight[] , const double bottomRight[] , const double bottomLeft[] ) {
		// this.width = width;
		this->height = height;

		blLat = bottomLeft[0];
		blLon = bottomLeft[1];

		brLat = bottomRight[0];
		brLon = bottomRight[1];

		trLat = topRight[0];
		trLon = topRight[1];

		// Optimization: check if we need to figure out N/S and E/W everytime,
		// or we are always on the same hemispheres.
		if (Math.signum(blLon) != Math.signum(trLon)
				|| Math.signum(blLat) != Math.signum(trLat)
				|| Math.signum(blLat) != Math.signum(trLat - brLat)
				|| Math.signum(blLon) != Math.signum(trLon - brLon)) {
			crossesZeroes = true;
			latHemisphere = null;
			lonHemisphere = null;
		} else {
			crossesZeroes = false;
			latHemisphere = getHemisphereByLatitude(blLat);
			lonHemisphere = getHemisphereByLongitude(blLon);
		}

		mapWidthDegrees =
				Math.sqrt(Math.pow(brLat - blLat, 2)
						+ Math.pow((brLon - blLon), 2));
		mapHeightDegrees =
				Math.sqrt(Math.pow(trLat - brLat, 2)
						+ Math.pow((trLon - brLon), 2));

		jFactor = mapWidthDegrees / width;
		iFactor = mapHeightDegrees / height;
		xFactor = width / mapWidthDegrees;

		double a = Math.acos((brLon - blLon) / mapWidthDegrees);

		cosA = Math.cos(a);
		sinA = Math.sin(a);

		yOffset = -(blLat * cosA) + (blLon * sinA);
		xOffset = -(blLat * sinA) - (blLon * cosA);
	}

	/**
	 * Convert a Siafu map position (a row column pair) into a string of the
	 * form "N 49 34.233 E 23 22.322", according to the map calibration.
	 * 
	 * @param pos the position
	 * @return the prettified string
	 */
	public String localToPrettyCoordinates(const Position pos) {
		return coordinatesToPrettyCoordinates(localToCoordinates(pos
				.getRow(), pos.getCol()));
	}

	/**
	 * Convert a Siafu map position (a row column pair) into a string of the
	 * form "N 49 34.233 E 23 22.322", according to the map calibration.
	 * 
	 * @param i the row of the position
	 * @param j the column of the position
	 * @return the prettified string
	 */
	public String localToPrettyCoordinates(const int i, const int j) {
		return coordinatesToPrettyCoordinates(localToCoordinates(i, j));
	}

	/**
	 * Convert a coordinate pair into a string of the form "N 49 34.233 E 23
	 * 22.322".
	 * 
	 * @param coord the coordinates to transofrm
	 * @return the prettified string
	 */
	public String coordinatesToPrettyCoordinates(const double[] coord) {
		FORMATER.setMaximumFractionDigits(PRETTY_COORDINATE_PRECISION);

		double angle = Math.abs(coord[0]);
		String lat =
				(((int) Math.floor(angle)) + " " + FORMATER
						.format((angle % 1) * MINUTES_PER_DEGREE));

		angle = Math.abs(coord[1]);
		String lon =
				(((int) Math.floor(angle)) + " " + FORMATER
						.format((angle % 1) * MINUTES_PER_DEGREE));

		if (!crossesZeroes) {
			return latHemisphere + " " + lat + " " + lonHemisphere + " "
					+ lon;
		} else {
			return getHemisphereByLatitude(coord[0]) + " " + lat + " "
					+ getHemisphereByLongitude(coord[1]) + " " + lon;
		}
	}

	/**
	 * Returns the latitude and longitude corresponding to the map internal
	 * row i and column j.
	 * 
	 * @param i the row
	 * @param j the column
	 * @return a double[2] with the latitude in position 0, and the
	 *         longitudein position 1.
	 */
	public double[] localToCoordinates(const int i, const int j) {
		double x = jFactor * j;
		double y = iFactor * (height - i);

		double[] coordinate = new double[2];
		// latitude
		coordinate[0] = x * sinA + y * cosA + blLat;

		// longitude
		coordinate[1] = x * cosA - y * sinA + blLon;

		return coordinate;
	}

	/**
	 * Returns the latitude and longitude corresponding to the map internal
	 * row and column given by the Position parameter.
	 * 
	 * @param pos the position to convert
	 * @return a double[2] with the latitude in position 0, and the
	 *         longitudein position 1.
	 */
	public double[] localToCoordinates(const Position pos) {
		return localToCoordinates(pos.getRow(), pos.getCol());
	}

	/**
	 * Returns the map row and column corresponding to the given coordinates.
	 * 
	 * @param lat the latitude
	 * @param lon the longitude
	 * @return a Position with the Siafu position matching the given
	 *         coordinates
	 */
	public Position coordinatesToLocal(const double lat, const double lon) {
		double y = -(lon * sinA) + lat * cosA + yOffset;
		double x = lon * cosA + lat * sinA + xOffset;

		int i = (int) Math.floor(height * (1 - (y / mapHeightDegrees)));
		int j = (int) Math.floor(xFactor * x);

		return new Position(i, j);
	}

	/**
	 * Get the name of the hemisphere for this latitude.
	 * 
	 * @param latitude a double with the latitude
	 * @return "N" if the latitude is 0 or above degrees, "S" otherwise
	 */
	String getHemisphereByLatitude(const double latitude) {
		if (latitude < 0) {
			return "S";
		} else {
			return "N";
		}
	}

	/**
	 * Get the name of the hemisphere for this longitude.
	 * 
	 * @param longitude a double with the longitude
	 * @return "E" if the latitude is 0 or above degrees, "W" otherwise
	 */
	String getHemisphereByLongitude(const double longitude) {
		if (longitude < 0) {
			return "W";
		} else {
			return "E";
		}
	}
};

#endif
