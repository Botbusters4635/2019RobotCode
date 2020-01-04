//
// Created by Abiel on 8/29/18.
//

#ifndef BOTBUSTERSREBIRTH_SPLINEUTILS_H
#define BOTBUSTERSREBIRTH_SPLINEUTILS_H

#include <vector>
#include "EctoMath/DataTypes/Point2D.h"

class QuinticSpline;

class RobotPose2DCurvature;

namespace SplineUtils {
    struct Spline {
        double a, b, c, d, e;
        double x_offset, y_offset, angle_offset, knot_distance, arc_length;
    };

    Point2D splineCoords(const Spline &s, double percentage);

    double splineDeriv2(const Spline &s, double knot_distance, double p);

    double splineDistance(Spline &s, double sample_count);

    double progressSplineDistance(const Spline &s, double distance, double sample_count);

	//TODO Set default maximums
	const double maxDx = .08;
	const double maxDy = 0.001;
	const double maxDTheta = 0.1;
	const double minSampleSize = 1.0;

	std::vector<RobotPose2DCurvature> parametrizeSpline(const QuinticSpline &spline,
	                                                    double t0 = 0.0, double t1 = 1.0, double maxDx = maxDx,
	                                                    double maxDy = maxDy, double maxDTheta = maxDTheta);

	std::vector<RobotPose2DCurvature>
	parametrizeSplines(const std::vector<QuinticSpline> &splines, double maxDx = maxDx, double maxDy = maxDy,
	                   double maxDTheta = maxDTheta);

	void getSegmentArc(std::vector<RobotPose2DCurvature> &returnArc, const QuinticSpline &spline, double t0, double t1,
	                   double maxDx, double maxDy, double maxDTheta);
}

#endif //BOTBUSTERSREBIRTH_SPLINEUTILS_H
