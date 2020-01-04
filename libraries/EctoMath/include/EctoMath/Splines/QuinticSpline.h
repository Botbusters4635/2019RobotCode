//
// Created by Abiel on 8/20/18.
//

#ifndef BOTBUSTERSREBIRTH_QUINTICSPLINE_H
#define BOTBUSTERSREBIRTH_QUINTICSPLINE_H

#include <vector>
#include <cmath>
#include <stdexcept>
#include <limits>
#include "Spline2D.h"

class Point2D;

class RobotPose2D;

class RobotPose2DCurvature;

class Rotation2D;

class QuinticSpline : public Spline2D{
public:
	QuinticSpline(const RobotPose2D &startingPose, const RobotPose2D &endingPose);

	RobotPose2D getStartingPose() const override;

	RobotPose2D getEndingPose() const override;

	Point2D getPoint(double t) const override;

	double getVelocity(double t) const override;

	double getCurvature(double t) const override;

	double getDCurvature(double t) const override;

	Rotation2D getHeading(double t) const override;

	//Sum of all splines in a vector
	static double sumDCurvature2(const std::vector<QuinticSpline> &splines);

	/**
	 * Optimizes splines, returns final sumDCurvature2
	 * @param splines
	 * @return
	 */
	static double optimizeSpline(std::vector<QuinticSpline> &splines);


private:
	QuinticSpline();

	static constexpr double samples = 100.0;
	static constexpr std::size_t maxIterations = 1000;
	static constexpr double minDelta = 0.001;
	static constexpr double stepSize = 1.0;

	static constexpr double epsilon = std::numeric_limits<double>::epsilon();

	QuinticSpline(double x0, double x1, double dx0, double dx1, double ddx0, double ddx1,
	              double y0, double y1, double dy0, double dy1, double ddy0, double ddy1);

	void computeCoefficients();

	double calc_dx(double t) const;

	double calc_ddx(double t) const;

	double calc_dddx(double t) const;

	double calc_dy(double t) const;

	double calc_ddy(double t) const;

	double calc_dddy(double t) const;

	double dCurvature2(double t) const;

	double sumDCurvature2() const;

	static void runOptimizationIteration(std::vector<QuinticSpline> &splines);

	double x0, x1, dx0, dx1, ddx0, ddx1, y0, y1, dy0, dy1, ddy0, ddy1;
	double ax, bx, cx, dx, ex, fx, ay, by, cy, dy, ey, fy;

	struct ControlPoint {
		double ddx, ddy;
	};
};


#endif //BOTBUSTERSREBIRTH_QUINTICSPLINE_H
