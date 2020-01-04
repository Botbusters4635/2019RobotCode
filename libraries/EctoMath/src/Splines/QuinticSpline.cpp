//
// Created by Abiel on 8/20/18.
//

#include "EctoMath/Splines/QuinticSpline.h"
#include "EctoMath/MathUtil.h"
#include "EctoMath/DataTypes/Point2D.h"
#include "EctoMath/DataTypes/RobotPose2D.h"
#include "EctoMath/DataTypes/RobotPose2DCurvature.h"

QuinticSpline::QuinticSpline() {
	;
}

QuinticSpline::QuinticSpline(const RobotPose2D &startingPose, const RobotPose2D &endingPose) {
	double scale = 1.2 * startingPose.getPoint().getDistance(endingPose.getPoint());
	x0 = startingPose.getPoint().getX();
	x1 = endingPose.getPoint().getX();

	dx0 = startingPose.getHeading().getCos() * scale;
	dx1 = endingPose.getHeading().getCos() * scale;

	ddx0 = 0;
	ddx1 = 0;

	y0 = startingPose.getPoint().getY();
	y1 = endingPose.getPoint().getY();

	dy0 = startingPose.getHeading().getSin() * scale;
	dy1 = endingPose.getHeading().getSin() * scale;

	ddy0 = 0;
	ddy1 = 0;

	computeCoefficients();
}

QuinticSpline::QuinticSpline(double x0, double x1, double dx0, double dx1, double ddx0, double ddx1, double y0,
                             double y1, double dy0, double dy1, double ddy0, double ddy1) {
	this->x0 = x0;
	this->x1 = x1;

	this->dx0 = dx0;
	this->dx1 = dx1;

	this->ddx0 = ddx0;
	this->ddx1 = ddx1;

	this->y0 = y0;
	this->y1 = y1;

	this->dy0 = dy0;
	this->dy1 = dy1;

	this->ddy0 = ddy0;
	this->ddy1 = ddy1;

	computeCoefficients();
}

void QuinticSpline::computeCoefficients() {
	ax = -6.0 * x0 - 3.0 * dx0 - 0.5 * ddx0 + 0.5 * ddx1 - 3.0 * dx1 + 6.0 * x1;
	bx = 15.0 * x0 + 8.0 * dx0 + 1.5 * ddx0 - ddx1 + 7.0 * dx1 - 15.0 * x1;
	cx = -10.0 * x0 - 6.0 * dx0 - 1.5 * ddx0 + 0.5 * ddx1 - 4.0 * dx1 + 10.0 * x1;
	dx = 0.5 * ddx0;
	ex = dx0;
	fx = x0;

	ay = -6.0 * y0 - 3.0 * dy0 - 0.5 * ddy0 + 0.5 * ddy1 - 3.0 * dy1 + 6.0 * y1;
	by = 15.0 * y0 + 8.0 * dy0 + 1.5 * ddy0 - ddy1 + 7.0 * dy1 - 15.0 * y1;
	cy = -10.0 * y0 - 6.0 * dy0 - 1.5 * ddy0 + 0.5 * ddy1 - 4.0 * dy1 + 10.0 * y1;
	dy = 0.5 * ddy0;
	ey = dy0;
	fy = y0;
}

RobotPose2D QuinticSpline::getStartingPose() const {
	return {Point2D(x0, y0), Rotation2D(dx0, dy0, true)};
}

RobotPose2D QuinticSpline::getEndingPose() const {
	return {Point2D(x1, y1), Rotation2D(dx1, dy1, true)};
}

Point2D QuinticSpline::getPoint(double t) const {
	double x = ax * pow(t, 5.0) + bx * pow(t, 4.0) + cx * pow(t, 3.0) + dx * pow(t, 2.0) + ex * t + fx;
	double y = ay * pow(t, 5.0) + by * pow(t, 4.0) + cy * pow(t, 3.0) + dy * pow(t, 2.0) + ey * t + fy;
	return {x, y};
}

double QuinticSpline::calc_dx(double t) const {
	return 5.0 * ax * pow(t, 4.0) + 4.0 * bx * pow(t, 3.0) + 3.0 * cx * pow(t, 2.0) + 2 * dx * t + ex;
}

double QuinticSpline::calc_ddx(double t) const {
	return 20.0 * ax * pow(t, 3.0) + 12.0 * bx * pow(t, 2.0) + 6.0 * cx * t + 2.0 * dx;
}

double QuinticSpline::calc_dddx(double t) const {
	return 60.0 * ax * pow(t, 2.0) + 24.0 * bx * t + 6.0 * cx;
}

