//
// Created by Abiel on 8/24/18.
//

#ifndef BOTBUSTERSREBIRTH_MATHUTIL_H
#define BOTBUSTERSREBIRTH_MATHUTIL_H

#include <limits>
#include <type_traits>
#include <cmath>

class Point2D;

namespace MathUtil {
	static constexpr double doubleEpsilon = std::numeric_limits<double>::epsilon();
	static constexpr int defaultUlp = 6;

	template<class T>
	typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
	almostEqual(T x, T y, int ulp = defaultUlp) {
		// the machine epsilon has to be scaled to the magnitude of the values used
		// and multiplied by the desired precision in ULPs (units in the last place)
		return std::abs(x - y) <= std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp
		       // unless the result is subnormal
		       || std::abs(x - y) < std::numeric_limits<T>::min();
	}

	bool almostEqual(double n1, double n2, double tresh);

	/**
	 * Limits a number between min and max
	 * @tparam T
	 * @param n
	 * @param min
	 * @param max
	 * @return
	 */
	double limitNumber(double n, double min, double max);

	/**
	 * Gets a number between a and b
	 * @param a
	 * @param b
	 * @param t
	 * @return
	 */
	double linearInterpolation(double a, double b, double t);

	/**
     * Fits a parabola to 3 points
     *
     * @return the x coordinate of the vertex of the parabola
     */
	double fitParabola(const Point2D &p1, const Point2D &p2, const Point2D &p3);
}

#endif //BOTBUSTERSREBIRTH_MATHUTIL_H
