//
// Created by Abiel on 8/24/18.
//

#include "EctoMath/MathUtil.h"
#include "EctoMath/DataTypes/Point2D.h"

double MathUtil::fitParabola(const Point2D &p1, const Point2D &p2, const Point2D &p3) {
	double A = (p3.getX() * (p2.getY() - p1.getY()) + p2.getX() * (p1.getY() - p3.getY()) +
	            p1.getX() * (p3.getY() - p2.getY()));
	double B = (p3.getX() * p3.getX() * (p1.getY() - p2.getY()) + p2.getX() * p2.getX() * (p3.getY() - p1.getY()) +
	            p1.getX() * p1.getX() *
	            (p2.getY() - p3.getY()));
	return -B / (2.0 * A);
}

bool MathUtil::almostEqual(double n1, double n2, double tresh) {
	return std::abs(n1 - n2) < tresh;
}

double MathUtil::limitNumber(double n, double min, double max) {
	return std::min(max, std::max(min, n));
}

double MathUtil::linearInterpolation(double a, double b, double t) {
	t = limitNumber(t, 0.0, 1.0);

	return a + (b - a) * t;
}