double QuinticSpline::calc_dy(double t) const {
	return 5.0 * ay * pow(t, 4.0) + 4.0 * by * pow(t, 3.0) + 3.0 * cy * pow(t, 2.0) + 2 * dy * t + ey;
}

double QuinticSpline::calc_ddy(double t) const {
	return 20.0 * ay * pow(t, 3.0) + 12.0 * by * pow(t, 2.0) + 6.0 * cy * t + 2.0 * dy;
}

double QuinticSpline::calc_dddy(double t) const {
	return 60.0 * ay * pow(t, 2.0) + 24.0 * by * t + 6.0 * cy;
}

double QuinticSpline::getVelocity(double t) const {
	return hypot(calc_dx(t), calc_dy(t));
}

double QuinticSpline::getCurvature(double t) const {
	return (calc_dx(t) * calc_ddy(t) - calc_ddx(t) * calc_dy(t))
	       / ((calc_dx(t) * calc_dx(t) + calc_dy(t) * calc_dy(t))
	          * sqrt((calc_dx(t) * calc_dx(t) + calc_dy(t) * calc_dy(t))));
}

double QuinticSpline::getDCurvature(double t) const {
	double dx2dy2 = (calc_dx(t) * calc_dx(t) + calc_dy(t) * calc_dy(t));

	double num = (calc_dx(t) * calc_dddy(t) - calc_dddx(t) * calc_dy(t))
	             * dx2dy2 - 3.0 *
	                        (calc_dx(t) * calc_ddy(t) - calc_ddx(t) * calc_dy(t))
	                        * (calc_dx(t) * calc_ddx(t) + calc_dy(t) * calc_ddy(t));

	return num / (dx2dy2 * dx2dy2 * sqrt(dx2dy2));
}

double QuinticSpline::dCurvature2(double t) const {
	double dx2dy2 = (pow(calc_dx(t), 2.0) + pow(calc_dy(t), 2.0));

	double num = (calc_dx(t) * calc_dddy(t) - calc_dddx(t) * calc_dy(t))
	             * dx2dy2 - 3.0 * (calc_dx(t) * calc_ddy(t) - calc_ddx(t) * calc_dy(t))
	                        * (calc_dx(t) * calc_ddx(t) + calc_dy(t) * calc_ddy(t));

	return pow(num, 2.0) / (pow(dx2dy2, 5.0));
}

Rotation2D QuinticSpline::getHeading(double t) const {
	return Rotation2D(calc_dx(t), calc_dy(t), true);
}

double QuinticSpline::sumDCurvature2() const {
	double dt = 1.0 / samples;
	double sum = 0;
	for (double t = 0; t < 1.0; t += dt) {
		sum += (dt * dCurvature2(t));
	}

	return sum;
}

double QuinticSpline::sumDCurvature2(const std::vector<QuinticSpline> &splines) {
	double sum = 0;

	for (const QuinticSpline &s : splines) {
		sum += s.sumDCurvature2();
	}

	return sum;
}

double QuinticSpline::optimizeSpline(std::vector<QuinticSpline> &splines) {
	double prev = sumDCurvature2(splines);

	for (std::size_t i = 0; i < maxIterations; ++i) {
		runOptimizationIteration(splines);
		double current = sumDCurvature2(splines);

		if (prev - current < minDelta)
			return current;

		prev = current;
	}

	return prev;
}

