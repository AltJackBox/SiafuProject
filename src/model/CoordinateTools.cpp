#include <model/CoordinateTools.h>
#include <cmath>

CoordinateTools::CoordinateTools(const int height, const int width, const double topRight[] , const double bottomRight[] , const double bottomLeft[] ) {
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
				|| std::signum(blLat) != Math.signum(trLat)
				|| Math.signum(blLat) != Math.signum(trLat - brLat)
				|| Math.signum(blLon) != Math.signum(trLon - brLon)) {
			crossesZeroes = true;
			latHemisphere = "";
			lonHemisphere = "";
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