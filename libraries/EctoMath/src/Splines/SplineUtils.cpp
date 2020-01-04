//
// Created by Abiel on 8/29/18.
//

#include "EctoMath/Splines/SplineUtils.h"
#include "EctoMath/Splines/QuinticSpline.h"
#include "EctoMath/DataTypes/Point2D.h"
#include "EctoMath/DataTypes/Rotation2D.h"
#include "EctoMath/DataTypes/RobotPose2D.h"
#include "EctoMath/DataTypes/RobotPose2DCurvature.h"
#include "EctoMath/DataTypes/Twist2D.h"

Point2D SplineUtils::splineCoords(const Spline &s, double percentage) {
    //Limit percentage to 0 - 1
	percentage = percentage > 1 ? 1 : percentage;
	percentage = percentage < 0 ? 0 : percentage;

	double x = percentage * s.knot_distance;
	double y = (s.a * x + s.b) *
	           pow(x, 4) + (s.c * x + s.d) *
	                       pow(x, 2) + s.e * x; //Magic thing that does magical things

	double cos_theta = cos(s.angle_offset);
	double sin_theta = sin(s.angle_offset);

	return {
			x * cos_theta - y * sin_theta + s.x_offset,
			x * sin_theta + y * cos_theta + s.y_offset
	};
}

double SplineUtils::splineDeriv2(const Spline &s, double knot_distance, double p) {
	double x = p * knot_distance;

	return (5 * s.a * x + 4 * s.b) + pow(x, 3) + (3 * s.c * x + 2 * s.d) * x + s.e;
}

double SplineUtils::splineDistance(Spline &s, double sample_count) {
	double arc_length = 0, t = 0, dydt = 0;

	double deriv0 = splineDeriv2(s, s.knot_distance, 0);

	double integrand = 0;
	double last_integrand = sqrt(1 + pow(deriv0, 2)) / sample_count;

	for (unsigned int i = 0; i <= (unsigned int) sample_count; i++) {
		t = i / sample_count;

		dydt = splineDeriv2(s, s.knot_distance, t);

		integrand = sqrt(1 + pow(dydt, 2)) / sample_count;

		arc_length += (integrand + last_integrand) / 2;
		last_integrand = integrand;
	}

	arc_length = s.knot_distance * arc_length;
	s.arc_length = arc_length;
	return arc_length;
}

double SplineUtils::progressSplineDistance(const Spline &s, double distance, double sample_count) {
	double arc_length = 0, t = 0, dydt = 0, last_arc_length = 0;

	double deriv0 = splineDeriv2(s, s.knot_distance, 0);

	double integrand = 0;
	double last_integrand = sqrt(1 + pow(deriv0, 2)) / sample_count;

	distance /= s.knot_distance;

	for (unsigned int i = 0; i <= (unsigned int) sample_count; i++) {
		t = i / sample_count;

		dydt = splineDeriv2(s, s.knot_distance, t);

		integrand = sqrt(1 + pow(dydt, 2)) / sample_count;

		arc_length += (integrand + last_integrand) / 2;

		if (arc_length > distance)
			break;

		last_integrand = integrand;
		last_arc_length = arc_length;
	}

	double interpolated = t;

	if (arc_length != last_arc_length) {
		interpolated += ((distance - last_arc_length)
		                 / (arc_length - last_arc_length) - 1) / sample_count;
	}

	return interpolated;
}

std::vector<RobotPose2DCurvature> SplineUtils::parametrizeSpline(const QuinticSpline &spline, double t0, double t1,
                                                                 double maxDx, double maxDy, double maxDTheta) {
	std::vector<RobotPose2DCurvature> output;

	output.emplace_back(spline.getRobotPose2DCurvature(0.0));

	double dt = t1 - t0;

	for (double t = 0; t <= t1; t += dt / minSampleSize) {
		getSegmentArc(output, spline, t, t + dt / minSampleSize, maxDx, maxDy, maxDTheta);
	}

	return output;
}

std::vector<RobotPose2DCurvature>
SplineUtils::parametrizeSplines(const std::vector<QuinticSpline> &splines, double maxDx,
                                double maxDy, double maxDTheta) {
	std::vector<RobotPose2DCurvature> output;

	if (splines.empty())
		return output;

	output.emplace_back(splines.at(0).getRobotPose2DCurvature(0.0));

	for (const QuinticSpline &spline : splines) {
		std::vector<RobotPose2DCurvature> samples = parametrizeSpline(spline, 0.0, 1.0, maxDx, maxDy, maxDTheta);
		samples.erase(samples.begin());

		//Combine output and samples
		output.insert(
				output.end(),
				std::make_move_iterator(samples.begin()),
				std::make_move_iterator(samples.end())
		);
	}

	return output;
}

void SplineUtils::getSegmentArc(std::vector<RobotPose2DCurvature> &returnArc, const QuinticSpline &spline, double t0,
                                double t1, double maxDx, double maxDy, double maxDTheta) {

	Point2D p0 = spline.getPoint(t0);
	Point2D p1 = spline.getPoint(t1);

	Rotation2D r0 = spline.getHeading(t0);
	Rotation2D r1 = spline.getHeading(t1);

	RobotPose2D trans(Point2D(p0, p1).rotateBy(r0.inverse()), r1.rotateBy(r0.inverse()));
	Twist2D twist = RobotPose2D::log(trans);

	if (twist.getDy() > maxDy || twist.getDx() > maxDx || twist.getDtheta() > maxDTheta) {
		getSegmentArc(returnArc, spline, t0, (t0 + t1) / 2.0, maxDx, maxDy, maxDTheta);
		getSegmentArc(returnArc, spline, (t0 + t1) / 2.0, t1, maxDx, maxDy, maxDTheta);
	} else {
		returnArc.emplace_back(spline.getRobotPose2DCurvature(t1));
	}
}