//
// Created by Abiel on 8/18/18.
//

#include "EctoMath/Splines/Spline2D.h"

RobotPose2D Spline2D::getRobotPose2D(double t) const {
	return {getPoint(t), getHeading(t)};
}

RobotPose2DCurvature Spline2D::getRobotPose2DCurvature(double t) const {
	return {getRobotPose2D(t), getCurvature(t), getDCurvature(t)};
}