void QuinticSpline::runOptimizationIteration(std::vector<QuinticSpline> &splines) {
	//Check if vector contains less than 2 splines, returns if it only has one spline
	if (splines.size() <= 1)
		throw std::runtime_error("Tried to run an optimization iteration with less than two splines");

	std::vector<ControlPoint> controlPoints;
	double magnitude = 0;

	for (std::size_t i = 0; i < splines.size() - 1; i++) {
		//don't try to optimize colinear points
		if (splines.at(i).getStartingPose().isColinear(splines.at(i + 1).getStartingPose()) ||
		    splines.at(i).getEndingPose().isColinear(splines.at(i + 1).getEndingPose())) {
			continue;
		}

		double original = sumDCurvature2(splines);
		QuinticSpline temp, temp1;

		temp = splines.at(i);
		temp1 = splines.at(i + 1);

		controlPoints.emplace_back();

		//calculate partial derivatives of sumDCurvature2
		splines[i] = QuinticSpline(temp.x0, temp.x1, temp.dx0, temp.dx1, temp.ddx0, temp.ddx1 + MathUtil::doubleEpsilon,
		                           temp.y0, temp.y1, temp.dy0, temp.dy1, temp.ddy0, temp.ddy1);
		splines[i + 1] = QuinticSpline(temp1.x0, temp1.x1, temp1.dx0, temp1.dx1, temp1.ddx0 + MathUtil::doubleEpsilon,
		                               temp1.ddx1, temp1.y0, temp1.y1, temp1.dy0, temp1.dy1, temp1.ddy0, temp1.ddy1);

		controlPoints[i].ddx = (sumDCurvature2(splines) - original) / MathUtil::doubleEpsilon;

		splines[i] = QuinticSpline(temp.x0, temp.x1, temp.dx0, temp.dx1, temp.ddx0, temp.ddx1, temp
				.y0, temp.y1, temp.dy0, temp.dy1, temp.ddy0, temp.ddy1 + MathUtil::doubleEpsilon);
		splines[i + 1] = QuinticSpline(temp1.x0, temp1.x1, temp1.dx0, temp1.dx1, temp1.ddx0,
		                               temp1.ddx1, temp1.y0, temp1.y1, temp1.dy0, temp1.dy1,
		                               temp1.ddy0 + MathUtil::doubleEpsilon, temp1.ddy1);

		controlPoints[i].ddy = (sumDCurvature2(splines) - original) / MathUtil::doubleEpsilon;

		splines[i] = temp;
		splines[i + 1] = temp;

		magnitude += std::pow(controlPoints[i].ddx, 2.0) + std::pow(controlPoints[i].ddy, 2.0);
	}

	magnitude = std::sqrt(magnitude);

	//minimize along the direction of the gradient
	//first calculate 3 points along the direction of the gradient
	Point2D p1, p2, p3;
	p2 = Point2D(0.0, sumDCurvature2(splines)); //middle point is at the current location

	for (std::size_t i = 0; i < splines.size() - 1; ++i) {
		if (splines.at(i).getStartingPose().isColinear(splines.at(i + 1).getStartingPose()) ||
		    splines.at(i).getEndingPose().isColinear(splines.at(i + 1).getEndingPose()))
			continue;

		//normalize to step size
		controlPoints[i].ddx *= stepSize / magnitude;
		controlPoints[i].ddy *= stepSize / magnitude;

		//move opposite the gradient by step size amount
		splines.at(i).ddx1 -= controlPoints[i].ddx;
		splines.at(i).ddy1 -= controlPoints[i].ddy;
		splines.at(i + 1).ddx0 -= controlPoints[i].ddx;
		splines.at(i + 1).ddy0 -= controlPoints[i].ddy;

		//recompute the spline's coefficients to account for new second derivatives
		splines.at(i).computeCoefficients();
		splines.at(i + 1).computeCoefficients();
	}

	p1 = Point2D(-stepSize, sumDCurvature2(splines));

	for (std::size_t i = 0; i < splines.size() - 1; ++i) {
		if (splines.at(i).getStartingPose().isColinear(splines.at(i + 1).getStartingPose()) ||
		    splines.at(i).getEndingPose().isColinear(splines.at(i + 1).getEndingPose()))
			continue;

		//move along the gradient by 2 times the step size amount (to return to original location and move by 1
		// step)
		splines.at(i).ddx1 += 2.0 * controlPoints[i].ddx;
		splines.at(i).ddy1 += 2.0 * controlPoints[i].ddy;
		splines.at(i + 1).ddx0 += 2.0 * controlPoints[i].ddx;
		splines.at(i + 1).ddy0 += 2.0 * controlPoints[i].ddy;

		//recompute the spline's coefficients to account for new second derivatives
		splines.at(i).computeCoefficients();
		splines.at(i + 1).computeCoefficients();
	}

	p3 = Point2D(stepSize, sumDCurvature2(splines));

	double splineStepSize = MathUtil::fitParabola(p1, p2, p3);

	for (size_t i = 0; i < splines.size() - 1; ++i) {
		if (splines.at(i).getStartingPose().isColinear(splines.at(i + 1).getStartingPose()) ||
		    splines.at(i).getEndingPose().isColinear(splines.at(i + 1).getEndingPose()))
			continue;

		//move by the step size calculated by the parabola fit (+1 to offset for the final transformation to find
		// p3)
		controlPoints[i].ddx *= 1 + splineStepSize / stepSize;
		controlPoints[i].ddy *= 1 + splineStepSize / stepSize;

		splines.at(i).ddx1 += controlPoints[i].ddx;
		splines.at(i).ddy1 += controlPoints[i].ddy;
		splines.at(i + 1).ddx0 += controlPoints[i].ddx;
		splines.at(i + 1).ddy0 += controlPoints[i].ddy;

		//recompute the spline's coefficients to account for new second derivatives
		splines.at(i).computeCoefficients();
		splines.at(i + 1).computeCoefficients();
	}
}